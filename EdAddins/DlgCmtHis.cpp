// DlgCmtHis.cpp : implementation file
//

#include "stdafx.h"
#include "edaddins.h"
#include "DlgCmtHis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCmtHis dialog


CDlgCmtHis::CDlgCmtHis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCmtHis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCmtHis)
	m_szDesp = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCmtHis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCmtHis)
	DDX_Text(pDX, IDC_DESP, m_szDesp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCmtHis, CDialog)
	//{{AFX_MSG_MAP(CDlgCmtHis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCmtHis message handlers

void CDlgCmtHis::OnOK() 
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
