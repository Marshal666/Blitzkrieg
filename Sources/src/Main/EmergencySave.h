#ifndef __EMERGENCYSAVE_H__
#define __EMERGENCYSAVE_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "iMain.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CEmergencySave : public IBaseCommand
{
	OBJECT_MINIMAL_METHODS( CEmergencySave );
	//
	CPtr<IMainLoop> pMainLoop;						// main loop to call save from
	CPtr<IStructureSaver> pSS;						// emergency save structure saver
public:
	CEmergencySave( IMainLoop *_pMainLoop, IStructureSaver *_pSS )
		: pMainLoop( _pMainLoop ), pSS( _pSS ) {  }
	// execute command
	virtual void STDCALL Do()
	{
		try
		{
			pMainLoop->operator&( *pSS );
			pSS = 0;
		}
		catch ( ... )
		{
			::MessageBox( 0, "Unable to execute 'emergency save' command", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		}
	}
	// un-execute command
	virtual void STDCALL UnDo() {  }
	// can this command be un-executed
	virtual bool STDCALL CanUnDo() { return false; }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __EMERGENCYSAVE_H__
