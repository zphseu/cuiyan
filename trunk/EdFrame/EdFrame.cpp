// Edvfc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "EdFrame.h"
#include "MainFrm.h"
#include <ssdsdk.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdFrame

BEGIN_MESSAGE_MAP(CEdFrame, CWinApp)
	//{{AFX_MSG_MAP(CEdFrame)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdFrame construction

CEdFrame::CEdFrame()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEdFrame object

CEdFrame theApp;
/////////////////////////////////////////////////////////////////////////////
// CEdFrame initialization

BOOL CEdFrame::InitInstance()
{
	if (!CHECKVALIDATE)
		return FALSE;
	
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey(_T("Edson"));
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	if (m_pDocManager)
		RegisterShellFileTypes(TRUE);

	return TRUE;
}

// App command to run the dialog
void CEdFrame::OnAppAbout()
{
	CDialog aboutDlg(IDD_ABOUTBOX);
	aboutDlg.DoModal();
}
