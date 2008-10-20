// BSUserView.cpp : implementation file
//

#include "stdafx.h"
#include "EdUserView.h"
#include "EdMod1Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CEdMod1Ini g_ini;
/////////////////////////////////////////////////////////////////////////////
// CEdUserView
extern "C" BOOL Validate(LPCSTR szRes);
IMPLEMENT_DYNCREATE(CEdUserView, CFormView)

static CDialog* g_pDlg[6];

CEdUserView::CEdUserView()
	:CFormView(CEdUserView::IDD)
{
	//{{AFX_DATA_INIT(CEdUserView)
	//}}AFX_DATA_INIT
}

CEdUserView::~CEdUserView()
{
}

void CEdUserView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEdUserView)
	DDX_Control(pDX, IDC_TAB, m_ctlTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEdUserView, CFormView)
	//{{AFX_MSG_MAP(CEdUserView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdUserView diagnostics

#ifdef _DEBUG
void CEdUserView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEdUserView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void CEdUserView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	if (m_ctlTab.m_hWnd != NULL)
	{
		CRect rt;
		GetParentFrame()->GetClientRect(&rt);
		MoveWindow(rt.left, rt.top, rt.right, rt.bottom);
		
		GetClientRect(&rt);
		m_ctlTab.MoveWindow(rt.left, rt.top, rt.right, rt.bottom);
		m_ctlTab.m_rc = rt;
		m_ctlTab.SetCurSel(m_ctlTab.GetCurSel());
	}
}

void CEdUserView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	if(g_ini.GetVisable(0))
		m_dlgUsr.InsertTo(m_ctlTab, this);
	
	if(g_ini.GetVisable(1))
		m_dlgRes.InsertTo(m_ctlTab, this);
	
	if(g_ini.GetVisable(2))
		m_dlgGrp.InsertTo(m_ctlTab, this);
	
	if(g_ini.GetVisable(3))
		m_dlgUsrCfg.InsertTo(m_ctlTab, this);
	
	m_ctlTab.SetCurSel(0);
}

