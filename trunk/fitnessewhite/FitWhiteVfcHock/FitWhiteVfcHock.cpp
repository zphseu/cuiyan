//#include <afx.h>
#include <windows.h>
#include <stdio.h>

HANDLE hThread = 0;
BOOL bRunning = FALSE;
TCHAR file[FILENAME_MAX];

typedef DWORD (*VFCAPI_LoadDLL)(LPCTSTR strDLLInfo, DWORD dwData);
VFCAPI_LoadDLL pVFCAPI_LoadDLL;


void DoCommand(LPCTSTR cmd, LPCTSTR param)
{
	if (strcmp(cmd, "Launch") == 0)
	{
		pVFCAPI_LoadDLL(param, NULL);
	}
	
	return;
}

DWORD WINAPI ThreadProc(LPVOID pParam)
{
	TCHAR cmd[FILENAME_MAX], param[FILENAME_MAX];
	while (bRunning) 
	{
		FILE *fp = fopen(file, "rt");
		if (fp != NULL)
		{
			fscanf(fp, "%s\n", cmd);
			fscanf(fp, "%s\n", param);
			fclose(fp);
			DeleteFile(file);
			DoCommand(cmd, param);
		}

		Sleep(300);

	}
	return 0;
}


extern "C" _declspec(dllexport) int Start()
{
	HMODULE hInstance = LoadLibrary("VFC2000.exe");
	pVFCAPI_LoadDLL = (VFCAPI_LoadDLL)GetProcAddress(hInstance,"VFCAPI_LoadDLL");
	TCHAR path[FILENAME_MAX];
	DWORD pid = GetCurrentProcessId();
	GetTempPath(FILENAME_MAX, path);
	sprintf(file, "%s\\Fit.White.BSVfcFrame-%d.tmp", path, pid);
	
    DWORD threadID = 0;
	bRunning = TRUE;
    hThread = CreateThread(NULL, 0, ThreadProc, (LPVOID)NULL, NULL, &threadID); 	
	return 0;
}

extern "C" _declspec(dllexport) int End()
{	
	bRunning = FALSE;
    WaitForSingleObject( hThread, 1000 );
    
    // Destroy the thread object.
    CloseHandle( hThread );
	return 0;
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
} 

