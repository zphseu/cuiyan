// EdFuncs.h: interface for the CEdFuncs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDFUNCS_H__8680EA37_E18A_4B86_80B2_8AF21ED4E831__INCLUDED_)
#define AFX_EDFUNCS_H__8680EA37_E18A_4B86_80B2_8AF21ED4E831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <Wininet.h>
#include <time.h>
using namespace std;
#ifdef _UNICODE
	#define string wstring
#endif

class CEdFuncs  
{
public:
	HDC		GetPrintHDC(LPCTSTR lpszPrinterName);
	BOOL	GetFile(LPCTSTR lpszFileName, string& strData);
	BOOL	GetHttpPage(LPCTSTR lpszUrl, string& strData);

	BOOL	GetFtpFile(LPCTSTR lpszUrl, string& strData, LPCTSTR lpszUsr = _T("anonymous"), 
		LPCTSTR lpszPwd = _T("EdFuncs@domain.com"), 
		DWORD dwPort = INTERNET_DEFAULT_FTP_PORT);
	
protected:
	void	urlencode(string sIn, string& sOut);
	int		sd(const unsigned long ip, const char* from, const char* machine, const char* msg);
};

#endif // !defined(AFX_EDFUNCS_H__8680EA37_E18A_4B86_80B2_8AF21ED4E831__INCLUDED_)
