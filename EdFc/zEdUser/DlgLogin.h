#if !defined(AFX_DLGLOGIN_H__20ECAF0D_9A10_4908_AF87_17481C89508E__INCLUDED_)
#define AFX_DLGLOGIN_H__20ECAF0D_9A10_4908_AF87_17481C89508E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog
#include "resource.h"
class CDlgLogin : public CDialog
{
// Construction
public:
	CDlgLogin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLogin)
	enum { IDD = IDD_LOGIN };
	CString	m_csPwd;
	CString	m_csUID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ValidateInput();

	// Generated message map functions
	//{{AFX_MSG(CDlgLogin)
	afx_msg void OnChgpwd();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGIN_H__20ECAF0D_9A10_4908_AF87_17481C89508E__INCLUDED_)
