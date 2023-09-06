@echo off
REM Is this a second launch
IF "%1"=="2ndlaunch" (
  goto justlaunch
) ELSE (
  goto docontinue
)

:justlaunch
if exist %~dp0gitinit.bat (
  call %~dp0gitinit.bat
)
REM Env
if exist %~dp0.startenv.bat (
  call %~dp0.startenv.bat
)
:: clink is advanced command prompt, see https://mridgers.github.io/clink/
if exist C:\LegacyPrograms\clink\clink.batZZZ (
  C:\LegacyPrograms\clink\clink.bat
  exit /b
) else (
  :: start powershell
  :: start cmd /k
  start powershell
)
exit

:docontinue
IF NOT "%1"=="" exit

REM always launch 64bit cmd
set "SystemPath=%SystemRoot%\System32"
if not "%ProgramFiles(x86)%"=="" (
    if exist %SystemRoot%\Sysnative\* set "SystemPath=%SystemRoot%\Sysnative"
)

if not exist %~dp0depot_tools\ (
    echo depot_tools not found at %~dp0depot_tools\
    echo Install depot_tools from https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html
    pause
    exit
)

REM set path to depot_tools
set PATH=%~dp0depot_tools;%~dp0gbin;%PATH%


REM This tells depot_tools to use your locally installed version of Visual Studio 
REM (by default, depot_tools will try to use a google-internal version).
set DEPOT_TOOLS_WIN_TOOLCHAIN=0


if exist %~dp0chromium\src (
  cd %~dp0chromium\src
)


REM always launch 64bit cmd
REM echo start %SystemPath%\cmd.exe /k %~dp0%~nx0 2ndlaunch
call %~dp0gbin\settarget.bat
start %SystemPath%\cmd.exe /k %~dp0%~nx0 2ndlaunch

