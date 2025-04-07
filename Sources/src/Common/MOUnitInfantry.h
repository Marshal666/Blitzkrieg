#ifndef __MOUNITINFANTRY_H__
#define __MOUNITINFANTRY_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MOUnit.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CMOUnitInfantry : public CMOUnit
{
	OBJECT_SERVICE_METHODS( CMOUnitInfantry );
	DECLARE_SERIALIZE;
	//
	CPtr<IMOSquad> pSquad;								// squad, this soldier in
	int nDeadCounter;											// unit dead counter
	CVec3 vSunDir;
	float fTraceProbabilityCoeff;
	float fTraceSpeedCoeff;
	//
	ISpriteVisObj* GetVisObj() { return static_cast_ptr<ISpriteVisObj*>( pVisObj ); }
	ISpriteAnimation* GetAnim() { return static_cast<ISpriteAnimation*>( GetVisObj()->GetAnimation() ); }
	const SInfantryRPGStats* GetRPGStats() const { return static_cast_gdb<const SInfantryRPGStats*>( pRPG ); }
	//
	virtual const CVec3 GetIconAddValue() const { return CVec3( 0, 0, 5 ); }
	void UpdateHPBarVisibility( const float fHP );
	virtual void MakeVisible( const bool bVisible );
	bool ChangeModeWithBlood( const std::string &szModelName );
	void UpdateVisibility();
public:
	CMOUnitInfantry();
	//
	virtual bool STDCALL Create( IRefCount *pAIObj, const SGDBObjectDesc *pDesc, int nSeason, int nFrameIndex, float fHP, interface IVisObjBuilder *pVOB, IObjectsDB *pGDB );
	// get status for mission status bar
	virtual void STDCALL GetStatus( struct SMissionStatusObject *pStatus ) const;
	//
	virtual void STDCALL SetSquad( interface IMOSquad *_pSquad );
	virtual IMOSquad* STDCALL GetSquad() { return pSquad; }
	// change selection state for this object
	virtual void STDCALL Select( ISelector *pSelector, bool bSelect, bool bSelectSuper );
	//
	virtual void STDCALL SetContainer( IMOContainer *_pContainer );
	//
	virtual bool STDCALL Load( interface IMOUnit *pMO, bool bEnter ) { return false; }
	virtual void STDCALL UpdatePassangers() {  }
	// get all passangers from container. return number of passangers. if pBuffer == 0, only returns number of passangers
	virtual int STDCALL GetPassangers( IMOUnit **pBuffer, const bool bCanSelectOnly ) const { return 0; }
	// get free places
	virtual int STDCALL GetFreePlaces() const { return 0; }
	// get actions, which this object can perform or actions, thi object can be acted with
	virtual void STDCALL GetActions( CUserActions *pActions, EActionsType eActions ) const;
	// common updates
	virtual void STDCALL AIUpdatePlacement( const struct SAINotifyPlacement &placement, const NTimer::STime &currTime, IScene *pScene );
	virtual bool STDCALL AIUpdateRPGStats( const SAINotifyRPGStats &stats, IVisObjBuilder *pVOB, IScene * pScene );
	virtual void STDCALL AIUpdateHit( const struct SAINotifyHitInfo &hit, const NTimer::STime &currTime, IScene *pScene, IVisObjBuilder *pVOB );
	//
	virtual int STDCALL AIUpdateActions( const struct SAINotifyAction &action, const NTimer::STime &currTime, IVisObjBuilder *pVOB, IScene *pScene, interface IClientAckManager *pAckManager );
	virtual IMapObj* STDCALL AIUpdateFireWithProjectile( const SAINotifyNewProjectile &projectile, const NTimer::STime &currTime, interface IVisObjBuilder *pVOB );
	virtual void STDCALL AIUpdateShot( const struct SAINotifyBaseShot &shot, const NTimer::STime &currTime, IVisObjBuilder *pVOB, IScene *pScene );
	// visiting
	virtual void STDCALL Visit( IMapObjVisitor *pVisitor );
	// change look with blood settings
	virtual bool STDCALL ChangeWithBlood( IVisObjBuilder *pVOB );
	virtual void STDCALL SetHPSimpleBar( bool bSimple = true );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __MOUNITINFANTRY_H__
