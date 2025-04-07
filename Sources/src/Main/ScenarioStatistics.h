#ifndef __SCENARIOSTATISTICS_H__
#define __SCENARIOSTATISTICS_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ScenarioTracker.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** mission statistics
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CMissionStatistics : public CTRefCount<IMissionStatistics>
{
	OBJECT_SERVICE_METHODS( CMissionStatistics );
	DECLARE_SERIALIZE;
	//
	struct SKIAUnit
	{
		std::string szOldName;
		std::string szNewName;
		std::string szRPGStats;
		//
		SKIAUnit() {  }
		SKIAUnit( const std::string &_szOldName, const std::string &_szNewName, const std::string &_szRPGStats )
			: szOldName( _szOldName ), szNewName( _szNewName ), szRPGStats( _szRPGStats ) {  }
		//
		int operator&( IStructureSaver &ss )
		{
			CSaverAccessor saver = &ss;
			saver.Add( 1, &szOldName );
			saver.Add( 2, &szNewName );
			saver.Add( 3, &szRPGStats );
			return 0;
		}
	};
	//
	std::string szName;										// game stats name
	std::vector<int> values;							// mission statistics values
	EMissionFinishStatus eStatus;					// finish status
	std::vector<SKIAUnit> kiaUnits;				// killed in this mission
public:
	CMissionStatistics();
	// get mission/chapter/campaign name
	const std::string& STDCALL GetName() const;
	// retrieve statistics value by type
	int STDCALL GetValue( const int nType ) const;
	// add (increment) value
	void STDCALL AddValue( const int nType, const int nValue );
	// set value directly (override)
	void STDCALL SetValue( const int nType, const int nValue );
	// get mission finish status
	EMissionFinishStatus STDCALL GetFinishStatus() const;
	// number of killed in action (KIA)
	int STDCALL GetNumKIA() const { return kiaUnits.size(); }
	// KIA name (file name with localized name)
	const std::string& STDCALL GetKIAName( const int nIndex ) const;
	// KIA new name (file name with localized name)
	const std::string& STDCALL GetKIANewName( const int nIndex ) const;
	// KIA RPG stats
	const std::string& STDCALL GetKIAStats( const int nIndex ) const;
	//
	// internal management
	//
	void SetName( const std::string &_szName ) { szName = _szName; }
	void SetFinishStatus( const EMissionFinishStatus _eStatus ) { eStatus = _eStatus; }
	void AddKIAUnit( const std::string &szOldName, const std::string &szNewName, const std::string &szRPGStats ) 
	{ 
		kiaUnits.push_back( SKIAUnit(szOldName, szNewName, szRPGStats) ); 
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** chapter statistics
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CChapterStatistics : public CTRefCount<IChapterStatistics>
{
	OBJECT_SERVICE_METHODS( CChapterStatistics );
	DECLARE_SERIALIZE;
	//
	std::string szName;										// game stats name
	typedef std::vector< CObj<CMissionStatistics> > CMissionStatisticsList;
	CMissionStatisticsList missions;			// all missions in this chapter
public:
	// get mission/chapter/campaign name
	const std::string& STDCALL GetName() const;
	// retrieve statistics value by type
	int STDCALL GetValue( const int nType ) const;
	// get num missions, ever started in this chapter
	int STDCALL GetNumMissions() const;
	// get particular mission statistics
	IMissionStatistics* STDCALL GetMission( const int nIndex ) const;
	// number of killed in action (KIA)
	int STDCALL GetNumKIA() const;
	// KIA name (file name with localized name)
	const std::string& STDCALL GetKIAName( const int nIndex ) const;
	// KIA new name (file name with localized name)
	const std::string& STDCALL GetKIANewName( const int nIndex ) const;
	// KIA RPG stats
	const std::string& STDCALL GetKIAStats( const int nIndex ) const;
	//
	// internal management
	//
	void SetName( const std::string &_szName ) { szName = _szName; }
	void AddMission( CMissionStatistics *pMission ) { missions.push_back( pMission ); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** campaign statistics
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCampaignStatistics : public CTRefCount<ICampaignStatistics>
{
	OBJECT_SERVICE_METHODS( CCampaignStatistics );
	DECLARE_SERIALIZE;
	//
	std::string szName;										// game stats name
	typedef std::vector< CObj<CChapterStatistics> > CChapterStatisticsList;
	CChapterStatisticsList chapters;			// all chapters in this campaign
	ECampaignType eType;									// campaign type
public:
	// get mission/chapter/campaign name
	const std::string& STDCALL GetName() const;
	// get campaign type
	ECampaignType STDCALL GetType() const;
	// retrieve statistics value by type
	int STDCALL GetValue( const int nType ) const;
	// get num chapters, ever started in this campaign
	int STDCALL GetNumChapters() const;
	// get particular chapter statistics
	IChapterStatistics* STDCALL GetChapter( const int nIndex ) const;
	// number of killed in action (KIA)
	int STDCALL GetNumKIA() const;
	// KIA name (file name with localized name)
	const std::string& STDCALL GetKIAName( const int nIndex ) const;
	// KIA new name (file name with localized name)
	const std::string& STDCALL GetKIANewName( const int nIndex ) const;
	// KIA RPG stats
	const std::string& STDCALL GetKIAStats( const int nIndex ) const;
	//
	// internal management
	//
	void SetName( const std::string &_szName, const ECampaignType _eType );
	void AddChapter( CChapterStatistics *pChapter ) { chapters.push_back( pChapter ); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __SCENARIOSTATISTICS_H__
