// ModelessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Controls_Demo.h"
#include "ModelessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelessDlg dialog


CModelessDlg::CModelessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModelessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModelessDlg)
	//}}AFX_DATA_INIT
}


void CModelessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModelessDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModelessDlg, CDialog)
	//{{AFX_MSG_MAP(CModelessDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelessDlg message handlers

BOOL CModelessDlg::Create()
{
	return CDialog::Create(CModelessDlg::IDD);
}

BOOL CModelessDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();
	return TRUE;  
}

void CModelessDlg::OnOK() 
{
	DestroyWindow();
}
