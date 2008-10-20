#if !defined(AFX_PTEMT_H__79591252_7796_48AA_94CA_6FB222B86B72__INCLUDED_)
#define AFX_PTEMT_H__79591252_7796_48AA_94CA_6FB222B86B72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PtEmt.h : main header file for PTEMT.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPtEmtApp : See PtEmt.cpp for implementation.

class CPtEmtApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTEMT_H__79591252_7796_48AA_94CA_6FB222B86B72__INCLUDED)
