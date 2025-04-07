# Microsoft Developer Studio Project File - Name="GameSpy" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GameSpy - Win32 Profiler
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GameSpy.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GameSpy.mak" CFG="GameSpy - Win32 Profiler"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GameSpy - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GameSpy - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "GameSpy - Win32 FastDebug" (based on "Win32 (x86) Static Library")
!MESSAGE "GameSpy - Win32 BetaRelease" (based on "Win32 (x86) Static Library")
!MESSAGE "GameSpy - Win32 Profiler" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/A7/GameSpy", QEYAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GameSpy - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "_FINALRELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "GameSpy - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /YX /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "GameSpy - Win32 FastDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "FastDebug"
# PROP BASE Intermediate_Dir "FastDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FastDebug"
# PROP Intermediate_Dir "FastDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Od /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "_DO_CHECKED_CAST" /YX /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "GameSpy - Win32 BetaRelease"

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
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D "_FINALRELEASE" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /Ot /Og /Op /Ob2 /D "_BETARELEASE" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "GameSpy - Win32 Profiler"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Profiler"
# PROP BASE Intermediate_Dir "Profiler"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Profiler"
# PROP Intermediate_Dir "Profiler"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_WINDOWS" /D "_DO_CHECKED_CAST" /D "WIN32" /D "_DEBUG" /D "_STL_RANGE_CHECK" /YX /FD /GZ /c
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

# Name "GameSpy - Win32 Release"
# Name "GameSpy - Win32 Debug"
# Name "GameSpy - Win32 FastDebug"
# Name "GameSpy - Win32 BetaRelease"
# Name "GameSpy - Win32 Profiler"
# Begin Source File

SOURCE=.\chat\chat.h
# End Source File
# Begin Source File

SOURCE=.\chat\chatCallbacks.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\chat\chatCallbacks.h
# End Source File
# Begin Source File

SOURCE=.\chat\chatChannel.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\chat\chatChannel.h
# End Source File
# Begin Source File

SOURCE=.\chat\chatCrypt.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\chat\chatCrypt.h
# End Source File
# Begin Source File

SOURCE=.\chat\chatHandlers.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\chat\chatHandlers.h
# End Source File
# Begin Source File

SOURCE=.\chat\chatMain.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\chat\chatMain.h
# End Source File
# Begin Source File

SOURCE=.\chat\chatSocket.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\chat\chatSocket.h
# End Source File
# Begin Source File

SOURCE=.\darray.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cengine\darray.h
# End Source File
# Begin Source File

SOURCE=.\darray.h
# End Source File
# Begin Source File

SOURCE=.\cengine\goaceng.h
# End Source File
# Begin Source File

SOURCE=.\queryreporting\gqueryreporting.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\queryreporting\gqueryreporting.h
# End Source File
# Begin Source File

SOURCE=.\cengine\gserver.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cengine\gserver.h
# End Source File
# Begin Source File

SOURCE=.\cengine\gserverlist.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cengine\gutil.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cengine\gutil.h
# End Source File
# Begin Source File

SOURCE=.\hashtable.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cengine\hashtable.h
# End Source File
# Begin Source File

SOURCE=.\hashtable.h
# End Source File
# Begin Source File

SOURCE=.\md5.h
# End Source File
# Begin Source File

SOURCE=.\md5c.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\nonport.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cengine\nonport.h
# End Source File
# Begin Source File

SOURCE=.\nonport.h
# End Source File
# Begin Source File

SOURCE=.\peer\peer.h
# End Source File
# Begin Source File

SOURCE=.\peer\peerCallbacks.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\peer\peerCallbacks.h
# End Source File
# Begin Source File

SOURCE=.\peer\peerCEngine.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\peer\peerCEngine.h
# End Source File
# Begin Source File

SOURCE=.\peer\peerGlobalCallbacks.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\peer\peerGlobalCallbacks.h
# End Source File
# Begin Source File

SOURCE=.\peer\peerKeys.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\peer\peerKeys.h
# End Source File
# Begin Source File

SOURCE=.\peer\peerMain.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\peer\peerMain.h
# End Source File
# Begin Source File

SOURCE=.\peer\peerMangle.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\peer\peerMangle.h
# End Source File
# Begin Source File

SOURCE=.\peer\peerOperations.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\peer\peerOperations.h
# End Source File
# Begin Source File

SOURCE=.\peer\peerPing.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\peer\peerPing.h
# End Source File
# Begin Source File

SOURCE=.\peer\peerPlayers.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\peer\peerPlayers.h
# End Source File
# Begin Source File

SOURCE=.\peer\peerRooms.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\peer\peerRooms.h
# End Source File
# Begin Source File

SOURCE=.\pinger\pinger.h
# End Source File
# Begin Source File

SOURCE=.\pinger\pingerMain.c
# SUBTRACT CPP /YX
# End Source File
# End Target
# End Project
