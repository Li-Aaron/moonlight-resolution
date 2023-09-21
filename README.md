# moonlight-resolution
usage example:
```
	Example: 
	Set - Execute - Restore: 
	    moonlight-resolution.exe -c 1920 1080 60 something.exe:
	Set only: 
	    moonlight-resolution.exe -s 1920 1080 60
	Restore only (to maximum supported resolution): 
	    moonlight-resolution.exe -r
	Test: 
	    moonlight-resolution.exe
```
Functionality:
  1. change the resolution to 1920x1080 before command execuate.
  2. reset to the maximum supported resolution when command exit.
  
Note:
  1. must set to supported resolution of the monitor.
  2. if run without parameter, will test 1280x720 resolution, run system command "pause"

> Tested with VS2015 on Windows 10 22H2 19045
