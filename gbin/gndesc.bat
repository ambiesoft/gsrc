@echo off
call checktarget.bat
echo gn desc out\%CURRENT_DEBUGDIR% %*
gn desc out\%CURRENT_DEBUGDIR% %*

