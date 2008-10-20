// OraSQLDoc.cpp : implementation of the COraSQLDoc class
//

#include "stdafx.h"
#include "OraSQL.h"

#include "OraSQLDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COraSQLDoc

IMPLEMENT_DYNCREATE(COraSQLDoc, CDocument)

BEGIN_MESSAGE_MAP(COraSQLDoc, CDocument)
	//{{AFX_MSG_MAP(COraSQLDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COraSQLDoc construction/destruction

COraSQLDoc::COraSQLDoc()
{
	// TODO: add one-time construction code here

}

COraSQLDoc::~COraSQLDoc()
{
}


BOOL COraSQLDoc::SaveModified() 
{
	return TRUE;
}

