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

#ifndef _PEEROPERATIONS_H_
#define _PEEROPERATIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*************
** INCLUDES **
*************/
#include "peerMain.h"

/**********
** TYPES **
**********/
typedef enum piOperationType
{
	PI_CONNECT_OPERATION,
	PI_CREATE_ROOM_OPERATION,
	PI_JOIN_ROOM_OPERATION,
	PI_ENUM_PLAYERS_OPERATION,
	PI_LIST_GROUP_ROOMS_OPERATION,
	PI_LIST_STAGING_ROOMS_OPERATION,
	PI_GET_PROFILE_ID_OPERATION,
	PI_GET_IP_OPERATION,
	PI_CHANGE_NICK_OPERATION,
	PI_GET_GLOBAL_KEYS_OPERATION,
	PI_GET_ROOM_KEYS_OPERATION,
	PI_NUM_OPERATION_TYPES
} piOperationType;

typedef struct piOperation
{
	PEER peer;             // the peer object
	piOperationType type;  // PI_<type>_OPERATION
	void * data;           // operation-specific data
	int ID;                // unique ID for this operation
	void * callback;       // the callback for this operation
	void * callbackParam;  // user-data for the callback
	RoomType roomType;     // lots of operations need this
	char * name;           // general purpose name
	int num;               // general purpose integer
	SOCKET socket;         // general purpose socket
	PEERBool cancel;       // this op has been cancelled
} piOperation;

/**************
** FUNCTIONS **
**************/
PEERBool piOperationsInit
(
	PEER peer
);

void piOperationsCleanup
(
	PEER peer
);

PEERBool piIsOperationFinished
(
	PEER peer,
	int opID
);

void piRemoveOperation
(
	PEER peer,
	piOperation * operation
);

PEERBool piNewConnectOperation
(
	PEER peer,
	const char * nick,
	peerConnectCallback callback,
	void * callbackParam,
	int opID
);

PEERBool piNewCreateStagingRoomOperation
(
	PEER peer,
	const char * name,
	SOCKET socket,
	peerJoinRoomCallback callback,
	void * callbackParam,
	int opID
);

PEERBool piNewJoinRoomOperation
(
	PEER peer,
	RoomType roomType,
	const char * ID,
	peerJoinRoomCallback callback,
	void * callbackParam,
	int opID
);

void piEnumStagingRoomsCEngineCallback
(
	GServerList gameList,
	int msg,
	PEER peer,
	void * param1,
	void * param2
);

PEERBool piNewListGroupRoomsOperation
(
	PEER peer,
	peerListGroupRoomsCallback callback,
	void * param,
	int opID
);

PEERBool piNewListingGamesOperation
(
	PEER peer,
	const char * filter,
	peerListingGamesCallback callback,
	void * param
);

PEERBool piNewGetProfileIDOperation
(
	PEER peer,
	const char * nick,
	peerGetPlayerProfileIDCallback callback,
	void * param,
	int opID
);

PEERBool piNewGetIPOperation
(
	PEER peer,
	const char * nick,
	peerGetPlayerIPCallback callback,
	void * param,
	int opID
);

PEERBool piNewChangeNickOperation
(
	PEER peer,
	const char * newNick,
	peerChangeNickCallback callback,
	void * param,
	int opID
);

PEERBool piNewGetGlobalKeysOperation
(
	PEER peer,
	const char * target,
	int num,
	const char ** keys,
	peerGetGlobalKeysCallback callback,
	void * param,
	int opID
);

PEERBool piNewGetRoomKeysOperation
(
	PEER peer,
	RoomType roomType,
	const char * nick,
	int num,
	const char ** keys,
	peerGetRoomKeysCallback callback,
	void * param,
	int opID
);

#ifdef __cplusplus
}
#endif

#endif
