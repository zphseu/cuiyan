// EdFuncs.cpp: implementation of the CEdFuncs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdFuncs.h"
#include <algorithm>

void CEdFuncs::urlencode(string sIn, string& sOut)
{
	static string sUnsafeString(_T("\"<>%\\^[]`+$,@:;/!#?=&"));
	#define toHex(x) (x) > 9 ? (x) + 55: (x) + 48

	for ( int i = 0; i < sIn.size(); i++)
	{
		char chIn = sIn[i];
		if(chIn <= 32 || chIn >= 123 || find(sUnsafeString.begin(), sUnsafeString.end(), chIn) != sUnsafeString.end())
			sOut += chIn;
		else if (chIn == _T(' '))
			sOut += _T('+');
		else if (chIn == _T('\n'))
			sOut += _T("%0D%0A");
		else if (chIn == _T('\r'))
			;
		else
		{
			sOut += _T('%');
			sOut += toHex(chIn >> 4);
			sOut += toHex(chIn % 16);
		}
	}
}


int CEdFuncs::sd(const unsigned long ip, const char* from, const char* machine, const char* msg)
{
	// Packet format found thanks to a bit a sniffing
	static unsigned char packet_header[] = 
		"\x04\x00\x28\x00"
		"\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
		"\x00\x00\x00\x00\xf8\x91\x7b\x5a\x00\xff\xd0\x11\xa9\xb2\x00\xc0"
		"\x4f\xb6\xe6\xfc"
		"\xff\xff\xff\xff" // @40 : unique id over 16 bytes ?
		"\xff\xff\xff\xff"
		"\xff\xff\xff\xff"
		"\xff\xff\xff\xff"
		"\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00"
		"\x00\x00\xff\xff\xff\xff"
		"\xff\xff\xff\xff" // @74 : fields length
		"\x00\x00";
	
	unsigned char field_header[] = 
		"\xff\xff\xff\xff" // @0 : field length
		"\x00\x00\x00\x00"
		"\xff\xff\xff\xff"; // @8 : field length

	int i, fields_size, s;
	struct	sockaddr_in addr;
	WSADATA wsaData;

	WSAStartup(0x0202, &wsaData);
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_addr.s_addr = ip; //IPµØÖ·
	addr.sin_port = htons(135);
	addr.sin_family = AF_INET;
	
	char packet[8192];
	ZeroMemory(packet, sizeof(packet));
	int packet_size = 0;
	memcpy(&packet[packet_size], packet_header, 80);
	packet_size += 80;
	i = strlen(from)+1;
	*(unsigned int *)(&field_header[0]) = i;
	*(unsigned int *)(&field_header[8]) = i;
	memcpy(&packet[packet_size], field_header, 12);
	packet_size += 12;
	strcpy(&packet[packet_size], from);
	packet_size += (((i - 1) >> 2) + 1) << 2; // padded to a multiple of 4
	i = strlen(machine) + 1;
	*(unsigned int *)(&field_header[0]) = i;
	*(unsigned int *)(&field_header[8]) = i;
	memcpy(&packet[packet_size], field_header, 12);
	packet_size +=12;
	strcpy(&packet[packet_size], machine);
	packet_size += (((i - 1) >> 2) + 1) << 2; // padded to a multiple of 4
	i = strlen(msg) + 1;
	*(unsigned int *)(&field_header[0]) = i;
	*(unsigned int *)(&field_header[8]) = i;
	memcpy(&packet[packet_size], field_header, 12);
	packet_size += 12;
	strcpy(&packet[packet_size], msg);
	packet_size += i;
	fields_size = packet_size - 80;
	*(unsigned int *)(&packet[40]) = time(NULL);
	*(unsigned int *)(&packet[74]) = fields_size;
	
	return ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) != -1 && 
		sendto(s, packet, packet_size, 0, (struct sockaddr *)&addr, sizeof(addr)) != -1);
}


BOOL CEdFuncs::GetHttpPage(LPCTSTR lpszUrl, string& strData)
{
	BOOL  bSuccessful = FALSE;
	
	HINTERNET hSession = InternetOpen(_T("EdFuncs"), 
		INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	
	HINTERNET hHttpFile = InternetOpenUrl(hSession, lpszUrl, NULL, 0, 0, 0);
	if (hHttpFile)
	{
		TCHAR szSizeBuffer[32];
		DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);
		if (HttpQueryInfo(hHttpFile, HTTP_QUERY_CONTENT_LENGTH, szSizeBuffer, &dwLengthSizeBuffer, NULL))
		{
			TCHAR *pStop;
			DWORD dwBytesRead, dwFileSize = _tcstol(szSizeBuffer, &pStop, 10);
			TCHAR *sz = new TCHAR[dwFileSize + 2];
			ZeroMemory(sz, sizeof(sz));
			bSuccessful = InternetReadFile(hHttpFile, sz, dwFileSize, &dwBytesRead);
			InternetCloseHandle(hHttpFile);
			strData = sz;
			delete []sz;
		}
	}
	
	InternetCloseHandle(hSession);
	
	return bSuccessful;
}

BOOL CEdFuncs::GetFile(LPCTSTR lpszFileName, string& strData)
{
	BOOL bRet = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_DELETE, 
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		TCHAR *sz = new TCHAR[dwFileSize + 2];
		ZeroMemory(sz, sizeof(sz));
		if (ReadFile(hFile, sz, dwFileSize, &dwFileSize, NULL))
			strData = sz;
		delete []sz;
		CloseHandle(hFile);
		bRet = TRUE;
	}
	
	return bRet;
}

BOOL CEdFuncs::GetFtpFile(LPCTSTR lpszUrl, string& strData, LPCTSTR lpszUsr, 
				LPCTSTR lpszPwd, DWORD dwPort)
{
	BOOL  bSuccessful = FALSE;
	
	string sfile(lpszUrl);
	string surl = sfile.erase(0, 6);
	int len = sfile.find_first_of(_T('/'));
	sfile.erase(0, len);
	surl.erase(len, sfile.length());
	
	HINTERNET hSession = InternetOpen(_T("EdFuncs"), INTERNET_OPEN_TYPE_PRECONFIG, 
		NULL, NULL, INTERNET_FLAG_NO_CACHE_WRITE);
	
	HINTERNET hFtpFile = InternetConnect (hSession, surl.c_str(), dwPort, lpszUsr, lpszPwd, 
		INTERNET_SERVICE_FTP, INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_PASSIVE, 0);
	
	if (hFtpFile)
	{
		TCHAR szTemp[MAX_PATH];
		GetTempPath(MAX_PATH, szTemp);
		string slocalfile(szTemp);
		srand( time( NULL ) );
		_ultot(rand(), szTemp, 16);
		slocalfile += szTemp;
		
		bSuccessful = FtpGetFile(hFtpFile, sfile.c_str(), slocalfile.c_str(), 
			FALSE, FILE_ATTRIBUTE_ARCHIVE, FTP_TRANSFER_TYPE_UNKNOWN, 0);
		InternetCloseHandle(hFtpFile);
		
		if (bSuccessful)
			bSuccessful = GetFile(slocalfile.c_str(), strData);
		DeleteFile(slocalfile.c_str());
	}
	
	InternetCloseHandle(hSession);
	
	return bSuccessful;
}

HDC CEdFuncs::GetPrintHDC(LPCTSTR lpszPrinterName)
{
	HDC hDC = NULL;
	
	LPTSTR szPrintName = _tcslwr(_tcsdup(lpszPrinterName));
	string csPrinterName(szPrintName);
	free( szPrintName );
	
	if (csPrinterName.compare(_T("")) == 0)
	{	
		PRINTDLG pd;		
		pd.lStructSize = sizeof(PRINTDLG);
		pd.Flags = PD_RETURNDC;
		pd.hDC = NULL;
		pd.hwndOwner = NULL;
		pd.hInstance = NULL;
		pd.nMaxPage = 1;
		pd.nMinPage = 1;
		pd.nFromPage = 1;
		pd.nToPage = 1;
		pd.nCopies = 1;
		pd.hDevMode = NULL;
		pd.hDevNames = NULL;
		
		if(PrintDlg(&pd))
			hDC = pd.hDC;
	}
	else if (csPrinterName.compare(_T("default")) == 0)
	{
		PRINTDLG pd;
		pd.lStructSize = sizeof(PRINTDLG);
		pd.Flags = PD_RETURNDC | PD_RETURNDEFAULT;
		pd.hDC = NULL;
		pd.hwndOwner = NULL;
		pd.hInstance = NULL;
		pd.nMaxPage = 1;
		pd.nMinPage = 1;
		pd.nFromPage = 1;
		pd.nToPage = 1;
		pd.nCopies = 1;
		pd.hDevMode = NULL;
		pd.hDevNames = NULL;
		
		if(PrintDlg(&pd))
			hDC = pd.hDC;
	}
	else
	{
		HANDLE hprinter = NULL;
		
		if ( !OpenPrinter((LPTSTR)csPrinterName.c_str(), &hprinter,NULL) ) 
			return NULL;
		
		LONG rc = DocumentProperties(NULL, hprinter, (LPTSTR)csPrinterName.c_str(), NULL, NULL, 0);
		if (rc < 0)
			return NULL;
		
		byte* hDevMode = new byte[rc + 1];
		ZeroMemory(hDevMode, rc + 1);
		
		rc = DocumentProperties(NULL, hprinter, (LPTSTR)csPrinterName.c_str(), 
			(DEVMODE *)hDevMode, NULL, DM_OUT_BUFFER);
		if (rc > 0)
			hDC = CreateDC(_T("WINSPOOL"), csPrinterName.c_str(), NULL, (DEVMODE *)hDevMode); 
		
		delete [] hDevMode;
	}
	
	return hDC;	
}


