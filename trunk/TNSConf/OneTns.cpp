// OneTns.cpp: implementation of the COneTns class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TNSConf.h"
#include "OneTns.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

LPCTSTR COneTns::m_lpszTnsPattern = 
	_T("(\\w+)\\s*=\\s*\\(\\s*DESCRIPTION\\s*=\\s*\\(\\s*ADDRESS_LIST\\s*=\\s*\\"
	   "(\\s*ADDRESS\\s*=\\s*\\(\\s*PROTOCOL\\s*=\\s*(\\w+)\\s*\\)\\s*\\(\\s*HOST\\s*=\\s*([\\w\\d.]+)"
	   "\\s*\\)\\s*\\(\\s*PORT\\s*=\\s*(\\d+)\\s*\\)\\s*\\)\\s*\\)\\s*\\(\\s*CONNECT_DATA\\s*=\\s*\\"
	   "(\\s*SERVICE_NAME\\s*=\\s*(\\w+)\\s*\\)\\s*\\)\\s*\\)");

CString COneTns::GetTns()
{
	static LPCTSTR lpszTnsFormat = 
		_T(
		"\r\n%s =\r\n"
		"  (DESCRIPTION =\r\n"
		"    (ADDRESS_LIST =\r\n"
		"      (ADDRESS = (PROTOCOL = TCP)(HOST = %s)(PORT = %s))\r\n"
		"      )\r\n"
		"    (CONNECT_DATA = (SERVICE_NAME = %s)\r\n"
		"    )\r\n"
		"  )\r\n" );

	m_csContext[TNS].Format(lpszTnsFormat, m_csContext[TNSNAME], m_csContext[HOST], m_csContext[PORT], m_csContext[SVRNAME]);
	return m_csContext[TNS];
}
