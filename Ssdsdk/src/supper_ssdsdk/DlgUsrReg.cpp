// DlgUsrReg.cpp: implementation of the CDlgUsrReg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DlgUsrReg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDlgUsrReg::CDlgUsrReg(CWnd* pParent)
	: CDynDialogEx(pParent)
{
	m_bAddSystemButtons = TRUE;
}

CDlgUsrReg::~CDlgUsrReg()
{

}

BEGIN_MESSAGE_MAP(CDlgUsrReg, CDynDialogEx)
	//{{AFX_MSG_MAP(CListDynDialogEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CDlgUsrReg::DoModal()
{
	SetWindowTitle(_T("User Infomation Dialog"));
	AddDlgControl(STATICTEXT, _T("FirstName:"), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_User.m_szFirstName);
	AddDlgControl(STATICTEXT, _T("LastName:"), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_User.m_szLastName);
	AddDlgControl(STATICTEXT, _T("Email:"), STYLE_STATIC, EXSTYLE_STATIC);	
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_User.m_szEmail);
	AddDlgControl(STATICTEXT, _T("Telephone:"), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_User.m_szTelephone);
	AddDlgControl(STATICTEXT, _T("QQ No.:"), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_User.m_szQQ);
	AddDlgControl(STATICTEXT, _T("MSN:"), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_User.m_szMSN);
	
	return CDynDialogEx::DoModal();
}

void CDlgUsrReg::OnOK() 
{
	UpdateData();
	if (m_User.m_szFirstName.IsEmpty()) {
		AfxMessageBox("Please fill in FirstName!");
		return;
	}
	if (m_User.m_szLastName.IsEmpty()) {
		AfxMessageBox("Please fill in LastName!");
		return;
	}
	if (m_User.m_szEmail.IsEmpty()) {
		AfxMessageBox("Please fill in Email!");
		return;
	}
	
	CDynDialogEx::OnOK();
}