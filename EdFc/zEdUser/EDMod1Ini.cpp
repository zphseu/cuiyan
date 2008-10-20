// BSUserIni.cpp: implementation of the CEdMod1Ini class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdMod1Ini.h"
#include "IniFile.h"
/////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdMod1Ini::CEdMod1Ini()
{
	m_bNeedLogin = TRUE;
	m_bUseDB = TRUE;
	m_csConStr = _T("DSN=BSIBMS");
	m_csDefUser = _T("admin");
}

CEdMod1Ini::~CEdMod1Ini()
{

}

BOOL CEdMod1Ini::ReadConfig()
{
	CIniFile f;
	
	try 
	{
		if (!f.OpenIniFileForRead(GetIniFileName()))
			return FALSE;
		
		f.GetItemInt("SYSCFG", "NeedLogin", m_bNeedLogin);
		f.GetItemInt("SYSCFG", "UseDB", m_bUseDB);
		f.GetItemString("SYSCFG", "DBCon", m_csConStr);
		f.GetItemString("SYSCFG", "DefUser", m_csDefUser);
		f.GetItemString("SYSCFG", "DefGroup", m_csDefGrp);
		f.GetItemString("SYSCFG", "Config", m_csConfig);
	}
	catch(CException *e)
	{
		e->ReportError();
		e->Delete();
		f.CloseIniFile();
		return FALSE;
	}
	
	f.CloseIniFile();
	return TRUE;
}

BOOL CEdMod1Ini::WriteConfig()
{
	CIniFile f;
	
	try
	{
		if (!f.OpenIniFileForWrite(GetIniFileName()))
			return FALSE;
		
		f.WriteSection("SYSCFG");
		f.WriteItemInt("NeedLogin", m_bNeedLogin);
		f.WriteItemInt("UseDB", m_bUseDB);
		f.WriteItemString("DBCon", m_csConStr);
		f.WriteItemString("DefUser", m_csDefUser);		
		f.WriteItemString("DefGroup", m_csDefGrp);
		f.WriteItemString("Config", m_csConfig);
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
		f.CloseIniFile();
		return FALSE;
	}

	f.CloseIniFile();
	return TRUE;
}

extern HINSTANCE g_hInstance;
CString CEdMod1Ini::GetIniFileName()
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(g_hInstance, szPath, MAX_PATH);
	CString csModelName(szPath);
	csModelName = csModelName.Left(csModelName.ReverseFind('.'));
	csModelName += ".ini";
	return csModelName;
}

BOOL CEdMod1Ini::GetVisable(int index)
{
	BOOL nConfig = atoi(m_csConfig);
	
	for (int i = 0; i < index; i++)
		nConfig /= 10;
	
	nConfig = nConfig % 10;
	
	return (nConfig == index);
}
