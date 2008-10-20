# Microsoft Developer Studio Project File - Name="gSoapWzd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=gSoapWzd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gSoapWzd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gSoapWzd.mak" CFG="gSoapWzd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gSoapWzd - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "gSoapWzd - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"bin/gSoapWzd.exe"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"bin/gSoapWzd.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "gSoapWzd - Win32 Release"
# Name "gSoapWzd - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DlgReport.cpp
# End Source File
# Begin Source File

SOURCE=.\gSoapWzd.cpp
# End Source File
# Begin Source File

SOURCE=.\gSoapWzd.rc
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Soapcpp2View.cpp
# End Source File
# Begin Source File

SOURCE=.\SoapSrc.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DlgReport.h
# End Source File
# Begin Source File

SOURCE=.\gSoapWzd.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Soapcpp2View.h
# End Source File
# Begin Source File

SOURCE=.\SoapSrc.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\project\apache.mingw

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\project\apache.vc6

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\source\apache_gsoap.resh

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\project\client.mingw

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\project\Client.vc6

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\gSoapWzd.ico

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\gSoapWzd.rc2

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\gSoapWzdDoc.ico

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\pthread\libpthreadGC.resa

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\pthread\pthread.resh

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\pthread\pthreadGC.resdll

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\pthread\pthreadVC.resdll

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\pthread\pthreadVC.reslib

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\pthread\sched.resh

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\pthread\semaphore.resh

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\project\server.mingw

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\project\SERVER.vc6

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\source\stdsoap2.resc

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\source\stdsoap2.resh

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\source\theClt.resc
# End Source File
# Begin Source File

SOURCE=.\res\source\theClt.rescpp

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\project\theCltDll.mingw

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\project\TheCltDll.vc6

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\source\theSvr.resc

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\source\theSvr.rescpp

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp

!IF  "$(CFG)" == "gSoapWzd - Win32 Release"

!ELSEIF  "$(CFG)" == "gSoapWzd - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\History.Txt
# End Source File
# End Target
# End Project
