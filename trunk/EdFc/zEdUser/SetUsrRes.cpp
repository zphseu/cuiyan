// SetUsrRes.cpp : implementation file
//

#include "stdafx.h"
#include "SetUsrRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetUsrRes

IMPLEMENT_DYNAMIC(CSetUsrRes, CRecordset)

CSetUsrRes::CSetUsrRes(CDatabase* pdb, LPCSTR szUsr)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetUsrRes)
	m_csUsrName = _T("");
	m_csResName = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_csUsr = szUsr;
}

CString CSetUsrRes::GetDefaultSQL()
{
	CString csDefSQL = _T("SELECT DISTINCT zed003.AB , zed004.AB FROM"
		"(zed002 INNER JOIN zed004 ON zed002.AA = zed004.AA) INNER JOIN zed003 ON zed002.AA = zed003.AA");

	if (!m_csUsr.IsEmpty())
		csDefSQL += " WHERE zed004.AB='" + m_csUsr + "'";
	
	return csDefSQL;
}

void CSetUsrRes::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetUsrRes)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[zed003.AB]"), m_csResName);
	RFX_Text(pFX, _T("[zed004.AB]"), m_csUsrName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetUsrRes diagnostics

#ifdef _DEBUG
void CSetUsrRes::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetUsrRes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CSetUsrRes::SetUser(LPCSTR szUsr)
{
	m_csUsr = szUsr;
}
