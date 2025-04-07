#if !defined(__TerrainState__)
#define __TerrainState__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "InputMultiState.h"
#include "TileDrawState.h"
#include "DrawShadeState.h"
#include "StateTerrainFields.h"
#include "TemplateEditorFrame1.h"

class CTerrainState : public CInputMultiState
{
public:
	CTerrainState()
	{
		AddInputState( static_cast<CTileDrawState*>( 0 ) );		// STATE_TERRAIN_TILES				= 0
		AddInputState( static_cast<CDrawShadeState*>( 0 ) );	// STATE_TERRAIN_ALTITUDES		= 1
		AddInputState( static_cast<CFieldsState*>( 0 ) );			// STATE_TERRAIN_FIELDS				= 2
		
		SetActiveState( CTemplateEditorFrame::STATE_TERRAIN_TILES );
	}
	virtual void STDCALL	Enter();
};
#endif // !defined(__TerrainState__)
