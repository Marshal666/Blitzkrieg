# Microsoft Developer Studio Project File - Name="LuaLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LuaLib - Win32 Profiler
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LuaLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LuaLib.mak" CFG="LuaLib - Win32 Profiler"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LuaLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LuaLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LuaLib - Win32 BetaRelease" (based on "Win32 (x86) Static Library")
!MESSAGE "LuaLib - Win32 FastDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "LuaLib - Win32 Profiler" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/LuaLib", CEOAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LuaLib - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "_FINALRELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LuaLib - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LuaLib - Win32 BetaRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BetaRelease"
# PROP BASE Intermediate_Dir "BetaRelease"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "BetaRelease"
# PROP Intermediate_Dir "BetaRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /Ot /Og /Op /Ob2 /D "_BETARELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /YX /FD /c
# SUBTRACT CPP /Ox /Oi
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LuaLib - Win32 FastDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "LuaLib___Win32_FastDebug"
# PROP BASE Intermediate_Dir "LuaLib___Win32_FastDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FastDebug"
# PROP Intermediate_Dir "FastDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "WIN32" /D "_DEBUG" /D "_STL_FAST_DEBUG" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LuaLib - Win32 Profiler"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "LuaLib___Win32_Profiler"
# PROP BASE Intermediate_Dir "LuaLib___Win32_Profiler"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Profiler"
# PROP Intermediate_Dir "Profiler"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /YX /FD /GZ /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_FINALRELEASE" /D "_PROFILER" /YX /FD /c
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

# Name "LuaLib - Win32 Release"
# Name "LuaLib - Win32 Debug"
# Name "LuaLib - Win32 BetaRelease"
# Name "LuaLib - Win32 FastDebug"
# Name "LuaLib - Win32 Profiler"
# Begin Group "LuaSrc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LuaSrc\lapi.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lapi.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lcode.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lcode.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\ldebug.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\ldebug.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\ldo.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\ldo.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lfunc.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lfunc.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lgc.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lgc.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\llex.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\llex.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\llimits.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lmem.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lmem.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lobject.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lobject.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lopcodes.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lparser.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lparser.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lstate.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lstate.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lstring.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lstring.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\ltable.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\ltable.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\ltm.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\ltm.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lua.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\luadebug.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lundump.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lundump.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lvm.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lvm.h
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lzio.c
# End Source File
# Begin Source File

SOURCE=.\LuaSrc\lzio.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Script.cpp
# End Source File
# Begin Source File

SOURCE=.\Script.h
# End Source File
# End Target
# End Project
