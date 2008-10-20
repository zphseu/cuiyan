// SetUsr.cpp : implementation file
//

#include "stdafx.h"
#include "SetUsr.h"
#include "EdMod1Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CEdMod1Ini g_ini;

/////////////////////////////////////////////////////////////////////////////
// CSetUsr

IMPLEMENT_DYNAMIC(CSetUsr, CRecordset)

CSetUsr::CSetUsr(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetUsr)
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CSetUsr::GetDefaultSQL()
{
	return _T("[zed001]");
}

void CSetUsr::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetUsr)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[AA]"), m_csName);
	RFX_Text(pFX, _T("[AB]"), m_csPwd);
	RFX_Text(pFX, _T("[AC]"), m_csPos);
	RFX_Text(pFX, _T("[AD]"), m_csTel);
	RFX_Text(pFX, _T("[AE]"), m_csHandset);
	RFX_Text(pFX, _T("[AF]"), m_csCmt);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetUsr diagnostics

#ifdef _DEBUG
void CSetUsr::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetUsr::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

CString CSetUsr::GetDefaultConnect() 
{
	return g_ini.m_csConStr;
}
