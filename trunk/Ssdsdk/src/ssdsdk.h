#ifndef _SSDSDK_INCLUDE_
#define _SSDSDK_INCLUDE_

// you config this infomation
#define MSGTIMEOUT	_T("TimeOut, please email to edsoncy@citiz.net!")
#define YOUREMAIL	_T("edsoncy@citiz.net")
#define TIMEOUTDATA CTime(2006, 01, 01, 00, 00, 00)

#define MSGLISINFO	_T("This program is a trial version. If you like it, please contact the author to get a office version.\n\nCopyright (c) Shanghai Edson Software Co., Ltd.\n\nhttp://edsoncy.objectis.net/\nmailto:edsoncy@citiz.net")

// ====================
// copy from ssd.h 
enum CRYPTTYPE {
	WINCRYPTAPI,
	CRYPTRC4,
	CRC_ADLER
};
// ====================

#ifdef _DEBUG
#pragma comment(lib, "ssdsdkd.lib")
#else
#pragma comment(lib, "ssdsdk.lib")
#endif

#ifdef _DEMO
	#define CHECKVALIDATE IsDlgLisence(MSGLISINFO)
#else
	#define CHECKVALIDATE (IsTimeOut(MSGTIMEOUT,TIMEOUTDATA) && IsRegisted(YOUREMAIL) )
#endif

BOOL IsTimeOut(CString errMsg, CTime tm);
BOOL IsRegisted(CString email, CRYPTTYPE crypt = CRC_ADLER);
BOOL IsDlgLisence(LPCSTR sinfo);

#endif //_SSDSDK_INCLUDE_
