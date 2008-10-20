// genSerial.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "genSerial.h"
#include "genSerialDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenSerialApp

BEGIN_MESSAGE_MAP(CGenSerialApp, CWinApp)
	//{{AFX_MSG_MAP(CGenSerialApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenSerialApp construction

CGenSerialApp::CGenSerialApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGenSerialApp object

CGenSerialApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGenSerialApp initialization

BOOL CGenSerialApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CGenSerialDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
