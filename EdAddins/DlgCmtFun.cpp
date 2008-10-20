// DlgCmtFun.cpp : implementation file
//

#include "stdafx.h"
#include "edaddins.h"
#include "DlgCmtFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCmtFun dialog


CDlgCmtFun::CDlgCmtFun(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCmtFun::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCmtFun)
	m_szDesp = _T("");
	m_szDetail = _T("");
	m_szReturn = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCmtFun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCmtFun)
	DDX_Text(pDX, IDC_DESP, m_szDesp);
	DDX_Text(pDX, IDC_DETAIL, m_szDetail);
	DDX_Text(pDX, IDC_RETURN, m_szReturn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCmtFun, CDialog)
	//{{AFX_MSG_MAP(CDlgCmtFun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCmtFun message handlers

void CDlgCmtFun::OnOK() 
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
