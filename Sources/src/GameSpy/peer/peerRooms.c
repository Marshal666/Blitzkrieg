/*
GameSpy Peer SDK 
Dan "Mr. Pants" Schoenblum
dan@gamespy.com

Copyright 1999-2001 GameSpy Industries, Inc

18002 Skypark Circle
Irvine, California 92614
949.798.4200 (Tel)
949.798.4299 (Fax)
devsupport@gamespy.com
*/

/*************
** INCLUDES **
*************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "peerRooms.h"
#include "peerPlayers.h"
#include "peerMangle.h"
#include "peerCallbacks.h"
#include "peerGlobalCallbacks.h"
#include "peerKeys.h"

/************
** DEFINES **
************/
#define PI_QUERYPORT    6500

/**************
** FUNCTIONS **
**************/
PEERBool piRoomsInit
(
	PEER peer
)
{
	RoomType roomType;

	PEER_CONNECTION;

	// Init rooms.
	//////////////
	for(roomType = 0 ; roomType < NumRooms ; roomType++)
	{
		if(connection->stayInTitleRoom && (roomType == TitleRoom))
			continue;

		ROOM[0] = '\0';
		NAME[0] = '\0';
		ENTERING_ROOM = PEERFalse;
		IN_ROOM = PEERFalse;
		connection->cancelJoinRoom[roomType] = PEERFalse;
		connection->oldFlags[roomType] = 0;
	}
	connection->groupID = 0;
	connection->titleRoomChannel[0] = '\0';

	return PEERTrue;
}

void piRoomsCleanup
(
	PEER peer
)
{
	RoomType roomType;

	PEER_CONNECTION;

	// Check all the rooms.
	///////////////////////
	for(roomType = 0 ; roomType < NumRooms ; roomType++)
	{
		if(connection->stayInTitleRoom && (roomType == TitleRoom))
			continue;

		// Are we in or entering the room?
		//////////////////////////////////
		if(IN_ROOM || ENTERING_ROOM)
		{
			// Leave it.
			////////////
			piLeaveRoom(peer, roomType, NULL);
		}
		ROOM[0] = '\0';
		NAME[0] = '\0';
		ENTERING_ROOM = PEERFalse;
		IN_ROOM = PEERFalse;
		connection->cancelJoinRoom[roomType] = PEERFalse;
	}
	connection->titleRoomChannel[0] = '\0';
}

void piStartedEnteringRoom
(
	PEER peer,
	RoomType roomType,
	const char * room
)
{
	PEER_CONNECTION;

	ASSERT_ROOMTYPE(roomType);
	assert(room);
	assert(room[0]);
	assert(strlen(room) < PI_ROOM_MAX_LEN);
	if(strlen(room) >= PI_ROOM_MAX_LEN)
		return;

	// Check that we're not entering, or in, this room.
	///////////////////////////////////////////////////
	assert(!ROOM[0]);
	assert(!ENTERING_ROOM);
	assert(!IN_ROOM);

	// Start entering.
	//////////////////
	strcpy(ROOM, room);
	ENTERING_ROOM = PEERTrue;
	connection->oldFlags[roomType] = 0;
}

void piFinishedEnteringRoom
(
	PEER peer,
	RoomType roomType,
	const char * name
)
{
	PEER_CONNECTION;

	ASSERT_ROOMTYPE(roomType);

	if(!name)
		name = "";

	// Check that we're entering.
	/////////////////////////////
	assert(ROOM[0]);
	assert(ENTERING_ROOM);
	assert(!IN_ROOM);
	assert(strlen(name) < PI_ROOM_MAX_LEN);

	// We're in.
	////////////
	IN_ROOM = PEERTrue;
	ENTERING_ROOM = PEERFalse;
	strzcpy(NAME, name, PI_NAME_MAX_LEN);

	// Set the flags.
	/////////////////
	piSetLocalFlags(peer);

	// Refresh the watch keys for this room.
	////////////////////////////////////////
	piKeyCacheRefreshRoom(peer, roomType);
}

PEERBool piStartHosting
(
	PEER peer,
	SOCKET socket
)
{
	PEER_CONNECTION;

	// Check that we're not hosting.
	////////////////////////////////
	assert(!connection->hosting);
	if(connection->hosting)
		return PEERFalse;

	// Set states.
	//////////////
	connection->hosting = PEERTrue;
	strcpy(connection->gamename, connection->title);
	if(connection->inRoom[GroupRoom])
		connection->reportingGroupID = connection->groupID;
	else
		connection->reportingGroupID = 0;

	// Start reporting.
	///////////////////
	piStartReporting(peer, socket);

	return PEERTrue;
}

void piResetHosting
(
	PEER peer
)
{
	PEER_CONNECTION;

	// Check that we're hosting.
	////////////////////////////
	assert(connection->hosting);
	if(!connection->hosting)
		return;

	// Reset.
	/////////
	assert(connection->queryReporting);
	qr_send_statechanged(connection->queryReporting);
}

void piStopHosting
(
	PEER peer
)
{
	PEER_CONNECTION;

	// Check that we're hosting.
	////////////////////////////
	assert(connection->hosting);
	if(!connection->hosting)
		return;

	// Stop reporting.
	//////////////////
	if(connection->reporting)
		piStopReporting(peer);

	// Reset states.
	////////////////
	connection->hosting = PEERFalse;
	connection->playing = PEERFalse;
	connection->ready = PEERFalse;

	// Set the flags.
	/////////////////
	piSetLocalFlags(peer);
}

PEERBool piStartReporting
(
	PEER peer,
	SOCKET socket
)
{
	int rcode;

	PEER_CONNECTION;

	// Check that we're not reporting.
	//////////////////////////////////
	assert(!connection->reporting);
	if(connection->reporting)
		piStopReporting(peer);

	// Init goa.
	////////////
	if(socket == INVALID_SOCKET)
	{
		int nPort = PI_QUERYPORT;
		rcode = qr_init(&connection->queryReporting, NULL, &nPort, connection->title, connection->qrSecretKey,
			piGOABasicCallback,
			piGOAInfoCallback,
			piGOARulesCallback,
			piGOAPlayersCallback,
			peer);
	}
	else
	{
		rcode = qr_init_socket(&connection->queryReporting, socket, connection->title, connection->qrSecretKey,
			piGOABasicCallback,
			piGOAInfoCallback,
			piGOARulesCallback,
			piGOAPlayersCallback,
			peer);
	}

	if(rcode != 0)
		return PEERFalse;

	// We're reporting.
	///////////////////
	connection->reporting = PEERTrue;
	
	// No options.
	//////////////
	connection->reportingOptions = 0;

	return PEERTrue;
}

void piStopReporting
(
	PEER peer
)
{
	PEER_CONNECTION;

	// Check that we're reporting.
	//////////////////////////////
	if(!connection->reporting)
		return;

	// Clean up GOA.
	////////////////
	assert(connection->queryReporting);
	//crt - 4/18/01 - use send exiting for faster removal
	qr_send_exiting(connection->queryReporting);
	qr_shutdown(connection->queryReporting);
	connection->queryReporting = NULL;
	connection->reporting = PEERFalse;
}

void piLeaveRoom
(
	PEER peer,
	RoomType roomType,
	const char * reason
)
{
	PEER_CONNECTION;

	ASSERT_ROOMTYPE(roomType);

	assert(ROOM[0]);

	// Check that we're in/entering this room.
	//////////////////////////////////////////
	if(!ENTERING_ROOM && !IN_ROOM)
	{
		assert(0);
		return;
	}

	// Leave the channel.
	/////////////////////
	if(connection->connected)
		chatLeaveChannel(connection->chat, ROOM, reason);

	// Clear all the players out of this room.
	//////////////////////////////////////////
	piClearRoomPlayers(peer, roomType);

	// Reset in/entering states.
	////////////////////////////
	if(IN_ROOM)
	{
		assert(!ENTERING_ROOM);
		IN_ROOM = PEERFalse;
	}
	else
	{
		assert(ENTERING_ROOM);
		ENTERING_ROOM = PEERFalse;
	}

	// Clear the room/name.
	///////////////////////
	ROOM[0] = '\0';
	NAME[0] = '\0';

	// Clear the flags.
	///////////////////
	connection->oldFlags[roomType] = 0;

	// Staging room?
	////////////////
	if(roomType == StagingRoom)
	{
		// Hosting?
		///////////
		if(connection->hosting)
		{
			// Are we playing, or reporting, but not both?
			//////////////////////////////////////////////
			if((connection->playing && !connection->reporting) || (!connection->playing && connection->reporting))
			{
				// Stop hosting.
				////////////////
				piStopHosting(peer);
			}
		}

		// No game server.
		//////////////////
		connection->gameServer = NULL;

		// No server IP.
		////////////////
		connection->serverIP = INADDR_NONE;

		// Turn ready off.
		//////////////////
		connection->ready = PEERFalse;

		// Set the flags.
		/////////////////
		piSetLocalFlags(peer);
	}

	// Cleanse the key cache.
	/////////////////////////
	piKeyCacheCleanse(peer);
}

PEERBool piRoomToType
(
	PEER peer,
	const char * room,
	RoomType * roomType
)
{
	int i;

	PEER_CONNECTION;

	for(i = 0 ; i < NumRooms ; i++)
	{
		if(strcasecmp(room, ROOMS[i]) == 0)
		{
			*roomType = (RoomType)i;
			return PEERTrue;
		}
	}

	return PEERFalse;
}

void piSetLocalFlags
(
	PEER peer
)
{
	char buffer[NumRooms][128];
	char * titleRoom;
	char * groupRoom;
	char * stagingRoom;
	const char * key = "b_flags";
	int nFlags;

	PEER_CONNECTION;
	
	if(!connection->connected)
		return;

	if(connection->inRoom[TitleRoom] || connection->enteringRoom[TitleRoom])
		titleRoom = buffer[TitleRoom];
	else
		titleRoom = NULL;
	if(connection->inRoom[GroupRoom] || connection->enteringRoom[GroupRoom])
		groupRoom = buffer[GroupRoom];
	else
		groupRoom = NULL;
	if(connection->inRoom[StagingRoom] || connection->enteringRoom[StagingRoom])
		stagingRoom = buffer[StagingRoom];
	else
		stagingRoom = NULL;

	// Check for staging room.
	//////////////////////////
	if(connection->inRoom[StagingRoom])
	{
		if(titleRoom)
			*titleRoom++ = 's';
		if(groupRoom)
			*groupRoom++ = 's';
		*stagingRoom++ = 's';

		// Check for ready.
		///////////////////
		if(connection->ready)
			*stagingRoom++ = 'r';
	}

	// Check for playing.
	/////////////////////
	if(connection->playing)
	{
		if(titleRoom)
			*titleRoom++ = 'g';
		if(groupRoom)
			*groupRoom++ = 'g';
		if(stagingRoom)
			*stagingRoom++ = 'g';
	}

	// Check for away.
	//////////////////
	if(connection->away)
	{
		if(titleRoom)
			*titleRoom++ = 'a';
		if(groupRoom)
			*groupRoom++ = 'a';
		if(stagingRoom)
			*stagingRoom++ = 'a';
	}

	// Cap it off.
	//////////////
	if(titleRoom)
	{
		*titleRoom = '\0';
		titleRoom = buffer[TitleRoom];
	}
	if(groupRoom)
	{
		*groupRoom = '\0';
		groupRoom = buffer[GroupRoom];
	}
	if(stagingRoom)
	{
		*stagingRoom = '\0';
		stagingRoom = buffer[StagingRoom];
	}

	// Set the keys.
	////////////////
	if(titleRoom)
	{
		nFlags = piParseFlags(titleRoom);
		if(nFlags != connection->oldFlags[TitleRoom])
		{
			chatSetChannelKeys(connection->chat, connection->rooms[TitleRoom], connection->nick, 1, &key, &titleRoom);
			connection->oldFlags[TitleRoom] = nFlags;
		}
	}
	if(groupRoom)
	{
		nFlags = piParseFlags(groupRoom);
		if(nFlags != connection->oldFlags[GroupRoom])
		{
			chatSetChannelKeys(connection->chat, connection->rooms[GroupRoom], connection->nick, 1, &key, &groupRoom);
			connection->oldFlags[GroupRoom] = nFlags;
		}
	}
	if(stagingRoom)
	{
		nFlags = piParseFlags(stagingRoom);
		if(nFlags != connection->oldFlags[StagingRoom])
		{
			chatSetChannelKeys(connection->chat, connection->rooms[StagingRoom], connection->nick, 1, &key, &stagingRoom);
			connection->oldFlags[StagingRoom] = nFlags;
		}
	}
}