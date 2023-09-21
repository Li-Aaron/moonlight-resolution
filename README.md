# moonlight-resolution
usage example:
```
moonlight-resolution.exe 1920 1080 "some command"
```
Functionality:
  1. change the resolution to 1920x1080 before command execuate.
  2. reset to the maximum supported resolution when command exit.
  
Note:
  1. must set to supported resolution of the monitor.
  2. if run without parameter, will test 1280x720 resolution, run system command "pause"

> Tested with VS2015 on Windows 10 22H2 19045
