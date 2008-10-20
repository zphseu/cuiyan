// OraDB.h: interface for the COraDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORADB_H__751D3C00_DE6E_4A36_BE55_D48CC5D1DE07__INCLUDED_)
#define AFX_ORADB_H__751D3C00_DE6E_4A36_BE55_D48CC5D1DE07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <oci.h>

class COraDB  
{
public:
	void StartLog() { m_csLog.Empty(); };
	LPCTSTR GetLog() { return m_csLog; };	
	HRESULT Close();
	HRESULT Open(LPCTSTR csServer, LPCTSTR csUser, LPCTSTR csPassword);
	COraDB();
	virtual ~COraDB();
	
protected:
	CheckErr( short status );
	CString m_csLog;	// PL/SQL statement log
	char szError[512];
	HRESULT hr;
	OCIEnv* hpEnv;
	OCIServer* hpServer;
	OCIError* hpErr;
	OCISvcCtx* hpContext;
	OCIStmt *hpSelect;
	void Clear();
};

#endif // !defined(AFX_ORADB_H__751D3C00_DE6E_4A36_BE55_D48CC5D1DE07__INCLUDED_)
