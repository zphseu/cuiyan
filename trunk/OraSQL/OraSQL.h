// OraSQL.h : main header file for the ORASQL application
//

#if !defined(AFX_ORASQL_H__96A33D01_6C37_4FE4_B3A6_611319E2EF74__INCLUDED_)
#define AFX_ORASQL_H__96A33D01_6C37_4FE4_B3A6_611319E2EF74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COraSQLApp:
// See OraSQL.cpp for the implementation of this class
//

class COraSQLApp : public CWinApp
{
public:
	COraSQLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COraSQLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COraSQLApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORASQL_H__96A33D01_6C37_4FE4_B3A6_611319E2EF74__INCLUDED_)
