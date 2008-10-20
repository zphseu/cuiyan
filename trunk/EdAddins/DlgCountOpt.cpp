// DlgCountOpt.cpp : implementation file
//

#include "stdafx.h"
#include "EdAddins.h"
#include "DlgCountOpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCountOpt dialog


CDlgCountOpt::CDlgCountOpt(CString exts, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCountOpt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCountOpt)
	//}}AFX_DATA_INIT
	m_exts = exts;
}


void CDlgCountOpt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCountOpt)
	DDX_Control(pDX, IDC_LIST, m_clist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCountOpt, CDialog)
	//{{AFX_MSG_MAP(CDlgCountOpt)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCountOpt message handlers

BOOL CDlgCountOpt::OnInitDialog() 
{
	CDialog::OnInitDialog();
	OnReset();
	return TRUE;
}

void CDlgCountOpt::OnOK() 
{
	// TODO: Add extra validation here
	int pos = m_clist.GetCount();
	CString tmp;
	m_exts = _T("");
	for (int i = 0; i < pos; i++)
	{
		m_clist.GetText(i, tmp);
		m_exts += (tmp + ";");
	}
	CDialog::OnOK();
}

#include "DlgExtName.h"
void CDlgCountOpt::OnInsert() 
{
	int pos = m_clist.GetCurSel();
	CDlgExtName dlg;
	if (dlg.DoModal() == IDOK)
		m_clist.InsertString(pos, dlg.m_extname);
}

void CDlgCountOpt::OnDelete() 
{
	int pos = m_clist.GetCurSel();
	m_clist.DeleteString(pos);
}

void CDlgCountOpt::OnReset() 
{
	CString cStr = m_exts;
	int pos = m_clist.GetCount();
	for(int i = 0; i < pos; i++)
		m_clist.DeleteString(i);

	while((pos = cStr.Find(";")) > 0)
	{
		m_clist.AddString(cStr.Left(pos));
		cStr = cStr.Mid(pos + 1);
	}
	m_clist.SetCurSel(0);
}
