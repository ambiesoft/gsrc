@echo off
call checktarget.bat
echo gn outputs out\%CURRENT_DEBUGDIR% %*
gn outputs out\%CURRENT_DEBUGDIR% %*

