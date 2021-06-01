@echo off

::set _NT_SYMBOL_PATH SRV*;c:\code\chromium\src\out\debug*https://msdl.microsoft.com/download/symbols
::set _NT_SOURCE_PATH SRV*;c:\code\chromium\src

start "" "%ProgramFiles(x86)%\Windows Kits\10\Debuggers\x64\windbg.exe" %*
