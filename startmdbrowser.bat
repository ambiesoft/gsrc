call C:\Linkout\bat\addpath.bat %~dp0depot_tools

start "" python %~dp0chromium\src\tools\md_browser\md_browser.py

echo %PATH%

echo Opening http://localhost:8080/docs/README.md ...
start "" "http://localhost:8080/docs/README.md"
