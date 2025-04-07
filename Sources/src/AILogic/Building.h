#ifndef __BUILDING_H__
#define __BUILDING_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StaticObject.h"
#include "Heap.h"
#include "StormableObject.h"
#include "RotatingFireplacesObject.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSoldier;
class CCommonUnit;
class CTurret;
class CUnitGuns;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************************************
//*														CBuilding															*
//*******************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBuilding : public CGivenPassabilityStObject, public ILoadableObject, public CStormableObject
{
	DECLARE_SERIALIZE;

	// начало состояния, когда все в стрелк. ячейках отдыхают
	NTimer::STime startOfRest;
	// тревога
	bool bAlarm;
	
	struct SHealthySort{ bool operator()( const CPtr<CSoldier> &a, const CPtr<CSoldier> &b ); };
	struct SIllSort{ bool operator()( const CPtr<CSoldier> &a, const CPtr<CSoldier> &b ); };

	struct SSwapAction
	{
		void operator()( CPtr<CSoldier> pSoldier1, CPtr<CSoldier> pSoldier2, const int nSoldier1Index, const int nSoldier2Index );
	};

	CHeap< CPtr<CSoldier>, SHealthySort, SSwapAction > medical;
	CHeap< CPtr<CSoldier>, SIllSort, SSwapAction > fire;
	CHeap< CPtr<CSoldier>, SIllSort, SSwapAction > rest;
	int nOveralPlaces;

	int nIterator;

	CCommonUnit *pLockingUnit;

	NTimer::STime nextSegmTime;
	
	std::vector< CObj<CTurret> > turrets;
	std::vector< CPtr<CUnitGuns> > guns;

	NTimer::STime lastDistibution;

	// для каждой из сторон 3 наблюдательных fireplace
	CArray2D<int> observationPlaces;
	struct SSideInfo
	{
		// количество fireSlots на стороне
		int nFireSlots;
		// количество observation points на стороне
		int nObservationPoints;
		// количество солдат в observation points стороны
		int nSoldiersInObservationPoints;

		SSideInfo() : nFireSlots( 0 ), nObservationPoints( 0 ), nSoldiersInObservationPoints( 0 ) { }
	};
	std::vector<SSideInfo> sides;
	// по fire place - <номер точки << 2> | <сторона>
	std::vector<int> firePlace2Observation;
	// по fireplace - солдат в нём
	std::vector< CPtr<CSoldier> > firePlace2Soldier;
	int nLastFreeFireSoldierChoice;

	// player последнего из защитников, побывавшего в здании
	int nLastPlayer;

	int nScriptID;
	
	// должны ли юниты убегать из здания, когда у него останется мало здоровья
	bool bShouldEscape;
	// units escaped
	bool bEscaped;
	NTimer::STime timeOfDeath;
	
	std::vector<NTimer::STime> lastLeave;

	//
	bool IsIllInFire();
	bool IsIllInRest();

	void SwapFireMed();
	void SwapRestMed();

	const BYTE GetFreeFireSlot();

	// засунуть конкретного юнита в слот
	void PopFromFire();

	// есть свободный слот, засунуть туда желающего
	void SeatSoldierToMedicalSlot();
	// есть свободный слот, засунуть туда добровольца
	void SeatSoldierToFireSlot();

	// перераспределить солдатов (полечить/выгнать из medical places )
	void DistributeAll();
	// перераспределить не стреляющих солдатов ( полечить/выгнать из medical places )
	void DistributeNonFires();

	void SetFiringUnitProperties( class CSoldier *pUnit, const int nSlot, const int nIndex );
	void DistributeFiringSoldiers();

	void InitObservationPlaces();

	//
	void DelSoldierFromFirePlace( CSoldier *pSoldier );
	void DelSoldierFromMedicalPlace( CSoldier *pSoldier );
	void DelSoldierFromRestPlace( CSoldier *pSoldier );

	void PushSoldierToFirePlace( CSoldier *pUnit, const int nFirePlace );

	// положить pUnit в первый попавшийся fireplace
	void PushToFire( class CSoldier *pUnit );
	void PushToMedical( class CSoldier *pUnit );
	void PushToRest( class CSoldier *pUnit );

	// рассадить солдат в точки наблюдения
	void SetSoldiersToObservationPoints();
	// попробовать отдыхающего солдата pSoldier поставить в точку наблюдения; true - поставился, false - нет
	bool TryToPushRestSoldierToObservation( CSoldier *pSoldier );
	// попробовать солдата в стрелковой ячейке поставить в точку наблюдения; true - поставился, false - нет
	bool TryToPushFireSoldierToObservation( CSoldier *pSoldier );

	// находится ли pSoldier в точке наблюдения
	bool IsSoldierInObservationPoint( CSoldier *pSoldier ) const;
	// поставить pSoldier в observation point на стороне nSide
	void PushSoldierToObservationPoint( CSoldier *pSoldier, const int nSide );

	// вернуть боковые точки наблюдения стороны nSide
	void GetSidesObservationPoints( const int nSide, int *pnLeftPoint, int *pnRightPoint ) const;
	// вернуть центральную точку наблюдения стороны nSide
	const int GetMiddleObservationPoint( const int nSide ) const;
	// вернуть первого из солдат на стороне nSize
	CSoldier* GetSoldierOnSide( const int nSide );
	// true, если pSoldierInPoint в observation point лучше сменить на pSoldier
	bool IsBetterChangeObservationSoldier( CSoldier *pSoldier, CSoldier *pSoldierInPoint );
	// выбрать сторону, чтобы посадить солдата в точку наблюдения,
	// если в каждой из точек уже сидит солдат, вовращает -1
	const int ChooseSideToSetSoldier( class CSoldier *pSoldier ) const;
	void CentreSoldiersInObservationPoints();
	// посадить солдат за встроенные пушки
	void ExchangeSoldiersToTurrets();

	// количество HP, когда пора убегать из здания ( убегать, если их станет меньше )
	const float GetEscapeHitPoints() const;
	// выгнать формацию солдата из дома, pFormations - список уже выгнанных формаций
	void DriveOut( CSoldier *pSoldier, std::hash_set<int> *pFormations );
	void KillAllInsiders();
protected:
	CGDBPtr<SBuildingRPGStats> pStats;

	virtual void AddSoldier( class CSoldier *pUnit );
	virtual void DelSoldier( class CSoldier *pUnit, const bool bFillEmptyFireplace );
	void SoldierDamaged( class CSoldier *pUnit );

	CBuilding() : pLockingUnit( 0 ), nextSegmTime ( 0 ), nScriptID( -1 ) { }
	CBuilding( const SBuildingRPGStats *pStats, const CVec2 &center, const int dbID, const float fHP, const int nFrameIndex );
public:
	const int GetNFreePlaces() const;
	const int GetNOverallPlaces() const { return nOveralPlaces; }

	virtual const SHPObjectRPGStats* GetStats() const { return pStats; }
	virtual void SetHitPoints( const float fNewHP );
	virtual void TakeDamage( const float fDamage, const bool bFromExplosion, const int nPlayerOfShoot, CAIUnit *pShotUnit );
	virtual void Die( const float fDamage );

	const int GetNEntrancePoints() const { return pStats->entrances.size(); }
	const CVec2 GetEntrancePoint( const int nEntrance ) const;
	// найти выход, ближайший чтобы идти в точку point
	bool ChooseEntrance( class CCommonUnit *pUnit, const CVec2 &vPoint, int *pnEntrance ) const;

	void GoOutFromEntrance( const int nEntrance, class CSoldier *pUnit );
	bool IsGoodPointForRunIn( const SVector &point, const int nEntrance, const float fMinDist = 0 ) const;

	virtual void Segment();
	virtual const NTimer::STime GetNextSegmentTime() const { return nextSegmTime; }
	
	virtual EStaticObjType GetObjectType() const { return ESOT_BUILDING; }

	// итерирование по fire slots
	virtual void StartIterate() { nIterator = 0; }
	virtual void Iterate() { if ( nIterator < fire.Size() ) ++nIterator; }
	virtual bool IsIterateFinished() { return nIterator == fire.Size(); }
	virtual class CAIUnit* GetIteratedUnit();

	virtual bool IsContainer() const { return true; }
	virtual const int GetNDefenders() const;
	virtual class CSoldier* GetUnit( const int n ) const;
	virtual const BYTE GetPlayer() const;
	
	void Lock( class CCommonUnit *pUnit );
	bool IsLocked( const int nPlayer ) const;
	void Unlock( class CCommonUnit *pUnit );

	void Alarm();
	
	const int GetNGunsInFireSlot( const int nSlot );
	CBasicGun* GetGunInFireSlot( const int nSlot, const int nGun );
	CTurret* GetTurretInFireSlot( const int nSlot );
	float GetMaxFireRangeInSlot( const int nSlot ) const;
	
	bool IsSoldierVisible( const int nParty, const CVec2 &center, bool bCamouflated, const float fCamouflage ) const;
	
	virtual bool IsSelectable() const;
	virtual const bool IsVisibleForDiplomacyUpdate();
	
	virtual bool CanUnitGoThrough( const EAIClass &eClass ) const;
	
	// можно ли менять слот у этого слодата
	virtual bool CanRotateSoldier( class CSoldier *pSoldier ) const;
	// поставить солдата в place вместо сидящего там
	virtual void ExchangeUnitToFireplace( class CSoldier *pSoldier, int nFirePlace );
	// количество fireplaces
	const int GetNFirePlaces() const;
	// солдат, сидящий в fireplace, если fireplace пуст, то возвращает 0
	class CSoldier* GetSoldierInFireplace( const int nFireplace) const;
	
	virtual void SetScriptID( const int _nScriptID ) { nScriptID = _nScriptID; }

	const NTimer::STime& GetLastLeaveTime( const int nPlayer ) const { return lastLeave[nPlayer]; }
	void SetLastLeaveTime( const int nPlayer );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// простое здание
class CBuildingSimple : public CBuilding
{
	DECLARE_SERIALIZE;
	OBJECT_COMPLETE_METHODS( CBuildingSimple );
public:
	CBuildingSimple() { }
	CBuildingSimple( const SBuildingRPGStats *pStats, const CVec2 &center, const int dbID, const float fHP, const int nFrameIndex )
	: CBuilding( pStats, center, dbID, fHP, nFrameIndex )
	{
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// здание, которое является складом (главным или промежуточным)
class CBuildingStorage : public CBuilding
{
	DECLARE_SERIALIZE;
	OBJECT_COMPLETE_METHODS( CBuildingStorage );
	
	int nPlayer; // кому принадлежит это здание
	bool bConnected;
	NTimer::STime timeLastBuildingRepair;		// для самолечения главного хранилища
protected:
	virtual void AddSoldier( CSoldier *pUnit );
public:
	CBuildingStorage () : timeLastBuildingRepair( 0 ), bConnected( true ) {  }
	CBuildingStorage( const SBuildingRPGStats *pStats, const CVec2 &center, const int dbID, const float fHP, const int nFrameIndex, int player );

	virtual void TakeDamage( const float fDamage, const bool bFromExplosion, const int nPlayerOfShoot, CAIUnit *pShotUnit );
	
	virtual const BYTE GetPlayer() const;
	virtual void SetPlayerForEditor( const int _nPlayer ) { nPlayer = _nPlayer; }

	virtual void Segment();
	virtual void SetHitPoints( const float fNewHP );

	void SetConnected( bool bConnected );
	bool IsConnected() const { return bConnected; }
	void ChangePlayer( const int nPlayer );
	
	void GetNewUnitInfo( SNewUnitInfo *pNewUnitInfo );

	virtual bool ShouldSuspendAction( const EActionNotify &eAction ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __BUILDING_H__
