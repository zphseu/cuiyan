// aSet.h : interface of the CASet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASET_H__9473DD01_5591_4A8F_9A20_CDBE94C6C30E__INCLUDED_)
#define AFX_ASET_H__9473DD01_5591_4A8F_9A20_CDBE94C6C30E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CASet : public CRecordset
{
public:
	CASet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CASet)

// Field/Param Data
	//{{AFX_FIELD(CASet, CRecordset)
	CString	m_DEPTNO;
	CString	m_DNAME;
	CString	m_LOC;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CASet)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASET_H__9473DD01_5591_4A8F_9A20_CDBE94C6C30E__INCLUDED_)

