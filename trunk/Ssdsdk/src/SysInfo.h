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
	BOOL GetDiskInfo();

private:
	CString m_szDiskInfo;	// Disk Volume Serical, + SysName [NTFS, FAT32, ...]
	CString m_szCPUInfo;
public:
	CString GetSysInfo(BOOL inDisk = FALSE);
};

#endif // !defined(AFX_SYSINFO_H__C02FF24F_FF11_4CB3_9B2B_B38B43B3D776__INCLUDED_)
