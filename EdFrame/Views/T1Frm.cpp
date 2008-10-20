// T1Frm.cpp : implementation of the CT1Frame class
//

#include "stdafx.h"
#include "T1Frm.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CT1Frame

IMPLEMENT_DYNCREATE(CT1Frame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CT1Frame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CT1Frame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT1Frame construction/destruction

CT1Frame::CT1Frame()
{
	// TODO: add member initialization code here
	
}

CT1Frame::~CT1Frame()
{
}

BOOL CT1Frame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CT1Frame diagnostics

#ifdef _DEBUG
void CT1Frame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CT1Frame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CT1Frame message handlers

int CT1Frame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_T1TYPE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	return 0;
}
