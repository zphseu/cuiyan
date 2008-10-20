// SetGrpUsr.cpp : implementation file
//

#include "stdafx.h"
#include "SetGrpUsr.h"
#include "EdMod1Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CEdMod1Ini g_ini;

/////////////////////////////////////////////////////////////////////////////
// CSetGrpUsr

IMPLEMENT_DYNAMIC(CSetGrpUsr, CRecordset)

CSetGrpUsr::CSetGrpUsr(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetGrpUsr)
	m_csGrp = _T("");
	m_csUsr = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CSetGrpUsr::GetDefaultConnect()
{
	return g_ini.m_csConStr;
}

CString CSetGrpUsr::GetDefaultSQL()
{
	return _T("[zed004]");
}

void CSetGrpUsr::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetGrpUsr)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[AA]"), m_csGrp);
	RFX_Text(pFX, _T("[AB]"), m_csUsr);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetGrpUsr diagnostics

#ifdef _DEBUG
void CSetGrpUsr::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetGrpUsr::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
