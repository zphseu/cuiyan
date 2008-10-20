// version.cpp
//      Class MSKVersionInfo
//      Handles accessing the VERSIONINFO resource 
//
//   More complete info is given in Version.h 
//
//
#include <stdafx.h>
#include "Version.h"
#pragma comment(lib, "Version.lib")
//
// MSKVersionInfo ctor
//
// Takes as it's parameter the name of the module to extract 
// the version information from.  If NULL or defaulted,
// get the information from the current EXE.
     
MSKVersionInfo::MSKVersionInfo(LPCTSTR lpszModuleName /* = NULL */)
        : m_VerData(NULL), m_isError(FALSE)
{
    try 
	{
		HMODULE     hModule;
		if (lpszModuleName == NULL) {
			hModule = AfxGetInstanceHandle();
		} else {
			hModule = GetModuleHandle(lpszModuleName);
			if (hModule == NULL)
				throw(0); //AfxThrowUserException();
		}
		
		char    name[_MAX_PATH];
		GetModuleFileName(hModule, name, sizeof(name));
		
		DWORD   hInfo;
		DWORD   dwLen;
		dwLen = GetFileVersionInfoSize(name, &hInfo);
		
		if (dwLen == 0)
			throw(0); //AfxThrowUserException();
		
		m_VerData = (void *) new char[dwLen];
		if (m_VerData == NULL)
			throw(0); //AfxThrowMemoryException();
		
		GetFileVersionInfo(name, hInfo,  dwLen, m_VerData);
		
		struct {
			WORD    first;
			WORD    second;
		} *lpBuffer;
		
		VerQueryValue(m_VerData, "\\VarFileInfo\\Translation",
            (LPVOID*) &lpBuffer,(unsigned int *) &dwLen);
		
		if (dwLen==0)
			throw(0); //AfxThrowUserException();
		
		wsprintf(name, "\\StringFileInfo\\%04x%04x\\", 
			lpBuffer->first, lpBuffer->second);
		m_sSubBlockHead = name;
	}
	catch (int)
	{
		m_isError = TRUE;
	}
}

MSKVersionInfo::~MSKVersionInfo()
{
    delete m_VerData;
}
     
CString MSKVersionInfo::GetValue(CString const sSubBlock)
{
    CString sBlock = m_sSubBlockHead + sSubBlock; 
    CString sRet;
     
    unsigned int    uSize;
    LPCTSTR         lpBuffer;
    BOOL bRet = VerQueryValue(m_VerData, 
                    (char *)((LPCTSTR) sBlock), 
                    (void**)&lpBuffer, &uSize);
     
    if (bRet)
        sRet = lpBuffer;
     
    return sRet;
}
// End of File
