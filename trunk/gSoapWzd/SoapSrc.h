// SoapSrc.h: interface for the CSoapSrc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPSRC_H__6375D1FB_F980_4517_8FEC_51F3D7E4E4DC__INCLUDED_)
#define AFX_SOAPSRC_H__6375D1FB_F980_4517_8FEC_51F3D7E4E4DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SoapCpp2View.h"
class CSoapSrc
{
public:

public:
	int DoModal(CSoapcpp2View* pView);

protected:
	BOOL SaveFile(LPCTSTR lpszFileName, BOOL bSrc = FALSE, LPCTSTR prefix = NULL);
	BOOL LoadFile(LPCTSTR lpszFileName, BOOL bSrc = FALSE, LPCTSTR prefix = NULL);
	LPCTSTR GetFilePath(LPCTSTR lpszName, BOOL bSrc, LPCTSTR prefix = NULL);
	void GetNsMaps();
	CSoapcpp2View*	m_pView;

	BOOL CreateCltpsFile();
	BOOL QueryFunction(LPCTSTR lpszStart, LPCTSTR lpszEnd);
	void ReplaceString(LPCTSTR lpszOld, LPCTSTR lpszNew);
	void ReplaceDspString();
	CString SaveResFile(HINSTANCE hInst, LPCTSTR name, LPCTSTR type, LPCTSTR filename = NULL);
private:
	void Do_Clt_Project();
	void Do_Svr_Project();
	void Do_Svr_c();
	void Do_Clt_c();
	void Do_Server_c();
	void Do_Client_c();
	void Do_Stub_h();
	void Do_Proxy_h();

	CStringArray	m_strArray;
	CString			m_csNsMaps;
};

#endif // !defined(AFX_SOAPSRC_H__6375D1FB_F980_4517_8FEC_51F3D7E4E4DC__INCLUDED_)
