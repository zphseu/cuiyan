// BSRpterView.cpp : implementation file
//

#include "stdafx.h"
#include "EdRptDoc.h"
#include "EdRptView.h"
#include "EdRptExport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int QueryDialog(HWND);
extern void ShowMessage(HWND, LPCTSTR, ...);
/////////////////////////////////////////////////////////////////////////////
// CEdRptView
IMPLEMENT_DYNCREATE(CEdRptView, CView)

BEGIN_MESSAGE_MAP(CEdRptView, CView)
	//{{AFX_MSG_MAP(CEdRptView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_APP_ABOUT, OnFileAbout)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_IMPORT, OnFileImport)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_COMMAND(ID_FILE_QUERY, OnFileQuery)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////
CEdRptView::CEdRptView()
{
	//{{AFX_DATA_INIT(CEdRptView)
	//}}AFX_DATA_INIT
	m_pWndToolBar = NULL;
	m_pProgress = NULL;
	m_pStatusBar= NULL;
}

CEdRptView::~CEdRptView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEdRptView diagnostics
#ifdef _DEBUG
void CEdRptView::AssertValid() const
{
	CView::AssertValid();
}

void CEdRptView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoView drawing

void CEdRptView::OnDraw(CDC* pDC) 
{
	if (m_bFirstDraw)
	{
		m_bFirstDraw = FALSE;
		OnFileQuery();
		m_pWndToolBar = (CToolBar*) AfxGetMainWnd()->SendMessage(WM_USER+1, 0, 0);
		ASSERT(m_pWndToolBar);
	}
	
	// modify 20030927 让每次都可以选择是否使用默认打印机打印
	if (doc.m_bDefaultPrint)
	{
		int nButton = m_pWndToolBar->GetCount();
		for (int i = 0; i < nButton; i++)
		{
			if (m_pWndToolBar->GetItemID(i) == ID_FILE_PRINT)
			{
				UINT nID, nStyle;
				int iImage;
				m_pWndToolBar->GetButtonInfo(i, nID, nStyle, iImage);
				m_pWndToolBar->SetButtonInfo(i, ID_FILE_PRINT_DIRECT, nStyle, iImage);
				break;						
			}
		}
	}
	
	ChangeWidth();
}

/////////////////////////////////////////////////////////////////////////////
// CEdRptView printing
void CEdRptView::OnFilePrintPreview()
{
	m_pWndToolBar->SetFocus();
	if (doc.IsLoad())
		CView::OnFilePrintPreview();
	else
		MessageBox("没有数据，请先进行查询！", "BSRpter", MB_OK);
}

void CEdRptView::OnFilePrint()
{
	if (doc.IsLoad())
		CView::OnFilePrint();
	else
		MessageBox("没有数据，请先进行查询！", "BSRpter", MB_OK);
}

BOOL CEdRptView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CEdRptView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	/*	第一次打印时无法改动打印机设置，而只能改变以后的打印机设置，因此目前撤销该功能。
	if(pDC->IsPrinting() && doc.m_bDefaultPrint)
	{
		HGLOBAL hDevMode = pInfo->m_pPD->m_pd.hDevMode;
		DEVMODE* lpDevMode = (DEVMODE*)::GlobalLock(hDevMode); 		
		lpDevMode->dmOrientation = doc.m_bVertical ? DMORIENT_PORTRAIT : DMORIENT_LANDSCAPE;
		::GlobalUnlock(hDevMode); 		
	}
*/	
	CView::OnPrepareDC(pDC, pInfo);
}

void CEdRptView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
 	CGridCtrl& Grid = doc.m_Grid;
 	for (int i = 0; i < doc.GetFieldCount(); i++)
 		Grid.SetColumnWidth(i, doc.m_ColFmt[i].width);

// 	HGLOBAL hDevMode = pInfo->m_pPD->m_pd.hDevMode;
// 	DEVMODE* lpDevMode = (DEVMODE*)::GlobalLock(hDevMode); 		
// 	int nWidth  = lpDevMode->dmPaperWidth;
// 	::GlobalUnlock(hDevMode);
// 	ChangeWidth(nWidth * 2); 
	
	doc.m_Grid.OnBeginPrinting(pDC, pInfo);
}

void CEdRptView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	SetFocus();
	doc.m_Grid.OnPrint(pDC, pInfo);
}

void CEdRptView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	doc.m_Grid.OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CEdRptView message handlers
void CEdRptView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CGridCtrl *pGrid = &doc.m_Grid;
	
	// Create the Gridctrl window
	CRect rect;
	GetClientRect(rect);
	pGrid->Create(rect, this, 100);	
	doc.SetHWnd(m_hWnd);
}

void CEdRptView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (doc.m_Grid.GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		doc.m_Grid.MoveWindow(rect);
	}
}

BOOL CEdRptView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEdRptView message handlers -- Record Brower
void CEdRptView::ChangeWidth()
{
	CGridCtrl& Grid = doc.m_Grid;
	int nFieldCount = doc.GetFieldCount();

	if (nFieldCount <= 0)
		return;

	CRect rt;
	GetClientRect(&rt);
	int WndWidth = rt.Width() - nFieldCount - Grid.GetFixedColumnCount() - 1;
	
	int TmplWidth = 0;
	for (int i = 0; i < nFieldCount; i++)
		TmplWidth += doc.m_ColFmt[i].width;
	
	int *width = new int[nFieldCount];
	
	if (width == NULL)
		return;
	
	int w = 0;
	for (i = 0; i < nFieldCount; i++)
	{
		width[i] = int( doc.m_ColFmt[i].width / (float)TmplWidth * WndWidth );
		w += width[i];
	}
	
	width[nFieldCount - 1] += (WndWidth - w);
	
	for (i = 0; i < nFieldCount; i++)
		Grid.SetColumnWidth(i, width[i]);
	
	SAFE_DELETE_ARRAY(width);
}

void CEdRptView::OnFileAbout() 
{
	CDialog aboutDlg(IDD_EDRPTABOUTBOX);
	aboutDlg.DoModal();
}

BOOL CEdRptView::CreateProgress(int n)
{
	CWnd *pMainWnd = AfxGetMainWnd();
	if (pMainWnd)
	{
		// If main window is a frame window, use normal methods...
		if (pMainWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
		{
			CWnd* pMessageBar = ((CFrameWnd*)pMainWnd)->GetMessageBar();
			m_pStatusBar = DYNAMIC_DOWNCAST(CStatusBar, pMessageBar);
		}
		// otherwise traverse children to try and find the status bar...
		else
			m_pStatusBar = DYNAMIC_DOWNCAST(CStatusBar, pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR));
	}
    

    CRect rect, rtWnd;
    int nIndex = m_pWndToolBar->GetCount() - 1;
	
	SAFE_DELETE(m_pProgress);
	m_pProgress = new CProgressCtrlX;
	if (!m_pProgress->Create(PBS_SMOOTH | WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 0, 0), m_pWndToolBar, ID_FILE_PROGRESS))
    {
        TRACE("Failed to create Progress\n");
        return FALSE;
    }

	m_pWndToolBar->GetItemRect(nIndex, &rect);
	m_pWndToolBar->GetClientRect(&rtWnd);
	int nWidth = rtWnd.Width() - rect.Width() * nIndex;
	rect.right = rect.left + nWidth * 3 / 4;
	rect.top += (rect.Height() / 8);
	rect.bottom -= (rect.Height() / 8);

	m_pProgress->SetPos(0);
	m_pProgress->SetStep(1);
	m_pProgress->SetRange(0, n);
	m_pProgress->SetTextFormat("%d%%", PBS_SHOW_PERCENT);
	m_pProgress->SetGradientColors(::GetSysColor(2), ::GetSysColor(27));	
	m_pProgress->MoveWindow(&rect);
    return TRUE;
}

void CEdRptView::StepProgress(int n, int i, BOOL bExport)
{
	CString strMsg;
	if (m_pProgress)
	{
		strMsg.Format("%d%%", i / n * 100 );
		m_pProgress->StepIt();
		m_pWndToolBar->UpdateWindow();		
	}

	if (m_pStatusBar)
	{
		CString csTmp;
		if (bExport)
			csTmp = "已导出 %d 条记录中的 %d 条。";
		else
			csTmp = "已载入 %d 条记录中的 %d 条。";

		strMsg.Format(csTmp, n, i+1);
		m_pStatusBar->SetPaneText(0, strMsg);
		m_pStatusBar->UpdateWindow();
	}
}

void CEdRptView::DestroyProgress()
{
 	SAFE_DELETE(m_pProgress);
}

void CEdRptView::OnFileExport() 
{
	if (doc.IsLoad())
	{
		CEdRptExport bsExport(&doc);
		bsExport.DoExporting();
	}
	else
		ShowMessage(m_hWnd, "没有数据，请先进行查询！");
}

void CEdRptView::OnFileImport() 
{
	CEdRptExport bsExport(&doc);
	bsExport.DoImporting();
}

void CEdRptView::OnFileQuery() 
{
	if (QueryDialog(m_hWnd) == IDOK && doc.LoadFrom() && doc.GetData())
		Invalidate();
}
int CEdRptView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bFirstDraw = TRUE;
	
	return 0;
}
