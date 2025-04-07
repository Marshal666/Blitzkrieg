# Microsoft Developer Studio Project File - Name="A7ExportModel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=A7ExportModel - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "A7ExportModel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "A7ExportModel.mak" CFG="A7ExportModel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "A7ExportModel - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "A7ExportModel - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/Tools/A7ExportModel", RTKAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "." /D "NDEBUG" /D "_DEVVERSION" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "NT_PLUGIN" /D "_DONT_USE_SINGLETON" /D "__MAYA4__" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Foundation.lib OpenMaya.lib OpenMayaAnim.lib /nologo /subsystem:windows /dll /machine:I386 /export:initializePlugin /export:uninitializePlugin

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "NT_PLUGIN" /D "_DONT_USE_SINGLETON" /D "__MAYA4__" /Yu"StdAfx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Foundation.lib OpenMaya.lib OpenMayaAnim.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /export:initializePlugin /export:uninitializePlugin

!ENDIF 

# Begin Target

# Name "A7ExportModel - Win32 Release"
# Name "A7ExportModel - Win32 Debug"
# Begin Group "Common"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h;hpp;hxx;hm;inl"
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
# Begin Group "Exporter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\A7ExportModel.cpp
# End Source File
# Begin Source File

SOURCE=.\A7ExportModel.h
# End Source File
# Begin Source File

SOURCE=.\Data.cpp
# End Source File
# Begin Source File

SOURCE=.\Data.h
# End Source File
# Begin Source File

SOURCE=.\pluginMain.cpp
# End Source File
# End Group
# Begin Group "MiniBall"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MiniBall\BoundingSphere.cpp

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MiniBall\BoundingSphere.h
# End Source File
# Begin Source File

SOURCE=.\MiniBall\BoundingVolume.cpp

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MiniBall\BoundingVolume.h
# End Source File
# Begin Source File

SOURCE=.\MiniBall\Matrix.cpp

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MiniBall\Matrix.h
# End Source File
# Begin Source File

SOURCE=.\MiniBall\Plane.cpp

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MiniBall\Plane.h
# End Source File
# Begin Source File

SOURCE=.\MiniBall\Point.cpp

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MiniBall\Point.h
# End Source File
# Begin Source File

SOURCE=.\MiniBall\Quaternion.cpp

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MiniBall\Quaternion.h
# End Source File
# Begin Source File

SOURCE=.\MiniBall\Sphere.cpp

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MiniBall\Sphere.h
# End Source File
# Begin Source File

SOURCE=.\MiniBall\Timer.cpp

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MiniBall\Timer.h
# End Source File
# Begin Source File

SOURCE=.\MiniBall\Tuple.cpp

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MiniBall\Tuple.h
# End Source File
# Begin Source File

SOURCE=.\MiniBall\Vector.cpp

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MiniBall\Vector.h
# End Source File
# Begin Source File

SOURCE=.\MiniBall\ViewFrustum.cpp

!IF  "$(CFG)" == "A7ExportModel - Win32 Release"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "A7ExportModel - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MiniBall\ViewFrustum.h
# End Source File
# End Group
# End Target
# End Project
