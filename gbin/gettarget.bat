@echo off
if %CURRENT_DEBUGDIR%x=="x" (
  echo No Target set, call 'settarget[64]'
  exit /b
)
echo %CURRENT_DEBUGDIR%
exit /b