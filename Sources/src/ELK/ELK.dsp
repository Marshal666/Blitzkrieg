# Microsoft Developer Studio Project File - Name="ELK" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ELK - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ELK.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ELK.mak" CFG="ELK - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ELK - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ELK - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ELK - Win32 FastDebug" (based on "Win32 (x86) Application")
!MESSAGE "ELK - Win32 BetaRelease" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/ELK", RHSAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ELK - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /D "_MBCS" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 htmlhelp.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ELK - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_DEBUG" /D "_STL_RANGE_CHECK" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /D "_MBCS" /Yu"StdAfx.h" /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "ELK - Win32 FastDebug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ELK___Win32_FastDebug"
# PROP BASE Intermediate_Dir "ELK___Win32_FastDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "FastDebug"
# PROP Intermediate_Dir "FastDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 htmlhelp.lib /nologo /subsystem:windows /map /debug /machine:I386

!ELSEIF  "$(CFG)" == "ELK - Win32 BetaRelease"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ELK___Win32_BetaRelease"
# PROP BASE Intermediate_Dir "ELK___Win32_BetaRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BetaRelease"
# PROP Intermediate_Dir "BetaRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /Ot /Og /Op /Ob2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "__AFX__" /D "_MBCS" /Yu"StdAfx.h" /FD /c
# SUBTRACT CPP /Ox
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 htmlhelp.lib /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "ELK - Win32 Release"
# Name "ELK - Win32 Debug"
# Name "ELK - Win32 FastDebug"
# Name "ELK - Win32 BetaRelease"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BlitzkriegELKDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseFontsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateFilterDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateFilterNameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ELK.cpp
# End Source File
# Begin Source File

SOURCE=.\ELK_Consts.cpp
# End Source File
# Begin Source File

SOURCE=.\ELK_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\ELK_StaticMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\ELK_TreeWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportFromGameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportFromPAKDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportFromXLSDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\InputViewDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\InputViewWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ResizeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SpellChecker.cpp
# End Source File
# Begin Source File

SOURCE=.\StatisticDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TranslateEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeDockWindow.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDialog.h
# End Source File
# Begin Source File

SOURCE=.\BlitzkriegELKDatabase.h
# End Source File
# Begin Source File

SOURCE=.\ChooseFontsDialog.h
# End Source File
# Begin Source File

SOURCE=.\CreateFilterDialog.h
# End Source File
# Begin Source File

SOURCE=.\CreateFilterNameDialog.h
# End Source File
# Begin Source File

SOURCE=.\CSAPI.H
# End Source File
# Begin Source File

SOURCE=.\ELK.h
# End Source File
# Begin Source File

SOURCE=.\ELK_TreeWindow.h
# End Source File
# Begin Source File

SOURCE=.\ELK_Types.h
# End Source File
# Begin Source File

SOURCE=.\htmlhelp.h
# End Source File
# Begin Source File

SOURCE=.\ImportFromGameDialog.h
# End Source File
# Begin Source File

SOURCE=.\ImportFromPAKDialog.h
# End Source File
# Begin Source File

SOURCE=.\ImportFromXLSDialog.h
# End Source File
# Begin Source File

SOURCE=.\InputViewDialog.h
# End Source File
# Begin Source File

SOURCE=.\InputViewWindow.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Messages.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.h
# End Source File
# Begin Source File

SOURCE=.\ResizeDialog.h
# End Source File
# Begin Source File

SOURCE=.\SpellChecker.h
# End Source File
# Begin Source File

SOURCE=.\StatisticDialog.h
# End Source File
# Begin Source File

SOURCE=.\TranslateEdit.h
# End Source File
# Begin Source File

SOURCE=.\TreeDockWindow.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "Resource VSS Check Out"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ELK.rc
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Bitmaps\0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Icons\back.ico
# End Source File
# Begin Source File

SOURCE=.\res\ELK.rc2
# End Source File
# Begin Source File

SOURCE=.\res\icons\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icons\idr_short_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icons\next.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icons\pback.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icons\pnext.ico
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\short_toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\short_toolbarlarge.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\StatisticNormalImageList.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\toolbarlarge.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmaps\TreeNormalImageList.bmp
# End Source File
# End Group
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
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\htmlhelp.lib
# End Source File
# End Target
# End Project
