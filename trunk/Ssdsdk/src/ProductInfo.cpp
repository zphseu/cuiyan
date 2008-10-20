// ProductInfo.cpp: implementation of the CProductInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProductInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#pragma comment(lib, "Version.lib")

CProductInfo::CProductInfo()
{
	TCHAR name[_MAX_PATH];
	if (AfxGetApp())
		GetModuleFileName(AfxGetApp()->m_hInstance, name, sizeof(name));
	else
		GetModuleFileName(NULL, name, sizeof(name));
	
	m_ProductName = name;

	m_Company = _T("");
	m_ProductName = m_ProductName.Right(m_ProductName.GetLength() - m_ProductName.ReverseFind('\\') - 1);
	m_ProductName = m_ProductName.Left(m_ProductName.Find('.'));

	void * VerData = NULL;
	try 
	{		
		DWORD   hInfo;
		DWORD   dwLen;
		dwLen = GetFileVersionInfoSize(name, &hInfo);
		
		if (dwLen == 0)
			throw(0); //AfxThrowUserException();
		
		VerData = (void *) new char[dwLen];
		if (VerData == NULL)
			throw(0); //AfxThrowMemoryException();
		
		GetFileVersionInfo(name, hInfo,  dwLen, VerData);
		
		struct {
			WORD    first;
			WORD    second;
		} *lpBuffer;
		
		VerQueryValue(VerData, _T("\\VarFileInfo\\Translation"),
            (LPVOID*) &lpBuffer,(unsigned int *) &dwLen);
		
		if (dwLen==0)
			throw(0); //AfxThrowUserException();
		
		wsprintf(name, _T("\\StringFileInfo\\%04x%04x\\"),
			lpBuffer->first, lpBuffer->second);
		
		unsigned int    uSize;
		LPCTSTR         pBuffer;
		CString sSubBlockHead(name);
		CString sBlock = sSubBlockHead + _T("ProductName"); 		
		if ( VerQueryValue(VerData, (char *)((LPCTSTR) sBlock), (void**)&pBuffer, &uSize) )
			m_ProductName = pBuffer;
		sBlock = sSubBlockHead + _T("CompanyName");
		if ( VerQueryValue(VerData, (char *)((LPCTSTR) sBlock), (void**)&pBuffer, &uSize) )
			m_Company = pBuffer;
		sBlock = sSubBlockHead + _T("ProductVersion");
		if ( VerQueryValue(VerData, (char *)((LPCTSTR) sBlock), (void**)&pBuffer, &uSize) )
			m_Version = pBuffer;
		sBlock = sSubBlockHead + _T("ProductVersion");
		if ( VerQueryValue(VerData, (char *)((LPCTSTR) sBlock), (void**)&pBuffer, &uSize) )
			m_Version = pBuffer;
		sBlock = sSubBlockHead + _T("SpecialBuild");
		if ( VerQueryValue(VerData, (char *)((LPCTSTR) sBlock), (void**)&pBuffer, &uSize) )
			m_SpecBuild = pBuffer;
		
	}
	catch (int) {
		;
	}

	if (VerData) 
		delete VerData;
}

