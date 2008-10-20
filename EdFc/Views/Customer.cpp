// CustomerContact.cpp : implementation file
//

#include "stdafx.h"
#include "Customer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomer

IMPLEMENT_DYNCREATE(CCustomer, CFormView)

CCustomer::CCustomer()
	: CFormView(CCustomer::IDD)
{
	//{{AFX_DATA_INIT(CCustomer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCustomer::~CCustomer()
{
}

void CCustomer::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomer)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomer, CFormView)
	//{{AFX_MSG_MAP(CCustomer)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomer diagnostics

#ifdef _DEBUG
void CCustomer::AssertValid() const
{
	CFormView::AssertValid();
}

void CCustomer::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomer message handlers

void CCustomer::OnButton1() 
{
	AfxMessageBox("WOWWOWWWW!!!!!!!");
	
}
