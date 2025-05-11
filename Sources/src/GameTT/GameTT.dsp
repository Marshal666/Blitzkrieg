# Microsoft Developer Studio Project File - Name="GameTT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GameTT - Win32 Profiler
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GameTT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GameTT.mak" CFG="GameTT - Win32 Profiler"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GameTT - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GameTT - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GameTT - Win32 BetaRelease" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GameTT - Win32 FastDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GameTT - Win32 Profiler" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/GameTT", EFNAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GameTT - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "_FINALRELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 version.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
OutDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "GameTT - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_ASSERT_SLOW" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /Yu"StdAfx.h" /FD /GZ /Zm300 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
OutDir=.\Debug
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "GameTT - Win32 BetaRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BetaRelease"
# PROP BASE Intermediate_Dir "BetaRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BetaRelease"
# PROP Intermediate_Dir "BetaRelease"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /Ot /Og /Op /Ob2 /D "_DO_ASSERT_SLOW" /D "_BETARELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /Zm200 /c
# SUBTRACT CPP /Ox /Oi
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 version.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /def:".\GameTT.def" /FIXED:NO
# Begin Special Build Tool
OutDir=.\BetaRelease
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "GameTT - Win32 FastDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameTT___Win32_FastDebug"
# PROP BASE Intermediate_Dir "GameTT___Win32_FastDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FastDebug"
# PROP Intermediate_Dir "FastDebug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_ASSERT_SLOW" /D "WIN32" /D "_DEBUG" /D "_STL_FAST_DEBUG" /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "_DO_ASSERT_SLOW" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /GZ /Zm200 /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
OutDir=.\FastDebug
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "GameTT - Win32 Profiler"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GameTT___Win32_Profiler"
# PROP BASE Intermediate_Dir "GameTT___Win32_Profiler"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Profiler"
# PROP Intermediate_Dir "Profiler"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "_DO_ASSERT_SLOW" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /GZ /Zm200 /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_FINALRELEASE" /D "_PROFILER" /Yu"StdAfx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vtuneapi.lib version.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /def:".\GameTT.def" /pdbtype:sept /fixed:no
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
OutDir=.\Profiler
SOURCE="$(InputPath)"
PostBuild_Cmds=copy  $(OutDir)\*.dll  c:\a7\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "GameTT - Win32 Release"
# Name "GameTT - Win32 Debug"
# Name "GameTT - Win32 BetaRelease"
# Name "GameTT - Win32 FastDebug"
# Name "GameTT - Win32 Profiler"
# Begin Group "Common"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\GlobalsLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\Specific.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\stl_user_config.h
# End Source File
# End Group
# Begin Group "GameX"

# PROP Default_Filter ""
# Begin Group "World"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SelectorVisitors.h
# End Source File
# Begin Source File

SOURCE=.\WorldClient.cpp
# End Source File
# Begin Source File

SOURCE=.\WorldClient.h
# End Source File
# Begin Source File

SOURCE=.\WorldClientActions.cpp
# End Source File
# End Group
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Group "InterMission"

# PROP Default_Filter ""
# Begin Group "Multyplayer"

# PROP Default_Filter ""
# Begin Group "GamesList"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MultiplayerGamesList.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiplayerGamesList.h
# End Source File
# End Group
# Begin Group "StartingGame"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MultiplayerStartingGame.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiplayerStartingGame.h
# End Source File
# End Group
# Begin Group "Chat"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InterfaceMPChat.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceMPChat.h
# End Source File
# End Group
# Begin Group "Common No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ChatWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatWrapper.h
# End Source File
# Begin Source File

SOURCE=.\ListControlWrapper.h
# End Source File
# End Group
# Begin Group "CreateGame"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InterfaceMPCreateGame.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceMPCreateGame.h
# End Source File
# End Group
# Begin Group "MapSettings No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InterfaceMPMapSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceMPMapSettings.h
# End Source File
# End Group
# Begin Group "AddressBook"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InterfaceMPAddressBook.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceMPAddressBook.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\MPConnectionError.cpp
# End Source File
# Begin Source File

SOURCE=.\MPConnectionError.h
# End Source File
# Begin Source File

SOURCE=.\MuliplayerToUIConsts.h
# End Source File
# Begin Source File

SOURCE=.\MultiplayerCommandManager.h
# End Source File
# Begin Source File

SOURCE=.\MultiplayerCommandManagerInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiplayerCommandManagerInternal.h
# End Source File
# End Group
# Begin Group "PlayersInterface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PlayersInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayersInterface.h
# End Source File
# End Group
# Begin Group "Options"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InterfaceOptionsSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceOptionsSettings.h
# End Source File
# Begin Source File

SOURCE=.\OptionEntryWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionEntryWrapper.h
# End Source File
# Begin Source File

SOURCE=.\UIOptions.h
# End Source File
# End Group
# Begin Group "UnitPerformance"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InterfaceAfterMissionPopups.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceAfterMissionPopups.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceUnitPerformance.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceUnitPerformance.h
# End Source File
# End Group
# Begin Group "SwitchMode"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InterfaceSwitchModeTo.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceSwitchModeTo.h
# End Source File
# End Group
# Begin Group "NewDepotUpgrades"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InterfaceNewDepotUpgrades.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceNewDepotUpgrades.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AddUnitToMission.cpp
# End Source File
# Begin Source File

SOURCE=.\AddUnitToMission.h
# End Source File
# Begin Source File

SOURCE=.\Campaign.cpp
# End Source File
# Begin Source File

SOURCE=.\Campaign.h
# End Source File
# Begin Source File

SOURCE=.\Chapter.cpp
# End Source File
# Begin Source File

SOURCE=.\Chapter.h
# End Source File
# Begin Source File

SOURCE=.\Common.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonId.h
# End Source File
# Begin Source File

SOURCE=.\encyclopedia.cpp
# End Source File
# Begin Source File

SOURCE=.\encyclopedia.h
# End Source File
# Begin Source File

SOURCE=.\etypes.h
# End Source File
# Begin Source File

SOURCE=.\InterMission.cpp
# End Source File
# Begin Source File

SOURCE=.\InterMission.h
# End Source File
# Begin Source File

SOURCE=.\MainMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\MainMenu.h
# End Source File
# Begin Source File

SOURCE=.\Mission.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission.h
# End Source File
# Begin Source File

SOURCE=.\SingleMedal.cpp
# End Source File
# Begin Source File

SOURCE=.\SingleMedal.h
# End Source File
# Begin Source File

SOURCE=.\Stats.cpp
# End Source File
# Begin Source File

SOURCE=.\Stats.h
# End Source File
# Begin Source File

SOURCE=.\TotalEncyclopedia.cpp
# End Source File
# Begin Source File

SOURCE=.\TotalEncyclopedia.h
# End Source File
# Begin Source File

SOURCE=.\UIState.cpp
# End Source File
# Begin Source File

SOURCE=.\UIState.h
# End Source File
# Begin Source File

SOURCE=.\UnitsPool.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitsPool.h
# End Source File
# Begin Source File

SOURCE=.\UnitTypes.h
# End Source File
# Begin Source File

SOURCE=.\UpgradeUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\UpgradeUnit.h
# End Source File
# End Group
# Begin Group "Mission"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\iMission.h
# End Source File
# Begin Source File

SOURCE=.\iMissionInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\iMissionInternal.h
# End Source File
# Begin Source File

SOURCE=.\MissionInterfaceEscapeMenu.h
# End Source File
# Begin Source File

SOURCE=.\QuitMission.cpp
# End Source File
# Begin Source File

SOURCE=.\QuitMission.h
# End Source File
# End Group
# Begin Group "PlayMovie"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PlayMovieInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayMovieInterface.h
# End Source File
# End Group
# Begin Group "PlayerProfile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InterfaceStartDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceStartDialog.h
# End Source File
# End Group
# Begin Group "MapSettings"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MapSettingsWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\MapSettingsWrapper.h
# End Source File
# End Group
# Begin Group "Popups"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseList.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseList.h
# End Source File
# Begin Source File

SOURCE=.\CustomCampaign.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomCampaign.h
# End Source File
# Begin Source File

SOURCE=.\CustomChapter.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomChapter.h
# End Source File
# Begin Source File

SOURCE=.\CustomList.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomList.h
# End Source File
# Begin Source File

SOURCE=.\CustomMission.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomMission.h
# End Source File
# Begin Source File

SOURCE=.\CutsceneList.cpp
# End Source File
# Begin Source File

SOURCE=.\CutsceneList.h
# End Source File
# Begin Source File

SOURCE=.\IMLoadMission.cpp
# End Source File
# Begin Source File

SOURCE=.\IMLoadMission.h
# End Source File
# Begin Source File

SOURCE=.\IMSaveMission.cpp
# End Source File
# Begin Source File

SOURCE=.\IMSaveMission.h
# End Source File
# Begin Source File

SOURCE=.\IMTutorial.cpp
# End Source File
# Begin Source File

SOURCE=.\IMTutorial.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceIMModsList.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceIMModsList.h
# End Source File
# Begin Source File

SOURCE=.\LoadMission.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadMission.h
# End Source File
# Begin Source File

SOURCE=.\PlayerGainLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerGainLevel.h
# End Source File
# Begin Source File

SOURCE=.\ReplayList.cpp
# End Source File
# Begin Source File

SOURCE=.\ReplayList.h
# End Source File
# Begin Source File

SOURCE=.\SaveLoadCommon.h
# End Source File
# Begin Source File

SOURCE=.\SaveMission.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveMission.h
# End Source File
# Begin Source File

SOURCE=.\SaveReplay.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveReplay.h
# End Source File
# Begin Source File

SOURCE=.\SwitchToNextChapter.cpp
# End Source File
# Begin Source File

SOURCE=.\SwitchToNextChapter.h
# End Source File
# Begin Source File

SOURCE=.\TutorialList.cpp
# End Source File
# Begin Source File

SOURCE=.\TutorialList.h
# End Source File
# End Group
# Begin Group "MessageBox"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InterfaceMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceMessageBox.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\UIConsts.cpp
# End Source File
# Begin Source File

SOURCE=.\UIConsts.h
# End Source File
# Begin Source File

SOURCE=.\UIMapInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMapInfo.h
# End Source File
# End Group
# Begin Group "MessageReaction"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CustomMessageReaction.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomMessageReaction.h
# End Source File
# Begin Source File

SOURCE=.\MessageReaction.h
# End Source File
# Begin Source File

SOURCE=.\MessageReactionINternal.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageReactionINternal.h
# End Source File
# Begin Source File

SOURCE=.\MessageReactionSerialize.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\MissionObjectFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\MissionObjectFactory.h
# End Source File
# End Group
# Begin Group "AckManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AckManager.cpp
# End Source File
# Begin Source File

SOURCE=.\AckManager.h
# End Source File
# End Group
# Begin Group "Resource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameTT.rc
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CutScenesHelper.h
# End Source File
# Begin Source File

SOURCE=.\MinimapCreation.cpp
# End Source File
# Begin Source File

SOURCE=.\MinimapCreation.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\GameTT.def

!IF  "$(CFG)" == "GameTT - Win32 Release"

!ELSEIF  "$(CFG)" == "GameTT - Win32 Debug"

!ELSEIF  "$(CFG)" == "GameTT - Win32 BetaRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GameTT - Win32 FastDebug"

!ELSEIF  "$(CFG)" == "GameTT - Win32 Profiler"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
