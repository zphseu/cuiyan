// EdFc.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "EdFc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////
class CEdFcDoc : public CDocument
{
	DECLARE_DYNCREATE(CEdFcDoc)
};
IMPLEMENT_DYNCREATE(CEdFcDoc, CDocument)

class CEdFcView : public CHtmlView
{
	DECLARE_DYNCREATE(CEdFcView)
	virtual void OnInitialUpdate()
	{
		CHtmlView::OnInitialUpdate();
		TCHAR lpszModule[_MAX_PATH];
		if (GetModuleFileName(AfxGetResourceHandle(), lpszModule, _MAX_PATH))
		{
			CString strResourceURL;
			strResourceURL.Format(_T("res://%s/%d"), lpszModule, IDR_ABOUT);
			Navigate2(strResourceURL, NULL, NULL);
		}
	}
};

IMPLEMENT_DYNCREATE(CEdFcView, CHtmlView)

//////////////////////////////////////////////////

// CEdFcApp

BEGIN_MESSAGE_MAP(CEdFcApp, CWinApp)
	ON_COMMAND(ID_EDFC_ABOUT, OnAppAbout)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CEdFcApp 构造

CEdFcApp::CEdFcApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CEdFcApp 对象

CEdFcApp theApp;

// CEdFcApp 初始化

BOOL CEdFcApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	SetRegistryKey(_T("Edson"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CEdFcDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CEdFcView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	((CMainFrame*)m_pMainWnd)->GetDefaultView();

	return TRUE;
}

// 用于运行对话框的应用程序命令
void CEdFcApp::OnAppAbout()
{
	CDialog aboutDlg(IDD_EDFC_ABOUT);
	aboutDlg.DoModal();
}


// CEdFcApp 消息处理程序

