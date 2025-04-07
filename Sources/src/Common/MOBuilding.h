#ifndef __MOBUILDING_H__
#define __MOBUILDING_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MapObject.h"
#include "..\Anim\Animation.h"
#include "..\Main\TextSystem.h"
#include "Passangers.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CMOBuilding : public CTRefCount<IMOContainer>
{
	OBJECT_SERVICE_METHODS( CMOBuilding );
	DECLARE_SERIALIZE;
	//
	CPassangersList passangers;
	mutable CPtr<IText> pLocalName;				// localized name of this building (ZB "������� ������")
	int nSeason;													// season
	CPtr<IVisObj> pGarbage;								// garbage around damaged or destroyed building
	float fTraceSpeedCoeff;
	float fTraceProbabilityCoeff;
	//
	ISpriteVisObj* GetVisObj() { return static_cast_ptr<ISpriteVisObj*>( pVisObj ); }
	ISpriteAnimation* GetAnim() { return static_cast<ISpriteAnimation*>( GetVisObj()->GetAnimation() ); }
	const SBuildingRPGStats* GetRPGStats() const { return static_cast_gdb<const SBuildingRPGStats*>( pRPG ); }
	//
	void SetIcon( const int nType, IVisObjBuilder *pVOB );
	void RemoveIcon( const int nType );
	//
	int GetNumTotalSlots() const { return GetRPGStats()->nMedicalSlots + GetRPGStats()->nRestSlots + GetRPGStats()->slots.size(); }
	int GetNumFreeSlots() const { return GetNumTotalSlots() - passangers.size(); }
	bool CanEnterOrBoard() const;
	//
	bool UpdateModelWithHP( const float fNewHP, IVisObjBuilder *pVOB, const bool bForced = false );
	void AddEffectsAtDamagePoints( const int nDamageState, const NTimer::STime &currTime, const NTimer::STime &timePassed, IVisObjBuilder *pVOB, IScene *pScene );
	//
	IText* GetLocalName() const
	{
		if ( pLocalName == 0 )
			pLocalName = ::GetLocalName( pDesc );
		return pLocalName;
	}
	//
	bool IsDOT() const { return GetRPGStats()->eType == SBuildingRPGStats::TYPE_DOT; }
	//
	virtual ~CMOBuilding();
	
	void UpdateGunTraces( const CVec3 &vStart, const CVec3 &vEnd, float fSpeed, NTimer::STime nCurrTime, IScene *pScene );
public:
	virtual bool STDCALL Create( IRefCount *pAIObj, const SGDBObjectDesc *pDesc, int nSeason, int nFrameIndex, float fHP, interface IVisObjBuilder *pVOB, IObjectsDB *pGDB );
	// placement
	virtual void STDCALL SetPlacement( const CVec3 &vPos, const WORD &wDir );
	virtual void STDCALL GetPlacement( CVec3 *pvPos, WORD *pwDir );
	// stats functions
	virtual const SGDBObjectDesc* STDCALL GetDesc() const { return pDesc; }
	virtual const SHPObjectRPGStats* STDCALL GetRPG() const { return pRPG;  }
	// AI object retrieving
	virtual IRefCount* STDCALL GetAIObj() { return pAIObj; }
	virtual IRefCount* STDCALL GetParentAIObj() { return 0; }
	// get status for mission status bar
	virtual void STDCALL GetStatus( struct SMissionStatusObject *pStatus ) const;
	// check, is this object selected?
	virtual bool STDCALL IsSelected() const { return pVisObj->GetSelectionState() == SGVOSS_SELECTED; }
	// change selection state for this object
	virtual void STDCALL Select( ISelector *pSelector, bool bSelect, bool bSelectSuper );
	virtual void STDCALL Select( int nSelectionState ) { pVisObj->Select( EVisObjSelectionState(nSelectionState) ); }
	//
	virtual bool STDCALL Load( interface IMOUnit *pMO, bool bEnter );
	// show icons of the passangers
	virtual void STDCALL UpdatePassangers();
	// get all passangers from container. return number of passangers. if pBuffer == 0, only returns number of passangers
	virtual int STDCALL GetPassangers( IMOUnit **pBuffer, const bool bCanSelectOnly ) const;
	// get free places
	virtual int STDCALL GetFreePlaces() const { return GetNumFreeSlots(); }
	// get actions, which this object can perform or actions, thi object can be acted with
	virtual void STDCALL GetActions( CUserActions *pActions, EActionsType eActions ) const;
	// common updates
	virtual int STDCALL AIUpdateActions( const struct SAINotifyAction &action, const NTimer::STime &currTime, IVisObjBuilder *pVOB, IScene *pScene, interface IClientAckManager *pAckManager );
	virtual void STDCALL AIUpdatePlacement( const SAINotifyPlacement &placement, const NTimer::STime &currTime, IScene *pScene );
	virtual bool STDCALL AIUpdateRPGStats( const SAINotifyRPGStats &stats, IVisObjBuilder *pVOB, IScene * pScene );
	virtual bool STDCALL AIUpdateDiplomacy( const SAINotifyDiplomacy &diplomacy );
	virtual void STDCALL AIUpdateHit( const struct SAINotifyHitInfo &hit, const NTimer::STime &currTime, IScene *pScene, IVisObjBuilder *pVOB );
	// firing... (from container of by himself)
	virtual void STDCALL AIUpdateShot( const struct SAINotifyBaseShot &shot, const NTimer::STime &currTime, IVisObjBuilder *pVOB, IScene *pScene );
	// visiting
	virtual void STDCALL Visit( IMapObjVisitor *pVisitor );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __MOBUILDING_H__
