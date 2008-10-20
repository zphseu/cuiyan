// DlgCmtNor.cpp : implementation file
//

#include "stdafx.h"
#include "edaddins.h"
#include "DlgCmtNor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCmtNor dialog


CDlgCmtNor::CDlgCmtNor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCmtNor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCmtNor)
	m_szDesp = _T("");
	m_szDetail = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCmtNor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCmtNor)
	DDX_Text(pDX, IDC_DESP, m_szDesp);
	DDX_Text(pDX, IDC_DETAIL, m_szDetail);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCmtNor, CDialog)
	//{{AFX_MSG_MAP(CDlgCmtNor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCmtNor message handlers

void CDlgCmtNor::OnOK() 
{
	UpdateData();
	if (m_szDesp.IsEmpty())
	{
		MessageBox( _T("Must fill in desp data."), _T("Exclamation"), 
			MB_OK | MB_ICONEXCLAMATION );
		return;
	}	
	CDialog::OnOK();
}
