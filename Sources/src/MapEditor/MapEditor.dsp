# Microsoft Developer Studio Project File - Name="MapEditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MapEditor - Win32 Profiler
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MapEditor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MapEditor.mak" CFG="MapEditor - Win32 Profiler"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MapEditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MapEditor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MapEditor - Win32 BetaRelease" (based on "Win32 (x86) Application")
!MESSAGE "MapEditor - Win32 FastDebug" (based on "Win32 (x86) Application")
!MESSAGE "MapEditor - Win32 Profiler" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/MapEditor", AJMAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MapEditor - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "COI" /D "_AFXDLL" /D "__AFX__" /D "_FINALRELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /Zm300 /c
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
# ADD LINK32 version.lib winmm.lib comsupp.lib htmlhelp.lib /nologo /subsystem:windows /pdb:none /machine:I386
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
OutDir=.\Release
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.exe c:\a7\*.*	call s:\soft\copydll.bat $(WkspDir) Release
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "COI" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /Yu"StdAfx.h" /FD /I /GZ /Zm400 /c
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
# ADD LINK32 version.lib winmm.lib comsupp.lib htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
OutDir=.\Debug
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.exe c:\a7\*.*	call s:\soft\copydll.bat $(WkspDir) Debug
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MapEditor - Win32 BetaRelease"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MapEditor___Win32_BetaRelease"
# PROP BASE Intermediate_Dir "MapEditor___Win32_BetaRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BetaRelease"
# PROP Intermediate_Dir "BetaRelease"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /I "COI" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /Ot /Og /Op /Ob2 /I "COI" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /D "_BETARELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /Zm300 /c
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
# ADD LINK32 version.lib winmm.lib comsupp.lib htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
OutDir=.\BetaRelease
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.exe c:\a7\*.*	call s:\soft\copydll.bat $(WkspDir) BetaRelease
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MapEditor - Win32 FastDebug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MapEditor___Win32_FastDebug"
# PROP BASE Intermediate_Dir "MapEditor___Win32_FastDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FastDebug"
# PROP Intermediate_Dir "FastDebug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "COI" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /D "WIN32" /D "_DEBUG" /D "_STL_FAST_DEBUG" /FR"" /Yu"StdAfx.h" /FD /I /GZ /Zm200 /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Od /I "COI" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Fr /Yu"StdAfx.h" /FD /I /GZ /Zm300 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 htmlhelp.lib version.lib winmm.lib comsupp.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
OutDir=.\FastDebug
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.exe c:\a7\*.*	call s:\soft\copydll.bat $(WkspDir) FastDebug
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Profiler"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MapEditor___Win32_Profiler"
# PROP BASE Intermediate_Dir "MapEditor___Win32_Profiler"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Profiler"
# PROP Intermediate_Dir "Profiler"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Zi /Od /I "COI" /D "_AFXDLL" /D "__AFX__" /D "_DO_ASSERT_SLOW" /D "_DO_SEH" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Fr /Yu"StdAfx.h" /FD /I /GZ /Zm300 /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /I "COI" /D "_AFXDLL" /D "__AFX__" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_FINALRELEASE" /D "_PROFILER" /Yu"StdAfx.h" /FD /I /Zm300 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 htmlhelp.lib version.lib winmm.lib comsupp.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 htmlhelp.lib version.lib winmm.lib comsupp.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
OutDir=.\Profiler
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.exe c:\a7\*.*	call s:\soft\copydll.bat $(WkspDir) Profiler
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "MapEditor - Win32 Release"
# Name "MapEditor - Win32 Debug"
# Name "MapEditor - Win32 BetaRelease"
# Name "MapEditor - Win32 FastDebug"
# Name "MapEditor - Win32 Profiler"
# Begin Group "Sources"

# PROP Default_Filter ""
# Begin Group "Main Frame"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\frames.cpp
# End Source File
# Begin Source File

SOURCE=.\frames.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# End Group
# Begin Group "Template editor"

# PROP Default_Filter ""
# Begin Group "IUndoRedoCmd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IUndoRedoCmd.cpp
# End Source File
# Begin Source File

SOURCE=.\IUndoRedoCmd.h
# End Source File
# End Group
# Begin Group "VC like button"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PushPin.cpp
# End Source File
# Begin Source File

SOURCE=.\PushPin.h
# End Source File
# End Group
# Begin Group "Propertie dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PropertieDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertieDialog.h
# End Source File
# End Group
# Begin Group "MultiTree control"

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
# Begin Group "State"

# PROP Default_Filter ""
# Begin Group "Road drawing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RoadDrawState.cpp
# End Source File
# Begin Source File

SOURCE=.\RoadDrawState.h
# End Source File
# End Group
# Begin Group "Object placer state"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObjectPlacerState.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectPlacerState.h
# End Source File
# End Group
# Begin Group "Map tool"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MapToolState.cpp
# End Source File
# Begin Source File

SOURCE=.\MapToolState.h
# End Source File
# End Group
# End Group
# Begin Group "Unit Manipulators"

# PROP Default_Filter ""
# Begin Group "Simple editor object"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EditorObjectItem.cpp
# End Source File
# Begin Source File

SOURCE=.\EditorObjectItem.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\SEditorMApObject.cpp
# End Source File
# Begin Source File

SOURCE=.\SEditorMApObject.h
# End Source File
# End Group
# Begin Group "Map options dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MapOptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MapOptionsDialog.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\TemplateEditorFrame1.cpp
# End Source File
# Begin Source File

SOURCE=.\TemplateEditorFrame1.h
# End Source File
# End Group
# Begin Group "Common Controls"

# PROP Default_Filter ""
# Begin Group "Resize Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ResizeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ResizeDialog.h
# End Source File
# End Group
# Begin Group "Direction Button"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DirectionButton.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectionButton.h
# End Source File
# End Group
# Begin Group "Progress Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ProgressDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.h
# End Source File
# End Group
# End Group
# Begin Group "Tabs"

# PROP Default_Filter ""
# Begin Group "Vector Objects Tab"

# PROP Default_Filter ""
# Begin Group "VSO Tab"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TabVOVSODialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TabVOVSODialog.h
# End Source File
# End Group
# Begin Group "Entrenchments Tab"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TrenchSetupWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\TrenchSetupWindow.h
# End Source File
# End Group
# End Group
# Begin Group "Input Tabs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Input3DTabWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Input3DTabWnd.h
# End Source File
# Begin Source File

SOURCE=.\InputNotifyShortcutBar.cpp
# End Source File
# Begin Source File

SOURCE=.\InputNotifyShortcutBar.h
# End Source File
# End Group
# Begin Group "Input Bar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MapEditorBarWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\MapEditorBarWnd.h
# End Source File
# End Group
# Begin Group "Toos Tab"

# PROP Default_Filter ""
# Begin Group "Area Name"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AreaNameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaNameDialog.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\TabToolsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TabToolsDialog.h
# End Source File
# End Group
# Begin Group "Groups Tab"

# PROP Default_Filter ""
# Begin Group "Group ID"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GetGroupID.cpp
# End Source File
# Begin Source File

SOURCE=.\GetGroupID.h
# End Source File
# End Group
# Begin Group "Script ID"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EnterScriptIDDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\EnterScriptIDDialog.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\GroupManagerDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupManagerDialog.h
# End Source File
# End Group
# Begin Group "AI General Tab"

# PROP Default_Filter ""
# Begin Group "Enter Script ID"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TabAIGeneralEnterScriptIDDialog.h
# End Source File
# Begin Source File

SOURCE=.\TabAIGeneralSetPositionTypeDialog.cpp
# End Source File
# End Group
# Begin Group "Enter Position Type"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TabAIGeneralEnterScriptIDDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TabAIGeneralSetPositionTypeDialog.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\TabAIGeneralDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TabAIGeneralDialog.h
# End Source File
# End Group
# Begin Group "Terrain Tab"

# PROP Default_Filter ""
# Begin Group "Tile Edit Tab"

# PROP Default_Filter ""
# Begin Group "Image group list"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\TabTileEditDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TabTileEditDialog.h
# End Source File
# End Group
# Begin Group "Terrain Altitudes Tab"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TabTerrainAltitudesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TabTerrainAltitudesDialog.h
# End Source File
# End Group
# Begin Group "Fields Tab"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TabTerrainFieldsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TabTerrainFieldsDialog.h
# End Source File
# End Group
# End Group
# Begin Group "Objects Tab"

# PROP Default_Filter ""
# Begin Group "Fences Tab"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FenceSetupWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\FenceSetupWindow.h
# End Source File
# End Group
# Begin Group "Simple Objects Tab"

# PROP Default_Filter ""
# Begin Group "Diplomacy"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TabSimpleObjectsDiplomacyDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TabSimpleObjectsDiplomacyDialog.h
# End Source File
# End Group
# Begin Group "Set Filter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SetupFilterDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SetupFilterDialog.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\TabSimpleObjectsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TabSimpleObjectsDialog.h
# End Source File
# End Group
# Begin Group "Bridges Tab"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BridgeSetupDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BridgeSetupDialog.h
# End Source File
# End Group
# End Group
# End Group
# Begin Group "States"

# PROP Default_Filter ""
# Begin Group "Vector Objects State"

# PROP Default_Filter ""
# Begin Group "Vector Stripe Objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\VectorStripeObjectsState.cpp
# End Source File
# Begin Source File

SOURCE=.\VectorStripeObjectsState.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\VectorObjectsState.cpp
# End Source File
# Begin Source File

SOURCE=.\VectorObjectsState.h
# End Source File
# End Group
# Begin Group "Input state"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InputMultiState.cpp
# End Source File
# Begin Source File

SOURCE=.\InputMultiState.h
# End Source File
# Begin Source File

SOURCE=.\InputState.cpp
# End Source File
# Begin Source File

SOURCE=.\InputState.h
# End Source File
# End Group
# Begin Group "AI General State"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StateAIGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\StateAIGeneral.h
# End Source File
# End Group
# Begin Group "Groups State"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StateGroups.cpp
# End Source File
# Begin Source File

SOURCE=.\StateGroups.h
# End Source File
# End Group
# Begin Group "Terrain State"

# PROP Default_Filter ""
# Begin Group "3DTerrain State"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DrawShadeState.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawShadeState.h
# End Source File
# End Group
# Begin Group "Tile drawing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TileDrawState.cpp
# End Source File
# Begin Source File

SOURCE=.\TileDrawState.h
# End Source File
# End Group
# Begin Group "Fields State"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\StateTerrainFields.cpp
# End Source File
# Begin Source File

SOURCE=.\StateTerrainFields.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\TerrainState.cpp
# End Source File
# Begin Source File

SOURCE=.\TerrainState.h
# End Source File
# End Group
# Begin Group "Simple Objects State"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SimpleObjectsState.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleObjectsState.h
# End Source File
# End Group
# End Group
# Begin Group "Drawing Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DrawingTools.h
# End Source File
# Begin Source File

SOURCE=.\ValuesCollector.h
# End Source File
# End Group
# Begin Group "Mini Map"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MiniMapBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MiniMapBar.h
# End Source File
# Begin Source File

SOURCE=.\MiniMapDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MiniMapDialog.h
# End Source File
# Begin Source File

SOURCE=.\MiniMapTypes.cpp
# End Source File
# Begin Source File

SOURCE=.\MiniMapTypes.h
# End Source File
# End Group
# Begin Group "AsyncImageList"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AsyncImageList.cpp

!IF  "$(CFG)" == "MapEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Debug"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 BetaRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "MapEditor - Win32 FastDebug"

!ELSEIF  "$(CFG)" == "MapEditor - Win32 Profiler"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AsyncImageList.h
# End Source File
# End Group
# Begin Group "Manipulators"

# PROP Default_Filter ""
# Begin Group "AIStartCommand Creation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AIStartCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\AIStartCommand.h
# End Source File
# Begin Source File

SOURCE=.\AIStartCommandsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AIStartCommandsDialog.h
# End Source File
# End Group
# Begin Group "ReservePosition"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ReservePosition.cpp
# End Source File
# Begin Source File

SOURCE=.\ReservePosition.h
# End Source File
# End Group
# Begin Group "Unit Creation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UnitCreation.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitCreation.h
# End Source File
# End Group
# Begin Group "Map Sound Info"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MapSoundInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MapSoundInfo.h
# End Source File
# End Group
# Begin Group "Property Editors"

# PROP Default_Filter ""
# Begin Group "PointsList"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PE_PointPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PE_PointPropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\PEPointsListDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PEPointsListDialog.h
# End Source File
# End Group
# Begin Group "SelectStrings"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PESelectStringsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PESelectStringsDialog.h
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Composers"

# PROP Default_Filter ""
# Begin Group "RMG Containers Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RMG_CreateContainerDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_CreateContainerDialog.h
# End Source File
# Begin Source File

SOURCE=.\RMG_PatchPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_PatchPropertiesDialog.h
# End Source File
# End Group
# Begin Group "RMG Templates Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RMG_CreateTemplateDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_CreateTemplateDialog.h
# End Source File
# Begin Source File

SOURCE=.\RMG_TemplateFieldPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_TemplateFieldPropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\RMG_TemplateGraphPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_TemplateGraphPropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\RMG_TemplateVSOPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_TemplateVSOPropertiesDialog.h
# End Source File
# End Group
# Begin Group "RMG Graphs Composer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RMG_CreateGraphDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_CreateGraphDialog.h
# End Source File
# Begin Source File

SOURCE=.\RMG_GraphLinkPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_GraphLinkPropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\RMG_GraphNodePropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_GraphNodePropertiesDialog.h
# End Source File
# End Group
# Begin Group "RMG Fields Composer"

# PROP Default_Filter ""
# Begin Group "RMG Field Objects Shells"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RMG_FieldObjectPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_FieldObjectPropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\RMG_FieldObjectsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_FieldObjectsDialog.h
# End Source File
# Begin Source File

SOURCE=.\RMG_FieldObjectsShellPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_FieldObjectsShellPropertiesDialog.h
# End Source File
# End Group
# Begin Group "RMG Field Terrain Shells"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RMG_FieldTerrainDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_FieldTerrainDialog.h
# End Source File
# Begin Source File

SOURCE=.\RMG_FieldTerrainShellPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_FieldTerrainShellPropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\RMG_FieldTilePropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_FieldTilePropertiesDialog.h
# End Source File
# End Group
# Begin Group "RMG Field Heights"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RMG_FieldHeightsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_FieldHeightsDialog.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\RMG_CreateFieldDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_CreateFieldDialog.h
# End Source File
# End Group
# End Group
# Begin Group "Create Filter Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CreateFilterDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateFilterDialog.h
# End Source File
# Begin Source File

SOURCE=.\CreateFilterNameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateFilterNameDialog.h
# End Source File
# End Group
# Begin Group "Create Random Map Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CreateRandomMapDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateRandomMapDialog.h
# End Source File
# End Group
# Begin Group "New Map Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NewMapDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\NewMapDialog.h
# End Source File
# End Group
# Begin Group "Open Map Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OpenMapDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenMapDialog.h
# End Source File
# End Group
# Begin Group "MOD Collector"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODCollector.cpp
# End Source File
# Begin Source File

SOURCE=.\MODCollector.h
# End Source File
# End Group
# Begin Group "Map Editor Options"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MapEditorOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\MapEditorOptions.h
# End Source File
# End Group
# Begin Group "Editor Window Singleton"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EditorWindowSingleton.cpp
# End Source File
# Begin Source File

SOURCE=.\EditorWindowSingleton.h
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

SOURCE=.\SetAnim.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "Resource VSS Check Out"

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

SOURCE=.\res\bridges_tab.ico
# End Source File
# Begin Source File

SOURCE=.\res\edit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\editor.ico
# End Source File
# Begin Source File

SOURCE=.\res\editor.rc2
# End Source File
# Begin Source File

SOURCE=.\res\entrenchments_icon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\entrenchments_tab.ico
# End Source File
# Begin Source File

SOURCE=.\res\fences_tab.ico
# End Source File
# Begin Source File

SOURCE=.\res\fields_tab.ico
# End Source File
# Begin Source File

SOURCE=.\res\heights_tab.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\object.bmp
# End Source File
# Begin Source File

SOURCE=.\res\objects_tab.ico
# End Source File
# Begin Source File

SOURCE=.\res\pushpin.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rivers_tab.ico
# End Source File
# Begin Source File

SOURCE=.\res\rmg_cf_heights.ico
# End Source File
# Begin Source File

SOURCE=.\res\rmg_cf_objects.ico
# End Source File
# Begin Source File

SOURCE=.\res\rmg_cf_tiles.ico
# End Source File
# Begin Source File

SOURCE=.\res\roads_tab.ico
# End Source File
# Begin Source File

SOURCE=.\res\terrain_tab.ico
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\GlobalsLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\htmlhelp.h
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
# Begin Source File

SOURCE=.\htmlhelp.lib
# End Source File
# End Target
# End Project
