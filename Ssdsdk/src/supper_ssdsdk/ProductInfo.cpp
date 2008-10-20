// ProductInfo.cpp: implementation of the CProductInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProductInfo.h"
#include "ARACrypt.h"
#include "myconfig.h"

CString CProductInfo::GetProductInfo()
{
	if (m_Version.IsError())
	{
		m_szName = theProductName;
		m_szVersion = theProductVersion;
		m_szBuild = theProductBuild;
		
		ASSERT(!m_szName.IsEmpty());
		ASSERT(!m_szVersion.IsEmpty());
	}
	else
	{
		m_szName = m_Version.ProductName();
		m_szVersion = m_Version.ProductVersion();
		m_szBuild = m_Version.SpecialBuild();
	}

	ARACrypt arac;
	CString szLong = m_szName + m_szBuild;
	arac.TransformString(m_szVersion, szLong);
	
	return szLong;
}