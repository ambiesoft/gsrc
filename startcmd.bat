@echo off
REM Is this a second launch
IF "%1"=="2ndlaunch" (
  goto justlaunch
) ELSE (
  goto docontinue
)

:justlaunch
git config --global user.email "ambiesoft.trueff@gmail.com"
git config --global user.name   "ambiesoft"
start cmd /k
::start powershell
exit

:docontinue
IF NOT "%1"=="" exit

REM always launch 64bit cmd
set "SystemPath=%SystemRoot%\System32"
if not "%ProgramFiles(x86)%"=="" (
    if exist %SystemRoot%\Sysnative\* set "SystemPath=%SystemRoot%\Sysnative"
)


REM set path to depot_tools
set PATH=%~dp0depot_tools;%~dp0gbin;%PATH%


REM This tells depot_tools to use your locally installed version of Visual Studio 
REM (by default, depot_tools will try to use a google-internal version).
set DEPOT_TOOLS_WIN_TOOLCHAIN=0


REM make current directory the location this script exists.
cd %~dp0\chromium\src


REM always launch 64bit cmd
REM echo start %SystemPath%\cmd.exe /k %~dp0%~nx0 2ndlaunch
start %SystemPath%\cmd.exe /k %~dp0%~nx0 2ndlaunch

