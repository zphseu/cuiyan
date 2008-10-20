// UserInfo.h: interface for the CUserInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERINFO_H__BA6A3176_9514_43FE_8A77_10EEC2F5C80F__INCLUDED_)
#define AFX_USERINFO_H__BA6A3176_9514_43FE_8A77_10EEC2F5C80F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DlgUsrReg.h"
#include "Registry.h"

class CUserInfo  
{
public:
	CUserInfo();
	virtual ~CUserInfo();
	BOOL GetUserInfo();

private:
	BOOL SaveUserInfoToReg();
	BOOL GetUserInfoFromDlg();
	BOOL GetUserInfoFromReg();

	USER m_User;
	CString m_RegPath;
};

#endif // !defined(AFX_USERINFO_H__BA6A3176_9514_43FE_8A77_10EEC2F5C80F__INCLUDED_)
