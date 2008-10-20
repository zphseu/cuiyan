// SetGrp.cpp : implementation file
//

#include "stdafx.h"
#include "SetGrp.h"
#include "EdMod1Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CEdMod1Ini g_ini;
/////////////////////////////////////////////////////////////////////////////
// CSetGrp

IMPLEMENT_DYNAMIC(CSetGrp, CRecordset)

CSetGrp::CSetGrp(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetGrp)
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CSetGrp::GetDefaultSQL()
{
	return _T("[zed002]");
}

void CSetGrp::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetGrp)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[AA]"), m_csName);
	RFX_Text(pFX, _T("[AB]"), m_csCmt);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetGrp diagnostics

#ifdef _DEBUG
void CSetGrp::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetGrp::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

CString CSetGrp::GetDefaultConnect() 
{
	return g_ini.m_csConStr;
}
