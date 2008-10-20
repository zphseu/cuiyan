// SysInfo.h: interface for the CSysInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSINFO_H__C02FF24F_FF11_4CB3_9B2B_B38B43B3D776__INCLUDED_)
#define AFX_SYSINFO_H__C02FF24F_FF11_4CB3_9B2B_B38B43B3D776__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSysInfo  
{
protected:
	BOOL GetCPUInfo();
	BOOL GetOSInfo();
	BOOL GetDiskInfo();

private:
	CString m_szDiskInfo;	// Disk Volume Serical, + SysName [NTFS, FAT32, ...]
	CString m_szOSInfo;		
			// Name         : Windows 2000 Professional
			// Version      : 5.0
			// Build        : 2195
			// Additional   : Service Pack 2
			// Service Pack : Service Pack 2.0
			// Suites       :
	CString m_szCPUInfo;
public:
	CString GetSysInfo(BOOL inDisk = FALSE);
};

#endif // !defined(AFX_SYSINFO_H__C02FF24F_FF11_4CB3_9B2B_B38B43B3D776__INCLUDED_)
