// OraOutView.cpp : implementation file
//

#include "stdafx.h"
#include "OraSQL.h"
#include "OraOutView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COraOutView

IMPLEMENT_DYNCREATE(COraOutView, CListView)

COraOutView::COraOutView()
{
}

COraOutView::~COraOutView()
{
}


BEGIN_MESSAGE_MAP(COraOutView, CListView)
	//{{AFX_MSG_MAP(COraOutView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COraOutView drawing

void COraOutView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// COraOutView diagnostics

#ifdef _DEBUG
void COraOutView::AssertValid() const
{
	CListView::AssertValid();
}

void COraOutView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COraOutView message handlers

BOOL COraOutView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= ES_AUTOVSCROLL | LVS_REPORT | LVS_NOCOLUMNHEADER;
	return CListView::PreCreateWindow(cs);
}

void COraOutView::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);
	CRect rt;
	GetClientRect(rt);
	GetListCtrl().SetColumnWidth(0, rt.Width());
}

void COraOutView::OnInitialUpdate() 
{
	CRect rt;
	CListView::OnInitialUpdate();
	CListCtrl& list = GetListCtrl();
	GetClientRect(rt);
	list.InsertColumn(0, "", LVCFMT_LEFT, rt.Width() - 1);
}


