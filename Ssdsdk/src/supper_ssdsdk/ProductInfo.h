// ProductInfo.h: interface for the CProductInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCTINFO_H__D1CEDBAC_8423_45DB_AC82_BA81DDAC811E__INCLUDED_)
#define AFX_PRODUCTINFO_H__D1CEDBAC_8423_45DB_AC82_BA81DDAC811E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "version.h"

class CProductInfo  
{
public:
	CString GetProductInfo();
	CString GetName() { return m_szName; }
private:
	CString m_szName;
	CString m_szVersion;
	CString m_szBuild;
	
	MSKVersionInfo m_Version;
};

#endif // !defined(AFX_PRODUCTINFO_H__D1CEDBAC_8423_45DB_AC82_BA81DDAC811E__INCLUDED_)
