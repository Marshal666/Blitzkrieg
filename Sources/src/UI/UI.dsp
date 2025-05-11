# Microsoft Developer Studio Project File - Name="UI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=UI - Win32 Profiler
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UI.mak" CFG="UI - Win32 Profiler"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UI - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UI - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UI - Win32 BetaRelease" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UI - Win32 FastDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UI - Win32 Profiler" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/UI", PCPAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UI - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "_FINALRELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /c
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

!ELSEIF  "$(CFG)" == "UI - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_ASSERT_SLOW" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /Yu"StdAfx.h" /FD /GZ /Zm200 /c
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

!ELSEIF  "$(CFG)" == "UI - Win32 BetaRelease"

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
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /Ot /Og /Op /Ob2 /D "_DO_ASSERT_SLOW" /D "_BETARELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /c
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /def:".\UI.def" /FIXED:NO
# Begin Special Build Tool
OutDir=.\BetaRelease
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "UI - Win32 FastDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "UI___Win32_FastDebug"
# PROP BASE Intermediate_Dir "UI___Win32_FastDebug"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FastDebug"
# PROP Intermediate_Dir "FastDebug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_ASSERT_SLOW" /D "WIN32" /D "_DEBUG" /D "_STL_FAST_DEBUG" /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "_DO_ASSERT_SLOW" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
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

!ELSEIF  "$(CFG)" == "UI - Win32 Profiler"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "UI___Win32_Profiler"
# PROP BASE Intermediate_Dir "UI___Win32_Profiler"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Profiler"
# PROP Intermediate_Dir "Profiler"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "_DO_ASSERT_SLOW" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /GZ /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_FINALRELEASE" /D "_PROFILER" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /def:".\UI.def" /pdbtype:sept /fixed:no
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
OutDir=.\Profiler
SOURCE="$(InputPath)"
PostBuild_Cmds=copy  $(OutDir)\*.dll  c:\a7\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "UI - Win32 Release"
# Name "UI - Win32 Debug"
# Name "UI - Win32 BetaRelease"
# Name "UI - Win32 FastDebug"
# Name "UI - Win32 Profiler"
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
# Begin Group "UI"

# PROP Default_Filter ""
# Begin Group "Base"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UIBasic.cpp
# End Source File
# Begin Source File

SOURCE=.\UIBasic.h
# End Source File
# Begin Source File

SOURCE=.\UIBasicM.cpp
# End Source File
# Begin Source File

SOURCE=.\UIBasicM.h
# End Source File
# Begin Source File

SOURCE=.\UIBridge.h
# End Source File
# Begin Source File

SOURCE=.\UIInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\UIInternal.h
# End Source File
# Begin Source File

SOURCE=.\UIInternalM.cpp
# End Source File
# Begin Source File

SOURCE=.\UIInternalM.h
# End Source File
# End Group
# Begin Group "Elements"

# PROP Default_Filter ""
# Begin Group "ColorTextScroll"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UIColorTextScroll.cpp
# End Source File
# Begin Source File

SOURCE=.\UIColorTextScroll.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\UIButton.cpp
# End Source File
# Begin Source File

SOURCE=.\UIButton.h
# End Source File
# Begin Source File

SOURCE=.\UIConsole.cpp
# End Source File
# Begin Source File

SOURCE=.\UIConsole.h
# End Source File
# Begin Source File

SOURCE=.\UICreditsScroller.cpp
# End Source File
# Begin Source File

SOURCE=.\UICreditsScroller.h
# End Source File
# Begin Source File

SOURCE=.\UIDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\UIDialog.h
# End Source File
# Begin Source File

SOURCE=.\UIEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UIEdit.h
# End Source File
# Begin Source File

SOURCE=.\UIMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMessageBox.h
# End Source File
# Begin Source File

SOURCE=.\UIMiniMap.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMiniMap.h
# End Source File
# Begin Source File

SOURCE=.\UINumberIndicator.cpp
# End Source File
# Begin Source File

SOURCE=.\UINumberIndicator.h
# End Source File
# Begin Source File

SOURCE=.\UIScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\UIScreen.h
# End Source File
# Begin Source File

SOURCE=.\UIScrollText.cpp
# End Source File
# Begin Source File

SOURCE=.\UIScrollText.h
# End Source File
# Begin Source File

SOURCE=.\UISlider.cpp
# End Source File
# Begin Source File

SOURCE=.\UISlider.h
# End Source File
# Begin Source File

SOURCE=.\UIStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UIStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\UITimeCounter.cpp
# End Source File
# Begin Source File

SOURCE=.\UITimeCounter.h
# End Source File
# Begin Source File

SOURCE=.\UIVideoButton.cpp
# End Source File
# Begin Source File

SOURCE=.\UIVideoButton.h
# End Source File
# End Group
# Begin Group "Complex"

# PROP Default_Filter ""
# Begin Group "ComplexScroll"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\UIComplexScroll.cpp
# End Source File
# Begin Source File

SOURCE=.\UIComplexScroll.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\UIComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UIComboBox.h
# End Source File
# Begin Source File

SOURCE=.\UIList.cpp
# End Source File
# Begin Source File

SOURCE=.\UIList.h
# End Source File
# Begin Source File

SOURCE=.\UIListSorter.cpp
# End Source File
# Begin Source File

SOURCE=.\UIListSorter.h
# End Source File
# Begin Source File

SOURCE=.\UIMedals.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMedals.h
# End Source File
# Begin Source File

SOURCE=.\UIObjectiveScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\UIObjectiveScreen.h
# End Source File
# Begin Source File

SOURCE=.\UIObjMap.cpp
# End Source File
# Begin Source File

SOURCE=.\UIObjMap.h
# End Source File
# Begin Source File

SOURCE=.\UIShortcutBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UIShortcutBar.h
# End Source File
# Begin Source File

SOURCE=.\UITree.cpp
# End Source File
# Begin Source File

SOURCE=.\UITree.h
# End Source File
# End Group
# Begin Group "Mask Manager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MaskManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MaskManager.h
# End Source File
# Begin Source File

SOURCE=.\MaskSystem.h
# End Source File
# Begin Source File

SOURCE=.\UIMask.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMask.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\UI.h
# End Source File
# Begin Source File

SOURCE=.\UIMessages.h
# End Source File
# Begin Source File

SOURCE=.\UIObjectFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\UIObjectFactory.h
# End Source File
# End Group
# Begin Group "Resource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\UI.rc
# End Source File
# End Group
# Begin Source File

SOURCE=.\UI.def

!IF  "$(CFG)" == "UI - Win32 Release"

!ELSEIF  "$(CFG)" == "UI - Win32 Debug"

!ELSEIF  "$(CFG)" == "UI - Win32 BetaRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UI - Win32 FastDebug"

!ELSEIF  "$(CFG)" == "UI - Win32 Profiler"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
