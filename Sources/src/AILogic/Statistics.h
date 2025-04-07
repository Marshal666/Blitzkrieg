#ifndef __STATISTICS_H__
#define __STATISTICS_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IScenarioTracker;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CStatistics
{
	DECLARE_SERIALIZE;

	CPtr<IScenarioTracker> pScenarioTracker;	// scenario tracker shortcut
	bool bEnablePlayerExp;										// can we add player exp? (false in tutorial mode - initialized in the Init())
public:
	CStatistics() : bEnablePlayerExp( false ) {  }

	void Init();

	// player captured oter player's unit
	void UnitCaptured( const int nPlayer );
	// игрок nPlayer уничтожил юниты игрока nKilledUnitsPlayer, nUnits - количество убитых, fTotalAIPrice - их price
	void UnitKilled( const int nPlayer, const int nKilledUnitsPlayer, const int nUnits, const float fTotalAIPrice );
	// unit умер
	void UnitDead( class CCommonUnit *pUnit );
	// игрок nPlayer уничтожил house
	void ObjectDestroyed( const int nPlayer );
	// игрок nPlayer вызвал авиацию
	void AviationCalled( const int nPlayer );
	// игрок nPlayer использовал reinforcement
	void ReinforcementUsed( const int nPlayer );
	// игрок nPlayer использовал ресурсы
	void ResourceUsed( const int nPlayer, const float fResources );
	// unit получил level
	void UnitLeveledUp( class CCommonUnit *pUnit );
	//player's experience
	void IncreasePlayerExperience( const int nPlayer, const float fPrice ) ;

	void SetFlagPoints( const int nParty, const float fPoints );
	void SetCapturedFlags( const int nParty, const int nFlags );

	interface IMissionStatistics* GetPlayerStats( const int nPlayer );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __STATISTICS_H__
