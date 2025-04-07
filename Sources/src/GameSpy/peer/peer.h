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

#ifndef _PEER_H_
#define _PEER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*************
** INCLUDES **
*************/
#if defined(applec) || defined(THINK_C) || defined(__MWERKS__) && !defined(__KATANA__) && !defined(__mips64)
	#include "::nonport.h"
	#include "::Chat:chat.h"
	#include "::queryreporting:gqueryreporting.h"
	#include "::CEngine:goaceng.h"
#else
	#include "../nonport.h"
	#include "../Chat/chat.h"
	#include "../queryreporting/gqueryreporting.h"
	#include "../CEngine/goaceng.h"
#endif


/************
** DEFINES **
************/
// Defines for the msg param that's passed into peerListingGamesCallback().
// PANTS-04.20.00-changed from PI_* to PEER_*
///////////////////////////////////////////////////////////////////////////
#define PEER_ADD        0  // a server is being added
#define PEER_UPDATE     1  // a server has been updated
#define PEER_REMOVE     2  // a server has been removed
#define PEER_CLEAR      3  // all the servers have been cleared

// Nick-errors, for peerNickErrorCallback.
//////////////////////////////////////////
#define PEER_IN_USE     0  // the nick is already being used
#define PEER_INVALID    1  // the nick contains invalid characters

// Maximum length of a room password, including the terminating NUL.
////////////////////////////////////////////////////////////////////
#define PEER_PASSWORD_LEN     24

// Each player can have various flags set for each room they are in.
////////////////////////////////////////////////////////////////////
#define PEER_FLAG_STAGING     0x01  // s
#define PEER_FLAG_READY       0x02  // r
#define PEER_FLAG_PLAYING     0x04  // g
#define PEER_FLAG_AWAY        0x08  // a
#define PEER_FLAG_OP          0x10
#define PEER_FLAG_VOICE       0x20

// Bitfield reporting options for peerStartGame.
////////////////////////////////////////////////
#define PEER_KEEP_REPORTING      0  // Continue reporting.
#define PEER_STOP_REPORTING      1  // Stop reporting.  Cannot be used with other options.
#define PEER_REPORT_INFO         2  // Reports all info to the GOAInfo callback (as if it were not playing).
#define PEER_REPORT_PLAYERS      4  // Reports all info to the GOAPlayers callback (as if it were not playing).

/**********
** TYPES **
**********/
// The peer object.
///////////////////
typedef void * PEER;

// Boolean.
///////////
typedef enum
{
	PEERFalse,
	PEERTrue
} PEERBool;

// Types of rooms.
//////////////////
typedef enum
{
	TitleRoom,  // The main room for a game.
	GroupRoom,  // A room which is, in general, for a particular type of gameplay (team, dm, etc.).
	StagingRoom,  // A room where players meet before starting a game.
	NumRooms
} RoomType;

// Types of messages. These have the same
// values as their CHAT SDK counterparts.
// PANTS-01.08.01
/////////////////////////////////////////
typedef enum
{
	NormalMessage,
	ActionMessage,
	NoticeMessage
} MessageType;

// Possible results when attempting to join a room.
// Passed into peerJoinRoomCallback().
///////////////////////////////////////////////////
typedef enum
{
	PEERJoinSuccess,     // The room was joined.

	PEERFullRoom,        // The room is full.
	PEERInviteOnlyRoom,  // The room is invite only.
	PEERBannedFromRoom,  // The local user is banned from the room.
	PEERBadPassword,     // An incorrect password (or none) was given for a passworded room.

	PEERAlreadyInRoom,   // The local user is already in or entering a room of the same type.
	PEERNoTitleSet,      // Can't join a room if no title is set.
	PEERNoConnection,    // Can't join a room if there's no chat connection.

	PEERJoinFailed       // Generic failure.
} PEERJoinResult;

/**************
** CALLBACKS **
**************/
// Called when the connection to the server gets disconnected.
//////////////////////////////////////////////////////////////
typedef void (* peerDisconnectedCallback)
(
	PEER peer,  // The peer object.
	const char * reason,  // The reason for the disconnection.
	void * param  // User-data.
);

// Called when a message is sent to a room the local player is in.
//////////////////////////////////////////////////////////////////
typedef void (* peerRoomMessageCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the message was in.
	const char * nick,  // The nick of the player who sent the message.
	const char * message,  // The text of the message.
	MessageType messageType,  // The type of message.
	void * param  // User-data.
);

// Called when a UTM is sent to a room the local player is in.
//////////////////////////////////////////////////////////////
typedef void (* peerRoomUTMCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the UTM was in.
	const char * nick,  // The nick of the player who sent the UTM.
	const char * command, // The UTM command for this message.
	const char * parameters,  // Any parameters for this UTM.
	PEERBool authenticated,  // True if this has been authenticated by the server.
	void * param  // User-data.
);

// Called when the name of a room the player is in changes.
// The new name can be checked with peerGetRoomName.
// PANTS|09.11.00
///////////////////////////////////////////////////////////
typedef void (* peerRoomNameChangedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the name changed in.
	void * param  // User-data
);

// Called when a room's mode changes.
// PANTS|04.17.00
///////////////////////////////////////////////////////////
typedef void (* peerRoomModeChangedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the name changed in.
	CHATChannelMode * mode,  // The current mode for this room.
	void * param  // User-data
);

// Called when a private message is received from another player.
/////////////////////////////////////////////////////////////////
typedef void (* peerPlayerMessageCallback)
(
	PEER peer,  // The peer object.
	const char * nick,  // The nick of the player who sent the message.
	const char * message,  // The text of the message.
	MessageType messageType,  // The type of message.
	void * param  // User-data
);

// Called when a private UTM is received from another player.
/////////////////////////////////////////////////////////////
typedef void (* peerPlayerUTMCallback)
(
	PEER peer,  // The peer object.
	const char * nick,  // The nick of the player who sent the UTM.
	const char * command, // The UTM command for this message.
	const char * parameters,  // Any parameters for this UTM.
	PEERBool authenticated,  // True if this has been authenticated by the server.
	void * param  // User-data
);

// Called when a player's ready state changes,
// from a call to peerSetReady().
//////////////////////////////////////////////
typedef void (* peerReadyChangedCallback)
(
	PEER peer,  // The peer object.
	const char * nick,  // The nick of the player who's ready state changed.
	PEERBool ready,  // The player's new ready state.
	void * param  // User-data.
);

// Called when the host of a staging room launches the game,
// with a call to peerGameStart().
////////////////////////////////////////////////////////////
typedef void (* peerGameStartedCallback)
(
	PEER peer,  // The peer object.
	unsigned int IP,  // The IP of the host, in network-byte order. PANTS|09.11.00 - was unsigned long
	const char * message,  // A message that was passed into peerGameStart().
	void * param  // User-data.
);

// A player joined a room.
//////////////////////////
typedef void (* peerPlayerJoinedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the player joined.
	const char * nick,  // The nick of the player that joined.
	void * param  // User-data.
);

// A player left a room.
////////////////////////
typedef void (* peerPlayerLeftCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the player left.
	const char * nick,  // The nick of the player that left.
	const char * reason,  // The reason the player left.
	void * param  // User-data.
);

// The local player was kicked from a room.
///////////////////////////////////////////
typedef void (* peerKickedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the player was kicked from.
	const char * nick,  // The nick of the player that did the kicking.
	const char * reason,  // An optional reason for the kick.
	void * param  // User-data.
);

// The entire player list for this room has been updated.
/////////////////////////////////////////////////////////
typedef void (* peerNewPlayerListCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room.
	void * param  // User-data
);

// A player in one of the rooms changed his nick.
/////////////////////////////////////////////////
typedef void (* peerPlayerChangedNickCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of the room the nick changed was in.
	const char * oldNick,  // The player's old nick.
	const char * newNick,  // The player's new nick.
	void * param  // User-data.
);

// The IP and ProfileID for this player has just been received.
// PANTS|01.08.01
// This gets called for all players (who are using peer) in a room
// shortly after joining.  It will be called with nick==NULL after
// getting info for all the players.
//////////////////////////////////////////////////////////////////
typedef void (* peerPlayerInfoCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room the info was gotten in.
	const char * nick,  // The nick of the player the info is for.
	unsigned int IP,  // The player's IP.
	int profileID,  // The player's profile ID.
	void * param  // User-data.
);

// This gets called when a player's flags have changed.
///////////////////////////////////////////////////////
typedef void (* peerPlayerFlagsChangedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room the flags were changed in.
	const char * nick,  // The player whose flags have changed.
	int oldFlags,  // The player's old flags.
	int newFlags,  // The player's new flags.
	void * param  // User-data
);

// An updated ping for a player, who may be in any room(s).
///////////////////////////////////////////////////////////
typedef void (* peerPingCallback)
(
	PEER peer,  // The peer object.
	const char * nick,  // The other player's nick.
	int ping,  // The ping.
	void * param  // User-data.
);

// An updated cross-ping between two players in the staging room.
/////////////////////////////////////////////////////////////////
typedef void (* peerCrossPingCallback)
(
	PEER peer,  // The peer object.
	const char * nick1,  // The first player's nick.
	const char * nick2,  // The second player's nick.
	int crossPing,  // The cross-ping.
	void * param  // User-data.
);

// This is called for watch keys when a room is joined, for
// watch keys when another player joins, and for any newly 
// set watch keys.
///////////////////////////////////////////////////////////
typedef void (* peerGlobalKeyChangedCallback)
(
	PEER peer,  // The peer object.
	const char * nick,  // The player whose key changed.
	const char * key,  // The key.
	const char * value,  // The value.
	void * param  // User-data.
);

// This is called for watch keys when a room is joined, for
// watch keys when another player joins, for any newly 
// set watch keys, and when a broadcast watch key is changed.
/////////////////////////////////////////////////////////////
typedef void (* peerRoomKeyChangedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room the player is in.
	const char * nick,  // The player whose key changed.
	const char * key,  // The key.
	const char * value,  // The value.
	void * param  // User-data.
);

// Type used for the GOA callbacks (basic, info, rules, players).
/////////////////////////////////////////////////////////////////
typedef void (* peerGOACallback)
(
	PEER peer,  // The peer object.
	PEERBool playing,  // PEERTrue if the game is being played.
	char * outbuf,  // Output buffer.
	int maxlen,  // Max data that can be written to outbuf
	void * param // User-data
);

// This struct gets passed into peerInitialize().
// param will be passed as the last parameter to each of the callbacks.
///////////////////////////////////////////////////////////////////////
typedef struct PEERCallbacks
{
	peerDisconnectedCallback disconnected;
	peerRoomMessageCallback roomMessage;
	peerRoomUTMCallback roomUTM;
	peerRoomNameChangedCallback roomNameChanged;  // PANTS|09.11.00
	peerRoomModeChangedCallback roomModeChanged;  // PANTS|04.17.01
	peerPlayerMessageCallback playerMessage;
	peerPlayerUTMCallback playerUTM;
	peerReadyChangedCallback readyChanged;
	peerGameStartedCallback gameStarted;
	peerPlayerJoinedCallback playerJoined;
	peerPlayerLeftCallback playerLeft;
	peerKickedCallback kicked;
	peerNewPlayerListCallback newPlayerList;
	peerPlayerChangedNickCallback playerChangedNick;
	peerPlayerInfoCallback playerInfo;  // PANTS|01.08.01
	peerPlayerFlagsChangedCallback playerFlagsChanged;  // PANTS|03.12.01
	peerPingCallback ping;
	peerCrossPingCallback crossPing;
	peerGlobalKeyChangedCallback globalKeyChanged;
	peerRoomKeyChangedCallback roomKeyChanged;
	peerGOACallback GOABasic;
		// gamename (Peer)
		// gamever (App)
		// location (App)
	peerGOACallback GOAInfo;
		// gamemode (Peer while staging, App while playing)
		//   the app only needs to set this if it's not openplaying
		// hostname (Peer while staging, App while playing)
		// numplayers (Peer while staging, App while playing)
		// maxplayers (Peer while staging, App while playing)
		// password (Peer while staging, App while playing)  // PANTS|09.11.00
		// hostport (App, except when using socket sharing)
		// mapname (App)
		// gametype (App)
	peerGOACallback GOARules;
		// timelimit (App)
		// fraglimit (App)
		// teamplay (App)
	peerGOACallback GOAPlayers;
		// player_N (Peer while staging, App while playing)
		// ping_N (Peer while staging, App while playing)
	void * param;
} PEERCallbacks;

/************
** GENERAL **
************/
// This creates and intializes a peer object.
// NULL is returned in case of an error, otherwise a peer
// object is returned.
// If a peer object is returned, peerShutdown() must be called
// to cleanup the object
///////////////////////////////////////////////////////////////
PEER peerInitialize
(
	PEERCallbacks * callbacks  // Global callbacks.
);

// This gets called when the connection attempt finishes.
/////////////////////////////////////////////////////////
typedef void (* peerConnectCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	void * param  // User-data.
);

// This gets called if there is an error with
//   the nickname while connecting.
// Call peerRetryWithNick() to try another nick.  If it
//   is called with a NULL nick, then the connect will be
//   stopped, and peerConnectCallback will be called with
//   failure.
/////////////////////////////////////////////////////////
typedef void (* peerNickErrorCallback)
(
	PEER peer,  // The peer object.
	int type,  // The type of nick error
		// PEER_IN_USE:  The nick is already being used by someone else.
		// PEER_INVALID: The nick contains invalid characters.
	const char * nick,  // The bad nick.
	void * param  // User-data.
);

// This connects a peer object to a chat server.
// Call peerDisconnect() to close the connection.
/////////////////////////////////////////////////
void peerConnect
(
	PEER peer,  // The peer object.
	const char * nick,  // The nick to connect with.
	int profileID,  // The profileID, or 0 if no profileID.
	peerNickErrorCallback nickErrorCallback,  // Called if nick error.
	peerConnectCallback connectCallback,  // Called on complete.
	void * param,  // User-data.
	PEERBool blocking  //  If PEERTrue, called synchronously.
);

// If peerNickErrorCallback is called, call this to
// try and continue the connection with a new nickname.
// If there is an error with this nick, the
// peerNickErrCallback will be called again.
///////////////////////////////////////////////////////
void peerRetryWithNick
(
	PEER peer,
	const char * nick
);

// Returns true if peer is connected.
// PANTS|09.11.00
/////////////////////////////////////
PEERBool peerIsConnected
(
	PEER peer
);

// Sets the current title.
// Must be connected before setting the title.
// Returns PEERFalse if an error, or PEERTrue if success.
/////////////////////////////////////////////////////////
PEERBool peerSetTitle
(
	PEER peer,  // The peer object.
	const char * title,  // The title to make current (ie., ut, gmtest).
	const char * qrSecretKey,  // The query&reporting secret key.
	const char * engineName,  // The engine name.
	const char * engineSecretKey,  // The engine secret key.
	int engineMaxUpdates,  // The maximum number of concurent updates
	                       // (10-15 for modem users, 20-30 for high-bandwidth).
	PEERBool pingRooms[NumRooms],  // To do pings int a room, set it to PEERTrue.
	PEERBool crossPingRooms[NumRooms]  // To do cross-pings in a room, set it to PEERTrue.
);

// Resets peer to no title.
///////////////////////////
void peerClearTitle
(
	PEER peer  // The peer object.
);

// Gets the currently set title.
// Returns NULL if no title is set.
///////////////////////////////////
const char * peerGetTitle
(
	PEER peer  // The peer object.
);

// Disconnect peer from the chat server.
////////////////////////////////////////
void peerDisconnect
(
	PEER peer  // The peer object.
);

// Shutdown peer.
// The peer object should not be used again after this call.
////////////////////////////////////////////////////////////
void peerShutdown
(
	PEER peer  // The peer object.
);

// Let's peer think.
// This should be called at least every ~10ms,
// typically, within the program's main loop.
//////////////////////////////////////////////
void peerThink
(
	PEER peer  // The peer object.
);

// Get the chat object associated with this peer object.
// This returns NULL if peer isn't connected.
////////////////////////////////////////////////////////
CHAT peerGetChat
(
	PEER peer  // The peer object.
);

// Get the local user's nickname.
/////////////////////////////////
const char * peerGetNick
(
	PEER peer  // The peer object.
);

// Gets the local IP address.  If called before
// the peer object is connected, will return 0.
///////////////////////////////////////////////
unsigned int peerGetLocalIP
(
	PEER peer  // The peer object.
);

// This gets called when an attempt to change nicks is finished.
////////////////////////////////////////////////////////////////
typedef void (* peerChangeNickCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	const char * oldNick,  // The old nickname.
	const char * newNick,  // The new nickname.
	void * param  // User-data.
);

// Changes the user's nickname.
///////////////////////////////
void peerChangeNick
(
	PEER peer,  // The peer object.
	const char * newNick,  // The nickname to which to change.
	peerChangeNickCallback callback,  // Called when finished.
	void * param,  // Passed to the callback.
	PEERBool blocking  // If PEERTrue, don't return until finished.
);

// Causes Peer to not automatically leave the
// room the next time peerSetTitle or peerClearTitle
// is called.  No effect if a title isn't set.  When
// the next title is set, the flag is cleared.
// Only TitleRoom is currently supported.
// This function is normally not needed.
////////////////////////////////////////////////////
void peerStayInRoom
(
	PEER peer,  // The peer object.
	RoomType roomType  // Only TitleRoom is currently supproted.
);

// Turns quiet mode on/off.
///////////////////////////
void peerSetQuietMode
(
	PEER peer,  // The peer object.
	PEERBool quiet  // If PEERTrue, enable quiet mode.
);

// Sets the away mode.
// If an empty string or NULL, away mode is off.
// If a valid string, away mode is on.
////////////////////////////////////////////////
void peerSetAwayMode
(
	PEER peer,  // The peer object.
	const char * reason  // The away reason.  If NULL or "", not away.
);

// When using peerStartReportingWithSocket or peerCreateStagingRoomWithSocket,
// any qureries received on the sockets need to be passed to the SDK.  Pass
// the data using this function.
//////////////////////////////////////////////////////////////////////////////
void peerParseQuery
(
	PEER peer,  // The peer object.
	char * query,  // String of query data.
	int len,  // The length of the string, not including the NUL.
	struct sockaddr * sender  // The address the query was received from.
);

/**********
** ROOMS **
**********/
// This gets called when an attempt to join or create a room has finished.
//////////////////////////////////////////////////////////////////////////
typedef void (* peerJoinRoomCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	PEERJoinResult result,  // The result of the attempt.
	RoomType roomType,  // The type of room joined/created.
	void * param  // User-data.
);

// Joins the currently selected title's title room.
///////////////////////////////////////////////////
void peerJoinTitleRoom
(
	PEER peer,  // The peer object.
	peerJoinRoomCallback callback,  // Called when finished.
	void * param,  // Passed to the callback.
	PEERBool blocking  // If PEERTrue, don't return until finished.
);

// Joins a group room.
// The groupID comes from the peerListGroupRoomsCallback.
/////////////////////////////////////////////////////////
void peerJoinGroupRoom
(
	PEER peer,  // The peer object.
	int groupID,  // The ID for the group to join.
	peerJoinRoomCallback callback,  // Called when finished.
	void * param,  // Passed to the callback.
	PEERBool blocking // If PEERTrue, don't return until finished.
);

// Joins a staging room.
// server is one of the server objects passed to peerListingGamesCallback().
// This call will only work if staging==PEERTrue for the server.
// PANTS|09.11.00 - The password is only needed for passworded rooms.
// PANTS|03.15.01 - No longer requires you to be actively listing games.
////////////////////////////////////////////////////////////////////////////
void peerJoinStagingRoom
(
	PEER peer,  // The peer object.
	GServer server,  // The server passed into peerlistingGamesCallback().
	const char password[PEER_PASSWORD_LEN],  // The password of the room being joined.  Can be NULL or "".
	peerJoinRoomCallback callback,  // Called when finished.
	void * param,  // Passed to the callback.
	PEERBool blocking   // If PEERTrue, don't return until finished.
);

// Joins a staging room.
// Similar to peerJoinStagingRoom, but joins based
// on the host's IP instead of the GServer object.
///////////////////////////////////////////////////
void peerJoinStagingRoomByIP
(
	PEER peer,  // The peer object.
	unsigned int IP,  // The IP of the staging room host.
	const char password[PEER_PASSWORD_LEN],  // The password of the room being joined.  Can be NULL or "".
	peerJoinRoomCallback callback,  // Called when finished.
	void * param,  // Passed to the callback.
	PEERBool blocking   // If PEERTrue, don't return until finished.
);

// Creates a new staging room, with the local player hosting.
// PANTS|09.11.00 - If the password parameter is not NULL
// or "", this will create a passworded room.  The same
// case-sensitive password needs to be passed into
// peerJoinStagingRoom() for other player's to join the room.
// PANTS|09.11.00 - The staging room will be reported as part
// of whatever group room the local player was in when the
// room was created.  Leaving the group room will not affect
// what group the staging room is reported as part of.
/////////////////////////////////////////////////////////////
void peerCreateStagingRoom
(
	PEER peer,  // The peer object.
	const char * name,  // The name of the room.
	int maxPlayers,  // The max number of players allowed in the room.
	const char password[PEER_PASSWORD_LEN],  // An optional password for the staging room
	peerJoinRoomCallback callback,  // Called when finished.
	void * param,  // Passed to the callback.
	PEERBool blocking // If PEERTrue, don't return until finished.
);

// Same as peerCreateStagingRoom, but uses the provided socket for
// sending heartbeats and query replies.  This allows the game
// to share a socket with the peer SDK, , which can make hosting
// games behind a NAT proxy possible.
//////////////////////////////////////////////////////////////////
void peerCreateStagingRoomWithSocket
(
	PEER peer,  // The peer object.
	const char * name,  // The name of the room.
	int maxPlayers,  // The max number of players allowed in the room.
	const char password[PEER_PASSWORD_LEN],  // An optional password for the staging room
	SOCKET socket,  // The socket to be used for reporting.
	peerJoinRoomCallback callback,  // Called when finished.
	void * param,  // Passed to the callback.
	PEERBool blocking // If PEERTrue, don't return until finished.
);

// Leave a room.
// PANTS|09.11.00 - You can now leave a group room
// without being forcibly removed from a staging room.
//////////////////////////////////////////////////////
void peerLeaveRoom
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room you want to leave (TitleRoom, GroupRoom, or StagingRoom).
	const char * reason  // The reason the player is leaving (can be NULL).  PANTS|03.13.01
);

// Gets called once for each group room when listing group rooms.
// After this has been called for each group room, it will be
// called one more time with groupID==0 and name==NULL.
/////////////////////////////////////////////////////////////////
typedef void (* peerListGroupRoomsCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	int groupID,  // A unique ID for this group.
	GServer server,  // The server object for this group room.
	const char * name,  // The group room's name.
	int numWaiting,  // The number of players in the room.
	int maxWaiting,  // The maximum number of players allowed in the room.
	int numGames,  // The number of games either staging or running in the group.
	int numPlaying,  // The total number of players in games in the group.
	void * param  // User-data.
);

// List all the groups rooms for the currently set title.
/////////////////////////////////////////////////////////
void peerListGroupRooms
(
	PEER peer,  // The peer object.
	peerListGroupRoomsCallback callback,  // Called for each group room.
	void * param,  // Passed to the callback.
	PEERBool blocking  // If PEERTrue, don't return until finished.
);

// Called with info on games being listed.
// Used to maintain a list of running games and staging rooms.
// The server object is a unique way of identifying each game.
// It can also be used with the calls in the "ServerFunctions" section
//   of goaceng.h to find out more info about the server.
// If staging==PEERTrue, the game hasn't started yet, it's still in the staging room
//   use peerJoinStagingRoom() to join the staging room, or if staging==peerfalse
//   use the server object to get the game's IP and port to join with.
// During the _intial_ listing of games, progress is the percentage (0-100) of the
//   games that have been added.  Once the initial listing is completed,
//   progress will always be 100.
// PANTS|09.11.00 - The "password" key will be set to 1 for games that are
// passworded.  This can be checked with ServerGetIntValue(server, "password", 0).
/////////////////////////////////////////////////////////////////////////////////////
typedef void (* peerListingGamesCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	const char * name,  // The name of the game being listed.
	GServer server,  // The server object for this game.
	PEERBool staging,  // If PEERTrue, this is a staging room and not a running game.
	int msg,  // The type of message this is.
		// PEER_CLEAR:
		//   Clear the list.  This has the same effect as if this was called
		//   with PEER_REMOVE for every server listed.
		// PEER_ADD:
		//   This is a new server. Add it to the list.
		// PEER_UPDATE:
		//   This server is already on the list, and its been updated.
		// PEER_REMOVE:
		//   Remove this server from the list.  The server object for this server
		//   should not be used again after this callback returns.
	int progress,  // The percent of servers that have been added.
	void * param  // User-data.
);

// Start listing the currently running games and staging rooms.
// This is used to maintain a list that can presented to the user,
//   so they can pick a game (or staging room) to join.
// Games and staging rooms are filtered based on what group the local
//   user is in.  If the local user isn't in a group, then only games
//   and staging rooms that aren't part of any group are listed.
/////////////////////////////////////////////////////////////////////
void peerStartListingGames
(
	PEER peer,  // The peer object.
	const char * filter,  // A SQL-like rule filter.
	peerListingGamesCallback callback,  // Called when finished.
	void * param  // Passed to the callback.
);

// Stop games from being listed. This does NOT clear the games list.
// So all games listed are still considered valid.  They stay valid
// until either another call to peerStartListingGames or until the
// title is cleared (or a new one set).
////////////////////////////////////////////////////////////////////
void peerStopListingGames
(
	PEER peer  // The peer object.
);

// Send a message to a room.
////////////////////////////
void peerMessageRoom
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room to send the message to.
	const char * message,  // The message.
	MessageType messageType  // The type of message.
);

// Send a UTM to a room.
////////////////////////
void peerUTMRoom
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room to send the UTM to.
	const char * command,  // The command.
	const char * parameters,  // The UTM's parameters.
	PEERBool authenticate  // If true, the server will authenticate this UTM (should normally be false).
);

// Set a password in a room you're hosting.
// The only roomType currently supported is StagingRoom.
// This will only work if the player is hosting the room.
// If password is NULL or "", the password will be cleared.
///////////////////////////////////////////////////////////
void peerSetPassword
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room in which to set the password.
	const char password[PEER_PASSWORD_LEN]  // The password to set.
);

// Set the name of a room you're hosting.
// The only roomType currently supported is StagingRoom.
// PANTS|09.11.00
////////////////////////////////////////////////////////
void peerSetRoomName
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room in which to set the name.
	const char * name  // The new name
);

// Get a room's name (the channel's title).
// Returns NULL if not in the room.
///////////////////////////////////////////
const char * peerGetRoomName
(
	PEER peer,  // The peer object.
	RoomType roomType  // The room to get the name for.
);

// Get's the chat channel associated with the room.
// Returns NULL if not in the room.
///////////////////////////////////////////////////
const char * peerGetRoomChannel
(
	PEER peer,  // The peer object.
	RoomType roomType  // The room to get the channel for.
);

// Returns PEERTrue if in the room.
///////////////////////////////////
PEERBool peerInRoom
(
	PEER peer,  // The peer object.
	RoomType roomType  // The room to check for.
);

// Use this channel for the title room for the currently set title.
// This function is normally not needed.
///////////////////////////////////////////////////////////////////
void peerSetTitleRoomChannel
(
	PEER peer,  // The peer object.
	const char * channel  // The channel to use for the title room.
);

// Use this channel for the updates room for the currently set title.
// This function is normally not needed.
/////////////////////////////////////////////////////////////////////
void peerSetUpdatesRoomChannel
(
	PEER peer,  // The peer object.
	const char * channel  // The channel to use for the updates room.
);

/************
** PLAYERS **
************/
// Called for each player in a room being enumerated, and once
//   when finished, with index==-1 and nick==NULL.
//////////////////////////////////////////////////////////////
typedef void (* peerEnumPlayersCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	RoomType roomType,  // The room whose players are being enumerated.
	int index,  // The index of the player (0 to (N - 1)).  -1 when finished.
	const char * nick,  // The nick of the player.
	int flags,  // This player's flags (see #define's above).  PANTS|03.12.01
	void * param  // User-data.
);

// Enumerates through the players in a room.
////////////////////////////////////////////
void peerEnumPlayers
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room to enum the players in.
	peerEnumPlayersCallback callback,  // Called when finished.
	void * param  // Passed to callback.
);

// Send a message to a player.
//////////////////////////////
void peerMessagePlayer
(
	PEER peer,  // The peer object.
	const char * nick,  // The nick of the player to send the message to.
	const char * message,  // The message to send.
	MessageType messageType  // The type of message.
);

// Send a UTM to a player.
//////////////////////////
void peerUTMPlayer
(
	PEER peer,  // The peer object.
	const char * nick,  // The nick of the player to send the UTM to.
	const char * command,  // The command.
	const char * parameters,  // The UTM's parameters.
	PEERBool authenticate  // If true, the server will authenticate this UTM (should normally be false).
);

// Gets a player's ping (between the local machine and the player's machine).
// Returns PEERFalse if we don't have or can't get the player's ping.
/////////////////////////////////////////////////////////////////////////////
PEERBool peerGetPlayerPing
(
	PEER peer,  // The peer object.
	const char * nick,  // The player to get the ping for.
	int * ping  // The player's ping is stored here, if we have it.
);

// Gets the cross-ping between 2 players.
// Returns PEERFalse if we don't have or can't get the player's cross-ping.
///////////////////////////////////////////////////////////////////////////
PEERBool peerGetPlayersCrossPing
(
	PEER peer,  // The peer object.
	const char * nick1,  // The first player.
	const char * nick2,  // The second player.
	int * crossPing  // The cross-ping is stored here, if we have it.
);

// Gets a player's info immediately.
// Returns PEERFalse if the info is no available.
/////////////////////////////////////////////////
PEERBool peerGetPlayerInfoNoWait
(
	PEER peer,
	const char * nick,
	unsigned int * IP,
	int * profileID
);

// Called as a result of a call to peerGetPlayerProfileID().
////////////////////////////////////////////////////////////
typedef void (* peerGetPlayerProfileIDCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	const char * nick,  // The player's nick.
	int profileID,  // The player's profile ID.
	void * param  // User-data.
);

// Called to get a player's profile ID.
///////////////////////////////////////
void peerGetPlayerProfileID
(
	PEER peer,  // The peer object.
	const char * nick,  // The player's nick.
	peerGetPlayerProfileIDCallback callback,  // Called when finished.
	void * param,  // Passed to callback.
	PEERBool blocking  // If PEERTrue, don't return until finished.
);

// Called as a result of a call to peerGetPlayerIP().
/////////////////////////////////////////////////////
typedef void (* peerGetPlayerIPCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	const char * nick,  // The player's nick.
	unsigned int IP,  // The player's IP, in network byte order.  PANTS|09.11.00 - was unsigned long
	void * param  // User-data.
);

// Called to get a player's IP.
///////////////////////////////
void peerGetPlayerIP
(
	PEER peer,  // The peer object.
	const char * nick,  // The player's nick.
	peerGetPlayerIPCallback callback,  // Called when finished.
	void * param,  // Passed to callback.
	PEERBool blocking  // If PEERTrue, don't return until finished.
);

// Checks if a player is a host (has ops).
// Returns PEERTrue if yes, PEERFalse if no.
////////////////////////////////////////////
PEERBool peerIsPlayerHost
(
	PEER peer,  // The peer object.
	const char * nick,  // The player's nick.
	RoomType roomType  // The room to check in.
);

// Gets a player's flags in a room.  Returns PEERFalse if
// the local player or this player is not in the room.
/////////////////////////////////////////////////////////
PEERBool peerGetPlayerFlags
(
	PEER peer,
	const char * nick,
	RoomType roomType,
	int * flags
);

/*********
** GAME **
*********/
// Sets the local player's ready state.
// PEERTrue if ready, PEERFalse if not ready.
/////////////////////////////////////////////
void peerSetReady
(
	PEER peer,  // The peer object.
	PEERBool ready  // Ready or not.
);

// Gets a player's ready state.
///////////////////////////////
PEERBool peerGetReady
(
	PEER peer,  // The peer object.
	const char * nick, // The player's nick.
	PEERBool * ready  // The player's ready state gets stored in here.
);

// Checks if all the player's in the staging room are ready.
////////////////////////////////////////////////////////////
PEERBool peerAreAllReady
(
	PEER peer  // The peer object.
);

// Called only by a staging room host to start the game.
// All the other people in the staging room will have their
//   peerGameStartedCallback() called.
// The message gets passed to everyone in the peerGameStartedCallback(), and
//   can be used to pass information such as a special port or password.
// If (reportingOptions & PEER_STOP_REPORTING), Peer will stop GOA reporting,
//   so the program is responsible for any server reporting.
// If !(reportingOptions & PEER_STOP_REPORTING), Peer will continue doing GOA
//   server reporting, and calling the program-supplied callbacks.  If
//   (reportingOptions & PEER_REPORT_INFO), all info will be reported in the
//   GOAInfo callback.  If (reportingOptions & PEER_REPORT_PLAYERS), all info
//   will be reported in the GOAPlayers callback.
/////////////////////////////////////////////////////////////////////////////
void peerStartGame
(
	PEER peer,  // The peer object.
	const char * message,  // A message to send to everyone.
	int reportingOptions  // Bitfield flags used to set reporting options.
);

// Starts GOA server reporting, without creating a staging room.
// Call peerStopGame() to stop reporting.
////////////////////////////////////////////////////////////////
PEERBool peerStartReporting
(
	PEER peer  // The peer object.
);

// Same as peerStartReporting, but uses the provided socket for
// sending heartbeats and query replies.  This allows the game
// to share a socket with the peer SDK, , which can make hosting
// games behind a NAT proxy possible.
////////////////////////////////////////////////////////////////
PEERBool peerStartReportingWithSocket
(
	PEER peer,  // The peer object.
	SOCKET socket  // The socket to be used for reporting.
);

// Mark the local player as playing.
// Use this if the player is in a game not
// started by peer, but he should be marked as playing.
///////////////////////////////////////////////////////
void peerStartPlaying
(
	PEER peer  // The peer object.
);

// Check to see if the local player is playing.
///////////////////////////////////////////////
PEERBool peerIsPlaying
(
	PEER peer  // The peer object.
);

// Needs to be called by the host when the game has stopped.
////////////////////////////////////////////////////////////
void peerStopGame
(
	PEER peer  // The peer object.
);

// Call this when hosting a staging room or a game to force peer
// to report the game again.  This will cause the peerGOACallback's
// to be called again.  An example of when to call this is when
// a player joins or leaves a game.
// PANTS|09.11.00
///////////////////////////////////////////////////////////////////
void peerStateChanged
(
	PEER peer  // The peer object.
);

/*********
** KEYS **
*********/
// Set global keys on the local player.
///////////////////////////////////////
void peerSetGlobalKeys
(
	PEER peer,  // The peer object.
	int num,  // The number of keys to set.
	const char ** keys,  // The keys to set.
	const char ** values  // The values for the keys.
);

// Called with a player's global keys.
//////////////////////////////////////
typedef void (* peerGetGlobalKeysCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // If PEERFalse, unable to get the keys.
	const char * nick,  // The player the keys are for.
	int num,  // The number of keys.
	const char ** keys,  // The keys got.
	const char ** values,  // The values for the keys.
	void * param  // User-data.
);

// Get a player's global keys.
//////////////////////////////
void peerGetPlayerGlobalKeys
(
	PEER peer,  // The peer object.
	const char * nick,  // The player to get the keys for.
	int num,  // The number of keys.
	const char ** keys,  // The keys to get.
	peerGetGlobalKeysCallback callback,  // Called with the keys.
	void * param,  // Passed to callback.
	PEERBool blocking  // If PEERTrue, don't return until finished.
);

// Get the global keys for all players in a room we're in.
//////////////////////////////////////////////////////////
void peerGetRoomGlobalKeys
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room to get the keys in.
	int num,  // The number of keys.
	const char ** keys,  // The keys to get.
	peerGetGlobalKeysCallback callback,  // Called with the keys.
	void * param,  // Passed to callback.
	PEERBool blocking  // If PEERTrue, don't return until finished.
);

// Set the room keys for a player.
// Use NULL or "" to set keys on the room itself.
/////////////////////////////////////////////////
void peerSetRoomKeys
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room to set the keys in.
	const char * nick,  // The player to set the keys on (NULL or "" for the room).
	int num,  // The number of keys.
	const char ** keys,  // The keys to set.
	const char ** values  // The values to set.
);

// Called with a player's room keys.
////////////////////////////////////
typedef void (* peerGetRoomKeysCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // If PEERFalse, unable to get the keys.
	RoomType roomType,  // The room the keys are in.
	const char * nick,  // The player the keys are for, or NULL for the room.
	int num,  // The number of keys.
	char ** keys,  // The keys.
	char ** values,  // The values for the keys.
	void * param  // User-data.
);

// Get the room keys for either a single player of an entire room.
// Use "*" for the player to get the keys for the entire room.
// Use NULL or "" for the player to get keys on the room itself.
//////////////////////////////////////////////////////////////////
void peerGetRoomKeys
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room to get the keys in.
	const char * nick,  // The player to get the keys for.
	int num,  // The number of keys.
	const char ** keys,  // The keys to get.
	peerGetRoomKeysCallback callback,  // Called with the keys.
	void * param,  // Passed to callback.
	PEERBool blocking  // If PEERTrue, don't return until finished.
);

// Set the global watch keys for a room type.
// If addKeys is set to PEERTrue, the keys will be
// added to the current global watch keys for this room.
// If addKeys is PEERFalse, these will replace any existing
// global watch keys for this room.
// When entering a room of the given type, peer will get and
// cache these keys for all players in the room.
////////////////////////////////////////////////////////////
void peerSetGlobalWatchKeys
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room to set the watch keys for.
	int num,  // The number of keys.
	const char ** keys,  // The keys to watch for.
	PEERBool addKeys  // If PEERTrue, add these keys to the existing global watch keys for this room.
);

// Set the room watch keys for a room type.
// If addKeys is set to PEERTrue, the keys will be
// added to the current room watch keys for this room.
// If addKeys is PEERFalse, these will replace any existing
// room watch keys for this room.
// When entering a room of the given type, peer will get and
// cache these keys for all players in the room.
////////////////////////////////////////////////////////////
void peerSetRoomWatchKeys
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room to set the watch keys for.
	int num,  // The number of keys.
	const char ** keys,  // The keys to watch for.
	PEERBool addKeys  // If PEERTrue, add these keys to the existing room watch keys for this room.
);

// Get the global watch key for a particular player.
// If the key isn't cached locally (either because it isn't
// a watch key or just isn't yet known), NULL will be returned.
// If the key is empty, "" will be returned.
///////////////////////////////////////////////////////////////
const char * peerGetGlobalWatchKey
(
	PEER peer,  // The peer object.
	const char * nick,  // The player to get the key for.
	const char * key  // The key to get.
);

// Get the room watch key for a particular player in a room.
// If the key isn't cached locally (either because it isn't
// a watch key or just isn't yet known), NULL will be returned.
// If the key is empty, "" will be returned.
///////////////////////////////////////////////////////////////
const char * peerGetRoomWatchKey
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room to get the key in.
	const char * nick,  // The player to get the key for.
	const char * key  // The key to get.
);

#ifdef __cplusplus
}
#endif

#endif
