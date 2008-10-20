// TnsNamesFile.cpp: implementation of the CTnsNamesFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TNSConf.h"
#include "TnsNamesFile.h"
#include <atlbase.h>
#include <pcre.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BOOL CTnsNamesFile::Save()
{		
	TRY
	{
		CString szFileName = GetFileName();
		CopyFile(szFileName, szFileName + _T(".bak"), FALSE); // 备份
		
		CString strFile(_T("# TNSNAMES.ORA NETWORK CONFIGURATION FILE."
			"\n# Modified by TnsConf (edson@edson.thefreeserver.com, @ 2003-2004.)\n\n"
			));
		for (int i = 0; i < Tns.GetSize(); i++)
			strFile += Tns[i].GetTns();

		CFile f(szFileName, CFile::modeCreate | CFile::modeWrite);
		f.WriteHuge(strFile, strFile.GetLength());
		f.Close();
	}
	CATCH(CException, pEx)
	{		
		pEx->ReportError();
		return FALSE;
	}
	END_CATCH
		
	return TRUE;
}

BOOL CTnsNamesFile::Load()
{
	CString strFile;
	TRY		// 读文件信息		
	{
		CFile f(GetFileName(), CFile::modeRead);
		{
			TCHAR *str = new TCHAR[f.GetLength()];
			if (str == NULL)
				throw new CMemoryException;
			f.ReadHuge(str, f.GetLength());
			strFile = str;
			delete [] str;
		}
		f.Close();
	}
	CATCH(CException, pEx)
	{		
		pEx->ReportError();
		return FALSE;
	}
	END_CATCH

	strFile.MakeUpper();
	
	return Parse(strFile);
}

CString CTnsNamesFile::GetFileName()
{
	CString szFileName;	
	CRegKey reg;
	
	if (reg.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\ORACLE")) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("在注册表中无法查询到键HKEY_LOCAL_MACHINE\\SOFTWARE\\ORACLE"));
		return _T("");
	}
	
	TCHAR strTmp[MAX_PATH];
	DWORD dwLen = MAX_PATH;
	ZeroMemory(strTmp, MAX_PATH);
	if (reg.QueryValue(strTmp, _T("ORACLE_HOME"), &dwLen) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("在注册表中键\\SOFTWARE\\ORACLE中无ORACLE_HOME"));
		return _T("");
	}

	reg.Close();
	
	szFileName = strTmp;
	if (szFileName[szFileName.GetLength() - 1] != '\\')
		szFileName += _T('\\');

	szFileName += _T("network\\ADMIN\\tnsnames.ora");

	return szFileName;
}

BOOL CTnsNamesFile::Parse(CString& strFile)
{
	pcre *re; 
	const char *error; 
	int erroffset = 0; 
	re = pcre_compile(COneTns::m_lpszTnsPattern, 0, &error, &erroffset, NULL);

	if (re == NULL)
		return FALSE;
	
	int ovector[COneTns::TNSINDEX*2], start(0);
	const char **listptr = NULL;
	
	Tns.RemoveAll();
	COneTns atns;
	while ( pcre_exec(re, NULL, strFile.GetBuffer(0) + start, strFile.GetLength() - start, 0, 0, ovector, 30) == COneTns::TNSINDEX )
	{
		int rcsl = pcre_get_substring_list(strFile.GetBuffer(0) + start, ovector, COneTns::TNSINDEX, &listptr);	//成功返回零
		
		for (int i = 0; rcsl == 0 && i < COneTns::TNSINDEX; i++)
			atns.m_csContext[i] = listptr[i];
		
		Tns.Add(atns);
		start += ovector[COneTns::TNSINDEX*2-1];
		pcre_free_substring_list(listptr);
	}
	
	return TRUE;
}
