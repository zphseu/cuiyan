#if !defined(AFX_SETGRPRES_H__3CF4CC48_F06C_4E4A_9FB3_3FC9D6A1E848__INCLUDED_)
#define AFX_SETGRPRES_H__3CF4CC48_F06C_4E4A_9FB3_3FC9D6A1E848__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGrpRes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetGrpRes recordset

class CSetGrpRes : public CRecordset
{
public:
	CSetGrpRes(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetGrpRes)

// Field/Param Data
	//{{AFX_FIELD(CSetGrpRes, CRecordset)
	CString	m_csGrp;
	CString	m_csRes;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetGrpRes)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETGRPRES_H__3CF4CC48_F06C_4E4A_9FB3_3FC9D6A1E848__INCLUDED_)
