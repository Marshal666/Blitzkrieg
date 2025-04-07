#include "StdAfx.h"

#include "ScenarioStatistics.h"

#include "..\Misc\Checker.h"
#include "ScenarioTrackerTypes.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** mission statistics
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CMissionStatistics::CMissionStatistics() 
: values( STMT_NUM_ELEMENTS ), eStatus( MISSION_FINISH_UNKNOWN )
{  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get mission/chapter/campaign name
const std::string& CMissionStatistics::GetName() const
{
	return szName;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// retrieve statistics value by type
int CMissionStatistics::GetValue( const int nType ) const
{
	CheckRange( values, nType );
	return values[nType];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// add (increment) value
void CMissionStatistics::AddValue( const int nType, const int nValue )
{
	CheckRange( values, nType );
	values[nType] += nValue;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set value directly (override)
void CMissionStatistics::SetValue( const int nType, const int nValue )
{
	CheckRange( values, nType );
	values[nType] = nValue;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get mission finish status
EMissionFinishStatus CMissionStatistics::GetFinishStatus() const
{
	return eStatus;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KIA name (file name with localized name)
const std::string& CMissionStatistics::GetKIAName( const int nIndex ) const
{
	CheckRange( kiaUnits, nIndex );
	return kiaUnits[nIndex].szOldName;
}
// KIA new name (file name with localized name)
const std::string& CMissionStatistics::GetKIANewName( const int nIndex ) const
{
	CheckRange( kiaUnits, nIndex );
	return kiaUnits[nIndex].szNewName;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const std::string& CMissionStatistics::GetKIAStats( const int nIndex ) const
{
	CheckRange( kiaUnits, nIndex );
	return kiaUnits[nIndex].szRPGStats;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CMissionStatistics::operator&( IStructureSaver &ss )
{
	CSaverAccessor saver = &ss;
	saver.Add( 1, &szName );
	saver.Add( 2, &values );
	saver.Add( 3, &eStatus );
	saver.Add( 4, &kiaUnits );
	if ( saver.IsReading() ) 
	{
		if ( values.size() != STMT_NUM_ELEMENTS ) 
			values.resize( STMT_NUM_ELEMENTS );
		if ( values[STMT_OBJECTIVES_RECIEVED] < values[STMT_OBJECTIVES_COMPLETED] ) 
			values[STMT_OBJECTIVES_RECIEVED] = values[STMT_OBJECTIVES_COMPLETED];
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** chapter statistics
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get mission/chapter/campaign name
const std::string& CChapterStatistics::GetName() const
{
	return szName;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// retrieve statistics value by type
int CChapterStatistics::GetValue( const int nType ) const
{
	int nValue = 0;
	for ( CMissionStatisticsList::const_iterator it = missions.begin(); it != missions.end(); ++it )
	{
		if ( (*it)->GetFinishStatus() == MISSION_FINISH_WIN ) 
			nValue += (*it)->GetValue( nType );
	}
	//
	return nValue;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get num missions, ever started in this chapter
int CChapterStatistics::GetNumMissions() const
{
	return missions.size();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get particular mission statistics
IMissionStatistics* CChapterStatistics::GetMission( const int nIndex ) const
{
	CheckRange( missions, nIndex );
	return missions[nIndex];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// number of killed in action (KIA)
int CChapterStatistics::GetNumKIA() const 
{ 
	int nAmount = 0;
	for ( CMissionStatisticsList::const_iterator it = missions.begin(); it != missions.end(); ++it )
	{
		if ( (*it)->GetFinishStatus() == MISSION_FINISH_WIN ) 
			nAmount += (*it)->GetNumKIA();
	}
	return nAmount; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const std::string szDummy;
// KIA name (file name with localized name)
const std::string& CChapterStatistics::GetKIAName( const int nIndex ) const
{
	int nAmount = 0;
	for ( CMissionStatisticsList::const_iterator it = missions.begin(); it != missions.end(); ++it )
	{
		if ( (*it)->GetFinishStatus() == MISSION_FINISH_WIN ) 
		{
			const int nNumKIA = (*it)->GetNumKIA();
			if ( (nAmount <= nIndex) && (nAmount + nNumKIA > nIndex) )
				return (*it)->GetKIAName( nIndex - nAmount );
			nAmount += (*it)->GetNumKIA();
		}
	}
	NI_ASSERT_T( false, "Invalid index for KIA name in chapter" );
	return szDummy;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KIA new name (file name with localized name)
const std::string& CChapterStatistics::GetKIANewName( const int nIndex ) const
{
	int nAmount = 0;
	for ( CMissionStatisticsList::const_iterator it = missions.begin(); it != missions.end(); ++it )
	{
		if ( (*it)->GetFinishStatus() == MISSION_FINISH_WIN ) 
		{
			const int nNumKIA = (*it)->GetNumKIA();
			if ( (nAmount <= nIndex) && (nAmount + nNumKIA > nIndex) )
				return (*it)->GetKIANewName( nIndex - nAmount );
			nAmount += (*it)->GetNumKIA();
		}
	}
	NI_ASSERT_T( false, "Invalid index for KIA new name in chapter" );
	return szDummy;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KIA RPG stats
const std::string& CChapterStatistics::GetKIAStats( const int nIndex ) const
{
	int nAmount = 0;
	for ( CMissionStatisticsList::const_iterator it = missions.begin(); it != missions.end(); ++it )
	{
		if ( (*it)->GetFinishStatus() == MISSION_FINISH_WIN ) 
		{
			const int nNumKIA = (*it)->GetNumKIA();
			if ( (nAmount <= nIndex) && (nAmount + nNumKIA > nIndex) )
				return (*it)->GetKIAStats( nIndex - nAmount );
			nAmount += (*it)->GetNumKIA();
		}
	}
	NI_ASSERT_T( false, "Invalid index for KIA stats in chapter" );
	return szDummy;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CChapterStatistics::operator&( IStructureSaver &ss )
{
	CSaverAccessor saver = &ss;
	saver.Add( 1, &szName );
	saver.Add( 2, &missions );
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** campaign statistics
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get mission/chapter/campaign name
const std::string& CCampaignStatistics::GetName() const
{
	return szName;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ECampaignType CCampaignStatistics::GetType() const
{
	return eType;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// retrieve statistics value by type
int CCampaignStatistics::GetValue( const int nType ) const
{
	int nValue = 0;
	for ( CChapterStatisticsList::const_iterator it = chapters.begin(); it != chapters.end(); ++it )
		nValue += (*it)->GetValue( nType );
	return nValue;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get num chapters, ever started in this campaign
int CCampaignStatistics::GetNumChapters() const
{
	return chapters.size();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get particular chapter statistics
IChapterStatistics* CCampaignStatistics::GetChapter( const int nIndex ) const
{
	CheckRange( chapters, nIndex );
	return chapters[nIndex];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCampaignStatistics::SetName( const std::string &_szName, const ECampaignType _eType )
{
	szName = _szName;
	eType = _eType;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CCampaignStatistics::GetNumKIA() const 
{ 
	int nAmount = 0;
	for ( CChapterStatisticsList::const_iterator it = chapters.begin(); it != chapters.end(); ++it )
		nAmount += (*it)->GetNumKIA();
	return nAmount; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KIA name (file name with localized name)
const std::string& CCampaignStatistics::GetKIAName( const int nIndex ) const
{
	int nAmount = 0;
	for ( CChapterStatisticsList::const_iterator it = chapters.begin(); it != chapters.end(); ++it )
	{
		const int nNumKIA = (*it)->GetNumKIA();
		if ( (nAmount <= nIndex) && (nAmount + nNumKIA > nIndex) )
			return (*it)->GetKIAName( nIndex - nAmount );
		nAmount += (*it)->GetNumKIA();
	}
	NI_ASSERT_T( false, "Invalid index for KIA name in campaign" );
	return szDummy;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KIA new name (file name with localized name)
const std::string& CCampaignStatistics::GetKIANewName( const int nIndex ) const
{
	int nAmount = 0;
	for ( CChapterStatisticsList::const_iterator it = chapters.begin(); it != chapters.end(); ++it )
	{
		const int nNumKIA = (*it)->GetNumKIA();
		if ( (nAmount <= nIndex) && (nAmount + nNumKIA > nIndex) )
			return (*it)->GetKIANewName( nIndex - nAmount );
		nAmount += (*it)->GetNumKIA();
	}
	NI_ASSERT_T( false, "Invalid index for KIA name in campaign" );
	return szDummy;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KIA RPG stats
const std::string& CCampaignStatistics::GetKIAStats( const int nIndex ) const
{
	int nAmount = 0;
	for ( CChapterStatisticsList::const_iterator it = chapters.begin(); it != chapters.end(); ++it )
	{
		const int nNumKIA = (*it)->GetNumKIA();
		if ( (nAmount <= nIndex) && (nAmount + nNumKIA > nIndex) )
			return (*it)->GetKIAStats( nIndex - nAmount );
		nAmount += (*it)->GetNumKIA();
	}
	NI_ASSERT_T( false, "Invalid index for KIA stats in campaign" );
	return szDummy;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CCampaignStatistics::operator&( IStructureSaver &ss )
{
	CSaverAccessor saver = &ss;
	saver.Add( 1, &szName );
	saver.Add( 2, &chapters );
	saver.Add( 3, &eType );
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
