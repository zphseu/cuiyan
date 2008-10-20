#if !defined(AFX_STDAFX_H__C790446F_96F3_4841_B6E9_052457C0F431__INCLUDED_)
#define AFX_STDAFX_H__C790446F_96F3_4841_B6E9_052457C0F431__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxctl.h>         // MFC support for ActiveX Controls
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Comon Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Delete the two includes below if you do not wish to use the MFC
//  database classes

#pragma warning( push )
#pragma warning( disable:4146 )
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename ("EOF", "adoEOF")   
#pragma warning( pop )

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C790446F_96F3_4841_B6E9_052457C0F431__INCLUDED_)
