#ifndef __GENERAL__
#define __GENERAL__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CGeneral;
interface IGeneralDelayedTask;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EResupplyType
{
	ERT_REPAIR						= 0,
	ERT_RESUPPLY					= 1,
	ERT_HUMAN_RESUPPLY		= 2,
	ERT_MORALE						= 3,
	ERT_MEDICINE					= 4,
	
	_ERT_COUNT						= 5,
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������� ������
class CSupremeBeing
{
	DECLARE_SERIALIZE;
	typedef std::hash_map<int, CPtr<CGeneral> > Generals;
	Generals generals;
	typedef std::list< CPtr<IGeneralDelayedTask> > DelayedTasks;
	DelayedTasks delayedTasks;

	std::hash_set<int/*Link ID*/> ironmans;

public:
	void Segment();
	void Clear();

	void SetUnitVisible( class CAIUnit *pUnit, const int nGeneralParty, const bool bVisible );
	
	// ����� ������� �������� ����� ������ ��������
	void SetAAVisible( class CAIUnit *pUnit, const int nGeneralParty, const bool bVisible );
	
	// creates number of generals
	// ������ ������� ����� � ������, ������� �������� ��������� ��������
	void Init( const struct SAIGeneralMapInfo &mapInfo );
	// ������� ����� ���������
	void GiveNewUnitsToGenerals( const std::list<class CCommonUnit*> &pUnits );

	bool IsMobileReinforcement( int nParty, int nGroup ) const;
	void AddReinforcement( class CAIUnit *pUnit );
	interface IEnemyContainer* GetEnemyConatiner( int nPlayer );
	
	bool MustShootToObstacles( const int nPlayer );
	void RegisterDelayedTask( interface IGeneralDelayedTask *pTask );
	
	// ��� ������ �������������
	void UpdateEnemyUnitInfo( class CAIUnitInfoForGeneral *pInfo,
		const NTimer::STime lastVisibleTimeDelta, const CVec2 &vLastVisiblePos,
		const NTimer::STime lastAntiArtTimeDelta, const CVec2 &vLastVisibleAntiArtCenter, const float fDistToLastVisibleAntiArt );
	void UnitChangedParty( class CAIUnit *pUnit, const int nNewParty );
	void UnitDied( class CAIUnitInfoForGeneral *pInfo );
	void UnitDied( class CCommonUnit * pUnit );
	
	void ReserveAviationForTimes( const int nParty, const std::vector<NTimer::STime> &times );
	
	// when some unit changed position.
	void UnitChangedPosition( class CCommonUnit * pUnit, const CVec2 &vNewPos );
	void UnitAskedForResupply( class CCommonUnit * pUnit, const EResupplyType eType, const bool bSet );

	void AddIronman( const int nScriptGroup );
	bool IsIronman( const int nScriptGroup ) const;

	bool IsInResistanceCircle( const CVec2 &vPoint, const int nGeneralParty );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __GENERAL__
