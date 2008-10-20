// DlgReport.cpp : implementation file
//

#include "stdafx.h"
#include "gsoapwzd.h"
#include "DlgReport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgReport dialog


CDlgReport::CDlgReport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgReport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgReport)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgReport)
	DDX_Control(pDX, IDC_LIST, m_ctlList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgReport, CDialog)
	//{{AFX_MSG_MAP(CDlgReport)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgReport message handlers

int CDlgReport::DoModal() 
{
	int nRet = IDCANCEL;

	if (DoCreatePipe() < 0)
		return nRet;

	THREADINFO info;
	info.strArgs = sArgs;
	
	CEvent theThreadEvent(FALSE, TRUE); 
	info.pTermThreadEvent = &theThreadEvent;
	info.pView = this;
	
	AfxBeginThread(LaunchAndWait, &info);
	m_pReadThread = AfxBeginThread( (AFX_THREADPROC)ReadPipeThreadProc, (LPVOID)this );
	WaitForSingleObject(theThreadEvent.m_hObject, INFINITE);
		
	nRet = CDialog::DoModal();

	DoDestroyPipe();

	return nRet;
}

UINT CDlgReport::ReadPipeThreadProc(LPVOID pParam)
{
	DWORD dwRead;
#define BUFSIZE 1024
	TCHAR chBuf[BUFSIZE];
	CString str, strLine;
	int n;
	CDlgReport* pMainWnd = (CDlgReport*) pParam;
	CStringArray& arInfo = pMainWnd->m_arInfo;
	arInfo.RemoveAll();
	
	for( ;1; )
	{ 
		if( !ReadFile( pMainWnd->hChildStdoutRd, chBuf, 
			BUFSIZE, &dwRead, NULL) || dwRead == 0) 
			break;
		chBuf[dwRead/sizeof(TCHAR)] = _T('\0');
		str = chBuf;
		
		while ((n = str.Find(_T("\r\n"))) >= 0)
		{
			strLine = str.Left(n);
			str.Delete(0, n + 2);
			str.TrimLeft();
			str.TrimRight();
			arInfo.Add(strLine);
		}
	}
	
	pMainWnd->m_pReadThread = NULL;
	return 1;
}

UINT CDlgReport::LaunchAndWait(LPVOID pParam)
{
	THREADINFO* pThreadInfo = (THREADINFO*) pParam;
	
	PROCESS_INFORMATION processInfo;
	STARTUPINFO startInfo;
	GetStartupInfo( &startInfo );   	
	startInfo.dwFlags = STARTF_USESTDHANDLES;
	startInfo.hStdOutput = pThreadInfo->pView->hChildStdoutWr;
	startInfo.hStdError = pThreadInfo->pView->hChildStdoutWr;
	
	if (!CreateProcess(NULL, (LPTSTR)(LPCTSTR)pThreadInfo->strArgs, NULL, NULL, TRUE, 
		DETACHED_PROCESS,
		NULL, NULL, &startInfo, &processInfo))
	{
		pThreadInfo->pTermThreadEvent->SetEvent();
		AfxMessageBox(_T("Can not run soapcpp2.exe!"));
		return -1;
	}
	else
	{
		pThreadInfo->pView->dwProcessId = processInfo.dwProcessId;
		// 子进程创建完毕，重置系统标准输入输出
		if( !SetStdHandle(STD_OUTPUT_HANDLE, pThreadInfo->pView->hSaveStdout) )
			AfxMessageBox( _T("Re-redirecting Stdout failed\n") );
		HANDLE hThreads[2];
		hThreads[0] = pThreadInfo->pTermThreadEvent->m_hObject;
		hThreads[1] = processInfo.hProcess;
		DWORD dwIndex = WaitForMultipleObjects(2, hThreads, FALSE, INFINITE);
		CloseHandle(processInfo.hThread);
		CloseHandle(processInfo.hProcess);
		pThreadInfo->pView->dwProcessId = DWORD(-1);
		pThreadInfo->pTermThreadEvent->SetEvent();
	}
	
    return 0;
}

int CDlgReport::DoCreatePipe()
{
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	HANDLE hTemp = NULL;
	
	// 重定向子进程的标准输出...
	// 保存当前标准输出的句柄
	hSaveStdout = GetStdHandle(STD_OUTPUT_HANDLE);  
	//为子进程的标准输出创建一个管道
	if( !CreatePipe( &hTemp, &hChildStdoutWr, &saAttr, 0) )
	{
		AfxMessageBox( _T("Stdout pipe creation failed\n") );
		return -1;
	}
	// 设置一个写句柄到管道，使之成为标准输出
	if( !SetStdHandle(STD_OUTPUT_HANDLE, hChildStdoutWr) )
	{
		AfxMessageBox( _T("Redirecting STDOUT failed\n") );
		return -1;
	}   
	// 创建不可继承的读句柄并关闭可继承的读句柄 
	
    if(! DuplicateHandle( GetCurrentProcess(), hTemp,
        GetCurrentProcess(),  &hChildStdoutRd , 
		0,  FALSE,
        DUPLICATE_SAME_ACCESS ) )
	{
		AfxMessageBox( _T("DuplicateHandle failed\n") );
        return -1;
	}
	CloseHandle( hTemp );
	
	return 0;
}

void CDlgReport::DoDestroyPipe()
{
	CloseHandle( hChildStdoutWr );
	CloseHandle( hChildStdoutRd );
	
	if( dwProcessId != DWORD(-1) )
	{
		HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwProcessId );
		if( hProcess )
		{
			TerminateProcess( hProcess, 0 );
			CloseHandle( hProcess );
		}
	}
	if( m_pReadThread )
	{
		TerminateThread( m_pReadThread->m_hThread, 0 );
		delete m_pReadThread;
	}
}

BOOL CDlgReport::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetTimer(0, 20, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgReport::OnTimer(UINT nIDEvent) 
{
	while (m_arInfo.GetSize() > 0)
	{
		m_ctlList.AddString(m_arInfo[0]);
		m_arInfo.RemoveAt(0);
	}

	CDialog::OnTimer(nIDEvent);
}
