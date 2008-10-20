// SetRes.cpp : implementation file
//

#include "stdafx.h"
#include "SetRes.h"
#include "EdMod1Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CEdMod1Ini g_ini;

/////////////////////////////////////////////////////////////////////////////
// CSetRes

IMPLEMENT_DYNAMIC(CSetRes, CRecordset)

CSetRes::CSetRes(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetRes)
	m_nFields = 3;
	//}}AFX_FIELD_INIT
 	m_nDefaultType = snapshot;
}
 
CString CSetRes::GetDefaultSQL()
{
	return _T("[zed000]");
}

void CSetRes::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetRes)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[AA]"), m_csName);
	RFX_Text(pFX, _T("[AB]"), m_csMod);
	RFX_Text(pFX, _T("[AC]"), m_csCmt);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetRes diagnostics

#ifdef _DEBUG
void CSetRes::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetRes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

CString CSetRes::GetDefaultConnect() 
{
	return g_ini.m_csConStr;
}

