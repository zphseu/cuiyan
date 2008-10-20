# Microsoft Developer Studio Project File - Name="EdFcMod1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=EdFcMod1 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EdFcMod1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EdFcMod1.mak" CFG="EdFcMod1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EdFcMod1 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EdFcMod1 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EdFcMod1 - Win32 Debug"

# PROP BASE Use_MFC 6
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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../Include" /I "../EdFcLib/zlib" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_MSVC6_" /Yu"stdafx.h" /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x804 /i "$(IntDir)" /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib olch2d7.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /out:"..\done\EdFcMod1.so" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib olch2d7.lib ../Lib/EdFcLib6.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /out:"..\done\EdFcMod16.so" /implib:"Debug/EdFcMod1.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "EdFcMod1 - Win32 Release"

# PROP BASE Use_MFC 6
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
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /I "../Include" /I "../EdFcLib/zlib" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_MSVC6_" /Yu"stdafx.h" /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x804 /i "$(IntDir)" /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib olch2d7.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /out:"..\done\EdFcMod1.so" /pdbtype:sept /opt:ref /opt:icf
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib olch2d7.lib ../Lib/EdFcLib6.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /out:"..\done\EdFcMod16.so" /implib:"Release/EdFcMod1.lib" /pdbtype:sept /opt:ref /opt:icf
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "EdFcMod1 - Win32 Debug"
# Name "EdFcMod1 - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=.\DlgImport.cpp
DEP_CPP_DLGIM=\
	"..\Include\PathDialog.h"\
	".\DlgImport.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EdFcMod1.cpp
DEP_CPP_EDFCM=\
	"..\Include\BarLine.h"\
	"..\Include\CellRange.h"\
	"..\Include\EasyReport.h"\
	"..\Include\Gradient.h"\
	"..\Include\Graphics.h"\
	"..\Include\GridCell.h"\
	"..\Include\GridCellBase.h"\
	"..\Include\GridCtrl.h"\
	"..\Include\GridDropTarget.h"\
	"..\Include\Pie.h"\
	"..\Include\Progress.h"\
	"..\Include\ProgressCtrlX.h"\
	"..\Include\TitleTip.h"\
	"..\Include\ZipArchive.h"\
	"..\Include\ZipAutoBuffer.h"\
	"..\Include\ZipBigFile.h"\
	"..\Include\ZipCentralDir.h"\
	"..\Include\ZipException.h"\
	"..\Include\ZipFileHeader.h"\
	"..\Include\ZipInternalInfo.h"\
	"..\Include\ZipStorage.h"\
	".\DlgImport.h"\
	".\EdHtmlView.h"\
	".\EdRptDoc.h"\
	".\EdRptExport.h"\
	".\EdRptTpl.h"\
	".\EdRptView.h"\
	".\EdStat2View.h"\
	".\EdStatDoc.h"\
	".\EdStatRptView.h"\
	".\EdStatTpl.h"\
	".\EdStatView.h"\
	".\stdafx.h"\
	".\ZipArc.h"\
	{$(INCLUDE)}"Chart7\och2dMFC.h"\
	{$(INCLUDE)}"Chart7\olch2d.h"\
	{$(INCLUDE)}"Chart7\olch2dcm.h"\
	
NODEP_CPP_EDFCM=\
	"..\Include\zlib.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EdFcMod1.def
# End Source File
# Begin Source File

SOURCE=.\EdHtmlView.cpp
DEP_CPP_EDHTM=\
	".\EdHtmlView.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EdRptDoc.cpp
DEP_CPP_EDRPT=\
	"..\Include\CellRange.h"\
	"..\Include\Gradient.h"\
	"..\Include\GridCell.h"\
	"..\Include\GridCellBase.h"\
	"..\Include\GridCtrl.h"\
	"..\Include\GridDropTarget.h"\
	"..\Include\Progress.h"\
	"..\Include\ProgressCtrlX.h"\
	"..\Include\TitleTip.h"\
	".\EdRptDoc.h"\
	".\EdRptTpl.h"\
	".\EdRptView.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EdRptExport.cpp
DEP_CPP_EDRPTE=\
	"..\EdFcLib\zlib\zconf.h"\
	"..\EdFcLib\zlib\zlib.h"\
	"..\Include\CellRange.h"\
	"..\Include\GridCell.h"\
	"..\Include\GridCellBase.h"\
	"..\Include\GridCtrl.h"\
	"..\Include\GridDropTarget.h"\
	"..\Include\TitleTip.h"\
	"..\Include\ZipArchive.h"\
	"..\Include\ZipAutoBuffer.h"\
	"..\Include\ZipBigFile.h"\
	"..\Include\ZipCentralDir.h"\
	"..\Include\ZipException.h"\
	"..\Include\ZipFileHeader.h"\
	"..\Include\ZipInternalInfo.h"\
	"..\Include\ZipStorage.h"\
	".\DlgImport.h"\
	".\EdRptDoc.h"\
	".\EdRptExport.h"\
	".\EdRptTpl.h"\
	".\stdafx.h"\
	".\ZipArc.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EdRptTpl.cpp
DEP_CPP_EDRPTT=\
	"..\Include\IniFile.h"\
	".\EdRptTpl.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EdRptView.cpp
DEP_CPP_EDRPTV=\
	"..\Include\CellRange.h"\
	"..\Include\Gradient.h"\
	"..\Include\GridCell.h"\
	"..\Include\GridCellBase.h"\
	"..\Include\GridCtrl.h"\
	"..\Include\GridDropTarget.h"\
	"..\Include\Progress.h"\
	"..\Include\ProgressCtrlX.h"\
	"..\Include\TitleTip.h"\
	"..\Include\ZipArchive.h"\
	"..\Include\ZipAutoBuffer.h"\
	"..\Include\ZipBigFile.h"\
	"..\Include\ZipCentralDir.h"\
	"..\Include\ZipException.h"\
	"..\Include\ZipFileHeader.h"\
	"..\Include\ZipInternalInfo.h"\
	"..\Include\ZipStorage.h"\
	".\EdRptDoc.h"\
	".\EdRptExport.h"\
	".\EdRptTpl.h"\
	".\EdRptView.h"\
	".\stdafx.h"\
	".\ZipArc.h"\
	
NODEP_CPP_EDRPTV=\
	"..\Include\zlib.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EdStat2View.cpp
DEP_CPP_EDSTA=\
	".\EdStat2View.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"Chart7\och2dMFC.cpp"\
	{$(INCLUDE)}"Chart7\och2dMFC.h"\
	{$(INCLUDE)}"Chart7\olch2d.h"\
	{$(INCLUDE)}"Chart7\olch2dcm.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EdStatDoc.cpp
DEP_CPP_EDSTAT=\
	"..\Include\BarLine.h"\
	"..\Include\EasyReport.h"\
	"..\Include\Graphics.h"\
	"..\Include\Pie.h"\
	".\EdStatDoc.h"\
	".\EdStatTpl.h"\
	".\GraphData.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EdStatRptView.cpp
DEP_CPP_EDSTATR=\
	"..\Include\BarLine.h"\
	"..\Include\EasyReport.h"\
	"..\Include\Graphics.h"\
	"..\Include\Pie.h"\
	".\EdStatDoc.h"\
	".\EdStatRptView.h"\
	".\EdStatTpl.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EdStatTpl.cpp
DEP_CPP_EDSTATT=\
	"..\Include\IniFile.h"\
	".\EdStatTpl.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EdStatView.cpp
DEP_CPP_EDSTATV=\
	"..\Include\BarLine.h"\
	"..\Include\EasyReport.h"\
	"..\Include\Graphics.h"\
	"..\Include\Pie.h"\
	".\EdStatDoc.h"\
	".\EdStatTpl.h"\
	".\EdStatView.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ZipArc.cpp
DEP_CPP_ZIPAR=\
	"..\Include\ZipArchive.h"\
	"..\Include\ZipAutoBuffer.h"\
	"..\Include\ZipBigFile.h"\
	"..\Include\ZipCentralDir.h"\
	"..\Include\ZipException.h"\
	"..\Include\ZipFileHeader.h"\
	"..\Include\ZipInternalInfo.h"\
	"..\Include\ZipStorage.h"\
	".\stdafx.h"\
	".\ZipArc.h"\
	
NODEP_CPP_ZIPAR=\
	"..\Include\zlib.h"\
	
# End Source File
# Begin Source File

SOURCE=.\ZipArc.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=.\DlgImport.h
# End Source File
# Begin Source File

SOURCE=.\EdHtmlView.h
# End Source File
# Begin Source File

SOURCE=.\EdRptDoc.h
# End Source File
# Begin Source File

SOURCE=.\EdRptExport.h
# End Source File
# Begin Source File

SOURCE=.\EdRptTpl.h
# End Source File
# Begin Source File

SOURCE=.\EdRptView.h
# End Source File
# Begin Source File

SOURCE=.\EdStat2View.h
# End Source File
# Begin Source File

SOURCE=.\EdStatDoc.h
# End Source File
# Begin Source File

SOURCE=.\EdStatRptView.h
# End Source File
# Begin Source File

SOURCE=.\EdStatTpl.h
# End Source File
# Begin Source File

SOURCE=.\EdStatView.h
# End Source File
# Begin Source File

SOURCE=.\GraphData.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx"
# Begin Source File

SOURCE=.\res\bsstat1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bsstat2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bsstat3.bmp
# End Source File
# Begin Source File

SOURCE=.\EdFcMod1.rc
# End Source File
# Begin Source File

SOURCE=.\res\EdFcMod1.rc2
# End Source File
# Begin Source File

SOURCE=.\res\EdHtml.ico
# End Source File
# Begin Source File

SOURCE=.\res\EdHtmlTb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EdHtmlTb24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\EdStat.ico
# End Source File
# Begin Source File

SOURCE=.\res\EdStat2.ico
# End Source File
# Begin Source File

SOURCE=.\res\graphall.bmp
# End Source File
# Begin Source File

SOURCE=.\res\largbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\largebar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\manager.bmp
# End Source File
# Begin Source File

SOURCE=.\res\normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PrintGlb.ico
# End Source File
# Begin Source File

SOURCE=.\res\smailbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\smallbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\supper.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
