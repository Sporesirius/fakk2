# Microsoft Developer Studio Project File - Name="fgame" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=fgame - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fgame.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fgame.mak" CFG="fgame - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fgame - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "fgame - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/fakk2_code/fakk2_new/fgame", FYHAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fgame - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./Release"
# PROP Intermediate_Dir "./Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FGAME_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FGAME_EXPORTS" /D "GAME_DLL" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib winmm.lib /nologo /dll /map /machine:I386 /out:"../Release/fgamex86.dll"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "fgame - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "./Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FGAME_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FGAME_EXPORTS" /D "GAME_DLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib winmm.lib /nologo /dll /debug /machine:I386 /out:"../Debug/fgamex86.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "fgame - Win32 Release"
# Name "fgame - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\actor.cpp
# End Source File
# Begin Source File

SOURCE=.\ammo.cpp
# End Source File
# Begin Source File

SOURCE=.\animate.cpp
# End Source File
# Begin Source File

SOURCE=.\archive.cpp
# End Source File
# Begin Source File

SOURCE=.\armor.cpp
# End Source File
# Begin Source File

SOURCE=.\beam.cpp
# End Source File
# Begin Source File

SOURCE=.\behavior.cpp
# End Source File
# Begin Source File

SOURCE=.\bg_misc.c
# End Source File
# Begin Source File

SOURCE=.\bg_pmove.c
# End Source File
# Begin Source File

SOURCE=.\bspline.cpp
# End Source File
# Begin Source File

SOURCE=.\camera.cpp
# End Source File
# Begin Source File

SOURCE=.\characterstate.cpp
# End Source File
# Begin Source File

SOURCE=.\class.cpp
# End Source File
# Begin Source File

SOURCE=.\clusterbomb.cpp
# End Source File
# Begin Source File

SOURCE=.\crossbow.cpp
# End Source File
# Begin Source File

SOURCE=.\debuglines.cpp
# End Source File
# Begin Source File

SOURCE=.\decals.cpp
# End Source File
# Begin Source File

SOURCE=.\doors.cpp
# End Source File
# Begin Source File

SOURCE=.\earthquake.cpp
# End Source File
# Begin Source File

SOURCE=.\edenwater.cpp
# End Source File
# Begin Source File

SOURCE=.\entity.cpp
# End Source File
# Begin Source File

SOURCE=.\explosion.cpp
# End Source File
# Begin Source File

SOURCE=.\flamethrower.cpp
# End Source File
# Begin Source File

SOURCE=.\flashbang.cpp
# End Source File
# Begin Source File

SOURCE=.\g_main.cpp
# End Source File
# Begin Source File

SOURCE=.\g_phys.cpp
# End Source File
# Begin Source File

SOURCE=.\g_spawn.cpp
# End Source File
# Begin Source File

SOURCE=.\g_utils.cpp
# End Source File
# Begin Source File

SOURCE=.\game.cpp
# End Source File
# Begin Source File

SOURCE=.\game.def
# End Source File
# Begin Source File

SOURCE=.\gamecmds.cpp
# End Source File
# Begin Source File

SOURCE=.\gamecvars.cpp
# End Source File
# Begin Source File

SOURCE=.\gamescript.cpp
# End Source File
# Begin Source File

SOURCE=.\gibs.cpp
# End Source File
# Begin Source File

SOURCE=.\goo.cpp
# End Source File
# Begin Source File

SOURCE=.\gravpath.cpp
# End Source File
# Begin Source File

SOURCE=.\health.cpp
# End Source File
# Begin Source File

SOURCE=.\hornofconjuring.cpp
# End Source File
# Begin Source File

SOURCE=.\inventoryitem.cpp
# End Source File
# Begin Source File

SOURCE=.\ipfilter.cpp
# End Source File
# Begin Source File

SOURCE=.\item.cpp
# End Source File
# Begin Source File

SOURCE=.\level.cpp
# End Source File
# Begin Source File

SOURCE=.\light.cpp
# End Source File
# Begin Source File

SOURCE=.\listener.cpp
# End Source File
# Begin Source File

SOURCE=.\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\mover.cpp
# End Source File
# Begin Source File

SOURCE=.\nature.cpp
# End Source File
# Begin Source File

SOURCE=.\navigate.cpp
# End Source File
# Begin Source File

SOURCE=.\object.cpp
# End Source File
# Begin Source File

SOURCE=.\path.cpp
# End Source File
# Begin Source File

SOURCE=.\player.cpp
# End Source File
# Begin Source File

SOURCE=.\player_combat.cpp
# End Source File
# Begin Source File

SOURCE=.\player_util.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerStart.cpp
# End Source File
# Begin Source File

SOURCE=.\portal.cpp
# End Source File
# Begin Source File

SOURCE=.\powerups.cpp
# End Source File
# Begin Source File

SOURCE=.\q_math.c
# End Source File
# Begin Source File

SOURCE=.\q_mathsys.c
# End Source File
# Begin Source File

SOURCE=.\q_shared.c
# End Source File
# Begin Source File

SOURCE=.\rope.cpp
# End Source File
# Begin Source File

SOURCE=.\script.cpp
# End Source File
# Begin Source File

SOURCE=.\scriptmaster.cpp
# End Source File
# Begin Source File

SOURCE=.\scriptslave.cpp
# End Source File
# Begin Source File

SOURCE=.\scriptvariable.cpp
# End Source File
# Begin Source File

SOURCE=.\sentient.cpp
# End Source File
# Begin Source File

SOURCE=.\shield.cpp
# End Source File
# Begin Source File

SOURCE=.\soulsucker.cpp
# End Source File
# Begin Source File

SOURCE=.\soundman.cpp
# End Source File
# Begin Source File

SOURCE=.\spawners.cpp
# End Source File
# Begin Source File

SOURCE=.\specialfx.cpp
# End Source File
# Begin Source File

SOURCE=.\steering.cpp
# End Source File
# Begin Source File

SOURCE=.\str.cpp
# End Source File
# Begin Source File

SOURCE=.\sword.cpp
# End Source File
# Begin Source File

SOURCE=.\trigger.cpp
# End Source File
# Begin Source File

SOURCE=.\vehicle.cpp
# End Source File
# Begin Source File

SOURCE=.\viewthing.cpp
# End Source File
# Begin Source File

SOURCE=.\weapon.cpp
# End Source File
# Begin Source File

SOURCE=.\weaputils.cpp
# End Source File
# Begin Source File

SOURCE=..\win32\win_bounds.cpp
# End Source File
# Begin Source File

SOURCE=.\worldspawn.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\actor.h
# End Source File
# Begin Source File

SOURCE=.\ammo.h
# End Source File
# Begin Source File

SOURCE=.\animate.h
# End Source File
# Begin Source File

SOURCE=.\archive.h
# End Source File
# Begin Source File

SOURCE=.\armor.h
# End Source File
# Begin Source File

SOURCE=.\beam.h
# End Source File
# Begin Source File

SOURCE=.\behavior.h
# End Source File
# Begin Source File

SOURCE=.\bg_local.h
# End Source File
# Begin Source File

SOURCE=.\bg_public.h
# End Source File
# Begin Source File

SOURCE=.\bspline.h
# End Source File
# Begin Source File

SOURCE=.\camera.h
# End Source File
# Begin Source File

SOURCE=.\characterstate.h
# End Source File
# Begin Source File

SOURCE=.\class.h
# End Source File
# Begin Source File

SOURCE=.\clusterbomb.h
# End Source File
# Begin Source File

SOURCE=.\container.h
# End Source File
# Begin Source File

SOURCE=.\crossbow.h
# End Source File
# Begin Source File

SOURCE=.\debuglines.h
# End Source File
# Begin Source File

SOURCE=.\decals.h
# End Source File
# Begin Source File

SOURCE=.\doors.h
# End Source File
# Begin Source File

SOURCE=.\earthquake.h
# End Source File
# Begin Source File

SOURCE=.\edenwater.h
# End Source File
# Begin Source File

SOURCE=.\entity.h
# End Source File
# Begin Source File

SOURCE=.\explosion.h
# End Source File
# Begin Source File

SOURCE=.\flamethrower.h
# End Source File
# Begin Source File

SOURCE=.\flashbang.h
# End Source File
# Begin Source File

SOURCE=.\g_local.h
# End Source File
# Begin Source File

SOURCE=.\g_main.h
# End Source File
# Begin Source File

SOURCE=.\g_phys.h
# End Source File
# Begin Source File

SOURCE=.\g_public.h
# End Source File
# Begin Source File

SOURCE=.\g_spawn.h
# End Source File
# Begin Source File

SOURCE=.\g_utils.h
# End Source File
# Begin Source File

SOURCE=.\game.h
# End Source File
# Begin Source File

SOURCE=.\gamecmds.h
# End Source File
# Begin Source File

SOURCE=.\gamecvars.h
# End Source File
# Begin Source File

SOURCE=.\gamescript.h
# End Source File
# Begin Source File

SOURCE=.\gibs.h
# End Source File
# Begin Source File

SOURCE=.\goo.h
# End Source File
# Begin Source File

SOURCE=.\gravpath.h
# End Source File
# Begin Source File

SOURCE=.\health.h
# End Source File
# Begin Source File

SOURCE=.\hornofconjuring.h
# End Source File
# Begin Source File

SOURCE=.\inventoryitem.h
# End Source File
# Begin Source File

SOURCE=.\ipfilter.h
# End Source File
# Begin Source File

SOURCE=.\item.h
# End Source File
# Begin Source File

SOURCE=.\level.h
# End Source File
# Begin Source File

SOURCE=.\light.h
# End Source File
# Begin Source File

SOURCE=.\Linklist.h
# End Source File
# Begin Source File

SOURCE=.\listener.h
# End Source File
# Begin Source File

SOURCE=.\misc.h
# End Source File
# Begin Source File

SOURCE=.\mover.h
# End Source File
# Begin Source File

SOURCE=.\nature.h
# End Source File
# Begin Source File

SOURCE=.\navigate.h
# End Source File
# Begin Source File

SOURCE=.\object.h
# End Source File
# Begin Source File

SOURCE=.\path.h
# End Source File
# Begin Source File

SOURCE=.\player.h
# End Source File
# Begin Source File

SOURCE=.\PlayerStart.h
# End Source File
# Begin Source File

SOURCE=.\portal.h
# End Source File
# Begin Source File

SOURCE=.\powerups.h
# End Source File
# Begin Source File

SOURCE=.\q_shared.h
# End Source File
# Begin Source File

SOURCE=.\queue.h
# End Source File
# Begin Source File

SOURCE=.\rope.h
# End Source File
# Begin Source File

SOURCE=.\script.h
# End Source File
# Begin Source File

SOURCE=.\scriptmaster.h
# End Source File
# Begin Source File

SOURCE=.\scriptslave.h
# End Source File
# Begin Source File

SOURCE=.\scriptvariable.h
# End Source File
# Begin Source File

SOURCE=.\sentient.h
# End Source File
# Begin Source File

SOURCE=.\shield.h
# End Source File
# Begin Source File

SOURCE=.\soulsucker.h
# End Source File
# Begin Source File

SOURCE=.\soundman.h
# End Source File
# Begin Source File

SOURCE=.\spawners.h
# End Source File
# Begin Source File

SOURCE=.\specialfx.h
# End Source File
# Begin Source File

SOURCE=.\stack.h
# End Source File
# Begin Source File

SOURCE=.\steering.h
# End Source File
# Begin Source File

SOURCE=.\str.h
# End Source File
# Begin Source File

SOURCE=.\surfaceflags.h
# End Source File
# Begin Source File

SOURCE=.\sword.h
# End Source File
# Begin Source File

SOURCE=.\trigger.h
# End Source File
# Begin Source File

SOURCE=.\umap.h
# End Source File
# Begin Source File

SOURCE=.\vector.h
# End Source File
# Begin Source File

SOURCE=.\vehicle.h
# End Source File
# Begin Source File

SOURCE=.\viewthing.h
# End Source File
# Begin Source File

SOURCE=.\weapon.h
# End Source File
# Begin Source File

SOURCE=.\weaputils.h
# End Source File
# Begin Source File

SOURCE=.\worldspawn.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
