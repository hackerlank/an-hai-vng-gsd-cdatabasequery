// AutoUpdateCF.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutoUpdateCF.h"
#include "CrossfireLauncher.h"
#include "FifaLauncher.h"
#include "AuditionLauncher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

BOOL CALLBACK FindTiepTheoButton(__in  HWND hwnd,__in  LPARAM lParam	) {

	TCHAR strWindowText[MAX_PATH];
	::GetWindowText(hwnd, strWindowText, MAX_PATH);
	if (lstrcmp(L"&Tiếp theo >", strWindowText) == 0) {
		::OutputDebugStringA("OK");
	}
	//::GetClassName(hwnd, strWindowText, MAX_PATH);
	::OutputDebugString(strWindowText);
	::OutputDebugStringA("\n");
	//::GetWindowText(hwnd, strWindowText, MAX_PATH);
	//TRACE("%s\n",  strWindowText);
	return TRUE;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		//TCHAR strSourcePath[] = L"D:\\GameUpdate\\CrossFire";
		//TCHAR strLauncherPath[] = L"D:\\GameUpdate\\CF_Patch_1108.exe";

		//CAutoLauncher *pAutoLauncher = new CCrossfireLauncher(strSourcePath, strLauncherPath);

		//TCHAR strSourcePath[] = L"D:\\GameUpdate\\Fifa Online 2";
		//TCHAR strLauncherPath[] = L"D:\\GameUpdate\\FIFA_Patch_1087.exe";

		//CAutoLauncher *pAutoLauncher = new CFifaLauncher(strSourcePath, strLauncherPath);

		TCHAR strSourcePath[] = L"D:\\GameUpdate\\Au6116";
		TCHAR strLauncherPath[] = L"D:\\GameUpdate\\Audition_Ban_Cap_Nhat_6117.exe";

		CAutoLauncher *pAutoLauncher = new CAuditionLauncher(strSourcePath, strLauncherPath);

		if (FALSE == pAutoLauncher->Run()) {
			AfxMessageBox(L"Fail", MB_ICONERROR);
		} else {
			TRACE("OK\n");
			//AfxMessageBox(L"OK", MB_ICONINFORMATION);
		}


		if (NULL != pAutoLauncher) {
			delete pAutoLauncher;
		}

		//TCHAR strSource[] = L"D:\\AnLNT\\Ebook\\abc.txt";
		//TCHAR strDest[] = L"D:\\Release\\ClickVersion\\abc.txt";

		//if (FALSE == ::CopyFile(strSource, strDest, FALSE)) {
		//	TRACE("fail\n");
		//} else {
		//	TRACE("OK\n");
		//}

	}

	return nRetCode;
}
