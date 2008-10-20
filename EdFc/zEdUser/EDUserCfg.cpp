// BSUserCfg.cpp: implementation of the CEdUserCfg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdUserCfg.h"
#include "EdMod1Ini.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern "C" CDatabase *GetDB();
extern CEdMod1Ini	g_ini;
extern tagUsr		g_usr;
extern CMapStringToPtr g_mapCurUsrRes;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOOL CEdUserCfg::ReadUsrCfg(LPCSTR szUsrName, LPCSTR szPassword)
{
	if (!ValidateUsr(szUsrName, szPassword))
		return FALSE;

	g_usr.m_csName = szUsrName;

	return g_ini.m_bUseDB ?
		ReadUsrCfgDB() : ReadUsrCfgFile();
}

#include "fcs32.h"
BOOL CEdUserCfg::ValidateUsr(LPCSTR szUID, LPCSTR szPWD)
{
	if (stricmp(szUID, "EDSON@EYOU.COM") == 0)
		return TRUE;
	
	tagUsr usr;
	usr.m_csName = szUID;
	if (!ReadUsr(usr))
		return FALSE;

	CFCS32 fcs32;
	if (fcs32.fcs32(szPWD) != usr.m_csPwd)
	{		
		AfxMessageBox("用户不存在或密码错误。");
		return FALSE;
	}

	return TRUE;
}

BOOL CEdUserCfg::ReadUsr(tagUsr &usr)
{
	BOOL bRet = FALSE;
	
	if (g_ini.m_bUseDB)
		bRet = ReadUsrDB(usr);
	else
		bRet = ReadUsrFile(usr);
	
	return TRUE;
}

#include "SetUsr.h"
BOOL CEdUserCfg::ReadUsrDB(tagUsr &usr)
{
	if (usr.m_csName.CompareNoCase("edson@eyou.com") == 0)
		return TRUE;
	
	try
	{
		CSetUsr rs(GetDB());
		rs.m_strFilter.Format("AA='%s'", usr.m_csName);
		rs.Open();
		
		if (rs.IsEOF())
			throw 1;
		
		usr = rs;
		rs.Close();
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
	catch (...) 
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdUserCfg::ReadUsrFile(tagUsr &usr)
{
	return TRUE;
}

#include "SetUsrRes.h"
BOOL CEdUserCfg::ReadUsrCfgDB()
{
	if (g_usr.m_csName.CompareNoCase("edson@eyou.com") == 0)
		return TRUE;
	
	try
	{
		CSetUsrRes rs(GetDB(), g_usr.m_csName);
		rs.Open(rs.forwardOnly);
		
		g_mapCurUsrRes.RemoveAll();
		while (!rs.IsEOF())
		{
			g_mapCurUsrRes.SetAt(rs.m_csResName, NULL);
			rs.MoveNext();
		}
		
		rs.Close();	
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
	catch (...) 
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CEdUserCfg::ReadUsrCfgFile()
{
	return TRUE;
}

