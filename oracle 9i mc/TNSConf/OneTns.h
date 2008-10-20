// OneTns.h: interface for the COneTns class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONETNS_H__B317FFB0_B861_41BF_A9AD_F520A94B5770__INCLUDED_)
#define AFX_ONETNS_H__B317FFB0_B861_41BF_A9AD_F520A94B5770__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct COneTns  
{
	enum { TNS, TNSNAME, PROTOCOL, HOST, PORT, SVRNAME, TNSINDEX };
	static LPCTSTR m_lpszTnsPattern;
	CString m_csContext[TNSINDEX];

public:
	CString GetTns();
};

#endif // !defined(AFX_ONETNS_H__B317FFB0_B861_41BF_A9AD_F520A94B5770__INCLUDED_)
