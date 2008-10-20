// CPUDetails.h: interface for the CCPUDetails class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPUDETAILS_H__EDA256D3_C475_4780_AFD3_77BB33DA773A__INCLUDED_)
#define AFX_CPUDETAILS_H__EDA256D3_C475_4780_AFD3_77BB33DA773A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCPUDetails  
{
public:
	CString GetCPUFeatures();
	CString DetectSpeed();
	CCPUDetails();
	virtual ~CCPUDetails();
	CString GetVendor();
	DWORD dwFamily, dwStepping, dwModel;

	BOOL IsL2Cache(BYTE nCache, BYTE nCacheInfo[16]);
	CString GetProcessorNameString();
	CString GetL2CacheAMD();
	CString GetL1CacheAMD();
	CString GetCPUName(	DWORD dwModel, 
								DWORD dwFamily, 
								DWORD dwStepping, 
								DWORD dwType, 
								DWORD dwExModel, 
								DWORD dwExFamily, 
								LPCSTR sBrand,
								BYTE nCacheInfo[16], 
								LONG nSpeed);

private:
};

#endif // !defined(AFX_CPUDETAILS_H__EDA256D3_C475_4780_AFD3_77BB33DA773A__INCLUDED_)
