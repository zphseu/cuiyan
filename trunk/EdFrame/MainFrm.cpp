// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "EdFrame.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_OUTLOOK_BAR, OnViewOutlookBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTLOOK_BAR, OnUpdateViewOutlookBar)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OpenFile)		// for COutLookBar;
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

CDocTemplate* CMainFrame::GetBestTemplate(LPCTSTR lpszFileName)
{
	// find the highest confidence
	CPtrList& templateList = *(CPtrList*)((char*)AfxGetApp()->m_pDocManager + 4);
	POSITION pos = templateList.GetHeadPosition();
	CDocTemplate::Confidence bestMatch = CDocTemplate::noAttempt;
	CDocTemplate* pBestTemplate = NULL;
	CDocument* pOpenDocument = NULL;
	
	TCHAR szPath[_MAX_PATH];
	lstrcpy(szPath, lpszFileName);
	
	while (pos != NULL)
	{
		CDocTemplate* pTemplate = (CDocTemplate*)templateList.GetNext(pos);
		ASSERT_KINDOF(CDocTemplate, pTemplate);
		
		CDocTemplate::Confidence match;
		ASSERT(pOpenDocument == NULL);
		match = pTemplate->MatchDocType(szPath, pOpenDocument);
		if (match > bestMatch)
		{
			bestMatch = match;
			pBestTemplate = pTemplate;
		}
		if (match == CDocTemplate::yesAlreadyOpen)
			break;      // stop here
	}
	
	if (pBestTemplate == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_OPEN_DOC);
		return NULL;
	}
	
	return pBestTemplate;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndOutlookBar.Create(_T("OutlookBar"), this, 0))
    {
        TRACE0("Failed to create Reportbar\n");
        return -1;      // fail to create
	}
	
	m_wndOutlookBar.SetBarStyle(m_wndOutlookBar.GetBarStyle() |
        CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	
    m_wndOutlookBar.EnableDocking(CBRS_ALIGN_ANY);	
	EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndOutlookBar, AFX_IDW_DOCKBAR_LEFT);
	ShowControlBar(&m_wndOutlookBar, m_wndOutlookBar.IsVisible(), FALSE);

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OpenFile(WPARAM wParam, LPARAM lParam)
{
	LPCSTR szFile = (LPCSTR)wParam;
	CFileFind ff;
	
	if ( ff.FindFile(szFile) ) 
	{
		AfxGetApp()->OpenDocumentFile(szFile);
	}
	else 
	{
 		CDocTemplate* pBestDocTemplate = GetBestTemplate(szFile);
		if (pBestDocTemplate) 
			pBestDocTemplate->OpenDocumentFile(NULL);
	}
}

void CMainFrame::OnViewOutlookBar() 
{
	ShowControlBar(&m_wndOutlookBar, !m_wndOutlookBar.IsVisible(), FALSE);
	RecalcLayout();
}

void CMainFrame::OnUpdateViewOutlookBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndOutlookBar.IsVisible());	
}
