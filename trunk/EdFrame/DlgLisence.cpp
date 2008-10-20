// DlgLisence.cpp : implementation file
//

#include "stdafx.h"
#include "edframe.h"
#include "DlgLisence.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlgLisence dialog


CMyDlgLisence::CMyDlgLisence(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlgLisence::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlgLisence)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMyDlgLisence::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlgLisence)
	DDX_Control(pDX, IDC_URL, m_Url);
	DDX_Control(pDX, IDC_EMAIL, m_Email);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlgLisence, CDialog)
	//{{AFX_MSG_MAP(CMyDlgLisence)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgLisence message handlers

BOOL CMyDlgLisence::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Email.SetURL("mailto:edsoncy@citiz.net");
	m_Url.SetURL("http://edsoncy.objectis.net/");
	
	return TRUE;
}
