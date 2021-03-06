
!include "Sections.nsh"
!include "StrFunc.nsh"
!include "MUI.nsh"
${StrStr}

;--------------------------------
;General
; The file to write
OutFile "ora8imc.exe"
; The name of the installer
Name "Oracle mini Client 8.17i"
; The default installation directory
InstallDir "d:\oracle"
;Get installation folder from registry if available
 InstallDirRegKey HKLM "Software\oracle" ""


;--------------------------------
;Interface Settings
!define MUI_ABORTWARNING

;--------------------------------
;Language Selection Dialog Settings
;Remember the installer language
!define MUI_LANGDLL_REGISTRY_ROOT "HKCU"
!define MUI_LANGDLL_REGISTRY_KEY "Software\oracle"
!define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"

;--------------------------------
;Pages
!insertmacro MUI_PAGE_LICENSE "License.txt"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
;--------------------------------
;Languages
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_RESERVEFILE_LANGDLL

;--------------------------------
;Version Information

  VIProductVersion "0.1.0.0"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "Oracle 8.17i mini Client Setup Application."
  VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "Oracle 8.17i mini Client"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Edson, inc."
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "� Edson company"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "Oracle 8.17i mini Client"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "0.1.0.4"

;--------------------------------
; Sections
Section "Uninstall"
  ;ADD YOUR OWN FILES HERE...
  Delete "$INSTDIR\Uninstall8.exe"

  delete "$INSTDIR\ora81\bin\EXP.EXE"
  delete "$INSTDIR\ora81\bin\IMP.EXE"
  delete "$INSTDIR\ora81\bin\mmdx32.ocx"
  delete "$INSTDIR\ora81\bin\mmtx32.ocx"
  delete "$INSTDIR\ora81\bin\oci.dll"
  delete "$INSTDIR\ora81\bin\ociw32.dll"
  delete "$INSTDIR\ora81\bin\oip8.dll"
  delete "$INSTDIR\ora81\bin\oip8.tlb"
  delete "$INSTDIR\ora81\bin\oracle.key"
  delete "$INSTDIR\ora81\bin\oraclient8.dll"
  delete "$INSTDIR\ora81\bin\oracommon8.dll"
  delete "$INSTDIR\ora81\bin\oracore8.dll"
  delete "$INSTDIR\ora81\bin\orageneric8.dll"
  delete "$INSTDIR\ora81\bin\oraldapclnt8.dll"
  delete "$INSTDIR\ora81\bin\oran8.dll"
  delete "$INSTDIR\ora81\bin\ORANCDS8.DLL"
  delete "$INSTDIR\ora81\bin\orancrypt8.dll"
  delete "$INSTDIR\ora81\bin\oranhost8.dll"
  delete "$INSTDIR\ora81\bin\ORANK58.DLL"
  delete "$INSTDIR\ora81\bin\oranl8.dll"
  delete "$INSTDIR\ora81\bin\oranldap8.dll"
  delete "$INSTDIR\ora81\bin\ORANLS8.DLL"
  delete "$INSTDIR\ora81\bin\oranms.dll"
  delete "$INSTDIR\ora81\bin\oranmsp.dll"
  delete "$INSTDIR\ora81\bin\orannds8.dll"
  delete "$INSTDIR\ora81\bin\orannss8.dll"
  delete "$INSTDIR\ora81\bin\orannts8.dll"
  delete "$INSTDIR\ora81\bin\orannzsbb8.dll"
  delete "$INSTDIR\ora81\bin\oranoname8.dll"
  delete "$INSTDIR\ora81\bin\ORANRAD8.DLL"
  delete "$INSTDIR\ora81\bin\oranro8.dll"
  delete "$INSTDIR\ora81\bin\ORANSID8.DLL"
  delete "$INSTDIR\ora81\bin\orantcp8.dll"
  delete "$INSTDIR\ora81\bin\orantns8.dll"
  delete "$INSTDIR\ora81\bin\OraOLEDB.dll"
  delete "$INSTDIR\ora81\bin\OraOLEDB.tlb"
  delete "$INSTDIR\ora81\bin\ORAPLS8.DLL"
  delete "$INSTDIR\ora81\bin\Oraslax8.dll"
  delete "$INSTDIR\ora81\bin\ORASQL8.DLL"
  delete "$INSTDIR\ora81\bin\oratrace8.dll"
  delete "$INSTDIR\ora81\bin\oravsn8.dll"
  delete "$INSTDIR\ora81\bin\orawtc8.dll"
  delete "$INSTDIR\ora81\bin\ott.exe"
  delete "$INSTDIR\ora81\bin\proc.exe"
  delete "$INSTDIR\ora81\bin\procob18.exe"
  delete "$INSTDIR\ora81\bin\procui.exe"
  delete "$INSTDIR\ora81\bin\SQLPLUS.EXE"
  delete "$INSTDIR\ora81\bin\SQLPLUSW.EXE"
  delete "$INSTDIR\ora81\bin\sqora32.dll"
  delete "$INSTDIR\ora81\bin\sqoras32.dll"
  delete "$INSTDIR\ora81\bin\sqresus.dll"
  delete "$INSTDIR\ora81\bin\TNSPING.EXE"
  delete "$INSTDIR\ora81\network\admin\tnsnames.ora"
  delete "$INSTDIR\ora81\network\mesg\naukus.msb"
  delete "$INSTDIR\ora81\network\mesg\naukus.msg"
  delete "$INSTDIR\ora81\network\mesg\ncrus.msb"
  delete "$INSTDIR\ora81\network\mesg\ncrzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\ncxus.msb"
  delete "$INSTDIR\ora81\network\mesg\ncxzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\niqus.msb"
  delete "$INSTDIR\ora81\network\mesg\niqzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\nltus.msb"
  delete "$INSTDIR\ora81\network\mesg\nlus.msb"
  delete "$INSTDIR\ora81\network\mesg\nlzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\nmpus.msb"
  delete "$INSTDIR\ora81\network\mesg\nmpzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\nmrus.msb"
  delete "$INSTDIR\ora81\network\mesg\nncus.msb"
  delete "$INSTDIR\ora81\network\mesg\nnczhs.msb"
  delete "$INSTDIR\ora81\network\mesg\nnfus.msb"
  delete "$INSTDIR\ora81\network\mesg\nnfzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\nnlus.msb"
  delete "$INSTDIR\ora81\network\mesg\nnlzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\nnous.msb"
  delete "$INSTDIR\ora81\network\mesg\nnozhs.msb"
  delete "$INSTDIR\ora81\network\mesg\nplus.msb"
  delete "$INSTDIR\ora81\network\mesg\nplzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\nzus.msb"
  delete "$INSTDIR\ora81\network\mesg\nzzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\snlus.msb"
  delete "$INSTDIR\ora81\network\mesg\snlzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\tnlus.msb"
  delete "$INSTDIR\ora81\network\mesg\tnlzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\tnplus.msb"
  delete "$INSTDIR\ora81\network\mesg\tnplzhs.msb"
  delete "$INSTDIR\ora81\network\mesg\tnsus.msb"
  delete "$INSTDIR\ora81\network\mesg\tnszhs.msb"
  delete "$INSTDIR\ora81\oci\include\cdemodp0.h"
  delete "$INSTDIR\ora81\oci\include\kusapi.h"
  delete "$INSTDIR\ora81\oci\include\kustags.h"
  delete "$INSTDIR\ora81\oci\include\nzerror.h"
  delete "$INSTDIR\ora81\oci\include\nzt.h"
  delete "$INSTDIR\ora81\oci\include\oci.h"
  delete "$INSTDIR\ora81\oci\include\oci1.h"
  delete "$INSTDIR\ora81\oci\include\oci8dp.h"
  delete "$INSTDIR\ora81\oci\include\ociap.h"
  delete "$INSTDIR\ora81\oci\include\ociapr.h"
  delete "$INSTDIR\ora81\oci\include\ocidef.h"
  delete "$INSTDIR\ora81\oci\include\ocidem.h"
  delete "$INSTDIR\ora81\oci\include\ocidfn.h"
  delete "$INSTDIR\ora81\oci\include\ociextp.h"
  delete "$INSTDIR\ora81\oci\include\ocikp.h"
  delete "$INSTDIR\ora81\oci\include\ocikpr.h"
  delete "$INSTDIR\ora81\oci\include\odci.h"
  delete "$INSTDIR\ora81\oci\include\oratypes.h"
  delete "$INSTDIR\ora81\oci\include\ori.h"
  delete "$INSTDIR\ora81\oci\include\orid.h"
  delete "$INSTDIR\ora81\oci\include\orl.h"
  delete "$INSTDIR\ora81\oci\include\oro.h"
  delete "$INSTDIR\ora81\oci\include\ort.h"
  delete "$INSTDIR\ora81\oci\include\tnsapi.h"
  delete "$INSTDIR\ora81\oci\lib\bc\oci.lib"
  delete "$INSTDIR\ora81\oci\lib\bc\ociw32.lib"
  delete "$INSTDIR\ora81\oci\lib\msvc\oci.lib"
  delete "$INSTDIR\ora81\oci\lib\msvc\ociw32.lib"
  delete "$INSTDIR\ora81\ocommon\nls\ADMIN\DATA\LX00001.NLB"
  delete "$INSTDIR\ora81\ocommon\nls\ADMIN\DATA\LX00023.NLB"
  delete "$INSTDIR\ora81\ocommon\nls\ADMIN\DATA\LX10001.NLB"
  delete "$INSTDIR\ora81\ocommon\nls\ADMIN\DATA\LX10035.NLB"
  delete "$INSTDIR\ora81\ocommon\nls\ADMIN\DATA\LX1BOOT.NLB"
  delete "$INSTDIR\ora81\ocommon\nls\ADMIN\DATA\LX20001.NLB"
  delete "$INSTDIR\ora81\ocommon\nls\ADMIN\DATA\LX20354.NLB"
  delete "$INSTDIR\ora81\ocommon\nls\ADMIN\DATA\LX60354.NLB"
  delete "$INSTDIR\ora81\oledb\doc\oledb.pdf"
  delete "$INSTDIR\ora81\oledb\doc\readme.txt"
  delete "$INSTDIR\ora81\oledb\include\OraOLEDB.h"
  delete "$INSTDIR\ora81\oledb\lib\OraOLEDB.lib"
  delete "$INSTDIR\ora81\oledb\mesg\oraoledbus.msb"
  delete "$INSTDIR\ora81\oledb\mesg\oraoledbzhs.msb"
  delete "$INSTDIR\ora81\oracore\mesg\lemus.msb"
  delete "$INSTDIR\ora81\oracore\mesg\lfius.msb"
  delete "$INSTDIR\ora81\oracore\mesg\lfizhs.msb"
  delete "$INSTDIR\ora81\oracore\mesg\lhtus.msb"
  delete "$INSTDIR\ora81\oracore\mesg\lmmus.msb"
  delete "$INSTDIR\ora81\oracore\mesg\lpmus.msb"
  delete "$INSTDIR\ora81\oracore\mesg\lpxus.msb"
  delete "$INSTDIR\ora81\oracore\mesg\lpxzhs.msb"
  delete "$INSTDIR\ora81\oracore\mesg\lrmus.msb"
  delete "$INSTDIR\ora81\oracore\mesg\lrmzhs.msb"
  delete "$INSTDIR\ora81\oracore\mesg\lsfus.msb"
  delete "$INSTDIR\ora81\oracore\mesg\ltmus.msb"
  delete "$INSTDIR\ora81\precomp\admin\ottcfg.cfg"
  delete "$INSTDIR\ora81\precomp\doc\ott\readme.doc"
  delete "$INSTDIR\ora81\precomp\mesg\o2fus.msb"
  delete "$INSTDIR\ora81\precomp\mesg\o2fzhs.msb"
  delete "$INSTDIR\ora81\precomp\mesg\o2ius.msb"
  delete "$INSTDIR\ora81\precomp\mesg\o2izhs.msb"
  delete "$INSTDIR\ora81\precomp\mesg\o2uus.msb"
  delete "$INSTDIR\ora81\precomp\mesg\o2uzhs.msb"
  delete "$INSTDIR\ora81\precomp\mesg\pgous.msb"
  delete "$INSTDIR\ora81\precomp\mesg\pgozhs.msb"
  delete "$INSTDIR\ora81\precomp\mesg\prous.msb"
  delete "$INSTDIR\ora81\precomp\mesg\prozhs.msb"
  delete "$INSTDIR\ora81\precomp\mesg\sqlus.msb"
  delete "$INSTDIR\ora81\precomp\mesg\sqlzhs.msb"
  delete "$INSTDIR\ora81\precomp\public\bnddsc.for"
  delete "$INSTDIR\ora81\precomp\public\oraca.cob"
  delete "$INSTDIR\ora81\precomp\public\oraca.for"
  delete "$INSTDIR\ora81\precomp\public\oraca.h"
  delete "$INSTDIR\ora81\precomp\public\oraca5.cob"
  delete "$INSTDIR\ora81\precomp\public\seldsc.for"
  delete "$INSTDIR\ora81\precomp\public\sql2oci.h"
  delete "$INSTDIR\ora81\precomp\public\sqlapr.h"
  delete "$INSTDIR\ora81\precomp\public\sqlca.cob"
  delete "$INSTDIR\ora81\precomp\public\sqlca.for"
  delete "$INSTDIR\ora81\precomp\public\sqlca.h"
  delete "$INSTDIR\ora81\precomp\public\sqlca5.cob"
  delete "$INSTDIR\ora81\precomp\public\sqlcpr.h"
  delete "$INSTDIR\ora81\precomp\public\sqlda.cob"
  delete "$INSTDIR\ora81\precomp\public\sqlda.h"
  delete "$INSTDIR\ora81\precomp\public\sqlda5.cob"
  delete "$INSTDIR\ora81\precomp\public\sqlkpr.h"
  delete "$INSTDIR\ora81\precomp\public\sqlucs2.h"
  delete "$INSTDIR\ora81\RDBMS\mesg\bbedus.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\bbedzhs.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\expus.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\expzhs.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\impus.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\impzhs.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\kgpus.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\kgpzhs.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\ocius.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\ocizhs.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\oraus.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\orazhs.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\rmanus.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\rmanzhs.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\sbtus.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\sbtzhs.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\ulus.msb"
  delete "$INSTDIR\ora81\RDBMS\mesg\ulzhs.msb"
  delete "$INSTDIR\ora81\sqlplus\admin\glogin.sql"
  delete "$INSTDIR\ora81\sqlplus\admin\help\helpbld.sql"
  delete "$INSTDIR\ora81\sqlplus\admin\help\helpdrop.sql"
  delete "$INSTDIR\ora81\sqlplus\admin\help\helpus.sql"
  delete "$INSTDIR\ora81\sqlplus\admin\plustrce.sql"
  delete "$INSTDIR\ora81\sqlplus\admin\pupbld.sql"
  delete "$INSTDIR\ora81\sqlplus\mesg\cpyus.msb"
  delete "$INSTDIR\ora81\sqlplus\mesg\cpyzhs.msb"
  delete "$INSTDIR\ora81\sqlplus\mesg\sp1us.msb"
  delete "$INSTDIR\ora81\sqlplus\mesg\sp1zhs.msb"
  delete "$INSTDIR\ora81\sqlplus\mesg\sp2us.msb"
  delete "$INSTDIR\ora81\sqlplus\mesg\sp2zhs.msb"
  delete "$INSTDIR\ora81\sqlplus\mesg\spwus.msb"
  delete "$INSTDIR\ora81\sqlplus\mesg\spwzhs.msb"

  RMDir /r "$INSTDIR\ora81\bin"
  RMDir /r "$INSTDIR\ora81\network\ADMIN"
  RMDir /r "$INSTDIR\ora81\network\mesg"
  RMDir /r "$INSTDIR\ora81\network"
  RMDir /r "$INSTDIR\ora81\oci\include"
  RMDir /r "$INSTDIR\ora81\oci\lib\msvc"
  RMDir /r "$INSTDIR\ora81\oci\bc"
  RMDir /r "$INSTDIR\ora81\oci\lib"
  RMDir /r "$INSTDIR\ora81\oci"
  RMDir /r "$INSTDIR\ora81\ocommon\nls\admin\data"
  RMDir /r "$INSTDIR\ora81\ocommon\nls\admin"
  RMDir /r "$INSTDIR\ora81\ocommon\nls"
  RMDir /r "$INSTDIR\ora81\ocommon"
  RMDir /r "$INSTDIR\ora81\oledb\doc"
  RMDir /r "$INSTDIR\ora81\oledb\include"
  RMDir /r "$INSTDIR\ora81\oledb\lib"
  RMDir /r "$INSTDIR\ora81\oledb\mesg"
  RMDir /r "$INSTDIR\ora81\oledb"
  RMDir /r "$INSTDIR\ora81\oracore\mesg"
  RMDir /r "$INSTDIR\ora81\oracore"
  RMDir /r "$INSTDIR\ora81\precomp\admin"
  RMDir /r "$INSTDIR\ora81\precomp\doc\ott"
  RMDir /r "$INSTDIR\ora81\precomp\doc"
  RMDir /r "$INSTDIR\ora81\precomp\public"
  RMDir /r "$INSTDIR\ora81\precomp\mesg"
  RMDir /r "$INSTDIR\ora81\precomp"
  RMDir /r "$INSTDIR\ora81\RDBMS\mesg"
  RMDir /r "$INSTDIR\ora81\RDBMS"
  RMDir /r "$INSTDIR\ora81\sqlplus\admin\help"
  RMDir /r "$INSTDIR\ora81\sqlplus\admin"
  RMDir /r "$INSTDIR\ora81\sqlplus\mesg"
  RMDir /r "$INSTDIR\ora81\sqlplus"
  RMDir /r "$INSTDIR\ora81"

  DeleteRegKey HKCU "Software\oracle"
  DeleteRegKey HKLM "Software\oracle"
  DeleteRegKey HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome81"
  DeleteRegValue  HKLM "SOFTWARE\ODBC\ODBCINST.INI\ODBC Drivers" "Oracle in OraHome81"
SectionEnd

Section "oracle 8.17i mini client (required)"
  SectionIn RO

  SetOutPath "$INSTDIR\ora81\bin"
  File ".\ora81\bin\EXP.EXE"
  File ".\ora81\bin\IMP.EXE"
  File ".\ora81\bin\mmdx32.ocx"
  File ".\ora81\bin\mmtx32.ocx"
  File ".\ora81\bin\oci.dll"
  File ".\ora81\bin\oip8.dll"
  File ".\ora81\bin\oip8.tlb"
  File ".\ora81\bin\oracle.key"
  File ".\ora81\bin\oraclient8.dll"
  File ".\ora81\bin\oracommon8.dll"
  File ".\ora81\bin\oracore8.dll"
  File ".\ora81\bin\orageneric8.dll"
  File ".\ora81\bin\oraldapclnt8.dll"
  File ".\ora81\bin\oran8.dll"
  File ".\ora81\bin\ORANCDS8.DLL"
  File ".\ora81\bin\orancrypt8.dll"
  File ".\ora81\bin\oranhost8.dll"
  File ".\ora81\bin\ORANK58.DLL"
  File ".\ora81\bin\oranl8.dll"
  File ".\ora81\bin\oranldap8.dll"
  File ".\ora81\bin\ORANLS8.DLL"
  File ".\ora81\bin\oranms.dll"
  File ".\ora81\bin\oranmsp.dll"
  File ".\ora81\bin\orannds8.dll"
  File ".\ora81\bin\orannss8.dll"
  File ".\ora81\bin\orannts8.dll"
  File ".\ora81\bin\orannzsbb8.dll"
  File ".\ora81\bin\oranoname8.dll"
  File ".\ora81\bin\ORANRAD8.DLL"
  File ".\ora81\bin\oranro8.dll"
  File ".\ora81\bin\ORANSID8.DLL"
  File ".\ora81\bin\orantcp8.dll"
  File ".\ora81\bin\orantns8.dll"
  File ".\ora81\bin\OraOLEDB.dll"
  File ".\ora81\bin\OraOLEDB.tlb"
  File ".\ora81\bin\ORAPLS8.DLL"
  File ".\ora81\bin\Oraslax8.dll"
  File ".\ora81\bin\ORASQL8.DLL"
  File ".\ora81\bin\oratrace8.dll"
  File ".\ora81\bin\oravsn8.dll"
  File ".\ora81\bin\orawtc8.dll"
  File ".\ora81\bin\sqora32.dll"
  File ".\ora81\bin\sqoras32.dll"
  File ".\ora81\bin\sqresus.dll"
  File ".\ztools\TNSConf.exe"
  File ".\ztools\OraSQL.exe"

  SetOutPath "$INSTDIR\ora81\network\ADMIN"
  File ".\ora81\network\admin\tnsnames.ora"

  SetOutPath "$INSTDIR\ora81\network\mesg"
  File ".\ora81\network\mesg\naukus.msb"
  File ".\ora81\network\mesg\naukus.msg"
  File ".\ora81\network\mesg\ncrus.msb"
  File ".\ora81\network\mesg\ncrzhs.msb"
  File ".\ora81\network\mesg\ncxus.msb"
  File ".\ora81\network\mesg\ncxzhs.msb"
  File ".\ora81\network\mesg\niqus.msb"
  File ".\ora81\network\mesg\niqzhs.msb"
  File ".\ora81\network\mesg\nltus.msb"
  File ".\ora81\network\mesg\nlus.msb"
  File ".\ora81\network\mesg\nlzhs.msb"
  File ".\ora81\network\mesg\nmpus.msb"
  File ".\ora81\network\mesg\nmpzhs.msb"
  File ".\ora81\network\mesg\nmrus.msb"
  File ".\ora81\network\mesg\nncus.msb"
  File ".\ora81\network\mesg\nnczhs.msb"
  File ".\ora81\network\mesg\nnfus.msb"
  File ".\ora81\network\mesg\nnfzhs.msb"
  File ".\ora81\network\mesg\nnlus.msb"
  File ".\ora81\network\mesg\nnlzhs.msb"
  File ".\ora81\network\mesg\nnous.msb"
  File ".\ora81\network\mesg\nnozhs.msb"
  File ".\ora81\network\mesg\nplus.msb"
  File ".\ora81\network\mesg\nplzhs.msb"
  File ".\ora81\network\mesg\nzus.msb"
  File ".\ora81\network\mesg\nzzhs.msb"
  File ".\ora81\network\mesg\snlus.msb"
  File ".\ora81\network\mesg\snlzhs.msb"
  File ".\ora81\network\mesg\tnlus.msb"
  File ".\ora81\network\mesg\tnlzhs.msb"
  File ".\ora81\network\mesg\tnplus.msb"
  File ".\ora81\network\mesg\tnplzhs.msb"

  SetOutPath "$INSTDIR\ora81\ocommon\nls\admin\data"
  File ".\ora81\ocommon\nls\ADMIN\DATA\LX00001.NLB"
  File ".\ora81\ocommon\nls\ADMIN\DATA\LX00023.NLB"
  File ".\ora81\ocommon\nls\ADMIN\DATA\LX10001.NLB"
  File ".\ora81\ocommon\nls\ADMIN\DATA\LX10035.NLB"
  File ".\ora81\ocommon\nls\ADMIN\DATA\LX1BOOT.NLB"
  File ".\ora81\ocommon\nls\ADMIN\DATA\LX20001.NLB"
  File ".\ora81\ocommon\nls\ADMIN\DATA\LX20354.NLB"
  File ".\ora81\ocommon\nls\ADMIN\DATA\LX60354.NLB"

  SetOutPath "$INSTDIR\ora81\oracore\mesg"
  File ".\ora81\oracore\mesg\lemus.msb"
  File ".\ora81\oracore\mesg\lfius.msb"
  File ".\ora81\oracore\mesg\lfizhs.msb"
  File ".\ora81\oracore\mesg\lhtus.msb"
  File ".\ora81\oracore\mesg\lmmus.msb"
  File ".\ora81\oracore\mesg\lpmus.msb"
  File ".\ora81\oracore\mesg\lpxus.msb"
  File ".\ora81\oracore\mesg\lpxzhs.msb"
  File ".\ora81\oracore\mesg\lrmus.msb"
  File ".\ora81\oracore\mesg\lrmzhs.msb"
  File ".\ora81\oracore\mesg\lsfus.msb"
  File ".\ora81\oracore\mesg\ltmus.msb"
  File ".\ora81\oracore\mesg\ltmus.msb"

  SetOutPath "$INSTDIR\ora81\RDBMS\mesg"
  File ".\ora81\RDBMS\mesg\bbedus.msb"
  File ".\ora81\RDBMS\mesg\bbedzhs.msb"
  File ".\ora81\RDBMS\mesg\expus.msb"
  File ".\ora81\RDBMS\mesg\expzhs.msb"
  File ".\ora81\RDBMS\mesg\impus.msb"
  File ".\ora81\RDBMS\mesg\impzhs.msb"
  File ".\ora81\RDBMS\mesg\kgpus.msb"
  File ".\ora81\RDBMS\mesg\kgpzhs.msb"
  File ".\ora81\RDBMS\mesg\ocius.msb"
  File ".\ora81\RDBMS\mesg\ocizhs.msb"
  File ".\ora81\RDBMS\mesg\oraus.msb"
  File ".\ora81\RDBMS\mesg\orazhs.msb"
  File ".\ora81\RDBMS\mesg\rmanus.msb"
  File ".\ora81\RDBMS\mesg\rmanzhs.msb"
  File ".\ora81\RDBMS\mesg\sbtus.msb"
  File ".\ora81\RDBMS\mesg\sbtzhs.msb"
  File ".\ora81\RDBMS\mesg\ulus.msb"
  File ".\ora81\RDBMS\mesg\ulzhs.msb"

  DeleteRegKey HKLM "SOFTWARE\ORACLE"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "ORACLE_HOME" "$INSTDIR\ora81"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "ORACLE_HOME_NAME" "OraHome81"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "API" "$INSTDIR\ora81\dbs"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "ORACLE_GROUP_NAME" "Oracle - OraHome81"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "NLS_LANG" "NA"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "OLEDB" "$INSTDIR\ora81\oledb\mesg"

  DeleteRegKey HKLM "SOFTWARE\ORACLE\ALL_HOMES"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES" "HOME_COUNTER" "1"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES" "DEFAULT_HOME" "OraHome81"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES" "LAST_HOME" "0"

  DeleteRegKey HKLM "SOFTWARE\ORACLE\ALL_HOMES\ID0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES\ID0" "NAME" "OraHome81"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES\ID0" "PATH" "$INSTDIR\ora81"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES\ID0" "NLS_LANG" "NA"

  DeleteRegKey HKLM "SOFTWARE\ORACLE\HOME0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ID" "0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ORACLE_GROUP_NAME" "Oracle - OraHome81"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ORACLE_HOME_NAME" "OraHome81"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ORACLE_HOME" "$INSTDIR\ora81"
  ; if english NA
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "NLS_LANG" "SIMPLIFIED CHINESE_CHINA.ZHS16GBK"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ORACLE_BUNDLE_NAME" "Enterprise"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ORACLE_HOME_KEY" "oftware\ORACLE\HOME0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "SQLPATH" "$INSTDIR\ora81\dbs"

  DeleteRegKey HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome81"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome81" "APILevel" "1"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome81" "CPTimeout" "60"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome81" "ConnectFunctions" "YYY"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome81" "Driver" "$INSTDIR\ora81\bin\sqora32.dll"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome81" "DriverODBCVer" "03.51"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome81" "FileUsage" "0"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome81" "Setup" "$INSTDIR\ora81\bin\sqoras32.dll"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome81" "SQLLevel" "1"

  DeleteRegValue  HKLM "SOFTWARE\ODBC\ODBCINST.INI\ODBC Drivers" ""
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\ODBC Drivers" "Oracle in OraHome81" "Installed"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\ODBC Drivers" "" ""

  WriteUninstaller "$INSTDIR\Uninstall8.exe"
  StrCpy $0 "$INSTDIR\ora81\bin"
  ReadRegStr $1 HKLM  "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "Path"
  ${StrStr} $2 $1 $0
  strcmp $2 "" setpath end
setpath:
  WriteRegExpandStr HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "path" "$1;$0"

end:
SectionEnd

Section "oracle 8.17i tools"
  SetOutPath "$INSTDIR\ora81\bin"
  File ".\ora81\bin\TNSPING.EXE"

  SetOutPath "$INSTDIR\ora81\network\mesg"
  File ".\ora81\network\mesg\tnsus.msb"
  File ".\ora81\network\mesg\tnszhs.msb"

SectionEnd

Section "oracle 8.17i sqlplus"
  SetOutPath "$INSTDIR\ora81\bin"
  File ".\ora81\bin\SQLPLUS.EXE"
  File ".\ora81\bin\SQLPLUSW.EXE"

  SetOutPath "$INSTDIR\ora81\sqlplus\admin"
  File ".\ora81\sqlplus\admin\glogin.sql"
  File ".\ora81\sqlplus\admin\plustrce.sql"
  File ".\ora81\sqlplus\admin\pupbld.sql"

  SetOutPath "$INSTDIR\ora81\sqlplus\admin\help"
  File ".\ora81\sqlplus\admin\help\helpbld.sql"
  File ".\ora81\sqlplus\admin\help\helpdrop.sql"
  File ".\ora81\sqlplus\admin\help\helpus.sql"


  SetOutPath "$INSTDIR\ora81\sqlplus\doc"
  File ".\ora81\sqlplus\doc\README.doc"

  SetOutPath "$INSTDIR\ora81\sqlplus\mesg"
  File ".\ora81\sqlplus\mesg\cpyus.msb"
  File ".\ora81\sqlplus\mesg\cpyzhs.msb"
  File ".\ora81\sqlplus\mesg\sp1us.msb"
  File ".\ora81\sqlplus\mesg\sp1zhs.msb"
  File ".\ora81\sqlplus\mesg\sp2us.msb"
  File ".\ora81\sqlplus\mesg\sp2zhs.msb"
  File ".\ora81\sqlplus\mesg\spwus.msb"
  File ".\ora81\sqlplus\mesg\spwzhs.msb"

SectionEnd

Section /o "oracle 8.17i oci sdk"
  SetOutPath "$INSTDIR\ora81\bin"
  File ".\ora81\bin\ociw32.dll"

  SetOutPath "$INSTDIR\ora81\oci\include"
  File ".\ora81\oci\include\cdemodp0.h"
  File ".\ora81\oci\include\kusapi.h"
  File ".\ora81\oci\include\kustags.h"
  File ".\ora81\oci\include\nzerror.h"
  File ".\ora81\oci\include\nzt.h"
  File ".\ora81\oci\include\oci.h"
  File ".\ora81\oci\include\oci1.h"
  File ".\ora81\oci\include\oci8dp.h"
  File ".\ora81\oci\include\ociap.h"
  File ".\ora81\oci\include\ociapr.h"
  File ".\ora81\oci\include\ocidef.h"
  File ".\ora81\oci\include\ocidem.h"
  File ".\ora81\oci\include\ocidfn.h"
  File ".\ora81\oci\include\ociextp.h"
  File ".\ora81\oci\include\ocikp.h"
  File ".\ora81\oci\include\ocikpr.h"
  File ".\ora81\oci\include\odci.h"
  File ".\ora81\oci\include\oratypes.h"
  File ".\ora81\oci\include\ori.h"
  File ".\ora81\oci\include\orid.h"
  File ".\ora81\oci\include\orl.h"
  File ".\ora81\oci\include\oro.h"
  File ".\ora81\oci\include\ort.h"
  File ".\ora81\oci\include\tnsapi.h"

  SetOutPath "$INSTDIR\ora81\oci\lib\bv"
  File ".\ora81\oci\lib\bc\oci.lib"
  File ".\ora81\oci\lib\bc\ociw32.lib"
  
  SetOutPath "$INSTDIR\ora81\oci\lib\msvc"
  File ".\ora81\oci\lib\msvc\oci.lib"
  File ".\ora81\oci\lib\msvc\ociw32.lib"

SectionEnd

Section /o "oracle 8.17i oledb sdk"
  SetOutPath "$INSTDIR\ora81\bin"
  File ".\ora81\bin\OraOLEDB.dll"
  File ".\ora81\bin\OraOLEDB.tlb"

  SetOutPath "$INSTDIR\ora81\oledb\doc"
  File ".\ora81\oledb\doc\oledb.pdf"
  File ".\ora81\oledb\doc\readme.txt"

  SetOutPath "$INSTDIR\ora81\oledb\include"
  File ".\ora81\oledb\include\OraOLEDB.h"

  SetOutPath "$INSTDIR\ora81\oledb\lib"
  File ".\ora81\oledb\lib\OraOLEDB.lib"

  SetOutPath "$INSTDIR\ora81\oledb\mesg"
  File ".\ora81\oledb\mesg\oraoledbus.msb"
  File ".\ora81\oledb\mesg\oraoledbzhs.msb"

  RegDLL "$INSTDIR\ora81\bin\OraOLEDB.dll"
  DeleteRegKey HKLM "SOFTWARE\ORACLE\OLEDB"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "CacheType" "Memory"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "ChunkSize" "100"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "DistribTX" "1"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "FetchSize" "100"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "OSAuthent" "0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "PLSQLRSet" "0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "PwdChgDlg" "1"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "SchRstLng" "10000"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "UserDefFn" "0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "DisableRetClause" "1"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "VCharNull" "1"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "TraceCategory" "0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "TraceFileName" "$INSTDIR\OraOLEDB.trc"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "TraceLevel" "0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\OLEDB" "TraceOption" "0"

SectionEnd

Section /o "oracle 8.17i proc sdk"
  SetOutPath "$INSTDIR\ora81\bin"
  File ".\ora81\bin\ott.exe"
  File ".\ora81\bin\proc.exe"
  File ".\ora81\bin\procob18.exe"
  File ".\ora81\bin\procui.exe"

 SetOutPath "$INSTDIR\ora81\precomp\admin"
  File ".\ora81\precomp\admin\ottcfg.cfg"

  SetOutPath "$INSTDIR\ora81\precomp\doc\ott"
  File ".\ora81\precomp\doc\ott\readme.doc"

  SetOutPath "$INSTDIR\ora81\precomp\mesg"
  File ".\ora81\precomp\mesg\o2fus.msb"
  File ".\ora81\precomp\mesg\o2fzhs.msb"
  File ".\ora81\precomp\mesg\o2ius.msb"
  File ".\ora81\precomp\mesg\o2izhs.msb"
  File ".\ora81\precomp\mesg\o2uus.msb"
  File ".\ora81\precomp\mesg\o2uzhs.msb"
  File ".\ora81\precomp\mesg\pgous.msb"
  File ".\ora81\precomp\mesg\pgozhs.msb"
  File ".\ora81\precomp\mesg\prous.msb"
  File ".\ora81\precomp\mesg\prozhs.msb"
  File ".\ora81\precomp\mesg\sqlus.msb"
  File ".\ora81\precomp\mesg\sqlzhs.msb"

  SetOutPath "$INSTDIR\ora81\precomp\public"
  File ".\ora81\precomp\public\bnddsc.for"
  File ".\ora81\precomp\public\oraca.cob"
  File ".\ora81\precomp\public\oraca.for"
  File ".\ora81\precomp\public\oraca.h"
  File ".\ora81\precomp\public\oraca5.cob"
  File ".\ora81\precomp\public\seldsc.for"
  File ".\ora81\precomp\public\sql2oci.h"
  File ".\ora81\precomp\public\sqlapr.h"
  File ".\ora81\precomp\public\sqlca.cob"
  File ".\ora81\precomp\public\sqlca.for"
  File ".\ora81\precomp\public\sqlca.h"
  File ".\ora81\precomp\public\sqlca5.cob"
  File ".\ora81\precomp\public\sqlcpr.h"
  File ".\ora81\precomp\public\sqlda.cob"
  File ".\ora81\precomp\public\sqlda.h"
  File ".\ora81\precomp\public\sqlda5.cob"
  File ".\ora81\precomp\public\sqlkpr.h"
  File ".\ora81\precomp\public\sqlucs2.h"

SectionEnd

;--------------------------------
Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

;--------------------------------
;Uninstaller Functions

Function un.onInit
  !insertmacro MUI_UNGETLANGUAGE
FunctionEnd

