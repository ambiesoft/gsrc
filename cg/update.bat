set GN_DEFINES=use_jumbo_build=true is_component_build=true
set GN_ARGUMENTS=--ide=vs2017 --sln=cef --filters=//cef/*
python ..\automate\automate-git.py --download-dir=c:\code\cg --depot-tools-dir=c:\code\depot_tools --no-distrib --no-build