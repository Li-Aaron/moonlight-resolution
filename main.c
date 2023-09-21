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

void printHelp(
	void
)
{
	printf("Example: \n");
	printf("Set - Execute - Restore: \n");
	printf("    moonlight-resolution.exe -c 1920 1080 60 something.exe:\n");
	printf("Set only: \n");
	printf("    moonlight-resolution.exe -s 1920 1080 60\n");
	printf("Restore only (to maximum supported resolution): \n");
	printf("    moonlight-resolution.exe -r\n");
	printf("Test: \n");
	printf("    moonlight-resolution.exe\n");
}


int main (
	int argc, 
	char *argv[]
) 
{
	DEVMODEA lpDevMode;
	LONG result;
	BOOL result1;
	INT  result2;
	BOOL doSet     = FALSE;
	BOOL doExecute = FALSE;
	BOOL doRestore = FALSE;
	DWORD  dmPelsWidthOri = 0;
	DWORD  dmPelsHeightOri = 0;
	DWORD  dmDisplayFrequencyOri = 0;
	DWORD  dmPelsWidthSet = 0;
	DWORD  dmPelsHeightSet = 0;
	DWORD  dmDisplayFrequencySet = 0;
	CHAR*  execmd = "";

	if (argc > 1) {
		// all functional
		if (strcmp(argv[1], "-c")) {
			if (argc == 6) {
				dmPelsWidthSet        = atoi(argv[2]);
				dmPelsHeightSet       = atoi(argv[3]);
				dmDisplayFrequencySet = atoi(argv[4]);
				execmd                = argv[5];
				doSet                 = TRUE;
				doExecute             = TRUE;
				doRestore             = TRUE;
			}
			else {
				printHelp();
			}
		}
		// set only
		else if (strcmp(argv[1], "-s")) {
			if (argc == 5) {
				dmPelsWidthSet        = atoi(argv[2]);
				dmPelsHeightSet       = atoi(argv[3]);
				dmDisplayFrequencySet = atoi(argv[4]);
				doSet                 = TRUE;
			}
			else {
				printHelp();
			}
		}
		// restore to maximum only
		else if (strcmp(argv[1], "-r")) {
			if (argc == 2) {
				doRestore             = TRUE;
			}
			else {
				printHelp();
			}
		}
		// error input
		else {
			printHelp();
		}
	}
	// test for full function
	else {
		printHelp();
		printf("Use defalut argument 1280 720\n");
		dmPelsWidthSet        = 1280;
		dmPelsHeightSet       = 720;
		dmDisplayFrequencySet = 60;
		execmd                = "pause";
		doSet                 = TRUE;
		doExecute             = TRUE;
		doRestore             = TRUE;
	}

	// get display setting.
	ZeroMemory(&lpDevMode, sizeof(lpDevMode));
	lpDevMode.dmSize = sizeof(lpDevMode);

	if (doSet) {
		// change the resolution
		lpDevMode.dmPelsWidth        = dmPelsWidthSet;
		lpDevMode.dmPelsHeight       = dmPelsHeightSet;
		lpDevMode.dmDisplayFrequency = dmDisplayFrequencySet;
		result = ChangeDisplaySettingsA(&lpDevMode, 0);
		if (result == DISP_CHANGE_SUCCESSFUL)
		{
			printf("修改成功!\n");
		}
	}

	if (doExecute) {
		// put a caller here
		printf("[%s] execuate.\n", execmd);
		result2 = system(execmd);
		printf("[%s] return: %d\n", execmd, result2);
	}

	if (doRestore) {
		// retrive the maximum supported setting
		result1 = TRUE;
		for (int i = 0; result1; i++) {
			result1 = EnumDisplaySettingsA(NULL, i, &lpDevMode);
			// printf("supported setting : %d x %d : %d\n", lpDevMode.dmPelsWidth, lpDevMode.dmPelsHeight, lpDevMode.dmDisplayFrequency);

			if (lpDevMode.dmPelsWidth >= dmPelsWidthOri && lpDevMode.dmPelsHeight >= dmPelsHeightOri) {
				// backup largest supported resolution
				dmPelsWidthOri  = lpDevMode.dmPelsWidth;
				dmPelsHeightOri = lpDevMode.dmPelsHeight;
			}
			if (lpDevMode.dmDisplayFrequency > dmDisplayFrequencyOri) {
				// backup largest supported frequency
				dmDisplayFrequencyOri = lpDevMode.dmDisplayFrequency;
			}
		}

		printf("dmPelsWidthOri:        %d\n", dmPelsWidthOri);
		printf("dmPelsHeightOri:       %d\n", dmPelsHeightOri);
		printf("dmDisplayFrequencyOri: %d\n", dmDisplayFrequencyOri);

		// change the resolution
		lpDevMode.dmPelsWidth        = dmPelsWidthOri;
		lpDevMode.dmPelsHeight       = dmPelsHeightOri;
		lpDevMode.dmDisplayFrequency = dmDisplayFrequencyOri;
		result = ChangeDisplaySettingsA(&lpDevMode, 0);
		if (result == DISP_CHANGE_SUCCESSFUL)
		{
			printf("修改成功!\n");
		}
	}
}
