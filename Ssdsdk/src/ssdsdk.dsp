# Microsoft Developer Studio Project File - Name="ssdsdk" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ssdsdk - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ssdsdk.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ssdsdk.mak" CFG="ssdsdk - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ssdsdk - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ssdsdk - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ssdsdk - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ssdsdk - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "simple___Win32_Debug"
# PROP BASE Intermediate_Dir "simple___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\ssdsdkd.lib"

!ENDIF 

# Begin Target

# Name "ssdsdk - Win32 Release"
# Name "ssdsdk - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ARACrypt.cpp
# End Source File
# Begin Source File

SOURCE=.\CPUDetails.cpp
# End Source File
# Begin Source File

SOURCE=.\CryptString.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLisence.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLoad.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptReg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSend.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUsrReg.cpp
# End Source File
# Begin Source File

SOURCE=.\DynDialogEx.cpp
# End Source File
# Begin Source File

SOURCE=.\DynDialogItemEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ProductInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Rc4.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\SSD.cpp
# End Source File
# Begin Source File

SOURCE=.\ssdsdk.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysInfo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ARACrypt.h
# End Source File
# Begin Source File

SOURCE=.\CPUDetails.h
# End Source File
# Begin Source File

SOURCE=.\CRC32.h
# End Source File
# Begin Source File

SOURCE=.\CryptString.h
# End Source File
# Begin Source File

SOURCE=.\DlgLisence.h
# End Source File
# Begin Source File

SOURCE=.\DlgLoad.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptReg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSend.h
# End Source File
# Begin Source File

SOURCE=.\DlgUsrReg.h
# End Source File
# Begin Source File

SOURCE=.\DynDialogEx.h
# End Source File
# Begin Source File

SOURCE=.\DynDialogItemEx.h
# End Source File
# Begin Source File

SOURCE=.\ProductInfo.h
# End Source File
# Begin Source File

SOURCE=.\Rc4.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\SSD.h
# End Source File
# Begin Source File

SOURCE=.\ssdsdk.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SysInfo.h
# End Source File
# End Group
# End Target
# End Project
