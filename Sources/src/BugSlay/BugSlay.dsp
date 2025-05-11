# Microsoft Developer Studio Project File - Name="BugSlay" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=BugSlay - Win32 Profiler
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BugSlay.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BugSlay.mak" CFG="BugSlay - Win32 Profiler"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BugSlay - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BugSlay - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BugSlay - Win32 BetaRelease" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BugSlay - Win32 FastDebug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BugSlay - Win32 Profiler" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/BugSlay", VSLAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BugSlay - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "BUGSLAYER_EXPORTS" /D "_DONT_LOAD_SINGLETONS" /D "_DONT_LOAD_STREAMIO" /D "_FINALRELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
OutDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BugSlay - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "BUGSLAYER_EXPORTS" /D "_DO_ASSERT_SLOW" /D "_WINDOWS" /D "_DONT_LOAD_SINGLETONS" /D "_DONT_LOAD_STREAMIO" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /Yu"StdAfx.h" /FD /GZ /c
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
# ADD LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ELSEIF  "$(CFG)" == "BugSlay - Win32 BetaRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BugSlay___Win32_BetaRelease"
# PROP BASE Intermediate_Dir "BugSlay___Win32_BetaRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BetaRelease"
# PROP Intermediate_Dir "BetaRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "BUGSLAYER_EXPORTS" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /Ot /Og /Op /Ob2 /D "BUGSLAYER_EXPORTS" /D "_DO_ASSERT_SLOW" /D "_DONT_LOAD_SINGLETONS" /D "_DONT_LOAD_STREAMIO" /D "_BETARELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /c
# SUBTRACT CPP /Ox /Oi
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /pdb:none /map /debug /machine:I386 /def:".\BugSlayer.def" /FIXED:NO
# Begin Special Build Tool
OutDir=.\BetaRelease
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BugSlay - Win32 FastDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BugSlay___Win32_FastDebug"
# PROP BASE Intermediate_Dir "BugSlay___Win32_FastDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FastDebug"
# PROP Intermediate_Dir "FastDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "BUGSLAYER_EXPORTS" /D "_DO_ASSERT_SLOW" /D "WIN32" /D "_DEBUG" /D "_STL_FAST_DEBUG" /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "NDEBUG" /D "BUGSLAYER_EXPORTS" /D "_DO_ASSERT_SLOW" /D "_DONT_LOAD_SINGLETONS" /D "_DONT_LOAD_STREAMIO" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
OutDir=.\FastDebug
SOURCE="$(InputPath)"
PostBuild_Cmds=copy $(OutDir)\*.dll c:\a7\*.*
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BugSlay - Win32 Profiler"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BugSlay___Win32_Profiler"
# PROP BASE Intermediate_Dir "BugSlay___Win32_Profiler"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Profiler"
# PROP Intermediate_Dir "Profiler"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "NDEBUG" /D "BUGSLAYER_EXPORTS" /D "_DO_ASSERT_SLOW" /D "_DONT_LOAD_SINGLETONS" /D "_DONT_LOAD_STREAMIO" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /GZ /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /D "BUGSLAYER_EXPORTS" /D "_DONT_LOAD_SINGLETONS" /D "_DONT_LOAD_STREAMIO" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_FINALRELEASE" /D "_PROFILER" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /def:".\BugSlayer.def" /pdbtype:sept /fixed:no
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "BugSlay - Win32 Release"
# Name "BugSlay - Win32 Debug"
# Name "BugSlay - Win32 BetaRelease"
# Name "BugSlay - Win32 FastDebug"
# Name "BugSlay - Win32 Profiler"
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
# Begin Group "BugSlayer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AllocAndFillProcessModuleList.cpp
# End Source File
# Begin Source File

SOURCE=.\BSUFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\BugSlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\BugSlayer.h
# End Source File
# Begin Source File

SOURCE=.\CallStack.cpp
# End Source File
# Begin Source File

SOURCE=.\CallStack.h
# End Source File
# Begin Source File

SOURCE=.\CrashHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\CriticalSection.h
# End Source File
# Begin Source File

SOURCE=.\CRTDBG_Internals.h
# End Source File
# Begin Source File

SOURCE=.\DiagAssert.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagAssert.h
# End Source File
# Begin Source File

SOURCE=.\GetLoadedModules.cpp
# End Source File
# Begin Source File

SOURCE=.\HookImportedFunctionByName.cpp
# End Source File
# Begin Source File

SOURCE=.\Internal.h
# End Source File
# Begin Source File

SOURCE=.\IsNT.cpp
# End Source File
# Begin Source File

SOURCE=.\MemDumperValidator.cpp
# End Source File
# Begin Source File

SOURCE=.\MemDumperValidator.h
# End Source File
# Begin Source File

SOURCE=.\MSJDBG.h
# End Source File
# Begin Source File

SOURCE=.\Notification.cpp
# End Source File
# Begin Source File

SOURCE=.\Notification.h
# End Source File
# Begin Source File

SOURCE=.\NT4ProcessInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Psapi.h
# End Source File
# Begin Source File

SOURCE=.\STLDebugTerminate.cpp
# End Source File
# Begin Source File

SOURCE=.\SymbolEngine.h
# End Source File
# Begin Source File

SOURCE=.\TLHELPProcessInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\WarningsOff.h
# End Source File
# Begin Source File

SOURCE=.\WarningsOn.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\BugSlayer.rc
# End Source File
# Begin Source File

SOURCE=.\error.ico
# End Source File
# Begin Source File

SOURCE=.\exclamation.ico
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Dialogs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DialogFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogFunctions.h
# End Source File
# Begin Source File

SOURCE=.\DialogMemory.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogMemory.h
# End Source File
# Begin Source File

SOURCE=.\ReportAssertionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportExceptionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WndUtils.h
# End Source File
# End Group
# Begin Group "Memory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DumbPow2Alloc.cpp
# End Source File
# Begin Source File

SOURCE=.\MemorySystem.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\BugSlayer.def

!IF  "$(CFG)" == "BugSlay - Win32 Release"

!ELSEIF  "$(CFG)" == "BugSlay - Win32 Debug"

!ELSEIF  "$(CFG)" == "BugSlay - Win32 BetaRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BugSlay - Win32 FastDebug"

!ELSEIF  "$(CFG)" == "BugSlay - Win32 Profiler"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
