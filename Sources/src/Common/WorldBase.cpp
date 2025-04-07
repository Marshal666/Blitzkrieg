#include "StdAfx.h"

#include "WorldBase.h"

#include "..\AILogic\AITypes.h"
#include "..\Scene\Terrain.h"
#include "..\Main\TextSystem.h"
#include "..\Formats\fmtTerrain.h"
#include "MapObjVisitors.h"
#include "PlayEffect.h"
#include "Icons.h"
#include "..\UI\UI.h"
#include "..\UI\UIMessages.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** world base
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CComplexObjects::operator&( IStructureSaver &ss )
{
	CSaverAccessor saver = &ss;
	typedef std::pair< CPtr<SMapObject>, CPtr<IRefCount> > CObjectPair;
	std::list<CObjectPair> objects;
	// 
	if ( !saver.IsReading() )
	{
		for ( CVisAIMap::iterator it = visai.begin(); it != visai.end(); ++it )
			objects.push_back( CObjectPair(it->first, it->second) );
	}
	//
	saver.Add( 1, &objects );
	//
	if ( saver.IsReading() )
	{
		visai.clear();
		aivis.clear();
		for ( std::list<CObjectPair>::iterator it = objects.begin(); it != objects.end(); ++it )
			AddSegment( it->second, it->first );
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SSpanStorage
{
	CPtr<SBridgeSpanObject> pSpan;
	CPtr<IRefCount> pAIObj;
	std::list< CPtr<IVisObj> > visobjects;
	//
	int operator&( IStructureSaver &ss )
	{
		CSaverAccessor saver = &ss;
		saver.Add( 1, &pSpan );
		saver.Add( 2, &pAIObj );
		saver.Add( 3, &visobjects );
		return 0;
	}
};
struct SMapObjectStorage
{
	CPtr<SMapObject> pMO;
	CPtr<IRefCount> pAIObj;
	CPtr<IVisObj> pVisObj;
	//
	int operator&( IStructureSaver &ss )
	{
		CSaverAccessor saver = &ss;
		saver.Add( 1, &pMO );
		saver.Add( 2, &pAIObj );
		saver.Add( 3, &pVisObj );
		return 0;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddSpan( IRefCount *pAIObj, SBridgeSpanObject *pSpan, std::list<SSpanStorage> &spans )
{
	spans.push_back( SSpanStorage() );
	SSpanStorage &storage = spans.back();
	storage.pAIObj = pAIObj;
	storage.pSpan = pSpan;
	if ( pSpan->pSlab ) 
		storage.visobjects.push_back( pSpan->pSlab->pVisObj );
	if ( pSpan->pBackGirder ) 
		storage.visobjects.push_back( pSpan->pBackGirder->pVisObj );
	if ( pSpan->pFrontGirder ) 
		storage.visobjects.push_back( pSpan->pFrontGirder->pVisObj );
}
void AddMapObj( IRefCount *pAIObj, SMapObject *pMO, std::list<SMapObjectStorage> &mos )
{
	mos.push_back( SMapObjectStorage() );
	SMapObjectStorage &storage = mos.back();
	storage.pMO = pMO;
	storage.pAIObj = pAIObj;
	storage.pVisObj = pMO->pVisObj;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CWorldBase::operator&( IStructureSaver &ss )
{
	CSaverAccessor saver = &ss;
	// serialize all map objects
	// ����� ����������� ���� ��� ����, ����� ��� ��������� ��������� �������������� �/� ������������� �������
	// Vis & AI objects must be stored separatelly, �.�. ������ ������������ ���������� ������ �� SMapObject � ������� ������������
	{
		std::list<SMapObjectStorage> mos;
		std::list<SSpanStorage> spans;
		typedef std::pair< CPtr<IRefCount>, CPtr<IRefCount> > CObjectsPair;
		std::list<CObjectsPair> containers;
		if ( saver.IsReading() )
		{
			bAADetectedFlag = false;
			saver.Add( 1, &mos );
			//saver.Add( 2, &containers );
			saver.Add( 3, &spans );
			saver.Add( 4, &inContainer );
			//
			for ( std::list<SMapObjectStorage>::iterator it = mos.begin(); it != mos.end(); ++it )
			{
				SMapObjectStorage &storage = *it;
				if ( storage.pAIObj ) 
					aiobjects[storage.pAIObj] = storage.pMO;
				if ( storage.pVisObj ) 
					visobjects[storage.pVisObj] = storage.pMO;
			}
			//
			for ( std::list<SSpanStorage>::iterator it = spans.begin(); it != spans.end(); ++it )
			{
				SSpanStorage &storage = *it;
				if ( storage.pAIObj ) 
					aispans[storage.pAIObj] = storage.pSpan;
				for ( std::list< CPtr<IVisObj> >::iterator vis = storage.visobjects.begin(); vis != storage.visobjects.end(); ++vis )
				{
					if ( *vis ) 
						visspans[*vis] = storage.pSpan;
				}
			}
			//
			/*
			for ( std::list<CObjectsPair>::iterator it = containers.begin(); it != containers.end(); ++it )
				inContainer[it->first] = it->second;
				*/
		}
		else
		{
			// map objects
			for ( CMapObjectsMap::iterator it = aiobjects.begin(); it != aiobjects.end(); ++it )
				AddMapObj( it->first, it->second, mos );
			for ( CMapObjectsMap::iterator it = visobjects.begin(); it != visobjects.end(); ++it )
			{
				if ( FindByAI(it->second->pAIObj) == 0 ) 
					AddMapObj( 0, it->second, mos );
			}
			// spans
			for ( CBridgeSpanObjectsMap::iterator it = aispans.begin(); it != aispans.end(); ++it )
				AddSpan( it->first, it->second, spans );
			for ( CBridgeSpanObjectsMap::iterator it = visspans.begin(); it != visspans.end(); ++it )
			{
				if ( FindSpanByAI(it->second->pAIObj) == 0 ) 
					AddSpan( 0, it->second, spans );
			}
			//
			/*
			for ( CLinksMap::iterator it = inContainer.begin(); it != inContainer.end(); ++it )
				containers.push_back( CObjectsPair(it->first, it->second) );
				*/
			//
			saver.Add( 1, &mos );
			//saver.Add( 2, &containers );
			saver.Add( 3, &spans );
			saver.Add( 4, &inContainer );
		}
	}
	saver.Add( 5, &vLastAnchor );
	saver.Add( 6, &warFogLastTime );
	saver.Add( 7, &bEnableAIInfo );
	//saver.Add( 8, &showicons );
	saver.Add( 9, &entrenchments );
	saver.Add( 11, &nSeason );
	saver.Add( 13, &updatable );
	if ( saver.IsReading() ) 
	{
		dwFlashFireColor = GetGlobalVar( (std::string("Scene.Colors.") + GetSeasonName() + ".FlashFire.Color").c_str(), int(0xffffffff) );
		dwFlashExpColor = GetGlobalVar( (std::string("Scene.Colors.") + GetSeasonName() + ".FlashExplode.Color").c_str(), int(0xffffffff) );
	}
	saver.Add( 14, &objectsSounds );
	//
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CWorldBase::CWorldBase()
{
	nSeason = SEASON_SUMMER;
	//
	vLastAnchor.Set( -1000000, -1000000, -1000000 );
	//
	// ������� ����� ������������ ����� �������, ������ ��� ��� ����� ������� � ���� �� �����
	// �� �� ����� ������ � ���� �� ����� �� ����� ��������� ����� - ��� � Updater-� �������������
	fnAIUpdates.push_back( &CWorldBase::AIUpdateNewProjectiles );	
	fnAIUpdates.push_back( &CWorldBase::AIUpdateNewObjects );	
	fnAIUpdates.push_back( &CWorldBase::AIUpdateNewUnits );

	// update actions MUST precede update placements
	fnAIUpdates.push_back( &CWorldBase::AIUpdateActions );

	fnAIUpdates.push_back( &CWorldBase::AIUpdateEntrances );
	fnAIUpdates.push_back( &CWorldBase::AIUpdateWarFog );
	fnAIUpdates.push_back( &CWorldBase::AIUpdatePlacements );
	fnAIUpdates.push_back( &CWorldBase::AIUpdateRPGParams );
	fnAIUpdates.push_back( &CWorldBase::AIUpdateDiplomacy );
	fnAIUpdates.push_back( &CWorldBase::AIUpdateShots );
	fnAIUpdates.push_back( &CWorldBase::AIUpdateAiming );
	fnAIUpdates.push_back( &CWorldBase::AIUpdateHits );

	fnAIUpdates.push_back( &CWorldBase::AIUpdateEntrenchments );
	fnAIUpdates.push_back( &CWorldBase::AIUpdateSquads );

	fnAIUpdates.push_back( &CWorldBase::AIUpdateFeedbacks );
	
	fnAIUpdates.push_back( &CWorldBase::AIUpdateDeadProjectiles );
	fnAIUpdates.push_back( &CWorldBase::AIUpdateDeadUnits );
	// AIUpdateRemoveObjects ���� ����� AIUpdateDeadUnits, ��� ��� ����� ����� ��������� ����� ������ � ��� �� ��������
	fnAIUpdates.push_back( &CWorldBase::AIUpdateRemoveObjects );
	//
	fnAIUpdates.push_back( &CWorldBase::AIUpdateBridges );
	fnAIUpdates.push_back( &CWorldBase::AIUpdateRevealCircles );
	fnAIUpdates.push_back( &CWorldBase::AIUpdateAreas );
	//
	fnAIUpdates.push_back( &CWorldBase::AIUpdateAcknowledgemets );
	fnAIUpdates.push_back( &CWorldBase::AIUpdateCombatSituationInfo );
	bForceRotation = false;
	bEnableAIInfo = false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CWorldBase::~CWorldBase()
{
	if ( pScene )
	{
//		for ( CMapObjectsMap::iterator it = visobjects.begin(); it != visobjects.end(); ++it )
//		{
//			SMapObject *pMO = it->second;
//			if ( pMO->pVisObj )
//				pScene->RemoveObject( pMO->pVisObj );
//			if ( pMO->pShadow )
//				pScene->RemoveObject( pMO->pShadow );
//		}
		pScene->Clear();
		pScene->SetTerrain( 0 );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::Init( ISingleton *pSingleton )
{
	pTimer = GetSingleton<IGameTimer>( pSingleton );
	pAckManager = GetSingleton<IClientAckManager>( pSingleton );
	pScene = GetSingleton<IScene>( pSingleton );
	pCursor = GetSingleton<ICursor>( pSingleton );
	pInput = GetSingleton<IInput>( pSingleton );
	pAILogic = GetSingleton<IAILogic>( pSingleton );
	pTransceiver = GetSingleton<ITransceiver>( pSingleton );
	pCamera = GetSingleton<ICamera>( pSingleton );
	pGFX = GetSingleton<IGFX>( pSingleton );
	pSFX = GetSingleton<ISFX>( pSingleton );
	pSMan = GetSingleton<ISoundManager>( pSingleton );
	pGDB = GetSingleton<IObjectsDB>( pSingleton );
	pVOB = GetSingleton<IVisObjBuilder>( pSingleton );
	//
	dwFlashFireColor = GetGlobalVar( (std::string("Scene.Colors.") + GetSeasonName() + ".FlashFire.Color").c_str(), int(0xffffffff) );
	dwFlashExpColor = GetGlobalVar( (std::string("Scene.Colors.") + GetSeasonName() + ".FlashExplode.Color").c_str(), int(0xffffffff) );
	bAADetectedFlag = false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::Clear()
{
	vLastAnchor = VNULL3;
	warFogLastTime = 0;
	//
	entrenchments.Clear();
	inContainer.clear();
	//
	aispans.clear();
	visspans.clear();
	//
	aiobjects.clear();
	visobjects.clear();
	//
	//showicons.clear();
	messages.clear();
	//
	if ( pScene )
	{
		pScene->Clear();
		pScene->SetTerrain( 0 );
	}
	objectsSounds.clear();
	bAADetectedFlag = false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::Start()
{
	//AIUpdateNewObjects( GetSingleton<IGameTimer>()->GetGameTime() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** adding/removing map objects to world/scene
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SMapObject* CWorldBase::CreateMapObject( IRefCount *pAIObj, int nDBID, int nFrameIndex, const float fNewHP )
{
	const SGDBObjectDesc *pDesc = pGDB->GetDesc( nDBID );
	IMapObj *pMO = 0;
	switch ( pDesc->eGameType ) 
	{
		case SGVOGT_UNIT:
			pMO = CreateObject<IMapObj>( pDesc->eVisType == SGVOT_SPRITE ? MISSION_MO_UNIT_INFANTRY : MISSION_MO_UNIT_MECHANICAL );
			break;
		case SGVOGT_SQUAD:
			pMO = CreateObject<IMapObj>( MISSION_MO_SQUAD );
			break;
		case SGVOGT_BUILDING:
		case SGVOGT_FORTIFICATION:
			pMO = CreateObject<IMapObj>( MISSION_MO_BUILDING );
			break;
		case SGVOGT_ENTRENCHMENT:
			pMO = CreateObject<IMapObj>( MISSION_MO_ENTRENCHMENT_SEGMENT );
			break;
		default:
			pMO = CreateObject<IMapObj>( MISSION_MO_OBJECT );
	}
	//
	if ( pMO->Create(pAIObj, pDesc, nSeason, nFrameIndex, fNewHP, pVOB, pGDB) == true )
		return (SMapObject*)pMO;
	else
	{
		pMO->AddRef();
		pMO->Release();
		return 0;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SMapObject* CWorldBase::AddToWorld( IRefCount *pAIObj, int nDBID, int nFrameIndex, const float fNewHP )
{
	// check for such object already exist
	NI_ASSERT_T( aiobjects.find( pAIObj ) == aiobjects.end(), NStr::Format("object 0x%x (%s) already exist as \"%s\"", pAIObj, typeid(*pAIObj).name(), aiobjects[pAIObj]->pDesc->szKey.c_str()) );
	// create
	SMapObject *pMO = CreateMapObject( pAIObj, nDBID, nFrameIndex, fNewHP );
	// 
	AddToWorld( pMO );
	//
	return pMO;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CWorldBase::AddToWorld( SMapObject *pMO )
{
	// register in AI map
	aiobjects[pMO->pAIObj] = pMO;
	//
	NewObjectAdded( pMO );
	//
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AddToScene( SMapObject *pMO, bool bOutbound, EObjGameType eGameType )
{
	SGetVisObjesVisitor visitor;
	pMO->Visit( &visitor );
	for ( std::list<SGetVisObjesVisitor::SVisObjDesc>::iterator it = visitor.objects.begin(); it != visitor.objects.end(); ++it )
	{
		if ( bOutbound )
			pScene->AddOutboundObject( it->pVisObj, it->eGameType );
		else if ( it->bOutbound ) 
			pScene->AddOutboundObject2( it->pVisObj, it->eGameType );
		else if ( it->eGameType == SGVOGT_SHADOW ) 
		{
			it->pVisObj->SetColor( 0x00000000 );
			it->pVisObj->SetOpacity( 0x80 );
			pScene->AddObject( it->pVisObj, SGVOGT_SHADOW, 0 );
		}
		else if ( it->eGameType == SGVOGT_FLAG ) 
			pScene->AddObject( it->pVisObj, SGVOGT_UNIT, pMO->pDesc );
		else if ( eGameType == SGVOGT_UNKNOWN )
			pScene->AddObject( it->pVisObj, it->eGameType, pMO->pDesc );
		else
			pScene->AddObject( it->pVisObj, eGameType, pMO->pDesc );
	}
	// register main object
	visobjects[pMO->pVisObj] = pMO;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::RemoveFromWorld( SMapObject *pMO )
{
	entrenchments.RemoveSegment( pMO );
	aiobjects.erase( pMO->pAIObj );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::RemoveFromScene( SMapObject *pMO )
{
	// remove shadow
	if ( pMO->pShadow )
		pScene->RemoveObject( pMO->pShadow );
	// remove main object
	pScene->RemoveObject( pMO->pVisObj );
	// unregister main object
	visobjects.erase( pMO->pVisObj );
}
void CWorldBase::RemoveAIObj( SMapObject *pMO, bool bDelayed )	
{ 
	if ( bDelayed )
		delayedRemoveAIObjes.push_back( pMO );
	else
	{
		CObj<SMapObject> pTemp = pMO;	// to preserve map object from untimely destruction
		aiobjects.erase( pMO->pAIObj ); 
		pMO->pAIObj = 0; 
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::RemoveMapObj( SMapObject *pMO ) 
{ 
	if ( SMapObject *pContainer = GetContainer(pMO) )
		static_cast<IMOContainer*>(pContainer)->Load( static_cast<IMOUnit*>(pMO), false );
	inContainer.erase( pMO->pAIObj );
	// remove from selection group and from active selection
	RemoveFromSelectionGroup( pMO );
	ResetSelection( pMO );
	//
	RemoveFromScene( pMO ); 
	RemoveFromWorld( pMO ); 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::GetAllObjectsByMatch( std::list<SMapObject*> &mapobjects, const SGDBObjectDesc *pDesc, const bool bSelectableOnly )
{
	for ( CMapObjectsMap::iterator it = visobjects.begin(); it != visobjects.end(); ++it )
	{
		if ( (it->second->pDesc == pDesc) && (!bSelectableOnly || (bSelectableOnly && it->second->CanSelect())) ) 
			mapobjects.push_back( it->second );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** adding/removing bridges to world/scene
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SBridgeSpanObject* CWorldBase::CreateSpanObject( int nDBID, int nFrameIndex, float fNewHP )
{
	// extract DB descriptor
	const SGDBObjectDesc *pDesc = pGDB->GetDesc( nDBID );
	NI_ASSERT_T( pDesc != 0, NStr::Format("can't find DB entry for object %d", nDBID) );
	const SBridgeRPGStats *pRPG = static_cast<const SBridgeRPGStats*>( pGDB->GetRPGStats( pDesc ) );
	// create new empty span object
	SBridgeSpanObject *pSpan = CreateObject<SBridgeSpanObject>( MISSION_MO_BRIDGE_SPAN );
	pSpan->Create( 0, pDesc, nSeason, nFrameIndex, fNewHP, pVOB, pGDB );
	//
	return pSpan;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SBridgeSpanObject* CWorldBase::AddSpanToWorld( IRefCount *pAIObj, int nDBID, int nFrameIndex, float fNewHP )
{
	// check for such object already exist
	NI_ASSERT_T( aispans.find( pAIObj ) == aispans.end(), NStr::Format("object 0x%x (%s) already exist as \"%s\"", pAIObj, typeid(*pAIObj).name(), aispans[pAIObj]->GetDesc()->szKey.c_str()) );
	// create
	SBridgeSpanObject *pSpan = CreateSpanObject( nDBID, nFrameIndex, fNewHP );
	pSpan->pSlab->pAIObj = pAIObj;
	if ( pSpan->pBackGirder )
		pSpan->pBackGirder->pAIObj = pAIObj;
	if ( pSpan->pFrontGirder )
		pSpan->pFrontGirder->pAIObj = pAIObj;
	pSpan->pAIObj = pAIObj;
	// register in AI map
	aispans[pSpan->GetAIObj()] = pSpan;
	//
	NewObjectAdded( pSpan->pSlab );
	if ( pSpan->pBackGirder )
		NewObjectAdded( pSpan->pBackGirder );
	if ( pSpan->pFrontGirder )
		NewObjectAdded( pSpan->pFrontGirder );
	//
	return pSpan;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AddToScene( SBridgeSpanObject *pSpan )
{
	// register main object
	visspans[pSpan->pSlab->pVisObj] = pSpan;
	if ( pSpan->pBackGirder )
		visspans[pSpan->pBackGirder->pVisObj] = pSpan;
	if ( pSpan->pFrontGirder )
		visspans[pSpan->pFrontGirder->pVisObj] = pSpan;
	// add main object
	AddToScene( pSpan->pSlab, false, SGVOGT_BRIDGE );
	if ( pSpan->pBackGirder )
		AddToScene( pSpan->pBackGirder, false, SGVOGT_OBJECT );
	if ( pSpan->pFrontGirder )
		AddToScene( pSpan->pFrontGirder, false, SGVOGT_OBJECT );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::RemoveFromWorld( SBridgeSpanObject *pSpan )
{
	aispans.erase( pSpan->GetAIObj() );
	pSpan->pAIObj = 0;
	if ( pSpan->pSlab ) 
		pSpan->pSlab->pAIObj = 0;
	if ( pSpan->pBackGirder ) 
		pSpan->pBackGirder->pAIObj = 0;
	if ( pSpan->pFrontGirder ) 
		pSpan->pFrontGirder->pAIObj = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::RemoveFromScene( SBridgeSpanObject *pSpan )
{
	// remove main object
	RemoveFromScene( pSpan->pSlab );
	if ( pSpan->pBackGirder )
		RemoveFromScene( pSpan->pBackGirder );
	if ( pSpan->pFrontGirder )
		RemoveFromScene( pSpan->pFrontGirder );
	// unregister main object
	visspans.erase( pSpan->pSlab->pVisObj );
	if ( pSpan->pBackGirder )
		visspans.erase( pSpan->pBackGirder->pVisObj );
	if ( pSpan->pFrontGirder )
		visspans.erase( pSpan->pFrontGirder->pVisObj );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** AI update functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// general update
void CWorldBase::Update( const NTimer::STime &currTime )
{
	pCamera->Update();
	pGFX->SetViewTransform( pCamera->GetPlacement() );
	// updatable units
	for ( std::list< CPtr<IMOUnit> >::iterator it = updatable.begin(); it != updatable.end(); )
	{
		if ( (*it)->Update(currTime) == true )
			it = updatable.erase( it );
		else
			++it;
	}
	//
	UpdatePick( GetSingleton<ICursor>()->GetPos(), currTime, true );
	// special case - for LAG in multiplayer game we need additional check for game and segment timer corellation
	ISegmentTimer *pSegmentTimer = GetSingleton<IGameTimer>()->GetGameSegmentTimer();
	if ( (pSegmentTimer->Get() + pSegmentTimer->GetSegmentTime() >= currTime) || (GetGlobalVar("editor", 0) != 0) )
	{
		for ( std::vector<AI_UPDATE>::iterator it = fnAIUpdates.begin(); it != fnAIUpdates.end(); ++it )
			(this->*(*it))( currTime );
		pAILogic->EndUpdates();
		UpdatePick( GetSingleton<ICursor>()->GetPos(), currTime, true );
	}
	// remove delayed objects from AI
	while ( !delayedRemoveAIObjes.empty() )
	{
		if ( SMapObject *pMO = delayedRemoveAIObjes.front() )
		{
			if ( pMO->pVisObj ) 
				pMO->pVisObj->Update( currTime );
			RemoveAIObj( delayedRemoveAIObjes.front(), false );
		}
		delayedRemoveAIObjes.pop_front();
	}
	// CRAP{ ��� ��������������� �������� ������� � �������� �������
	if ( bForceRotation )
	{
		int nRotateDirection = currTime * 2;
		for ( CMapObjectsMap::iterator it = visobjects.begin(); it != visobjects.end(); ++it )
			it->second->pVisObj->SetDirection( nRotateDirection );
	}
	// CRAP}

	pAckManager->Update( pScene );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::GetVisibilityRectBounds( const CTRect<float> &rcScreen, CVec2 *pvLT, CVec2 *pvRT, CVec2 *pvLB, CVec2 *pvRB )
{
	CVec3 vPos;
	const float fCellCoeff = 1.0f / fWorldCellSize;
	{
		CTPoint<float> point = rcScreen.GetLeftTop();
		GetPos3( &vPos, point.x, point.y );
		pvLT->Set( int(vPos.x * fCellCoeff + 0.5f) - 3, int(vPos.y * fCellCoeff + 0.5f) );
	}
	{
		CTPoint<float> point = rcScreen.GetRightBottom();
		GetPos3( &vPos, point.x, point.y );
		pvRB->Set( int(vPos.x * fCellCoeff + 0.5f) + 3, int(vPos.y * fCellCoeff + 0.5f) );
	}
	// correct result
	pvLB->x = 0.5f*( pvRB->x - pvRB->y + pvLT->x + pvLT->y );
	pvLB->y = 0.5f*( pvLT->x + pvLT->y - pvRB->x + pvRB->y );
	if ( (MINT(pvLB->x) != pvLB->x) || (MINT(pvLB->y) != pvLB->y) )
		pvLT->x--;
	// recalc
	pvLB->x = 0.5f*( pvRB->x - pvRB->y + pvLT->x + pvLT->y );
	pvLB->y = 0.5f*( pvLT->x + pvLT->y - pvRB->x + pvRB->y );

	pvRT->x = 0.5f*( pvLT->x - pvLT->y + pvRB->x + pvRB->y );
	pvRT->y = 0.5f*( pvRB->x + pvRB->y - pvLT->x + pvLT->y );
	//
	NI_ASSERT( pvLT->x - pvLT->y == pvRT->x - pvRT->y );
	NI_ASSERT( pvRB->x - pvRB->y == pvLB->x - pvLB->y );
	NI_ASSERT( pvLT->x + pvLT->y == pvLB->x + pvLB->y );
	NI_ASSERT( pvRB->x + pvRB->y == pvRT->x + pvRT->y );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateWarFogLocal()
{
	CTRect<float> rcRect = pGFX->GetScreenRect();
	CVec2 vLT, vLB, vRB, vRT;
	GetVisibilityRectBounds( rcRect, &vLT, &vRT, &vLB, &vRB );
	// war fog
	struct SAIVisInfo *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->GetVisibilities( vLT, vLB, vRB, vRT, &pObjects, &nNumObjects );
	pScene->SetWarFog( pObjects, nNumObjects );
	// AI passability info
	AIUpdatePassability( vLT, vLB, vRB, vRT );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateWarFog( const NTimer::STime &currTime )
{
	if ( (currTime >= warFogLastTime + 1000) || (vLastAnchor != pCamera->GetAnchor()) )
	{
		AIUpdateWarFogLocal();
		warFogLastTime = currTime;
		vLastAnchor = pCamera->GetAnchor();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CWorldBase::ToggleAIInfo() 
{ 
	bEnableAIInfo = !bEnableAIInfo; 
	if ( !bEnableAIInfo )
		pScene->GetTerrain()->SetAIMarker( 0, 0 );
	else if ( bEnableAIInfo )
		vLastAnchor.Set( -1000000, -1000000, -1000000 );
	return bEnableAIInfo; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdatePassability( const CVec2 &vLT, const CVec2 &vLB, const CVec2 &vRB, const CVec2 &vRT )
{
	if ( !bEnableAIInfo )
		return;
	//
	SAIPassabilityInfo *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->GetDisplayPassability( vLT, vLB, vRB, vRT, &pObjects, &nNumObjects );
	pScene->GetTerrain()->SetAIMarker( pObjects, nNumObjects );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateNewObjects( const NTimer::STime &currTime )
{
	int nNumObjects = 0;
	SNewUnitInfo *pObjects = 0;
	pAILogic->GetNewStaticObjects( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		const SNewUnitInfo &info = pObjects[i];
		NI_ASSERT_TF( info.dbID != 0xffff, "object with undefined type has come from AI", continue );
		const SGDBObjectDesc *pDesc = pGDB->GetDesc( info.dbID );
		NI_ASSERT_SLOW_TF( pDesc != 0, NStr::Format("Can't find DB description with index %d", info.dbID), continue );
		// object's position
		CVec3 vPos;
		AI2Vis( &vPos, info.center.x, info.center.y, info.z );
		if ( info.nFrameIndex == -2 )				// special case - "�����-�����-������"
		{
			if ( const SMechUnitRPGStats *pRPG = NGDB::GetRPGStats<SMechUnitRPGStats>(pGDB, pDesc) )
			{
				if ( !pRPG->deathCraters.empty() )
					SetCraterEffect( pRPG->deathCraters[rand() % pRPG->deathCraters.size()], nSeason, vPos, 100, pScene, pVOB );
			}
		}
		else																// ordinary static object
		{
			// add to world
			SMapObject *pMO = AddToWorld( info.pObj, info.dbID, info.nFrameIndex, info.fHitPoints );
			pMO->SetPlacement( vPos, info.dir );
			if ( info.eDipl != EDI_NEUTRAL ) 
			{
				NI_ASSERT_SLOW_T( dynamic_cast<IMOSelectable*>(pMO) != 0, NStr::Format("Object of %s is not a IMOSelectable - wrong diplomacy update", typeid(*pMO).name()) );
				static_cast<IMOSelectable*>(pMO)->AIUpdateDiplomacy( SAINotifyDiplomacy(info.eDipl, pMO->GetAIObj(), info.nPlayer ) );
			}
			// CRAP{ set scale
			if ( pObjects[i].fResize != 1.0f ) 
				static_cast_ptr<IObjVisObj*>(pMO->pVisObj)->SetScale( pObjects[i].fResize, pObjects[i].fResize, pObjects[i].fResize );
			// CRAP}
			// add to scene
			AddToScene( pMO );
			if ( SGVOGT_OBJECT == pMO->pDesc->eGameType ||
					 SGVOGT_BUILDING == pMO->pDesc->eGameType )
			{
				const SObjectBaseRPGStats * pStats = static_cast_gdb<const SObjectBaseRPGStats*>(pMO->pRPG);
				const CVec3 vPos = pMO->pVisObj->GetPosition();
				SObjectSounds info;
				if ( !pStats->szAmbientSound.empty() )
					info.wSoundID = pScene->AddSoundToMap( pStats->szAmbientSound.c_str(), vPos );
				if ( !pStats->szCycledSound.empty() )
					info.wLoopedSoundID = pScene->AddSoundToMap( pStats->szCycledSound.c_str(), vPos );
				if ( info.wSoundID || info.wLoopedSoundID )
					objectsSounds[pMO] = info;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateRemoveObjects( const NTimer::STime &currTime )
{
	IRefCount **ppObjects = 0;
	int nNumObjects = 0;
	// units
	pAILogic->GetDisappearedUnits( &ppObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		if ( SMapObject *pMO = FindByAI(ppObjects[i]) )
		{
			if ( pMO->GetDesc()->eGameType == SGVOGT_UNIT ) 
			{
				IMOUnit *pMOUnit = static_cast<IMOUnit*>(pMO);
				pMOUnit->PrepareToRemove();
				pMOUnit->SetSquad( 0 );
				pAckManager->UnitDead( pMOUnit, pScene );
			}
			RemoveMapObj( pMO );
		}
	}
	// static objects
	pAILogic->GetDeletedStaticObjects( &ppObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		if ( SMapObject *pMO = FindByAI(ppObjects[i]) )
		{
			if ( pMO->pDesc->eGameType == SGVOGT_ENTRENCHMENT )
				entrenchments.RemoveSegment( pMO );
			RemoveMapObj( pMO );
		}
		else if ( SBridgeSpanObject *pSpan = FindSpanByAI( ppObjects[i] ) )
		{
			RemoveSpanObj( pSpan );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateNewUnits( const NTimer::STime &currTime )
{
	SNewUnitInfo *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->GetNewUnits( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		const SNewUnitInfo &info = pObjects[i];
		NI_ASSERT_TF( info.dbID != 0xffff, "object with undefined type has come from AI", continue );
		// create unit and add to world
		SMapObject *pMO = AddToWorld( info.pObj, info.dbID, info.nFrameIndex, info.fHitPoints );
		// set placement for unit
		CVec3 vPos;
		AI2Vis( &vPos, info.center.x, info.center.y, info.z );
		pMO->SetPlacement( vPos, info.dir );
		pMO->AIUpdatePlacement( info, currTime, pScene );
		//if ( info.eDipl != EDI_NEUTRAL ) 
		{
			NI_ASSERT_SLOW_T( dynamic_cast<IMOSelectable*>(pMO) != 0, NStr::Format("Object of type \"%s\" (AI type \"%s\") is not a IMOSelectable - wrong diplomacy update", typeid(*pMO).name(), typeid(*(pMO->pAIObj)).name()) );
			if ( dynamic_cast<IMOSelectable*>(pMO) != 0 ) 
				static_cast<IMOSelectable*>(pMO)->AIUpdateDiplomacy( SAINotifyDiplomacy(info.eDipl, pMO->GetAIObj(), info.nPlayer ) );
		}
		// and, at rest, add object to scene
		if ( pMO->GetDesc()->eGameType == SGVOGT_UNIT )
		{
			const SUnitBaseRPGStats *pRPG = static_cast<const SUnitBaseRPGStats*>( pMO->pRPG.GetPtr() );
			AddToScene( pMO, pRPG->IsAviation() );	// aviation can be outbound
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateNewProjectiles( const NTimer::STime &currTime )
{
	SAINotifyNewProjectile *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->GetNewProjectiles( &pObjects, &nNumObjects );
	if ( nNumObjects > 0 )
	{
		for ( int i=0; i<nNumObjects; ++i )
		{
			SMapObject *pUnit = FindByAI( pObjects[i].pSource );
			if ( pUnit == 0 )
				continue;
			if ( SMapObject *pMO = static_cast<SMapObject*>( static_cast<IMOUnit*>(pUnit)->AIUpdateFireWithProjectile(pObjects[i], currTime, pVOB) ) )
			{
				AddToWorld( pMO );
				AddToScene( pMO, true, SGVOGT_EFFECT );
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdatePlacements( const NTimer::STime &currTime )
{
	SAINotifyPlacement *pObjects = 0;
	int nNumObjects = 0;
	// unit
	pAILogic->UpdatePlacements( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		if ( IMapObj *pMO = FindByAI(pObjects[i].pObj) )
			pMO->AIUpdatePlacement( pObjects[i], currTime, pScene );
	}
	// static objects
	pAILogic->UpdateStObjPlacements( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		if ( IMapObj *pMO = FindByAI(pObjects[i].pObj) )
			pMO->AIUpdatePlacement( pObjects[i], currTime, pScene );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateRPGParams( const NTimer::STime &currTime )
{
	SAINotifyRPGStats *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->UpdateRPGParams( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		if ( SMapObject *pMO = FindByAI(pObjects[i].pObj) )
		{
			if ( pMO->AIUpdateRPGStats(pObjects[i], pVOB, pScene) == false )
			{
				ResetSelection( pMO );
				RemoveFromSelectionGroup( pMO );
				// delete sounds
				ObjectsSounds::iterator soundIter = objectsSounds.find( pMO );
				if ( objectsSounds.end() != soundIter )
				{
					pScene->RemoveSoundFromMap( soundIter->second.wLoopedSoundID );
					pScene->RemoveSoundFromMap( soundIter->second.wSoundID );
				}
				objectsSounds.erase( soundIter );
			}
		}
		else if ( SBridgeSpanObject *pSpan = FindSpanByAI(pObjects[i].pObj) )
			pSpan->AIUpdateRPGStats( pObjects[i], pVOB, pScene );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateDiplomacy( const NTimer::STime &currTime )
{
	SAINotifyDiplomacy *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->UpdateDiplomacies( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		SMapObject *pMO = FindByAI( pObjects[i].pObj );
		if ( pMO )
		{
			if ( checked_cast<IMOSelectable*>(pMO)->AIUpdateDiplomacy(pObjects[i]) == false )
			{
				RemoveFromSelectionGroup( pMO );
				ResetSelection( pMO );
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateActions( const NTimer::STime &currTime )
{
	SAINotifyAction *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->UpdateActions( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		SMapObject *pMO = FindByAI( pObjects[i].pObj );
		if ( pMO == 0 ) 
			continue;
		//process selection messages
		switch ( pObjects[i].typeID ) 
		{
			case ACTION_NOTIFY_CHANGE_SELECTION:
				if ( pObjects[i].nParam == 1 )
					Select( pMO );
				else if ( pObjects[i].nParam == 0 )
					ResetSelectionOverridable( pMO->pVisObj );
				break;
			case ACTION_NOTIFY_SELECT_CHECKED:
				{
					IMOSelectable *pMOSelectable = dynamic_cast<IMOSelectable*>( FindByAI(reinterpret_cast<IRefCount*>(pObjects[i].nParam)) );
					if ( pMOSelectable && pMOSelectable->IsSelected() )
						Select( pMO );
				}
				break;
			case ACTION_SET_SELECTION_GROUP:
				{
					IMOSquad *pMOToCheck = dynamic_cast<IMOSquad*>( FindByAI(reinterpret_cast<IRefCount*>(pAILogic->GetObjByUniqueID(pObjects[i].nParam))) );
					int nSelGroup = -1;
					bool isSelected = false;
					if ( pMOToCheck )
					{
						nSelGroup = pMOToCheck->GetSelectionGroupID();							
						isSelected = pMOToCheck->IsSelected();
						const int nNumPassangers = pMOToCheck->GetPassangers( 0 );
						if ( nNumPassangers > 0 )
						{
							std::vector<IMOUnit*> vMOUnit( nNumPassangers );
							vMOUnit.resize( nNumPassangers );
							pMOToCheck->GetPassangers( &(vMOUnit[0]) );
							for ( std::vector<IMOUnit*>::iterator it = vMOUnit.begin(); it != vMOUnit.end(); ++it )
							{
								isSelected = isSelected || (*it)->IsSelected();
								RemoveFromSelectionGroup( *it );
							}
						}
					}
					else
					{
						IMOSelectable *pMOTemp = dynamic_cast<IMOSelectable*>( FindByAI(reinterpret_cast<IRefCount*>(pAILogic->GetObjByUniqueID(pObjects[i].nParam))) );
						if ( pMOTemp )
						{
							nSelGroup = pMOTemp->nSelectionGroupID;
							isSelected = pMOTemp->IsSelected();
						}
					}
					IMOSquad *pMOUnitToGroup = dynamic_cast<IMOSquad*>(pMO);
					if ( pMOUnitToGroup )
					{
						const int nNumPassangers = pMOUnitToGroup->GetPassangers( 0 );
						if ( nNumPassangers > 0 )
						{
							std::vector<IMOUnit*> vMOUnit( nNumPassangers );
							vMOUnit.resize( nNumPassangers );
							pMOUnitToGroup->GetPassangers( &(vMOUnit[0]) );
							for ( std::vector<IMOUnit*>::iterator it = vMOUnit.begin(); it != vMOUnit.end(); ++it )
							{
								AddUnitToSelectionGroup( *it, nSelGroup );
								if ( isSelected )
									Select( *it );
							}
						}
					}
					else
					{
						IMOUnit *pMOTemp = dynamic_cast<IMOUnit*>(pMO);
						if ( pMOTemp )
						{
							AddUnitToSelectionGroup( pMOTemp, nSelGroup );
							if ( isSelected )
								Select( pMOTemp );
						}
					}
				}
				break;
			case ACTION_NOTIFY_SELECTABLE_CHANGED:
				if ( pObjects[i].nParam == 0 ) 
					ResetSelection( pMO );
				break;
		}
		if ( static_cast<IMOSelectable*>(pMO)->AIUpdateActions(pObjects[i], currTime, pVOB, pScene, pAckManager ) != 0 )
			AddUpdatableUnit( static_cast<IMOUnit*>(pMO) );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SUnitBaseRPGStats::SAnimDesc* GetAnimationByType( int nType, const SUnitBaseRPGStats *pStats )
{
	if ( (nType >= pStats->animdescs.size()) || pStats->animdescs[nType].empty() )
		return 0;
	return &( pStats->animdescs[nType][ rand() % pStats->animdescs[nType].size() ] );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateShots( const NTimer::STime &currTime )
{
	// mechanical unit shots
	{
		SAINotifyMechShot *pObjects = 0;
		int nNumObjects = 0;
		pAILogic->UpdateShots( &pObjects, &nNumObjects );
		for ( int i=0; i<nNumObjects; ++i )
		{
			if ( SMapObject *pMO = FindByAI(pObjects[i].pObj) )
				static_cast<IMOContainer*>(pMO)->AIUpdateShot( pObjects[i], currTime, pVOB, pScene );
		}
	}
	// infantry unit shots
	{
		SAINotifyInfantryShot *pObjects = 0;
		int nNumObjects = 0;
		pAILogic->UpdateShots( &pObjects, &nNumObjects );
		for ( int i=0; i<nNumObjects; ++i )
		{
			if ( SMapObject *pMO = FindByAI(pObjects[i].pObj) )
				static_cast<IMOContainer*>(pMO)->AIUpdateShot( pObjects[i], currTime, pVOB, pScene );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateAiming( const NTimer::STime &currTime )
{
	SAINotifyTurretTurn *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->UpdateTurretTurn( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		if ( pObjects[i].nModelPart != -1 )
		{
			if ( SMapObject *pMO = FindByAI(pObjects[i].pObj) )
			{
				if ( IMeshAnimation *pAnim = static_cast<IMeshAnimation*>(static_cast_ptr<IObjVisObj*>(pMO->pVisObj)->GetAnimation()) )
				{
					const float fAngle = float( pObjects[i].wAngle ) / 65536.0f * FP_2PI;
					const NTimer::STime timeStart = currTime, timeEnd = pObjects[i].endTime;
					// for all model parts, packed in the 'nModelPart'
					for ( int j = 0; j != 4; ++j )
					{
						const int nModelPart = ( DWORD( pObjects[i].nModelPart ) >> (j*8) ) & 0x000000ff;
						if ( nModelPart != 0xff )
							pAnim->AddProceduralNode( nModelPart, currTime, timeStart, timeEnd, fAngle );
					}
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateDeadUnits( const NTimer::STime &currTime )
{
	SAINotifyDeadAtAll *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->GetDeadUnits( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		IMOUnit *pUnit = static_cast<IMOUnit*>( FindByAI(pObjects[i].pObj) );

		if ( pUnit == 0 )
			continue;
		// remove from selection & selection group
		RemoveFromSelectionGroup( pUnit );
		ResetSelection( pUnit );
		// remove from squad
		pUnit->SetSquad( 0 );
		// remove all effectors
		if ( pUnit->pDesc->eVisType == SGVOT_MESH )
			static_cast_ptr<IMeshVisObj*>(pUnit->pVisObj)->RemoveEffector( -1, -1 );

		pUnit->RemoveSounds( pScene );
		
		if ( SMapObject *pContainer = GetContainer(pUnit) )
		{
			if ( static_cast<IMOUnit*>(pUnit)->GetContainer() )
				static_cast<IMOContainer*>(pContainer)->Load( static_cast<IMOUnit*>(pUnit), false );
			RemoveFromContainer( pUnit );
			RemoveFromScene( pUnit );
		}
		else
		{
			CLinksMap::iterator pos = inContainer.find( pUnit->pAIObj );
			if ( pos != inContainer.end() )		// remove from links
			{
				RemoveFromScene( pUnit );
				inContainer.erase( pos );
			}
			else
			{
				pUnit->pVisObj->Update( currTime, true );
				static_cast_ptr<IObjVisObj*>(pUnit->pVisObj)->SetPriority( 110 );	// the same as for craters
				pScene->TransferToGraveyard( pUnit->pVisObj );
			}
		}
		if ( pObjects[i].bRot == false )
			RemoveAIObj( pUnit, true );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateDeadProjectiles( const NTimer::STime &currTime )
{
	IRefCount **ppObjects = 0;
	int nNumObjects = 0;
	pAILogic->GetDeadProjectiles( &ppObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		if ( SMapObject *pMO = FindByAI(ppObjects[i]) )
			RemoveMapObj( pMO );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateHits( const NTimer::STime &currTime )
{
	SAINotifyHitInfo *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->UpdateHits( &pObjects, &nNumObjects );
	if ( nNumObjects > 0 )
	{
		for ( int i = 0; i != nNumObjects; ++i )
		{
			if ( pObjects[i].pWeapon == 0 )
				continue;
			const SWeaponRPGStats::SShell &shell = pObjects[i].pWeapon->shells[pObjects[i].wShell];
			// coords
			CVec3 vPos = VNULL3;
			if ( pObjects[i].pVictim )			// to object
			{
				if ( SMapObject *pVictim = FindByAI( pObjects[i].pVictim ) ) // ordinal object
				{
					pVictim->AIUpdateHit( pObjects[i], currTime, pScene, pVOB );
					WORD wDir = 0;
					pVictim->GetPlacement( &vPos, &wDir );
				}
				else if ( SBridgeSpanObject *pSpan = FindSpanByAI(pObjects[i].pVictim) ) // bridge
				{
					pSpan->AIUpdateHit( pObjects[i], currTime, pScene, pVOB );
					WORD wDir;
					pSpan->GetPlacement( &vPos, &wDir );
				}
				else
				{
					NStr::DebugTrace( "Victim 0x%x (%s) for hit is not a valid map object\n", pObjects[i].pVictim, typeid(pObjects[i].pVictim).name() );
				}
			}
			else														// to ground
			{
				vPos = pObjects[i].explCoord;
				AI2Vis( &vPos );
				bool bNeedCrater = false;
				// effects (sounds and particles)
				const std::string *pEffectName = 0;
				switch ( pObjects[i].eHitType ) 
				{
					case SAINotifyHitInfo::EHT_GROUND:
						pEffectName = &shell.szEffectHitGround;
						bNeedCrater = true;
						break;
					case SAINotifyHitInfo::EHT_WATER:
						pEffectName = &shell.szEffectHitWater;
						break;
					case SAINotifyHitInfo::EHT_AIR:
						pEffectName = &shell.szEffectHitAir;
						break;
				}
				// effects
				if ( pEffectName ) 
					PlayEffect( *pEffectName, vPos, currTime, false, pScene, pVOB, 0, SFX_MIX_IF_TIME_EQUALS, SAM_ADD_N_FORGET, ESCT_COMBAT );
				// crater picture
				if ( bNeedCrater && shell.HasCraters() )
					SetCraterEffect( shell.GetRandomCrater(), nSeason, vPos, 110, pScene, pVOB );
				// flash
				if ( bNeedCrater && shell.flashExplosion.HasFlash() ) 
					SetFlashEffect( shell.flashExplosion, currTime, vPos, dwFlashExpColor, pScene, pVOB );
			}
			// add earthquake
			if ( (vPos != VNULL3) && (shell.fDetonationPower > 0) ) 
				pCamera->AddEarthquake( vPos, shell.fDetonationPower );
		}			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateAcknowledgemets( const NTimer::STime &currTime )
{
	{
		SAIAcknowledgment *pAcks = 0;
		int nNumObjs = 0;
		pAILogic->UpdateAcknowledgments( &pAcks, &nNumObjs );
		for ( int i = 0; i < nNumObjs; ++i )
		{
			SMapObject *pMO = FindByAI( pAcks[i].pObj );
			if ( pMO )
			{
				IMOUnit * pUnit = static_cast<IMOUnit*>(pMO);
				pUnit->AIUpdateAcknowledgement( pAcks[i].eAck, pAckManager, pAcks[i].nSet );
			}
		}
	}
	
	{
		SAIBoredAcknowledgement *pBoredAcks = 0;
		int nNumObjs = 0;
		pAILogic->UpdateAcknowledgments( &pBoredAcks, &nNumObjs );
		for ( int i = 0; i < nNumObjs; ++i )
		{
			SMapObject *pMO = FindByAI( pBoredAcks[i].pObj );
			if ( pMO )
			{
				IMOUnit * pUnit = static_cast<IMOUnit*>(pMO);
				pUnit->AIUpdateBoredAcknowledgement( pBoredAcks[i], pAckManager );
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateFeedbacks( const NTimer::STime &currTime )
{
	SAIFeedBack *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->UpdateFeedbacks( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		switch ( pObjects[i].feedBackType ) 
		{
			case EFB_DRAW:
				pInput->AddMessage( SGameMessage(WCB_DRAW) );
				break;
			case EFB_WIN:
				pInput->AddMessage( SGameMessage(WCB_YOU_WIN) );
				break;
			case EFB_LOOSE:
				pInput->AddMessage( SGameMessage(WCB_YOU_LOOSE) );
				break;
			case EFB_SCOUT_ENABLED:				// enable scout
				pInput->AddMessage( SGameMessage(USER_ACTION_ENABLE_PLANE_SCOUT, 0) );
				break;
			case EFB_SCOUT_DISABLED:			// disable scouts
				pInput->AddMessage( SGameMessage(USER_ACTION_DISABLE_PLANE_SCOUT, pObjects[i].nParam) );
				break;
			case EFB_FIGHTERS_ENABLED:		// enable figters
				pInput->AddMessage( SGameMessage(USER_ACTION_ENABLE_PLANE_FIGHTER, 0) );
				break;
			case EFB_FIGHTERS_DISABLED:		// disable figters
				pInput->AddMessage( SGameMessage(USER_ACTION_DISABLE_PLANE_FIGHTER, pObjects[i].nParam) );
				break;
			case EFB_BOMBERS_ENABLED:			// enable bombers
				pInput->AddMessage( SGameMessage(USER_ACTION_ENABLE_PLANE_BOMBER, 0) );
				break;
			case EFB_BOMBERS_DISABLED:		// disbale bombers
				pInput->AddMessage( SGameMessage(USER_ACTION_DISABLE_PLANE_BOMBER, pObjects[i].nParam) );
				break;
			case EFB_PARADROPS_ENABLED:		// enable paradropers
				pInput->AddMessage( SGameMessage(USER_ACTION_ENABLE_PLANE_PARADROPER, 0) );
				break;
			case EFB_PARADROPERS_DISABLED:// disable paradropers
				pInput->AddMessage( SGameMessage(USER_ACTION_DISABLE_PLANE_PARADROPER, pObjects[i].nParam) );
				break;
			case EFB_SHTURMOVIKS_ENABLED:	// enable gunplanes
				pInput->AddMessage( SGameMessage(USER_ACTION_ENABLE_PLANE_GUNPLANE, 0) );
				break;
			case EFB_SHTURMOVIKS_DISABLED:// disable gunplanes
				pInput->AddMessage( SGameMessage(USER_ACTION_DISABLE_PLANE_GUNPLANE, pObjects[i].nParam) );
				break;
			case EFB_AVIA_DISABLED:
				pInput->AddMessage( SGameMessage(USER_ACTION_DISABLE_PLANES, pObjects[i].nParam) );
				break;
			case EFB_OBJECTIVE_CHANGED:
				ReportObjectiveStateChanged( (pObjects[i].nParam >> 8) & 0xff, pObjects[i].nParam & 0xff );
				break;
			case EFB_YOU_LOST_STORAGE:
				break;
			case 	EFB_UPDATE_TEAM_F_L_AGS:
				pInput->AddMessage( SGameMessage(MC_UPDATE_TEAM_F_L_AGS, pObjects[i].nParam) );
				break;
			case EFB_UPDATE_TEAM_F_R_AGS:
				pInput->AddMessage( SGameMessage(MC_UPDATE_TEAM_F_R_AGS, pObjects[i].nParam) );
				break;
			case EFB_UPDATE_TIME_BEFORE_CAPTURE:
				pInput->AddMessage( SGameMessage(MC_UPDATE_TIME_BEFORE_CAPTURE, pObjects[i].nParam) );
				break;

			case EFB_REINFORCEMENT_ARRIVED:
				ReportReinforcementArrived();
				break;

			case EFB_REINFORCEMENT_CENTER:
				pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_REINFORCEMENT_ARRIVAL, pObjects[i].nParam) );
				break;

			case EFB_PLACE_MARKER:
				pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_PLACE_MARKER, pObjects[i].nParam) );
				break;

			case EFB_SCENARIO_UNIT_DEAD:
				pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_SCENARIOUNIT_DEAD, pObjects[i].nParam) );
				break;

			case EFB_TROOPS_PASSED:
				pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_UNITS_PASSED, pObjects[i].nParam) );
				break;

			case EFB_SNIPER_DEAD:
				pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_SNIPER_DEAD, pObjects[i].nParam) );
				break;

			case EFB_AAGUN_FIRED:
				if ( bAADetectedFlag )
					pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_AA_NEWDETECTED, pObjects[i].nParam) );					
				else
				{
					pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_AA_STARTED, pObjects[i].nParam) );
					bAADetectedFlag = true;
				}
				break;

			case EFB_AVIA_ENABLED:
				pInput->AddMessage( SGameMessage(USER_ACTION_ENABLE_PLANES, 0) );
				pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_AVIATION_READY, 0) );
				break;

			case EFB_ENEMY_STARTED_ANTIARTILLERY:
				pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_ENEMY_ANTIARTILLERY, pObjects[i].nParam ) );
				break;

			case EFB_ENEMY_AVIATION_CALLED:
				pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_ENEMY_AVIATION, pObjects[i].nParam ) );
				break;

			case EFB_BAD_WEATER:
				{
					const bool bStart = pObjects[i].nParam;
					GetSingleton<IScene>()->SwitchWeather( bStart );
					if ( bStart )
						pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_BAD_WEATHER) );

				}
				break;
				
			case EFB_ASK_FOR_WARFOG:
				AIUpdateWarFogLocal();
				
				break;
			case EFB_AVIA_KILLED:
				pInput->AddMessage( SGameMessage(MC_VISUALIZE_FEEDBACK_AVIATION_KILLED, pObjects[i].nParam ) );
				
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateEntrances( const NTimer::STime &currTime )
{
	SAINotifyEntranceState *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->UpdateEntranceStates( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		SMapObject *pInf = FindByAI( pObjects[i].pInfantry );
		if ( pInf == 0 ) 
			continue;
		SMapObject *pMO = FindByAI( pObjects[i].pTarget );
		// pMO == 0 in the case of entrenchment!!!
//		NI_ASSERT_SLOW_TF( pInf != 0, "Can't find unit to enter/leave", return );
		if ( pObjects[i].bEnter )
		{
			// add to container
			if ( pMO )
				static_cast<IMOContainer*>(pMO)->Load( static_cast<IMOUnit*>(pInf), true );
			// reset selection from this object
			ResetSelection( pInf );
			// add to container links
			inContainer[pObjects[i].pInfantry] = pObjects[i].pTarget;
		}
		else
		{
			// remove from container
			if ( pMO )
				static_cast<IMOContainer*>(pMO)->Load( static_cast<IMOUnit*>(pInf), false );
			else
			{
				IMOUnit *pUnit = checked_cast<IMOUnit*>( pInf );
				IObjVisObj *pVO = static_cast_ptr<IObjVisObj*>( pUnit->pVisObj );
				const bool bSelected = pUnit->GetSquad() ? pUnit->GetSquad()->IsSelected() : pUnit->IsSelected();
				pVO->Select( bSelected ? SGVOSS_SELECTED : SGVOSS_UNSELECTED );
				if ( ISceneIcon *pIcon = pVO->GetIcon(ICON_HP_BAR) )
				{
					if ( (pUnit->fHP < 1.0f) || bSelected )
						pIcon->Enable( true );
					else
						pIcon->Enable( false );
				}
			}
			// remove from container links
			inContainer.erase( pObjects[i].pInfantry );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateEntrenchments( const NTimer::STime &currTime )
{
	SSegment2Trench *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->GetEntrenchments( &pObjects, &nNumObjects );
	for ( int i=0; i<nNumObjects; ++i )
	{
		SMapObject *pMO = FindByAI( pObjects[i].pSegment );
		entrenchments.AddSegment( pObjects[i].pEntrenchment, pMO );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AddToSquad( IRefCount *pAISquad, IMOUnit *pUnit )
{
	if ( IMOSquad *pSquad = static_cast<IMOSquad*>(FindByAI(pAISquad)) )
	{
		pSquad->Load( pUnit, true );
		if ( pSquad->IsSelected() ) 
			Select( pUnit );
		AddUnitToSelectionGroup( pUnit, pSquad->GetSelectionGroupID() );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateSquads( const NTimer::STime &currTime )
{
	SSoldier2Formation *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->GetFormations( &pObjects, &nNumObjects );
	for ( int i = 0; i != nNumObjects; ++i )
	{
		if ( IMOUnit *pUnit = static_cast<IMOUnit*>(FindByAI(pObjects[i].pSoldier)) ) 
			AddToSquad( pObjects[i].pFormation, pUnit );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateBridges( const NTimer::STime &currTime )
{
	// update spans
	{
		SNewUnitInfo *pObjects = 0;
		int nNumObjects = 0;
		pAILogic->GetNewBridgeSpans( &pObjects, &nNumObjects );
		for ( int i = 0; i != nNumObjects; ++i )
		{
			const SNewUnitInfo &info = pObjects[i];
			NI_ASSERT_TF( info.dbID != 0xffff, "object with undefined type has come from AI", continue );
			// create unit and add to world
			SBridgeSpanObject *pSpan = AddSpanToWorld( info.pObj, info.dbID, info.nFrameIndex, info.fHitPoints );
			// set placement for span
			CVec3 vPos;
			AI2Vis( &vPos, info.center.x, info.center.y, info.z );
			pSpan->SetPlacement( vPos, info.dir );
			//pSpan->SetDiplomacy( info.eDipl );
			// and, at rest, add object to scene
			AddToScene( pSpan );
		}
	}
	// update bridges
	{
		while ( 1 )
		{
			IRefCount **ppObjects = 0;
			int nNumObjects = 0;
			pAILogic->GetNewBridge( &ppObjects, &nNumObjects );
			if ( nNumObjects == 0 ) 
				break;
			for ( int i = 0; i != nNumObjects; ++i )
			{
				SBridgeSpanObject *pSpan = FindSpanByAI( ppObjects[i] );
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateRevealCircles( const NTimer::STime &currTime )
{
	/*
	CCircle *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->GetRevealCircles( &pObjects, &nNumObjects );
	for ( int i = 0; i != nNumObjects; ++i )
	{
		CVec3 vCenter;
		AI2Vis( &vCenter, pObjects[i].center.x, pObjects[i].center.y, 0 );
		const float fRadius = pObjects[i].r * fAITileXCoeff;
		//
		pScene->AddCircle( vCenter, fRadius, currTime, fRadius*4.5f );
	}
	*/
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateAreas( const NTimer::STime &currTime )
{
	SShootAreas *pObjects = 0;
	int nNumObjects = 0;
	pAILogic->UpdateShootAreas( &pObjects, &nNumObjects );
	pScene->SetAreas( pObjects, nNumObjects );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::AIUpdateCombatSituationInfo( const NTimer::STime &currTime )
{
	if ( pAILogic->IsCombatSituation() )
		pScene->CombatNotify();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** manipulations
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::MoveObject( IVisObj *pObj, const CVec3 &vPos )
{
	NTimer::STime currTime = pTimer->GetGameTime();
	//
	SGetVisObjesVisitor visitor;
	if ( SMapObject *pMO = FindByVis(pObj) )
	{
		pMO->Visit( &visitor );
		for ( std::list<SGetVisObjesVisitor::SVisObjDesc>::iterator it = visitor.objects.begin(); it != visitor.objects.end(); ++it )
		{
			pScene->MoveObject( it->pVisObj, vPos );
			it->pVisObj->Update( currTime, true );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::ShowIcons( int nID, bool bShow )
{
	if ( nID != -1 ) 
	{
		//showicons[nID] = bShow;
		for ( CMapObjectsMap::iterator it = visobjects.begin(); it != visobjects.end(); ++it )
		{
			if ( it->second && it->second->pDesc && it->second->pDesc->IsObj() )
			{
				ISceneIcon *pIcon = static_cast<IObjVisObj*>( it->second->pVisObj.GetPtr() )->GetIcon( nID );
				if ( pIcon )
					pIcon->Enable( bShow );
			}
		}
	}
	else
	{
		for ( CMapObjectsMap::iterator it = visobjects.begin(); it != visobjects.end(); ++it )
		{
			if ( it->second && it->second->pDesc && it->second->pDesc->IsObj() )
			{
				for ( int i = 0; i < ICON_NUM_ICONS; ++i )
				{
					if ( ISceneIcon *pIcon = static_cast<IObjVisObj*>( it->second->pVisObj.GetPtr() )->GetIcon(i) ) 
						pIcon->Enable( bShow );
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** pick functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SBridgeSpanObject* CWorldBase::PickSpan( const CVec2 &vPos )
{
	if ( pScene == 0 )
		return 0;
	//
	std::pair<IVisObj*, CVec2> *pObjects = 0;
	int nNumObjects = 0;
	pScene->Pick( vPos, &pObjects, &nNumObjects, SGVOGT_UNKNOWN );
	for ( int i = 0; i != nNumObjects; ++i )
	{
		SBridgeSpanObject *pSpan = FindSpanByVis( pObjects[i].first );
		if ( pSpan )
			return pSpan;
	}
	//
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** misc
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::SetSeason( int _nSeason ) 
{ 
	nSeason = _nSeason; 
	GetSingleton<IScene>()->SetSeason( _nSeason );	
	SetGlobalVar( "World.Season", GetSeasonName() );
	//
	dwFlashFireColor = GetGlobalVar( (std::string("Scene.Colors.") + GetSeasonName() + ".FlashFire.Color").c_str(), int(0xffffffff) );
	dwFlashExpColor = GetGlobalVar( (std::string("Scene.Colors.") + GetSeasonName() + ".FlashExplode.Color").c_str(), int(0xffffffff) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CWorldBase::GetSeasonName() const
{
	return ::GetSeasonName( nSeason );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::ReportReinforcementArrived()
{
	const DWORD dwColor = GetGlobalVar( (std::string("Scene.Colors.") + GetSeasonName() + ".Text.Information.Color").c_str(), int(0xffffffff) );
	if ( IText *pText = GetSingleton<ITextManager>()->GetString("reinforcement_arrived") ) 
	{
		GetSingleton<IConsoleBuffer>()->Write( CONSOLE_STREAM_CHAT, pText->GetString(), dwColor );
		if ( pScene ) 
			pScene->AddSound( "sounds\\reports\\information", VNULL3, SFX_INTERFACE, SAM_ADD_N_FORGET );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorldBase::UpdateAllUnits()
{
	IVisObjBuilder *pVOB = GetSingleton<IVisObjBuilder>();
	for ( CMapObjectsMap::iterator it = visobjects.begin(); it != visobjects.end(); ++it )
	{
		if ( IMOUnit *pUnit = dynamic_cast_ptr<IMOUnit*>(it->second) )
			pUnit->ChangeWithBlood( pVOB );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
