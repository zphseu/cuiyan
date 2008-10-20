// ViewPrintPreview.cpp : implementation file
//

#include "stdafx.h"
#include "GridPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridPreview

IMPLEMENT_DYNCREATE(CGridPreview, CView)

CGridPreview::CGridPreview()
{
	m_pCtrl = NULL;
}

CGridPreview::~CGridPreview()
{
}


BEGIN_MESSAGE_MAP(CGridPreview, CView)
	//{{AFX_MSG_MAP(CGridPreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridPreview drawing

void CGridPreview::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CGridPreview diagnostics

#ifdef _DEBUG
void CGridPreview::AssertValid() const
{
	CView::AssertValid();
}

void CGridPreview::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridPreview message handlers

void CGridPreview::OnFilePrintPreview()
{
	CView::OnFilePrintPreview();
}

void CGridPreview::OnFilePrint()
{
	CView::OnFilePrint();
}

BOOL CGridPreview::OnPreparePrinting(CPrintInfo* pInfo) 
{
	pInfo->m_bDirect = m_bPrintDirect
		|| LOWORD(GetCurrentMessage()->wParam) == ID_FILE_PRINT_DIRECT;
	
	return DoPreparePrinting(pInfo);
}

void CGridPreview::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	if (m_pCtrl) m_pCtrl->OnMyBeginPrinting(pDC, pInfo);
}

void CGridPreview::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if (m_pCtrl) m_pCtrl->OnMyPrint(pDC, pInfo);
}

void CGridPreview::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	if (m_pCtrl) m_pCtrl->OnMyEndPrinting(pDC, pInfo);
}

void CGridPreview::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	
	if (m_pCtrl)
		m_pCtrl->ShowWindow(SW_SHOW);
	
	GetParentFrame()->DestroyWindow();
}

