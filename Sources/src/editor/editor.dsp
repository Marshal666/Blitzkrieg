# Microsoft Developer Studio Project File - Name="editor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=editor - Win32 Profiler
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "editor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "editor.mak" CFG="editor - Win32 Profiler"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "editor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "editor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "editor - Win32 BetaRelease" (based on "Win32 (x86) Application")
!MESSAGE "editor - Win32 FastDebug" (based on "Win32 (x86) Application")
!MESSAGE "editor - Win32 Profiler" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/editor", AJMAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "editor - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "COI" /D "_AFXDLL" /D "__AFX__" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D "_FINALRELEASE" /Yu"StdAfx.h" /FD /Zm200 /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib winmm.lib comsupp.lib Shlwapi.lib /nologo /subsystem:windows /pdb:none /machine:I386 /out:"Release/reseditor.exe"
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
OutDir=.\Release
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.exe c:\a7\*.*	call s:\soft\copydll.bat $(WkspDir) Release
# End Special Build Tool

!ELSEIF  "$(CFG)" == "editor - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "COI" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /Yu"StdAfx.h" /FD /I /GZ /Zm200 /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib winmm.lib comsupp.lib Shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/reseditor.exe" /pdbtype:sept
# Begin Special Build Tool
OutDir=.\Debug
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.exe c:\a7\*.*	call s:\soft\copydll.bat $(WkspDir) Debug
# End Special Build Tool

!ELSEIF  "$(CFG)" == "editor - Win32 BetaRelease"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "editor___Win32_BetaRelease"
# PROP BASE Intermediate_Dir "editor___Win32_BetaRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BetaRelease"
# PROP Intermediate_Dir "BetaRelease"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /I "COI" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /Ot /Og /Op /Ob2 /I "COI" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D "_BETARELEASE" /Yu"StdAfx.h" /FD /Zm200 /c
# SUBTRACT CPP /Ox /Oi /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib winmm.lib comsupp.lib Shlwapi.lib /nologo /subsystem:windows /pdb:none /debug /machine:I386 /out:"BetaRelease/reseditor.exe"
# Begin Special Build Tool
OutDir=.\BetaRelease
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.exe c:\a7\*.*	call s:\soft\copydll.bat $(WkspDir) BetaRelease
# End Special Build Tool

!ELSEIF  "$(CFG)" == "editor - Win32 FastDebug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "editor___Win32_FastDebug"
# PROP BASE Intermediate_Dir "editor___Win32_FastDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FastDebug"
# PROP Intermediate_Dir "FastDebug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "COI" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /D "WIN32" /D "_DEBUG" /D "_STL_FAST_DEBUG" /FR"" /Yu"StdAfx.h" /FD /I /GZ /Zm200 /c
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /Zi /Od /I "COI" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /D "_DEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /I /GZ /Zm200 /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib winmm.lib comsupp.lib Shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /out:"FastDebug/reseditor.exe" /pdbtype:sept
# Begin Special Build Tool
OutDir=.\FastDebug
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.exe c:\a7\*.*	call s:\soft\copydll.bat $(WkspDir) FastDebug
# End Special Build Tool

!ELSEIF  "$(CFG)" == "editor - Win32 Profiler"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "editor___Win32_Profiler"
# PROP BASE Intermediate_Dir "editor___Win32_Profiler"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Profiler"
# PROP Intermediate_Dir "Profiler"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "COI" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /D "_DEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /I /GZ /Zm200 /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /Zi /O2 /I "COI" /D "_AFXDLL" /D "__AFX__" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_FINALRELEASE" /Yu"StdAfx.h" /FD /I /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 version.lib winmm.lib comsupp.lib Shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /out:"FastDebug/reseditor.exe" /pdbtype:sept
# ADD LINK32 version.lib winmm.lib comsupp.lib Shlwapi.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"FastDebug/reseditor.exe" /pdbtype:sept
# Begin Special Build Tool
OutDir=.\Profiler
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.exe c:\a7\*.*	call s:\soft\copydll.bat $(WkspDir) Profiler
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "editor - Win32 Release"
# Name "editor - Win32 Debug"
# Name "editor - Win32 BetaRelease"
# Name "editor - Win32 FastDebug"
# Name "editor - Win32 Profiler"
# Begin Group "Editor"

# PROP Default_Filter ""
# Begin Group "Frames"

# PROP Default_Filter ""
# Begin Group "Animations Frame"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AnimationFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimationFrm.h
# End Source File
# Begin Source File

SOURCE=.\AnimationView.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimationView.h
# End Source File
# Begin Source File

SOURCE=.\AnimTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimTreeItem.h
# End Source File
# End Group
# Begin Group "GUI Frame"

# PROP Default_Filter ""
# Begin Group "TemplateTree"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TemplateTree.cpp
# End Source File
# Begin Source File

SOURCE=.\TemplateTree.h
# End Source File
# Begin Source File

SOURCE=.\TemplateTreeDock.cpp
# End Source File
# Begin Source File

SOURCE=.\TemplateTreeDock.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\GUIFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\GUIFrame.h
# End Source File
# Begin Source File

SOURCE=.\GUIFrame2.cpp
# End Source File
# Begin Source File

SOURCE=.\GUITreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\GUITreeItem.h
# End Source File
# Begin Source File

SOURCE=.\GUIundo.cpp
# End Source File
# Begin Source File

SOURCE=.\GUIundo.h
# End Source File
# Begin Source File

SOURCE=.\GUIView.cpp
# End Source File
# Begin Source File

SOURCE=.\GUIView.h
# End Source File
# End Group
# Begin Group "Sprite Compose Frame"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SpriteFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SpriteFrm.h
# End Source File
# Begin Source File

SOURCE=.\SpriteTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\SpriteTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\SpriteView.cpp
# End Source File
# Begin Source File

SOURCE=.\SpriteView.h
# End Source File
# End Group
# Begin Group "Effects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EffectFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\EffectFrm.h
# End Source File
# Begin Source File

SOURCE=.\EffectView.cpp
# End Source File
# Begin Source File

SOURCE=.\EffectView.h
# End Source File
# Begin Source File

SOURCE=.\EffTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\EffTreeItem.h
# End Source File
# End Group
# Begin Group "Object Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObjectFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectFrm.h
# End Source File
# Begin Source File

SOURCE=.\ObjectView.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectView.h
# End Source File
# Begin Source File

SOURCE=.\ObjTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjTreeItem.h
# End Source File
# End Group
# Begin Group "Mesh Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MeshFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshFrm.h
# End Source File
# Begin Source File

SOURCE=.\MeshTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\MeshView.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshView.h
# End Source File
# End Group
# Begin Group "Weapon Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WeaponFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\WeaponFrm.h
# End Source File
# Begin Source File

SOURCE=.\WeaponTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\WeaponTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\WeaponView.cpp
# End Source File
# Begin Source File

SOURCE=.\WeaponView.h
# End Source File
# End Group
# Begin Group "Building Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BuildDirExp.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildFire.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildFrm.h
# End Source File
# Begin Source File

SOURCE=.\BuildShoot.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildSmoke.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\BuildView.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildView.h
# End Source File
# Begin Source File

SOURCE=.\GridFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\GridFrm.h
# End Source File
# End Group
# Begin Group "TileSet Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\test.cpp
# End Source File
# Begin Source File

SOURCE=.\TileSetFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\TileSetFrm.h
# End Source File
# Begin Source File

SOURCE=.\TileSetView.cpp
# End Source File
# Begin Source File

SOURCE=.\TileSetView.h
# End Source File
# Begin Source File

SOURCE=.\TileTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TileTreeItem.h
# End Source File
# End Group
# Begin Group "Fence Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FenceFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\FenceFrm.h
# End Source File
# Begin Source File

SOURCE=.\FenceTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\FenceTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\FenceView.cpp
# End Source File
# Begin Source File

SOURCE=.\FenceView.h
# End Source File
# End Group
# Begin Group "Particles"

# PROP Default_Filter ""
# Begin Group "Refs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ParticleSourceData.cpp
# End Source File
# Begin Source File

SOURCE=.\SmokinParticleSourceData.cpp
# End Source File
# Begin Source File

SOURCE=.\Track.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ParticleFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticleFrm.h
# End Source File
# Begin Source File

SOURCE=.\ParticleTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticleTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\ParticleView.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticleView.h
# End Source File
# End Group
# Begin Group "Trenches"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TrenchFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\TrenchFrm.h
# End Source File
# Begin Source File

SOURCE=.\TrenchTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TrenchTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\TrenchView.cpp
# End Source File
# Begin Source File

SOURCE=.\TrenchView.h
# End Source File
# End Group
# Begin Group "Squad Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SquadFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SquadFrm.h
# End Source File
# Begin Source File

SOURCE=.\SquadTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\SquadTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\SquadView.cpp
# End Source File
# Begin Source File

SOURCE=.\SquadView.h
# End Source File
# End Group
# Begin Group "Mine Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MineFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MineFrm.h
# End Source File
# Begin Source File

SOURCE=.\MineTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\MineTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\MineView.cpp
# End Source File
# Begin Source File

SOURCE=.\MineView.h
# End Source File
# End Group
# Begin Group "Bridge Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BridgeCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\BridgeFire.cpp
# End Source File
# Begin Source File

SOURCE=.\BridgeFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\BridgeFrm.h
# End Source File
# Begin Source File

SOURCE=.\BridgeSmoke.cpp
# End Source File
# Begin Source File

SOURCE=.\BridgeTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\BridgeTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\BridgeView.cpp
# End Source File
# Begin Source File

SOURCE=.\BridgeView.h
# End Source File
# End Group
# Begin Group "Mission Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MissionFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MissionFrm.h
# End Source File
# Begin Source File

SOURCE=.\MissionTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\MissionTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\MissionView.cpp
# End Source File
# Begin Source File

SOURCE=.\MissionView.h
# End Source File
# End Group
# Begin Group "Chapter Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ChapterFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ChapterFrm.h
# End Source File
# Begin Source File

SOURCE=.\ChapterTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ChapterTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\ChapterView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChapterView.h
# End Source File
# Begin Source File

SOURCE=.\UnitSide.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitSide.h
# End Source File
# End Group
# Begin Group "Campaign Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CampaignFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CampaignFrm.h
# End Source File
# Begin Source File

SOURCE=.\CampaignTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\CampaignTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\CampaignView.cpp
# End Source File
# Begin Source File

SOURCE=.\CampaignView.h
# End Source File
# Begin Source File

SOURCE=.\ImageFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageFrm.h
# End Source File
# Begin Source File

SOURCE=.\ImageView.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageView.h
# End Source File
# End Group
# Begin Group "3D Roads"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3dRoadFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\3dRoadFrm.h
# End Source File
# Begin Source File

SOURCE=.\3dRoadTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\3dRoadTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\3dRoadView.cpp
# End Source File
# Begin Source File

SOURCE=.\3dRoadView.h
# End Source File
# End Group
# Begin Group "3D Rivers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\3dRiverFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\3dRiverFrm.h
# End Source File
# Begin Source File

SOURCE=.\3dRiverTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\3dRiverTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\3dRiverView.cpp
# End Source File
# Begin Source File

SOURCE=.\3dRiverView.h
# End Source File
# End Group
# Begin Group "Medals"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MedalFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MedalFrm.h
# End Source File
# Begin Source File

SOURCE=.\MedalTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\MedalTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\MedalView.cpp
# End Source File
# Begin Source File

SOURCE=.\MedalView.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\common.cpp
# End Source File
# Begin Source File

SOURCE=.\common.h
# End Source File
# Begin Source File

SOURCE=.\frames.cpp
# End Source File
# Begin Source File

SOURCE=.\frames.h
# End Source File
# Begin Source File

SOURCE=.\localization.cpp
# End Source File
# Begin Source File

SOURCE=.\localization.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyOpenFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MyOpenFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\ParentFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ParentFrame.h
# End Source File
# Begin Source File

SOURCE=.\TreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeItem.h
# End Source File
# Begin Source File

SOURCE=.\TreeItemFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeItemFactory.h
# End Source File
# End Group
# Begin Group "Common Controls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BrowseDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BrowseDialog.h
# End Source File
# Begin Source File

SOURCE=.\DirectionButton.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectionButton.h
# End Source File
# Begin Source File

SOURCE=.\DirectionButtonDock.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectionButtonDock.h
# End Source File
# Begin Source File

SOURCE=.\ETreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ETreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\KeyFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyFrame.h
# End Source File
# Begin Source File

SOURCE=.\KeyFrameDock.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyFrameDock.h
# End Source File
# Begin Source File

SOURCE=.\PictureOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureOptions.h
# End Source File
# Begin Source File

SOURCE=.\PropertyDockBar.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyDockBar.h
# End Source File
# Begin Source File

SOURCE=.\SingleIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\SingleIcon.h
# End Source File
# Begin Source File

SOURCE=.\ThumbList.cpp
# End Source File
# Begin Source File

SOURCE=.\ThumbList.h
# End Source File
# Begin Source File

SOURCE=.\ThumbListDockBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ThumbListDockBar.h
# End Source File
# Begin Source File

SOURCE=.\TreeDockWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeDockWnd.h
# End Source File
# End Group
# Begin Group "References"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BatchModeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BatchModeDialog.h
# End Source File
# Begin Source File

SOURCE=.\BuildCompose.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildCompose.h
# End Source File
# Begin Source File

SOURCE=.\MODDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MODDialog.h
# End Source File
# Begin Source File

SOURCE=.\MultySelDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MultySelDialog.h
# End Source File
# Begin Source File

SOURCE=.\NewDirDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\NewDirDialog.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.h
# End Source File
# Begin Source File

SOURCE=.\RefDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RefDlg.h
# End Source File
# Begin Source File

SOURCE=.\Reference.cpp
# End Source File
# Begin Source File

SOURCE=.\Reference.h
# End Source File
# Begin Source File

SOURCE=.\SetDirDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SetDirDialog.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\editor.cpp
# End Source File
# Begin Source File

SOURCE=.\editor.h
# End Source File
# Begin Source File

SOURCE=.\GameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GameWnd.h
# End Source File
# Begin Source File

SOURCE=.\MinimapCreation.cpp
# End Source File
# Begin Source File

SOURCE=.\MinimapCreation.h
# End Source File
# Begin Source File

SOURCE=.\SpriteCompose.cpp
# End Source File
# Begin Source File

SOURCE=.\SpriteCompose.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "For VSS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\editor.rc
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\a7_editor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp3droa.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bridge_t.bmp
# End Source File
# Begin Source File

SOURCE=.\res\building.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chapter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\editor.ico
# End Source File
# Begin Source File

SOURCE=.\res\editor.rc2
# End Source File
# Begin Source File

SOURCE=.\res\effect_t.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fence_to.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\idr_edit.ico
# End Source File
# Begin Source File

SOURCE=.\res\infantry.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mesh_too.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mission_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MultiTreeConrtol.ico
# End Source File
# Begin Source File

SOURCE=.\res\objectb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\particle.bmp
# End Source File
# Begin Source File

SOURCE=.\res\squad_to.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tileset.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\treebmp.bmp
# End Source File
# End Group
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
# Begin Group "ObjectInspector"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\COI\CtrlObjectInspector.cpp
# End Source File
# Begin Source File

SOURCE=.\COI\CtrlObjectInspector.h
# End Source File
# Begin Source File

SOURCE=.\COI\OIBrowEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\COI\OIBrowEdit.h
# End Source File
# Begin Source File

SOURCE=.\COI\OIColorEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\COI\OIColorEdit.h
# End Source File
# Begin Source File

SOURCE=.\COI\OICombo.cpp
# End Source File
# Begin Source File

SOURCE=.\COI\OICombo.h
# End Source File
# Begin Source File

SOURCE=.\COI\OIEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\COI\OIEdit.h
# End Source File
# Begin Source File

SOURCE=.\COI\OIReference.cpp
# End Source File
# Begin Source File

SOURCE=.\COI\OIReference.h
# End Source File
# Begin Source File

SOURCE=.\COI\PropView.cpp
# End Source File
# Begin Source File

SOURCE=.\COI\PropView.h
# End Source File
# Begin Source File

SOURCE=.\COI\Variant.cpp
# End Source File
# Begin Source File

SOURCE=.\COI\Variant.h
# End Source File
# End Group
# Begin Group "MultyTree"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\MTree ctrl\CTreeItem.cpp"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\CTreeItem.h"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\FrameTree.cpp"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\FrameTree.h"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\MultiTree.cpp"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\MultiTree.h"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\MultiTreeEditBox.cpp"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\MultiTreeEditBox.h"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\MultiTreeSlider.cpp"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\MultiTreeSlider.h"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\PercentDialog.cpp"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\PercentDialog.h"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\TreeItemComboBox.cpp"
# End Source File
# Begin Source File

SOURCE=".\MTree ctrl\TreeItemComboBox.h"
# End Source File
# End Group
# End Target
# End Project
