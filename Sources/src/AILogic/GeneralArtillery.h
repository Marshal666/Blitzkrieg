#ifndef __GENERAL_ARTILLERY_H__
#define __GENERAL_ARTILLERY_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "GeneralInternalInterfaces.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAntiArtillery;
class CAIUnit;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CGeneralArtilleryGoToPosition : public IRefCount
{
	OBJECT_COMPLETE_METHODS( CGeneralArtilleryGoToPosition );
	DECLARE_SERIALIZE;
	
	enum EBombardmentState { EBS_START, EBS_MOVING, EBS_WAIT_FOR_TRUCK, EBS_MOVING_WITH_TRUCK, EBS_FINISHING };
	EBombardmentState eState;

	CAIUnit *pUnit;
	CVec2 vPos;
	bool bToReservePosition;
	bool bFinished;
	NTimer::STime timeOfFinish;
	NTimer::STime startTime;

	// 
	void StartState();
	void WaitForTruck();
	void MovingWithTruck();
	void Finishing();
public:
	CGeneralArtilleryGoToPosition() { }
	CGeneralArtilleryGoToPosition( CAIUnit *pUnit, const CVec2 &vPos, bool bToReservePosition );

	void Segment();
	bool IsFinished() { return bFinished; }

	bool DoesGoToReservePosition() const { return bToReservePosition; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CGeneralArtilleryTask
{
	DECLARE_SERIALIZE;

	bool bBombardmentFinished;

	CVec2 vBombardmentCenter;
	float fBombardmentRadius;
	NTimer::STime timeToFinishBombardment;
	NTimer::STime timeToSendAntiArtilleryAck;
	CVec2 vAntiArtilleryAckCenter;
	bool bIsAntiArtilleryFight;
	NTimer::STime startRotatingTime;

	enum EBombardmentState { EBS_START, EBS_ROTATING, EBS_GOING_TO_BATTLE, EBS_FIRING, EBS_ESCAPING };
	EBombardmentState eState;

	struct SBombardmentUnitState
	{
		DECLARE_SERIALIZE;
	public:
		CVec2 vReservePosition;
		CVec2 vAttackPos;

		CPtr<CAIUnit> pUnit;
		CPtr<CGeneralArtilleryGoToPosition> pGoToPosition;

		SBombardmentUnitState() { }
		explicit SBombardmentUnitState( CAIUnit *pUnit );
	};

	std::list<SBombardmentUnitState> bombardmentUnits;

	class CGeneralArtillery *pOwner;

	int nCellNumber;
	int nParty;

	//
	// начало обстрела - дать команды подцепиться к грузовикам и ехать
	void StartBombardment();
	// как только приехали, дать команду развернуться к врагу
	void GoingToBattle();
	// как только развернулись, дать команду стрелять
	void Rotating();
	// когда отстрелялись, дать команду уезжать на резервные позиции
	void Firing();
	// когда приехали на резервные позиции, закончить артобстрел
	void Escaping();
	// если часть юнитов по какой-то причине не смогла провести артобстрел, проследить, 
	// чтобы они вернулись на резервные позиции
	void CheckEscapingUnits();

	void CalculateTimeToSendAntiArtilleryAck();

	void SetBombardmentFinished();
public:
	CGeneralArtilleryTask() : bBombardmentFinished( true ), bIsAntiArtilleryFight( false ) { }
	CGeneralArtilleryTask( CGeneralArtillery *pOwner, std::list<CAIUnit*> &givenUnits, bool bAntiArtilleryFight, const CVec2 &vCenter, const float fRadius, const int nCellNumber );

	void Segment();

	bool IsTaskFinished() const { return bBombardmentFinished; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CGeneralArtillery : public IRefCount, public IEnemyEnumerator
{
	OBJECT_COMPLETE_METHODS( CGeneralArtillery );
	DECLARE_SERIALIZE;

	class CGeneral *pGeneralOwner;
	int nParty;

	typedef std::list< CPtr<CAIUnit> > CUnitsList;
	CUnitsList freeUnits;
	CUnitsList trucks;

	std::list<CGeneralArtilleryTask> tasks;
public:
	CGeneralArtillery() { }
	CGeneralArtillery( const int nParty, CGeneral *pGeneralOwner );
	
	// дать генералу юнит для использования в качестве артиллерии
	void TakeArtillery( CAIUnit *pUnit );
	// the same for trucks
	void TakeTruck( CAIUnit *pUnit );

	void Segment();
	bool CanBombardRegion( const CVec2 &vRegionCenter );

	int RequestForSupport( const CVec2 &vCenter, const float fRadius, bool bIsAntiArtilleryFight, const int nCellNumber );
	void CancelRequest( int nRequestID, enum EForceType eType );

	void SetEnemyContainer( IEnemyContainer *pEnemyContainer );

	//IEnemyEnumerator
	virtual bool EnumEnemy( class CAIUnit *pEnemy );

	const int GetParty() const { return nParty; }
	const int GetNFreeUnits() const { return freeUnits.size(); }

	void SetCellInUse( const int nResistanceCell, bool bInUse );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __GENERAL_ARTILLERY_H__
