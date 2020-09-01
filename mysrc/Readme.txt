1, run mingw
2, cd /c/gsrc
3, cat mysrc/addthistosrcBuild.ng.txt >> chromium/src/BUILD.gn
4, open command
5, In windows, C:\gsrc>mklink /D /J chromium\src\mysrc mysrc
6, In Linux, ln -s ../../mysrc mysrc
