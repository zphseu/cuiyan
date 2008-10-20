@echo off
if "z%1"=="z" goto usage

set srcpath=%1
set despath=.\ora81

md %despath%
md %despath%\bin
md %despath%\network
md %despath%\network\ADMIN
md %despath%\network\mesg
md %despath%\oci
md %despath%\oci\include
md %despath%\oci\lib
md %despath%\oci\lib\bc
md %despath%\oci\lib\msvc
md %despath%\ocommon
md %despath%\ocommon\nls
md %despath%\ocommon\nls\admin
md %despath%\ocommon\nls\admin\data
md %despath%\oledb
md %despath%\oledb\doc
md %despath%\oledb\include
md %despath%\oledb\lib
md %despath%\oledb\mesg
md %despath%\oracore
md %despath%\oracore\mesg
md %despath%\precomp
md %despath%\precomp\admin
md %despath%\precomp\doc
md %despath%\precomp\doc\ott
md %despath%\precomp\mesg
md %despath%\precomp\public
md %despath%\RDBMS
md %despath%\RDBMS\mesg
md %despath%\sqlplus
md %despath%\sqlplus\admin
md %despath%\sqlplus\admin\help
md %despath%\sqlplus\mesg

copy %srcpath%\bin\EXP.EXE                        %srcpath%\bin\EXP.EXE                        > NUL                        
copy %srcpath%\bin\IMP.EXE			  %srcpath%\bin\IMP.EXE                        > NUL
copy %srcpath%\bin\mmdx32.ocx			  %srcpath%\bin\mmdx32.ocx                     > NUL
copy %srcpath%\bin\mmtx32.ocx			  %srcpath%\bin\mmtx32.ocx                     > NUL
copy %srcpath%\bin\oci.dll			  %srcpath%\bin\oci.dll                        > NUL
copy %srcpath%\bin\ociw32.dll			  %srcpath%\bin\ociw32.dll                     > NUL
copy %srcpath%\bin\oip8.dll			  %srcpath%\bin\oip8.dll                       > NUL
copy %srcpath%\bin\oip8.tlb			  %srcpath%\bin\oip8.tlb                       > NUL
copy %srcpath%\bin\oracle.key			  %srcpath%\bin\oracle.key                     > NUL
copy %srcpath%\bin\oraclient8.dll		  %srcpath%\bin\oraclient8.dll                 > NUL
copy %srcpath%\bin\oracommon8.dll		  %srcpath%\bin\oracommon8.dll                 > NUL
copy %srcpath%\bin\oracore8.dll			  %srcpath%\bin\oracore8.dll                   > NUL
copy %srcpath%\bin\orageneric8.dll		  %srcpath%\bin\orageneric8.dll                > NUL
copy %srcpath%\bin\oraldapclnt8.dll		  %srcpath%\bin\oraldapclnt8.dll               > NUL
copy %srcpath%\bin\oran8.dll			  %srcpath%\bin\oran8.dll                      > NUL
copy %srcpath%\bin\ORANCDS8.DLL			  %srcpath%\bin\ORANCDS8.DLL                   > NUL
copy %srcpath%\bin\orancrypt8.dll		  %srcpath%\bin\orancrypt8.dll                 > NUL
copy %srcpath%\bin\oranhost8.dll		  %srcpath%\bin\oranhost8.dll                  > NUL
copy %srcpath%\bin\ORANK58.DLL			  %srcpath%\bin\ORANK58.DLL                    > NUL
copy %srcpath%\bin\oranl8.dll			  %srcpath%\bin\oranl8.dll                     > NUL
copy %srcpath%\bin\oranldap8.dll		  %srcpath%\bin\oranldap8.dll                  > NUL
copy %srcpath%\bin\ORANLS8.DLL			  %srcpath%\bin\ORANLS8.DLL                    > NUL
copy %srcpath%\bin\oranms.dll			  %srcpath%\bin\oranms.dll                     > NUL
copy %srcpath%\bin\oranmsp.dll			  %srcpath%\bin\oranmsp.dll                    > NUL
copy %srcpath%\bin\orannds8.dll			  %srcpath%\bin\orannds8.dll                   > NUL
copy %srcpath%\bin\orannss8.dll			  %srcpath%\bin\orannss8.dll                   > NUL
copy %srcpath%\bin\orannts8.dll			  %srcpath%\bin\orannts8.dll                   > NUL
copy %srcpath%\bin\orannzsbb8.dll		  %srcpath%\bin\orannzsbb8.dll                 > NUL
copy %srcpath%\bin\oranoname8.dll		  %srcpath%\bin\oranoname8.dll                 > NUL
copy %srcpath%\bin\ORANRAD8.DLL			  %srcpath%\bin\ORANRAD8.DLL                   > NUL
copy %srcpath%\bin\oranro8.dll			  %srcpath%\bin\oranro8.dll                    > NUL
copy %srcpath%\bin\ORANSID8.DLL			  %srcpath%\bin\ORANSID8.DLL                   > NUL
copy %srcpath%\bin\orantcp8.dll			  %srcpath%\bin\orantcp8.dll                   > NUL
copy %srcpath%\bin\orantns8.dll			  %srcpath%\bin\orantns8.dll                   > NUL
copy %srcpath%\bin\OraOLEDB.dll			  %srcpath%\bin\OraOLEDB.dll                   > NUL
copy %srcpath%\bin\OraOLEDB.tlb			  %srcpath%\bin\OraOLEDB.tlb                   > NUL
copy %srcpath%\bin\ORAPLS8.DLL			  %srcpath%\bin\ORAPLS8.DLL                    > NUL
copy %srcpath%\bin\Oraslax8.dll			  %srcpath%\bin\Oraslax8.dll                   > NUL
copy %srcpath%\bin\ORASQL8.DLL			  %srcpath%\bin\ORASQL8.DLL                    > NUL
copy %srcpath%\bin\oratrace8.dll		  %srcpath%\bin\oratrace8.dll                  > NUL
copy %srcpath%\bin\oravsn8.dll			  %srcpath%\bin\oravsn8.dll                    > NUL
copy %srcpath%\bin\orawtc8.dll			  %srcpath%\bin\orawtc8.dll                    > NUL
copy %srcpath%\bin\ott.exe			  %srcpath%\bin\ott.exe                        > NUL
copy %srcpath%\bin\proc.exe			  %srcpath%\bin\proc.exe                       > NUL
copy %srcpath%\bin\procob18.exe			  %srcpath%\bin\procob18.exe                   > NUL
copy %srcpath%\bin\procui.exe			  %srcpath%\bin\procui.exe                     > NUL
copy %srcpath%\bin\SQLPLUS.EXE			  %srcpath%\bin\SQLPLUS.EXE                    > NUL
copy %srcpath%\bin\SQLPLUSW.EXE			  %srcpath%\bin\SQLPLUSW.EXE                   > NUL
copy %srcpath%\bin\sqora32.dll			  %srcpath%\bin\sqora32.dll                    > NUL
copy %srcpath%\bin\sqoras32.dll			  %srcpath%\bin\sqoras32.dll                   > NUL
copy %srcpath%\bin\sqresus.dll			  %srcpath%\bin\sqresus.dll                    > NUL
copy %srcpath%\bin\TNSPING.EXE			  %srcpath%\bin\TNSPING.EXE                    > NUL
copy %srcpath%\network\admin\tnsnames.ora	  %srcpath%\network\admin\tnsnames.ora         > NUL
copy %srcpath%\network\mesg\naukus.msb		  %srcpath%\network\mesg\naukus.msb            > NUL
copy %srcpath%\network\mesg\naukus.msg		  %srcpath%\network\mesg\naukus.msg            > NUL
copy %srcpath%\network\mesg\ncrus.msb		  %srcpath%\network\mesg\ncrus.msb             > NUL
copy %srcpath%\network\mesg\ncrzhs.msb		  %srcpath%\network\mesg\ncrzhs.msb            > NUL
copy %srcpath%\network\mesg\ncxus.msb		  %srcpath%\network\mesg\ncxus.msb             > NUL
copy %srcpath%\network\mesg\ncxzhs.msb		  %srcpath%\network\mesg\ncxzhs.msb            > NUL
copy %srcpath%\network\mesg\niqus.msb		  %srcpath%\network\mesg\niqus.msb             > NUL
copy %srcpath%\network\mesg\niqzhs.msb		  %srcpath%\network\mesg\niqzhs.msb            > NUL
copy %srcpath%\network\mesg\nltus.msb		  %srcpath%\network\mesg\nltus.msb             > NUL
copy %srcpath%\network\mesg\nlus.msb		  %srcpath%\network\mesg\nlus.msb              > NUL
copy %srcpath%\network\mesg\nlzhs.msb		  %srcpath%\network\mesg\nlzhs.msb             > NUL
copy %srcpath%\network\mesg\nmpus.msb		  %srcpath%\network\mesg\nmpus.msb             > NUL
copy %srcpath%\network\mesg\nmpzhs.msb		  %srcpath%\network\mesg\nmpzhs.msb            > NUL
copy %srcpath%\network\mesg\nmrus.msb		  %srcpath%\network\mesg\nmrus.msb             > NUL
copy %srcpath%\network\mesg\nncus.msb		  %srcpath%\network\mesg\nncus.msb             > NUL
copy %srcpath%\network\mesg\nnczhs.msb		  %srcpath%\network\mesg\nnczhs.msb            > NUL
copy %srcpath%\network\mesg\nnfus.msb		  %srcpath%\network\mesg\nnfus.msb             > NUL
copy %srcpath%\network\mesg\nnfzhs.msb		  %srcpath%\network\mesg\nnfzhs.msb            > NUL
copy %srcpath%\network\mesg\nnlus.msb		  %srcpath%\network\mesg\nnlus.msb             > NUL
copy %srcpath%\network\mesg\nnlzhs.msb		  %srcpath%\network\mesg\nnlzhs.msb            > NUL
copy %srcpath%\network\mesg\nnous.msb		  %srcpath%\network\mesg\nnous.msb             > NUL
copy %srcpath%\network\mesg\nnozhs.msb		  %srcpath%\network\mesg\nnozhs.msb            > NUL
copy %srcpath%\network\mesg\nplus.msb		  %srcpath%\network\mesg\nplus.msb             > NUL
copy %srcpath%\network\mesg\nplzhs.msb		  %srcpath%\network\mesg\nplzhs.msb            > NUL
copy %srcpath%\network\mesg\nzus.msb		  %srcpath%\network\mesg\nzus.msb              > NUL
copy %srcpath%\network\mesg\nzzhs.msb		  %srcpath%\network\mesg\nzzhs.msb             > NUL
copy %srcpath%\network\mesg\snlus.msb		  %srcpath%\network\mesg\snlus.msb             > NUL
copy %srcpath%\network\mesg\snlzhs.msb		  %srcpath%\network\mesg\snlzhs.msb            > NUL
copy %srcpath%\network\mesg\tnlus.msb		  %srcpath%\network\mesg\tnlus.msb             > NUL
copy %srcpath%\network\mesg\tnlzhs.msb		  %srcpath%\network\mesg\tnlzhs.msb            > NUL
copy %srcpath%\network\mesg\tnplus.msb		  %srcpath%\network\mesg\tnplus.msb            > NUL
copy %srcpath%\network\mesg\tnplzhs.msb		  %srcpath%\network\mesg\tnplzhs.msb           > NUL
copy %srcpath%\network\mesg\tnsus.msb		  %srcpath%\network\mesg\tnsus.msb             > NUL
copy %srcpath%\network\mesg\tnszhs.msb		  %srcpath%\network\mesg\tnszhs.msb            > NUL
copy %srcpath%\oci\include\cdemodp0.h		  %srcpath%\oci\include\cdemodp0.h             > NUL
copy %srcpath%\oci\include\kusapi.h		  %srcpath%\oci\include\kusapi.h               > NUL
copy %srcpath%\oci\include\kustags.h		  %srcpath%\oci\include\kustags.h              > NUL
copy %srcpath%\oci\include\nzerror.h		  %srcpath%\oci\include\nzerror.h              > NUL
copy %srcpath%\oci\include\nzt.h		  %srcpath%\oci\include\nzt.h                  > NUL
copy %srcpath%\oci\include\oci.h		  %srcpath%\oci\include\oci.h                  > NUL
copy %srcpath%\oci\include\oci1.h		  %srcpath%\oci\include\oci1.h                 > NUL
copy %srcpath%\oci\include\oci8dp.h		  %srcpath%\oci\include\oci8dp.h               > NUL
copy %srcpath%\oci\include\ociap.h		  %srcpath%\oci\include\ociap.h                > NUL
copy %srcpath%\oci\include\ociapr.h		  %srcpath%\oci\include\ociapr.h               > NUL
copy %srcpath%\oci\include\ocidef.h		  %srcpath%\oci\include\ocidef.h               > NUL
copy %srcpath%\oci\include\ocidem.h		  %srcpath%\oci\include\ocidem.h               > NUL
copy %srcpath%\oci\include\ocidfn.h		  %srcpath%\oci\include\ocidfn.h               > NUL
copy %srcpath%\oci\include\ociextp.h		  %srcpath%\oci\include\ociextp.h              > NUL
copy %srcpath%\oci\include\ocikp.h		  %srcpath%\oci\include\ocikp.h                > NUL
copy %srcpath%\oci\include\ocikpr.h		  %srcpath%\oci\include\ocikpr.h               > NUL
copy %srcpath%\oci\include\odci.h		  %srcpath%\oci\include\odci.h                 > NUL
copy %srcpath%\oci\include\oratypes.h		  %srcpath%\oci\include\oratypes.h             > NUL
copy %srcpath%\oci\include\ori.h		  %srcpath%\oci\include\ori.h                  > NUL
copy %srcpath%\oci\include\orid.h		  %srcpath%\oci\include\orid.h                 > NUL
copy %srcpath%\oci\include\orl.h		  %srcpath%\oci\include\orl.h                  > NUL
copy %srcpath%\oci\include\oro.h		  %srcpath%\oci\include\oro.h                  > NUL
copy %srcpath%\oci\include\ort.h		  %srcpath%\oci\include\ort.h                  > NUL
copy %srcpath%\oci\include\tnsapi.h		  %srcpath%\oci\include\tnsapi.h               > NUL
copy %srcpath%\oci\lib\bc\oci.lib		  %srcpath%\oci\lib\bc\oci.lib                 > NUL
copy %srcpath%\oci\lib\bc\ociw32.lib		  %srcpath%\oci\lib\bc\ociw32.lib              > NUL
copy %srcpath%\oci\lib\msvc\oci.lib		  %srcpath%\oci\lib\msvc\oci.lib               > NUL
copy %srcpath%\oci\lib\msvc\ociw32.lib		  %srcpath%\oci\lib\msvc\ociw32.lib            > NUL
copy %srcpath%\ocommon\nls\ADMIN\DATA\LX00001.NLB %srcpath%\ocommon\nls\ADMIN\DATA\LX00001.NLB > NUL 
copy %srcpath%\ocommon\nls\ADMIN\DATA\LX00023.NLB %srcpath%\ocommon\nls\ADMIN\DATA\LX00023.NLB > NUL
copy %srcpath%\ocommon\nls\ADMIN\DATA\LX10001.NLB %srcpath%\ocommon\nls\ADMIN\DATA\LX10001.NLB > NUL
copy %srcpath%\ocommon\nls\ADMIN\DATA\LX10035.NLB %srcpath%\ocommon\nls\ADMIN\DATA\LX10035.NLB > NUL
copy %srcpath%\ocommon\nls\ADMIN\DATA\LX1BOOT.NLB %srcpath%\ocommon\nls\ADMIN\DATA\LX1BOOT.NLB > NUL
copy %srcpath%\ocommon\nls\ADMIN\DATA\LX20001.NLB %srcpath%\ocommon\nls\ADMIN\DATA\LX20001.NLB > NUL
copy %srcpath%\ocommon\nls\ADMIN\DATA\LX20354.NLB %srcpath%\ocommon\nls\ADMIN\DATA\LX20354.NLB > NUL
copy %srcpath%\ocommon\nls\ADMIN\DATA\LX60354.NLB %srcpath%\ocommon\nls\ADMIN\DATA\LX60354.NLB > NUL
copy %srcpath%\oledb\doc\oledb.pdf		  %srcpath%\oledb\doc\oledb.pdf                > NUL
copy %srcpath%\oledb\doc\readme.txt		  %srcpath%\oledb\doc\readme.txt               > NUL
copy %srcpath%\oledb\include\OraOLEDB.h		  %srcpath%\oledb\include\OraOLEDB.h           > NUL
copy %srcpath%\oledb\lib\OraOLEDB.lib		  %srcpath%\oledb\lib\OraOLEDB.lib             > NUL
copy %srcpath%\oledb\mesg\oraoledbus.msb	  %srcpath%\oledb\mesg\oraoledbus.msb          > NUL
copy %srcpath%\oledb\mesg\oraoledbzhs.msb	  %srcpath%\oledb\mesg\oraoledbzhs.msb         > NUL
copy %srcpath%\oracore\mesg\lemus.msb		  %srcpath%\oracore\mesg\lemus.msb             > NUL
copy %srcpath%\oracore\mesg\lfius.msb		  %srcpath%\oracore\mesg\lfius.msb             > NUL
copy %srcpath%\oracore\mesg\lfizhs.msb		  %srcpath%\oracore\mesg\lfizhs.msb            > NUL
copy %srcpath%\oracore\mesg\lhtus.msb		  %srcpath%\oracore\mesg\lhtus.msb             > NUL
copy %srcpath%\oracore\mesg\lmmus.msb		  %srcpath%\oracore\mesg\lmmus.msb             > NUL
copy %srcpath%\oracore\mesg\lpmus.msb		  %srcpath%\oracore\mesg\lpmus.msb             > NUL
copy %srcpath%\oracore\mesg\lpxus.msb		  %srcpath%\oracore\mesg\lpxus.msb             > NUL
copy %srcpath%\oracore\mesg\lpxzhs.msb		  %srcpath%\oracore\mesg\lpxzhs.msb            > NUL
copy %srcpath%\oracore\mesg\lrmus.msb		  %srcpath%\oracore\mesg\lrmus.msb             > NUL
copy %srcpath%\oracore\mesg\lrmzhs.msb		  %srcpath%\oracore\mesg\lrmzhs.msb            > NUL
copy %srcpath%\oracore\mesg\lsfus.msb		  %srcpath%\oracore\mesg\lsfus.msb             > NUL
copy %srcpath%\oracore\mesg\ltmus.msb		  %srcpath%\oracore\mesg\ltmus.msb             > NUL
copy %srcpath%\precomp\admin\ottcfg.cfg		  %srcpath%\precomp\admin\ottcfg.cfg           > NUL
copy %srcpath%\precomp\doc\ott\readme.doc	  %srcpath%\precomp\doc\ott\readme.doc         > NUL
copy %srcpath%\precomp\mesg\o2fus.msb		  %srcpath%\precomp\mesg\o2fus.msb             > NUL
copy %srcpath%\precomp\mesg\o2fzhs.msb		  %srcpath%\precomp\mesg\o2fzhs.msb            > NUL
copy %srcpath%\precomp\mesg\o2ius.msb		  %srcpath%\precomp\mesg\o2ius.msb             > NUL
copy %srcpath%\precomp\mesg\o2izhs.msb		  %srcpath%\precomp\mesg\o2izhs.msb            > NUL
copy %srcpath%\precomp\mesg\o2uus.msb		  %srcpath%\precomp\mesg\o2uus.msb             > NUL
copy %srcpath%\precomp\mesg\o2uzhs.msb		  %srcpath%\precomp\mesg\o2uzhs.msb            > NUL
copy %srcpath%\precomp\mesg\pgous.msb		  %srcpath%\precomp\mesg\pgous.msb             > NUL
copy %srcpath%\precomp\mesg\pgozhs.msb		  %srcpath%\precomp\mesg\pgozhs.msb            > NUL
copy %srcpath%\precomp\mesg\prous.msb		  %srcpath%\precomp\mesg\prous.msb             > NUL
copy %srcpath%\precomp\mesg\prozhs.msb		  %srcpath%\precomp\mesg\prozhs.msb            > NUL
copy %srcpath%\precomp\mesg\sqlus.msb		  %srcpath%\precomp\mesg\sqlus.msb             > NUL
copy %srcpath%\precomp\mesg\sqlzhs.msb		  %srcpath%\precomp\mesg\sqlzhs.msb            > NUL
copy %srcpath%\precomp\public\bnddsc.for	  %srcpath%\precomp\public\bnddsc.for          > NUL
copy %srcpath%\precomp\public\oraca.cob		  %srcpath%\precomp\public\oraca.cob           > NUL
copy %srcpath%\precomp\public\oraca.for		  %srcpath%\precomp\public\oraca.for           > NUL
copy %srcpath%\precomp\public\oraca.h		  %srcpath%\precomp\public\oraca.h             > NUL
copy %srcpath%\precomp\public\oraca5.cob	  %srcpath%\precomp\public\oraca5.cob          > NUL
copy %srcpath%\precomp\public\seldsc.for	  %srcpath%\precomp\public\seldsc.for          > NUL
copy %srcpath%\precomp\public\sql2oci.h		  %srcpath%\precomp\public\sql2oci.h           > NUL
copy %srcpath%\precomp\public\sqlapr.h		  %srcpath%\precomp\public\sqlapr.h            > NUL
copy %srcpath%\precomp\public\sqlca.cob		  %srcpath%\precomp\public\sqlca.cob           > NUL
copy %srcpath%\precomp\public\sqlca.for		  %srcpath%\precomp\public\sqlca.for           > NUL
copy %srcpath%\precomp\public\sqlca.h		  %srcpath%\precomp\public\sqlca.h             > NUL
copy %srcpath%\precomp\public\sqlca5.cob	  %srcpath%\precomp\public\sqlca5.cob          > NUL
copy %srcpath%\precomp\public\sqlcpr.h		  %srcpath%\precomp\public\sqlcpr.h            > NUL
copy %srcpath%\precomp\public\sqlda.cob		  %srcpath%\precomp\public\sqlda.cob           > NUL
copy %srcpath%\precomp\public\sqlda.h		  %srcpath%\precomp\public\sqlda.h             > NUL
copy %srcpath%\precomp\public\sqlda5.cob	  %srcpath%\precomp\public\sqlda5.cob          > NUL
copy %srcpath%\precomp\public\sqlkpr.h		  %srcpath%\precomp\public\sqlkpr.h            > NUL
copy %srcpath%\precomp\public\sqlucs2.h		  %srcpath%\precomp\public\sqlucs2.h           > NUL
copy %srcpath%\RDBMS\mesg\bbedus.msb		  %srcpath%\RDBMS\mesg\bbedus.msb              > NUL
copy %srcpath%\RDBMS\mesg\bbedzhs.msb		  %srcpath%\RDBMS\mesg\bbedzhs.msb             > NUL
copy %srcpath%\RDBMS\mesg\expus.msb		  %srcpath%\RDBMS\mesg\expus.msb               > NUL
copy %srcpath%\RDBMS\mesg\expzhs.msb		  %srcpath%\RDBMS\mesg\expzhs.msb              > NUL
copy %srcpath%\RDBMS\mesg\impus.msb		  %srcpath%\RDBMS\mesg\impus.msb               > NUL
copy %srcpath%\RDBMS\mesg\impzhs.msb		  %srcpath%\RDBMS\mesg\impzhs.msb              > NUL
copy %srcpath%\RDBMS\mesg\kgpus.msb		  %srcpath%\RDBMS\mesg\kgpus.msb               > NUL
copy %srcpath%\RDBMS\mesg\kgpzhs.msb		  %srcpath%\RDBMS\mesg\kgpzhs.msb              > NUL
copy %srcpath%\RDBMS\mesg\ocius.msb		  %srcpath%\RDBMS\mesg\ocius.msb               > NUL
copy %srcpath%\RDBMS\mesg\ocizhs.msb		  %srcpath%\RDBMS\mesg\ocizhs.msb              > NUL
copy %srcpath%\RDBMS\mesg\oraus.msb		  %srcpath%\RDBMS\mesg\oraus.msb               > NUL
copy %srcpath%\RDBMS\mesg\orazhs.msb		  %srcpath%\RDBMS\mesg\orazhs.msb              > NUL
copy %srcpath%\RDBMS\mesg\rmanus.msb		  %srcpath%\RDBMS\mesg\rmanus.msb              > NUL
copy %srcpath%\RDBMS\mesg\rmanzhs.msb		  %srcpath%\RDBMS\mesg\rmanzhs.msb             > NUL
copy %srcpath%\RDBMS\mesg\sbtus.msb		  %srcpath%\RDBMS\mesg\sbtus.msb               > NUL
copy %srcpath%\RDBMS\mesg\sbtzhs.msb		  %srcpath%\RDBMS\mesg\sbtzhs.msb              > NUL
copy %srcpath%\RDBMS\mesg\ulus.msb		  %srcpath%\RDBMS\mesg\ulus.msb                > NUL
copy %srcpath%\RDBMS\mesg\ulzhs.msb		  %srcpath%\RDBMS\mesg\ulzhs.msb               > NUL
copy %srcpath%\sqlplus\admin\glogin.sql		  %srcpath%\sqlplus\admin\glogin.sql           > NUL
copy %srcpath%\sqlplus\admin\help\helpbld.sql	  %srcpath%\sqlplus\admin\help\helpbld.sql     > NUL
copy %srcpath%\sqlplus\admin\help\helpdrop.sql	  %srcpath%\sqlplus\admin\help\helpdrop.sql    > NUL
copy %srcpath%\sqlplus\admin\help\helpus.sql	  %srcpath%\sqlplus\admin\help\helpus.sql      > NUL
copy %srcpath%\sqlplus\admin\plustrce.sql	  %srcpath%\sqlplus\admin\plustrce.sql         > NUL
copy %srcpath%\sqlplus\admin\pupbld.sql		  %srcpath%\sqlplus\admin\pupbld.sql           > NUL
copy %srcpath%\sqlplus\mesg\cpyus.msb		  %srcpath%\sqlplus\mesg\cpyus.msb             > NUL
copy %srcpath%\sqlplus\mesg\cpyzhs.msb		  %srcpath%\sqlplus\mesg\cpyzhs.msb            > NUL
copy %srcpath%\sqlplus\mesg\sp1us.msb		  %srcpath%\sqlplus\mesg\sp1us.msb             > NUL
copy %srcpath%\sqlplus\mesg\sp1zhs.msb		  %srcpath%\sqlplus\mesg\sp1zhs.msb            > NUL
copy %srcpath%\sqlplus\mesg\sp2us.msb		  %srcpath%\sqlplus\mesg\sp2us.msb             > NUL
copy %srcpath%\sqlplus\mesg\sp2zhs.msb		  %srcpath%\sqlplus\mesg\sp2zhs.msb            > NUL
copy %srcpath%\sqlplus\mesg\spwus.msb		  %srcpath%\sqlplus\mesg\spwus.msb             > NUL
copy %srcpath%\sqlplus\mesg\spwzhs.msb		  %srcpath%\sqlplus\mesg\spwzhs.msb            > NUL

set srcpath=
set despath=

goto end

:usage
echo usage: orcl8_cp srcpath

:end