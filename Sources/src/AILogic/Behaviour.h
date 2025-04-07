#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCommonUnit;
class CAIUnit;
class CBasicGun;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// выбор наилучшего воздушного юнита ( для легких зениток ) - для стрельбы сопро-
//водительным огнем
class CShootEstimatorLighAA
{
	BYTE party;
	
	CPtr<CCommonUnit> pUnit;
	CPtr<CAIUnit> pResult;
	CPtr<CBasicGun> pGun;
	float fWorstDamage;
	NTimer::STime bestTime;
	float fMinDistance;
	bool bCanShootNow;

public:
	CShootEstimatorLighAA() 
	: fWorstDamage( -1 ),
		bestTime( 100000 ),
		fMinDistance( 1e10 ),
		bCanShootNow( false ) { }

	void Init( class CCommonUnit *pUnit );
	// выбрать оптимальный юнит для данного gun, приоценки времени, чтобы пристрелить, 
	// учитывается только время поворота gun до этого юнита
	void Init( class CCommonUnit *pUnit, CBasicGun *pGun );
	void AddUnit( class CAIUnit *pTarget );
	class CAIUnit* GetBestUnit();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CStandartBehaviour
{
	DECLARE_SERIALIZE;
	//
	class CAIUnit* LookForTargetInFireRange( class CCommonUnit *pUnit );

	NTimer::STime camouflateTime;

	NTimer::STime underFireAnalyzeTime;
	NTimer::STime lastTimeOfRotate;
	NTimer::STime fleeTraceEnemyTime;
	int nLastSign;

	// отслеживать врага, если нет никого, в кого возможно стрелять и нельзя двигаться, и есть turret
	bool TryToTraceEnemy( class CAIUnit *pUnit );
public:
	CStandartBehaviour() : camouflateTime( 0 ), underFireAnalyzeTime( 0 ), nLastSign( 1 ), lastTimeOfRotate( -1 ), fleeTraceEnemyTime( 0 ) { }

	void ResetTime( class CCommonUnit *pUnit );
	void UponFire( class CCommonUnit *pUnit, class CAIUnit *pWho, class CAICommand *pCommand );

	void AnalyzeUnderFire( class CAIUnit *pUnit );
	
//	void StartCamouflating();
//	void AnalyzeCamouflage( class CAIUnit *pUnit );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __BEHAVIOUR_H__
