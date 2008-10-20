// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__8C92FDC1_0603_4E0A_B658_E2CC68DC2036__INCLUDED_)
#define AFX_STDAFX_H__8C92FDC1_0603_4E0A_B658_E2CC68DC2036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#pragma warning( push )
#pragma warning( disable:4146 )
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename ("EOF", "adoEOF")
#import <msxml.dll> named_guids
using namespace MSXML;
#pragma warning( pop )
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8C92FDC1_0603_4E0A_B658_E2CC68DC2036__INCLUDED)
