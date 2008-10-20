// TNSConf.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TNSConf.h"
#include "TNSConfDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTNSConfApp

BEGIN_MESSAGE_MAP(CTNSConfApp, CWinApp)
	//{{AFX_MSG_MAP(CTNSConfApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTNSConfApp construction

CTNSConfApp::CTNSConfApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTNSConfApp object

CTNSConfApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTNSConfApp initialization

BOOL CTNSConfApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTNSConfDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}
