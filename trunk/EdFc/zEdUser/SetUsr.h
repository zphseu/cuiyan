#if !defined(AFX_SETUSR_H__E017E711_8270_4454_AB84_9960EAF8B7DC__INCLUDED_)
#define AFX_SETUSR_H__E017E711_8270_4454_AB84_9960EAF8B7DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetUsr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetUsr recordset

struct tagUsr
{
	CString m_csName;
	CString m_csPwd;
	CString m_csPos;
	CString m_csTel;
	CString m_csHandset;
	CString m_csCmt;

	tagUsr()
	{
		m_csPwd = "@@#$#$)(*(_$";
	}
};

class CSetUsr : public CRecordset, public tagUsr
{
public:
	CSetUsr(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CSetUsr)

// Field/Param Data
	//{{AFX_FIELD(CSetUsr, CRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetUsr)
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

#endif // !defined(AFX_SETUSR_H__E017E711_8270_4454_AB84_9960EAF8B7DC__INCLUDED_)
