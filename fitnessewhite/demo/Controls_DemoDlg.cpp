// Controls_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Controls_Demo.h"
#include "Controls_DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControls_DemoDlg dialog

CControls_DemoDlg::CControls_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControls_DemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControls_DemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CControls_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControls_DemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CControls_DemoDlg, CDialog)
	//{{AFX_MSG_MAP(CControls_DemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControls_DemoDlg message handlers

BOOL CControls_DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_sheet.AddPage(&m_page3);                               //添加页3到表
	m_sheet.AddPage(&m_page4);                               //添加页4到表
	
	m_sheet.Create(this, WS_CHILD | WS_VISIBLE, 0);          //创建表
	m_sheet.ModifyStyleEx(0, WS_EX_CONTROLPARENT);           //设置扩展风格
	m_sheet.ModifyStyle(0, WS_TABSTOP);                      //设置风格
	
	m_sheet.SetWindowPos(NULL, 0, 0, 0, 0,                   //设置尺寸SWP_NOSIZE不改变页原来尺寸
		SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE  );

	m_sheet.SetActivePage(&m_page4);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CControls_DemoDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CControls_DemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
