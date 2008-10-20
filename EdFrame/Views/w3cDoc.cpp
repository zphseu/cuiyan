// w3cDoc.cpp : implementation of the CW3CDoc class
//

#include "stdafx.h"
#include "w3cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CW3CDoc

IMPLEMENT_DYNCREATE(CW3CDoc, CDocument)

BEGIN_MESSAGE_MAP(CW3CDoc, CDocument)
	//{{AFX_MSG_MAP(CW3CDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CW3CDoc construction/destruction

CW3CDoc::CW3CDoc()
{
	// TODO: add one-time construction code here

}

CW3CDoc::~CW3CDoc()
{
}

BOOL CW3CDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CW3CDoc serialization

void CW3CDoc::Serialize(CArchive& ar)
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
// CW3CDoc diagnostics

#ifdef _DEBUG
void CW3CDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CW3CDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CW3CDoc commands
