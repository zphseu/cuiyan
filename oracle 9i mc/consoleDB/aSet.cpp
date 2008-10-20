// aSet.cpp : implementation of the CASet class
//

#include "stdafx.h"
#include "aSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CASet implementation

IMPLEMENT_DYNAMIC(CASet, CRecordset)

CASet::CASet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CASet)
	m_DEPTNO = _T("");
	m_DNAME = _T("");
	m_LOC = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CASet::GetDefaultConnect()
{
	return _T("ODBC;DSN=scott");
}

CString CASet::GetDefaultSQL()
{
	return _T("[SCOTT].[DEPT]");
}

void CASet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CASet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[DEPTNO]"), m_DEPTNO);
	RFX_Text(pFX, _T("[DNAME]"), m_DNAME);
	RFX_Text(pFX, _T("[LOC]"), m_LOC);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CASet diagnostics

#ifdef _DEBUG
void CASet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CASet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
