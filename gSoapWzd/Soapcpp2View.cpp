// Soapcpp2view.cpp : implementation of the CSoapcpp2View class
//

#include "stdafx.h"
#include "gSoapWzd.h"
#include "DlgReport.h"
#include "SoapSrc.h"
#include "Soapcpp2view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoapcpp2View

IMPLEMENT_DYNCREATE(CSoapcpp2View, CFormView)

BEGIN_MESSAGE_MAP(CSoapcpp2View, CFormView)
//{{AFX_MSG_MAP(CSoapcpp2View)
ON_BN_CLICKED(IDC_CHECK_CLIENT, OnCheckClient)
ON_BN_CLICKED(IDC_CHECK_SERVER, OnCheckServer)
ON_BN_CLICKED(IDC_BTN_BROWER_HEADFILE, OnBtnBrowerHeadfile)
ON_BN_CLICKED(IDC_BTN_BROWER_PATH, OnBtnBrowerPath)
ON_BN_CLICKED(IDC_BTN_GENERATE, OnBtnGenerate)
	ON_BN_CLICKED(IDC_RADIO_COMPILER3, OnRadioCompiler3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoapcpp2View construction/destruction

CSoapcpp2View::CSoapcpp2View()
: CFormView(CSoapcpp2View::IDD)
{
	//{{AFX_DATA_INIT(CSoapcpp2View)
	m_bC = FALSE;
	m_bH = FALSE;
	m_bM = FALSE;
	m_bW = FALSE;
	m_bServer = TRUE;
	m_bClient = TRUE;
	m_nClient = 0;
	m_nCompiler = 0;
	m_nServer = 1;
	m_nVersion = 0;
	m_csHeadFile = _T("");
	m_csPrjName = _T("");
	m_csPrjPath = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here
#ifdef _DEBUG
	m_csHeadFile = _T("E:\\Temp\\env\\env.h");
	m_csPrjPath = _T("E:\\Temp\\env");
	m_csPrjName = _T("env");
#endif	
}

CSoapcpp2View::~CSoapcpp2View()
{
}

void CSoapcpp2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoapcpp2View)
	DDX_Check(pDX, IDC_CHECK_C, m_bC);
	DDX_Check(pDX, IDC_CHECK_H, m_bH);
	DDX_Check(pDX, IDC_CHECK_M, m_bM);
	DDX_Check(pDX, IDC_CHECK_W, m_bW);
	DDX_Check(pDX, IDC_CHECK_SERVER, m_bServer);
	DDX_Check(pDX, IDC_CHECK_CLIENT, m_bClient);
	DDX_Radio(pDX, IDC_RADIO_CLIENT, m_nClient);
	DDX_Radio(pDX, IDC_RADIO_COMPILER, m_nCompiler);
	DDX_Radio(pDX, IDC_RADIO_SERVER, m_nServer);
	DDX_Radio(pDX, IDC_RADIO_VERSION, m_nVersion);
	DDX_Text(pDX, IDC_EDIT_HEADFILE, m_csHeadFile);
	DDX_Text(pDX, IDC_EDIT_PRJNAME, m_csPrjName);
	DDX_Text(pDX, IDC_EDIT_PROPATH, m_csPrjPath);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSoapcpp2View diagnostics

#ifdef _DEBUG
void CSoapcpp2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CSoapcpp2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSoapcpp2View message handlers

void CSoapcpp2View::OnCheckClient() 
{
	UpdateData();
	GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(m_bClient);
	GetDlgItem(IDC_RADIO_CLIENT1)->EnableWindow(m_bClient);
	GetDlgItem(IDC_BTN_GENERATE)->EnableWindow(m_bClient || m_bServer);
}

void CSoapcpp2View::OnCheckServer() 
{
	UpdateData();
	GetDlgItem(IDC_RADIO_SERVER)->EnableWindow(m_bServer);
	GetDlgItem(IDC_RADIO_SERVER1)->EnableWindow(m_bServer);
	GetDlgItem(IDC_RADIO_SERVER2)->EnableWindow(m_bServer);
	//GetDlgItem(IDC_RADIO_SERVER3)->EnableWindow(m_bServer);
	GetDlgItem(IDC_RADIO_SERVER4)->EnableWindow(m_bServer);
	GetDlgItem(IDC_BTN_GENERATE)->EnableWindow(m_bClient || m_bServer);
}

void CSoapcpp2View::OnBtnBrowerHeadfile() 
{
	CFileDialog dlg(TRUE, ".h", m_csHeadFile, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		"C/C++ Head Files (*.h;*.hpp;*.hxx)|*.h;*.hpp;*.hxx|All Files (*.*)|*.*||");
	if (dlg.DoModal() == IDOK)
	{		
		m_csHeadFile = dlg.GetPathName();
		m_csPrjPath = m_csHeadFile.Left(m_csHeadFile.ReverseFind(_T('\\')));
		m_csPrjName = m_csHeadFile.Right(m_csHeadFile.GetLength() - m_csPrjPath.GetLength() - 1);
		m_csPrjName = m_csPrjName.Left(m_csPrjName.ReverseFind(_T('.')));
		m_csPrjPath += _T("\\src");
		UpdateData(FALSE);
	}
}

void CSoapcpp2View::OnBtnBrowerPath() 
{
	LPMALLOC pMalloc;//利用shell扩展功能
	if (SUCCEEDED(SHGetMalloc(&pMalloc)))	//为生成目录选择对话框分配自由内存
	{
		BROWSEINFO bi;
		ZeroMemory(&bi,sizeof(bi));	//清零分配的空间
		char pszDirName[MAX_PATH];	//存放选择的目录名
		LPITEMIDLIST pidl;
		bi.hwndOwner = GetSafeHwnd();
		bi.pidlRoot = NULL;
		bi.pszDisplayName = pszDirName;
		bi.lpszTitle = _T("Select the folder of this prject:");
		bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
		bi.lpfn = NULL;
		bi.lParam = 0;
		if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)//调用选择目录对话框
		{
			if (::SHGetPathFromIDList(pidl, pszDirName))//获得所选择的目录
			{ 
				m_csPrjPath = pszDirName;
				UpdateData(FALSE);				
			}
			pMalloc->Free(pidl);//释放使用完的资源
		}
		pMalloc->Release();//释放使用完的资源
	}
}

void CSoapcpp2View::OnBtnGenerate() 
{
	UpdateData();

	if (m_csPrjPath.IsEmpty() || m_csPrjName.IsEmpty() || m_csHeadFile.IsEmpty())
 	{
 		AfxMessageBox(_T("Please fill with infomation!"));
 		return;
 	}
	
	CDlgReport dlg;
	dlg.sArgs = AfxGetApp()->m_pszHelpFilePath;
	dlg.sArgs = dlg.sArgs.Left(dlg.sArgs.ReverseFind(_T('\\')));
	dlg.sArgs += _T("\\soapcpp2.exe");
	if (m_bC)	dlg.sArgs += _T(" -c ");
	if (m_bH)	dlg.sArgs += _T(" -h ");
	if (m_bM)	dlg.sArgs += _T(" -m ");
	if (!m_bW)	dlg.sArgs += _T(" -w ");
	if (m_nVersion == 1) dlg.sArgs += _T(" -2 ");
	dlg.sArgs += _T(" -d\"") + m_csPrjPath + _T("\" -p") + m_csPrjName + _T(" ") + m_csHeadFile;
	
	dlg.DoModal();

	CSoapSrc src;
	src.DoModal(this);
}

void CSoapcpp2View::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}


void CSoapcpp2View::OnRadioCompiler3() 
{
	UpdateData();
	m_bC = TRUE;
	UpdateData(FALSE);
}
