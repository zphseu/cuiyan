// gSoapWzd.h : main header file for the GSOAPWZD application
//

#if !defined(AFX_GSOAPWZD_H__08C1A207_9942_44CF_ADBD_33999BE1F96C__INCLUDED_)
#define AFX_GSOAPWZD_H__08C1A207_9942_44CF_ADBD_33999BE1F96C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGSoapWzdApp:
// See gSoapWzd.cpp for the implementation of this class
//

class CGSoapWzdApp : public CWinApp
{
public:
	CGSoapWzdApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGSoapWzdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGSoapWzdApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GSOAPWZD_H__08C1A207_9942_44CF_ADBD_33999BE1F96C__INCLUDED_)
