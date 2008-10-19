/**************************************************************
 *  Filename:    Page3.cpp
 *  Copyright:   Shanghai Baosight Software Co., Ltd.
 *
 *  Description: 演示模态窗体和非模态窗体.
 *
 *  @author:     wangyi
 *  @version     09/09/2004  wangyi  Initial Version
**************************************************************/


#include "stdafx.h"
#include "Controls_Demo.h"
#include "Page3.h"
#include "ModeDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage3 property page

IMPLEMENT_DYNCREATE(CPage3, CPropertyPage)

CPage3::CPage3() : CPropertyPage(CPage3::IDD)
{
	//{{AFX_DATA_INIT(CPage3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_MDlg = new CModelessDlg(this);
}

CPage3::~CPage3()
{
	if (m_MDlg != NULL) 
		delete m_MDlg;
}

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CPage3)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage3 message handlers

void CPage3::OnButton1() 
{
	CModeDlg dlgM;
	dlgM.DoModal();
}

void CPage3::OnButton2() 
{
	if (m_MDlg->GetSafeHwnd() == NULL)
		m_MDlg->Create();
	else
		m_MDlg->CenterWindow();
}

void CPage3::OnButton3() 
{
	AfxMessageBox(_T("报警框1"));	
}

void CPage3::OnButton4() 
{
	AfxMessageBox( _T("报警框2"), MB_OKCANCEL|MB_ICONINFORMATION );
}

void CPage3::OnButton5() 
{
	AfxMessageBox( _T("报警框3"), MB_RETRYCANCEL| MB_ICONSTOP);
}

void CPage3::OnButton7() 
{
	AfxMessageBox( _T("报警框4"), MB_YESNOCANCEL|MB_ICONQUESTION);
	
}

void CPage3::OnButton8() 
{
	CFileDialog Dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"DOC文件 (*.doc)|*.doc||",this);
	Dlg.DoModal();
}

void CPage3::OnButton6() 
{
	CFileDialog Dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"Text Files (*.txt)|*.txt||",this);
	Dlg.DoModal();	
}

void CPage3::OnButton9() 
{
	CColorDialog dlg(RGB(255, 0, 0), CC_FULLOPEN);
	dlg.DoModal();
}

void CPage3::OnButton10() 
{
	CPrintDialog dlg(FALSE);
	dlg.DoModal();
}
