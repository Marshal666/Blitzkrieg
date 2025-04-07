#ifndef __NET_MESSAGES_H__
#define __NET_MESSAGES_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum ENetGameMessages
{
	// game creation phase
	NGM_LOGIC_ID,
	NGM_BROADCAST_PLAYER_INFO,
	NGM_DIRECT_PLAYER_INFO,
	NGM_PLAYER_LEFT, 
	NGM_PLAYER_KICKED,
	NGM_GAME_INFO,
	NGM_GAME_STARTED,
	NGM_ASK_FOR_NAME,
	NGM_ANSWER_PLAYER_NAME,
	NGM_PING,
	NGM_GAME_IS_ALREADY_STARTED, // if new client tries to connect to already started game
	NGM_GAME_SETTINGS_CHANGED,

	// game playing phase
	NGM_ID_SEGMENT,
	NGM_ID_PLAYER_INFO,
	NGM_ID_LOGIC_ID,
	NGM_ID_START_GAME,

	NGM_ID_COMMAND_REGISTER_GROUP,
	NGM_ID_COMMAND_UNREGISTER_GROUP,
	NGM_ID_COMMAND_GROUP_COMMAND,
	NGM_ID_COMMAND_UNIT_COMMAND,
	NGM_ID_COMMAND_SHOW_AREAS,
	NGM_ID_COMMAND_CHECK_SUM,
	NGM_ID_COMMAND_DROP_PLAYER,

	// client commands
	NGM_PAUSE,
	NGM_GAME_SPEED,
	NGM_DROP_PLAYER,
	NGM_TIMEOUT,
	
	NGM_IAM_ALIVE,
	NGM_LEFT_GAME,

	// chat messages
	NGM_CHAT_MESSAGE,
	
	// load map messages
	NGM_SEND_ME_MAP,
	NGM_TOTAL_PACKED_SIZE,
	NGM_PACKED_FILE_INFO,
	NGM_FILE_INFO,
	NGM_PACKET,
	NGM_FINISHED,
	NGM_STREAM_FINISHED,
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __NET_MESSAGES_H__
