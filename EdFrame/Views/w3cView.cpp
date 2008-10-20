// w3cView.cpp : implementation of the CW3CView class
//

#include "stdafx.h"
#include "w3cDoc.h"
#include "w3cView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CW3CView

IMPLEMENT_DYNCREATE(CW3CView, CHtmlView)

BEGIN_MESSAGE_MAP(CW3CView, CHtmlView)
	//{{AFX_MSG_MAP(CW3CView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_BUTTON0, ID_BUTTON6, OnButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CW3CView construction/destruction

CW3CView::CW3CView()
{
	m_szHome = _T("http://edsoncy.objectis.net/");
}

CW3CView::~CW3CView()
{
}

BOOL CW3CView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CW3CView drawing

void CW3CView::OnDraw(CDC* pDC)
{
}

void CW3CView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	Navigate2(m_szHome,NULL,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CW3CView diagnostics

#ifdef _DEBUG
void CW3CView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CW3CView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CW3CView message handlers

void CW3CView::OnButton(UINT id)
{
	switch(id) 
	{
	case ID_BUTTON0:	
		GoBack();
		break;
	case ID_BUTTON1:
		GoForward();
		break;
	case ID_BUTTON2:
		Stop();
		break;
	case ID_BUTTON3:
		Refresh();
		break;
	case ID_BUTTON4:
		Navigate2(m_szHome, NULL, NULL);
		break;
	case ID_BUTTON5:
		CHtmlView::OnFilePrint();
		break;
	case ID_BUTTON6:
		break;
	default:
		;
	}
}
