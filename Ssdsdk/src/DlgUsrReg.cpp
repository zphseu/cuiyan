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
	SetWindowTitle(_T("Regist Dialog"));
	AddDlgControl(STATICTEXT, _T("Name:"), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_User.m_szName);
	AddDlgControl(STATICTEXT, _T("Email:"), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_User.m_szEmail);
	AddDlgControl(STATICTEXT, _T("Serial:"), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_User.m_szSerial);

	return CDynDialogEx::DoModal();
}

void CDlgUsrReg::OnOK() 
{
	UpdateData();
	if (m_User.m_szName.IsEmpty()) {
		AfxMessageBox("Please fill in Name!");
		return;
	}

	if (m_User.m_szEmail.IsEmpty()) {
		AfxMessageBox("Please fill in Email!");
		return;
	}
	
	if (m_User.m_szSerial.IsEmpty()) {
		AfxMessageBox("Please fill in Email!");
		return;
	}

	CDynDialogEx::OnOK();
}