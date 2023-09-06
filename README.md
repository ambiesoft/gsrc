# gsrc: various tools for cef and chromium

## Get ready for windows
```
> cd C:\
> git clone git@github.com:ambiesoft/gsrc.git code
> cd code
> git submodule update -i
```

## install depot_tools
Download **depot_tools** from [here](https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html) and extract to C:\Code\depot_tools

## Open command prompt
Run **startcmd.bat**, this script adds **depot_tools** to the PATH.

## Get source code
https://chromium.googlesource.com/chromium/src/+/master/docs/windows_build_instructions.md

## Useful script in gbin
First run **gettarget** to show current build-output directory. If it show 'Debug', Commands in gbin/ assumes that your build-output directory is out\Debug. Run **settarget** to change the debug target.

### creategnout
This script creates various gn output as a cache in gnout\. Commands that start with '**catgn**' uses this cache to show the results.

### gngennin
Builds a target and create a Visual Studio's sln file.

example:
```
gngennin -j 8 //content/shell:content_shell
```

### lssln
Shows sln files in current build-output directory.

### startsln
Starts Visual Studio's sln. Needs to provide first few letters that can identify a sln.

