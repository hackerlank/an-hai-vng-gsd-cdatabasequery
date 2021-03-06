// AutoUpdateCF.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AutoUpdate.h"
#include "MyPath.h"
#include "InputReader.h"
#include "Fifa2AutoLauncher.h"
#include "AuditionAutoLauncher.h"
#include "CrossfireAutoLauncher.h"
#include "AutoUpdateTool.h"
#include "FolderCompare.h"
#include "Launcher.h"
#include "TLBBAutoLauncher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CWinApp theApp;

using namespace std;


BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
	

	int ID =  GetDlgCtrlID(hwnd);

	RECT rect;
	::GetWindowRect(hwnd, &rect);
	CString strText;

	strText.Format(L"id = %d, left = %d, top = %d, right = %d, bottom = %d\n", ID, rect.left, rect.top, rect.right, rect.bottom);
	_tprintf(strText);

	//
	//

	//if (ID == 1027) {
	//	
	//	HWND hParentWnd = ::GetParent(hwnd);
	//	

	//	WORD lParam  = (WORD)hwnd;
	//	WORD wParam = MAKEWPARAM(ID, BN_CLICKED);

	//	::SendMessage(hParentWnd, WM_COMMAND, wParam, lParam);
	//}
	//EnumChildWindows(hwnd, EnumChildProc, 0);

	//_tprintf(strText);

	//strText.Format(L"ID = %d\n", ID);
	//_tprintf(strText);

	//::GetClassName(hwnd, strClassName, MAX_LENGTH);
	//CString strText;
	//strText.Format(L"Class name: %s\n", strClassName);

	//_tprintf(strClassName);
	
	//CString strText;

	//strText.Format(L"Class name: %s. Window name: %s. CtrlID: \n", strClassName, strWindowName);
	//_tprintf(strText);

	//EnumChildWindows(hwnd, EnumChildProc, 0);
	return TRUE;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		
		//int iHandle = 0x00030F92;
		//HWND hWnd = (HWND)iHandle;

		//const int MAX_LENGTH = 128;

		//TCHAR strClassName[MAX_LENGTH];
		//::GetClassName(hWnd, strClassName, MAX_LENGTH);
		//_tprintf(L"Class name: %s\n", strClassName);

		//int iCount = ::SendMessage(hWnd, TVM_GETCOUNT, 0, 0);
		//_tprintf(L"COunt: %u\n", iCount);

		//
		//HTREEITEM hTreeItem = TreeView_GetFirstVisible(hWnd);

		//if (NULL == hTreeItem) {
		//	_tprintf(L"Fail\n");
		//}

		//TreeView_SelectItem(hWnd, hTreeItem);

		//if (NULL == hTreeItem) {
			//_tprintf(L" fail\n");
		//}

		
		//const int MAX_LENGTH = 128;

		//TCHAR strClassName[MAX_LENGTH];
		//::GetClassName(hWnd, strClassName, MAX_LENGTH);
		//_tprintf(L"Class name: %s\n", strClassName);
		//
		//CTreeCtrl treeCtrl;
		//if (FALSE == treeCtrl.Attach(hWnd)) {
		//	_tprintf(L"attach fail\n");
		//}

		//UINT uiCount = treeCtrl.GetCount();

		//HTREEITEM hItem = treeCtrl.GetFirstVisibleItem();
		//treeCtrl.SetCheck(hItem, FALSE);
		////CString strText = treeCtrl.GetItemText(hItem);

		////_tprintf(L"Text: %s\n", strText);


		//_tprintf(L"COunt: %u\n", uiCount);
		//treeCtrl.Detach();
		//_tprintf(L"OK\n");

		
		//TCHAR strSource[] = L"D:\\GameUpdate\\Au6116";

		//CLauncher *pLaucher = new CAuditionAutoLauncher(strSource);

		//if (FALSE == pLaucher->Run()) {
		//	_tprintf(L"Fail\n");
		//} else {
		//	_tprintf(L"Success\n");
		//}

		
		CMyPath myPath;

		CString strExeFilePath = myPath.GetExeFilePath();
		CString strInputFilePath = strExeFilePath + L"\\input.ini";

		CInputReader reader(strInputFilePath);
		if (FALSE == reader.Read()) {
			_tprintf(L"fail\n");
		} else {
			_tprintf(L"ok\n");
		}
		
	}

	return nRetCode;
}


