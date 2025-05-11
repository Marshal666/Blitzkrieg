# Microsoft Developer Studio Project File - Name="AILogic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AILogic - Win32 Profiler
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AILogic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AILogic.mak" CFG="AILogic - Win32 Profiler"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AILogic - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AILogic - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AILogic - Win32 BetaRelease" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AILogic - Win32 FastDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AILogic - Win32 Profiler" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/AILogic", TFNAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AILogic - Win32 Release"

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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
OutDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AILogic - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_ASSERT_SLOW" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /Yu"StdAfx.h" /FD /GZ /Zm400 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
OutDir=.\Debug
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AILogic - Win32 BetaRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AILogic___Win32_BetaRelease"
# PROP BASE Intermediate_Dir "AILogic___Win32_BetaRelease"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BetaRelease"
# PROP Intermediate_Dir "BetaRelease"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
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
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /def:".\AILogic.def" /FIXED:NO
# Begin Special Build Tool
OutDir=.\BetaRelease
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AILogic - Win32 FastDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AILogic___Win32_FastDebug"
# PROP BASE Intermediate_Dir "AILogic___Win32_FastDebug"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FastDebug"
# PROP Intermediate_Dir "FastDebug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_ASSERT_SLOW" /D "WIN32" /D "_DEBUG" /D "_STL_FAST_DEBUG" /FR /Yu"StdAfx.h" /FD /GZ /Zm170 /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "_DO_ASSERT_SLOW" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /D "_HASHMAP_OPERATOR_SKOBKI_INSERT" /Yu"StdAfx.h" /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
OutDir=.\FastDebug
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AILogic - Win32 Profiler"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AILogic___Win32_Profiler"
# PROP BASE Intermediate_Dir "AILogic___Win32_Profiler"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Profiler"
# PROP Intermediate_Dir "Profiler"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "_DO_ASSERT_SLOW" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /D "_HASHMAP_OPERATOR_SKOBKI_INSERT" /Yu"StdAfx.h" /FD /GZ /Zm170 /c
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
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib vtuneapi.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /def:".\AILogic.def" /pdbtype:sept /fixed:no
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "AILogic - Win32 Release"
# Name "AILogic - Win32 Debug"
# Name "AILogic - Win32 BetaRelease"
# Name "AILogic - Win32 FastDebug"
# Name "AILogic - Win32 Profiler"
# Begin Group "Common"

# PROP Default_Filter ""
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
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AIClassesID.h
# End Source File
# Begin Source File

SOURCE=.\AILogic.h
# End Source File
# Begin Source File

SOURCE=.\AILogicObjectFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\AILogicObjectFactory.h
# End Source File
# Begin Source File

SOURCE=.\AITypes.h
# End Source File
# Begin Source File

SOURCE=.\DifficultyLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\DifficultyLevel.h
# End Source File
# End Group
# Begin Group "AILogic"

# PROP Default_Filter ""
# Begin Group "WarFog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AIWarFog.cpp
# End Source File
# Begin Source File

SOURCE=.\AIWarFog.h
# End Source File
# Begin Source File

SOURCE=.\WarFogSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\WarFogTracer.h
# End Source File
# End Group
# Begin Group "PathFinding"

# PROP Default_Filter ""
# Begin Group "PathUnits"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PathUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\PathUnit.h
# End Source File
# Begin Source File

SOURCE=.\PathUnitSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\TrainPathUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\TrainPathUnit.h
# End Source File
# End Group
# Begin Group "Collisions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Collision.h
# End Source File
# Begin Source File

SOURCE=.\CollisionInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\CollisionInternal.h
# End Source File
# Begin Source File

SOURCE=.\CollisionInternalSerialize.cpp
# End Source File
# End Group
# Begin Group "Paths"

# PROP Default_Filter ""
# Begin Group "StandartPath"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StandartPath.cpp
# End Source File
# Begin Source File

SOURCE=.\StandartPath.h
# End Source File
# Begin Source File

SOURCE=.\StandartSmoothMechPath.cpp
# End Source File
# Begin Source File

SOURCE=.\StandartSmoothMechPath.h
# End Source File
# Begin Source File

SOURCE=.\StandartSmoothSoldierPath.cpp
# End Source File
# Begin Source File

SOURCE=.\StandartSmoothSoldierPath.h
# End Source File
# End Group
# Begin Group "PlanePath"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PlanePath.cpp
# End Source File
# Begin Source File

SOURCE=.\PlanePath.h
# End Source File
# End Group
# Begin Group "ArtilleryPaths"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ArtilleryPaths.cpp
# End Source File
# Begin Source File

SOURCE=.\ArtilleryPaths.h
# End Source File
# End Group
# Begin Group "ParatrooperPath"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ParatrooperPath.cpp
# End Source File
# Begin Source File

SOURCE=.\ParatrooperPath.h
# End Source File
# End Group
# Begin Group "PresizePath"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PresizePath.cpp
# End Source File
# Begin Source File

SOURCE=.\PresizePath.h
# End Source File
# End Group
# Begin Group "TrainPath"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TrainPath.cpp
# End Source File
# Begin Source File

SOURCE=.\TrainPath.h
# End Source File
# End Group
# Begin Group "TankPitPath"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TankPitPath.cpp
# End Source File
# Begin Source File

SOURCE=.\TankPitPath.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Path.h
# End Source File
# Begin Source File

SOURCE=.\PathInternalSerialize.cpp
# End Source File
# End Group
# Begin Group "PathFinders"

# PROP Default_Filter ""
# Begin Group "StandartPathFinder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PathFinderInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\PathFinderInternal.h
# End Source File
# End Group
# Begin Group "TrainPathFinder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TrainPathFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\TrainPathFinder.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\PathFinder.h
# End Source File
# Begin Source File

SOURCE=.\PathFindersSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\PathSearchFuncs.cpp
# End Source File
# Begin Source File

SOURCE=.\PointChecking.cpp
# End Source File
# Begin Source File

SOURCE=.\PointChecking.h
# End Source File
# End Group
# End Group
# Begin Group "Commands"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Commands.cpp
# End Source File
# Begin Source File

SOURCE=.\Commands.h
# End Source File
# Begin Source File

SOURCE=.\CommandsSerialize.cpp
# End Source File
# End Group
# Begin Group "Guns"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Guns.cpp
# End Source File
# Begin Source File

SOURCE=.\Guns.h
# End Source File
# Begin Source File

SOURCE=.\GunsInternal.h
# End Source File
# Begin Source File

SOURCE=.\GunsSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\HitsStore.cpp
# End Source File
# Begin Source File

SOURCE=.\HitsStore.h
# End Source File
# Begin Source File

SOURCE=.\HitsStoreSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\MountedGun.cpp
# End Source File
# Begin Source File

SOURCE=.\MountedGun.h
# End Source File
# Begin Source File

SOURCE=.\MountedGunsSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\Shell.cpp
# End Source File
# Begin Source File

SOURCE=.\Shell.h
# End Source File
# Begin Source File

SOURCE=.\ShellSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\Turret.cpp
# End Source File
# Begin Source File

SOURCE=.\Turret.h
# End Source File
# Begin Source File

SOURCE=.\TurretSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitGuns.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitGuns.h
# End Source File
# End Group
# Begin Group "GroupLogic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GridCreation.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCreation.h
# End Source File
# Begin Source File

SOURCE=.\GroupLogic.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupLogic.h
# End Source File
# Begin Source File

SOURCE=.\GroupLogicSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupUnit.h
# End Source File
# Begin Source File

SOURCE=.\SegmentedObjects.h
# End Source File
# Begin Source File

SOURCE=.\UnitsSegments.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitsSegments.h
# End Source File
# End Group
# Begin Group "Units"

# PROP Default_Filter ""
# Begin Group "Behaviour"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Behaviour.cpp
# End Source File
# Begin Source File

SOURCE=.\Behaviour.h
# End Source File
# Begin Source File

SOURCE=.\BehaviourSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\FreeFireManager.cpp
# End Source File
# Begin Source File

SOURCE=.\FreeFireManager.h
# End Source File
# Begin Source File

SOURCE=.\FreeFireManagerSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\RndRunUpToEnemy.cpp
# End Source File
# Begin Source File

SOURCE=.\RndRunUpToEnemy.h
# End Source File
# End Group
# Begin Group "UnitTypes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Artillery.cpp
# End Source File
# Begin Source File

SOURCE=.\Artillery.h
# End Source File
# Begin Source File

SOURCE=.\Aviation.cpp
# End Source File
# Begin Source File

SOURCE=.\Aviation.h
# End Source File
# Begin Source File

SOURCE=.\Soldier.cpp
# End Source File
# Begin Source File

SOURCE=.\Soldier.h
# End Source File
# Begin Source File

SOURCE=.\Technics.cpp
# End Source File
# Begin Source File

SOURCE=.\Technics.h
# End Source File
# End Group
# Begin Group "AnimUnit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AnimUnit.h
# End Source File
# Begin Source File

SOURCE=.\AnimUnitMech.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimUnitMech.h
# End Source File
# Begin Source File

SOURCE=.\AnimUnitSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimUnitSoldier.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimUnitSoldier.h
# End Source File
# End Group
# Begin Group "UnitsContainer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Units.cpp
# End Source File
# Begin Source File

SOURCE=.\Units.h
# End Source File
# Begin Source File

SOURCE=.\UnitsIterators.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitsIterators.h
# End Source File
# Begin Source File

SOURCE=.\UnitsIterators2.h
# End Source File
# Begin Source File

SOURCE=.\UnitsSerialize.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AIUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\AIUnit.h
# End Source File
# Begin Source File

SOURCE=.\AIUnitInfoForGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\AIUnitInfoForGeneral.h
# End Source File
# Begin Source File

SOURCE=.\AIUnitSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\BasePathUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\BasePathUnit.h
# End Source File
# Begin Source File

SOURCE=.\CommonUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonUnit.h
# End Source File
# Begin Source File

SOURCE=.\QueueUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\QueueUnit.h
# End Source File
# Begin Source File

SOURCE=.\ScanLimiter.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanLimiter.h
# End Source File
# End Group
# Begin Group "AILogicInternal"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AIEditorInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\AIEditorInternal.h
# End Source File
# Begin Source File

SOURCE=.\AIEditorSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\AILogicInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\AILogicInternal.h
# End Source File
# Begin Source File

SOURCE=.\AILogicSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\Cheats.cpp
# End Source File
# Begin Source File

SOURCE=.\Cheats.h
# End Source File
# Begin Source File

SOURCE=.\GlobalObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobalObjects.h
# End Source File
# Begin Source File

SOURCE=.\StaticMembers.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticMembers.h
# End Source File
# End Group
# Begin Group "AIStaticMap"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AIStaticMap.cpp
# End Source File
# Begin Source File

SOURCE=.\AIStaticMap.h
# End Source File
# Begin Source File

SOURCE=.\AIStaticMapSerialize.cpp
# End Source File
# End Group
# Begin Group "AITools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AICellsTiles.h
# End Source File
# Begin Source File

SOURCE=.\AIGeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\AIGeometry.h
# End Source File
# Begin Source File

SOURCE=.\AIGeometryDebug.cpp
# End Source File
# Begin Source File

SOURCE=.\BetaSpline3D.cpp
# End Source File
# Begin Source File

SOURCE=.\BetaSpline3D.h
# End Source File
# Begin Source File

SOURCE=.\CLockWithUnlockPossibilities.cpp
# End Source File
# Begin Source File

SOURCE=.\CLockWithUnlockPossibilities.h
# End Source File
# Begin Source File

SOURCE=.\Heap.h
# End Source File
# Begin Source File

SOURCE=.\ListsSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ListsSet.h
# End Source File
# Begin Source File

SOURCE=.\MemoryConsumeCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\MemoryConsumeCheck.h
# End Source File
# Begin Source File

SOURCE=.\MPLog.h
# End Source File
# Begin Source File

SOURCE=.\Probability.cpp
# End Source File
# Begin Source File

SOURCE=.\Probability.h
# End Source File
# Begin Source File

SOURCE=.\Randomize.h
# End Source File
# Begin Source File

SOURCE=.\RectTiles.cpp
# End Source File
# Begin Source File

SOURCE=.\RectTiles.h
# End Source File
# Begin Source File

SOURCE=.\SaveDBID.h
# End Source File
# Begin Source File

SOURCE=.\TimeCounter.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeCounter.h
# End Source File
# Begin Source File

SOURCE=.\Trigonometry.cpp
# End Source File
# Begin Source File

SOURCE=.\Trigonometry.h
# End Source File
# Begin Source File

SOURCE=.\ValidObjectCheck.h
# End Source File
# End Group
# Begin Group "Scripts"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Scripts\Scripts.cpp
# End Source File
# Begin Source File

SOURCE=.\Scripts\Scripts.h
# End Source File
# Begin Source File

SOURCE=.\ScriptsSerialize.cpp
# End Source File
# End Group
# Begin Group "Updater"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AAFeedBacks.cpp
# End Source File
# Begin Source File

SOURCE=.\AAFeedBacks.h
# End Source File
# Begin Source File

SOURCE=.\SuspendedUpdates.cpp
# End Source File
# Begin Source File

SOURCE=.\SuspendedUpdates.h
# End Source File
# Begin Source File

SOURCE=.\SuspendedUpdatesSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdatableObject.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdatableObject.h
# End Source File
# Begin Source File

SOURCE=.\Updater.cpp
# End Source File
# Begin Source File

SOURCE=.\Updater.h
# End Source File
# Begin Source File

SOURCE=.\UpdaterSerialize.cpp
# End Source File
# End Group
# Begin Group "LinkObjects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LinkObject.cpp
# End Source File
# Begin Source File

SOURCE=.\LinkObject.h
# End Source File
# Begin Source File

SOURCE=.\LinkObjectSerialize.cpp
# End Source File
# End Group
# Begin Group "Formation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Formation.cpp
# End Source File
# Begin Source File

SOURCE=.\Formation.h
# End Source File
# Begin Source File

SOURCE=.\FormationSerialize.cpp
# End Source File
# End Group
# Begin Group "Diplomacy"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Diplomacy.cpp
# End Source File
# Begin Source File

SOURCE=.\Diplomacy.h
# End Source File
# End Group
# Begin Group "UnitsStates"

# PROP Default_Filter ""
# Begin Group "SoldierStates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InBuildingStates.cpp
# End Source File
# Begin Source File

SOURCE=.\InBuildingStates.h
# End Source File
# Begin Source File

SOURCE=.\InEntrenchmentStates.cpp
# End Source File
# Begin Source File

SOURCE=.\InEntrenchmentStates.h
# End Source File
# Begin Source File

SOURCE=.\InTransportStates.cpp
# End Source File
# Begin Source File

SOURCE=.\InTransportStates.h
# End Source File
# Begin Source File

SOURCE=.\SoldierStates.cpp
# End Source File
# Begin Source File

SOURCE=.\SoldierStates.h
# End Source File
# Begin Source File

SOURCE=.\SoldierStatesSerialize.cpp
# End Source File
# End Group
# Begin Group "PlaneStates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PlaneStates.cpp
# End Source File
# Begin Source File

SOURCE=.\PlaneStates.h
# End Source File
# Begin Source File

SOURCE=.\PlaneStatesSerialize.cpp
# End Source File
# End Group
# Begin Group "TankStates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TankStates.cpp
# End Source File
# Begin Source File

SOURCE=.\TankStates.h
# End Source File
# Begin Source File

SOURCE=.\TankStatesSerialize.cpp
# End Source File
# End Group
# Begin Group "TransportStates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TransportEngineerStates.cpp
# End Source File
# Begin Source File

SOURCE=.\TransportStates.cpp
# End Source File
# Begin Source File

SOURCE=.\TransportStates.h
# End Source File
# Begin Source File

SOURCE=.\TransportStatesSerialize.cpp
# End Source File
# End Group
# Begin Group "CommonStates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CommonStates.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonStates.h
# End Source File
# Begin Source File

SOURCE=.\CommonStatesSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\SerializeOwner.h
# End Source File
# End Group
# Begin Group "FormationStates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FormationEngineerStates.cpp
# End Source File
# Begin Source File

SOURCE=.\FormationStates.cpp
# End Source File
# Begin Source File

SOURCE=.\FormationStates.h
# End Source File
# Begin Source File

SOURCE=.\FormationStatesSerialize.cpp
# End Source File
# End Group
# Begin Group "ArtilleryStates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ArtilleryStates.cpp
# End Source File
# Begin Source File

SOURCE=.\ArtilleryStates.h
# End Source File
# Begin Source File

SOURCE=.\ArtilleryStatesSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\ArtRocketStates.cpp
# End Source File
# Begin Source File

SOURCE=.\ArtRocketStates.h
# End Source File
# Begin Source File

SOURCE=.\ArtRocketStatesSerialize.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\StatesFactory.h
# End Source File
# Begin Source File

SOURCE=.\TechnicsStates.h
# End Source File
# Begin Source File

SOURCE=.\TechnicStates.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitStates.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitStates.h
# End Source File
# End Group
# Begin Group "ObjectsCreation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EntrenchmentCreation.cpp
# End Source File
# Begin Source File

SOURCE=.\EntrenchmentCreation.h
# End Source File
# Begin Source File

SOURCE=.\UnitCreation.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitCreation.h
# End Source File
# End Group
# Begin Group "AntiArtillery"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AntiArtillery.cpp
# End Source File
# Begin Source File

SOURCE=.\AntiArtillery.h
# End Source File
# Begin Source File

SOURCE=.\AntiArtilleryManager.cpp
# End Source File
# Begin Source File

SOURCE=.\AntiArtilleryManager.h
# End Source File
# Begin Source File

SOURCE=.\AntiArtillerySerialize.cpp
# End Source File
# End Group
# Begin Group "Acknowledgments"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AckManager.cpp
# End Source File
# Begin Source File

SOURCE=.\AckManager.h
# End Source File
# End Group
# Begin Group "Consts"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AIConsts.cpp
# End Source File
# Begin Source File

SOURCE=.\aiconsts.h
# End Source File
# Begin Source File

SOURCE=.\AIInternalConsts.h
# End Source File
# End Group
# Begin Group "ShootEstimators"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DamageToEnemyUpdater.cpp
# End Source File
# Begin Source File

SOURCE=.\DamageToEnemyUpdater.h
# End Source File
# Begin Source File

SOURCE=.\ShootEstimator.h
# End Source File
# Begin Source File

SOURCE=.\ShootEstimatorInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\ShootEstimatorInternal.h
# End Source File
# Begin Source File

SOURCE=.\ShootEstimatorSerialize.cpp
# End Source File
# End Group
# Begin Group "CombatEstimator"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CombatEstimator.cpp
# End Source File
# Begin Source File

SOURCE=.\CombatEstimator.h
# End Source File
# End Group
# Begin Group "Statistics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Statistics.cpp
# End Source File
# Begin Source File

SOURCE=.\Statistics.h
# End Source File
# End Group
# Begin Group "General"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Commander.cpp
# End Source File
# Begin Source File

SOURCE=.\Commander.h
# End Source File
# Begin Source File

SOURCE=.\EnemyRememberer.cpp
# End Source File
# Begin Source File

SOURCE=.\EnemyRememberer.h
# End Source File
# Begin Source File

SOURCE=.\General.h
# End Source File
# Begin Source File

SOURCE=.\GeneralAirForce.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralAirForce.h
# End Source File
# Begin Source File

SOURCE=.\GeneralArtillery.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralArtillery.h
# End Source File
# Begin Source File

SOURCE=.\GeneralConsts.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralConsts.h
# End Source File
# Begin Source File

SOURCE=.\GeneralHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralHelper.h
# End Source File
# Begin Source File

SOURCE=.\GeneralIntendant.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralIntendant.h
# End Source File
# Begin Source File

SOURCE=.\GeneralInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralInternal.h
# End Source File
# Begin Source File

SOURCE=.\GeneralInternalInterfaces.h
# End Source File
# Begin Source File

SOURCE=.\GeneralSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralTasks.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralTasks.h
# End Source File
# Begin Source File

SOURCE=.\Resistance.cpp
# End Source File
# Begin Source File

SOURCE=.\Resistance.h
# End Source File
# Begin Source File

SOURCE=.\SupremeBeing.cpp
# End Source File
# End Group
# Begin Group "Railroad"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Graph.cpp
# End Source File
# Begin Source File

SOURCE=.\Graph.h
# End Source File
# Begin Source File

SOURCE=.\GraphSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\RailroadGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\RailroadGraph.h
# End Source File
# Begin Source File

SOURCE=.\RailroadsSerialize.cpp
# End Source File
# End Group
# Begin Group "Obstacle"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Obstacle.h
# End Source File
# Begin Source File

SOURCE=.\ObstacleInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\ObstacleInternal.h
# End Source File
# Begin Source File

SOURCE=.\ObstaclesSerialize.cpp
# End Source File
# End Group
# Begin Group "StaticObjects"

# PROP Default_Filter ""
# Begin Group "StaticObjectsContainer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StaticObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticObjects.h
# End Source File
# Begin Source File

SOURCE=.\StaticObjectsIters.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticObjectsIters.h
# End Source File
# End Group
# Begin Group "StaticObjectTypes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ArtilleryBulletStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\ArtilleryBulletStorage.h
# End Source File
# Begin Source File

SOURCE=.\Bridge.cpp
# End Source File
# Begin Source File

SOURCE=.\Bridge.h
# End Source File
# Begin Source File

SOURCE=.\Building.cpp
# End Source File
# Begin Source File

SOURCE=.\Building.h
# End Source File
# Begin Source File

SOURCE=.\Entrenchment.cpp
# End Source File
# Begin Source File

SOURCE=.\Entrenchment.h
# End Source File
# Begin Source File

SOURCE=.\Fence.cpp
# End Source File
# Begin Source File

SOURCE=.\Fence.h
# End Source File
# Begin Source File

SOURCE=.\Flag.cpp
# End Source File
# Begin Source File

SOURCE=.\Flag.h
# End Source File
# Begin Source File

SOURCE=.\Mine.cpp
# End Source File
# Begin Source File

SOURCE=.\Mine.h
# End Source File
# Begin Source File

SOURCE=.\RotatingFireplacesObject.cpp
# End Source File
# Begin Source File

SOURCE=.\RotatingFireplacesObject.h
# End Source File
# Begin Source File

SOURCE=.\SmokeScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\SmokeScreen.h
# End Source File
# Begin Source File

SOURCE=.\StaticObject.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticObject.h
# End Source File
# Begin Source File

SOURCE=.\StaticObjectSlotInfo.h
# End Source File
# Begin Source File

SOURCE=.\StormableObject.cpp
# End Source File
# Begin Source File

SOURCE=.\StormableObject.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\StaticObjectsSerialize.cpp
# End Source File
# End Group
# Begin Group "Multiplayer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MultiplayerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiplayerInfo.h
# End Source File
# End Group
# Begin Group "Weather"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Weather.cpp
# End Source File
# Begin Source File

SOURCE=.\Weather.h
# End Source File
# End Group
# Begin Group "Graveyard"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Graveyard.cpp
# End Source File
# Begin Source File

SOURCE=.\Graveyard.h
# End Source File
# Begin Source File

SOURCE=.\GraveyardSerialize.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AIHashFuncs.cpp
# End Source File
# Begin Source File

SOURCE=.\AIHashFuncs.h
# End Source File
# End Group
# Begin Group "Resource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AILogic.rc
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AILogic.def

!IF  "$(CFG)" == "AILogic - Win32 Release"

!ELSEIF  "$(CFG)" == "AILogic - Win32 Debug"

!ELSEIF  "$(CFG)" == "AILogic - Win32 BetaRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "AILogic - Win32 FastDebug"

!ELSEIF  "$(CFG)" == "AILogic - Win32 Profiler"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
