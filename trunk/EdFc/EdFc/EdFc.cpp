// EdFc.cpp : ����Ӧ�ó��������Ϊ��
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
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CEdFcApp ����

CEdFcApp::CEdFcApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CEdFcApp ����

CEdFcApp theApp;

// CEdFcApp ��ʼ��

BOOL CEdFcApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	SetRegistryKey(_T("Edson"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CEdFcDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
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

// �������жԻ����Ӧ�ó�������
void CEdFcApp::OnAppAbout()
{
	CDialog aboutDlg(IDD_EDFC_ABOUT);
	aboutDlg.DoModal();
}


// CEdFcApp ��Ϣ�������

