@echo off
call checktarget.bat
dir out\%CURRENT_DEBUGDIR%\*.sln %*

