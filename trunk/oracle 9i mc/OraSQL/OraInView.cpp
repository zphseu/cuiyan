// OraInView.cpp : implementation of the COraInView class
//

#include "stdafx.h"
#include "OraSQL.h"

#include "OraSQLDoc.h"
#include "OraInView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COraInView

IMPLEMENT_DYNCREATE(COraInView, CEditView)

BEGIN_MESSAGE_MAP(COraInView, CEditView)
	//{{AFX_MSG_MAP(COraInView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COraInView construction/destruction

COraInView::COraInView()
{
	// TODO: add construction code here

}

COraInView::~COraInView()
{
}

BOOL COraInView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// COraInView drawing

void COraInView::OnDraw(CDC* pDC)
{
	COraSQLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COraInView diagnostics

#ifdef _DEBUG
void COraInView::AssertValid() const
{
	CEditView::AssertValid();
}

void COraInView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

COraSQLDoc* COraInView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COraSQLDoc)));
	return (COraSQLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COraInView message handlers

