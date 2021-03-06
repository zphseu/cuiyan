#if !defined(AFX_SETGRPUSR_H__FE66BFBA_7D01_4506_8AE7_9A93EA5C7B77__INCLUDED_)
#define AFX_SETGRPUSR_H__FE66BFBA_7D01_4506_8AE7_9A93EA5C7B77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGrpUsr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetGrpUsr recordset

class CSetGrpUsr : public CRecordset
{
public:
	CSetGrpUsr(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetGrpUsr)

// Field/Param Data
	//{{AFX_FIELD(CSetGrpUsr, CRecordset)
	CString	m_csGrp;
	CString	m_csUsr;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetGrpUsr)
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

#endif // !defined(AFX_SETGRPUSR_H__FE66BFBA_7D01_4506_8AE7_9A93EA5C7B77__INCLUDED_)
