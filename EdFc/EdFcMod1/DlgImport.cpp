// DlgImport.cpp : implementation file
//

#include "stdafx.h"
#include "DlgImport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImport dialog

CDlgImport::CDlgImport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgImport)
	m_szDir = _T("");
	m_szFile = _T("");
	//}}AFX_DATA_INIT
}

void CDlgImport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImport)
	DDX_Text(pDX, IDC_EDIT_DIR, m_szDir);
	DDX_Text(pDX, IDC_EDIT_FILE, m_szFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImport, CDialog)
	//{{AFX_MSG_MAP(CDlgImport)
	ON_BN_CLICKED(IDC_DIR, OnDir)
	ON_BN_CLICKED(IDC_FILE, OnFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImport message handlers

#include "PathDialog.h"

void CDlgImport::OnDir() 
{
	TCHAR szTmp[MAX_PATH];
	GetTempPath(MAX_PATH, szTmp);
	m_szDir = szTmp;
	CPathDialog dlg("BSRpter Importer", "选择一个路径放置数据文件", m_szDir);

	if (dlg.DoModal() == IDOK)
		m_szDir = dlg.GetPathName();
	else
		m_szDir = _T("");
	
	UpdateData(FALSE);
}

extern CString g_csPath;
void CDlgImport::OnFile() 
{
	m_szFile = g_csPath + CString(_T(".bsexim"));
	
	CFileDialog dlg(TRUE, _T("*.bsexim"), m_szFile, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("BSExport Files (*.bsexim)|*.bsexim|All Files (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
		m_szFile = dlg.GetPathName();
	else
		m_szFile = _T("");

	UpdateData(FALSE);
}

