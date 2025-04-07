#ifndef __MULTIPLAYER_MESSAGES_H__
#define __MULTIPLAYER_MESSAGES_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EMultiplayerMessages
{
	// servers list messages
	EM_NEW_SERVER_ADDED = 0,
	SERVER_INFO_REFRESHED = 1,
	SERVER_REMOVED = 2,

	// game creation messages
	CONNECTION_FAILED			= 100,
	PLAYER_INFO_REFRESHED = 101,
	PLAYER_DELETED				= 102,
	GAME_INFO_RECEIVED		= 103,
	OUR_SIDE_CHANGED			= 104,
	
	//
	GAME_STARTED						= 200,
	WRONG_RESOURCES					= 201,
	WRONG_MAP								= 202,
	NO_MAP									= 203,
	WRONG_PASSWORD					= 204,
	GAME_IS_ALREADY_STARTED	= 205,
	CAN_START_GAME					= 206,
	GAME_INFO_CHANGED				= 207,
	CREATE_STAGING_ROOM			= 208,
	AIM_KICKED							= 209,
	
	//
	E_CHAT_MESSAGE				 = 300,
	SIMPLE_CHAT_MESSAGE		 = 301,
	CHAT_USER_CHANGED			 = 302,
	CHAT_USER_CHANGED_NICK = 303,
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IMultiplayerMessage : public IRefCount
{
	virtual const EMultiplayerMessages GetMessageID() const = 0;
	virtual void SendToUI() = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __MULTIPLAYER_MESSAGES_H__
