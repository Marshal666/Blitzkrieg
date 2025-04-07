#if !defined(__VectorObjectsState__)
#define __VectorObjectsState__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "InputMultiState.h"
#include "VectorStripeObjectsState.h"
#include "RoadDrawState.h"
#include "TemplateEditorFrame1.h"

class CVectorObjectsState : public CInputMultiState
{
public:
	CVectorObjectsState()
	{
		AddInputState( static_cast<CRoadDrawState*>( 0 ) );	//STATE_VO_ENTRENCHMENTS			= 0
		AddInputState( static_cast<CRoads3DState*>( 0 ) );	//STATE_VO_ROADS3D						= 1
		AddInputState( static_cast<CRiversState*>( 0 ) );		//STATE_VO_RIVERS							= 2

		SetActiveState( CTemplateEditorFrame::STATE_VO_ENTRENCHMENTS );
	}
	virtual void STDCALL	Enter();
};
#endif // !defined(__VectorObjectsState__)
