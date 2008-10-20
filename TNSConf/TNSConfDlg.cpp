// TNSConfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TNSConf.h"
#include "TNSConfDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTNSConfDlg dialog

CTNSConfDlg::CTNSConfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTNSConfDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTNSConfDlg)
	m_szHost = _T("");
	m_szSvr = _T("");
	m_szTns = _T("");
	m_szPort = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_uCurSel = -1;
	m_bError = FALSE;
	m_bToSave = FALSE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTNSConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTNSConfDlg)
	DDX_Control(pDX, IDC_LIST, m_ctlList);
	DDX_Text(pDX, IDC_HOST, m_szHost);
	DDX_Text(pDX, IDC_SERVER, m_szSvr);
	DDX_Text(pDX, IDC_TNS, m_szTns);
	DDX_Text(pDX, IDC_PORT, m_szPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTNSConfDlg, CDialog)
	//{{AFX_MSG_MAP(CTNSConfDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_WM_CREATE()
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_EN_CHANGE(IDC_HOST, OnChanged)
	ON_EN_CHANGE(IDC_PORT, OnChanged)
	ON_EN_CHANGE(IDC_SERVER, OnChanged)
	ON_EN_CHANGE(IDC_TNS, OnChanged)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTNSConfDlg message handlers

int CTNSConfDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_File.Load())
		return -1;
	
	return 0;
}

BOOL CTNSConfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	Freshlist();

	return TRUE;
}

void CTNSConfDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CDialog dlgAbout(IDD_ABOUTBOX);
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTNSConfDlg::OnPaint() 
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
HCURSOR CTNSConfDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTNSConfDlg::OnSelchangeList() 
{
	if (m_bChange)
	{
		UpdateData();
		if (m_szHost.IsEmpty() || m_szPort.IsEmpty() || m_szTns.IsEmpty() || m_szSvr.IsEmpty())
		{
			MessageBox( _T("Please fill out all essential data.!"), _T("Error"), MB_OK);
			m_ctlList.SetCurSel(m_uCurSel);
			m_bError = TRUE;
			return;
		}

		if (m_bToSave || MessageBox( _T("TnsConfig has changed, do u want to save?"), _T("Save"), 
			MB_YESNO | MB_ICONQUESTION ) == IDYES)
		{
			
			m_File.Tns[m_uCurSel].m_csContext[COneTns::HOST] = m_szHost;
			m_File.Tns[m_uCurSel].m_csContext[COneTns::PORT] = m_szPort;
			m_File.Tns[m_uCurSel].m_csContext[COneTns::TNSNAME]  = m_szTns;
			m_File.Tns[m_uCurSel].m_csContext[COneTns::SVRNAME]  = m_szSvr;
			Freshlist(m_uCurSel);
		}
		else
		{
			m_bError = TRUE;
		}
	}	

	m_uCurSel = m_ctlList.GetCurSel();
	
	m_szHost = m_File.Tns[m_uCurSel].m_csContext[COneTns::HOST];
	m_szPort = m_File.Tns[m_uCurSel].m_csContext[COneTns::PORT];
	m_szTns  = m_File.Tns[m_uCurSel].m_csContext[COneTns::TNSNAME];
	m_szSvr  = m_File.Tns[m_uCurSel].m_csContext[COneTns::SVRNAME];
	m_bChange = FALSE;
	
	UpdateData(FALSE);
	m_bError = FALSE;
}

void CTNSConfDlg::OnChanged() 
{
	m_bChange = TRUE;
}

void CTNSConfDlg::OnDel() 
{
	CString szTmp;
	UpdateData();
	szTmp.Format(_T("Are u sure to delete TNS:\n[ %s ]?"), m_szTns);

	if (MessageBox( szTmp, _T("Delete"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
	{
		m_File.Tns.RemoveAt(m_uCurSel);
		Freshlist();
	}
}

void CTNSConfDlg::OnOK() 
{
	m_bToSave = TRUE;
	OnSelchangeList();
	m_bToSave = FALSE;
	if (!m_bError)
	{
		m_File.Save();
		Freshlist(m_uCurSel);
	}
}

void CTNSConfDlg::OnAdd() 
{	
	LPCTSTR szNewTns = _T("NewTNS");
	for (int i = 0; i < m_File.Tns.GetSize(); i++)
	{
		if (m_File.Tns[i].m_csContext[COneTns::TNSNAME].CompareNoCase(szNewTns) == 0)
			break;
	}

	// 已经存在新的
	COneTns newTns;
	if (i >= m_File.Tns.GetSize())
	{
		COneTns newTns;
		newTns.m_csContext[COneTns::TNSNAME] = szNewTns;
		m_File.Tns.Add(newTns);
		i = m_File.Tns.GetSize() - 1;
	}

	Freshlist(i);
	m_bChange = TRUE;
}

void CTNSConfDlg::Freshlist(int nSel)
{
	// add TNS NAME
	while ( m_ctlList.DeleteString(0) != LB_ERR );

	for (int i = 0; i < m_File.Tns.GetSize(); i++)
		m_ctlList.AddString(m_File.Tns[i].m_csContext[COneTns::TNSNAME]);
	
	if (m_ctlList.GetCount() > 0)
	{
		m_uCurSel = nSel;
		m_ctlList.SetCurSel(m_uCurSel);
		m_bChange = FALSE;
		OnSelchangeList();
	}
}

#include "DlgLogin.h"
#include "OraDB.h"
void CTNSConfDlg::OnTest() 
{
	CDlgLogin dlg;

	if (m_bChange)
		OnOK();
	else
		UpdateData();

	do{
		COraDB db;

		try 
		{
			if (FAILED(db.Open(m_szTns, dlg.m_szUid, dlg.m_szPwd)))
				throw db.GetLog();
			throw 0;
		}
		catch (int)
		{
			db.Close();
			CString szTmp;
			szTmp.Format(_T("Connect success!\n\n%s"), db.GetLog());
			AfxMessageBox(szTmp);
			break;					
		}
		catch (...)
		{
			if( AfxMessageBox( _T("Connect fail, do u\n want to change schema and test again?"), MB_YESNO ) == IDNO)
				break;
		}
		
	} while (dlg.DoModal() == IDOK);
}
