// TNSConf.h : main header file for the TNSCONF application
//

#if !defined(AFX_TNSCONF_H__B0F71ADD_05AF_40FD_9481_100850B0A8F4__INCLUDED_)
#define AFX_TNSCONF_H__B0F71ADD_05AF_40FD_9481_100850B0A8F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTNSConfApp:
// See TNSConf.cpp for the implementation of this class
//

//##ModelId=3EE0691B0196
class CTNSConfApp : 
public CWinApp   
{
public:
	//##ModelId=3EE0691B0198
	CTNSConfApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTNSConfApp)
	public:
	//##ModelId=3EE0691B01A5
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTNSConfApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TNSCONF_H__B0F71ADD_05AF_40FD_9481_100850B0A8F4__INCLUDED_)
