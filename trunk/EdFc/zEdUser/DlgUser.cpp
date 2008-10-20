// DlgUser.cpp : implementation file
//

#include "stdafx.h"
#include "DlgUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUser dialog
extern "C" BOOL Validate(LPCSTR szRes);

CDlgUser::CDlgUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUser)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUser)
	DDX_Control(pDX, IDC_TAB, m_ctlTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUser, CDialog)
	//{{AFX_MSG_MAP(CDlgUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUser message handlers

BOOL CDlgUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_dlgUsr.InsertTo(m_ctlTab, this);
	m_dlgRes.InsertTo(m_ctlTab, this);
	m_dlgGrp.InsertTo(m_ctlTab, this);
	m_dlgUsrCfg.InsertTo(m_ctlTab, this);
	
	m_ctlTab.SetCurSel(0);	

	return TRUE;
}
