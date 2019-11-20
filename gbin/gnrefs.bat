@echo off
call checktarget.bat
echo gn refs out\%CURRENT_DEBUGDIR% %*
gn refs out\%CURRENT_DEBUGDIR% %*

