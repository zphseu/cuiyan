#if !defined(AFX_DLGCHGINFO_H__EA0290CA_CD58_428C_9A10_1C1C05C1C785__INCLUDED_)
#define AFX_DLGCHGINFO_H__EA0290CA_CD58_428C_9A10_1C1C05C1C785__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChgInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChgInfo dialog
#include "resource.h"

class CDlgChgInfo : public CDialog
{
// Construction
public:
	CDlgChgInfo(LPCSTR szUid, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChgInfo)
	enum { IDD = IDD_CHANGEPSW };
	CString	m_cmt;
	CString	m_pwd2;
	CString	m_handset;
	CString	m_pwd;
	CString	m_oldpwd;
	CString	m_tel;
	CString	m_uid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChgInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ValidateInput();
	// Generated message map functions
	//{{AFX_MSG(CDlgChgInfo)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHGINFO_H__EA0290CA_CD58_428C_9A10_1C1C05C1C785__INCLUDED_)
