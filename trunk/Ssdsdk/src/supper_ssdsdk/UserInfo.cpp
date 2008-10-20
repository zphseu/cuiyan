// UserInfo.cpp: implementation of the CUserInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UserInfo.h"
#include "MyConfig.h"
#include "ProductInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserInfo::CUserInfo()
{
#ifndef theRegPath
	CProductInfo pi;
	pi.GetProductInfo();
	m_RegPath.Format(_T("Software\\%s"), pi.GetName());
#else
	m_RegPath = theRegPath;
#endif
	ASSERT(!m_RegPath.IsEmpty());
}

CUserInfo::~CUserInfo()
{

}

CUserInfo::GetUserInfo()
{
	BOOL bRet = GetUserInfoFromReg();
	if (!bRet)
		bRet = GetUserInfoFromDlg();
	return bRet;
}

BOOL CUserInfo::GetUserInfoFromReg()
{
	CRegistry Reg(HKEY_LOCAL_MACHINE);
	if (!Reg.Open(m_RegPath))
		return FALSE;
	
	if (!Reg.ReadString(_T("FirstName"), m_User.m_szFirstName) ||
		!Reg.ReadString(_T("LastName"), m_User.m_szLastName) ||
		!Reg.ReadString(_T("Email"), m_User.m_szEmail) )
		return FALSE;
	
	if (m_User.m_szFirstName.IsEmpty() || m_User.m_szLastName.IsEmpty()
		|| m_User.m_szEmail.IsEmpty())
		return FALSE;

	Reg.ReadString(_T("Telephone"), m_User.m_szTelephone);
	Reg.ReadString(_T("QQ"), m_User.m_szQQ);
	Reg.ReadString(_T("MSN"), m_User.m_szMSN);

	Reg.Close();

	return TRUE;
}

BOOL CUserInfo::SaveUserInfoToReg()
{
	CRegistry Reg(HKEY_LOCAL_MACHINE);
	
	if (!Reg.Open(m_RegPath))
		return FALSE;
	
	if (m_User.m_szFirstName.IsEmpty() || m_User.m_szLastName.IsEmpty()
		|| m_User.m_szEmail.IsEmpty())
		return FALSE;
	
	if (!Reg.WriteString(_T("FirstName"), m_User.m_szFirstName) ||
		!Reg.WriteString(_T("LastName"), m_User.m_szLastName) ||
		!Reg.WriteString(_T("Email"), m_User.m_szEmail) )
		return FALSE;
	
	Reg.WriteString(_T("Telephone"), m_User.m_szTelephone);
	Reg.WriteString(_T("QQ"), m_User.m_szQQ);
	Reg.WriteString(_T("MSN"), m_User.m_szMSN);

	Reg.Close();

	return TRUE;
}

BOOL CUserInfo::GetUserInfoFromDlg()
{
	CWnd* pParentWnd = AfxGetMainWnd();
	CDlgUsrReg dlg(pParentWnd);
	dlg.m_User = m_User;
	if (dlg.DoModal() == IDOK)
	{
		m_User = dlg.m_User;
		return SaveUserInfoToReg();
	}
	return FALSE;
}

