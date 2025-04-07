#if !defined(__State__Groups__)
#define __State__Groups__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "InputState.h"
class CGroupsState : public IInputState
{
	//Common tools
	CInputStateParameter stateParameter;

	//IInputState interface
	virtual void STDCALL Enter();
	virtual void STDCALL	OnMouseMove( UINT nFlags, const CTPoint<int> &rMousePoint, CTemplateEditorFrame* pFrame );
};
#endif // !defined(__State__Groups__)
