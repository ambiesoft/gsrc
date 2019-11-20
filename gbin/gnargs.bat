@echo off
call checktarget.bat
gn args out\%CURRENT_DEBUGDIR% %*

