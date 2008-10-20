// DlgLogin.cpp : implementation file
//

#include "stdafx.h"
#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogin)
	m_csPwd = _T("");
	m_csUID = _T("");
	//}}AFX_DATA_INIT
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogin)
	DDX_Text(pDX, IDC_PWD, m_csPwd);
	DDX_Text(pDX, IDC_UID, m_csUID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	//{{AFX_MSG_MAP(CDlgLogin)
	ON_BN_CLICKED(IDCHGPWD, OnChgpwd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin message handlers

#include "DlgChgInfo.h"
void CDlgLogin::OnChgpwd() 
{
	if (!ValidateInput()) 
		return;

	if (!m_csUID.IsEmpty())
	{
		CDlgChgInfo dlg(m_csUID, this);
		dlg.DoModal();
	}
	else
	{
		MessageBox("������д�û�����", "ע��");
	}
}

BOOL CDlgLogin::ValidateInput()
{
	UpdateData();
	if( (m_csUID.GetLength()) > 32 )
	{
		MessageBox("�û������ȱ�����32�ַ�֮��!","ע��",MB_OK);
		GetDlgItem(IDC_UID)->SetFocus();
		return FALSE;
	}
	
	if( (m_csPwd.GetLength()) > 32 )
	{
		MessageBox("���볤�ȱ�����32�ַ�֮��!","ע��",MB_OK);
		GetDlgItem(IDC_PWD)->SetFocus();
		return FALSE;
	}

	return TRUE;
}

void CDlgLogin::OnOK() 
{
	if (!ValidateInput()) 
		return;
	
	EndDialog(IDOK);
}
