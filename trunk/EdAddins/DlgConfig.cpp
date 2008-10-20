// DlgAutoSave.cpp : implementation file
//

#include "stdafx.h"
#include "EdAddins.h"
#include "DlgConfig.h"
#include "TimeWinAutoSave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CTimeWinAutoSave* gTimeWin;
/////////////////////////////////////////////////////////////////////////////
// CDlgConfig dialog


CDlgConfig::CDlgConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConfig)
	m_bSaveDSW = TRUE;
	m_bSaveFiles = TRUE;
	m_nSaveTime = 10;
	m_bByDialog = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConfig)
	DDX_Check(pDX, IDC_SAVEDSW, m_bSaveDSW);
	DDX_Check(pDX, IDC_SAVEFILES, m_bSaveFiles);
	DDX_Text(pDX, IDC_MIN, m_nSaveTime);
	DDV_MinMaxUInt(pDX, m_nSaveTime, 0, 60);
	DDX_Check(pDX, IDC_BYDIALOG, m_bByDialog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgConfig)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConfig message handlers

void CDlgConfig::OnOK() 
{
	UpdateData();

	gTimeWin->setPeriod(m_nSaveTime);
	gTimeWin->setSaveFiles(m_bSaveFiles != 0);
	gTimeWin->setSaveWorkspace(m_bSaveDSW != 0);
	gTimeWin->SetByBialog(m_bByDialog != 0);

	CDialog::OnOK();
}

BOOL CDlgConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN))->SetRange(0, 60);

	return TRUE;
}

int CDlgConfig::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_nSaveTime = gTimeWin->getPeriod();
	m_bSaveFiles = gTimeWin->getSaveFiles() ? 1 : 0;
	m_bSaveDSW = gTimeWin->getSaveWorkspace() ? 1 : 0;
	m_bByDialog = gTimeWin->getByDialog() ? 1 : 0;
	return 0;
}

