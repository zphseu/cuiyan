// CPUDetails.cpp: implementation of the CCPUDetails class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CPUDetails.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCPUDetails::CCPUDetails()
{
//	dwBrand = 0;
//	dwExFamily = 0;
//	dwExModel = 0;
	dwFamily = 0;
//	dwFMS = 0;
	dwModel = 0;
	dwStepping = 0;
//	dwTest = 0;
//	dwType = 0;
//	nSpeed = 0;
//	sBrand = "Unknown";
//	sBrandID = "Not available";
	
}

CCPUDetails::~CCPUDetails()
{

}

CString CCPUDetails::DetectSpeed()
{
	LARGE_INTEGER ulFreq, ulTicks, ulValue, ulStartCounter, ulEAX_EDX;
	if (QueryPerformanceFrequency(&ulFreq)) {
		QueryPerformanceCounter(&ulTicks);
		ulValue.QuadPart = ulTicks.QuadPart + ulFreq.QuadPart;
		__asm RDTSC
		__asm mov ulEAX_EDX.LowPart, EAX
		__asm mov ulEAX_EDX.HighPart, EDX
		ulStartCounter.QuadPart = ulEAX_EDX.QuadPart;
		do {
			QueryPerformanceCounter(&ulTicks);
		} while (ulTicks.QuadPart <= ulValue.QuadPart);
		__asm RDTSC
		__asm mov ulEAX_EDX.LowPart, EAX
		__asm mov ulEAX_EDX.HighPart, EDX
		CString sRes;
		sRes.Format("%d", (DWORD) ((ulEAX_EDX.QuadPart - ulStartCounter.QuadPart) / 1000000));
		//GetDlgItem(IDC_STATIC_SPEED)->SetWindowText(sRes);
		return sRes;
	} else {
		// No high-resolution counter present:
		return "";
	}
}

CString CCPUDetails::GetL1CacheAMD()
{
	CString sTmp = "";
	CString s1 = "";
	DWORD dwEAX, dwEBX, dwECX, dwEDX = 0;
	__asm
	{
		mov eax, 0x80000005;
		CPUID;
		mov dwEAX, eax;
		mov dwEBX, ebx;
		mov dwECX, ecx;
		mov dwEDX, edx;
	}
	sTmp.Format("%d kb code L1 cache, %d line associativity, %d lines per tag, %d bytes line size", 
		((dwEDX >> 24) & 0xff), ((dwEDX >> 16) & 0xff), ((dwEDX >> 8) & 0xff), ((dwEDX >> 0) & 0xff));
	s1 = sTmp;
	sTmp.Format("%d kb data L1 cache, %d line associativity, %d lines per tag, %d bytes line size", 
		((dwECX >> 24) & 0xff), ((dwECX >> 16) & 0xff), ((dwECX >> 8) & 0xff), ((dwECX >> 0) & 0xff));
	s1 = s1 + "\n" + sTmp;
	sTmp.Format("4KB L1 TLB descriptor: %d code entries, %d code associativity, %d data entries, %d data associativity", 
		((dwEBX >> 0) & 0xff), ((dwEBX >> 8) & 0xff), ((dwEBX >> 16) & 0xff), ((dwEBX >> 24) & 0xff));
	s1 = s1 + "\n" + sTmp;
	sTmp.Format("2/4MB L1 TLB descriptor: %d code entries, %d code associativity, %d data entries, %d data associativity", 
		((dwEAX >> 0) & 0xff), ((dwEAX >> 8) & 0xff), ((dwEAX >> 16) & 0xff), ((dwEAX >> 24) & 0xff));
	s1 = s1 + "\n" + sTmp;
	return s1;

}

CString CCPUDetails::GetL2CacheAMD()
{
	CString sTmp = "";
	CString s1 = "";
	DWORD dwEAX, dwEBX, dwECX, dwEDX = 0;
	__asm
	{
		mov eax, 0x80000006;
		CPUID;
		mov dwEAX, eax;
		mov dwEBX, ebx;
		mov dwECX, ecx;
	}
	if((dwFamily == 6) && (dwModel == 3) && (dwStepping == 0)) //check if it's a Duron rev. A0 which reports wrong L2 cache size
	{
		return "unified L2 cache, 64 kb.\nAMD Duron rev A0 - L2 cache reporting bug";
	}
	else
	{
		sTmp.Format("%d kb unified L2 cache, %d line associativity, %d lines per tag, %d bytes line size", 
			((dwECX >> 16) & 0xff), (((dwECX >> 12) & 0xf) * 2), ((dwECX >> 8) & 0xf), ((dwECX >> 0) & 0xff));
		s1 = sTmp;
		sTmp.Format("4KB L2 TLB descriptor: %d code entries, %d code associativity, %d data entries, %d data associativity", 
			((dwEBX >> 0) & 0xfff), ((dwEBX >> 12) & 0xff), ((dwEBX >> 16) & 0xfff), ((dwEBX >> 28) & 0xff));
		s1 = s1 + "\n" + sTmp;
		sTmp.Format("2/4MB L2 TLB descriptor: %d code entries, %d code associativity, %d data entries, %d data associativity", 
			((dwEAX >> 0) & 0xfff), ((dwEAX >> 12) & 0xff), ((dwEAX >> 16) & 0xfff), ((dwEAX >> 28) & 0xff));
		s1 = s1 + "\n" + sTmp;
		return s1;
	}
}

CString CCPUDetails::GetProcessorNameString()
{
	char sNameString1[16];
	char sNameString2[16];
	char sNameString3[16];
	memset(sNameString1, 0, sizeof(sNameString1));
	memset(sNameString2, 0, sizeof(sNameString2));
	memset(sNameString3, 0, sizeof(sNameString3));
	__asm
	{
		mov eax, 0x80000002;
		CPUID;
		mov dword ptr [sNameString1], eax;
		mov dword ptr [sNameString1 + 4], ebx;
		mov dword ptr [sNameString1 + 8], ecx;
		mov dword ptr [sNameString1 + 12], edx;
		mov eax, 0x80000003;
		CPUID;
		mov dword ptr [sNameString2], eax;
		mov dword ptr [sNameString2 + 4], ebx;
		mov dword ptr [sNameString2 + 8], ecx;
		mov dword ptr [sNameString2 + 12], edx;
		mov eax, 0x80000004;
		CPUID;
		mov dword ptr [sNameString3], eax;
		mov dword ptr [sNameString3 + 4], ebx;
		mov dword ptr [sNameString3 + 8], ecx;
		mov dword ptr [sNameString3 + 12], edx;
	}
	if ((sNameString1[0] < 48) || (sNameString1[0]) > 122)
		return "Not available";
	strcat(sNameString1, sNameString2);
	strcat(sNameString1, sNameString3);
	return sNameString1;
}

BOOL CCPUDetails::IsL2Cache(BYTE nCache, BYTE nCacheInfo[])
{
	for(int i = 0; i < 15; i++)
	{
		if(nCacheInfo[i] == nCache)
			return TRUE;
	}
	return FALSE;
}

CString CCPUDetails::GetCPUName(	DWORD dwModel, 
								DWORD dwFamily, 
								DWORD dwStepping, 
								DWORD dwType, 
								DWORD dwExModel, 
								DWORD dwExFamily, 
								LPCSTR sBrand,
								BYTE nCacheInfo[16], 
								LONG nSpeed)
{
	int i;
	BOOL bCeleron = TRUE;
	DWORD dwFMS = 0;
	if(strcmp(sBrand, "Intel") == 0)
	{
		switch(dwFamily)
		{
			case 3:
				return "Intel 386";
				break;
			case 4:		//486s
				switch(dwModel)
				{
					case 0:
						return "Intel i80486DX-25/33";
						break;
					case 1:
						return "Intel i80486DX-50";
						break;
					case 2:
						return "Intel i80486SX";
						break;
					case 3:
						return "Intel i80486DX2";
						break;
					case 4:
						return "Intel i80486SL";
						break;
					case 5:
						return "Intel i80486SX2";
						break;
					case 7:
						return "Intel i80486DX2WB";
						break;
					case 8:
						return "Intel i80486DX4";
						break;
					case 9:
						return "Intel i80486DX4WB";
						break;
					default:
						return "Unknown Intel 486 processor";
				}
				break;
			case 5:		//P5s
				switch(dwModel)
				{
					case 0:
						return "Intel Pentium P5 A-step (Pentium A80501, P5)";
						break;
					case 1:
						switch(dwStepping)
						{
							case 3:
								return "Intel Pentium P5 B1 (FDIV bug)";
								break;
							case 5:
								return "Intel Pentium P5 C1 (FDIV bug)";
								break;
							case 7:
								return "Intel Pentium P5 D1";
								break;
							case 0xa:
								return "Intel Pentium tA0 - P54C overdrive for P5 socket";
								break;
							default:
								return "Intel Pentium P5 (A80501, P5)";
						}
						break;
					case 2:
						switch(dwStepping)
						{
							case 1:
								return "Intel Pentium P54C B1 (FDIV bug)";
								break;
							case 2:
								return "Intel Pentium P54C B3 (FDIV bug)";
								break;
							case 4:
								return "Intel Pentium P54C B5";
								break;
							case 5:
								return "Intel Pentium P54C C2/mA1";
								break;
							case 6:
								return "Intel Pentium P54C E0";
								break;
							case 0xb:
								return "Intel Pentium P54C cB1, mcB1";
								break;
							case 0xc:
								return "Intel Pentium P54C cC0, mcC0, acC0";
								break;
							default:
								return "Intel Pentium P54C (A80502, P54)";
						}
						break;
					case 3:
						switch(dwStepping)
						{
							case 1:
								return "Intel Pentium P24T Overdrive P24T: B1, B2 - version 1.x";
								break;
							case 2:
								return "Intel Pentium P24T Overdrive P24B: C0 - version 2.x";;
								break;
							default:
								return "Intel Pentium P24T Overdrive (PODP5V)";
						}
						break;
					case 4:
						switch(dwStepping)
						{
							case 3:
								return "Intel Pentium P55C with MMX xA3/mxA3/oxA3";
								break;
							case 4:
								return "Intel Pentium P55C with MMX xB1/mxB1";
								break;
							default:
								return "Intel Pentium P55C (with MMX - A80503, P55)";
						}
						break;
					case 5:
						return "Intel 486 DX4 Overdrive";
						break;
					case 6:
						return "Intel P5 Overdrive";
						break;
					case 7:
						switch(dwStepping)
						{
							case 0:
								return "Intel Pentium P54C mA4";
								break;
							default:
								return "Intel Pentium P54C (A80502, P54)";
						}
						break;
					case 8:
						switch(dwStepping)
						{
							case 1:
								return "Intel Pentium P55C 0.25 µm with MMX myA0";
								break;
							default:
								return "Intel Pentium P55C 0.25 µm (with MMX - A80503, P55)";
						}
						break;
					default:
						return "Unknown Intel Pentium P5 processor";
				}
				break;
			case 6:		//P6s, P2s and P3s
				switch(dwModel)
				{
					case 0:
						return "Intel Pentium Pro P6 A-step (A80521, P6)";
						break;
					case 1:
						return "Intel Pentium Pro (B0, C0, sA0, sA1, sB1)"; 
						break;
					case 3:
						return "Intel Pentium II Klamath (tdB0, C0, C1)";
						break;
					case 4:
						return "Intel Pentium II Klamath";
					case 5:
						for(i = 0; i < 16; i++) // 0kb L2 cache
						{
							if(nCacheInfo[i] != 0)
								bCeleron = FALSE;
						}
						if(bCeleron)
							return "Intel Celeron Covington 0.35 µm";
						if(IsL2Cache(0x83, nCacheInfo) |  //512 kb L2 cache
							IsL2Cache(0x7b, nCacheInfo) | 
							IsL2Cache(0x43, nCacheInfo))
							if(nSpeed < 333)
								return "Intel Pentium II Deschutes or Mobile Pentium II Tonga 0.25 µm 266-333";
							else
								return "Intel Pentium II Xeon 400-450";
						if(IsL2Cache(0x3c, nCacheInfo) | //256 kb L2 cache
							IsL2Cache(0x42, nCacheInfo) |
							IsL2Cache(0x7a, nCacheInfo) |
							IsL2Cache(0x7e, nCacheInfo) |
							IsL2Cache(0x82, nCacheInfo))
							if(nSpeed < 400)
								return "Intel Mobile Pentium II PE Dixon 0.25 µm";
							else
								return "Intel Mobile Pentium II PE Dixon 0.18 µm";
						if(IsL2Cache(0x39, nCacheInfo) |  //128 kb L2 Cache
							IsL2Cache(0x41, nCacheInfo) |
							IsL2Cache(0x79, nCacheInfo) |
							IsL2Cache(0x81, nCacheInfo))
							return "Intel Mobile Celeron Dixon /LV 0.18-0.25 µm";
						return "Intel Pentium II Deschutes";
					case 6:
						return "Intel Mendocino 0.28 µm with on-die L2 cache (128 kb)";
					case 7:
						switch(dwStepping)
						{
							case 2:
								return "Intel Pentium II Katmai 0.25 µm";
							case 3:
								return "Intel Pentium II Katmai 0.25 µm";
							default:
								return "Intel Pentium II Katmai";
						}
					case 8:
						if(IsL2Cache(0x39, nCacheInfo) |  //128 kb L2 Cache
							IsL2Cache(0x41, nCacheInfo) |
							IsL2Cache(0x79, nCacheInfo) |
							IsL2Cache(0x81, nCacheInfo))
							return "Intel (Mobile) Celeron Coppermine128 LV/ULV, 0.18 µm" ;
						if(IsL2Cache(0x83, nCacheInfo) |  //512 kb L2 cache
							IsL2Cache(0x7b, nCacheInfo) | 
							IsL2Cache(0x43, nCacheInfo))
							return "Intel Celeron Coppermine128 D0h XBox, 0.18 µm";
						if(IsL2Cache(0x3c, nCacheInfo) | //256 kb L2 cache
							IsL2Cache(0x42, nCacheInfo) |
							IsL2Cache(0x7a, nCacheInfo) |
							IsL2Cache(0x7e, nCacheInfo) |
							IsL2Cache(0x82, nCacheInfo))
							switch(dwStepping)
							{
								case 1:
									return "Intel Pentium III Coppermine, 0.18 µm";
								case 2:
									return "Intel Pentium III Coppermine, 0.18 µm";
								case 3:
									return "Intel Pentium III Coppermine, 0.18 µm";
								case 6:
									return "Intel Pentium III Coppermine128 C0h, 0.18 µm";
								case 0xa:
									return "Intel (Mobile LV/ULV) Pentium III Coppermine128 D0h, 0.18 µm";
							}
						return "Intel (Mobile) Celeron Coppermine128" ;
					case 0xa:
						if(nSpeed < 733)
							return "Intel Pentium III Cascades 0.18 µm";
						else
							return "Intel Pentium III Cascades 0.18 µm or Gallatin 0.13 µm";
					case 0xb:
						if(IsL2Cache(0x3c, nCacheInfo) | //256 kb L2 cache
							IsL2Cache(0x42, nCacheInfo) |
							IsL2Cache(0x7a, nCacheInfo) |
							IsL2Cache(0x7e, nCacheInfo) |
							IsL2Cache(0x82, nCacheInfo))
							return "Intel Pentium III/III-T Tualatin 0.13 µm, 1.13+ GHz";
						if(IsL2Cache(0x83, nCacheInfo) |  //512 kb L2 cache
							IsL2Cache(0x7b, nCacheInfo) | 
							IsL2Cache(0x43, nCacheInfo))
							return "Intel Pentium III-S/III-T/III-M (Mobile) Tualatin 0.13 µm";
				}
				break;
			case 0xa:
				{
					__asm
					{
						mov eax,1;
						CPUID;
						mov dwFMS, eax;
					}
					if((((dwFMS>>20)&0xf) == 0) && (dwFamily == 0xf))
					{
						if(IsL2Cache(0x39, nCacheInfo) |  //128 kb L2 Cache
								IsL2Cache(0x41, nCacheInfo) |
								IsL2Cache(0x79, nCacheInfo) |
								IsL2Cache(0x81, nCacheInfo))
								return "Intel Celeron Willamette (P4)";
						switch(dwModel)
						{
							case 0:
								if(dwStepping < 5)
									return "Intel Pentium IV Willamette ES";
								if((5 < dwStepping) && (dwStepping < 8))
									return "Intel Pentium IV Willamette B2 step";
								if(dwStepping == 0xa)
									return "Intel Pentium IV Willamette C1 step";
							case 1:
								if(dwStepping == 2)
									return "Intel Pentium IV Willamette D0 step";
							case 2:
								if(dwStepping == 4)
									return "Intel Pentium IV Northwood (Mobile) B0 step";
								if(dwStepping == 7)
									return "Intel Pentium IV Northwood C1 step";
						}	
						if(IsL2Cache(0x3c, nCacheInfo) | //256 kb L2 cache
							IsL2Cache(0x42, nCacheInfo) |
							IsL2Cache(0x7a, nCacheInfo) |
							IsL2Cache(0x7e, nCacheInfo) |
							IsL2Cache(0x82, nCacheInfo))
							{
							if(IsL2Cache(0x23, nCacheInfo) | //512kB-1MB L3 cache
								IsL2Cache(0x22, nCacheInfo))
								return "Intel Xeon Foster MP";
							else
								return "Intel Xeon Foster (Willamette w/ DualCPU support, 1.4+GHz )";
							}
						if(IsL2Cache(0x83, nCacheInfo) |  //512 kb L2 cache
							IsL2Cache(0x7b, nCacheInfo) | 
							IsL2Cache(0x43, nCacheInfo))
							return "Intel Xeon Prestonia (HyperThreading, 2xP4 cores) 0.13 µm Foster, 2.0+GHz";
						return "Intel Pentium IV Willamette";
					}
					else if((((dwFMS>>20)&0xf) == 1) && (dwFamily == 0xf))
					{
						if(IsL2Cache(0x25, nCacheInfo) | //2-4 MB L3 Cache
								IsL2Cache(0x29, nCacheInfo) |
								IsL2Cache(0x88, nCacheInfo) |
								IsL2Cache(0x89, nCacheInfo))
								return "Intel Merced step B1/B2/C/D";
						else
							return "Intel Itanium 2 (McKinley)";
					}

				}

		}
		return "Unknown Intel processor";
	}
	else if (strcmp(sBrand, "UMC") == 0)
	{
	}
	else if (strcmp(sBrand, "AMD") == 0)
	{
		switch(dwFamily)
		{
			case 0x4:
				switch(dwModel)
				{
					case 0x1:
						if(dwStepping == 2)
							return "AMD 486 Am80486DXL/DXLV";
						else
							return "AMD 486 Am80486DX";
					case 0x3:
						return "AMD 486 Am80486DX2/DXL2";
					case 0x7:
						return "AMD 486 Am80486DX2";
					case 0x8:
						return "AMD 486 Am80486DX4";
					case 0x9:
						return "AMD 486 Am80486DX4";
					case 0xe:
						return "AMD 586  5x86 X5";
					case 0xf:
						return "AMD 586  5x86 X5";
				}
				return "AMD 486/586";
			case 0x5:
				switch(dwModel)
				{
					case 0x0:
						return "AMD K5 5k86 SSA/5";
					case 0x1:
						return "AMD K5 5k86 Godot";
					case 0x2:
						return "AMD K5 5k86 Godot";
					case 0x3:
						return "AMD K5 5k86 Godot";
					case 0x6:
						return "AMD K6 K6 Little Foot";
					case 0x7:
						return "AMD K6 Little Foot/Mobile/Embedded";
					case 0x8:
						switch(dwStepping)
						{
							case 0x0:
								return "AMD K6-2 Chomper APR";
							case 0x12:
								return "AMD K6-2 Chomper CXT (Chomper eXtended Tech), K6-III core";
							default:
								return "AMD K6-2 /Mobile/P Mobile/Embedded";
						}
					case 0x13:
						return "AMD K6-2+ mobile/K6-2E+ embedded";
					case 0x9:
						return "AMD K6-III Sharptooth/mobile/embedded";
					default:
						return "AMD K6";
				}
			case 0x6:
				switch(dwModel)
				{
					case 0x1:
						return "AMD Athlon K7 Model 1, Slot A, 0.25µm, 1.6V";
					case 0x2:
						return "AMD Athlon K75 Model 2, Slot A, 0.18µm, 1.7V";
					case 0x3:
						return "AMD Duron Spitfire/Select/mobile, Socket A, 0.18µm Cu, FSB200, 1.6V";
					case 0x4:
						return "AMD Athlon K76, 0.7-1.5GHz, Pro, Thunderbird, Socket A, 0.18µm Cu";
					case 0x6:
						return "AMD Athlon 4/MP/XP, Corvette, Mustang 256, Palomino, Socket A, 0.18µm Cu, OPGA, FSB266, 1.75V";
					case 0x7:
						return "AMD Duron, Camaro, Morgan, PowerNow!, 0.18µm, SSE, 1.75V, FSB200";
					case 0x8:
						return "AMD Athlon Thoroughbred, 0.13µm";
					default:
						if((nSpeed < 1510) && (nSpeed > 900))
							return "AMD Mobile Duron Morgan,  0.13µm SOI";
						if(nSpeed > 1510)
							return "AMD Athlon Thoroughbred, ClawHammer A0/A1, SledgeHammer, 0.13µm SOI";

				}
		}
		return "Unknown AMD processor";
	}
	else if (strcmp(sBrand, "Transmeta") == 0)
	{
	}
	else if (strcmp(sBrand, "Cyrix") == 0)
	{
	}
	else if (strcmp(sBrand, "Centaur") == 0)
	{
	}
	else if (strcmp(sBrand, "NexGen") == 0)
	{
	}
	else if (strcmp(sBrand, "Rise") == 0)
	{
	}
	else
		return "Unknown processor";
	return sBrand;
}

CString CCPUDetails::GetVendor()
{
	char sVendor[13] = "Unknown  cpu";
	__asm
	{
		mov eax,0;
		CPUID;
		mov dword ptr [sVendor],ebx;
		mov dword ptr [sVendor+4],edx;
		mov dword ptr [sVendor+8],ecx;
	}
	return sVendor;
}

CString CCPUDetails::GetCPUFeatures()
{
	DWORD dwFeatures = 0;
	CString sTmp;
	__asm
	{
		mov eax, 0x1;
		CPUID;
		mov dwFeatures, edx;
	}
	if(((dwFeatures >> 0) & 1) == 1)
		sTmp = "On chip floating point unit - yes";
	else
		sTmp = "On chip floating point unit - no";
	if(((dwFeatures >> 1) & 1) == 1)
		sTmp = sTmp + "\nVirtual Mode Extension support - yes";
	else
		sTmp = sTmp + "\nVirtual Mode Extension support - no";
	if(((dwFeatures >> 2) & 1) == 1)
		sTmp = sTmp + "\nDebugging Extension support - yes";
	else
		sTmp = sTmp + "\nDebugging Extension support - no";
	if(((dwFeatures >> 3) & 1) == 1)
		sTmp = sTmp + "\nPage Size Extension support - yes";
	else
		sTmp = sTmp + "\nPage Size Extension support - no";
	if(((dwFeatures >> 4) & 1) == 1)
		sTmp = sTmp + "\nTime Stamp Counter support - yes";
	else
		sTmp = sTmp + "\nTime Stamp Counter support - no";
	if(((dwFeatures >> 5) & 1) == 1)
		sTmp = sTmp + "\nModel Specific Registers support - yes";
	else
		sTmp = sTmp + "\nModel Specific Registers support - no";
	if(((dwFeatures >> 6) & 1) == 1)
		sTmp = sTmp + "\nPhysical Address Extension support - yes";
	else
		sTmp = sTmp + "\nPhysical Address Extension support - no";
	if(((dwFeatures >> 7) & 1) == 1)
		sTmp = sTmp + "\nMachine Check Exception support - yes";
	else
		sTmp = sTmp + "\nMachine Check Exception support - no";
	if(((dwFeatures >> 8) & 1) == 1)
		sTmp = sTmp + "\nCMPXCHG8 instruction support - yes";
	else
		sTmp = sTmp + "\nCMPXCHG8 instruction support - no";
	if(((dwFeatures >> 9) & 1) == 1)
		sTmp = sTmp + "\nOn chip APIC hardware support - yes";
	else
		sTmp = sTmp + "\nOn chip APIC hardware support - no";
	if(((dwFeatures >> 11) & 1) == 1)
		sTmp = sTmp + "\nFast System Call support - yes";
	else
		sTmp = sTmp + "\nFast System Call support - no";
	if(((dwFeatures >> 12) & 1) == 1)
		sTmp = sTmp + "\nMemory Type Range Registers support - yes";
	else
		sTmp = sTmp + "\nMemory Type Range Registers support - no";
	if(((dwFeatures >> 13) & 1) == 1)
		sTmp = sTmp + "\nPage Global Enable support - yes";
	else
		sTmp = sTmp + "\nPage Global Enable support - no";
	if(((dwFeatures >> 14) & 1) == 1)
		sTmp = sTmp + "\nMachine Check Architecture support - yes";
	else
		sTmp = sTmp + "\nMachine Check Architecture support - no";
	if(((dwFeatures >> 15) & 1) == 1)
		sTmp = sTmp + "\nConditional Move Instruction support - yes";
	else
		sTmp = sTmp + "\nConditional Move Instruction support - no";
	if(((dwFeatures >> 16) & 1) == 1)
		sTmp = sTmp + "\nPage Attribute Table support - yes";
	else
		sTmp = sTmp + "\nPage Attribute Table support - no";
	if(((dwFeatures >> 17) & 1) == 1)
		sTmp = sTmp + "\n36-bit Page Size Extension support - yes";
	else
		sTmp = sTmp + "\n36-bit Page Size Extension support - no";
	if(((dwFeatures >> 18) & 1) == 1)
		sTmp = sTmp + "\nProcessor serial nr present and enabled - yes";
	else
		sTmp = sTmp + "\nProcessor serial nr present and enabled - no";
	if(((dwFeatures >> 19) & 1) == 1)
		sTmp = sTmp + "\nCLFLUSH instruction support - yes";
	else
		sTmp = sTmp + "\nCLFLUSH instruction support - no";
	if(((dwFeatures >> 21) & 1) == 1)
		sTmp = sTmp + "\nDebug Store support - yes";
	else
		sTmp = sTmp + "\nDebug Store support - no";
	if(((dwFeatures >> 22) & 1) == 1)
		sTmp = sTmp + "\nThermal Monitor and Software Controlled Clock Facilities support - yes";
	else
		sTmp = sTmp + "\nThermal Monitor and Software Controlled Clock Facilities support - no";
	if(((dwFeatures >> 23) & 1) == 1)
		sTmp = sTmp + "\nMMX Technology support - yes";
	else
		sTmp = sTmp + "\nMMX Technology support - no";
	if(((dwFeatures >> 24) & 1) == 1)
		sTmp = sTmp + "\nFast floating point save and restore support - yes";
	else
		sTmp = sTmp + "\nFast floating point save and restore support - no";
	if(((dwFeatures >> 25) & 1) == 1)
		sTmp = sTmp + "\nStreaming SIMD Extensions support - yes";
	else
		sTmp = sTmp + "\nStreaming SIMD Extensions support - no";
	if(((dwFeatures >> 26) & 1) == 1)
		sTmp = sTmp + "\nStreaming SIMD Extensions 2 support - yes";
	else
		sTmp = sTmp + "\nStreaming SIMD Extensions 2 support - no";
	if(((dwFeatures >> 27) & 1) == 1)
		sTmp = sTmp + "\nSelf-Snoop support - yes";
	else
		sTmp = sTmp + "\nSelf-Snoop support - no";
	if(((dwFeatures >> 28) & 1) == 1)
		sTmp = sTmp + "\nHyper-Threading Technology support - yes";
	else
		sTmp = sTmp + "\nHyper-Threading Technology support - no";
	if(((dwFeatures >> 29) & 1) == 1)
		sTmp = sTmp + "\nThermal Monitor support - yes";
	else
		sTmp = sTmp + "\nThermal Monitor support - no";

	return sTmp;

}
