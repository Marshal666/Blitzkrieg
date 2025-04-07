# Microsoft Developer Studio Project File - Name="InterfaceSystemTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=InterfaceSystemTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "InterfaceSystemTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "InterfaceSystemTest.mak" CFG="InterfaceSystemTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "InterfaceSystemTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "InterfaceSystemTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/InterfaceSystemTest", KCGBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "InterfaceSystemTest - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "InterfaceSystemTest - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "InterfaceSystemTest - Win32 Release"
# Name "InterfaceSystemTest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Background.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\DeepCPtrCopy.cpp
# End Source File
# Begin Source File

SOURCE=.\EffectorMoveTo.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceSystemTest.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceSystemTest.rc
# End Source File
# Begin Source File

SOURCE=.\InterfaceSystemTestDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\IUIInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageReaction.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageReactions.cpp
# End Source File
# Begin Source File

SOURCE=.\SegmentCaller.cpp
# End Source File
# Begin Source File

SOURCE=.\SInterfaceConsts.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UIScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Window.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowConsole.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowEditLine.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowMessageHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowMultiBkg.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowTextView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Background.h
# End Source File
# Begin Source File

SOURCE=.\CustomCheck.h
# End Source File
# Begin Source File

SOURCE=.\DeepCPtrCopy.h
# End Source File
# Begin Source File

SOURCE=.\EffectorMoveTo.h
# End Source File
# Begin Source File

SOURCE=.\EffectorRunReaction.h
# End Source File
# Begin Source File

SOURCE=.\Heap.h
# End Source File
# Begin Source File

SOURCE=.\IMessageReaction.h
# End Source File
# Begin Source File

SOURCE=.\Interface.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceSystemTest.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceSystemTestDlg.h
# End Source File
# Begin Source File

SOURCE=.\IUIInternal.h
# End Source File
# Begin Source File

SOURCE=.\MessageReaction.h
# End Source File
# Begin Source File

SOURCE=.\MessageReactions.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SegmentCaller.h
# End Source File
# Begin Source File

SOURCE=.\SInterfaceConsts.h
# End Source File
# Begin Source File

SOURCE=.\Specific.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UIScreen.h
# End Source File
# Begin Source File

SOURCE=.\Window.h
# End Source File
# Begin Source File

SOURCE=.\WindowConsole.h
# End Source File
# Begin Source File

SOURCE=.\WindowEditLine.h
# End Source File
# Begin Source File

SOURCE=.\WindowMessageHandle.h
# End Source File
# Begin Source File

SOURCE=.\WindowMultiBkg.h
# End Source File
# Begin Source File

SOURCE=.\WindowScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\WindowSlider.h
# End Source File
# Begin Source File

SOURCE=.\WindowTextView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\InterfaceSystemTest.ico
# End Source File
# Begin Source File

SOURCE=.\res\InterfaceSystemTest.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
