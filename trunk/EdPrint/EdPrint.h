#if !defined(AFX_EDPRINT_H__DAFF6633_D355_483F_A4A2_99200F7DB7D3__INCLUDED_)
#define AFX_EDPRINT_H__DAFF6633_D355_483F_A4A2_99200F7DB7D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// EdPrint.h : main header file for EDPRTCTRL.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEdPrintApp : See EdPrint.cpp for implementation.

class CEdPrintApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;
extern HDC GetPrintHDC(COleControl* pCtrl, LPCTSTR lpszPrinterName);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDPRINT_H__DAFF6633_D355_483F_A4A2_99200F7DB7D3__INCLUDED)
