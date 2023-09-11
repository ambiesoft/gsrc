## catgnargs.bat

## catgnls.bat

## catgnlsexe.bat

## checktarget.bat

## chrome_debug_ppapi.bat

## chrome_debug_singleprocess.bat

## chrome_debug_utility.bat

## cnote.bat

## creategnout.bat

## dev\*.bat

## gettarget.bat

```
shows %CURRENT_DEBUGDIR%
```

## git-show-HEAD.bat

```
git rev-parse HEAD
```

## gnargs.bat

```
gn args out\%CURRENT_DEBUGDIR% %*
```

## gndesc.bat

```
gn desc out\%CURRENT_DEBUGDIR% %*
```

## gngen.bat

```
gn gen out\%CURRENT_DEBUGDIR% %*
```

## gngennin.bat

```
 gngennin.bat //content/shell:content_shell
```

## gnls.bat gnlsexe.bat

## gnoutputs.bat

```
gn outputs out\%CURRENT_DEBUGDIR% %*
```

## gnpath.bat

```
gn path out\%CURRENT_DEBUGDIR% %*
```

## gnrefs.bat

```
gn refs out\%CURRENT_DEBUGDIR% %*
```

## gnrefsreal.bat

call gnref with realpath input

```

```

## headless_debug_gpu.bat

Run 'headless_example.exe'

```
start "" out\debug\headless_example.exe --gpu-startup-dialog --no-sandbox --remote-debugging-port=9222 http://ambiesoft.com/webapp/testclient/chromiumprint.html
```

## idlerun.bat

Run command with lowest priority

## lsexe.bat

Shows \*.exe in the target directory

## lssln.bat

Shows \*.sln in the target directory

## ninjac.bat

```
ninja -C out\%CURRENT_DEBUGDIR% %*
```

## openlsall.bat

```
mery %~dp0..\gnout\gn-ls.gnout
```

## openlsexe.bat

```
mery %~dp0..\gnout\gn-ls-executable.gnout
```

## pnote.bat

```
Read stdin and open them with chrome
This script can be used in the same way of 'less'
ex)

> dir | python pnote.py
>
```

## qtcreator.bat

```
start "" "C:\local\Qt\Tools\QtCreator\bin\qtcreator.exe"  %*
```

## real2gn.bat

```
Get relative path from sourceDir.
if input = C:\\a\\b\\c\\d\\x.txt and sourceDir = C:\\a\\b,
the result is c\\d\\x.txt
```

```
real2gn .\chrome\app\access_code_cast_strings.grdp
```

## removeninjafromproj.bat

```
removeninjafromproj.bat .\out\Debug\obj\content\shell\content_shell.vcxproj
```

## settarget.bat

Sets target directory

## showtarget.bat

Shows the target directory

## startexe.bat

Starts exe

```
startexe con
```

## startsln.bat

Start sln start with input letter

```
startsln con
```

## websrc.bat

Open source file with https://chromium.googlesource.com/

```
websrc.bat C:\code\chromium\src\content\app\content_main_runner_impl.cc
```

## windbg.bat
