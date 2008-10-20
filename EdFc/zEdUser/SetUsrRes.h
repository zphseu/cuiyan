#if !defined(AFX_SETUSRRES_H__1F177ECA_038B_4E27_B538_ED9E782F8B0B__INCLUDED_)
#define AFX_SETUSRRES_H__1F177ECA_038B_4E27_B538_ED9E782F8B0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetUsrRes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetUsrRes recordset

class CSetUsrRes : public CRecordset
{
public:
	void SetUser(LPCSTR szUsr);
	CSetUsrRes(CDatabase* pDatabase, LPCSTR szUsr = NULL);
	DECLARE_DYNAMIC(CSetUsrRes)

// Field/Param Data
	//{{AFX_FIELD(CSetUsrRes, CRecordset)
	CString	m_csUsrName;
	CString	m_csResName;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetUsrRes)
	public:
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_csUsr;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUSRRES_H__1F177ECA_038B_4E27_B538_ED9E782F8B0B__INCLUDED_)
