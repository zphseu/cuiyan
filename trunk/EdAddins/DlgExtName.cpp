// DlgExtName.cpp : implementation file
//

#include "stdafx.h"
#include "EdAddins.h"
#include "DlgExtName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgExtName dialog


CDlgExtName::CDlgExtName(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExtName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgExtName)
	m_extname = _T("");
	//}}AFX_DATA_INIT
}


void CDlgExtName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgExtName)
	DDX_Text(pDX, IDC_EXT, m_extname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgExtName, CDialog)
	//{{AFX_MSG_MAP(CDlgExtName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgExtName message handlers

void CDlgExtName::OnOK() 
{
	UpdateData();
	if (!m_extname.IsEmpty())
		CDialog::OnOK();
	else
		AfxMessageBox(_T("Please Input an extname."), MB_YESNO | MB_APPLMODAL | MB_ICONEXCLAMATION | MB_DEFBUTTON1);
}
