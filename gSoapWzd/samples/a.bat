cd src
if "%1%" == "g" goto g
if "%1%" == "v" goto v
echo usage a [g/v]

:v
call devars vc6
@echo on
if exist calcClt.dsp 	call msdev calcClt.dsp /MAKE ALL
if exist calcSvr.dsp 	call msdev calcSvr.dsp /MAKE ALL
if exist calcCltps.dsp 	call msdev calcCltps.dsp /MAKE ALL
if exist mod_calc.dsp 	call msdev mod_calc.dsp /MAKE ALL
goto end

:g
call devars gcc
@echo on
if exist calcClt.mak 	make -f calcClt.mak
if exist calcSvr.mak 	make -f calcSvr.mak
if exist calcCltps.mak 	make -f calcCltps.mak
if exist mod_calc.mak	make -f mod_calc.mak
goto end

:end
del *.o *.c *.h *.nsmap *.dsp *.mak *.opt *.plg *.cpp *.xml *.a *.def
cd ..
