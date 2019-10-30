@echo off
echo creating outputs of varios gn commands...
dir > %~dp0..\gnout\test-dir.out

echo creating gn-ls-executable.gnout...
call gn ls out\debug --type=executable > %~dp0..\gnout\gn-ls-executable.gnout

echo creating gn-ls.gnout...
call gn ls out\debug > %~dp0..\gnout\gn-ls.gnout

echo creating gn-args-list.gnout...
call gn args out\debug --list > %~dp0..\gnout\gn-args-list.gnout


