// DlgLoad.cpp: implementation of the CDlgLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DlgLoad.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDlgLoad::CDlgLoad(CWnd* pParent)
	: CDynDialogEx(pParent)
{
	m_bAddSystemButtons = TRUE;
}

CDlgLoad::~CDlgLoad()
{

}

#define IDC_BROWER WM_USER + 187

BEGIN_MESSAGE_MAP(CDlgLoad, CDynDialogEx)
	//{{AFX_MSG_MAP(CListDynDialogEx)
	ON_BN_CLICKED(IDC_BROWER, OnBrower)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CDlgLoad::DoModal()
{
	SetWindowTitle(_T("Dialog for Load SSD"));
	AddDlgControl(STATICTEXT, _T("FileName"), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(EDITCONTROL, _T(""), STYLE_EDIT, EXSTYLE_EDIT, NULL, &m_FileName);
	AddDlgControl(STATICTEXT, _T(""), STYLE_STATIC, EXSTYLE_STATIC);
	AddDlgControl(BUTTON, _T("&Brower"), STYLE_BUTTON, EXSTYLE_BUTTON, NULL, NULL, IDC_BROWER);		
	return CDynDialogEx::DoModal();
}

void CDlgLoad::OnOK() 
{
	UpdateData();
	if (m_FileName.IsEmpty()) {
		AfxMessageBox("Please fill in FileName!");
		return;
	}

	CDynDialogEx::OnOK();
}

#include <Afxdlgs.h>
void CDlgLoad::OnBrower() 
{
	UpdateData();

	CFileDialog dlg(TRUE, ".key", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"SSD Key Files (*.ssd)|*.ssd||");

	if(dlg.DoModal() == IDOK) {
		m_FileName = dlg.GetPathName();
		UpdateData(FALSE);
	}
}