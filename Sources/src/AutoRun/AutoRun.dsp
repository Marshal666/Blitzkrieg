# Microsoft Developer Studio Project File - Name="AutoRun" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AutoRun - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AutoRun.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AutoRun.mak" CFG="AutoRun - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AutoRun - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AutoRun - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/AutoRun", FDUAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AutoRun - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Winmm.lib Shell32.lib /nologo /subsystem:windows /machine:I386 /swaprun:cd
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "AutoRun - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Winmm.lib Shell32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AutoRun - Win32 Release"
# Name "AutoRun - Win32 Debug"
# Begin Group "AutoRun Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AutoRunDialog.cpp

!IF  "$(CFG)" == "AutoRun - Win32 Release"

!ELSEIF  "$(CFG)" == "AutoRun - Win32 Debug"

# ADD CPP /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AutoRunDialog.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\autorun.ico
# End Source File
# Begin Source File

SOURCE=.\AutoRun.rc
# End Source File
# Begin Source File

SOURCE=.\res\AutoRun.rc2
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AutoRun.cpp

!IF  "$(CFG)" == "AutoRun - Win32 Release"

!ELSEIF  "$(CFG)" == "AutoRun - Win32 Debug"

# ADD CPP /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AutoRun.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "ARDataStorage"

# PROP Default_Filter ""
# Begin Group "ARBitmap"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ARBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\ARBitmap.h
# End Source File
# End Group
# Begin Group "ARText"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ARText.cpp
# End Source File
# Begin Source File

SOURCE=.\ARText.h
# End Source File
# End Group
# Begin Group "ARConfiguration"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ARConfiguration.cpp
# End Source File
# Begin Source File

SOURCE=.\ARConfiguration.h
# End Source File
# End Group
# Begin Group "ARSound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ARSound.cpp
# End Source File
# Begin Source File

SOURCE=.\ARSound.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DataStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\DataStorage.h
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FileUtils.cpp

!IF  "$(CFG)" == "AutoRun - Win32 Release"

!ELSEIF  "$(CFG)" == "AutoRun - Win32 Debug"

# ADD CPP /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FileUtils.h
# End Source File
# Begin Source File

SOURCE=.\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\StrProc.cpp
# End Source File
# Begin Source File

SOURCE=.\StrProc.h
# End Source File
# Begin Source File

SOURCE=.\ZipFile.cpp

!IF  "$(CFG)" == "AutoRun - Win32 Release"

!ELSEIF  "$(CFG)" == "AutoRun - Win32 Debug"

# ADD CPP /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ZipFile.h
# End Source File
# End Group
# Begin Group "Types"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AR_Consts.cpp
# End Source File
# Begin Source File

SOURCE=.\AR_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\AR_Types.h
# End Source File
# End Group
# End Target
# End Project
