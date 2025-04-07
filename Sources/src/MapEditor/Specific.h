// Stingray Objective Toolkit

#define SEC_NO_NAMESPACE_USING 1
#include <ot_dockingwindows.h>		// Objective Toolkit docking windows
#include <ot_toolbar.h>						// Objective Toolkit toolbar/menubar
#include <ot_shortcutbar.h>				// Objective Toolkit shortcut bar
//
#include "..\Formats\fmtTerrain.h"
inline bool IsShiftKeyDown()
{
	return ( GetKeyState( VK_SHIFT ) < 0 );
}

inline bool IsCtrlKeyDown()
{
	return ( GetKeyState( VK_CONTROL ) < 0 );
}