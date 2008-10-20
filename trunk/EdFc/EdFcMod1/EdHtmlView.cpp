// BSHtmlView.cpp : implementation file
//

#include "stdafx.h"
#include "EdHtmlView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_csData;
/////////////////////////////////////////////////////////////////////////////
// CEdHtmlView
IMPLEMENT_DYNCREATE(CEdHtmlView, CHtmlView)

CEdHtmlView::CEdHtmlView()
{
	if (g_csData.IsEmpty())
		m_szHome = _T("http://www.edson.thefreeserver.com");
	else
		m_szHome = g_csData;
}

CEdHtmlView::~CEdHtmlView()
{
}

BEGIN_MESSAGE_MAP(CEdHtmlView, CHtmlView)
	//{{AFX_MSG_MAP(CEdHtmlView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_BUTTON0, ID_BUTTON5, OnButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdHtmlView diagnostics

#ifdef _DEBUG
//##ModelId=3F430FB70040
void CEdHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

//##ModelId=3F430FB70047
void CEdHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEdHtmlView message handlers
void CEdHtmlView::OnButton(UINT id)
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
	default:
		;
	}
}

void CEdHtmlView::OnInitialUpdate() 
{
	Navigate2(m_szHome, NULL, NULL);
}
