#ifndef __GAME_STATS_H__
#define __GAME_STATS_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** basic game stats
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SBasicGameStats : public IGDBObject
{
	std::string szParentName;							// parent object key name. ����������� ����������� ��� �������� �������
	std::string szKeyName;								// key name
	std::string szStatsType;							// ��� ������� - mission, chapter, campaign
	//
	std::string szHeaderText;							// description header (txt)
	std::string szSubheaderText;					// description sub-header (txt)
	std::string szDescriptionText;				// description body (txt)
	//
	SBasicGameStats() : szStatsType( "Basic" ) {  }
	SBasicGameStats( const char *pszStatsType ) : szStatsType( pszStatsType ) {  }
	virtual ~SBasicGameStats() {  }
	//
	virtual const char* STDCALL GetName() const { return szStatsType.c_str(); }
	virtual const char* STDCALL GetKeyName() const { return szKeyName.c_str(); }
	virtual const char* STDCALL GetParentName() const { return szParentName.c_str(); }
	//
	virtual void STDCALL RetrieveShortcuts( IObjectsDB *pGDB ) {  }
	virtual const uLong STDCALL GetCheckSum() const { return 0L; }
	//
	virtual int STDCALL operator&( IDataTree &ss );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** common stats for campaign/chapter/mission descriptions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SCommonGameStats : public SBasicGameStats
{
	std::string szMapImage;								// map (tga)
	CTRect<float> mapImageRect;						// x1 y1 ��� ���������� � ��������, x2 y2 ���������� ����������
	//
	SCommonGameStats( const char *pszStatsType ) : SBasicGameStats( pszStatsType ) {  }
	virtual ~SCommonGameStats() {  }
	//
	virtual int STDCALL operator&( IDataTree &ss );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** mission stats
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SMissionStats : public SCommonGameStats
{
	struct SObjective
	{
		std::string szHeader;								// objective header
		std::string szDescriptionText;			// objective description
		CVec2 vPosOnMap;										// objective position on the mission map
		bool bSecret;												// is this objective secret ?
		int nAnchorScriptID;								// reference object to retrieve coords for template missions
		//
		SObjective()
			: bSecret( false ), nAnchorScriptID( -1 ) {  }
		//
		int operator&( IDataTree &ss );
	};
	//
	std::vector<std::string> combatMusics;			// mission combat music themes
	std::vector<std::string> explorMusics;			// mission exploration music themes
	std::vector<SObjective> objectives;		// objectives of this mission
	std::string szTemplateMap;						// template map (xml file)
	std::string szFinalMap;								// final map (xml file)
	std::string szSettingName;						// settings file name
	std::string szMODName;
	std::string szMODVersion;
	//
	SMissionStats() : SCommonGameStats( "Mission" ) {  }
	virtual ~SMissionStats() { }
	//
	virtual const uLong STDCALL GetCheckSum() const { return 0L; }
	const bool IsTemplate() const { return !szTemplateMap.empty(); }
	//
	virtual int STDCALL operator&( IDataTree &ss );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** chapter (set of missions) stats
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SChapterStats : public SCommonGameStats
{
	struct SMission
	{
		const SMissionStats *pMission;			// shortcut to the mission stats
		std::string szMission;							// mission name (to retrieve shortcuts)
		CVec2 vPosOnMap;										// position on the chapter map
		int nMissionDifficulty;							// difficulty for random missions
		std::string szMissionBonus;					// bonus after win random mission
		std::vector<std::string> szAllBonuses;	// all possible bonuses for this mission
		//
		SMission() : nMissionDifficulty( 0 ) {  }
		//
		void RetrieveShortcuts( IObjectsDB *pGDB );
		int operator&( IDataTree &ss );
		int operator&( IStructureSaver &ss );
	};
	//
	struct SPlaceHolder
	{
		CVec2 vPosOnMap;										// position on the chapter map
		int operator&( IDataTree &ss );
	};
	//
	int nSeason;													// season: summer, winter, africa
	std::string szInterfaceMusic;					// interface music theme (mp3)
	std::vector<SMission> missions;				// all missions in this chapter
	std::vector<SPlaceHolder> placeHolders;	// all placeholders in this chapter
	std::string szScript;									// chapter script (lua)
	std::string szSettingName;						// settings file name
	std::string szContextName;						// reference to context file
	std::string szSideName;								// player side file name
	std::string szMODName; 
	std::string szMODVersion;
	//
	SChapterStats()
		: SCommonGameStats( "Chapter" ), nSeason( 0 )	{  }
	virtual ~SChapterStats() {  }
	//
	virtual const uLong STDCALL GetCheckSum() const { return 0L; }
	//
	virtual void STDCALL RemoveTemplateMissions();
	virtual void STDCALL AddMission( const SChapterStats::SMission &mission );

	virtual void STDCALL RetrieveShortcuts( IObjectsDB *pGDB );
	virtual int STDCALL operator&( IDataTree &ss );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** campaign (set of chapters) stats
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SCampaignStats : public SCommonGameStats
{
	struct SChapter
	{
		const SChapterStats *pChapter;			// shortcut to the chapter stats
		std::string szChapter;							// chapter name (to retrieve shortcuts)
		CVec2 vPosOnMap;										// position on the campaign map
		bool bVisible;											// is this chapter visible ?
		bool bSecret;												// is this chapter secret ?
		//
		SChapter()
			: pChapter( 0 ), vPosOnMap( VNULL2 ), bVisible( true ), bSecret( false ) {  }
		//
		void RetrieveShortcuts( IObjectsDB *pGDB );
		int operator&( IDataTree &ss );
	};
	std::vector<SChapter> chapters;				// all chapters in this campaign
	//
	std::vector< std::string > templateMissions;	// all template missions in this campaign
	//
	std::string szIntroMovie;							// intro movie (bik)
	std::string szOutroMovie;							// outro movie (bik)
	std::string szInterfaceMusic;					// interface music theme (mp3)
	std::string szSideName;								// player side name
	std::string szMODName;
	std::string szMODVersion;
	//
	SCampaignStats() : SCommonGameStats( "Campaign" ) {  }
	virtual ~SCampaignStats() {  }
	//
	virtual const uLong STDCALL GetCheckSum() const { return 0L; }
	//
	virtual void STDCALL RetrieveShortcuts( IObjectsDB *pGDB );
	virtual int STDCALL operator&( IDataTree &ss );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** medal
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SMedalStats : public SBasicGameStats
{
	std::string szTexture;								// texture with medal's picture
	CTRect<float> mapImageRect;						// ������ ��� ���������� - �������, ������ - maps
	CVec2 vPicturePos;										// ���������� �������� ������������ �������� ����
	CVec2 vTextCenterPos;									// ���������� ������ ������ ������������ �������� ����
	//
	SMedalStats() : SBasicGameStats( "Medal" ), vPicturePos( 0, 0 ), vTextCenterPos( 0, 0 ) {  }
	virtual ~SMedalStats() {  }
	//
	virtual const uLong STDCALL GetCheckSum() const { return 0L; }
	//
	virtual int STDCALL operator&( IDataTree &ss );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __GAMESTATS_H__
