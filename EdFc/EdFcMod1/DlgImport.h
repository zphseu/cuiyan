#if !defined(AFX_DLGIMPORT_H__FB23080E_6EA0_4DCD_8146_79DCE7C29F85__INCLUDED_)
#define AFX_DLGIMPORT_H__FB23080E_6EA0_4DCD_8146_79DCE7C29F85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgImport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgImport dialog
#include "resource.h"

class CDlgImport : public CDialog
{
// Construction
public:
	CDlgImport(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgImport)
	enum { IDD = IDD_BSIMPORT };
	CString	m_szDir;
	CString	m_szFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgImport)
	afx_msg void OnDir();
	afx_msg void OnFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIMPORT_H__FB23080E_6EA0_4DCD_8146_79DCE7C29F85__INCLUDED_)
