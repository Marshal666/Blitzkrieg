# Microsoft Developer Studio Project File - Name="RandomMapGen" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RandomMapGen - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RandomMapGen.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RandomMapGen.mak" CFG="RandomMapGen - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RandomMapGen - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RandomMapGen - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RandomMapGen - Win32 BetaRelease" (based on "Win32 (x86) Static Library")
!MESSAGE "RandomMapGen - Win32 FastDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "RandomMapGen - Win32 Profiler" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/RandomMapGen", MGRAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RandomMapGen - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "_FINALRELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /Zm200 /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RandomMapGen - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_ASSERT_SLOW" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /Yu"StdAfx.h" /FD /GZ /Zm250 /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RandomMapGen - Win32 BetaRelease"

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
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /Ot /Og /Op /Ob2 /D "_DO_ASSERT_SLOW" /D "_BETARELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /Yu"StdAfx.h" /FD /Zm200 /c
# SUBTRACT CPP /Ox /Oi
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RandomMapGen - Win32 FastDebug"

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
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Zd /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_DO_ASSERT_SLOW" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "NDEBUG" /D "_DO_ASSERT_SLOW" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /Zm200 /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RandomMapGen - Win32 Profiler"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "RandomMapGen___Win32_Profiler"
# PROP BASE Intermediate_Dir "RandomMapGen___Win32_Profiler"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Profiler"
# PROP Intermediate_Dir "Profiler"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "NDEBUG" /D "_DO_ASSERT_SLOW" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /Yu"StdAfx.h" /FD /Zm200 /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_FINALRELEASE" /D "_PROFILER" /Yu"StdAfx.h" /FD /Zm200 /c
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

# Name "RandomMapGen - Win32 Release"
# Name "RandomMapGen - Win32 Debug"
# Name "RandomMapGen - Win32 BetaRelease"
# Name "RandomMapGen - Win32 FastDebug"
# Name "RandomMapGen - Win32 Profiler"
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
# Begin Group "Random Map Generator"

# PROP Default_Filter ""
# Begin Group "External Builders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BetaSpline.cpp
# End Source File
# Begin Source File

SOURCE=.\BetaSpline.h
# End Source File
# Begin Source File

SOURCE=.\Builders.h
# End Source File
# Begin Source File

SOURCE=.\PNoise.cpp
# End Source File
# Begin Source File

SOURCE=.\PNoise.h
# End Source File
# Begin Source File

SOURCE=.\TerrainBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\TerrainBuilder.h
# End Source File
# Begin Source File

SOURCE=.\TerrainGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\TerrainGenerator.h
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Bresenham_Types.h
# End Source File
# Begin Source File

SOURCE=.\IB_Types.h
# End Source File
# Begin Source File

SOURCE=.\LA_Types.h
# End Source File
# Begin Source File

SOURCE=.\MapInfo_Types.h
# End Source File
# Begin Source File

SOURCE=.\MiniMap_Types.h
# End Source File
# Begin Source File

SOURCE=.\Polygons_Types.h
# End Source File
# Begin Source File

SOURCE=.\Registry_Types.h
# End Source File
# Begin Source File

SOURCE=.\Resource_Types.h
# End Source File
# Begin Source File

SOURCE=.\RMG_Types.h
# End Source File
# Begin Source File

SOURCE=.\RP_Types.h
# End Source File
# Begin Source File

SOURCE=.\VA_Types.h
# End Source File
# Begin Source File

SOURCE=.\VSO_Types.h
# End Source File
# Begin Source File

SOURCE=.\WV_Types.h
# End Source File
# End Group
# Begin Group "Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IB_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\IB_StaticMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\LA_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\MapInfo_CheckSums.cpp
# End Source File
# Begin Source File

SOURCE=.\MapInfo_Consts.cpp
# End Source File
# Begin Source File

SOURCE=.\MapInfo_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\MapInfo_StaticMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\MapInfo_StaticMethods_MiniMapCreation.cpp
# End Source File
# Begin Source File

SOURCE=.\MapInfo_StaticMethods_RMGeneration.cpp
# End Source File
# Begin Source File

SOURCE=.\MapInfo_StaticMethods_SoundsCreation.cpp
# End Source File
# Begin Source File

SOURCE=.\MiniMap_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\Polygons_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry_Sources.cpp
# End Source File
# Begin Source File

SOURCE=.\Resource_Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\Resource_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\Resource_StaticMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_Consts.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\RMG_StaticMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\RP_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\VA_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\VA_StaticMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\VSO_Methods.cpp
# End Source File
# Begin Source File

SOURCE=.\VSO_StaticMethods.cpp
# End Source File
# End Group
# End Group
# End Target
# End Project
