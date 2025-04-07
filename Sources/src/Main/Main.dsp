# Microsoft Developer Studio Project File - Name="Main" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Main - Win32 Profiler
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Main.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Main.mak" CFG="Main - Win32 Profiler"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Main - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Main - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Main - Win32 BetaRelease" (based on "Win32 (x86) Static Library")
!MESSAGE "Main - Win32 FastDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "Main - Win32 Profiler" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/Main", NULAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Main - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "_FINALRELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /Zm200 /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Main - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_ASSERT_SLOW" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /Yu"StdAfx.h" /FD /GZ /Zm200 /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Main - Win32 BetaRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Main___Win32_BetaRelease"
# PROP BASE Intermediate_Dir "Main___Win32_BetaRelease"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BetaRelease"
# PROP Intermediate_Dir "BetaRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_DO_ASSERT_SLOW" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /Ot /Og /Op /Ob2 /D "_DO_ASSERT_SLOW" /D "_BETARELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /Zm200 /c
# SUBTRACT CPP /Ox /Oi
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Main - Win32 FastDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Main___Win32_FastDebug"
# PROP BASE Intermediate_Dir "Main___Win32_FastDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FastDebug"
# PROP Intermediate_Dir "FastDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_ASSERT_SLOW" /D "WIN32" /D "_DEBUG" /D "_STL_FAST_DEBUG" /Yu"StdAfx.h" /FD /GZ /Zm200 /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "_DO_ASSERT_SLOW" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /GZ /Zm200 /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Main - Win32 Profiler"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Main___Win32_Profiler"
# PROP BASE Intermediate_Dir "Main___Win32_Profiler"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Profiler"
# PROP Intermediate_Dir "Profiler"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "_DO_ASSERT_SLOW" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /GZ /Zm200 /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_FINALRELEASE" /D "_PROFILER" /Yu"StdAfx.h" /FD /Zm200 /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Main - Win32 Release"
# Name "Main - Win32 Debug"
# Name "Main - Win32 BetaRelease"
# Name "Main - Win32 FastDebug"
# Name "Main - Win32 Profiler"
# Begin Group "Common"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h;hpp;hxx;hm;inl"
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
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\iMain.h
# End Source File
# Begin Source File

SOURCE=.\iMainClassIDs.h
# End Source File
# Begin Source File

SOURCE=.\iMainCommands.h
# End Source File
# Begin Source File

SOURCE=.\iMainInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\iMainInternal.h
# End Source File
# Begin Source File

SOURCE=.\MainLoopCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\MainLoopCommands.h
# End Source File
# Begin Source File

SOURCE=.\MainObjectFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\MainObjectFactory.h
# End Source File
# Begin Source File

SOURCE=.\RandomMapHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\RandomMapHelper.h
# End Source File
# End Group
# Begin Group "Timer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameTimer.h
# End Source File
# Begin Source File

SOURCE=.\GameTimerInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\GameTimerInternal.h
# End Source File
# End Group
# Begin Group "GDB"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameDB.cpp
# End Source File
# Begin Source File

SOURCE=.\GameDB.h
# End Source File
# Begin Source File

SOURCE=.\GameStats.cpp
# End Source File
# Begin Source File

SOURCE=.\GameStats.h
# End Source File
# Begin Source File

SOURCE=.\RPGStats.cpp
# End Source File
# Begin Source File

SOURCE=.\RPGStats.h
# End Source File
# End Group
# Begin Group "Other"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EmergencySave.h
# End Source File
# Begin Source File

SOURCE=.\FilesInspector.cpp
# End Source File
# Begin Source File

SOURCE=.\FilesInspector.h
# End Source File
# Begin Source File

SOURCE=.\InitGlobalVarConsts.cpp
# End Source File
# Begin Source File

SOURCE=.\Initialization.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadDLLs.cpp
# End Source File
# End Group
# Begin Group "Text"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TextManager.cpp
# End Source File
# Begin Source File

SOURCE=.\TextManager.h
# End Source File
# Begin Source File

SOURCE=.\TextObject.cpp
# End Source File
# Begin Source File

SOURCE=.\TextObject.h
# End Source File
# Begin Source File

SOURCE=.\TextSystem.h
# End Source File
# End Group
# Begin Group "Transceiver"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AILogicCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\AILogicCommand.h
# End Source File
# Begin Source File

SOURCE=.\AILogicCommandInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\AILogicCommandInternal.h
# End Source File
# Begin Source File

SOURCE=.\MultiPlayerTransceiver.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiPlayerTransceiver.h
# End Source File
# Begin Source File

SOURCE=.\SinglePlayerTransceiver.cpp
# End Source File
# Begin Source File

SOURCE=.\SinglePlayerTransceiver.h
# End Source File
# Begin Source File

SOURCE=.\Transceiver.h
# End Source File
# End Group
# Begin Group "Multiplayer"

# PROP Default_Filter ""
# Begin Group "Messages"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ChatMessages.cpp
# End Source File
# Begin Source File

SOURCE=.\ChatMessages.h
# End Source File
# Begin Source File

SOURCE=.\GameCreationMessages.cpp
# End Source File
# Begin Source File

SOURCE=.\GameCreationMessages.h
# End Source File
# Begin Source File

SOURCE=.\Messages.h
# End Source File
# Begin Source File

SOURCE=.\MessagesStore.cpp
# End Source File
# Begin Source File

SOURCE=.\MessagesStore.h
# End Source File
# Begin Source File

SOURCE=.\ServersListMessages.cpp
# End Source File
# Begin Source File

SOURCE=.\ServersListMessages.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\assert.cpp
# End Source File
# Begin Source File

SOURCE=.\GameCreation.cpp
# End Source File
# Begin Source File

SOURCE=.\GameCreation.h
# End Source File
# Begin Source File

SOURCE=.\GameCreationInterfaces.h
# End Source File
# Begin Source File

SOURCE=.\GamePlaying.cpp
# End Source File
# Begin Source File

SOURCE=.\GamePlaying.h
# End Source File
# Begin Source File

SOURCE=.\GameSpyChat.cpp
# End Source File
# Begin Source File

SOURCE=.\GameSpyChat.h
# End Source File
# Begin Source File

SOURCE=.\GameSpyPeerChat.cpp
# End Source File
# Begin Source File

SOURCE=.\GameSpyPeerChat.h
# End Source File
# Begin Source File

SOURCE=.\LanChat.cpp
# End Source File
# Begin Source File

SOURCE=.\LanChat.h
# End Source File
# Begin Source File

SOURCE=.\Multiplayer.h
# End Source File
# Begin Source File

SOURCE=.\MultiplayerConsts.h
# End Source File
# Begin Source File

SOURCE=.\MultiplayerInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiplayerInternal.h
# End Source File
# Begin Source File

SOURCE=.\NetMessages.h
# End Source File
# Begin Source File

SOURCE=.\ServerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerInfo.h
# End Source File
# Begin Source File

SOURCE=.\ServersList.cpp
# End Source File
# Begin Source File

SOURCE=.\ServersList.h
# End Source File
# End Group
# Begin Group "CommandsHistory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CommandsHistory.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandsHistory.h
# End Source File
# Begin Source File

SOURCE=.\CommandsHistoryInterface.h
# End Source File
# Begin Source File

SOURCE=.\SaveCommandsHistoryCommand.h
# End Source File
# End Group
# Begin Group "Scenario Tracker"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PlayerScenarioInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerScenarioInfo.h
# End Source File
# Begin Source File

SOURCE=.\PlayerSkill.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerSkill.h
# End Source File
# Begin Source File

SOURCE=.\ScenarioStatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\ScenarioStatistics.h
# End Source File
# Begin Source File

SOURCE=.\ScenarioTracker.h
# End Source File
# Begin Source File

SOURCE=.\ScenarioTracker2Internal.cpp
# End Source File
# Begin Source File

SOURCE=.\ScenarioTracker2Internal.h
# End Source File
# Begin Source File

SOURCE=.\ScenarioTrackerTypes.h
# End Source File
# Begin Source File

SOURCE=.\UserProfile.cpp
# End Source File
# Begin Source File

SOURCE=.\UserProfile.h
# End Source File
# End Group
# Begin Group "Beta Protection"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BetaKey.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\todo.txt
# End Source File
# End Target
# End Project
