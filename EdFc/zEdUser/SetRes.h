#if !defined(AFX_SETRES_H__49D83969_7E48_4F5B_9AB5_A2040FDBCBCF__INCLUDED_)
#define AFX_SETRES_H__49D83969_7E48_4F5B_9AB5_A2040FDBCBCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetRes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetRes recordset
struct tagRes 
{
	CString	m_csName;
	CString	m_csMod;
	CString	m_csCmt;
};

class CSetRes : public CRecordset, public tagRes
{
public:
	CSetRes(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetRes)

// Field/Param Data
	//{{AFX_FIELD(CSetRes, CRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetRes)
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

#endif // !defined(AFX_SETRES_H__49D83969_7E48_4F5B_9AB5_A2040FDBCBCF__INCLUDED_)
