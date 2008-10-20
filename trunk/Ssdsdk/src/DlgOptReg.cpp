// DlgOptReg.cpp: implementation of the CDlgOptReg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DlgOptReg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDlgOptReg::CDlgOptReg(CWnd* pParent)
{
	m_bAddSystemButtons = TRUE;
	m_nOption = 0;
}

CDlgOptReg::~CDlgOptReg()
{

}

BEGIN_MESSAGE_MAP(CDlgOptReg, CDynDialogEx)
	//{{AFX_MSG_MAP(CListDynDialogEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CDlgOptReg::DoModal()
{
	SetWindowTitle(_T("Register Option"));
	AddDlgControl(BUTTON, _T("Fill in key directly."), STYLE_RADIO_GROUP, EXSTYLE_RADIO, NULL, &m_nOption);
	AddDlgControl(BUTTON, _T("Load a key from file."), STYLE_RADIO, EXSTYLE_RADIO);
	AddDlgControl(BUTTON, _T("Create an email for key"), STYLE_RADIO, EXSTYLE_RADIO);

	return CDynDialogEx::DoModal();
}

void CDlgOptReg::OnOK() 
{
	UpdateData();
	CDynDialogEx::OnOK();
}