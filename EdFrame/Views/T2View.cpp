// T2View.cpp : implementation file
//

#include "stdafx.h"
#include "T2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CT2View

IMPLEMENT_DYNCREATE(CT2View, CListView)

CT2View::CT2View()
{
}

CT2View::~CT2View()
{
}


BEGIN_MESSAGE_MAP(CT2View, CListView)
	//{{AFX_MSG_MAP(CT2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT2View drawing

void CT2View::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CT2View diagnostics

#ifdef _DEBUG
void CT2View::AssertValid() const
{
	CListView::AssertValid();
}

void CT2View::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CT2View message handlers

void CT2View::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	SetWindowLong(m_hWnd,GWL_STYLE,GetWindowLong(m_hWnd, GWL_STYLE) | LVS_REPORT);	//���ô�������
	GetListCtrl().SetExtendedStyle(GetListCtrl().GetExtendedStyle() | LVS_EX_GRIDLINES);
	
	LV_COLUMN lvcol;
	CListCtrl *pCtrl = &GetListCtrl();
	int i = 0;
	lvcol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcol.fmt = LVCFMT_CENTER; //����
	lvcol.cx = 50;
	lvcol.iSubItem = 0;
	lvcol.pszText = "ʱ  ��";
	pCtrl->InsertColumn(i++, &lvcol);
	lvcol.cx = 80;
	lvcol.pszText = "������";
	pCtrl->InsertColumn(i++, &lvcol);
	lvcol.pszText = "�Ŷӳ���(s)";
	pCtrl->InsertColumn(i++, &lvcol);
	lvcol.pszText="����ʱ��(s)";
	pCtrl->InsertColumn(i++, &lvcol);
	lvcol.pszText="ͨ����(veh)";
	pCtrl->InsertColumn(i++, &lvcol);
	lvcol.pszText="���ڳ�(s)";
	pCtrl->InsertColumn(i++, &lvcol);
	lvcol.pszText="���ű�(%)";
	pCtrl->InsertColumn(i++, &lvcol);	
}
