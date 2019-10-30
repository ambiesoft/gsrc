@echo on
setlocal
set PROJ=%1
set PROJEXE=%~x1
set PROJSAVE=%PROJ%.save

echo %PROJ%
IF [%PROJ%] == [] (
  echo No Input Project file
  goto end
)

::: Compare extension case-insensitively
if /I not "%PROJEXE%" == ".vcxproj" (
  echo %PROJ% is not visual studio project file
  goto end
)

::: Remove lines which contains 'ninja' and write to new file
grep -v ninja  %PROJ% > %PROJSAVE%

::: Rename the new file with old one
move %PROJSAVE% %PROJ%

:end
endlocal