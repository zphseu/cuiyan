// T1Doc.cpp : implementation of the CT1Doc class
//

#include "stdafx.h"
#include "T1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CT1Doc

IMPLEMENT_DYNCREATE(CT1Doc, CDocument)

BEGIN_MESSAGE_MAP(CT1Doc, CDocument)
	//{{AFX_MSG_MAP(CT1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT1Doc construction/destruction

CT1Doc::CT1Doc()
{
	// TODO: add one-time construction code here

}

CT1Doc::~CT1Doc()
{
}

BOOL CT1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CT1Doc serialization

void CT1Doc::Serialize(CArchive& ar)
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
// CT1Doc diagnostics

#ifdef _DEBUG
void CT1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CT1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CT1Doc commands
