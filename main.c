#include <stdio.h> 
#include <windows.h> 
#include <winuser.h>
#include <wingdi.h>


/*
LONG ChangeDisplaySettingsA(
	[in] DEVMODEA *lpDevMode,
	[in] DWORD    dwFlags
);
*/
/*
BOOL EnumDisplaySettingsA(
	[in]  LPCWSTR  lpszDeviceName,
	[in]  DWORD    iModeNum,
	[out] DEVMODEW *lpDevMode
);
*/

int main (
	int argc, 
	char *argv[]
) 
{
	DEVMODEA lpDevMode;
	LONG result;
	BOOL result1;
	INT  result2;
	DWORD  dmPelsWidthOri = 0;
	DWORD  dmPelsHeightOri = 0;
	DWORD  dmPelsWidthSet = 0;
	DWORD  dmPelsHeightSet = 0;
	CHAR*  execmd;

	if (argc > 1) {
		if (argc != 4) {
			printf("Error argument number error\n");
			printf("Example: \n    moonlight-resolution.exe 1920 1080 something.exe:\n");
		}
		dmPelsWidthSet = atoi(argv[1]);
		dmPelsHeightSet = atoi(argv[2]);
		execmd = argv[3];
	}
	else {
		printf("Use defalut argument 1280 720\n");
		dmPelsWidthSet = 1280;
		dmPelsHeightSet = 720;
		execmd = "pause";
	}

	// get display setting.
	ZeroMemory(&lpDevMode, sizeof(lpDevMode));
	lpDevMode.dmSize = sizeof(lpDevMode);
	// ENUM_CURRENT_SETTINGS: 0

	// retrive the last supported setting
	result1 = TRUE;
	for (int i = 0; result1; i++) {
		result1 = EnumDisplaySettingsA(NULL, i, &lpDevMode);
		// printf("supported setting : %d x %d\n", lpDevMode.dmPelsWidth, lpDevMode.dmPelsHeight);

		if (lpDevMode.dmPelsWidth > dmPelsWidthOri && lpDevMode.dmPelsHeight > dmPelsHeightOri) {
			// backup largest supported resolution
			dmPelsWidthOri = lpDevMode.dmPelsWidth;
			dmPelsHeightOri = lpDevMode.dmPelsHeight;
		}
	}

	printf("dmPelsWidthOri: %d\n", dmPelsWidthOri);
	printf("dmPelsHeightOri: %d\n", dmPelsHeightOri);

	// change the resolution
	lpDevMode.dmPelsWidth = dmPelsWidthSet;
	lpDevMode.dmPelsHeight = dmPelsHeightSet;
	result = ChangeDisplaySettingsA(&lpDevMode, 0);
	if (result == DISP_CHANGE_SUCCESSFUL)
	{
		printf("修改成功!\n");
	}

	// put a caller here
	printf("[%s] execuate.\n", execmd);
	result2 = system(execmd);
	printf("[%s] return: %d\n", execmd, result2);

	// change the resolution
	lpDevMode.dmPelsWidth = dmPelsWidthOri;
	lpDevMode.dmPelsHeight = dmPelsHeightOri;

	result = ChangeDisplaySettingsA(&lpDevMode, 0);
	if (result == DISP_CHANGE_SUCCESSFUL)
	{
		printf("修改成功!\n");
	}

}
