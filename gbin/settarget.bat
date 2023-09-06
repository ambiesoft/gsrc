@echo off

if "%~1"=="" (
    set CURRENT_DEBUGDIR=Debug
    echo CURRENT_DEBUGDIR is set to Debug
) else (
    set "CURRENT_DEBUGDIR=%~1"
    echo CURRENT_DEBUGDIR is set to %~1
)
