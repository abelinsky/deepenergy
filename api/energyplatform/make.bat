@echo off

set ROOT=.\..\energyplatform
set OUTPUT=build_results
set CPP_DESTINATION_DIR=.\..\..\simulators\gas\src\EnvSimulatorGas\EnvSimulatorGas
set PY_DESTINATION_DIR=.\..\..\agents_py
REM Set the list of directories with *.proto files to compile. Example: set APIS=(core, core2)
set APIS=(core)

REM Build protobuf files 
for %%d in %APIS% do ( 
	for %%f in (%%d/*.proto) do call :build "%%d/%%f"
)

REM Inserts #include "pch.h" to cpp files
pushd "%OUTPUT%"
for /r %%i in (*.cc) do call :add_header %%i
popd

REM copy generated scripts to destinations
ROBOCOPY %OUTPUT% %CPP_DESTINATION_DIR% *.cc *.h /R:0 /e
ROBOCOPY %OUTPUT% %PY_DESTINATION_DIR% *.py  /R:0 /e

EXIT /B %ERRORLEVEL%

REM Builds *.proto file
:build
echo Building file: %~1 
call _build_proto.bat %ROOT% %~1 %OUTPUT%
EXIT /B 0

REM Adds #include "pch.h" header to cpp files
:add_header
copy %~1 temp.txt
echo.#include "pch.h">%~1
type temp.txt >>%~1
del temp.txt
EXIT /B 0


