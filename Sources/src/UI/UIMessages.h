#ifndef __UI_MESSAGES_H__
#define __UI_MESSAGES_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EUIMessages
{
	UI_UNKNOWN_MESSAGE							= 0,
	
	UI_CLEAR_KEYBOARD_STATE					= 0x00009999,

	UI_SET_STATE_MESSAGE						= 0x00010000,
	UI_NEXT_STATE_MESSAGE						= 0x00010001,
	UI_SET_STATE_WO_NOTIFY					= 0x00010002,

	UI_SHOW_WINDOW									= 0x00010010,
	UI_ENABLE_WINDOW								= 0x00010020,
	UI_SET_MODAL_FLAG								= 0x00010030,
	UI_SET_ANIMATION_TIME						= 0x00010040,				//for Time Counter control
	UI_BLINK_WINDOW									= 0x00010050,

	UI_HIDE_WINDOW_FORCE						= 0x00010060,
	UI_SHOW_WINDOW_FORCE						= 0x00010070,
	UI_MODAL_FLAG_FORCE_REMOVE			= 0x00010080,
	UI_MODAL_FLAG_FORCE_SET					= 0x00010090,
	
	UI_ENABLE_WINDOW_FORCE					= 0x00010100,
	UI_DISABLE_WINDOW_FORCE					= 0x00010110,
	
	UI_NOTIFY_STATE_CHANGED_MESSAGE	= 0x20010000,
	UI_NOTIFY_POSITION_CHANGED			= 0x20010001,
	UI_NOTIFY_WINDOW_CLICKED				= 0x20010002,
	UI_NOTIFY_SELECTION_CHANGED			= 0x20010003,
	UI_NOTIFY_BAR_EXPAND						= 0x20010004,
	UI_NOTIFY_LIST_DOUBLE_CLICK			= 0x20010005,
	UI_NOTIFY_ANIMATION_FINISHED		= 0x20010010,
	UI_NOTIFY_EDIT_BOX_RETURN				= 0x20010020,
	UI_NOTIFY_EDIT_BOX_ESCAPE				= 0x20010021,
	UI_NOTIFY_EDIT_BOX_TEXT_CHANGED	= 0x20010022,
	
	UI_NOTIFY_LIST_RESORTED					= 0x20010023,
	UI_NOTIFY_WINDOW_RCLICKED				= 0x20010024,
	
	UI_BREAK_MESSAGE_BOX						= 0x20010100,
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif		//__UI_MESSAGES_H__
