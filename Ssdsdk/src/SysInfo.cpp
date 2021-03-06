// SysInfo.cpp: implementation of the CSysInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysInfo.h"
#include "CPUDetails.h"
#include "ARACrypt.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// enum {
// 	VER_SUITE_SMALLBUSINESS = 0x1,
// 	VER_SUITE_ENTERPRISE = 0x2,
// 	VER_SUITE_BACKOFFICE = 0x4,
// 	VER_SUITE_COMMUNICATIONS = 0x8,
// 	VER_SUITE_TERMINAL = 0x10,
// 	VER_SUITE_SMALLBUSINESS_RESTRICTED = 0x20,
// 	VER_SUITE_EMBEDDEDNT = 0x40,
// 	VER_SUITE_DATACENTER = 0x80,
// 	VER_SUITE_SINGLEUSERTS = 0x100,
// 	VER_SUITE_PERSONAL = 0x200,
// 	VER_SUITE_BLADE = 0x400
// };
// 
// enum {
// 	VER_NT_WORKSTATION = 1,
// 	VER_NT_DOMAIN_CONTROLLER = 2,
// 	VER_NT_SERVER = 3
// };

BOOL CSysInfo::GetDiskInfo()
{
	TCHAR	szSysName[MAX_PATH];
	TCHAR	szVolName[MAX_PATH];
	TCHAR	szSysDir[MAX_PATH];
	DWORD	dwMaxLen;
	DWORD	dwVolSeri;
	DWORD	sysflag;

	GetSystemDirectory(szSysDir, MAX_PATH);
	szSysName[4] = 0;
	GetVolumeInformation(szSysDir, szVolName, MAX_PATH, &dwVolSeri, 
		&dwMaxLen, &sysflag, szSysName, MAX_PATH);

	m_szDiskInfo.Format(_T("%X"), dwVolSeri);
	m_szDiskInfo += _T(" ");
	m_szDiskInfo += szSysName;
	
	return TRUE;
}

BOOL CSysInfo::GetCPUInfo()
{
	DWORD cpuid_result = 0;
	BOOL bSN = FALSE;
	
	CCPUDetails CPU;
	char sVendor[13] = "Unknown  cpu";
	CString sBrand;
	CString sBrandID = "Not available";
	DWORD dwFMS = 0;
	DWORD dwBrand = 0;
	DWORD dwFamily, dwStepping, dwModel, dwExModel, dwExFamily, dwType = 0;
	LONG nSpeedvar = 0;

	TCHAR sVendorString[MAX_PATH];
	TCHAR sFamily[MAX_PATH];
	TCHAR sModel[MAX_PATH];
	TCHAR sStepping[MAX_PATH];
	TCHAR sType[MAX_PATH];
	TCHAR sBrandString[MAX_PATH];
	TCHAR sBrandIDString[MAX_PATH];
	TCHAR sProcessorNameString[MAX_PATH];
	TCHAR sCacheString[MAX_PATH];
	TCHAR sSerialNr[MAX_PATH];
	TCHAR sCPU[MAX_PATH];

	__asm
	{
		xor eax, eax;
		mov eax, 01h;
		CPUID;
		mov [cpuid_result], edx;
	}
	if(((cpuid_result>>18)&1) == 1)
	{
		bSN = TRUE;
	}

	__asm
	{
		mov eax,0;
		CPUID;
		mov dword ptr [sVendor],ebx;
		mov dword ptr [sVendor+4],edx;
		mov dword ptr [sVendor+8],ecx;
	}
	
	sBrand = _T("Unknown");
	sBrandID = _T("Not available");
	
	strcpy(sBrandIDString, sBrandID);
	strcpy(sVendorString, sVendor);
	if(strcmp(sVendor, "GenuineIntel") == 0)
		sBrand = "Intel";
	if(strcmp(sVendor, "UMC UMC UMC") == 0)
		sBrand = "UMC";
	if(strcmp(sVendor, "AuthenticAMD") == 0)
		sBrand = "AMD";
	if(strcmp(sVendor, "CyrixInstead") == 0)
		sBrand = "Cyrix";
	if(strcmp(sVendor, "NexGenDriven") == 0)
		sBrand = "NexGen";
	if(strcmp(sVendor, "CentaurHauls") == 0)
		sBrand = "Centaur";
	if(strcmp(sVendor, "RiseRiseRise") == 0)
		sBrand = "Rise";
	if(strcmp(sVendor, "GenuineTMx86") == 0)
		sBrand = "Transmeta";
	strcpy(sBrandString, sBrand);
	DWORD dwCache[4] = {0, 0, 0, 0};
	BYTE dwCacheInfo[16];
	memset(dwCacheInfo, 0, sizeof(dwCacheInfo));
	__asm
	{
		mov eax,1;
		CPUID;
		mov dwFMS, eax;
		mov dwBrand, ebx;
	}
	if(sBrand == "Intel")
	{
		switch((dwBrand >> 0) & 0xff)
		{
			case 0x1:
				sBrandID = "Intel� Celeron� processor";
				break;
			case 0x2:
				sBrandID = "Intel� Pentium� III processor";
				break;
			case 0x3:
				if(dwFMS == 0x000006B1)
				{
					sBrandID = "Intel� Celeron� processor";
					break;
				}
				else
				{
					sBrandID = "Intel� Pentium� III Xeon� processor";
					break;
				}
			case 0x4:
				sBrandID = "Intel� Pentium� III processor";
				break;
			case 0x6:
				sBrandID = "Mobile Intel� Pentium� III Processor-M";
			case 0x7:
				sBrandID = "Mobile Intel� Celeron� processor";
			case 0x8:
				if(dwFMS >= 0x00000F13)
				{
					sBrandID = "Intel� Genuine processor";
					break;
				}
				else
				{
					sBrandID = "Intel� Pentium� 4 processor";
					break;
				}
			case 0x9:
				sBrandID = "Intel� Pentium� 4 processor";
				break;
			case 0xa:
				sBrandID = "Intel� Celeron� Processor";
				break;
			case 0xb:
				if(dwFMS < 0x00000F13)
				{
					sBrandID = "Intel� Xeon� processor MP";
					break;
				}
				else
				{
					sBrandID = "Intel� Xeon� processor";
					break;
				}
			case 0xc:
				sBrandID = "Intel� Xeon� processor MP";
				break;
			case 0xe:
				if(dwFMS < 0x00000F13)
				{
					sBrandID = "Intel� Xeon� processor";
					break;
				}
				else
				{
					sBrandID = "Mobile Intel� Pentium� 4 processor�M";
					break;
				}
			case 0xf:
				sBrandID = "Mobile Intel� Celeron� Processor";
				break;
			default:
				sBrandID = "Not available";
		}
		strcpy(sBrandIDString, sBrandID);
	}
	dwModel = (dwFMS >> 4) & 0xf;
	dwFamily = (dwFMS >> 8) & 0xf;
	dwStepping = (dwFMS >> 0) & 0xf;
	dwType = (dwFMS >> 12) & 0xf;
	ltoa(dwFamily, sFamily, 10);
	ltoa(dwModel, sModel, 10);
	ltoa(dwStepping, sStepping, 10);
	CString st;
	switch(dwType)
	{
	case 0:
		st = "Primary processor";
		strcpy(sType, st);
		break;
	case 1:
		st = "Overdrive processor";
		strcpy(sType, st);
		break;
	case 2:
		st = "Secondary processor (for MP)";
		strcpy(sType, st);
		break;
	default:
		st = "Unknown";
		strcpy(sType, st);
		break;
	}
	DWORD dw1, dw2, dw3 = 0;
	CString sCache;
	if(sBrand == "AMD")
	{
		CString sCacheAMD;
		sCacheAMD = CPU.GetL1CacheAMD() + "\n" + CPU.GetL2CacheAMD();
		strcpy(sCacheString, sCacheAMD);
	}
	if(sBrand == "Intel")
	{
		if(!bSN)
		{
			strcpy(sSerialNr, "Not available");
		}
		else
		{
			__asm
			{
				mov eax, 01h;
				CPUID;
				mov [dw1], eax;
				mov eax, 03h;
				CPUID;
				mov [dw2], edx;
				mov [dw3], ecx;
			}
			CString x;
			x.Format("%04X-%04X-%04X-%04X-%04X-%04X", HIWORD(dw1), LOWORD(dw1), HIWORD(dw2), 
				LOWORD(dw2), HIWORD(dw3), LOWORD(dw3));
			strcpy(sSerialNr, x);
		}
		__asm
		{
			mov eax, 2;
			CPUID;
			cmp al, 1;
			jne nocache;
			mov dword ptr [dwCache], eax;
			mov dword ptr [dwCache + 4], ebx;
			mov dword ptr [dwCache + 8], ecx;
			mov dword ptr [dwCache + 12], edx;
			nocache:
		}
//		if(LOBYTE(LOWORD(dwCache[0])) != 1)
//			GetDlgItem(IDC_STATIC_CACHE)->SetWindowText("No cache?");
		BYTE nReadByte;
		for(int i = 1; i < 16; i++)
		{
			nReadByte = ((BYTE *) dwCache)[i];
			switch(nReadByte)
			{
				case 0x1:
					dwCacheInfo[i] = 0x1;
					sCache = sCache + "\ncode TLB, 4K pages, 4 ways, 32 entries";
					break;
				case 0x2:
					dwCacheInfo[i] = 0x2;
					sCache = sCache + "\ncode TLB, 4M pages, fully, 2 entries";
					break;
				case 0x3:
					dwCacheInfo[i] = 0x3;
					sCache = sCache + "\ndata TLB, 4K pages, 4 ways, 64 entries";
					break;
				case 0x4:
					dwCacheInfo[i] = 0x4;
					sCache = sCache + "\ndata TLB, 4M pages, 4 ways, 8 entries";
					break;
				case 0x6:
					dwCacheInfo[i] = 0x6;
					sCache = sCache + "\ncode L1 cache, 8 KB, 4 ways, 32 byte lines";
					break;
				case 0x8:
					dwCacheInfo[i] = 0x8;
					sCache = sCache + "\ncode L1 cache, 16 KB, 4 ways, 32 byte lines";
					break;
				case 0xa:
					dwCacheInfo[i] = 0xa;
					sCache = sCache + "\ndata L1 cache, 8 KB, 2 ways, 32 byte lines";
					break;
				case 0xc:
					dwCacheInfo[i] = 0xc;
					sCache = sCache + "\ndata L1 cache, 16 KB, 4 ways, 32 byte lines";
					break;
				case 0x10:
					dwCacheInfo[i] = 0x10;
					sCache = sCache + "\ndata L1 cache, 16 KB, 4 ways, 32 byte lines (IA-64)";
					break;
				case 0x15:
					dwCacheInfo[i] = 0x15;
					sCache = sCache + "\ndata L1 cache, 16 KB, 4 ways, 32 byte lines (IA-64)";
					break;
				case 0x1a:
					dwCacheInfo[i] = 0x1a;
					sCache = sCache + "\ncode and data L2 cache, 96 KB, 6 ways, 64 byte lines (IA-64)";
					break;
				case 0x22:
					dwCacheInfo[i] = 0x22;
					sCache = sCache + "\ncode and data L3 cache, 512 KB, 4 ways, 64 byte lines, sectored";
					break;
				case 0x23:
					dwCacheInfo[i] = 0x23;
					sCache = sCache + "\ncode and data L3 cache, 1024 KB, 8 ways, 64 byte lines, sectored";
					break;
				case 0x25:
					dwCacheInfo[i] = 0x25;
					sCache = sCache + "\ncode and data L3 cache, 2048 KB, 8 ways, 64 byte lines, sectored";
					break;
				case 0x29:
					dwCacheInfo[i] = 0x29;
					sCache = sCache + "\ncode and data L3 cache, 4096 KB, 8 ways, 64 byte lines, sectored";
					break;
				case 0x39:
					dwCacheInfo[i] = 0x39;
					sCache = sCache + "\ncode and data L2 cache, 128 KB, 4 ways, 64 byte lines, sectored";
					break;
				case 0x3c:
					dwCacheInfo[i] = 0x3c;
					sCache = sCache + "\ncode and data L2 cache, 256 KB, 4 ways, 64 byte lines, sectored";
					break;
				case 0x40:
					dwCacheInfo[i] = 0x40;
					sCache = sCache + "\nno integrated L2 cache";
					break;
				case 0x41:
					dwCacheInfo[i] = 0x41;
					sCache = sCache + "\ncode and data L2 cache, 128 KB, 4 ways, 32 byte lines";
					break;
				case 0x42:
					dwCacheInfo[i] = 0x42;
					sCache = sCache + "\ncode and data L2 cache, 256 KB, 4 ways, 32 byte lines";
					break;
				case 0x43:
					dwCacheInfo[i] = 0x43;
					sCache = sCache + "\ncode and data L2 cache, 512 KB, 4 ways, 32 byte lines";
					break;
				case 0x44:
					dwCacheInfo[i] = 0x44;
					sCache = sCache + "\ncode and data L2 cache, 1024 KB, 4 ways, 32 byte lines";
					break;
				case 0x45:
					dwCacheInfo[i] = 0x45;
					sCache = sCache + "\ncode and data L2 cache, 2048 KB, 4 ways, 32 byte lines";
					break;
				case 0x50:
					dwCacheInfo[i] = 0x50;
					sCache = sCache + "\ncode TLB, 4K/4M/2M pages, fully, 64 entries";
					break;
				case 0x51:
					dwCacheInfo[i] = 0x51;
					sCache = sCache + "\ncode TLB, 4K/4M/2M pages, fully, 128 entries";
					break;
				case 0x52:
					dwCacheInfo[i] = 0x52;
					sCache = sCache + "\ncode TLB, 4K/4M/2M pages, fully, 256 entries";
					break;
				case 0x5b:
					dwCacheInfo[i] = 0x5b;
					sCache = sCache + "\ndata TLB, 4K/4M pages, fully, 64 entries";
					break;
				case 0x5c:
					dwCacheInfo[i] = 0x5c;
					sCache = sCache + "\ndata TLB, 4K/4M pages, fully, 128 entries";
					break;
				case 0x5d:
					dwCacheInfo[i] = 0x5d;
					sCache = sCache + "\ndata TLB, 4K/4M pages, fully, 256 entries";
					break;
				case 0x66:
					dwCacheInfo[i] = 0x66;
					sCache = sCache + "\ndata L1 cache, 8 KB, 4 ways, 64 byte lines, sectored";
					break;
				case 0x67:
					dwCacheInfo[i] = 0x67;
					sCache = sCache + "\ndata L1 cache, 16 KB, 4 ways, 64 byte lines, sectored";
					break;
				case 0x68:
					dwCacheInfo[i] = 0x68;
					sCache = sCache + "\ndata L1 cache, 32 KB, 4 ways, 64 byte lines, sectored";
					break;
				case 0x70:
					dwCacheInfo[i] = 0x70;
					sCache = sCache + "\ntrace L1 cache, 12 K�OPs, 8 ways";
					break;
				case 0x71:
					dwCacheInfo[i] = 0x71;
					sCache = sCache + "\ntrace L1 cache, 16 K�OPs, 8 ways";
					break;
				case 0x72:
					dwCacheInfo[i] = 0x72;
					sCache = sCache + "\ntrace L1 cache, 32 K�OPs, 8 ways";
					break;
				case 0x77:
					dwCacheInfo[i] = 0x77;
					sCache = sCache + "\ncode L1 cache, 16 KB, 4 ways, 64 byte lines, sectored (IA-64)";
					break;
				case 0x79:
					dwCacheInfo[i] = 0x79;
					sCache = sCache + "\ncode and data L2 cache, 128 KB, 8 ways, 64 byte lines, sectored";
					break;
				case 0x7a:
					dwCacheInfo[i] = 0x7a;
					sCache = sCache + "\ncode and data L2 cache, 256 KB, 8 ways, 64 byte lines, sectored";
					break;
				case 0x7b:
					dwCacheInfo[i] = 0x7b;
					sCache = sCache + "\ncode and data L2 cache, 512 KB, 8 ways, 64 byte lines, sectored";
					break;
				case 0x7c:
					dwCacheInfo[i] = 0x7c;
					sCache = sCache + "\ncode and data L2 cache, 1024 KB, 8 ways, 64 byte lines, sectored";
					break;
				case 0x7e:
					dwCacheInfo[i] = 0x7e;
					sCache = sCache + "\ncode and data L2 cache, 256 KB, 8 ways, 128 byte lines, sectored";
					break;
				case 0x81:
					dwCacheInfo[i] = 0x81;
					sCache = sCache + "\ncode and data L2 cache, 128 KB, 8 ways, 32 byte lines";
					break;
				case 0x82:
					dwCacheInfo[i] = 0x82;
					sCache = sCache + "\ncode and data L2 cache, 256 KB, 8 ways, 32 byte lines";
					break;
				case 0x83:
					dwCacheInfo[i] = 0x83;
					sCache = sCache + "\ncode and data L2 cache, 512 KB, 8 ways, 32 byte lines";
					break;
				case 0x84:
					dwCacheInfo[i] = 0x84;
					sCache = sCache + "\ncode and data L2 cache, 1024 KB, 8 ways, 32 byte lines";
					break;
				case 0x85:
					dwCacheInfo[i] = 0x85;
					sCache = sCache + "\ncode and data L2 cache, 2048 KB, 8 ways, 32 byte lines";
					break;
				case 0x88:
					dwCacheInfo[i] = 0x88;
					sCache = sCache + "\ncode and data L3 cache, 2048 KB, 4 ways, 64 byte lines (IA-64)";
					break;
				case 0x89:
					dwCacheInfo[i] = 0x89;
					sCache = sCache + "\ncode and data L3 cache, 4096 KB, 4 ways, 64 byte lines (IA-64)";
					break;
				case 0x8a:
					dwCacheInfo[i] = 0x8a;
					sCache = sCache + "\ncode and data L3 cache, 8192 KB, 4 ways, 64 byte lines (IA-64)";
					break;
				case 0x8d:
					dwCacheInfo[i] = 0x8d;
					sCache = sCache + "\ncode and data L3 cache, 3096 KB, 12 ways, 128 byte lines (IA-64)";
					break;
				case 0x90:
					dwCacheInfo[i] = 0x90;
					sCache = sCache + "\ncode TLB, 4K...256M pages, fully, 64 entries (IA-64)";
					break;
				case 0x96:
					dwCacheInfo[i] = 0x96;
					sCache = sCache + "\ndata L1 TLB, 4K...256M pages, fully, 32 entries (IA-64)";
					break;
				case 0x9b:
					dwCacheInfo[i] = 0x9b;
					sCache = sCache + "\ndata L2 TLB, 4K...256M pages, fully, 96 entries (IA-64)";
					break;
			}
		}
		sCache = sCache.Right(sCache.GetLength() - 1);
		strcpy(sCacheString, sCache);
	}
	CString sc = CPU.GetCPUName(dwModel, dwFamily, dwStepping, 
													dwType, dwExModel, dwExFamily, 
													sBrand, dwCacheInfo, nSpeedvar);
	strcpy(sCPU, sc);
	CString spn = CPU.GetProcessorNameString();
	strcpy(sProcessorNameString, spn);
	
	CString szTmp;
	szTmp = sCPU;			szTmp.TrimRight();
	m_szCPUInfo += CString(_T("CPU: ")) + szTmp;
	szTmp = sVendor;		szTmp.TrimRight();
	m_szCPUInfo += CString(_T("Vendor: ")) + szTmp;
	szTmp = sBrandString;	szTmp.TrimRight();
	m_szCPUInfo += CString(_T("Brand: ")) + szTmp;
	szTmp = sBrandIDString;	szTmp.TrimRight();
	m_szCPUInfo += CString(_T("Brand ID: ")) + szTmp;
	szTmp = sProcessorNameString;	szTmp.TrimRight();
	m_szCPUInfo += CString(_T("ProcessorName: ")) + szTmp;
	szTmp = sFamily;		szTmp.TrimRight();
	m_szCPUInfo += CString(_T("Family: ")) + szTmp;
	szTmp = sModel;			szTmp.TrimRight();
	m_szCPUInfo += CString(_T("Model: ")) + szTmp;
	szTmp = sStepping;		szTmp.TrimRight();
	m_szCPUInfo += CString(_T("Stepping: ")) + szTmp;
	szTmp = sType;			szTmp.TrimRight();
	m_szCPUInfo += CString(_T("Type: ")) + szTmp;
	szTmp = sCacheString;	szTmp.TrimRight();
	m_szCPUInfo += CString(_T("Cache: ")) + szTmp;
	szTmp = sSerialNr;		szTmp.TrimRight();
	m_szCPUInfo += CString(_T("Serial Nr: ")) + szTmp;

	return TRUE;
}

CString CSysInfo::GetSysInfo(BOOL inDisk)
{
	GetCPUInfo();
	if (inDisk)		GetDiskInfo();
	return (m_szCPUInfo + m_szDiskInfo);
}
