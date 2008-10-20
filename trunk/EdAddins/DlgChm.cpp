// DlgChm.cpp : implementation file
//

#include "stdafx.h"
#include "edaddins.h"
#include "DlgChm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChm dialog


CDlgChm::CDlgChm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChm)
	m_bPrivate = FALSE;
	m_bStatic = FALSE;
	m_nLanguage = 0;
	m_bOpen = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgChm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChm)
	DDX_Check(pDX, IDC_PRIVATEM, m_bPrivate);
	DDX_Check(pDX, IDC_STATICM, m_bStatic);
	DDX_CBIndex(pDX, IDC_LANGUAGE, m_nLanguage);
	DDX_Check(pDX, IDC_STATIC_OPEN, m_bOpen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChm, CDialog)
	//{{AFX_MSG_MAP(CDlgChm)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChm message handlers
