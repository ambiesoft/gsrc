@echo off
call checktarget.bat
gn ls out\%CURRENT_DEBUGDIR% %*

