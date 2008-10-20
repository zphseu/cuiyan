@echo off
if "z%1"=="z" goto usage

set srcpath=%1
set despath=.\ora90

if not exist %despath%\NUL md %despath%
if not exist %despath%\bin\NUL                      md %despath%\bin
if not exist %despath%\network\NUL                  md %despath%\network
if not exist %despath%\network\ADMIN\NUL            md %despath%\network\ADMIN
if not exist %despath%\network\mesg\NUL             md %despath%\network\mesg
if not exist %despath%\oci\NUL                      md %despath%\oci
if not exist %despath%\oci\include\NUL              md %despath%\oci\include
if not exist %despath%\oci\lib\NUL                  md %despath%\oci\lib
if not exist %despath%\oci\lib\msvc\NUL             md %despath%\oci\lib\msvc
if not exist %despath%\ocommon\NUL                  md %despath%\ocommon
if not exist %despath%\ocommon\nls\NUL              md %despath%\ocommon\nls
if not exist %despath%\ocommon\nls\admin\NUL        md %despath%\ocommon\nls\admin
if not exist %despath%\ocommon\nls\admin\data\NUL   md %despath%\ocommon\nls\admin\data
if not exist %despath%\ocommon\nls\mesg\NUL         md %despath%\ocommon\nls\mesg
if not exist %despath%\oledb\NUL                    md %despath%\oledb
if not exist %despath%\oledb\doc\NUL                md %despath%\oledb\doc
if not exist %despath%\oledb\include\NUL            md %despath%\oledb\include
if not exist %despath%\oledb\lib\NUL                md %despath%\oledb\lib
if not exist %despath%\oledb\mesg\NUL               md %despath%\oledb\mesg
if not exist %despath%\oracore\NUL                  md %despath%\oracore
if not exist %despath%\oracore\mesg\NUL             md %despath%\oracore\mesg
if not exist %despath%\oracore\zoneinfo\NUL         md %despath%\oracore\zoneinfo
if not exist %despath%\precomp\NUL                  md %despath%\precomp
if not exist %despath%\precomp\admin\NUL            md %despath%\precomp\admin
if not exist %despath%\precomp\help\NUL             md %despath%\precomp\help
if not exist %despath%\precomp\help\proc\NUL        md %despath%\precomp\help\proc
if not exist %despath%\precomp\help\proc\zhs\NUL    md %despath%\precomp\help\proc\zhs
if not exist %despath%\precomp\lib\NUL              md %despath%\precomp\lib
if not exist %despath%\precomp\lib\msvc\NUL         md %despath%\precomp\lib\msvc
if not exist %despath%\precomp\mesg\NUL             md %despath%\precomp\mesg
if not exist %despath%\precomp\misc\NUL             md %despath%\precomp\misc
if not exist %despath%\precomp\misc\proc\NUL        md %despath%\precomp\misc\proc
if not exist %despath%\precomp\public\NUL           md %despath%\precomp\public
if not exist %despath%\RDBMS\NUL                    md %despath%\RDBMS
if not exist %despath%\RDBMS\mesg\NUL               md %despath%\RDBMS\mesg
if not exist %despath%\sqlplus\NUL                  md %despath%\sqlplus
if not exist %despath%\sqlplus\admin\NUL            md %despath%\sqlplus\admin
if not exist %despath%\sqlplus\mesg\NUL             md %despath%\sqlplus\mesg
if not exist %despath%\sqlplus\admin\help\NUL       md %despath%\sqlplus\admin\help

if exist  %srcpath%\bin\oci.dll				copy %srcpath%\bin\oci.dll				%despath%\bin\oci.dll					> NUL
if exist  %srcpath%\bin\ociw32.dll			copy %srcpath%\bin\ociw32.dll				%despath%\bin\ociw32.dll				> NUL
if exist  %srcpath%\bin\oracle.key			copy %srcpath%\bin\oracle.key				%despath%\bin\oracle.key				> NUL
if exist  %srcpath%\bin\oraclient9.dll			copy %srcpath%\bin\oraclient9.dll			%despath%\bin\oraclient9.dll				> NUL
if exist  %srcpath%\bin\oracommon9.dll			copy %srcpath%\bin\oracommon9.dll			%despath%\bin\oracommon9.dll				> NUL
if exist  %srcpath%\bin\ORACORE9.DLL			copy %srcpath%\bin\ORACORE9.DLL				%despath%\bin\ORACORE9.DLL				> NUL
if exist  %srcpath%\bin\orageneric9.dll			copy %srcpath%\bin\orageneric9.dll			%despath%\bin\orageneric9.dll				> NUL
if exist  %srcpath%\bin\oraldapclnt9.dll		copy %srcpath%\bin\oraldapclnt9.dll			%despath%\bin\oraldapclnt9.dll				> NUL
if exist  %srcpath%\bin\oran9.dll			copy %srcpath%\bin\oran9.dll				%despath%\bin\oran9.dll					> NUL
if exist  %srcpath%\bin\ORANCDS9.DLL			copy %srcpath%\bin\ORANCDS9.DLL				%despath%\bin\ORANCDS9.DLL				> NUL
if exist  %srcpath%\bin\orancrypt9.dll			copy %srcpath%\bin\orancrypt9.dll			%despath%\bin\orancrypt9.dll				> NUL
if exist  %srcpath%\bin\oranhost9.dll			copy %srcpath%\bin\oranhost9.dll			%despath%\bin\oranhost9.dll				> NUL
if exist  %srcpath%\bin\oranl9.dll			copy %srcpath%\bin\oranl9.dll				%despath%\bin\oranl9.dll				> NUL
if exist  %srcpath%\bin\oranldap9.dll			copy %srcpath%\bin\oranldap9.dll			%despath%\bin\oranldap9.dll				> NUL
if exist  %srcpath%\bin\ORANLS9.DLL			copy %srcpath%\bin\ORANLS9.DLL				%despath%\bin\ORANLS9.DLL				> NUL
if exist  %srcpath%\bin\oranms.dll			copy %srcpath%\bin\oranms.dll				%despath%\bin\oranms.dll				> NUL
if exist  %srcpath%\bin\oranmsp.dll			copy %srcpath%\bin\oranmsp.dll				%despath%\bin\oranmsp.dll				> NUL
if exist  %srcpath%\bin\orannts9.dll			copy %srcpath%\bin\orannts9.dll				%despath%\bin\orannts9.dll				> NUL
if exist  %srcpath%\bin\orannzsbb9.dll			copy %srcpath%\bin\orannzsbb9.dll			%despath%\bin\orannzsbb9.dll				> NUL
if exist  %srcpath%\bin\oranoname9.dll			copy %srcpath%\bin\oranoname9.dll			%despath%\bin\oranoname9.dll				> NUL
if exist  %srcpath%\bin\oranro9.dll			copy %srcpath%\bin\oranro9.dll				%despath%\bin\oranro9.dll				> NUL
if exist  %srcpath%\bin\orantcp9.dll			copy %srcpath%\bin\orantcp9.dll				%despath%\bin\orantcp9.dll				> NUL
if exist  %srcpath%\bin\orantns9.dll			copy %srcpath%\bin\orantns9.dll				%despath%\bin\orantns9.dll				> NUL
if exist  %srcpath%\bin\oraocci9.dll			copy %srcpath%\bin\oraocci9.dll				%despath%\bin\oraocci9.dll				> NUL
if exist  %srcpath%\bin\OraOLEDB.dll			copy %srcpath%\bin\OraOLEDB.dll				%despath%\bin\OraOLEDB.dll				> NUL
if exist  %srcpath%\bin\OraOLEDB.tlb			copy %srcpath%\bin\OraOLEDB.tlb				%despath%\bin\OraOLEDB.tlb				> NUL
if exist  %srcpath%\bin\ORAPLS9.DLL			copy %srcpath%\bin\ORAPLS9.DLL				%despath%\bin\ORAPLS9.DLL				> NUL
if exist  %srcpath%\bin\ORASLAX9.DLL			copy %srcpath%\bin\ORASLAX9.DLL				%despath%\bin\ORASLAX9.DLL				> NUL
if exist  %srcpath%\bin\ORASNLS9.DLL			copy %srcpath%\bin\ORASNLS9.DLL				%despath%\bin\ORASNLS9.DLL				> NUL
if exist  %srcpath%\bin\OraSQL.exe			copy %srcpath%\bin\OraSQL.exe				%despath%\bin\OraSQL.exe				> NUL
if exist  %srcpath%\bin\ORASQL9.DLL			copy %srcpath%\bin\ORASQL9.DLL				%despath%\bin\ORASQL9.DLL				> NUL
if exist  %srcpath%\bin\oratrace9.dll			copy %srcpath%\bin\oratrace9.dll			%despath%\bin\oratrace9.dll				> NUL
if exist  %srcpath%\bin\ORAUNLS9.DLL			copy %srcpath%\bin\ORAUNLS9.DLL				%despath%\bin\ORAUNLS9.DLL				> NUL
if exist  %srcpath%\bin\oravsn9.dll			copy %srcpath%\bin\oravsn9.dll				%despath%\bin\oravsn9.dll				> NUL
if exist  %srcpath%\bin\orawtc9.dll			copy %srcpath%\bin\orawtc9.dll				%despath%\bin\orawtc9.dll				> NUL
if exist  %srcpath%\bin\ott.exe				copy %srcpath%\bin\ott.exe				%despath%\bin\ott.exe					> NUL
if exist  %srcpath%\bin\ott8.exe			copy %srcpath%\bin\ott8.exe				%despath%\bin\ott8.exe					> NUL
if exist  %srcpath%\bin\proc.exe			copy %srcpath%\bin\proc.exe				%despath%\bin\proc.exe					> NUL
if exist  %srcpath%\bin\procd9.dll			copy %srcpath%\bin\procd9.dll				%despath%\bin\procd9.dll				> NUL
if exist  %srcpath%\bin\proce9.dll			copy %srcpath%\bin\proce9.dll				%despath%\bin\proce9.dll				> NUL
if exist  %srcpath%\bin\procf9.dll			copy %srcpath%\bin\procf9.dll				%despath%\bin\procf9.dll				> NUL
if exist  %srcpath%\bin\proci9.dll			copy %srcpath%\bin\proci9.dll				%despath%\bin\proci9.dll				> NUL
if exist  %srcpath%\bin\procja9.dll			copy %srcpath%\bin\procja9.dll				%despath%\bin\procja9.dll				> NUL
if exist  %srcpath%\bin\procko9.dll			copy %srcpath%\bin\procko9.dll				%despath%\bin\procko9.dll				> NUL
if exist  %srcpath%\bin\procob.exe			copy %srcpath%\bin\procob.exe				%despath%\bin\procob.exe				> NUL
if exist  %srcpath%\bin\procob18.exe			copy %srcpath%\bin\procob18.exe				%despath%\bin\procob18.exe				> NUL
if exist  %srcpath%\bin\procptb9.dll			copy %srcpath%\bin\procptb9.dll				%despath%\bin\procptb9.dll				> NUL
if exist  %srcpath%\bin\procui.exe			copy %srcpath%\bin\procui.exe				%despath%\bin\procui.exe				> NUL
if exist  %srcpath%\bin\procus9.dll			copy %srcpath%\bin\procus9.dll				%despath%\bin\procus9.dll				> NUL
if exist  %srcpath%\bin\proczhs9.dll			copy %srcpath%\bin\proczhs9.dll				%despath%\bin\proczhs9.dll				> NUL
if exist  %srcpath%\bin\sqlplus.exe			copy %srcpath%\bin\sqlplus.exe				%despath%\bin\sqlplus.exe				> NUL
if exist  %srcpath%\bin\sqlplusw.exe			copy %srcpath%\bin\sqlplusw.exe				%despath%\bin\sqlplusw.exe				> NUL
if exist  %srcpath%\bin\sqora32.dll			copy %srcpath%\bin\sqora32.dll				%despath%\bin\sqora32.dll				> NUL
if exist  %srcpath%\bin\sqoras32.dll			copy %srcpath%\bin\sqoras32.dll				%despath%\bin\sqoras32.dll				> NUL
if exist  %srcpath%\bin\sqresus.dll			copy %srcpath%\bin\sqresus.dll				%despath%\bin\sqresus.dll				> NUL
if exist  %srcpath%\bin\TNSConf.exe			copy %srcpath%\bin\TNSConf.exe				%despath%\bin\TNSConf.exe				> NUL
if exist  %srcpath%\bin\TNSPING.EXE			copy %srcpath%\bin\TNSPING.EXE				%despath%\bin\TNSPING.EXE				> NUL
if exist  %srcpath%\network\ADMIN\tnsnames.ora		copy %srcpath%\network\ADMIN\tnsnames.ora		%despath%\network\ADMIN\tnsnames.ora  			> NUL
if exist  %srcpath%\network\mesg\ncrus.msb		copy %srcpath%\network\mesg\ncrus.msb			%despath%\network\mesg\ncrus.msb			> NUL
if exist  %srcpath%\network\mesg\ncrzhs.msb		copy %srcpath%\network\mesg\ncrzhs.msb			%despath%\network\mesg\ncrzhs.msb			> NUL
if exist  %srcpath%\network\mesg\ncxus.msb		copy %srcpath%\network\mesg\ncxus.msb			%despath%\network\mesg\ncxus.msb			> NUL
if exist  %srcpath%\network\mesg\ncxzhs.msb		copy %srcpath%\network\mesg\ncxzhs.msb			%despath%\network\mesg\ncxzhs.msb			> NUL
if exist  %srcpath%\network\mesg\niqus.msb		copy %srcpath%\network\mesg\niqus.msb			%despath%\network\mesg\niqus.msb			> NUL
if exist  %srcpath%\network\mesg\niqzhs.msb		copy %srcpath%\network\mesg\niqzhs.msb			%despath%\network\mesg\niqzhs.msb			> NUL
if exist  %srcpath%\network\mesg\nltus.msb		copy %srcpath%\network\mesg\nltus.msb			%despath%\network\mesg\nltus.msb			> NUL
if exist  %srcpath%\network\mesg\nlus.msb		copy %srcpath%\network\mesg\nlus.msb			%despath%\network\mesg\nlus.msb				> NUL
if exist  %srcpath%\network\mesg\nlzhs.msb		copy %srcpath%\network\mesg\nlzhs.msb			%despath%\network\mesg\nlzhs.msb			> NUL
if exist  %srcpath%\network\mesg\nmpus.msb		copy %srcpath%\network\mesg\nmpus.msb			%despath%\network\mesg\nmpus.msb			> NUL
if exist  %srcpath%\network\mesg\nmpzhs.msb		copy %srcpath%\network\mesg\nmpzhs.msb			%despath%\network\mesg\nmpzhs.msb			> NUL
if exist  %srcpath%\network\mesg\nmrus.msb		copy %srcpath%\network\mesg\nmrus.msb			%despath%\network\mesg\nmrus.msb			> NUL
if exist  %srcpath%\network\mesg\nncus.msb		copy %srcpath%\network\mesg\nncus.msb			%despath%\network\mesg\nncus.msb			> NUL
if exist  %srcpath%\network\mesg\nnczhs.msb		copy %srcpath%\network\mesg\nnczhs.msb			%despath%\network\mesg\nnczhs.msb			> NUL
if exist  %srcpath%\network\mesg\nnfus.msb		copy %srcpath%\network\mesg\nnfus.msb			%despath%\network\mesg\nnfus.msb			> NUL
if exist  %srcpath%\network\mesg\nnfzhs.msb		copy %srcpath%\network\mesg\nnfzhs.msb			%despath%\network\mesg\nnfzhs.msb			> NUL
if exist  %srcpath%\network\mesg\nnlus.msb		copy %srcpath%\network\mesg\nnlus.msb			%despath%\network\mesg\nnlus.msb			> NUL
if exist  %srcpath%\network\mesg\nnlzhs.msb		copy %srcpath%\network\mesg\nnlzhs.msb			%despath%\network\mesg\nnlzhs.msb			> NUL
if exist  %srcpath%\network\mesg\nnous.msb		copy %srcpath%\network\mesg\nnous.msb			%despath%\network\mesg\nnous.msb			> NUL
if exist  %srcpath%\network\mesg\nnozhs.msb		copy %srcpath%\network\mesg\nnozhs.msb			%despath%\network\mesg\nnozhs.msb			> NUL
if exist  %srcpath%\network\mesg\nplus.msb		copy %srcpath%\network\mesg\nplus.msb			%despath%\network\mesg\nplus.msb			> NUL
if exist  %srcpath%\network\mesg\nplzhs.msb		copy %srcpath%\network\mesg\nplzhs.msb			%despath%\network\mesg\nplzhs.msb			> NUL
if exist  %srcpath%\network\mesg\nzus.msb		copy %srcpath%\network\mesg\nzus.msb			%despath%\network\mesg\nzus.msb				> NUL
if exist  %srcpath%\network\mesg\nzzhs.msb		copy %srcpath%\network\mesg\nzzhs.msb			%despath%\network\mesg\nzzhs.msb			> NUL
if exist  %srcpath%\network\mesg\snlus.msb		copy %srcpath%\network\mesg\snlus.msb			%despath%\network\mesg\snlus.msb			> NUL
if exist  %srcpath%\network\mesg\snlzhs.msb		copy %srcpath%\network\mesg\snlzhs.msb			%despath%\network\mesg\snlzhs.msb			> NUL
if exist  %srcpath%\network\mesg\tnlus.msb		copy %srcpath%\network\mesg\tnlus.msb			%despath%\network\mesg\tnlus.msb			> NUL
if exist  %srcpath%\network\mesg\tnlzhs.msb		copy %srcpath%\network\mesg\tnlzhs.msb			%despath%\network\mesg\tnlzhs.msb			> NUL
if exist  %srcpath%\network\mesg\tnplus.msb		copy %srcpath%\network\mesg\tnplus.msb			%despath%\network\mesg\tnplus.msb			> NUL
if exist  %srcpath%\network\mesg\tnplzhs.msb		copy %srcpath%\network\mesg\tnplzhs.msb			%despath%\network\mesg\tnplzhs.msb			> NUL
if exist  %srcpath%\network\mesg\tnsus.msb		copy %srcpath%\network\mesg\tnsus.msb			%despath%\network\mesg\tnsus.msb			> NUL
if exist  %srcpath%\network\mesg\tnszhs.msb		copy %srcpath%\network\mesg\tnszhs.msb			%despath%\network\mesg\tnszhs.msb			> NUL
if exist  %srcpath%\oci\include\cdemodp0.h		copy %srcpath%\oci\include\cdemodp0.h			%despath%\oci\include\cdemodp0.h			> NUL
if exist  %srcpath%\oci\include\kusapi.h		copy %srcpath%\oci\include\kusapi.h			%despath%\oci\include\kusapi.h				> NUL
if exist  %srcpath%\oci\include\kustags.h		copy %srcpath%\oci\include\kustags.h			%despath%\oci\include\kustags.h				> NUL
if exist  %srcpath%\oci\include\nzerror.h		copy %srcpath%\oci\include\nzerror.h			%despath%\oci\include\nzerror.h				> NUL
if exist  %srcpath%\oci\include\nzt.h			copy %srcpath%\oci\include\nzt.h			%despath%\oci\include\nzt.h				> NUL
if exist  %srcpath%\oci\include\occi.h			copy %srcpath%\oci\include\occi.h			%despath%\oci\include\occi.h				> NUL
if exist  %srcpath%\oci\include\occiCommon.h		copy %srcpath%\oci\include\occiCommon.h			%despath%\oci\include\occiCommon.h			> NUL
if exist  %srcpath%\oci\include\occiControl.h		copy %srcpath%\oci\include\occiControl.h		%despath%\oci\include\occiControl.h			> NUL
if exist  %srcpath%\oci\include\occiData.h		copy %srcpath%\oci\include\occiData.h			%despath%\oci\include\occiData.h			> NUL
if exist  %srcpath%\oci\include\occiObjects.h		copy %srcpath%\oci\include\occiObjects.h		%despath%\oci\include\occiObjects.h			> NUL
if exist  %srcpath%\oci\include\oci.h			copy %srcpath%\oci\include\oci.h			%despath%\oci\include\oci.h				> NUL
if exist  %srcpath%\oci\include\oci1.h			copy %srcpath%\oci\include\oci1.h			%despath%\oci\include\oci1.h				> NUL
if exist  %srcpath%\oci\include\oci8dp.h		copy %srcpath%\oci\include\oci8dp.h			%despath%\oci\include\oci8dp.h				> NUL
if exist  %srcpath%\oci\include\ociap.h			copy %srcpath%\oci\include\ociap.h			%despath%\oci\include\ociap.h				> NUL
if exist  %srcpath%\oci\include\ociapr.h		copy %srcpath%\oci\include\ociapr.h			%despath%\oci\include\ociapr.h				> NUL
if exist  %srcpath%\oci\include\ocidef.h		copy %srcpath%\oci\include\ocidef.h			%despath%\oci\include\ocidef.h				> NUL
if exist  %srcpath%\oci\include\ocidem.h		copy %srcpath%\oci\include\ocidem.h			%despath%\oci\include\ocidem.h				> NUL
if exist  %srcpath%\oci\include\ocidfn.h		copy %srcpath%\oci\include\ocidfn.h			%despath%\oci\include\ocidfn.h				> NUL
if exist  %srcpath%\oci\include\ociextp.h		copy %srcpath%\oci\include\ociextp.h			%despath%\oci\include\ociextp.h				> NUL
if exist  %srcpath%\oci\include\ocikp.h			copy %srcpath%\oci\include\ocikp.h			%despath%\oci\include\ocikp.h				> NUL
if exist  %srcpath%\oci\include\ocikpr.h		copy %srcpath%\oci\include\ocikpr.h			%despath%\oci\include\ocikpr.h				> NUL
if exist  %srcpath%\oci\include\ocixad.h		copy %srcpath%\oci\include\ocixad.h			%despath%\oci\include\ocixad.h				> NUL
if exist  %srcpath%\oci\include\odci.h			copy %srcpath%\oci\include\odci.h			%despath%\oci\include\odci.h				> NUL
if exist  %srcpath%\oci\include\oratypes.h		copy %srcpath%\oci\include\oratypes.h			%despath%\oci\include\oratypes.h			> NUL
if exist  %srcpath%\oci\include\ori.h			copy %srcpath%\oci\include\ori.h			%despath%\oci\include\ori.h				> NUL
if exist  %srcpath%\oci\include\orid.h			copy %srcpath%\oci\include\orid.h			%despath%\oci\include\orid.h				> NUL
if exist  %srcpath%\oci\include\orl.h			copy %srcpath%\oci\include\orl.h			%despath%\oci\include\orl.h				> NUL
if exist  %srcpath%\oci\include\oro.h			copy %srcpath%\oci\include\oro.h			%despath%\oci\include\oro.h				> NUL
if exist  %srcpath%\oci\include\ort.h			copy %srcpath%\oci\include\ort.h			%despath%\oci\include\ort.h				> NUL
if exist  %srcpath%\oci\lib\oci.lib			copy %srcpath%\oci\lib\oci.lib				%despath%\oci\lib\oci.lib				> NUL
if exist  %srcpath%\oci\lib\ociw32.lib			copy %srcpath%\oci\lib\ociw32.lib			%despath%\oci\lib\ociw32.lib				> NUL
if exist  %srcpath%\oci\lib\oraocci9.lib		copy %srcpath%\oci\lib\oraocci9.lib			%despath%\oci\lib\oraocci9.lib				> NUL
if exist  %srcpath%\ocommon\nls\admin\data\LX00001.NLB	copy %srcpath%\ocommon\nls\admin\data\LX00001.NLB	%despath%\ocommon\nls\admin\data\LX00001.NLB    	> NUL
if exist  %srcpath%\ocommon\nls\admin\data\LX00023.NLB	copy %srcpath%\ocommon\nls\admin\data\LX00023.NLB	%despath%\ocommon\nls\admin\data\LX00023.NLB		> NUL
if exist  %srcpath%\ocommon\nls\admin\data\LX10001.NLB	copy %srcpath%\ocommon\nls\admin\data\LX10001.NLB	%despath%\ocommon\nls\admin\data\LX10001.NLB		> NUL
if exist  %srcpath%\ocommon\nls\admin\data\LX10035.NLB	copy %srcpath%\ocommon\nls\admin\data\LX10035.NLB	%despath%\ocommon\nls\admin\data\LX10035.NLB		> NUL
if exist  %srcpath%\ocommon\nls\admin\data\LX1BOOT.NLB	copy %srcpath%\ocommon\nls\admin\data\LX1BOOT.NLB	%despath%\ocommon\nls\admin\data\LX1BOOT.NLB		> NUL
if exist  %srcpath%\ocommon\nls\admin\data\LX20001.NLB	copy %srcpath%\ocommon\nls\admin\data\LX20001.NLB	%despath%\ocommon\nls\admin\data\LX20001.NLB		> NUL
if exist  %srcpath%\ocommon\nls\admin\data\LX20354.NLB	copy %srcpath%\ocommon\nls\admin\data\LX20354.NLB	%despath%\ocommon\nls\admin\data\LX20354.NLB		> NUL
if exist %srcpath%\ocommon\nls\admin\data\LX60354.NLB	copy %srcpath%\ocommon\nls\admin\data\LX60354.NLB	%despath%\ocommon\nls\admin\data\LX60354.NLB		> NUL
if exist %srcpath%\ocommon\nls\mesg\lxeus.msb		copy %srcpath%\ocommon\nls\mesg\lxeus.msb		%despath%\ocommon\nls\mesg\lxeus.msb			> NUL
if exist %srcpath%\ocommon\nls\mesg\lxius.msb		copy %srcpath%\ocommon\nls\mesg\lxius.msb		%despath%\ocommon\nls\mesg\lxius.msb			> NUL
if exist %srcpath%\oledb\doc\oledb.pdf			copy %srcpath%\oledb\doc\oledb.pdf			%despath%\oledb\doc\oledb.pdf				> NUL
if exist %srcpath%\oledb\doc\readme.txt			copy %srcpath%\oledb\doc\readme.txt			%despath%\oledb\doc\readme.txt				> NUL
if exist %srcpath%\oledb\include\OraOLEDB.h		copy %srcpath%\oledb\include\OraOLEDB.h			%despath%\oledb\include\OraOLEDB.h			> NUL
if exist %srcpath%\oledb\lib\OraOLEDB.lib		copy %srcpath%\oledb\lib\OraOLEDB.lib			%despath%\oledb\lib\OraOLEDB.lib			> NUL
if exist %srcpath%\oledb\mesg\oraoledbus.msb		copy %srcpath%\oledb\mesg\oraoledbus.msb		%despath%\oledb\mesg\oraoledbus.msb			> NUL
if exist %srcpath%\oledb\mesg\oraoledbzhs.msb		copy %srcpath%\oledb\mesg\oraoledbzhs.msb		%despath%\oledb\mesg\oraoledbzhs.msb			> NUL
if exist %srcpath%\oracore\mesg\lemus.msb		copy %srcpath%\oracore\mesg\lemus.msb			%despath%\oracore\mesg\lemus.msb			> NUL
if exist %srcpath%\oracore\mesg\lfius.msb		copy %srcpath%\oracore\mesg\lfius.msb			%despath%\oracore\mesg\lfius.msb			> NUL
if exist %srcpath%\oracore\mesg\lfizhs.msb		copy %srcpath%\oracore\mesg\lfizhs.msb			%despath%\oracore\mesg\lfizhs.msb			> NUL
if exist %srcpath%\oracore\mesg\lhtus.msb		copy %srcpath%\oracore\mesg\lhtus.msb			%despath%\oracore\mesg\lhtus.msb			> NUL
if exist %srcpath%\oracore\mesg\lmmus.msb		copy %srcpath%\oracore\mesg\lmmus.msb			%despath%\oracore\mesg\lmmus.msb			> NUL
if exist %srcpath%\oracore\mesg\lpmus.msb		copy %srcpath%\oracore\mesg\lpmus.msb			%despath%\oracore\mesg\lpmus.msb			> NUL
if exist %srcpath%\oracore\mesg\lrmus.msb		copy %srcpath%\oracore\mesg\lrmus.msb			%despath%\oracore\mesg\lrmus.msb			> NUL
if exist %srcpath%\oracore\mesg\lrmzhs.msb		copy %srcpath%\oracore\mesg\lrmzhs.msb			%despath%\oracore\mesg\lrmzhs.msb			> NUL
if exist %srcpath%\oracore\mesg\lsfus.msb		copy %srcpath%\oracore\mesg\lsfus.msb			%despath%\oracore\mesg\lsfus.msb			> NUL
if exist %srcpath%\oracore\mesg\ltmus.msb		copy %srcpath%\oracore\mesg\ltmus.msb			%despath%\oracore\mesg\ltmus.msb			> NUL
if exist %srcpath%\oracore\zoneinfo\timezlrg.dat	copy %srcpath%\oracore\zoneinfo\timezlrg.dat		%despath%\oracore\zoneinfo\timezlrg.dat			> NUL
if exist %srcpath%\oracore\zoneinfo\timezone.dat	copy %srcpath%\oracore\zoneinfo\timezone.dat		%despath%\oracore\zoneinfo\timezone.dat			> NUL
if exist %srcpath%\precomp\admin\ottcfg.cfg		copy %srcpath%\precomp\admin\ottcfg.cfg			%despath%\precomp\admin\ottcfg.cfg			> NUL
if exist %srcpath%\precomp\admin\pcbcfg.cfg		copy %srcpath%\precomp\admin\pcbcfg.cfg			%despath%\precomp\admin\pcbcfg.cfg			> NUL
if exist %srcpath%\precomp\admin\pcccob.cfg		copy %srcpath%\precomp\admin\pcccob.cfg			%despath%\precomp\admin\pcccob.cfg			> NUL
if exist %srcpath%\precomp\admin\pcscfg.cfg		copy %srcpath%\precomp\admin\pcscfg.cfg			%despath%\precomp\admin\pcscfg.cfg			> NUL
if exist %srcpath%\precomp\help\proc\connect.hlp	copy %srcpath%\precomp\help\proc\connect.hlp		%despath%\precomp\help\proc\connect.hlp			> NUL
if exist %srcpath%\precomp\help\proc\lsterror.hlp	copy %srcpath%\precomp\help\proc\lsterror.hlp		%despath%\precomp\help\proc\lsterror.hlp		> NUL
if exist %srcpath%\precomp\help\proc\options.hlp	copy %srcpath%\precomp\help\proc\options.hlp		%despath%\precomp\help\proc\options.hlp			> NUL
if exist %srcpath%\precomp\help\proc\zhs\connect.hlp	copy %srcpath%\precomp\help\proc\zhs\connect.hlp	%despath%\precomp\help\proc\zhs\connect.hlp		> NUL
if exist %srcpath%\precomp\help\proc\zhs\lsterror.hlp	copy %srcpath%\precomp\help\proc\zhs\lsterror.hlp	%despath%\precomp\help\proc\zhs\lsterror.hlp		> NUL
if exist %srcpath%\precomp\help\proc\zhs\options.hlp	copy %srcpath%\precomp\help\proc\zhs\options.hlp	%despath%\precomp\help\proc\zhs\options.hlp		> NUL
if exist %srcpath%\precomp\lib\msvc\oraSQL9.LIB		copy %srcpath%\precomp\lib\msvc\oraSQL9.LIB		%despath%\precomp\lib\msvc\oraSQL9.LIB			> NUL
if exist %srcpath%\precomp\lib\msvc\oraSQX9.LIB		copy %srcpath%\precomp\lib\msvc\oraSQX9.LIB		%despath%\precomp\lib\msvc\oraSQX9.LIB			> NUL
if exist %srcpath%\precomp\lib\orasql9.lib		copy %srcpath%\precomp\lib\orasql9.lib			%despath%\precomp\lib\orasql9.lib			> NUL
if exist %srcpath%\precomp\mesg\o2fus.msb		copy %srcpath%\precomp\mesg\o2fus.msb			%despath%\precomp\mesg\o2fus.msb			> NUL
if exist %srcpath%\precomp\mesg\o2fzhs.msb		copy %srcpath%\precomp\mesg\o2fzhs.msb			%despath%\precomp\mesg\o2fzhs.msb			> NUL
if exist %srcpath%\precomp\mesg\o2ius.msb		copy %srcpath%\precomp\mesg\o2ius.msb			%despath%\precomp\mesg\o2ius.msb			> NUL
if exist %srcpath%\precomp\mesg\o2izhs.msb		copy %srcpath%\precomp\mesg\o2izhs.msb			%despath%\precomp\mesg\o2izhs.msb			> NUL
if exist %srcpath%\precomp\mesg\o2uus.msb		copy %srcpath%\precomp\mesg\o2uus.msb			%despath%\precomp\mesg\o2uus.msb			> NUL
if exist %srcpath%\precomp\mesg\o2uzhs.msb		copy %srcpath%\precomp\mesg\o2uzhs.msb			%despath%\precomp\mesg\o2uzhs.msb			> NUL
if exist %srcpath%\precomp\mesg\pcbeus.msb		copy %srcpath%\precomp\mesg\pcbeus.msb			%despath%\precomp\mesg\pcbeus.msb			> NUL
if exist %srcpath%\precomp\mesg\pcbezhs.msb		copy %srcpath%\precomp\mesg\pcbezhs.msb			%despath%\precomp\mesg\pcbezhs.msb			> NUL
if exist %srcpath%\precomp\mesg\pcfus.msb		copy %srcpath%\precomp\mesg\pcfus.msb			%despath%\precomp\mesg\pcfus.msb			> NUL
if exist %srcpath%\precomp\mesg\pcfzhs.msb		copy %srcpath%\precomp\mesg\pcfzhs.msb			%despath%\precomp\mesg\pcfzhs.msb			> NUL
if exist %srcpath%\precomp\mesg\pcsus.msb		copy %srcpath%\precomp\mesg\pcsus.msb			%despath%\precomp\mesg\pcsus.msb			> NUL
if exist %srcpath%\precomp\mesg\pcszhs.msb		copy %srcpath%\precomp\mesg\pcszhs.msb			%despath%\precomp\mesg\pcszhs.msb			> NUL
if exist %srcpath%\precomp\mesg\pg2us.msb		copy %srcpath%\precomp\mesg\pg2us.msb			%despath%\precomp\mesg\pg2us.msb			> NUL
if exist %srcpath%\precomp\mesg\pg2zhs.msb		copy %srcpath%\precomp\mesg\pg2zhs.msb			%despath%\precomp\mesg\pg2zhs.msb			> NUL
if exist %srcpath%\precomp\mesg\pgous.msb		copy %srcpath%\precomp\mesg\pgous.msb			%despath%\precomp\mesg\pgous.msb			> NUL
if exist %srcpath%\precomp\mesg\pgozhs.msb		copy %srcpath%\precomp\mesg\pgozhs.msb			%despath%\precomp\mesg\pgozhs.msb			> NUL
if exist %srcpath%\precomp\mesg\ppeus.msb		copy %srcpath%\precomp\mesg\ppeus.msb			%despath%\precomp\mesg\ppeus.msb			> NUL
if exist %srcpath%\precomp\mesg\ppezhs.msb		copy %srcpath%\precomp\mesg\ppezhs.msb			%despath%\precomp\mesg\ppezhs.msb			> NUL
if exist %srcpath%\precomp\mesg\pr2us.msb		copy %srcpath%\precomp\mesg\pr2us.msb			%despath%\precomp\mesg\pr2us.msb			> NUL
if exist %srcpath%\precomp\mesg\pr2zhs.msb		copy %srcpath%\precomp\mesg\pr2zhs.msb			%despath%\precomp\mesg\pr2zhs.msb			> NUL
if exist %srcpath%\precomp\mesg\prous.msb		copy %srcpath%\precomp\mesg\prous.msb			%despath%\precomp\mesg\prous.msb			> NUL
if exist %srcpath%\precomp\mesg\prozhs.msb		copy %srcpath%\precomp\mesg\prozhs.msb			%despath%\precomp\mesg\prozhs.msb			> NUL
if exist %srcpath%\precomp\mesg\sqlus.msb		copy %srcpath%\precomp\mesg\sqlus.msb			%despath%\precomp\mesg\sqlus.msb			> NUL
if exist %srcpath%\precomp\mesg\sqlzhs.msb		copy %srcpath%\precomp\mesg\sqlzhs.msb			%despath%\precomp\mesg\sqlzhs.msb			> NUL
if exist %srcpath%\precomp\misc\proc\add_newl.bat	copy %srcpath%\precomp\misc\proc\add_newl.bat		%despath%\precomp\misc\proc\add_newl.bat		> NUL
if exist %srcpath%\precomp\misc\proc\mod_incl.bat	copy %srcpath%\precomp\misc\proc\mod_incl.bat		%despath%\precomp\misc\proc\mod_incl.bat		> NUL
if exist %srcpath%\precomp\public\bnddsc.for		copy %srcpath%\precomp\public\bnddsc.for		%despath%\precomp\public\bnddsc.for			> NUL
if exist %srcpath%\precomp\public\oraca.cob		copy %srcpath%\precomp\public\oraca.cob			%despath%\precomp\public\oraca.cob			> NUL
if exist %srcpath%\precomp\public\oraca.for		copy %srcpath%\precomp\public\oraca.for			%despath%\precomp\public\oraca.for			> NUL
if exist %srcpath%\precomp\public\oraca.h		copy %srcpath%\precomp\public\oraca.h			%despath%\precomp\public\oraca.h			> NUL
if exist %srcpath%\precomp\public\oraca5.cob		copy %srcpath%\precomp\public\oraca5.cob		%despath%\precomp\public\oraca5.cob			> NUL
if exist %srcpath%\precomp\public\seldsc.for		copy %srcpath%\precomp\public\seldsc.for		%despath%\precomp\public\seldsc.for			> NUL
if exist %srcpath%\precomp\public\sql2oci.h		copy %srcpath%\precomp\public\sql2oci.h			%despath%\precomp\public\sql2oci.h			> NUL
if exist %srcpath%\precomp\public\sqlapr.h		copy %srcpath%\precomp\public\sqlapr.h			%despath%\precomp\public\sqlapr.h			> NUL
if exist %srcpath%\precomp\public\sqlca.cob		copy %srcpath%\precomp\public\sqlca.cob			%despath%\precomp\public\sqlca.cob			> NUL
if exist %srcpath%\precomp\public\sqlca.for		copy %srcpath%\precomp\public\sqlca.for			%despath%\precomp\public\sqlca.for			> NUL
if exist %srcpath%\precomp\public\sqlca.h		copy %srcpath%\precomp\public\sqlca.h			%despath%\precomp\public\sqlca.h			> NUL
if exist %srcpath%\precomp\public\sqlca5.cob		copy %srcpath%\precomp\public\sqlca5.cob		%despath%\precomp\public\sqlca5.cob			> NUL
if exist %srcpath%\precomp\public\sqlcpr.h		copy %srcpath%\precomp\public\sqlcpr.h			%despath%\precomp\public\sqlcpr.h			> NUL
if exist %srcpath%\precomp\public\sqlda.cob		copy %srcpath%\precomp\public\sqlda.cob			%despath%\precomp\public\sqlda.cob			> NUL
if exist %srcpath%\precomp\public\sqlda.h		copy %srcpath%\precomp\public\sqlda.h			%despath%\precomp\public\sqlda.h			> NUL
if exist %srcpath%\precomp\public\sqlda5.cob		copy %srcpath%\precomp\public\sqlda5.cob		%despath%\precomp\public\sqlda5.cob			> NUL
if exist %srcpath%\precomp\public\sqlkpr.h		copy %srcpath%\precomp\public\sqlkpr.h			%despath%\precomp\public\sqlkpr.h			> NUL
if exist %srcpath%\precomp\public\sqlucs2.h		copy %srcpath%\precomp\public\sqlucs2.h			%despath%\precomp\public\sqlucs2.h			> NUL
if exist %srcpath%\RDBMS\mesg\kgpus.msb			copy %srcpath%\RDBMS\mesg\kgpus.msb			%despath%\RDBMS\mesg\kgpus.msb				> NUL
if exist %srcpath%\RDBMS\mesg\kgpzhs.msb		copy %srcpath%\RDBMS\mesg\kgpzhs.msb			%despath%\RDBMS\mesg\kgpzhs.msb				> NUL
if exist %srcpath%\RDBMS\mesg\ocius.msb			copy %srcpath%\RDBMS\mesg\ocius.msb			%despath%\RDBMS\mesg\ocius.msb				> NUL
if exist %srcpath%\RDBMS\mesg\ocizhs.msb		copy %srcpath%\RDBMS\mesg\ocizhs.msb			%despath%\RDBMS\mesg\ocizhs.msb				> NUL
if exist %srcpath%\RDBMS\mesg\oraus.msb			copy %srcpath%\RDBMS\mesg\oraus.msb			%despath%\RDBMS\mesg\oraus.msb				> NUL
if exist %srcpath%\RDBMS\mesg\orazhs.msb		copy %srcpath%\RDBMS\mesg\orazhs.msb			%despath%\RDBMS\mesg\orazhs.msb				> NUL
if exist %srcpath%\RDBMS\mesg\ulus.msb			copy %srcpath%\RDBMS\mesg\ulus.msb			%despath%\RDBMS\mesg\ulus.msb				> NUL
if exist %srcpath%\RDBMS\mesg\ulzhs.msb			copy %srcpath%\RDBMS\mesg\ulzhs.msb			%despath%\RDBMS\mesg\ulzhs.msb				> NUL
if exist %srcpath%\sqlplus\admin\glogin.sql		copy %srcpath%\sqlplus\admin\glogin.sql			%despath%\sqlplus\admin\glogin.sql			> NUL
if exist %srcpath%\sqlplus\admin\help\helpbld.sql	copy %srcpath%\sqlplus\admin\help\helpbld.sql		%despath%\sqlplus\admin\help\helpbld.sql		> NUL
if exist %srcpath%\sqlplus\admin\help\helpdrop.sql	copy %srcpath%\sqlplus\admin\help\helpdrop.sql		%despath%\sqlplus\admin\help\helpdrop.sql		> NUL
if exist %srcpath%\sqlplus\admin\help\helpus.sql	copy %srcpath%\sqlplus\admin\help\helpus.sql		%despath%\sqlplus\admin\help\helpus.sql			> NUL
if exist %srcpath%\sqlplus\admin\help\hlpbld.sql	copy %srcpath%\sqlplus\admin\help\hlpbld.sql		%despath%\sqlplus\admin\help\hlpbld.sql			> NUL
if exist %srcpath%\sqlplus\admin\plustrce.sql		copy %srcpath%\sqlplus\admin\plustrce.sql		%despath%\sqlplus\admin\plustrce.sql			> NUL
if exist %srcpath%\sqlplus\admin\pupbld.sql		copy %srcpath%\sqlplus\admin\pupbld.sql			%despath%\sqlplus\admin\pupbld.sql			> NUL
if exist %srcpath%\sqlplus\mesg\cpyus.msb		copy %srcpath%\sqlplus\mesg\cpyus.msb			%despath%\sqlplus\mesg\cpyus.msb			> NUL
if exist %srcpath%\sqlplus\mesg\cpyzhs.msb		copy %srcpath%\sqlplus\mesg\cpyzhs.msb			%despath%\sqlplus\mesg\cpyzhs.msb			> NUL
if exist %srcpath%\sqlplus\mesg\sp1us.msb		copy %srcpath%\sqlplus\mesg\sp1us.msb			%despath%\sqlplus\mesg\sp1us.msb			> NUL
if exist %srcpath%\sqlplus\mesg\sp1zhs.msb		copy %srcpath%\sqlplus\mesg\sp1zhs.msb			%despath%\sqlplus\mesg\sp1zhs.msb			> NUL
if exist %srcpath%\sqlplus\mesg\sp2us.msb		copy %srcpath%\sqlplus\mesg\sp2us.msb			%despath%\sqlplus\mesg\sp2us.msb			> NUL
if exist %srcpath%\sqlplus\mesg\sp2zhs.msb		copy %srcpath%\sqlplus\mesg\sp2zhs.msb			%despath%\sqlplus\mesg\sp2zhs.msb			> NUL
if exist %srcpath%\sqlplus\mesg\spwus.msb		copy %srcpath%\sqlplus\mesg\spwus.msb			%despath%\sqlplus\mesg\spwus.msb			> NUL
if exist %srcpath%\sqlplus\mesg\spwzhs.msb		copy %srcpath%\sqlplus\mesg\spwzhs.msb			%despath%\sqlplus\mesg\spwzhs.msb			> NUL
if exist %systemroot%\oraodbc.ini			copy %systemroot%\oraodbc.ini				%despath%						> NUL

if not exist %srcpath%\bin\oci.dll				echo not exist %srcpath%\bin\oci.dll                                        	
if not exist %srcpath%\bin\ociw32.dll				echo not exist %srcpath%\bin\ociw32.dll			
if not exist %srcpath%\bin\oracle.key				echo not exist %srcpath%\bin\oracle.key			
if not exist %srcpath%\bin\oraclient9.dll			echo not exist %srcpath%\bin\oraclient9.dll		
if not exist %srcpath%\bin\oracommon9.dll			echo not exist %srcpath%\bin\oracommon9.dll		
if not exist %srcpath%\bin\ORACORE9.DLL				echo not exist %srcpath%\bin\ORACORE9.DLL		
if not exist %srcpath%\bin\orageneric9.dll			echo not exist %srcpath%\bin\orageneric9.dll		
if not exist %srcpath%\bin\oraldapclnt9.dll			echo not exist %srcpath%\bin\oraldapclnt9.dll		
if not exist %srcpath%\bin\oran9.dll				echo not exist %srcpath%\bin\oran9.dll			
if not exist %srcpath%\bin\ORANCDS9.DLL				echo not exist %srcpath%\bin\ORANCDS9.DLL		
if not exist %srcpath%\bin\orancrypt9.dll			echo not exist %srcpath%\bin\orancrypt9.dll		
if not exist %srcpath%\bin\oranhost9.dll			echo not exist %srcpath%\bin\oranhost9.dll		
if not exist %srcpath%\bin\oranl9.dll				echo not exist %srcpath%\bin\oranl9.dll			
if not exist %srcpath%\bin\oranldap9.dll			echo not exist %srcpath%\bin\oranldap9.dll		
if not exist %srcpath%\bin\ORANLS9.DLL				echo not exist %srcpath%\bin\ORANLS9.DLL			
if not exist %srcpath%\bin\oranms.dll				echo not exist %srcpath%\bin\oranms.dll			
if not exist %srcpath%\bin\oranmsp.dll				echo not exist %srcpath%\bin\oranmsp.dll			
if not exist %srcpath%\bin\orannts9.dll				echo not exist %srcpath%\bin\orannts9.dll		
if not exist %srcpath%\bin\orannzsbb9.dll			echo not exist %srcpath%\bin\orannzsbb9.dll		
if not exist %srcpath%\bin\oranoname9.dll			echo not exist %srcpath%\bin\oranoname9.dll		
if not exist %srcpath%\bin\oranro9.dll				echo not exist %srcpath%\bin\oranro9.dll			
if not exist %srcpath%\bin\orantcp9.dll				echo not exist %srcpath%\bin\orantcp9.dll		
if not exist %srcpath%\bin\orantns9.dll				echo not exist %srcpath%\bin\orantns9.dll		
if not exist %srcpath%\bin\oraocci9.dll				echo not exist %srcpath%\bin\oraocci9.dll		
if not exist %srcpath%\bin\OraOLEDB.dll				echo not exist %srcpath%\bin\OraOLEDB.dll		
if not exist %srcpath%\bin\OraOLEDB.tlb				echo not exist %srcpath%\bin\OraOLEDB.tlb		
if not exist %srcpath%\bin\ORAPLS9.DLL				echo not exist %srcpath%\bin\ORAPLS9.DLL			
if not exist %srcpath%\bin\ORASLAX9.DLL				echo not exist %srcpath%\bin\ORASLAX9.DLL		
if not exist %srcpath%\bin\ORASNLS9.DLL				echo not exist %srcpath%\bin\ORASNLS9.DLL		
if not exist %srcpath%\bin\OraSQL.exe				echo not exist %srcpath%\bin\OraSQL.exe			
if not exist %srcpath%\bin\ORASQL9.DLL				echo not exist %srcpath%\bin\ORASQL9.DLL			
if not exist %srcpath%\bin\oratrace9.dll			echo not exist %srcpath%\bin\oratrace9.dll		
if not exist %srcpath%\bin\ORAUNLS9.DLL				echo not exist %srcpath%\bin\ORAUNLS9.DLL		
if not exist %srcpath%\bin\oravsn9.dll				echo not exist %srcpath%\bin\oravsn9.dll			
if not exist %srcpath%\bin\orawtc9.dll				echo not exist %srcpath%\bin\orawtc9.dll			
if not exist %srcpath%\bin\ott.exe				echo not exist %srcpath%\bin\ott.exe			
if not exist %srcpath%\bin\ott8.exe				echo not exist %srcpath%\bin\ott8.exe			
if not exist %srcpath%\bin\proc.exe				echo not exist %srcpath%\bin\proc.exe			
if not exist %srcpath%\bin\procd9.dll				echo not exist %srcpath%\bin\procd9.dll			
if not exist %srcpath%\bin\proce9.dll				echo not exist %srcpath%\bin\proce9.dll			
if not exist %srcpath%\bin\procf9.dll				echo not exist %srcpath%\bin\procf9.dll			
if not exist %srcpath%\bin\proci9.dll				echo not exist %srcpath%\bin\proci9.dll			
if not exist %srcpath%\bin\procja9.dll				echo not exist %srcpath%\bin\procja9.dll			
if not exist %srcpath%\bin\procko9.dll				echo not exist %srcpath%\bin\procko9.dll			
if not exist %srcpath%\bin\procob.exe				echo not exist %srcpath%\bin\procob.exe			
if not exist %srcpath%\bin\procob18.exe				echo not exist %srcpath%\bin\procob18.exe		
if not exist %srcpath%\bin\procptb9.dll				echo not exist %srcpath%\bin\procptb9.dll		
if not exist %srcpath%\bin\procui.exe				echo not exist %srcpath%\bin\procui.exe			
if not exist %srcpath%\bin\procus9.dll				echo not exist %srcpath%\bin\procus9.dll			
if not exist %srcpath%\bin\proczhs9.dll				echo not exist %srcpath%\bin\proczhs9.dll		
if not exist %srcpath%\bin\sqlplus.exe				echo not exist %srcpath%\bin\sqlplus.exe			
if not exist %srcpath%\bin\sqlplusw.exe				echo not exist %srcpath%\bin\sqlplusw.exe		
if not exist %srcpath%\bin\sqora32.dll				echo not exist %srcpath%\bin\sqora32.dll			
if not exist %srcpath%\bin\sqoras32.dll				echo not exist %srcpath%\bin\sqoras32.dll		
if not exist %srcpath%\bin\sqresus.dll				echo not exist %srcpath%\bin\sqresus.dll			
if not exist %srcpath%\bin\TNSConf.exe				echo not exist %srcpath%\bin\TNSConf.exe			
if not exist %srcpath%\bin\TNSPING.EXE				echo not exist %srcpath%\bin\TNSPING.EXE			
if not exist %srcpath%\network\ADMIN\tnsnames.ora		echo not exist %srcpath%\network\ADMIN\tnsnames.ora	
if not exist %srcpath%\network\mesg\ncrus.msb			echo not exist %srcpath%\network\mesg\ncrus.msb		
if not exist %srcpath%\network\mesg\ncrzhs.msb			echo not exist %srcpath%\network\mesg\ncrzhs.msb		
if not exist %srcpath%\network\mesg\ncxus.msb			echo not exist %srcpath%\network\mesg\ncxus.msb		
if not exist %srcpath%\network\mesg\ncxzhs.msb			echo not exist %srcpath%\network\mesg\ncxzhs.msb		
if not exist %srcpath%\network\mesg\niqus.msb			echo not exist %srcpath%\network\mesg\niqus.msb		
if not exist %srcpath%\network\mesg\niqzhs.msb			echo not exist %srcpath%\network\mesg\niqzhs.msb		
if not exist %srcpath%\network\mesg\nltus.msb			echo not exist %srcpath%\network\mesg\nltus.msb		
if not exist %srcpath%\network\mesg\nlus.msb			echo not exist %srcpath%\network\mesg\nlus.msb		
if not exist %srcpath%\network\mesg\nlzhs.msb			echo not exist %srcpath%\network\mesg\nlzhs.msb		
if not exist %srcpath%\network\mesg\nmpus.msb			echo not exist %srcpath%\network\mesg\nmpus.msb		
if not exist %srcpath%\network\mesg\nmpzhs.msb			echo not exist %srcpath%\network\mesg\nmpzhs.msb		
if not exist %srcpath%\network\mesg\nmrus.msb			echo not exist %srcpath%\network\mesg\nmrus.msb		
if not exist %srcpath%\network\mesg\nncus.msb			echo not exist %srcpath%\network\mesg\nncus.msb		
if not exist %srcpath%\network\mesg\nnczhs.msb			echo not exist %srcpath%\network\mesg\nnczhs.msb		
if not exist %srcpath%\network\mesg\nnfus.msb			echo not exist %srcpath%\network\mesg\nnfus.msb		
if not exist %srcpath%\network\mesg\nnfzhs.msb			echo not exist %srcpath%\network\mesg\nnfzhs.msb		
if not exist %srcpath%\network\mesg\nnlus.msb			echo not exist %srcpath%\network\mesg\nnlus.msb		
if not exist %srcpath%\network\mesg\nnlzhs.msb			echo not exist %srcpath%\network\mesg\nnlzhs.msb		
if not exist %srcpath%\network\mesg\nnous.msb			echo not exist %srcpath%\network\mesg\nnous.msb		
if not exist %srcpath%\network\mesg\nnozhs.msb			echo not exist %srcpath%\network\mesg\nnozhs.msb		
if not exist %srcpath%\network\mesg\nplus.msb			echo not exist %srcpath%\network\mesg\nplus.msb		
if not exist %srcpath%\network\mesg\nplzhs.msb			echo not exist %srcpath%\network\mesg\nplzhs.msb		
if not exist %srcpath%\network\mesg\nzus.msb			echo not exist %srcpath%\network\mesg\nzus.msb		
if not exist %srcpath%\network\mesg\nzzhs.msb			echo not exist %srcpath%\network\mesg\nzzhs.msb		
if not exist %srcpath%\network\mesg\snlus.msb			echo not exist %srcpath%\network\mesg\snlus.msb		
if not exist %srcpath%\network\mesg\snlzhs.msb			echo not exist %srcpath%\network\mesg\snlzhs.msb		
if not exist %srcpath%\network\mesg\tnlus.msb			echo not exist %srcpath%\network\mesg\tnlus.msb		
if not exist %srcpath%\network\mesg\tnlzhs.msb			echo not exist %srcpath%\network\mesg\tnlzhs.msb		
if not exist %srcpath%\network\mesg\tnplus.msb			echo not exist %srcpath%\network\mesg\tnplus.msb		
if not exist %srcpath%\network\mesg\tnplzhs.msb			echo not exist %srcpath%\network\mesg\tnplzhs.msb	
if not exist %srcpath%\network\mesg\tnsus.msb			echo not exist %srcpath%\network\mesg\tnsus.msb		
if not exist %srcpath%\network\mesg\tnszhs.msb			echo not exist %srcpath%\network\mesg\tnszhs.msb		
if not exist %srcpath%\oci\include\cdemodp0.h			echo not exist %srcpath%\oci\include\cdemodp0.h		
if not exist %srcpath%\oci\include\kusapi.h			echo not exist %srcpath%\oci\include\kusapi.h		
if not exist %srcpath%\oci\include\kustags.h			echo not exist %srcpath%\oci\include\kustags.h		
if not exist %srcpath%\oci\include\nzerror.h			echo not exist %srcpath%\oci\include\nzerror.h		
if not exist %srcpath%\oci\include\nzt.h			echo not exist %srcpath%\oci\include\nzt.h		
if not exist %srcpath%\oci\include\occi.h			echo not exist %srcpath%\oci\include\occi.h		
if not exist %srcpath%\oci\include\occiCommon.h			echo not exist %srcpath%\oci\include\occiCommon.h	
if not exist %srcpath%\oci\include\occiControl.h		echo not exist %srcpath%\oci\include\occiControl.h	
if not exist %srcpath%\oci\include\occiData.h			echo not exist %srcpath%\oci\include\occiData.h		
if not exist %srcpath%\oci\include\occiObjects.h		echo not exist %srcpath%\oci\include\occiObjects.h	
if not exist %srcpath%\oci\include\oci.h			echo not exist %srcpath%\oci\include\oci.h		
if not exist %srcpath%\oci\include\oci1.h			echo not exist %srcpath%\oci\include\oci1.h		
if not exist %srcpath%\oci\include\oci8dp.h			echo not exist %srcpath%\oci\include\oci8dp.h		
if not exist %srcpath%\oci\include\ociap.h			echo not exist %srcpath%\oci\include\ociap.h		
if not exist %srcpath%\oci\include\ociapr.h			echo not exist %srcpath%\oci\include\ociapr.h		
if not exist %srcpath%\oci\include\ocidef.h			echo not exist %srcpath%\oci\include\ocidef.h		
if not exist %srcpath%\oci\include\ocidem.h			echo not exist %srcpath%\oci\include\ocidem.h		
if not exist %srcpath%\oci\include\ocidfn.h			echo not exist %srcpath%\oci\include\ocidfn.h		
if not exist %srcpath%\oci\include\ociextp.h			echo not exist %srcpath%\oci\include\ociextp.h		
if not exist %srcpath%\oci\include\ocikp.h			echo not exist %srcpath%\oci\include\ocikp.h		
if not exist %srcpath%\oci\include\ocikpr.h			echo not exist %srcpath%\oci\include\ocikpr.h		
if not exist %srcpath%\oci\include\ocixad.h			echo not exist %srcpath%\oci\include\ocixad.h		
if not exist %srcpath%\oci\include\odci.h			echo not exist %srcpath%\oci\include\odci.h		
if not exist %srcpath%\oci\include\oratypes.h			echo not exist %srcpath%\oci\include\oratypes.h		
if not exist %srcpath%\oci\include\ori.h			echo not exist %srcpath%\oci\include\ori.h		
if not exist %srcpath%\oci\include\orid.h			echo not exist %srcpath%\oci\include\orid.h		
if not exist %srcpath%\oci\include\orl.h			echo not exist %srcpath%\oci\include\orl.h		
if not exist %srcpath%\oci\include\oro.h			echo not exist %srcpath%\oci\include\oro.h		
if not exist %srcpath%\oci\include\ort.h			echo not exist %srcpath%\oci\include\ort.h		
if not exist %srcpath%\oci\lib\oci.lib				echo not exist %srcpath%\oci\lib\oci.lib			
if not exist %srcpath%\oci\lib\ociw32.lib			echo not exist %srcpath%\oci\lib\ociw32.lib		
if not exist %srcpath%\oci\lib\oraocci9.lib			echo not exist %srcpath%\oci\lib\oraocci9.lib		
if not exist %srcpath%\ocommon\nls\admin\data\LX00001.NLB	echo not exist %srcpath%\ocommon\nls\admin\data\LX00001.NLB
if not exist %srcpath%\ocommon\nls\admin\data\LX00023.NLB	echo not exist %srcpath%\ocommon\nls\admin\data\LX00023.NLB
if not exist %srcpath%\ocommon\nls\admin\data\LX10001.NLB	echo not exist %srcpath%\ocommon\nls\admin\data\LX10001.NLB
if not exist %srcpath%\ocommon\nls\admin\data\LX10035.NLB	echo not exist %srcpath%\ocommon\nls\admin\data\LX10035.NLB
if not exist %srcpath%\ocommon\nls\admin\data\LX1BOOT.NLB	echo not exist %srcpath%\ocommon\nls\admin\data\LX1BOOT.NLB
if not exist %srcpath%\ocommon\nls\admin\data\LX20001.NLB	echo not exist %srcpath%\ocommon\nls\admin\data\LX20001.NLB
if not exist %srcpath%\ocommon\nls\admin\data\LX20354.NLB	echo not exist %srcpath%\ocommon\nls\admin\data\LX20354.NLB
if not exist %srcpath%\ocommon\nls\admin\data\LX60354.NLB 	echo not exist %srcpath%\ocommon\nls\admin\data\LX60354.NLB
if not exist %srcpath%\ocommon\nls\mesg\lxeus.msb		echo not exist %srcpath%\ocommon\nls\mesg\lxeus.msb	
if not exist %srcpath%\ocommon\nls\mesg\lxius.msb		echo not exist %srcpath%\ocommon\nls\mesg\lxius.msb	
if not exist %srcpath%\oledb\doc\oledb.pdf			echo not exist %srcpath%\oledb\doc\oledb.pdf		
if not exist %srcpath%\oledb\doc\readme.txt			echo not exist %srcpath%\oledb\doc\readme.txt		
if not exist %srcpath%\oledb\include\OraOLEDB.h			echo not exist %srcpath%\oledb\include\OraOLEDB.h		
if not exist %srcpath%\oledb\lib\OraOLEDB.lib			echo not exist %srcpath%\oledb\lib\OraOLEDB.lib		
if not exist %srcpath%\oledb\mesg\oraoledbus.msb		echo not exist %srcpath%\oledb\mesg\oraoledbus.msb	
if not exist %srcpath%\oledb\mesg\oraoledbzhs.msb		echo not exist %srcpath%\oledb\mesg\oraoledbzhs.msb	
if not exist %srcpath%\oracore\mesg\lemus.msb			echo not exist %srcpath%\oracore\mesg\lemus.msb		
if not exist %srcpath%\oracore\mesg\lfius.msb			echo not exist %srcpath%\oracore\mesg\lfius.msb		
if not exist %srcpath%\oracore\mesg\lfizhs.msb			echo not exist %srcpath%\oracore\mesg\lfizhs.msb		
if not exist %srcpath%\oracore\mesg\lhtus.msb			echo not exist %srcpath%\oracore\mesg\lhtus.msb		
if not exist %srcpath%\oracore\mesg\lmmus.msb			echo not exist %srcpath%\oracore\mesg\lmmus.msb		
if not exist %srcpath%\oracore\mesg\lpmus.msb			echo not exist %srcpath%\oracore\mesg\lpmus.msb		
if not exist %srcpath%\oracore\mesg\lrmus.msb			echo not exist %srcpath%\oracore\mesg\lrmus.msb		
if not exist %srcpath%\oracore\mesg\lrmzhs.msb			echo not exist %srcpath%\oracore\mesg\lrmzhs.msb		
if not exist %srcpath%\oracore\mesg\lsfus.msb			echo not exist %srcpath%\oracore\mesg\lsfus.msb		
if not exist %srcpath%\oracore\mesg\ltmus.msb			echo not exist %srcpath%\oracore\mesg\ltmus.msb		
if not exist %srcpath%\oracore\zoneinfo\timezlrg.dat		echo not exist %srcpath%\oracore\zoneinfo\timezlrg.dat	
if not exist %srcpath%\oracore\zoneinfo\timezone.dat		echo not exist %srcpath%\oracore\zoneinfo\timezone.dat	
if not exist %srcpath%\precomp\admin\ottcfg.cfg			echo not exist %srcpath%\precomp\admin\ottcfg.cfg		
if not exist %srcpath%\precomp\admin\pcbcfg.cfg			echo not exist %srcpath%\precomp\admin\pcbcfg.cfg		
if not exist %srcpath%\precomp\admin\pcccob.cfg			echo not exist %srcpath%\precomp\admin\pcccob.cfg		
if not exist %srcpath%\precomp\admin\pcscfg.cfg			echo not exist %srcpath%\precomp\admin\pcscfg.cfg		
if not exist %srcpath%\precomp\help\proc\connect.hlp		echo not exist %srcpath%\precomp\help\proc\connect.hlp	
if not exist %srcpath%\precomp\help\proc\lsterror.hlp		echo not exist %srcpath%\precomp\help\proc\lsterror.hlp	
if not exist %srcpath%\precomp\help\proc\options.hlp		echo not exist %srcpath%\precomp\help\proc\options.hlp	
if not exist %srcpath%\precomp\help\proc\zhs\connect.hlp	echo not exist %srcpath%\precomp\help\proc\zhs\connect.hlp
if not exist %srcpath%\precomp\help\proc\zhs\lsterror.hlp 	echo not exist %srcpath%\precomp\help\proc\zhs\lsterror.hlp
if not exist %srcpath%\precomp\help\proc\zhs\options.hlp	echo not exist %srcpath%\precomp\help\proc\zhs\options.hlp
if not exist %srcpath%\precomp\lib\msvc\oraSQL9.LIB		echo not exist %srcpath%\precomp\lib\msvc\oraSQL9.LIB	
if not exist %srcpath%\precomp\lib\msvc\oraSQX9.LIB		echo not exist %srcpath%\precomp\lib\msvc\oraSQX9.LIB	
if not exist %srcpath%\precomp\lib\orasql9.lib			echo not exist %srcpath%\precomp\lib\orasql9.lib		
if not exist %srcpath%\precomp\mesg\o2fus.msb			echo not exist %srcpath%\precomp\mesg\o2fus.msb		
if not exist %srcpath%\precomp\mesg\o2fzhs.msb			echo not exist %srcpath%\precomp\mesg\o2fzhs.msb		
if not exist %srcpath%\precomp\mesg\o2ius.msb			echo not exist %srcpath%\precomp\mesg\o2ius.msb		
if not exist %srcpath%\precomp\mesg\o2izhs.msb			echo not exist %srcpath%\precomp\mesg\o2izhs.msb		
if not exist %srcpath%\precomp\mesg\o2uus.msb			echo not exist %srcpath%\precomp\mesg\o2uus.msb		
if not exist %srcpath%\precomp\mesg\o2uzhs.msb			echo not exist %srcpath%\precomp\mesg\o2uzhs.msb		
if not exist %srcpath%\precomp\mesg\pcbeus.msb			echo not exist %srcpath%\precomp\mesg\pcbeus.msb		
if not exist %srcpath%\precomp\mesg\pcbezhs.msb			echo not exist %srcpath%\precomp\mesg\pcbezhs.msb		
if not exist %srcpath%\precomp\mesg\pcfus.msb			echo not exist %srcpath%\precomp\mesg\pcfus.msb		
if not exist %srcpath%\precomp\mesg\pcfzhs.msb			echo not exist %srcpath%\precomp\mesg\pcfzhs.msb		
if not exist %srcpath%\precomp\mesg\pcsus.msb			echo not exist %srcpath%\precomp\mesg\pcsus.msb		
if not exist %srcpath%\precomp\mesg\pcszhs.msb			echo not exist %srcpath%\precomp\mesg\pcszhs.msb		
if not exist %srcpath%\precomp\mesg\pg2us.msb			echo not exist %srcpath%\precomp\mesg\pg2us.msb		
if not exist %srcpath%\precomp\mesg\pg2zhs.msb			echo not exist %srcpath%\precomp\mesg\pg2zhs.msb		
if not exist %srcpath%\precomp\mesg\pgous.msb			echo not exist %srcpath%\precomp\mesg\pgous.msb		
if not exist %srcpath%\precomp\mesg\pgozhs.msb			echo not exist %srcpath%\precomp\mesg\pgozhs.msb		
if not exist %srcpath%\precomp\mesg\ppeus.msb			echo not exist %srcpath%\precomp\mesg\ppeus.msb		
if not exist %srcpath%\precomp\mesg\ppezhs.msb			echo not exist %srcpath%\precomp\mesg\ppezhs.msb		
if not exist %srcpath%\precomp\mesg\pr2us.msb			echo not exist %srcpath%\precomp\mesg\pr2us.msb		
if not exist %srcpath%\precomp\mesg\pr2zhs.msb			echo not exist %srcpath%\precomp\mesg\pr2zhs.msb		
if not exist %srcpath%\precomp\mesg\prous.msb			echo not exist %srcpath%\precomp\mesg\prous.msb		
if not exist %srcpath%\precomp\mesg\prozhs.msb			echo not exist %srcpath%\precomp\mesg\prozhs.msb		
if not exist %srcpath%\precomp\mesg\sqlus.msb			echo not exist %srcpath%\precomp\mesg\sqlus.msb		
if not exist %srcpath%\precomp\mesg\sqlzhs.msb			echo not exist %srcpath%\precomp\mesg\sqlzhs.msb		
if not exist %srcpath%\precomp\misc\proc\add_newl.bat		echo not exist %srcpath%\precomp\misc\proc\add_newl.bat	
if not exist %srcpath%\precomp\misc\proc\mod_incl.bat		echo not exist %srcpath%\precomp\misc\proc\mod_incl.bat	
if not exist %srcpath%\precomp\public\bnddsc.for		echo not exist %srcpath%\precomp\public\bnddsc.for	
if not exist %srcpath%\precomp\public\oraca.cob			echo not exist %srcpath%\precomp\public\oraca.cob		
if not exist %srcpath%\precomp\public\oraca.for			echo not exist %srcpath%\precomp\public\oraca.for		
if not exist %srcpath%\precomp\public\oraca.h			echo not exist %srcpath%\precomp\public\oraca.h		
if not exist %srcpath%\precomp\public\oraca5.cob		echo not exist %srcpath%\precomp\public\oraca5.cob	
if not exist %srcpath%\precomp\public\seldsc.for		echo not exist %srcpath%\precomp\public\seldsc.for	
if not exist %srcpath%\precomp\public\sql2oci.h			echo not exist %srcpath%\precomp\public\sql2oci.h		
if not exist %srcpath%\precomp\public\sqlapr.h			echo not exist %srcpath%\precomp\public\sqlapr.h		
if not exist %srcpath%\precomp\public\sqlca.cob			echo not exist %srcpath%\precomp\public\sqlca.cob		
if not exist %srcpath%\precomp\public\sqlca.for			echo not exist %srcpath%\precomp\public\sqlca.for		
if not exist %srcpath%\precomp\public\sqlca.h			echo not exist %srcpath%\precomp\public\sqlca.h		
if not exist %srcpath%\precomp\public\sqlca5.cob		echo not exist %srcpath%\precomp\public\sqlca5.cob	
if not exist %srcpath%\precomp\public\sqlcpr.h			echo not exist %srcpath%\precomp\public\sqlcpr.h		
if not exist %srcpath%\precomp\public\sqlda.cob			echo not exist %srcpath%\precomp\public\sqlda.cob		
if not exist %srcpath%\precomp\public\sqlda.h			echo not exist %srcpath%\precomp\public\sqlda.h		
if not exist %srcpath%\precomp\public\sqlda5.cob		echo not exist %srcpath%\precomp\public\sqlda5.cob	
if not exist %srcpath%\precomp\public\sqlkpr.h			echo not exist %srcpath%\precomp\public\sqlkpr.h		
if not exist %srcpath%\precomp\public\sqlucs2.h			echo not exist %srcpath%\precomp\public\sqlucs2.h		
if not exist %srcpath%\RDBMS\mesg\kgpus.msb			echo not exist %srcpath%\RDBMS\mesg\kgpus.msb		
if not exist %srcpath%\RDBMS\mesg\kgpzhs.msb			echo not exist %srcpath%\RDBMS\mesg\kgpzhs.msb		
if not exist %srcpath%\RDBMS\mesg\ocius.msb			echo not exist %srcpath%\RDBMS\mesg\ocius.msb		
if not exist %srcpath%\RDBMS\mesg\ocizhs.msb			echo not exist %srcpath%\RDBMS\mesg\ocizhs.msb		
if not exist %srcpath%\RDBMS\mesg\oraus.msb			echo not exist %srcpath%\RDBMS\mesg\oraus.msb		
if not exist %srcpath%\RDBMS\mesg\orazhs.msb			echo not exist %srcpath%\RDBMS\mesg\orazhs.msb		
if not exist %srcpath%\RDBMS\mesg\ulus.msb			echo not exist %srcpath%\RDBMS\mesg\ulus.msb		
if not exist %srcpath%\RDBMS\mesg\ulzhs.msb			echo not exist %srcpath%\RDBMS\mesg\ulzhs.msb		
if not exist %srcpath%\sqlplus\admin\glogin.sql			echo not exist %srcpath%\sqlplus\admin\glogin.sql		
if not exist %srcpath%\sqlplus\admin\help\helpbld.sql		echo not exist %srcpath%\sqlplus\admin\help\helpbld.sql	
if not exist %srcpath%\sqlplus\admin\help\helpdrop.sql		echo not exist %srcpath%\sqlplus\admin\help\helpdrop.sql	
if not exist %srcpath%\sqlplus\admin\help\helpus.sql		echo not exist %srcpath%\sqlplus\admin\help\helpus.sql	
if not exist %srcpath%\sqlplus\admin\help\hlpbld.sql		echo not exist %srcpath%\sqlplus\admin\help\hlpbld.sql	
if not exist %srcpath%\sqlplus\admin\plustrce.sql		echo not exist %srcpath%\sqlplus\admin\plustrce.sql	
if not exist %srcpath%\sqlplus\admin\pupbld.sql			echo not exist %srcpath%\sqlplus\admin\pupbld.sql		
if not exist %srcpath%\sqlplus\mesg\cpyus.msb			echo not exist %srcpath%\sqlplus\mesg\cpyus.msb		
if not exist %srcpath%\sqlplus\mesg\cpyzhs.msb			echo not exist %srcpath%\sqlplus\mesg\cpyzhs.msb		
if not exist %srcpath%\sqlplus\mesg\sp1us.msb			echo not exist %srcpath%\sqlplus\mesg\sp1us.msb		
if not exist %srcpath%\sqlplus\mesg\sp1zhs.msb			echo not exist %srcpath%\sqlplus\mesg\sp1zhs.msb		
if not exist %srcpath%\sqlplus\mesg\sp2us.msb			echo not exist %srcpath%\sqlplus\mesg\sp2us.msb		
if not exist %srcpath%\sqlplus\mesg\sp2zhs.msb			echo not exist %srcpath%\sqlplus\mesg\sp2zhs.msb		
if not exist %srcpath%\sqlplus\mesg\spwus.msb			echo not exist %srcpath%\sqlplus\mesg\spwus.msb		
if not exist %srcpath%\sqlplus\mesg\spwzhs.msb			echo not exist %srcpath%\sqlplus\mesg\spwzhs.msb		
if not exist %systemroot%\oraodbc.ini				echo not exist %systemroot%\oraodbc.ini			
								

set srcpath=
set despath=

goto end

:usage
echo usage: orcl9_cp srcpath

:end