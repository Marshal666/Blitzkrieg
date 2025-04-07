#ifndef __FREE_FIRE_MANAGER_H__
#define __FREE_FIRE_MANAGER_H__

#pragma ONCE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAIUnit;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// для атаки второстепенными пушками.
// если турели, на которых расположены пушки не залоканы, то вращает турели.
class CFreeFireManager
{
	DECLARE_SERIALIZE;

	enum { TIME_TO_CHECK = 1500 };

	struct SShotInfo
	{
		DECLARE_SERIALIZE;
		public:
		
		CPtr<CAIUnit> pTarget;
		CVec2 shootingPos;
		WORD unitDir;
		WORD gunDir;

		SShotInfo() : shootingPos( VNULL2 ), unitDir( 0 ), gunDir( 0 ) { }
		
		bool NeedAim( CAIUnit *pNewTarget, class CBasicGun *pGun ) const;
		void SetInfo( CAIUnit *pNewTarget, class CBasicGun *pGun );
	};

	std::vector<SShotInfo> shootInfo;

	NTimer::STime lastCheck;
public:
	CFreeFireManager() : lastCheck( 0 ) { }
	CFreeFireManager( class CCommonUnit *pOwner );
	// считается, что base уже залокана pActiveGun-ом
	void Analyze( class CCommonUnit *pUnit, class CBasicGun *pActiveGun );
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __FREE_FIRE_MANAGER_H__
