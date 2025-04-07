#ifndef __IMAINCOMMANDS_H__
#define __IMAINCOMMANDS_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EMainLoopCommands
{
  CMD_WIREFRAME		= 0x00100000,
	CMD_SAVE				= 0x00100001,
	CMD_LOAD				= 0x00100002,
	CMD_EXIT				= 0x00100003,
	CMD_SCREENSHOT	= 0x00100004,
	CMD_SAVE_INPUT	= 0x00100005,
	CMD_PLAY_INPUT	= 0x00100006,
	CMD_DUMP_MEMORY = 0x00100007,
	// game speed
	CMD_GAME_SPEED_INC_SEND	= 0x00100008,
	CMD_GAME_SPEED_DEC_SEND	= 0x00100009,
	CMD_GAME_TIMEOUT				= 0x0010000a,
	CMD_GAME_UNTIMEOUT			= 0x0010000b,
	CMD_GAME_TIMEOUT_UPDATE = 0x0010000c,
	CMD_GAME_PAUSE_SEND			= 0x00100010,
	CMD_GAME_PAUSE_MENU			= 0x00100011,
	CMD_GAME_UNPAUSE_MENU		= 0x00100012,
	// some support
	CMD_LOAD_FINISHED		= 0x00100013,
	//
	CMD_GAME_PAUSE			= 0x00100014,
	CMD_GAME_SPEED_INC	= 0x00100015,
	CMD_GAME_SPEED_DEC	= 0x00100016,
	//
	CMD_GAME_TIMEOUT_SEND		= 0x00100017,
	CMD_GAME_UNTIMEOUT_SEND	= 0x00100018,
	// double clicks
	CMD_MOUSE0_DBLCLK	= 0x00100020,
	// actions
	CMD_BEGIN_ACTION1	= 0x00100021,
	CMD_END_ACTION1		= 0x00100022,
	CMD_BEGIN_ACTION2 = 0x00100023,
	CMD_END_ACTION2		= 0x00100024,
	// special commands for interface processing
	CMD_MOUSE_BUTTON0_DOWN = 0x00110001,
	CMD_MOUSE_BUTTON0_UP   = 0x00110002,
	CMD_MOUSE_BUTTON1_DOWN = 0x00110003,
	CMD_MOUSE_BUTTON1_UP   = 0x00110004,
	CMD_MOUSE_BUTTON2_DOWN = 0x00110005,
	CMD_MOUSE_BUTTON2_UP   = 0x00110006,
	// 
	// enum : 0 - remove, 1 - out of sync, 2 - lag started, 3 - lag finished, 4 - loading started, 5 - loading finished,
	//				6 - we out of sync, the end, 7 - part of players is our of sync, the end
	// the format is following:
	// nPlayer << 8 | enum
	CMD_MP_PLAYER_STATE_CHANGED	= 0x00110007,
	//
	CMD_RESTART_MISSION					= 0x00110008,
	CMD_QUIT_TO_MAINMENU				= 0x00110009,
	
	CMD_NUMPAD_ENTER						= 0x0011000A,
	
	CMD_SWITCH_INPUT						= 0x0011000b,

	CMD_FORCE_DWORD = 0x7fffffff
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __IMAINCOMMANDS_H__