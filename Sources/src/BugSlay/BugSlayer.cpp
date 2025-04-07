#include "stdafx.h"

#include "CallStack.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY DllMain( HANDLE hModule, DWORD dwCallReason, LPVOID lpReserved )
{
  switch ( dwCallReason )
	{
		case DLL_PROCESS_ATTACH:
			{
				NBugSlayer::SetModuleHandle( reinterpret_cast<HINSTANCE>(hModule) );
				InitCommonControls();
			}
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
  }
  return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
