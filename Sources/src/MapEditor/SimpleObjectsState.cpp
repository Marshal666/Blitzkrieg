#include "stdafx.h"
#include "editor.h"
#include "SimpleObjectsState.h"
#include "frames.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CSimpleObjectsState::Enter()
{
	CInputMultiState::Enter();
}
