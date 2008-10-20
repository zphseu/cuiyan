// EdStatRptView.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EdStatRptView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int QueryDialog(HWND);
/////////////////////////////////////////////////////////////////////////////
// CEdStatRptView

IMPLEMENT_DYNCREATE(CEdStatRptView, CScrollView)

CEdStatRptView::CEdStatRptView()
{
}

CEdStatRptView::~CEdStatRptView()
{
}

BEGIN_MESSAGE_MAP(CEdStatRptView, CScrollView)
	//{{AFX_MSG_MAP(CEdStatRptView)
	ON_COMMAND(ID_FIRSTPAGE, OnFirstpage)
	ON_UPDATE_COMMAND_UI(ID_FIRSTPAGE, OnUpdateFirstpage)
	ON_COMMAND(ID_LASTPAGE, OnLastpage)
	ON_UPDATE_COMMAND_UI(ID_LASTPAGE, OnUpdateLastpage)
	ON_COMMAND(ID_NEXTPAGE, OnNextpage)
	ON_UPDATE_COMMAND_UI(ID_NEXTPAGE, OnUpdateNextpage)
	ON_COMMAND(ID_PREPAGE, OnPrepage)
	ON_UPDATE_COMMAND_UI(ID_PREPAGE, OnUpdatePrepage)
	ON_COMMAND(ID_FILE_QUERY, OnQuery)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdStatRptView drawing

void CEdStatRptView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	sizeTotal.cx = (int)(8.5*254);
	sizeTotal.cy = (int)(11*245);
	SetScrollSizes(MM_LOMETRIC, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CEdStatRptView diagnostics

#ifdef _DEBUG
void CEdStatRptView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEdStatRptView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEdStatRptView message handlers

void CEdStatRptView::OnDraw(CDC* pDC) 
{
	if (m_bFirstDraw)
	{
		m_bFirstDraw = FALSE;
		OnQuery();
	}

	if (m_Doc.IsLoaded())
		m_Doc.m_Report.DrawCurrentPage(pDC);
}

void CEdStatRptView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	pInfo->SetMaxPage( m_Doc.m_Report.GetPageCount() );
}

void CEdStatRptView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
}

BOOL CEdStatRptView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CEdStatRptView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	m_Doc.m_Report.GotoPage( pInfo->m_nCurPage - 1);
	CScrollView::OnPrint(pDC, pInfo);
}

void CEdStatRptView::OnFirstpage() 
{
	m_Doc.m_Report.m_CurPage = 0;
	Invalidate();
}

void CEdStatRptView::OnUpdateFirstpage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Doc.m_Report.m_CurPage > 0);
}

void CEdStatRptView::OnLastpage() 
{
	m_Doc.m_Report.m_CurPage = m_Doc.m_Report.m_PageCount - 1;
	Invalidate();
}

void CEdStatRptView::OnUpdateLastpage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Doc.m_Report.m_CurPage < m_Doc.m_Report.m_PageCount - 1);
}

void CEdStatRptView::OnNextpage() 
{
	m_Doc.m_Report.m_CurPage++;
	if (m_Doc.m_Report.m_CurPage > m_Doc.m_Report.m_PageCount - 1)
		m_Doc.m_Report.m_CurPage = m_Doc.m_Report.m_PageCount - 1;
	Invalidate();
}

void CEdStatRptView::OnUpdateNextpage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Doc.m_Report.m_CurPage < m_Doc.m_Report.m_PageCount - 1);
}

void CEdStatRptView::OnPrepage() 
{
	m_Doc.m_Report.m_CurPage--;
	if (m_Doc.m_Report.m_CurPage < 0)
		m_Doc.m_Report.m_CurPage = 0;
	Invalidate();
}

void CEdStatRptView::OnUpdatePrepage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Doc.m_Report.m_CurPage > 0);
}

void CEdStatRptView::OnQuery() 
{
	if (QueryDialog(m_hWnd) == IDOK && m_Doc.GetData())
		Invalidate();
}
void CEdStatRptView::OnAppAbout() 
{
	CDialog dlg(IDD_ESSTATRPTABOUTBOX);
	dlg.DoModal();
}

int CEdStatRptView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bFirstDraw = TRUE;	
	
	return 0;
}
