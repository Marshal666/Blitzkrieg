#ifndef __IMAINCLASSIDS_H__
#define __IMAINCLASSIDS_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum
{
	MAIN_BASE_VALUE			= 0x10010000,

	MAIN_MAIN_LOOP													= MAIN_BASE_VALUE + 1,
	MAIN_TRANSCEIVER												= MAIN_BASE_VALUE + 2,	// common ID for transceivers
	MAIN_SP_TRANSCEIVER											= MAIN_BASE_VALUE + 3,	// single-player transceiver
	MAIN_MP_TRANSCEIVER											= MAIN_BASE_VALUE + 4,	// multiplayer transceiver
	MAIN_PRE_LMP_TRANSCEIVER								= MAIN_BASE_VALUE + 5,	// pre-LMP transceiver
	MAIN_COMMAND_CHANGE_TRANSCEIVER					= MAIN_BASE_VALUE + 6,	// command to change transceiver
	//
	MAIN_TRANS_COMMAND_REGISTER_GROUP				= MAIN_BASE_VALUE + 10,	// internal command for MP transceiver
	MAIN_TRANS_COMMAND_UNREGISTER_GROUP			= MAIN_BASE_VALUE + 11,	// internal command for MP transceiver
	MAIN_TRANS_COMMAND_GROUP_COMMAND				= MAIN_BASE_VALUE + 12,	// internal command for MP transceiver
	MAIN_TRANS_COMMAND_UNIT_COMMAND					= MAIN_BASE_VALUE + 13,	// internal command for MP transceiver
	MAIN_TRANS_COMMAND_SHOW_AREAS						= MAIN_BASE_VALUE + 14,	// internal command for MP transceiver
	MAIN_CONTROL_CHECK_SUM_COMMAND					= MAIN_BASE_VALUE + 15, // internal command for MP transceiver
	MAIN_DROP_PLAYER_COMMAND								= MAIN_BASE_VALUE + 16, // internal command for MP transceiver
	//
	MAIN_COMMAND_SAVE												= MAIN_BASE_VALUE + 20,
	MAIN_COMMAND_LOAD												= MAIN_BASE_VALUE + 21,
	MAIN_COMMAND_POP												= MAIN_BASE_VALUE + 22,
	MAIN_COMMAND_CMD												= MAIN_BASE_VALUE + 23,
	MAIN_COMMAND_ENABLE_MESSAGE_PROCESSING	= MAIN_BASE_VALUE + 24,
	MAIN_COMMAND_EXIT_GAME									= MAIN_BASE_VALUE + 25,
	MAIN_COMMAND_CHANGE_MOD									= MAIN_BASE_VALUE + 26,
	MAIN_COMMAND_PAUSE											= MAIN_BASE_VALUE + 27,
	//
	MAIN_SINGLE_TIMER												= MAIN_BASE_VALUE + 30,
	MAIN_SEGMENT_TIMER											= MAIN_BASE_VALUE + 31,
	MAIN_GAME_TIMER													= MAIN_BASE_VALUE + 32,
	MAIN_TIME_SLIDER												= MAIN_BASE_VALUE + 33,
	//
	MAIN_SCENARIO_TRACKER										= MAIN_BASE_VALUE + 100,
	MAIN_USER_PROFILE												= MAIN_BASE_VALUE + 103,
	MAIN_SCENARIO_UNIT											= MAIN_BASE_VALUE + 104,
	MAIN_PLAYER_SCENARIO_INFO								= MAIN_BASE_VALUE + 105,
	MAIN_CAMPAIGN_STATISTICS								= MAIN_BASE_VALUE + 106,
	MAIN_CHAPTER_STATISTICS									= MAIN_BASE_VALUE + 107,
	MAIN_MISSION_STATISTICS									= MAIN_BASE_VALUE + 108,
	//
	LAN_MULTIPLAYER													= MAIN_BASE_VALUE + 200,
	GAMESPY_MULTIPLAYER											= MAIN_BASE_VALUE + 201,
	INTERNET_MULTIPLAYER										= MAIN_BASE_VALUE + 202,
	//
	MAIN_PROGRESS_INDICATOR									= MAIN_BASE_VALUE + 300,
	//
	MAIN_COMMANDS_HISTORY										= MAIN_BASE_VALUE + 400,
	MAIN_COMMANDS_HISTORY_INTERNAL					= MAIN_BASE_VALUE + 401,
	//
	MAIN_FILES_INSPECTOR										= MAIN_BASE_VALUE + 500,
	MAIN_FILES_INSPECTOR_ENTRY_GDB					= MAIN_BASE_VALUE + 501,
	MAIN_FILES_INSPECTOR_ENTRY_COLLECTOR		= MAIN_BASE_VALUE + 502,
	
	MAIN_AUTOMAGIC													= MAIN_BASE_VALUE + 503,
	//
	MAIN_FORCE_DWORD = 0x7fffffff
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __IMAINCLASSIDS_H__