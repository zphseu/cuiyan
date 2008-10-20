// SetGrpRes.cpp : implementation file
//

#include "stdafx.h"
#include "SetGrpRes.h"
#include "EdMod1Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CEdMod1Ini g_ini;

/////////////////////////////////////////////////////////////////////////////
// CSetGrpRes

IMPLEMENT_DYNAMIC(CSetGrpRes, CRecordset)

CSetGrpRes::CSetGrpRes(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetGrpRes)
	m_csGrp = _T("");
	m_csRes = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CSetGrpRes::GetDefaultConnect()
{
	return g_ini.m_csConStr;
}

CString CSetGrpRes::GetDefaultSQL()
{
	return _T("[zed003]");
}

void CSetGrpRes::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetGrpRes)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[AA]"), m_csGrp);
	RFX_Text(pFX, _T("[AB]"), m_csRes);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetGrpRes diagnostics

#ifdef _DEBUG
void CSetGrpRes::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetGrpRes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
