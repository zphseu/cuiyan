// Controls_Demo.h : main header file for the CONTROLS_DEMO application
//

#if !defined(AFX_CONTROLS_DEMO_H__A7643C64_3F9C_4232_8299_7A27E5A6C4C5__INCLUDED_)
#define AFX_CONTROLS_DEMO_H__A7643C64_3F9C_4232_8299_7A27E5A6C4C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CControls_DemoApp:
// See Controls_Demo.cpp for the implementation of this class
//

class CControls_DemoApp : public CWinApp
{
public:
	CControls_DemoApp();
	HINSTANCE m_hInstance;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControls_DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CControls_DemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLS_DEMO_H__A7643C64_3F9C_4232_8299_7A27E5A6C4C5__INCLUDED_)
