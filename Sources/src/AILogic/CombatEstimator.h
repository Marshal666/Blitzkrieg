#ifndef __COMBATESTIMATOR_H__
#define __COMBATESTIMATOR_H__
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\Misc\HashFuncs.h"
#include "AIHashFuncs.h"
class CAIUnit;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// для определения комбатной стуации
class CCombatEstimator
{
	DECLARE_SERIALIZE;
	float fDamage;
	struct SShellInfo
	{
		NTimer::STime time;
		float fDamage;
		//
		SShellInfo() {}
		SShellInfo( NTimer::STime time, float fDamage )
			:time( time ), fDamage( fDamage ) { }
	};

	typedef std::hash_set<int> CRegisteredUnits;
	CRegisteredUnits registeredMechUnits;			// вражескте юниты (не пехота)с ненулевой текущей скоростью
	CRegisteredUnits registeredInfantry;			// вражескте юниты (пехота)с ненулевой текущей скоростью

	typedef std::list<SShellInfo> CShellTimes;
	CShellTimes shellTimes;								// время выстрела

public:
	CCombatEstimator();

	void Clear();
	void Segment();

	bool IsCombatSituation() const ;

	void AddShell( NTimer::STime time, float fDamage );
	
	void AddUnit( CAIUnit *pUnit );
	void DelUnit( CAIUnit *pUnit );
	                                                                                                                          
};
#endif // __COMBATESTIMATOR_H__

