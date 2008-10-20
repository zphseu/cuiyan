// SoapSrc.cpp: implementation of the CSoapSrc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gsoapwzd.h"
#include "SoapSrc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CGSoapWzdApp theApp;

CString CSoapSrc::SaveResFile(HINSTANCE hInst, LPCTSTR name, LPCTSTR type, LPCTSTR filename)
{
	CString csName;
	HRSRC res = FindResource (hInst, name, type);
	HGLOBAL gl = LoadResource (hInst, res);
	LPVOID lp = LockResource(gl);
	csName.Format(_T("%s\\%s"), m_pView->m_csPrjPath, (filename == NULL) ? name : filename);
	HANDLE fp = CreateFile(csName ,GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	DWORD a = SizeofResource (hInst,res);
	if (!WriteFile (fp,lp, a, &a,NULL))	csName = _T("");
	CloseHandle (fp);
	FreeResource (gl);
	return csName;
}

LPCTSTR CSoapSrc::GetFilePath(LPCTSTR lpszName, BOOL bSrc, LPCTSTR prefix)
{
	static CString csName;
	
	if (prefix == NULL)
		csName.Format(_T("%s\\%s%s"), m_pView->m_csPrjPath, m_pView->m_csPrjName, lpszName);
	else
		csName.Format(_T("%s\\%s%s%s"), m_pView->m_csPrjPath, prefix, m_pView->m_csPrjName, lpszName);
	
	if (bSrc && !m_pView->m_bC)
		csName += _T("pp");

	CString s = csName;
	return csName;
}

BOOL CSoapSrc::SaveFile(LPCTSTR lpszFileName, BOOL bSrc, LPCTSTR prefix)
{
	BOOL bRet = TRUE;
	try	{
		CStdioFile f(GetFilePath(lpszFileName, bSrc, prefix), CFile::modeCreate | CFile::typeText | CFile::modeWrite);
		for (int i = 0; i < m_strArray.GetSize(); i++)
			f.WriteString(m_strArray[i]);
		f.Close();	
	} catch (CException *e) {
		e->ReportError();
		e->Delete();
		bRet = FALSE;
	}
	return bRet;
}

BOOL CSoapSrc::LoadFile(LPCTSTR lpszFileName, BOOL bSrc, LPCTSTR prefix)
{
	TCHAR t[1024];
	FILE *fp = _tfopen(GetFilePath(lpszFileName, bSrc, prefix), _T("r"));
	if (fp == NULL)
		return FALSE;
	
	m_strArray.RemoveAll();
	while (!feof(fp))
	{
		_fgetts(t, sizeof(t), fp);
		m_strArray.Add(t);
	}
	m_strArray.RemoveAt(m_strArray.GetSize() - 1);
	
	fclose(fp);
	
	return TRUE;
}

void CSoapSrc::ReplaceString(LPCTSTR lpszOld, LPCTSTR lpszNew)
{
	for (int i = 0; i < m_strArray.GetSize(); i++)
		m_strArray[i].Replace(lpszOld, lpszNew);
}

void CSoapSrc::ReplaceDspString()
{
	for (int i = 0; i < m_strArray.GetSize(); i++)
	{
		CString& str = m_strArray[i];
		str.Replace(_T("@EDSON@"), m_pView->m_csPrjName);
		str.Replace(_T("@CPP@"), m_pView->m_bC ? _T("c") : _T("cpp") );
	}
}

BOOL CSoapSrc::CreateCltpsFile()
{
	if (!QueryFunction(_T("/* Stubs */"), _T("/* Skeletons */")))
		return FALSE;

	CStringArray arFuns;
	CString csSoapFunc, csTmp, csParam;
	for (int j = 0; j < m_strArray.GetSize(); j++)
	{
		csTmp = m_strArray[j];
		csTmp.Replace(_T("SOAP_FMAC5 int SOAP_FMAC6 "), NULL);
		csSoapFunc = csTmp;
		csSoapFunc = csSoapFunc.Left(csSoapFunc.Find(_T("(")));
		csSoapFunc += _T("(&soap, URL, \"");
		
		int nIndex = csTmp.Find(_T("__"));
		if (nIndex > 0)
		{
			csTmp = csTmp.Right(csTmp.GetLength() - nIndex - 2);
			csSoapFunc += csTmp.Left(csTmp.Find(_T("(")));
			csSoapFunc += _T("\", ");
		}
		
		csTmp.Replace(_T("struct soap* soap, const char* p1, const char* p2, "), _T("const char* URL, "));
		nIndex = csTmp.Find(_T(","), csTmp.Find(_T(",")) + 1);
		for (int i = 3; nIndex >= 0; i++)
		{
			csParam.Format(_T("p%d, "), i);
			csSoapFunc += csParam;
			nIndex = csTmp.Find(_T(","), nIndex + csParam.GetLength() + 1);
		}
		csSoapFunc += _T("result)");
		arFuns.Add(csTmp);
		arFuns.Add(csSoapFunc);
	}

	//////////////////////////////////////////////////////////////////////////
	CStdioFile f;
	if (!f.Open(GetFilePath(_T("Cltps.h"), FALSE), CFile::modeCreate | CFile::modeWrite))
		return FALSE;
	
	CString csTmp2 = m_pView->m_csPrjName;
	csTmp2.MakeUpper();
	csTmp.Format(_T(
		"#ifndef _%sCLTPS_INCLUDE_\n"
		"#define _%sCLTPS_INCLUDE_\n\n"
		"#ifdef _USRDLL\n"
		"#define GSOAP_API __declspec(dllexport)\n"
		"#else\n"
		"#define GSOAP_API __declspec(dllimport)\n"
		"#endif\n\n"
		"#ifdef __cplusplus\n"
		"extern \"C\" {\n"
		"#endif\n\n"), csTmp2, csTmp2, csTmp2);
	f.WriteString(csTmp);

	for (int i = 0; i < arFuns.GetSize(); i+=2)
	{
		f.WriteString(_T("GSOAP_API int "));
		f.WriteString(arFuns[i]);
		f.WriteString(_T(";\n"));
	}

	csTmp.Format(_T("\n#ifdef __cplusplus\n}\n#endif\n\n#endif //_%sCLTPS_INCLUDE_\n"), csTmp2);	
	f.WriteString(csTmp);

	f.Close();
	//////////////////////////////////////////////////////////////////////////
	
	if (!f.Open(GetFilePath(_T("Cltps.c"), TRUE), CFile::modeCreate | CFile::modeWrite))
		return FALSE;
	
	csTmp.Format(_T("#include \"%sH.h\"\n#include \"%sCltps.h\"\n\n"
		"#ifdef __cplusplus\n"
		"extern \"C\" {\n"
		"#endif\n\n"), 
		m_pView->m_csPrjName, m_pView->m_csPrjName);
	f.WriteString(csTmp);
	
	for (i = 0; i < arFuns.GetSize(); i+=2 )
	{
		csTmp.Format(_T(
			"GSOAP_API int %s\n"
			"{\n"
			"\tstruct soap soap;\n"
			"\tint ret = SOAP_OK;"
			"\tsoap_init(&soap);\n"
			"\tret = %s;\n"
			"\tsoap_destroy(&soap);\n"
			"\tsoap_end(&soap);\n"
			"\tsoap_done(&soap);\n"
			"\treturn ret;\n"
			"}\n\n"), arFuns[i], arFuns[i+1]);
	
		f.WriteString(csTmp);
	}
	
	f.WriteString(_T("#ifdef __cplusplus\n}\n#endif\n"));
	f.Close();	
	return TRUE;
}

BOOL CSoapSrc::QueryFunction(LPCTSTR lpszStart, LPCTSTR lpszEnd)
{
	CStdioFile f;
	m_strArray.RemoveAll();
	
	if (!f.Open(GetFilePath(_T("Stub.h"), FALSE), CFile::modeRead))
		return FALSE;
	
	BOOL bStart = FALSE;
	CString csTmp;
	while(f.ReadString(csTmp))
	{
		if (csTmp.Find(lpszStart) >= 0)
			bStart = TRUE;
		
		if (csTmp.Find(lpszEnd) >= 0)
			break;
		
		if (bStart && csTmp.Find(_T("SOAP_FMAC5 int SOAP_FMAC6")) >= 0)
		{
			csTmp.Replace(_T(';'), NULL);
			csTmp.Replace(_T("struct soap*,"), _T("struct soap* soap,"));
			csTmp.TrimRight();
			csTmp.Insert(csTmp.ReverseFind(_T(')')), _T("result"));
			
			CString csParam;
			int nFind = csTmp.Find(_T(','), 0);
			if (nFind < 0)
				break;
			
			nFind = csTmp.Find(_T(','), nFind + 1);
			for (int j = 1; nFind > 0; j++)
			{
				csParam.Format(_T(" p%d"), j);
				csTmp.Insert(nFind, csParam);
				nFind = csTmp.Find(_T(','), nFind + csParam.GetLength() + 1);
			}
			m_strArray.Add(csTmp);
		}
	}
	f.Close();
	
	return TRUE;
}

int CSoapSrc::DoModal(CSoapcpp2View* pView)
{
	ASSERT(pView);
	m_pView = pView;
 
	SaveResFile(theApp.m_hInstance, _T("STDSOAP2.H"), _T("SOURCE"));
 	SaveResFile(theApp.m_hInstance, _T("STDSOAP2.C"), _T("SOURCE"), 
		m_pView->m_bC ? _T("stdsoap2.c") : _T("stdsoap2.cpp"));

	GetNsMaps();
	
	Do_Proxy_h();
	Do_Stub_h();
	Do_Client_c();
	Do_Server_c();
	
	if (m_pView->m_bClient)
	{
		Do_Clt_c();
		Do_Clt_Project();
	}

	if (m_pView->m_bServer)
	{
		Do_Svr_c();
		Do_Svr_Project();
	}
 
	return IDOK;
}

void CSoapSrc::Do_Proxy_h()
{
	if (m_pView->m_bC)
	{
		if (!LoadFile(_T("Proxy.h")))	return;
		ReplaceString(_T("&result)"), _T("*result)"));		
		SaveFile(_T("Proxy.h"));
	}
}

void CSoapSrc::Do_Stub_h()
{
	if (!LoadFile(_T("Stub.h")))	return;

	if (m_pView->m_bC)
		ReplaceString(_T("&);"), _T("*);"));		

	if (m_pView->m_bClient && m_pView->m_nClient == 1)
	{
		
	}

	SaveFile(_T("Stub.h"));	
}


void CSoapSrc::Do_Client_c()
{
	if (m_pView->m_bC)
	{
		if (!LoadFile(_T("Client.c"), TRUE)) return;
		ReplaceString(_T(" &result)"), _T(" *result)"));
		ReplaceString(_T("(soap, *result)"), _T("(soap, result)"));
		ReplaceString(_T("result = soap_"), _T("*result = soap_"));
		SaveFile(_T("Client.c"), TRUE);
	}	
}

void CSoapSrc::Do_Server_c()
{	
	/* for 2.6.2 
		Relpace from
			|| soap_end_recv(soap))
				return soap->error;
			soap->error = ns__sub(soap, soap_tmp_ns__sub.a, soap_tmp_ns__sub.b, *soap_tmp_ns__subResponse.result);
		to
			|| soap_end_recv(soap))
				return soap->error;
			soap->error = ns__sub(soap, soap_tmp_ns__sub.a, soap_tmp_ns__sub.b, &soap_tmp_ns__subResponse.result);
	if (m_pView->m_bC)
	{	
		if (!LoadFile(_T("Server.c"), TRUE)) return;
		for (int i = 0; i < m_strArray.GetSize(); i++)
		{
			CString& str = m_strArray[i];
			
			if (i > 1 && m_strArray[i-2].Find(_T("|| soap_end_recv(soap))")) >= 0 && 
				m_strArray[i-1].Find(_T("return soap->error;")) >= 0 &&
				str.Find(_T("soap->error =")) >= 0 )
			{
				int nLastDot = str.ReverseFind(_T(','));
				str.Insert(++nLastDot, _T('&'));
			}
		}

		SaveFile(_T("Server.c"), TRUE);
	}
	*/ 
}

void CSoapSrc::GetNsMaps()
{
	m_csNsMaps = _T("");
	CFileFind finder;
	BOOL bWorking = finder.FindFile(m_pView->m_csPrjPath + _T("\\*.nsmap"));
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		m_csNsMaps += _T("// #include \"") + finder.GetFileName() + _T("\"\n");
	}
	m_csNsMaps.Delete(0, 3);
}

void CSoapSrc::Do_Clt_c()
{
	switch(m_pView->m_nClient) 
	{
	case 0: // console application
		{
			SaveResFile(theApp.m_hInstance, 
				m_pView->m_bC ? _T("THECLT.C") : _T("THECLT.CPP"), _T("SOURCE"), 
				m_pView->m_csPrjName + (m_pView->m_bC ? _T("Clt.c") : _T("Clt.cpp")));

			if (!LoadFile(_T("Clt.c"), TRUE)) return;
			ReplaceString(_T("\"@nsmap@\""), m_csNsMaps);
			ReplaceString(_T("@EDSON@"), m_pView->m_csPrjName);
			SaveFile(_T("Clt.c"), TRUE);
		}
		break;

	case 1: // Dynamic-link library.
		if (!LoadFile(_T("ClientLib.c"), TRUE)) return;
		ReplaceString(
			_T("#define WITH_NOGLOBAL"), m_csNsMaps + 
			_T("\n#define WITH_NOGLOBAL\n\n#ifdef SOAP_FMAC3\n#undef SOAP_FMAC3\n#endif\n"));
		
		SaveFile(_T("ClientLib.c"), TRUE);
		
		//////////////////////////////////////////////////////////////////////////
		CreateCltpsFile();
		
		break;
		
	default:
		;
	}
}

void CSoapSrc::Do_Svr_c()
{
	if (m_pView->m_nServer == 4) // apache module dll
	{
		SaveResFile(theApp.m_hInstance, _T("APACHE_GSOAP.H"), _T("SOURCE"), _T("apache_gsoap.h"));
		CStdioFile f;
		if (!f.Open(GetFilePath(_T(".c"), TRUE, _T("mod_")), CFile::modeCreate | CFile::modeWrite)
			|| !QueryFunction(_T("/* Remote Methods */"), _T("/* Stubs */")))
			return;
		
		CString csTemp = _T(
			"/** the @EDSON@ gsoap service implemented as a shared library that\n"
			" * can be loaded from Apache Http Server.\n"
			" * @author gSoapWzd (http://cosoft.org.cn/projects/gsoapwzd/)\n"
			" * @file mod_@EDSON@.cpp\n"
			" */\n\n"
			"#define SOAP_FMAC1 __declspec(dllexport)\n"
			"#define SOAP_FMAC3 static\n"
			"@NSMAPS@"
			"#include \"apache_gsoap.h\"\n\n"
			"#ifdef __cplusplus\n"
			"extern \"C\" {\n"
			"#endif\n\n"
			"IMPLEMENT_GSOAP_SERVER() ///< this macro defines the necessary exports from the dll.\n\n"
			"#ifdef __cplusplus\n"
			"}\n"
			"#endif\n\n");

		csTemp.Replace(_T("@EDSON@"), m_pView->m_csPrjName);
		csTemp.Replace(_T("@NSMAPS@"), m_csNsMaps);
		f.WriteString(csTemp);
		
		for (int i = 0; i < m_strArray.GetSize(); i++ )
		{
			f.WriteString(m_strArray[i]);
			f.WriteString(_T("\n{\n\treturn SOAP_OK;\n}\n\n"));
		}
		
		f.Close();	
		
		return;
	}

	SaveResFile(theApp.m_hInstance, 
		m_pView->m_bC ? _T("THESVR.C") : _T("THESVR.CPP"), _T("SOURCE"), 
		m_pView->m_csPrjName + (m_pView->m_bC ? _T("Svr.c") : _T("Svr.cpp")));
	
	if (!LoadFile(_T("Svr.c"), TRUE)) return;
	ReplaceString(_T("\"@nsmap@\""), m_csNsMaps);
	
	int nInPhase = 0;
	BOOL bInPhase = FALSE;
	CStringArray strArrayTmp;
	for (int i = 0; i < m_strArray.GetSize(); i++)
	{
		CString& str = m_strArray[i];
		if (str.Find(_T("/// EDSON START ")) >= 0)
		{
			if (str.Find(_T("/// EDSON END")) >= 0)
			{
				bInPhase = FALSE;
				str = _T("");
			}
			else
			{
				nInPhase++;
				bInPhase = TRUE;
				str = m_strArray[++i];
			}
		}

		if (!bInPhase || nInPhase == m_pView->m_nServer + 2 || 
			(m_pView->m_nServer != 0 && nInPhase == 1) )
			strArrayTmp.Add(str);
	}
	m_strArray.RemoveAll();
	m_strArray.Append(strArrayTmp);
	
	if (m_pView->m_nServer > 1)
	{
		switch(m_pView->m_nCompiler) {
		case 0: // MSVC6
			SaveResFile(theApp.m_hInstance, _T("pthreadVC.lib"), _T("PTHREAD"),	_T("pthreadVC.lib"));
			SaveResFile(theApp.m_hInstance, _T("pthreadVC.dll"), _T("PTHREAD"),	_T("pthreadVC.dll"));
			break;
		case 1: // MINGW
			SaveResFile(theApp.m_hInstance, _T("LIBPTHREADGC.A"), _T("PTHREAD"),	_T("libpthreadGC.a"));
			SaveResFile(theApp.m_hInstance, _T("pthreadGC.dll"), _T("PTHREAD"),	_T("pthreadGC.dll"));
			break;
		case 2: // BCC
			break;
		case 3: // LCCWIN
			break;
		default:
			;
		}
		SaveResFile(theApp.m_hInstance, _T("semaphore.h"), _T("PTHREAD"),	_T("semaphore.h"));
		SaveResFile(theApp.m_hInstance, _T("pthread.h"), _T("PTHREAD"),	_T("pthread.h"));
		SaveResFile(theApp.m_hInstance, _T("sched.h"), _T("PTHREAD"),	_T("sched.h"));
	}
	
	SaveFile(_T("Svr.c"), TRUE);
	
	//////////////////////////////////////////////////////////////////////////
	CStdioFile f;
	if (!f.Open(GetFilePath(_T("SvrFun.c"), TRUE), CFile::modeCreate | CFile::modeWrite)
		|| !QueryFunction(_T("/* Remote Methods */"), _T("/* Stubs */")))
		return;
	
	f.WriteString(_T("//\n// Implement your remote methods\n//\n\n#include \""));
	f.WriteString(m_pView->m_csPrjName);
	f.WriteString(_T("Stub.h\"\n\n"));
	
	for (i = 0; i < m_strArray.GetSize(); i++ )
	{
		f.WriteString(m_strArray[i]);
		f.WriteString(_T("\n{\n\treturn SOAP_OK;\n}\n\n"));
	}
	
	f.Close();	
}

void CSoapSrc::Do_Svr_Project()
{
	CString csName, csResName, csPrefix, csWSockLib, csPThreadLib;

	switch(m_pView->m_nCompiler) 
	{
	case 0: //MSVC6
		if (m_pView->m_nServer == 4)
		{
			csResName = _T("APACHE.DSP");
			csName = _T(".dsp");
			csPrefix = _T("mod_");
		}
		else
		{
			csName = _T("Svr.dsp");
			csResName = _T("SERVER.DSP");
			csWSockLib = _T("wsock32.lib ");
			csPThreadLib = _T("pthreadVC.lib ");
		}		
		break;

	case 1:	// MINGW
		if (m_pView->m_nServer == 4)
		{
			csResName = _T("APACHE.MINGW");
			csName = _T(".mak");
			csPrefix = _T("mod_");
		}
		else
		{
			csName = _T("Svr.mak");
			csResName = _T("SERVER.MINGW");
			csWSockLib = _T("LIBS+=-lwsock32 ");
			csPThreadLib = _T(".\\libpthreadGC.a ");
		}
		break;

	case 2: // BCC
		break;
	case 3: // LCCWIN
		break;
	default:
		;
	}
	
	SaveResFile(theApp.m_hInstance, csResName, _T("PROJECT"), csPrefix + m_pView->m_csPrjName + csName);
	if (!LoadFile(csName, FALSE, csPrefix)) return;
	ReplaceDspString();
	switch(m_pView->m_nServer) 
	{
	case 2:
	case 3: // console application
		ReplaceString(csWSockLib, csWSockLib + csPThreadLib);
		break;
	default:
		;
	}
	SaveFile(csName, FALSE, csPrefix);
}

void CSoapSrc::Do_Clt_Project()
{
	CString csName, csResName;

	switch(m_pView->m_nClient) {
	case 0:	 // console application
		csName = _T("Clt");
		csResName = _T("CLIENT");
		break;
	case 1:	// Dynamic-link library.
		csName = _T("Cltps");
		csResName = _T("THECLTDLL");
		break;
	default:
		;
	}
	
	switch(m_pView->m_nCompiler) 
	{
	case 0: //MSVC6
		csName += _T(".dsp");
		csResName += _T(".DSP");
		break;
	case 1: // MINGW
		csName += _T(".mak");
		csResName += _T(".MINGW");
		break;
	case 2: // BCC
		break;
	case 3: // LCCWIN
		break;
	default:
		;
	}

	SaveResFile(theApp.m_hInstance, csResName, _T("PROJECT"), m_pView->m_csPrjName + csName);
	if (!LoadFile(csName)) return;
	ReplaceDspString();
	SaveFile(csName);
}
