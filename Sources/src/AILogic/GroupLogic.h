#ifndef __AI_GROUP_LOGIC_H__
#define __AI_GROUP_LOGIC_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "SegmentedObjects.h"
#include "UnitsSegments.h"

#include "..\Common\Actions.h"
#include "..\Misc\FreeIDs.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCommonUnit;
class CAIUnit;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CGroupLogic : public IRefCount
{
	OBJECT_NORMAL_METHODS( CGroupLogic );
	DECLARE_SERIALIZE;

	CFreeIds groupIds;
	std::hash_set<int> registeredGroups;
	CQueuesSet< CPtr<CCommonUnit> > groupUnits;
	std::list< CPtr<CCommonUnit> > followingUnits;

	// 0 - all units, except of infantry; 1 - infantry
	std::vector< NSegmObjs::CContainer< CPtr<CCommonUnit> > > segmUnits;
	NSegmObjs::CContainer< CPtr<CCommonUnit> > freezeUnits;
	NSegmObjs::CContainer< CPtr<CAIUnit> > firstPathUnits;
	NSegmObjs::CContainer< CPtr<CAIUnit> > secondPathUnits;

	NTimer::STime lastSegmTime;
	
	struct SAmbushInfo
	{
		int nUniqueId;
		CVec2 vAmbushCenter;
		WORD wAmbushDir;
		bool bGivenCommandToRestore;

		SAmbushInfo() : nUniqueId( -1 ), vAmbushCenter( VNULL2 ), wAmbushDir( 0 ), bGivenCommandToRestore( false ) { }
		SAmbushInfo( const int _nUniqueId )
			: nUniqueId( _nUniqueId ), vAmbushCenter( -1.0f, -1.0f ), wAmbushDir( 0 ), bGivenCommandToRestore( false ) { }
	};
	typedef std::list< std::list<SAmbushInfo> > CAmbushGroups;
	CAmbushGroups ambushGroups;
	std::hash_set<int> ambushUnits;
	NTimer::STime lastAmbushCheck;

	//
	void DelGroup( const int nGroup );
	void DivideBySubGroups( const SAIUnitCmd &command, const int nGroup );

	// �������� ������ � follow
	void SegmentFollowingUnits();
	// ��������� ���������� ��-�� �������� ������
	void StayTimeSegment();

	void ProcessGridCommand( const CVec2 &vGridCenter, const CVec2 &vGridDir, const int nGroup, bool bPlaceInQueue );

	void EraseFromAmbushGroups( const SAIUnitCmd &command, const WORD wGroup );
	void CreateAmbushGroup( const WORD wGroup );
	void ProcessAmbushGroups();
	void SetToAmbush( CAmbushGroups::iterator &iter );

	//
	static WORD GetGroupNumberByID( const WORD wID );
	static WORD GetSpecialGroupNumberByID( const WORD wID );
	static WORD GetIdByGroupNumber( const WORD wGroup ); 
	static WORD GetPlayerByGroupNumber( const WORD wGroup );
public:
	CGroupLogic() { }
	void Init();
	void Clear() { DestroyContents(); }

	const WORD GenerateGroupNumber();
	void RegisterGroup( IRefCount **pUnitsBuffer, const int nLen, const WORD wGroup );
	void UnregisterGroup( const WORD wGroup );
	
	void DelUnitFromGroup( class CCommonUnit *pUnit );
	void AddUnitToGroup( class CCommonUnit *pUnit, const int nGroup );
	void DelUnitFromSpecialGroup( class CCommonUnit *pUnit );

	void GroupCommand( const SAIUnitCmd &command, const WORD wGroup, bool bPlaceInQueue );
	void UnitCommand( const SAIUnitCmd &command, class CCommonUnit *pGroupUnit, bool bPlaceInQueue );
	void InsertUnitCommand( const SAIUnitCmd &command, class CCommonUnit *pUnit );
	void PushFrontUnitCommand( const SAIUnitCmd &command, class CCommonUnit *pUnit );
	
	// ������� updates �� shoot areas ��� ���� ������ � ������
	void UpdateAllAreas( const int nGroup, const EActionNotify eAction );

	void Segment();
	
	void CreateSpecialGroup( const WORD wGroup );
	void UnregisterSpecialGroup( const WORD wSpecialGroup );
	
	int BeginGroup( const int nGroup ) const { return groupUnits.begin( nGroup ); }
	int EndGroup() const { return groupUnits.end(); }
	int Next( const int nIter ) const { return groupUnits.GetNext( nIter ); }
	class CCommonUnit* GetGroupUnit( const int nIter ) const { return groupUnits.GetEl( nIter ); }

	void AddFollowingUnit( class CCommonUnit *pUnit );

	void RegisterSegments( class CCommonUnit *pUnit, const bool bInitialization, const bool bAllInfo );
	void RegisterPathSegments( class CAIUnit *pUnit, const bool bInitialization );

	void UnregisterSegments( class CCommonUnit *pUnit );

	void UnitSetToAmbush( class CCommonUnit *pUnit );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CVec2 GetGoPointByCommand( const SAIUnitCmd &cmd );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //__AI_GROUP_LOGIC_H__
