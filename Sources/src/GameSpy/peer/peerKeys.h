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

#ifndef _PEERKEYS_H_
#define _PEERKEYS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*************
** INCLUDES **
*************/
#include "peerMain.h"
#include "peerPlayers.h"

/**************
** FUNCTIONS **
**************/
PEERBool piKeysInit
(
	PEER peer
);

void piKeysCleanup
(
	PEER peer
);

const char * piGetGlobalWatchKey
(
	PEER peer,
	const char * nick,
	const char * key
);

const char * piGetRoomWatchKey
(
	PEER peer,
	RoomType roomType,
	const char * nick,
	const char * key
);

void piSetGlobalWatchKeys
(
	PEER peer,
	RoomType roomType,
	int num,
	const char ** keys,
	PEERBool addKeys
);

void piSetRoomWatchKeys
(
	PEER peer,
	RoomType roomType,
	int num,
	const char ** keys,
	PEERBool addKeys
);

void piGlobalKeyChanged
(
	PEER peer,
	const char * nick,
	const char * key,
	const char * value
);

void piRoomKeyChanged
(
	PEER peer,
	RoomType roomType,
	const char * nick,
	const char * key,
	const char * value
);

void piKeyCachePlayerChangedNick
(
	PEER peer,
	const char * oldNick,
	const char * newNick
);

void piKeyCachePlayerLeftRoom
(
	PEER peer,
	RoomType roomType,
	piPlayer * player
);

void piKeyCacheLeftRoom
(
	PEER peer,
	RoomType roomType
);

void piKeyCacheRefreshPlayer
(
	PEER peer,
	RoomType roomType,
	const char * nick
);

void piKeyCacheRefreshRoom
(
	PEER peer,
	RoomType roomType
);

void piKeyCacheCleanse
(
	PEER peer
);

#if 0
typedef void (* piKeyCacheMapCallback)
(
	PEER peer,
	const char * player,
	const char * key,
	const char * value,
	RoomType roomType,
	void * param
);

void piKeyCacheMap
(
	PEER peer,
	piKeyCacheMapCallback callback,
	void * param
);
#endif

#ifdef __cplusplus
}
#endif

#endif
