#ifndef __MOBRIDGE_H__
#define __MOBRIDGE_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MapObject.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CMOBridgeSpan : public CTRefCount<SBridgeSpanObject>
{
	OBJECT_SERVICE_METHODS( CMOBridgeSpan );
	DECLARE_SERIALIZE;
	//
	int nSpanType;												// 0 - begin, 1 - center, 2 - end
	//
	const SBridgeRPGStats::SSpan& GetSpanStats( const int nDamageState = 0 ) const;
	int GetSpanStatsIndex( const int nDamageState = 0 ) const;
	void UpdateModelWithHP( const float fNewHP, const NTimer::STime &currTime, IVisObjBuilder *pVOB ) const;
public:	
	virtual bool STDCALL Create( IRefCount *pAIObj, const SGDBObjectDesc *pDesc, int nSeason, int nFrameIndex, float fHP, interface IVisObjBuilder *pVOB, IObjectsDB *pGDB );
	// placement
	virtual void STDCALL SetPlacement( const CVec3 &vPos, const WORD &wDir );
	virtual void STDCALL GetPlacement( CVec3 *pvPos, WORD *pwDir );
	// stats functions
	virtual const SGDBObjectDesc* STDCALL GetDesc() const;
	virtual const SHPObjectRPGStats* STDCALL GetRPG() const;
	// AI object retrieving
	virtual IRefCount* STDCALL GetAIObj();
	virtual IRefCount* STDCALL GetParentAIObj();
	//
	virtual bool STDCALL CanSelect() const;
	// get status for mission status bar
	virtual void STDCALL GetStatus( struct SMissionStatusObject *pStatus ) const;
	// get actions, which this object can perform or actions, thi object can be acted with
	virtual void STDCALL GetActions( CUserActions *pActions, EActionsType eActions ) const;
	// common updates
	virtual void STDCALL AIUpdatePlacement( const struct SAINotifyPlacement &placement, const NTimer::STime &currTime, IScene *pScene );
	virtual bool STDCALL AIUpdateRPGStats( const struct SAINotifyRPGStats &stats, IVisObjBuilder *pVOB, IScene * pScene );
	virtual void STDCALL AIUpdateHit( const struct SAINotifyHitInfo &hit, const NTimer::STime &currTime, IScene *pScene, IVisObjBuilder *pVOB );
	virtual int STDCALL AIUpdateActions( const struct SAINotifyAction &action, const NTimer::STime &currTime, IVisObjBuilder *pVOB, IScene *pScene, interface IClientAckManager *pAckManager ) { return 0; }
	// visiting
	virtual void STDCALL Visit( IMapObjVisitor *pVisitor );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __MOBRIDGE_H__
