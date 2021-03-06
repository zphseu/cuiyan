
!include "Sections.nsh"
!include "StrFunc.nsh"
!include "MUI.nsh"
${StrStr}

;--------------------------------
;General
; The file to write
OutFile "ora9imc.exe"
; The name of the installer
Name "Oracle mini Client 9i"
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
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "Oracle 9i mini Client Setup Application."
  VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "Oracle 9i mini Client"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Edson, inc."
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "?Edson company"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "Oracle 9i mini Client"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "0.1.0.4"

;--------------------------------
; Sections
Section "Uninstall"
  ;ADD YOUR OWN FILES HERE...
  Delete "$INSTDIR\Uninstall9.exe"
  Delete "$WINDIR\oraodbc.ini"

  delete "$INSTDIR\ora90\bin\oci.dll"
  delete "$INSTDIR\ora90\bin\ociw32.dll"
  delete "$INSTDIR\ora90\bin\oracle.key"
  delete "$INSTDIR\ora90\bin\oraclient9.dll"
  delete "$INSTDIR\ora90\bin\oracommon9.dll"
  delete "$INSTDIR\ora90\bin\ORACORE9.DLL"
  delete "$INSTDIR\ora90\bin\orageneric9.dll"
  delete "$INSTDIR\ora90\bin\oraldapclnt9.dll"
  delete "$INSTDIR\ora90\bin\oran9.dll"
  delete "$INSTDIR\ora90\bin\ORANCDS9.DLL"
  delete "$INSTDIR\ora90\bin\orancrypt9.dll"
  delete "$INSTDIR\ora90\bin\oranhost9.dll"
  delete "$INSTDIR\ora90\bin\oranl9.dll"
  delete "$INSTDIR\ora90\bin\oranldap9.dll"
  delete "$INSTDIR\ora90\bin\ORANLS9.DLL"
  delete "$INSTDIR\ora90\bin\oranms.dll"
  delete "$INSTDIR\ora90\bin\oranmsp.dll"
  delete "$INSTDIR\ora90\bin\orannts9.dll"
  delete "$INSTDIR\ora90\bin\orannzsbb9.dll"
  delete "$INSTDIR\ora90\bin\oranoname9.dll"
  delete "$INSTDIR\ora90\bin\oranro9.dll"
  delete "$INSTDIR\ora90\bin\orantcp9.dll"
  delete "$INSTDIR\ora90\bin\orantns9.dll"
  delete "$INSTDIR\ora90\bin\oraocci9.dll"
  delete "$INSTDIR\ora90\bin\OraOLEDB.dll"
  delete "$INSTDIR\ora90\bin\OraOLEDB.tlb"
  delete "$INSTDIR\ora90\bin\ORAPLS9.DLL"
  delete "$INSTDIR\ora90\bin\ORASLAX9.DLL"
  delete "$INSTDIR\ora90\bin\ORASNLS9.DLL"
  delete "$INSTDIR\ora90\bin\OraSQL.exe"
  delete "$INSTDIR\ora90\bin\ORASQL9.DLL"
  delete "$INSTDIR\ora90\bin\oratrace9.dll"
  delete "$INSTDIR\ora90\bin\ORAUNLS9.DLL"
  delete "$INSTDIR\ora90\bin\oravsn9.dll"
  delete "$INSTDIR\ora90\bin\orawtc9.dll"
  delete "$INSTDIR\ora90\bin\ott.exe"
  delete "$INSTDIR\ora90\bin\ott8.exe"
  delete "$INSTDIR\ora90\bin\proc.exe"
  delete "$INSTDIR\ora90\bin\procd9.dll"
  delete "$INSTDIR\ora90\bin\proce9.dll"
  delete "$INSTDIR\ora90\bin\procf9.dll"
  delete "$INSTDIR\ora90\bin\proci9.dll"
  delete "$INSTDIR\ora90\bin\procja9.dll"
  delete "$INSTDIR\ora90\bin\procko9.dll"
  delete "$INSTDIR\ora90\bin\procob.exe"
  delete "$INSTDIR\ora90\bin\procob18.exe"
  delete "$INSTDIR\ora90\bin\procptb9.dll"
  delete "$INSTDIR\ora90\bin\procui.exe"
  delete "$INSTDIR\ora90\bin\procus9.dll"
  delete "$INSTDIR\ora90\bin\proczhs9.dll"
  delete "$INSTDIR\ora90\bin\sqlplus.exe"
  delete "$INSTDIR\ora90\bin\sqlplusw.exe"
  delete "$INSTDIR\ora90\bin\sqora32.dll"
  delete "$INSTDIR\ora90\bin\sqoras32.dll"
  delete "$INSTDIR\ora90\bin\sqresus.dll"
  delete "$INSTDIR\ora90\bin\TNSConf.exe"
  delete "$INSTDIR\ora90\bin\TNSPING.EXE"
  delete "$INSTDIR\ora90\network\ADMIN\tnsnames.ora"
  delete "$INSTDIR\ora90\network\mesg\ncrus.msb"
  delete "$INSTDIR\ora90\network\mesg\ncrzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\ncxus.msb"
  delete "$INSTDIR\ora90\network\mesg\ncxzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\niqus.msb"
  delete "$INSTDIR\ora90\network\mesg\niqzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\nltus.msb"
  delete "$INSTDIR\ora90\network\mesg\nlus.msb"
  delete "$INSTDIR\ora90\network\mesg\nlzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\nmpus.msb"
  delete "$INSTDIR\ora90\network\mesg\nmpzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\nmrus.msb"
  delete "$INSTDIR\ora90\network\mesg\nncus.msb"
  delete "$INSTDIR\ora90\network\mesg\nnczhs.msb"
  delete "$INSTDIR\ora90\network\mesg\nnfus.msb"
  delete "$INSTDIR\ora90\network\mesg\nnfzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\nnlus.msb"
  delete "$INSTDIR\ora90\network\mesg\nnlzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\nnous.msb"
  delete "$INSTDIR\ora90\network\mesg\nnozhs.msb"
  delete "$INSTDIR\ora90\network\mesg\nplus.msb"
  delete "$INSTDIR\ora90\network\mesg\nplzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\nzus.msb"
  delete "$INSTDIR\ora90\network\mesg\nzzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\snlus.msb"
  delete "$INSTDIR\ora90\network\mesg\snlzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\tnlus.msb"
  delete "$INSTDIR\ora90\network\mesg\tnlzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\tnplus.msb"
  delete "$INSTDIR\ora90\network\mesg\tnplzhs.msb"
  delete "$INSTDIR\ora90\network\mesg\tnsus.msb"
  delete "$INSTDIR\ora90\network\mesg\tnszhs.msb"
  delete "$INSTDIR\ora90\oci\include\cdemodp0.h"
  delete "$INSTDIR\ora90\oci\include\kusapi.h"
  delete "$INSTDIR\ora90\oci\include\kustags.h"
  delete "$INSTDIR\ora90\oci\include\nzerror.h"
  delete "$INSTDIR\ora90\oci\include\nzt.h"
  delete "$INSTDIR\ora90\oci\include\occi.h"
  delete "$INSTDIR\ora90\oci\include\occiCommon.h"
  delete "$INSTDIR\ora90\oci\include\occiControl.h"
  delete "$INSTDIR\ora90\oci\include\occiData.h"
  delete "$INSTDIR\ora90\oci\include\occiObjects.h"
  delete "$INSTDIR\ora90\oci\include\oci.h"
  delete "$INSTDIR\ora90\oci\include\oci1.h"
  delete "$INSTDIR\ora90\oci\include\oci8dp.h"
  delete "$INSTDIR\ora90\oci\include\ociap.h"
  delete "$INSTDIR\ora90\oci\include\ociapr.h"
  delete "$INSTDIR\ora90\oci\include\ocidef.h"
  delete "$INSTDIR\ora90\oci\include\ocidem.h"
  delete "$INSTDIR\ora90\oci\include\ocidfn.h"
  delete "$INSTDIR\ora90\oci\include\ociextp.h"
  delete "$INSTDIR\ora90\oci\include\ocikp.h"
  delete "$INSTDIR\ora90\oci\include\ocikpr.h"
  delete "$INSTDIR\ora90\oci\include\ocixad.h"
  delete "$INSTDIR\ora90\oci\include\odci.h"
  delete "$INSTDIR\ora90\oci\include\oratypes.h"
  delete "$INSTDIR\ora90\oci\include\ori.h"
  delete "$INSTDIR\ora90\oci\include\orid.h"
  delete "$INSTDIR\ora90\oci\include\orl.h"
  delete "$INSTDIR\ora90\oci\include\oro.h"
  delete "$INSTDIR\ora90\oci\include\ort.h"
  delete "$INSTDIR\ora90\oci\lib\oci.lib"
  delete "$INSTDIR\ora90\oci\lib\ociw32.lib"
  delete "$INSTDIR\ora90\oci\lib\oraocci9.lib"
  delete "$INSTDIR\ora90\ocommon\nls\admin\data\LX00001.NLB"
  delete "$INSTDIR\ora90\ocommon\nls\admin\data\LX00023.NLB"
  delete "$INSTDIR\ora90\ocommon\nls\admin\data\LX10001.NLB"
  delete "$INSTDIR\ora90\ocommon\nls\admin\data\LX10035.NLB"
  delete "$INSTDIR\ora90\ocommon\nls\admin\data\LX1BOOT.NLB"
  delete "$INSTDIR\ora90\ocommon\nls\admin\data\LX20001.NLB"
  delete "$INSTDIR\ora90\ocommon\nls\admin\data\LX20354.NLB"
  delete "$INSTDIR\ora90\ocommon\nls\admin\data\LX60354.NLB"
  delete "$INSTDIR\ora90\ocommon\nls\mesg\lxeus.msb"
  delete "$INSTDIR\ora90\ocommon\nls\mesg\lxius.msb"
  delete "$INSTDIR\ora90\oledb\doc\oledb.pdf"
  delete "$INSTDIR\ora90\oledb\doc\readme.txt"
  delete "$INSTDIR\ora90\oledb\include\OraOLEDB.h"
  delete "$INSTDIR\ora90\oledb\lib\OraOLEDB.lib"
  delete "$INSTDIR\ora90\oledb\mesg\oraoledbus.msb"
  delete "$INSTDIR\ora90\oledb\mesg\oraoledbzhs.msb"
  delete "$INSTDIR\ora90\oracore\mesg\lemus.msb"
  delete "$INSTDIR\ora90\oracore\mesg\lfius.msb"
  delete "$INSTDIR\ora90\oracore\mesg\lfizhs.msb"
  delete "$INSTDIR\ora90\oracore\mesg\lhtus.msb"
  delete "$INSTDIR\ora90\oracore\mesg\lmmus.msb"
  delete "$INSTDIR\ora90\oracore\mesg\lpmus.msb"
  delete "$INSTDIR\ora90\oracore\mesg\lrmus.msb"
  delete "$INSTDIR\ora90\oracore\mesg\lrmzhs.msb"
  delete "$INSTDIR\ora90\oracore\mesg\lsfus.msb"
  delete "$INSTDIR\ora90\oracore\mesg\ltmus.msb"
  delete "$INSTDIR\ora90\oracore\zoneinfo\timezlrg.dat"
  delete "$INSTDIR\ora90\oracore\zoneinfo\timezone.dat"
  delete "$INSTDIR\ora90\precomp\admin\ottcfg.cfg"
  delete "$INSTDIR\ora90\precomp\admin\pcbcfg.cfg"
  delete "$INSTDIR\ora90\precomp\admin\pcccob.cfg"
  delete "$INSTDIR\ora90\precomp\admin\pcscfg.cfg"
  delete "$INSTDIR\ora90\precomp\help\proc\connect.hlp"
  delete "$INSTDIR\ora90\precomp\help\proc\lsterror.hlp"
  delete "$INSTDIR\ora90\precomp\help\proc\options.hlp"
  delete "$INSTDIR\ora90\precomp\help\proc\zhs\connect.hlp"
  delete "$INSTDIR\ora90\precomp\help\proc\zhs\lsterror.hlp"
  delete "$INSTDIR\ora90\precomp\help\proc\zhs\options.hlp"
  delete "$INSTDIR\ora90\precomp\lib\msvc\oraSQL9.LIB"
  delete "$INSTDIR\ora90\precomp\lib\msvc\oraSQX9.LIB"
  delete "$INSTDIR\ora90\precomp\lib\orasql9.lib"
  delete "$INSTDIR\ora90\precomp\mesg\o2fus.msb"
  delete "$INSTDIR\ora90\precomp\mesg\o2fzhs.msb"
  delete "$INSTDIR\ora90\precomp\mesg\o2ius.msb"
  delete "$INSTDIR\ora90\precomp\mesg\o2izhs.msb"
  delete "$INSTDIR\ora90\precomp\mesg\o2uus.msb"
  delete "$INSTDIR\ora90\precomp\mesg\o2uzhs.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pcbeus.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pcbezhs.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pcfus.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pcfzhs.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pcsus.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pcszhs.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pg2us.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pg2zhs.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pgous.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pgozhs.msb"
  delete "$INSTDIR\ora90\precomp\mesg\ppeus.msb"
  delete "$INSTDIR\ora90\precomp\mesg\ppezhs.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pr2us.msb"
  delete "$INSTDIR\ora90\precomp\mesg\pr2zhs.msb"
  delete "$INSTDIR\ora90\precomp\mesg\prous.msb"
  delete "$INSTDIR\ora90\precomp\mesg\prozhs.msb"
  delete "$INSTDIR\ora90\precomp\mesg\sqlus.msb"
  delete "$INSTDIR\ora90\precomp\mesg\sqlzhs.msb"
  delete "$INSTDIR\ora90\precomp\misc\proc\add_newl.bat"
  delete "$INSTDIR\ora90\precomp\misc\proc\mod_incl.bat"
  delete "$INSTDIR\ora90\precomp\public\bnddsc.for"
  delete "$INSTDIR\ora90\precomp\public\oraca.cob"
  delete "$INSTDIR\ora90\precomp\public\oraca.for"
  delete "$INSTDIR\ora90\precomp\public\oraca.h"
  delete "$INSTDIR\ora90\precomp\public\oraca5.cob"
  delete "$INSTDIR\ora90\precomp\public\seldsc.for"
  delete "$INSTDIR\ora90\precomp\public\sql2oci.h"
  delete "$INSTDIR\ora90\precomp\public\sqlapr.h"
  delete "$INSTDIR\ora90\precomp\public\sqlca.cob"
  delete "$INSTDIR\ora90\precomp\public\sqlca.for"
  delete "$INSTDIR\ora90\precomp\public\sqlca.h"
  delete "$INSTDIR\ora90\precomp\public\sqlca5.cob"
  delete "$INSTDIR\ora90\precomp\public\sqlcpr.h"
  delete "$INSTDIR\ora90\precomp\public\sqlda.cob"
  delete "$INSTDIR\ora90\precomp\public\sqlda.h"
  delete "$INSTDIR\ora90\precomp\public\sqlda5.cob"
  delete "$INSTDIR\ora90\precomp\public\sqlkpr.h"
  delete "$INSTDIR\ora90\precomp\public\sqlucs2.h"
  delete "$INSTDIR\ora90\RDBMS\mesg\kgpus.msb"
  delete "$INSTDIR\ora90\RDBMS\mesg\kgpzhs.msb"
  delete "$INSTDIR\ora90\RDBMS\mesg\ocius.msb"
  delete "$INSTDIR\ora90\RDBMS\mesg\ocizhs.msb"
  delete "$INSTDIR\ora90\RDBMS\mesg\oraus.msb"
  delete "$INSTDIR\ora90\RDBMS\mesg\orazhs.msb"
  delete "$INSTDIR\ora90\RDBMS\mesg\ulus.msb"
  delete "$INSTDIR\ora90\RDBMS\mesg\ulzhs.msb"
  delete "$INSTDIR\ora90\sqlplus\admin\glogin.sql"
  delete "$INSTDIR\ora90\sqlplus\admin\helpbld.sql"
  delete "$INSTDIR\ora90\sqlplus\admin\helpdrop.sql"
  delete "$INSTDIR\ora90\sqlplus\admin\helpus.sql"
  delete "$INSTDIR\ora90\sqlplus\admin\hlpbld.sql"
  delete "$INSTDIR\ora90\sqlplus\admin\plustrce.sql"
  delete "$INSTDIR\ora90\sqlplus\admin\pupbld.sql"
  delete "$INSTDIR\ora90\sqlplus\admin\sqlplus.ini"
  delete "$INSTDIR\ora90\sqlplus\mesg\cpyus.msb"
  delete "$INSTDIR\ora90\sqlplus\mesg\cpyzhs.msb"
  delete "$INSTDIR\ora90\sqlplus\mesg\sp1us.msb"
  delete "$INSTDIR\ora90\sqlplus\mesg\sp1zhs.msb"
  delete "$INSTDIR\ora90\sqlplus\mesg\sp2us.msb"
  delete "$INSTDIR\ora90\sqlplus\mesg\sp2zhs.msb"
  delete "$INSTDIR\ora90\sqlplus\mesg\spwus.msb"
  delete "$INSTDIR\ora90\sqlplus\mesg\spwzhs.msb"

  RMDir /r "$INSTDIR\ora90\bin"
  RMDir /r "$INSTDIR\ora90\network\ADMIN"
  RMDir /r "$INSTDIR\ora90\network\mesg"
  RMDir /r "$INSTDIR\ora90\network"
  RMDir /r "$INSTDIR\ora90\oci\include"
  RMDir /r "$INSTDIR\ora90\oci\lib"
  RMDir /r "$INSTDIR\ora90\oci"
  RMDir /r "$INSTDIR\ora90\ocommon\nls\admin\data"
  RMDir /r "$INSTDIR\ora90\ocommon\nls\admin"
  RMDir /r "$INSTDIR\ora90\ocommon\nls\mesg"
  RMDir /r "$INSTDIR\ora90\ocommon\nls"
  RMDir /r "$INSTDIR\ora90\ocommon"
  RMDir /r "$INSTDIR\ora90\oledb\doc"
  RMDir /r "$INSTDIR\ora90\oledb\include"
  RMDir /r "$INSTDIR\ora90\oledb\lib"
  RMDir /r "$INSTDIR\ora90\oledb\mesg"
  RMDir /r "$INSTDIR\ora90\oledb"
  RMDir /r "$INSTDIR\ora90\oracore\zoneinfo"
  RMDir /r "$INSTDIR\ora90\oracore\mesg"
  RMDir /r "$INSTDIR\ora90\oracore"
  RMDir /r "$INSTDIR\ora90\precomp\admin\help"
  RMDir /r "$INSTDIR\ora90\precomp\admin"
  RMDir /r "$INSTDIR\ora90\precomp\help\proc\zhs"
  RMDir /r "$INSTDIR\ora90\precomp\help\proc"
  RMDir /r "$INSTDIR\ora90\precomp\help"
  RMDir /r "$INSTDIR\ora90\precomp\lib\msvc"
  RMDir /r "$INSTDIR\ora90\precomp\lib"
  RMDir /r "$INSTDIR\ora90\precomp\misc\proc"
  RMDir /r "$INSTDIR\ora90\precomp\misc"
  RMDir /r "$INSTDIR\ora90\precomp\public"
  RMDir /r "$INSTDIR\ora90\precomp\mesg"
  RMDir /r "$INSTDIR\ora90\precomp"
  RMDir /r "$INSTDIR\ora90\RDBMS\mesg"
  RMDir /r "$INSTDIR\ora90\RDBMS"
  RMDir /r "$INSTDIR\ora90\sqlplus\admin\help"
  RMDir /r "$INSTDIR\ora90\sqlplus\admin"
  RMDir /r "$INSTDIR\ora90\sqlplus\mesg"
  RMDir /r "$INSTDIR\ora90\sqlplus"
  RMDir /r "$INSTDIR\ora90"

  DeleteRegKey HKCU "Software\oracle"
  DeleteRegKey HKLM "Software\oracle"
  DeleteRegKey HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome90"
  DeleteRegValue  HKLM "SOFTWARE\ODBC\ODBCINST.INI\ODBC Drivers" "Oracle in OraHome90"
SectionEnd

Section "oracle 9i mini client (required)"
  SectionIn RO

  SetOutPath "$INSTDIR\ora90\bin"
  File ".\ora90\bin\oci.dll"
  File ".\ora90\bin\oracle.key"
  File ".\ora90\bin\oraclient9.dll"
  File ".\ora90\bin\oracommon9.dll"
  File ".\ora90\bin\ORACORE9.DLL"
  File ".\ora90\bin\orageneric9.dll"
  File ".\ora90\bin\oraldapclnt9.dll"
  File ".\ora90\bin\oran9.dll"
  File ".\ora90\bin\ORANCDS9.DLL"
  File ".\ora90\bin\orancrypt9.dll"
  File ".\ora90\bin\oranhost9.dll"
  File ".\ora90\bin\oranl9.dll"
  File ".\ora90\bin\oranldap9.dll"
  File ".\ora90\bin\ORANLS9.DLL"
  File ".\ora90\bin\oranms.dll"
  File ".\ora90\bin\oranmsp.dll"
  File ".\ora90\bin\orannts9.dll"
  File ".\ora90\bin\orannzsbb9.dll"
  File ".\ora90\bin\oranoname9.dll"
  File ".\ora90\bin\oranro9.dll"
  File ".\ora90\bin\orantcp9.dll"
  File ".\ora90\bin\orantns9.dll"
  File ".\ora90\bin\ORAPLS9.DLL"
  File ".\ora90\bin\ORASLAX9.DLL"
  File ".\ora90\bin\ORASNLS9.DLL"
  File ".\ora90\bin\ORASQL9.DLL"
  File ".\ora90\bin\oratrace9.dll"
  File ".\ora90\bin\ORAUNLS9.DLL"
  File ".\ora90\bin\oravsn9.dll"
  File ".\ora90\bin\orawtc9.dll"
  File ".\ora90\bin\sqora32.dll"
  File ".\ora90\bin\sqoras32.dll"
  File ".\ora90\bin\sqresus.dll"
  File ".\ztools\TNSConf.exe"
  File ".\ztools\OraSQL.exe"

  SetOutPath "$INSTDIR\ora90\network\ADMIN"
  File ".\ora90\network\ADMIN\tnsnames.ora"

  SetOutPath "$INSTDIR\ora90\network\mesg"
  File ".\ora90\network\mesg\ncrus.msb"
  File ".\ora90\network\mesg\ncrzhs.msb"
  File ".\ora90\network\mesg\ncxus.msb"
  File ".\ora90\network\mesg\ncxzhs.msb"
  File ".\ora90\network\mesg\niqus.msb"
  File ".\ora90\network\mesg\niqzhs.msb"
  File ".\ora90\network\mesg\nltus.msb"
  File ".\ora90\network\mesg\nlus.msb"
  File ".\ora90\network\mesg\nlzhs.msb"
  File ".\ora90\network\mesg\nmpus.msb"
  File ".\ora90\network\mesg\nmpzhs.msb"
  File ".\ora90\network\mesg\nmrus.msb"
  File ".\ora90\network\mesg\nncus.msb"
  File ".\ora90\network\mesg\nnczhs.msb"
  File ".\ora90\network\mesg\nnfus.msb"
  File ".\ora90\network\mesg\nnfzhs.msb"
  File ".\ora90\network\mesg\nnlus.msb"
  File ".\ora90\network\mesg\nnlzhs.msb"
  File ".\ora90\network\mesg\nnous.msb"
  File ".\ora90\network\mesg\nnozhs.msb"
  File ".\ora90\network\mesg\nplus.msb"
  File ".\ora90\network\mesg\nplzhs.msb"
  File ".\ora90\network\mesg\nzus.msb"
  File ".\ora90\network\mesg\nzzhs.msb"
  File ".\ora90\network\mesg\snlus.msb"
  File ".\ora90\network\mesg\snlzhs.msb"
  File ".\ora90\network\mesg\tnlus.msb"
  File ".\ora90\network\mesg\tnlzhs.msb"
  File ".\ora90\network\mesg\tnplus.msb"
  File ".\ora90\network\mesg\tnplzhs.msb"

  SetOutPath "$INSTDIR\ora90\ocommon\nls\admin\data"
  File ".\ora90\ocommon\nls\admin\data\LX00001.NLB"
  File ".\ora90\ocommon\nls\admin\data\LX00023.NLB"
  File ".\ora90\ocommon\nls\admin\data\LX10001.NLB"
  File ".\ora90\ocommon\nls\admin\data\LX10035.NLB"
  File ".\ora90\ocommon\nls\admin\data\LX1BOOT.NLB"
  File ".\ora90\ocommon\nls\admin\data\LX20001.NLB"
  File ".\ora90\ocommon\nls\admin\data\LX20354.NLB"
  File ".\ora90\ocommon\nls\admin\data\LX60354.NLB"
  
  SetOutPath "$INSTDIR\ora90\ocommon\nls\mesg"
  File ".\ora90\ocommon\nls\mesg\lxeus.msb"
  File ".\ora90\ocommon\nls\mesg\lxius.msb"

  SetOutPath "$INSTDIR\ora90\oracore\mesg"
  File ".\ora90\oracore\mesg\lemus.msb"
  File ".\ora90\oracore\mesg\lfius.msb"
  File ".\ora90\oracore\mesg\lfizhs.msb"
  File ".\ora90\oracore\mesg\lhtus.msb"
  File ".\ora90\oracore\mesg\lmmus.msb"
  File ".\ora90\oracore\mesg\lpmus.msb"
  File ".\ora90\oracore\mesg\lrmus.msb"
  File ".\ora90\oracore\mesg\lrmzhs.msb"
  File ".\ora90\oracore\mesg\lsfus.msb"
  File ".\ora90\oracore\mesg\ltmus.msb"

  SetOutPath "$INSTDIR\ora90\oracore\zoneinfo"
  File ".\ora90\oracore\zoneinfo\timezlrg.dat"
  File ".\ora90\oracore\zoneinfo\timezone.dat"


  SetOutPath "$INSTDIR\ora90\RDBMS\mesg"
  File ".\ora90\RDBMS\mesg\kgpus.msb"
  File ".\ora90\RDBMS\mesg\kgpzhs.msb"
  File ".\ora90\RDBMS\mesg\ocius.msb"
  File ".\ora90\RDBMS\mesg\ocizhs.msb"
  File ".\ora90\RDBMS\mesg\oraus.msb"
  File ".\ora90\RDBMS\mesg\orazhs.msb"
  File ".\ora90\RDBMS\mesg\ulus.msb"
  File ".\ora90\RDBMS\mesg\ulzhs.msb"

  SetOutPath $WINDIR
  File ".\ora90\oraodbc.ini"
  
  DeleteRegKey HKLM "SOFTWARE\ORACLE"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "ORACLE_HOME" "$INSTDIR\ora90"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "ORACLE_HOME_NAME" "OraHome90"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "API" "$INSTDIR\ora90\dbs"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "ORACLE_GROUP_NAME" "Oracle - OraHome90"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "NLS_LANG" "NA"
  WriteRegStr  HKLM "SOFTWARE\ORACLE" "OLEDB" "$INSTDIR\ora90\oledb\mesg"

  DeleteRegKey HKLM "SOFTWARE\ORACLE\ALL_HOMES"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES" "HOME_COUNTER" "1"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES" "DEFAULT_HOME" "OraHome90"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES" "LAST_HOME" "0"

  DeleteRegKey HKLM "SOFTWARE\ORACLE\ALL_HOMES\ID0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES\ID0" "NAME" "OraHome90"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES\ID0" "PATH" "$INSTDIR\ora90"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\ALL_HOMES\ID0" "NLS_LANG" "NA"

  DeleteRegKey HKLM "SOFTWARE\ORACLE\HOME0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ID" "0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ORACLE_GROUP_NAME" "Oracle - OraHome90"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ORACLE_HOME_NAME" "OraHome90"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ORACLE_HOME" "$INSTDIR\ora90"
  ; if english NA
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "NLS_LANG" "SIMPLIFIED CHINESE_CHINA.ZHS16GBK"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ORACLE_BUNDLE_NAME" "Enterprise"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "ORACLE_HOME_KEY" "oftware\ORACLE\HOME0"
  WriteRegStr  HKLM "SOFTWARE\ORACLE\HOME0" "SQLPATH" "$INSTDIR\ora90\dbs"

  DeleteRegKey HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome90"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome90" "APILevel" "1"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome90" "CPTimeout" "60"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome90" "ConnectFunctions" "YYY"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome90" "Driver" "$INSTDIR\ora90\bin\sqora32.dll"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome90" "DriverODBCVer" "03.51"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome90" "FileUsage" "0"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome90" "Setup" "$INSTDIR\ora90\bin\sqoras32.dll"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\Oracle in OraHome90" "SQLLevel" "1"

  DeleteRegValue  HKLM "SOFTWARE\ODBC\ODBCINST.INI\ODBC Drivers" ""
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\ODBC Drivers" "Oracle in OraHome90" "Installed"
  WriteRegStr  HKLM "SOFTWARE\ODBC\ODBCINST.INI\ODBC Drivers" "" ""
  
  WriteUninstaller "$INSTDIR\Uninstall9.exe"
  StrCpy $0 "$INSTDIR\ora90\bin"
  ReadRegStr $1 HKLM  "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "Path"
  ${StrStr} $2 $1 $0
  strcmp $2 "" setpath end
setpath:
  WriteRegExpandStr HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment" "path" "$1;$0"

end:
SectionEnd

Section "oracle 9i tools"
  SetOutPath "$INSTDIR\ora90\bin"
  File ".\ora90\bin\TNSPING.EXE"

  SetOutPath "$INSTDIR\ora90\network\mesg"
  File ".\ora90\network\mesg\tnsus.msb"
  File ".\ora90\network\mesg\tnszhs.msb"

SectionEnd

Section "oracle 9i sqlplus"
  SetOutPath "$INSTDIR\ora90\bin"
  File ".\ora90\bin\sqlplus.exe"
  File ".\ora90\bin\sqlplusw.exe"
  
  SetOutPath "$INSTDIR\ora90\sqlplus\admin"
  File ".\ora90\sqlplus\admin\glogin.sql"
  File ".\ora90\sqlplus\admin\plustrce.sql"
  File ".\ora90\sqlplus\admin\pupbld.sql"

  SetOutPath "$INSTDIR\ora90\sqlplus\admin\help"
  File ".\ora90\sqlplus\admin\help\helpbld.sql"
  File ".\ora90\sqlplus\admin\help\helpdrop.sql"
  File ".\ora90\sqlplus\admin\help\helpus.sql"
  File ".\ora90\sqlplus\admin\help\hlpbld.sql"

  SetOutPath "$INSTDIR\ora90\sqlplus\mesg"
  File ".\ora90\sqlplus\mesg\cpyus.msb"
  File ".\ora90\sqlplus\mesg\cpyzhs.msb"
  File ".\ora90\sqlplus\mesg\sp1us.msb"
  File ".\ora90\sqlplus\mesg\sp1zhs.msb"
  File ".\ora90\sqlplus\mesg\sp2us.msb"
  File ".\ora90\sqlplus\mesg\sp2zhs.msb"
  File ".\ora90\sqlplus\mesg\spwus.msb"
  File ".\ora90\sqlplus\mesg\spwzhs.msb"

SectionEnd

Section /o "oracle 9i oci sdk"
  SetOutPath "$INSTDIR\ora90\bin"
  File ".\ora90\bin\ociw32.dll"
  File ".\ora90\bin\oraocci9.dll"

  SetOutPath "$INSTDIR\ora90\oci\include"
  File ".\ora90\oci\include\cdemodp0.h"
  File ".\ora90\oci\include\kusapi.h"
  File ".\ora90\oci\include\kustags.h"
  File ".\ora90\oci\include\nzerror.h"
  File ".\ora90\oci\include\nzt.h"
  File ".\ora90\oci\include\occi.h"
  File ".\ora90\oci\include\occiCommon.h"
  File ".\ora90\oci\include\occiControl.h"
  File ".\ora90\oci\include\occiData.h"
  File ".\ora90\oci\include\occiObjects.h"
  File ".\ora90\oci\include\oci.h"
  File ".\ora90\oci\include\oci1.h"
  File ".\ora90\oci\include\oci8dp.h"
  File ".\ora90\oci\include\ociap.h"
  File ".\ora90\oci\include\ociapr.h"
  File ".\ora90\oci\include\ocidef.h"
  File ".\ora90\oci\include\ocidem.h"
  File ".\ora90\oci\include\ocidfn.h"
  File ".\ora90\oci\include\ociextp.h"
  File ".\ora90\oci\include\ocikp.h"
  File ".\ora90\oci\include\ocikpr.h"
  File ".\ora90\oci\include\ocixad.h"
  File ".\ora90\oci\include\odci.h"
  File ".\ora90\oci\include\oratypes.h"
  File ".\ora90\oci\include\ori.h"
  File ".\ora90\oci\include\orid.h"
  File ".\ora90\oci\include\orl.h"
  File ".\ora90\oci\include\oro.h"
  File ".\ora90\oci\include\ort.h"

  SetOutPath "$INSTDIR\ora90\oci\lib"
  File ".\ora90\oci\lib\oci.lib"
  File ".\ora90\oci\lib\ociw32.lib"
  File ".\ora90\oci\lib\oraocci9.lib"

SectionEnd

Section /o "oracle 9i oledb sdk"
  SetOutPath "$INSTDIR\ora90\bin"
  File ".\ora90\bin\OraOLEDB.dll"
  File ".\ora90\bin\OraOLEDB.tlb"

  SetOutPath "$INSTDIR\ora90\oledb\doc"
  File ".\ora90\oledb\doc\oledb.pdf"
  File ".\ora90\oledb\doc\readme.txt"

  SetOutPath "$INSTDIR\ora90\oledb\include"
  File ".\ora90\oledb\include\OraOLEDB.h"

  SetOutPath "$INSTDIR\ora90\oledb\lib"
  File ".\ora90\oledb\lib\OraOLEDB.lib"

  SetOutPath "$INSTDIR\ora90\oledb\mesg"
  File ".\ora90\oledb\mesg\oraoledbus.msb"
  File ".\ora90\oledb\mesg\oraoledbzhs.msb"
  
  RegDLL "$INSTDIR\ora90\bin\OraOLEDB.dll"
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

Section /o "oracle 9i proc sdk"
  SetOutPath "$INSTDIR\ora90\bin"
  File ".\ora90\bin\ott.exe"
  File ".\ora90\bin\ott8.exe"
  File ".\ora90\bin\proc.exe"
  File ".\ora90\bin\procd9.dll"
  File ".\ora90\bin\proce9.dll"
  File ".\ora90\bin\procf9.dll"
  File ".\ora90\bin\proci9.dll"
  File ".\ora90\bin\procja9.dll"
  File ".\ora90\bin\procko9.dll"
  File ".\ora90\bin\procob.exe"
  File ".\ora90\bin\procob18.exe"
  File ".\ora90\bin\procptb9.dll"
  File ".\ora90\bin\procui.exe"
  File ".\ora90\bin\procus9.dll"
  File ".\ora90\bin\proczhs9.dll"

 SetOutPath "$INSTDIR\ora90\precomp\admin"
  File ".\ora90\precomp\admin\ottcfg.cfg"
  File ".\ora90\precomp\admin\pcbcfg.cfg"
  File ".\ora90\precomp\admin\pcccob.cfg"
  File ".\ora90\precomp\admin\pcscfg.cfg"

  SetOutPath "$INSTDIR\ora90\precomp\help\proc"
  File ".\ora90\precomp\help\proc\connect.hlp"
  File ".\ora90\precomp\help\proc\lsterror.hlp"
  File ".\ora90\precomp\help\proc\options.hlp"

  SetOutPath "$INSTDIR\ora90\precomp\help\proc\zhs"
  File ".\ora90\precomp\help\proc\zhs\connect.hlp"
  File ".\ora90\precomp\help\proc\zhs\lsterror.hlp"
  File ".\ora90\precomp\help\proc\zhs\options.hlp"

  SetOutPath "$INSTDIR\ora90\precomp\lib\msvc"
  File ".\ora90\precomp\lib\msvc\oraSQL9.LIB"
  File ".\ora90\precomp\lib\msvc\oraSQX9.LIB"

  SetOutPath "$INSTDIR\ora90\precomp\lib"
  File ".\ora90\precomp\lib\orasql9.lib"

  SetOutPath "$INSTDIR\ora90\precomp\mesg"
  File ".\ora90\precomp\mesg\o2fus.msb"
  File ".\ora90\precomp\mesg\o2fzhs.msb"
  File ".\ora90\precomp\mesg\o2ius.msb"
  File ".\ora90\precomp\mesg\o2izhs.msb"
  File ".\ora90\precomp\mesg\o2uus.msb"
  File ".\ora90\precomp\mesg\o2uzhs.msb"
  File ".\ora90\precomp\mesg\pcbeus.msb"
  File ".\ora90\precomp\mesg\pcbezhs.msb"
  File ".\ora90\precomp\mesg\pcfus.msb"
  File ".\ora90\precomp\mesg\pcfzhs.msb"
  File ".\ora90\precomp\mesg\pcsus.msb"
  File ".\ora90\precomp\mesg\pcszhs.msb"
  File ".\ora90\precomp\mesg\pg2us.msb"
  File ".\ora90\precomp\mesg\pg2zhs.msb"
  File ".\ora90\precomp\mesg\pgous.msb"
  File ".\ora90\precomp\mesg\pgozhs.msb"
  File ".\ora90\precomp\mesg\ppeus.msb"
  File ".\ora90\precomp\mesg\ppezhs.msb"
  File ".\ora90\precomp\mesg\pr2us.msb"
  File ".\ora90\precomp\mesg\pr2zhs.msb"
  File ".\ora90\precomp\mesg\prous.msb"
  File ".\ora90\precomp\mesg\prozhs.msb"
  File ".\ora90\precomp\mesg\sqlus.msb"
  File ".\ora90\precomp\mesg\sqlzhs.msb"

  SetOutPath "$INSTDIR\ora90\precomp\misc\proc"
  File ".\ora90\precomp\misc\proc\add_newl.bat"
  File ".\ora90\precomp\misc\proc\mod_incl.bat"

  SetOutPath "$INSTDIR\ora90\precomp\public"
  File ".\ora90\precomp\public\bnddsc.for"
  File ".\ora90\precomp\public\oraca.cob"
  File ".\ora90\precomp\public\oraca.for"
  File ".\ora90\precomp\public\oraca.h"
  File ".\ora90\precomp\public\oraca5.cob"
  File ".\ora90\precomp\public\seldsc.for"
  File ".\ora90\precomp\public\sql2oci.h"
  File ".\ora90\precomp\public\sqlapr.h"
  File ".\ora90\precomp\public\sqlca.cob"
  File ".\ora90\precomp\public\sqlca.for"
  File ".\ora90\precomp\public\sqlca.h"
  File ".\ora90\precomp\public\sqlca5.cob"
  File ".\ora90\precomp\public\sqlcpr.h"
  File ".\ora90\precomp\public\sqlda.cob"
  File ".\ora90\precomp\public\sqlda.h"
  File ".\ora90\precomp\public\sqlda5.cob"
  File ".\ora90\precomp\public\sqlkpr.h"
  File ".\ora90\precomp\public\sqlucs2.h"

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


