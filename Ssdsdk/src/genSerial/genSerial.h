// genSerial.h : main header file for the GENSERIAL application
//

#if !defined(AFX_GENSERIAL_H__7331F1CB_D682_4147_B055_C3BA4C6AFA10__INCLUDED_)
#define AFX_GENSERIAL_H__7331F1CB_D682_4147_B055_C3BA4C6AFA10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGenSerialApp:
// See genSerial.cpp for the implementation of this class
//

class CGenSerialApp : public CWinApp
{
public:
	CGenSerialApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenSerialApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGenSerialApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENSERIAL_H__7331F1CB_D682_4147_B055_C3BA4C6AFA10__INCLUDED_)
