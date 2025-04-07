#if !defined(__SimpleObjectsState__)
#define __SimpleObjectsState__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "InputMultiState.h"
#include "RoadDrawState.h"
#include "TemplateEditorFrame1.h"
#include "ObjectPlacerState.h"

class CSimpleObjectsState : public CInputMultiState
{
public:
	CSimpleObjectsState()
	{
		AddInputState( static_cast<CObjectPlacerState*>( 0 ) );	//STATE_SO_OBJECTS				= 1
		AddInputState( static_cast<CRoadDrawState*>( 0 ) );			//STATE_SO_FENCES					= 1
		AddInputState( static_cast<CRoadDrawState*>( 0 ) );			//STATE_SO_BRIDGES				= 2
		
		SetActiveState( CTemplateEditorFrame::STATE_SO_OBJECTS );
	}
	virtual void STDCALL	Enter();
};
#endif // !defined(__SimpleObjectsState__)
