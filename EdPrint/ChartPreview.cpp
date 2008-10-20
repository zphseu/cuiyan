// ViewPrintPreview.cpp : implementation file
//

#include "stdafx.h"
#include "ChartPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartPreview

IMPLEMENT_DYNCREATE(CChartPreview, CView)

CChartPreview::CChartPreview()
{
	m_pChart = NULL;
}

CChartPreview::~CChartPreview()
{
}


BEGIN_MESSAGE_MAP(CChartPreview, CView)
	//{{AFX_MSG_MAP(CChartPreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartPreview drawing

void CChartPreview::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CChartPreview diagnostics

#ifdef _DEBUG
void CChartPreview::AssertValid() const
{
	CView::AssertValid();
}

void CChartPreview::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChartPreview message handlers

void CChartPreview::OnFilePrintPreview()
{
	CView::OnFilePrintPreview();
}

void CChartPreview::OnFilePrint()
{
	CView::OnFilePrint();
}

BOOL CChartPreview::OnPreparePrinting(CPrintInfo* pInfo) 
{
	pInfo->m_bDirect = m_bPrintDirect
		|| LOWORD(GetCurrentMessage()->wParam) == ID_FILE_PRINT_DIRECT;
	pInfo->SetMaxPage(0);	//cycy	
	return DoPreparePrinting(pInfo);
}

void CChartPreview::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CRect rect;
	int  nPageWidth,  nPageHeight;
	int  nChartWidth, nChartHeight;
	
	m_pChart->GetClientRect(rect);	
	pDC->SetMapMode(MM_ANISOTROPIC);
	
	nPageWidth   = pDC->GetDeviceCaps(HORZRES);
	nPageHeight  = pDC->GetDeviceCaps(VERTRES);
	nChartWidth  = rect.right  - rect.left;
	nChartHeight = rect.bottom - rect.top;
	
	pDC->SetWindowExt(nChartWidth, nChartHeight);
	pDC->SetViewportExt(nPageWidth, nPageHeight);
	
	::LPtoDP(pDC->m_hDC, (POINT*)(&rect), 2);
	m_pChart->DrawToDC(pDC->m_hDC, XRT_DRAW_ENHMETAFILE, XRT_DRAWSCALE_TOMAX, 
		rect.left, rect.top, (rect.right-rect.left), (rect.bottom-rect.top));
}

void CChartPreview::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	GetParentFrame()->DestroyWindow();
}

