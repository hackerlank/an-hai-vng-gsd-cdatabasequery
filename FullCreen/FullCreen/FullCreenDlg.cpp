
// FullCreenDlg.cpp : implementation file
//


#include "stdafx.h"
#include "FullCreen.h"
#include "FullCreenDlg.h"
#include "StrSafe.h"
#include "Winuser.h"
#include "TlHelp32.h"



#ifndef MAKEULONGLONG
#define MAKEULONGLONG(ldw, hdw) ((ULONGLONG(hdw) << 32) | ((ldw) & 0xFFFFFFFF))
#endif
  
#ifndef MAXULONGLONG
#define MAXULONGLONG ((ULONGLONG)~((ULONGLONG)0))
#endif



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IMPORT __declspec(dllimport)
IMPORT void doSetForegroundGlobalHook(HWND hWnd);
IMPORT void doRemoveGlobalHook();

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFullCreenDlg dialog




CFullCreenDlg::CFullCreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFullCreenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFullCreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFullCreenDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_FULLCREEN, &CFullCreenDlg::OnBnClickedBtnFullcreen)
	ON_BN_CLICKED(IDC_BTN_NORMAL, &CFullCreenDlg::OnBnClickedBtnNormal)
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_FIFA, &CFullCreenDlg::OnBnClickedBtnFifa)
	ON_BN_CLICKED(IDC_BTN_MINIMIZEPID, &CFullCreenDlg::OnBnClickedBtnMinimizepid)
	ON_BN_CLICKED(IDC_BTN_RESTORE, &CFullCreenDlg::OnBnClickedBtnRestore)
END_MESSAGE_MAP()


// CFullCreenDlg message handlers

BOOL CFullCreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	// TODO: Add extra initialization here
	
	OnBnClickedBtnFifa();
	//SetTimer(1, 500,NULL);
	
	//OnBnClickedBtnFullcreen();
	//doSetForegroundGlobalHook(this->m_hWnd);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFullCreenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFullCreenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFullCreenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFullCreenDlg::OnBnClickedBtnFullcreen()
{
	// TODO: Add your control notification handler code here
	/*HDC hDC = ::GetWindowDC(NULL); 
	CWnd* handle = GetWindow( IDD_FULLCREEN_DIALOG);

	SetWindowPos(handle, 0, 0, ::GetDeviceCaps(hDC, HORZRES), ::GetDeviceCaps(hDC, VERTRES), SWP_SHOWWINDOW);*/

	int  iCX,iCY; 
    iCX = GetSystemMetrics(SM_CXSCREEN);
    iCY = GetSystemMetrics(SM_CYSCREEN);
     
	DWORD style =  GetStyle();
	style &= ~WS_BORDER;
	this->ModifyStyle(WS_BORDER, NULL, 0);
	ShowWindow(SW_SHOWMAXIMIZED);
	SetForegroundWindow();
    SetWindowPos(&wndTopMost, 0, 0, iCX, iCY, SWP_NOSIZE| SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
	
	
}

void CFullCreenDlg::OnBnClickedBtnNormal()
{
	// TODO: Add your control notification handler code here
	//KillTimer(1);
	this->ModifyStyle(NULL, WS_BORDER, 0);
	ShowWindow(SW_SHOWNORMAL);
}
void CFullCreenDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{
		SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
		CWnd* winMain = GetWindow( IDD_FULLCREEN_DIALOG);
		CWnd* winForeground = GetForegroundWindow();
		//this->ModifyStyleEx(NULL, WS_EX_TOPMOST , 0);
		
		CWnd* winActive = GetActiveWindow();
		
		if(NULL != winActive && winMain != winActive)
		{
			SetActiveWindow();
		}
		if(winMain != winForeground)
		{

			
			
			//::SwitchToThisWindow(winForeground->m_hWnd, TRUE);
			//ShowWindow(SW_SHOW);
			//this->ModifyStyle(WS_BORDER, NULL, 0);
			//ShowWindow(SW_SHOWMAXIMIZED);
			
			//HWND hFrgWnd = ::GetForegroundWindow();
			//SetForegroundWindow();
			//::GetForegroundWindow();
			AttachThreadInput(GetWindowThreadProcessId(winForeground->m_hWnd, NULL), GetCurrentThreadId(), TRUE);
			//BOOL flag = FALSE;
			//do
			//{
			
				//HWND hFocus = ::GetFocus();
			
				
				::SetForegroundWindow(GetSafeHwnd());
				this->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			
				
				SendMessage(WM_ACTIVATE, MAKEWPARAM( WA_ACTIVE, 0), (LPARAM)winForeground->m_hWnd);
				::SendMessage(winForeground->m_hWnd, WM_SIZE, SIZE_MINIMIZED, MAKELPARAM(20, 20));
				
				//if(flag)
				//flag = this->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			//}while(!flag);

			AttachThreadInput(GetWindowThreadProcessId(winForeground->m_hWnd, NULL), GetCurrentThreadId(), FALSE);
			//BringWindowToTop();
			SetActiveWindow();
			//::EnableWindow(winForeground->m_hWnd, FALSE);
		}
		
		/*HWND hFrgWnd = ::GetForegroundWindow();
		AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL), GetCurrentThreadId(), TRUE);
		::SetForegroundWindow(GetSafeHwnd());
		AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL), GetCurrentThreadId(), TRUE);*/
	}
}
void CFullCreenDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);
	//if(nIDEvent == 1)
	//{
	//	CWnd* winMain = GetWindow( IDD_FULLCREEN_DIALOG);
	//	CWnd* winForeground = GetForegroundWindow();
	//	if(winMain != winForeground)
	//	{
	//		ShowWindow(SW_SHOW);
	//		SetForegroundWindow();
	//	}

	//	/*HWND hFrgWnd = ::GetForegroundWindow();
	//	AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL), GetCurrentThreadId(), TRUE);
	//	::SetForegroundWindow(GetSafeHwnd());
	//	AttachThreadInput(GetWindowThreadProcessId(hFrgWnd, NULL), GetCurrentThreadId(), TRUE);*/
	//}
	// TODO: Add your message handler code here
	::OutputDebugString(_T("kill focus \n"));
	
}
int CFullCreenDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//this->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	m_lpCreateStruct = lpCreateStruct;
	return CDialog::OnCreate(lpCreateStruct);
}
LRESULT CFullCreenDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	//if(message == WM_ACTIVATEAPP)
	//{
	//	
	//	//AfxMessageBox(_T("no topmost"));
	//	::OutputDebugString(_T("moving \n"));
	//	wParam = TRUE;
	//	lParam = (LPARAM)GetCurrentThreadId();
	//	
	//	return ::DefWindowProc(this->m_hWnd ,message, 0, 0);
	//}
	//else
		return CDialog::DefWindowProc(message, wParam, lParam);
}

void CFullCreenDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	//doRemoveGlobalHook();
	
	CDialog::OnClose();
}
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	HWND hwndMain = (HWND)lParam;
	TCHAR buffer[256];
	::GetWindowText(hWnd, buffer, 256);
	
	if(wcscmp(buffer, _T("FIFA Online 2")) == 0)
	{
	// Insert it into the list box
		::ShowWindow(hWnd, SW_HIDE);
		
	}
	if(hWnd != hwndMain)
	{
		
	}
	return TRUE;
}



//bool CloseProcessMainThread(DWORD dwProcID)
//{
//  DWORD dwMainThreadID = 0;
//  ULONGLONG ullMinCreateTime = MAXULONGLONG;
//  
//  HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
//  if (hThreadSnap != INVALID_HANDLE_VALUE) {
//    THREADENTRY32 th32;
//    th32.dwSize = sizeof(THREADENTRY32);
//    BOOL bOK = TRUE;
//    for (bOK = Thread32First(hThreadSnap, &th32); bOK;
//         bOK = Thread32Next(hThreadSnap, &th32)) {
//      if (th32.th32OwnerProcessID == dwProcID) {
//        HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION,
//                                    TRUE, th32.th32ThreadID);
//        if (hThread) {
//          FILETIME afTimes[4] = {0};
//          if (GetThreadTimes(hThread,
//                             &afTimes[0], &afTimes[1], &afTimes[2], &afTimes[3])) {
//            ULONGLONG ullTest = MAKEULONGLONG(afTimes[0].dwLowDateTime,
//                                              afTimes[0].dwHighDateTime);
//            if (ullTest && ullTest < ullMinCreateTime) {
//              ullMinCreateTime = ullTest;
//              dwMainThreadID = th32.th32ThreadID; // let it be main... :)
//            }
//          }
//          CloseHandle(hThread);
//        }
//      }
//    }
//	#ifndef UNDER_CE
//		CloseHandle(hThreadSnap);
//	#else
//		CloseToolhelp32Snapshot(hThreadSnap);
//	#endif
//	  }
//  
//	  if (dwMainThreadID) {
//		  //PostThreadMessage(dwMainThreadID, WM_QUIT, 0, 0); // close your eyes...
//		  
//	  }
//  
//	return (0 != dwMainThreadID);
//}
//


DWORD CloseProcessMainThread(DWORD dwProcID)
{
  DWORD dwMainThreadID = 0;
  ULONGLONG ullMinCreateTime = MAXULONGLONG;
  
  HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
  if (hThreadSnap != INVALID_HANDLE_VALUE) {
    THREADENTRY32 th32;
    th32.dwSize = sizeof(THREADENTRY32);
    BOOL bOK = TRUE;
    for (bOK = Thread32First(hThreadSnap, &th32); bOK;
         bOK = Thread32Next(hThreadSnap, &th32)) {
      if (th32.th32OwnerProcessID == dwProcID) {
        HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION,
                                    TRUE, th32.th32ThreadID);
        if (hThread) {
          FILETIME afTimes[4] = {0};
          if (GetThreadTimes(hThread,
                             &afTimes[0], &afTimes[1], &afTimes[2], &afTimes[3])) {
            ULONGLONG ullTest = MAKEULONGLONG(afTimes[0].dwLowDateTime,
                                              afTimes[0].dwHighDateTime);
            if (ullTest && ullTest < ullMinCreateTime) {
              ullMinCreateTime = ullTest;
              dwMainThreadID = th32.th32ThreadID; // let it be main... :)
            }
          }
          CloseHandle(hThread);
        }
      }
    }
	#ifndef UNDER_CE
		CloseHandle(hThreadSnap);
	#else
		CloseToolhelp32Snapshot(hThreadSnap);
	#endif
	  }
  
	  if (dwMainThreadID) {
		  //PostThreadMessage(dwMainThreadID, WM_QUIT, 0, 0); // close your eyes...
		  
	  }
  
	return dwMainThreadID;
}
BOOL CALLBACK EnumWindowsProcMinimizeFifa(HWND hWnd, LPARAM lParam)
{
	DWORD idProc = (DWORD)lParam;
	DWORD windowPID;

	windowPID = ::GetWindowThreadProcessId( hWnd,NULL );
	
	if(windowPID == idProc && IsWindow(hWnd) &&IsWindowVisible(hWnd))
	{
		ShowWindow(hWnd, SW_MINIMIZE);
		
	}
	return TRUE;
}

BOOL CALLBACK EnumWindowsProcRestore(HWND hWnd, LPARAM lParam)
{
	DWORD idProc = (DWORD)lParam;
	DWORD windowPID;
	(void)::GetWindowThreadProcessId( hWnd, &windowPID );
	if(windowPID == idProc && IsWindow(hWnd) &&IsWindowVisible(hWnd))
	{
		ShowWindow(hWnd, SW_RESTORE);
		OutputDebugString( _T("Restore \n"));
	}
	return TRUE;
}

void CFullCreenDlg::OnBnClickedBtnFifa()
{
	// TODO: Add your control notification handler code here

	FARPROC EnumProcInstance = MakeProcInstance((FARPROC)EnumWindowsProc, AfxGetInstanceHandle());
	EnumWindows((WNDENUMPROC)EnumProcInstance, (LPARAM)this->m_hWnd);
	FreeProcInstance(EnumProcInstance);
}






void CFullCreenDlg::OnBnClickedBtnMinimizepid()
{
	// TODO: Add your control notification handler code here
	//CEdit* edtPID = (CEdit*)GetDlgItem(IDC_EDT_PID);
	CString strPID;
	GetDlgItemText(IDC_EDT_PID,  strPID);
	DWORD idProc = wcstoul(strPID.GetBuffer(), NULL, 0);

	//HANDLE hMainFifa = OpenProcess(PROCESS_ALL_ACCESS, TRUE, idProc);
	idProc = CloseProcessMainThread(idProc);
	EnumWindows(&EnumWindowsProcMinimizeFifa, (LPARAM)idProc);
	
}


void CFullCreenDlg::OnBnClickedBtnRestore()
{
	// TODO: Add your control notification handler code here
	CString strPID;
	GetDlgItemText(IDC_EDT_PID,  strPID);
	DWORD idProc = wcstoul(strPID.GetBuffer(), NULL, 0);
	EnumWindows(&EnumWindowsProcRestore, (LPARAM)idProc);
	
}
