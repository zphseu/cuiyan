// T2Doc.cpp : implementation file
//

#include "stdafx.h"
#include "T2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CT2Doc

IMPLEMENT_DYNCREATE(CT2Doc, CDocument)

CT2Doc::CT2Doc()
{
}

BOOL CT2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CT2Doc::~CT2Doc()
{
}


BEGIN_MESSAGE_MAP(CT2Doc, CDocument)
	//{{AFX_MSG_MAP(CT2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT2Doc diagnostics

#ifdef _DEBUG
void CT2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CT2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CT2Doc serialization

void CT2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CT2Doc commands
