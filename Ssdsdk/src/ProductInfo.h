// ProductInfo.h: interface for the CProductInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCTINFO_H__D03F3772_AD15_4282_8491_4E7F83BC3A5F__INCLUDED_)
#define AFX_PRODUCTINFO_H__D03F3772_AD15_4282_8491_4E7F83BC3A5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProductInfo  
{
public:
	CProductInfo();
	const CString GetProductName()	{ return m_ProductName; }
	const CString GetCompanyName()	{ return m_Company; }
	const CString GetVersion()		{ return m_Version; }
	const CString GetSpecBuild()	{ return m_SpecBuild; }

protected:
	CString	m_ProductName;
	CString m_Company;
	CString m_Version;
	CString m_SpecBuild;
};

#endif // !defined(AFX_PRODUCTINFO_H__D03F3772_AD15_4282_8491_4E7F83BC3A5F__INCLUDED_)
