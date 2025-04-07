# Microsoft Developer Studio Project File - Name="StreamIOLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=StreamIOLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "StreamIOLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StreamIOLib.mak" CFG="StreamIOLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StreamIOLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "StreamIOLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "StreamIOLib - Win32 BetaRelease" (based on "Win32 (x86) Static Library")
!MESSAGE "StreamIOLib - Win32 FastDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "StreamIOLib - Win32 Profiler" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/StreamIOLib", QUVAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StreamIOLib - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "_MBCS" /D "_LIB" /D "_DONT_USE_SINGLETON" /D "__REDUCED_SINGLETON__" /D "WIN32" /D "NDEBUG" /D "_FINALRELEASE" /Yu"StdAfx.h" /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "StreamIOLib - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_MBCS" /D "_LIB" /D "_DONT_USE_SINGLETON" /D "__REDUCED_SINGLETON__" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /Yu"StdAfx.h" /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "StreamIOLib - Win32 BetaRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BetaRelease"
# PROP BASE Intermediate_Dir "BetaRelease"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BetaRelease"
# PROP Intermediate_Dir "BetaRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /Ot /Og /Op /D "_MBCS" /D "_LIB" /D "_DONT_USE_SINGLETON" /D "__REDUCED_SINGLETON__" /D "WIN32" /D "NDEBUG" /D "_BETARELEASE" /Yu"StdAfx.h" /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "StreamIOLib - Win32 FastDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "FastDebug"
# PROP BASE Intermediate_Dir "FastDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "FastDebug"
# PROP Intermediate_Dir "FastDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_DONT_USE_SINGLETON" /D "__REDUCED_SINGLETON__" /Yu"StdAfx.h" /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "StreamIOLib - Win32 Profiler"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "StreamIOLib___Win32_Profiler"
# PROP BASE Intermediate_Dir "StreamIOLib___Win32_Profiler"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Profiler"
# PROP Intermediate_Dir "Profiler"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_DONT_USE_SINGLETON" /D "__REDUCED_SINGLETON__" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_DONT_USE_SINGLETON" /D "__REDUCED_SINGLETON__" /Yu"StdAfx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "StreamIOLib - Win32 Release"
# Name "StreamIOLib - Win32 Debug"
# Name "StreamIOLib - Win32 BetaRelease"
# Name "StreamIOLib - Win32 FastDebug"
# Name "StreamIOLib - Win32 Profiler"
# Begin Group "Common"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Specific.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "StreamIOLib - Win32 Release"

# ADD CPP /MD /GR /Yc"StdAfx.h"

!ELSEIF  "$(CFG)" == "StreamIOLib - Win32 Debug"

# ADD CPP /MDd /GR /Yc"StdAfx.h"

!ELSEIF  "$(CFG)" == "StreamIOLib - Win32 BetaRelease"

# ADD BASE CPP /MD /GR /Yc"StdAfx.h"
# ADD CPP /MD /GR /Yc"StdAfx.h"

!ELSEIF  "$(CFG)" == "StreamIOLib - Win32 FastDebug"

# ADD BASE CPP /MD /GR /Yc"StdAfx.h"
# ADD CPP /MD /GR /Yc"StdAfx.h"

!ELSEIF  "$(CFG)" == "StreamIOLib - Win32 Profiler"

# ADD BASE CPP /MD /GR /Yc"StdAfx.h"
# ADD CPP /MD /GR /Yc"StdAfx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\stl_user_config.h
# End Source File
# End Group
# Begin Group "StreamIO"

# PROP Default_Filter ""
# Begin Group "Zip"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ZipFile.cpp
# End Source File
# Begin Source File

SOURCE=.\ZipFile.h
# End Source File
# Begin Source File

SOURCE=.\ZipFileSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\ZipFileSystem.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CommonFileSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonFileSystem.h
# End Source File
# Begin Source File

SOURCE=.\FileAttribs.h
# End Source File
# Begin Source File

SOURCE=.\FileSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\FileSystem.h
# End Source File
# Begin Source File

SOURCE=.\GetSLS.cpp
# End Source File
# Begin Source File

SOURCE=.\MemFileSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\MemFileSystem.h
# End Source File
# Begin Source File

SOURCE=.\ModFileSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\ModFileSystem.h
# End Source File
# Begin Source File

SOURCE=.\ProgressHook.h
# End Source File
# Begin Source File

SOURCE=.\SaveLoadSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveLoadSystem.h
# End Source File
# Begin Source File

SOURCE=.\StreamAdaptor.h
# End Source File
# Begin Source File

SOURCE=.\StreamIO.h
# End Source File
# Begin Source File

SOURCE=.\StreamIOHelper.h
# End Source File
# End Group
# Begin Group "DBIO"

# PROP Default_Filter ""
# Begin Group "Ini"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DataBase.h
# End Source File
# Begin Source File

SOURCE=.\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\IniFile.h
# End Source File
# End Group
# Begin Group "XML"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataTableXML.cpp
# End Source File
# Begin Source File

SOURCE=.\DataTableXML.h
# End Source File
# End Group
# End Group
# Begin Group "SaveLoad"

# PROP Default_Filter ""
# Begin Group "Structure Saver"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Streams.cpp
# End Source File
# Begin Source File

SOURCE=.\Streams.h
# End Source File
# Begin Source File

SOURCE=.\StructureSaver2.cpp
# End Source File
# Begin Source File

SOURCE=.\StructureSaver2.h
# End Source File
# End Group
# Begin Group "Data Tree"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DataTreeXML.cpp
# End Source File
# Begin Source File

SOURCE=.\DataTreeXML.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DTHelper.h
# End Source File
# Begin Source File

SOURCE=.\SSHelper.h
# End Source File
# Begin Source File

SOURCE=.\StructureSaver.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Singleton.cpp
# End Source File
# End Target
# End Project
