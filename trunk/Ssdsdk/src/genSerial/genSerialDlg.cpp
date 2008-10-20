// genSerialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "genSerial.h"
#include "genSerialDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenSerialDlg dialog

CGenSerialDlg::CGenSerialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGenSerialDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGenSerialDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_cssd.m_ssd.m_szProduct = _T("");
}

void CGenSerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenSerialDlg)
	DDX_Control(pDX, IDC_COMBO1, m_Type);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT1, m_cssd.m_ssd.m_szName);
	DDX_Text(pDX, IDC_EDIT2, m_cssd.m_ssd.m_szEmail);
	DDX_Text(pDX, IDC_EDIT3, m_cssd.m_ssd.m_szProduct);
	DDX_Text(pDX, IDC_EDIT4, m_cssd.m_ssd.m_szSerial);
}

BEGIN_MESSAGE_MAP(CGenSerialDlg, CDialog)
	//{{AFX_MSG_MAP(CGenSerialDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenSerialDlg message handlers

BOOL CGenSerialDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	for (int i = 0; m_cssd.szCryptType[i] != NULL; i++)
		m_Type.AddString(m_cssd.szCryptType[i]);
	
	m_Type.SetCurSel(0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGenSerialDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CGenSerialDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGenSerialDlg::OnOK() 
{
	UpdateData();
	m_cssd.GenSerial();
	UpdateData(FALSE);
}

void CGenSerialDlg::OnButton1() 
{
	CFileDialog dlg(TRUE, ".forkey", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"SSD for Key Files (*.forkey)|*.forkey||");

	if(dlg.DoModal() == IDOK) {
		if (m_cssd.LoadFromFile(dlg.GetPathName())) {
			m_Type.SetCurSel(m_cssd.m_Crypt);
			m_Path = dlg.GetPathName();
			m_Path = m_Path.Left(m_Path.ReverseFind('\\') + 1);
			m_cssd.m_ssd.m_szSerial = _T("");
			UpdateData(FALSE);
		}
	}
}

void CGenSerialDlg::OnButton2() 
{
	OnOK();
	CString szFileName = m_Path + m_cssd.m_ssd.m_szName;
	szFileName += _T(".ssd");
	m_cssd.SaveToFile(szFileName);
}
