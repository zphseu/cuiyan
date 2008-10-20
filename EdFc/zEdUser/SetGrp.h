#if !defined(AFX_SETGRP_H__71AC8DFA_9B1A_498F_BC3E_13635DCA1BCB__INCLUDED_)
#define AFX_SETGRP_H__71AC8DFA_9B1A_498F_BC3E_13635DCA1BCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetGrp recordset

struct tagGrp 
{
	CString m_csName;
	CString m_csCmt;
};

class CSetGrp : public CRecordset, public tagGrp
{
public:
	CSetGrp(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetGrp)

// Field/Param Data
	//{{AFX_FIELD(CSetGrp, CRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetGrp)
	public:
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	virtual CString GetDefaultConnect();
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETGRP_H__71AC8DFA_9B1A_498F_BC3E_13635DCA1BCB__INCLUDED_)
