1, run mingw
2, cd /c/gsrc
3, cat mysrc/addthistosrcBuild.ng.txt >> chromium/src/BUILD.gn
4, open command
5, C:\gsrc>mklink /D /J chromium\src\mysrc mysrc

Add following lines to C:\code\chromium\src\tools\gritsettings\resource_ids.spec
  "mysrc/gndev/gndev_resources.grd": {
    "messages": [3900],
  },

