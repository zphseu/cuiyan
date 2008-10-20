// DlgSend.cpp: implementation of the CDlgSend class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DlgSend.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDlgSend::CDlgSend(CWnd* pParent)
	: CDynDialogEx(pParent)
{
	m_bAddSystemButtons = TRUE;
}

CDlgSend::~CDlgSend()
{

}

BEGIN_MESSAGE_MAP(CDlgSend, CDynDialogEx)
	//{{AFX_MSG_MAP(CListDynDialogEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CDlgSend::DoModal()
{
	SetWindowTitle(_T("Dialog for UserInfo to Save"));
	AddDlgControl(STATICTEXT, _T("Name:"), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_User.m_szName);
	AddDlgControl(STATICTEXT, _T("Email:"), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_User.m_szEmail);
	return CDynDialogEx::DoModal();
}

void CDlgSend::OnOK() 
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
	
	CDynDialogEx::OnOK();
}