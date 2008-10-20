/**************************************************************
 *  filename:    DlgCmtFun.h
 *  copyright:   Shanghai Baosight Software Co., Ltd.
 *
 *  description: to fill in infomation of comment when to insert <br>
 * function.
 *
 *  @author:     cuiyan
 *  history:
 *    1.  11/17/2002  cuiyan  Initial Version
 *
**************************************************************/
#if !defined(AFX_DLGCMTFUN_H__6D7A399D_2407_46F8_8170_401D55B607C2__INCLUDED_)
#define AFX_DLGCMTFUN_H__6D7A399D_2407_46F8_8170_401D55B607C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCmtFun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCmtFun dialog

class CDlgCmtFun : public CDialog
{
// Construction
public:
	CDlgCmtFun(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCmtFun)
	enum { IDD = IDD_DLGCMTFUN };
	CString	m_szDesp;
	CString	m_szDetail;
	CString	m_szReturn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCmtFun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCmtFun)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCMTFUN_H__6D7A399D_2407_46F8_8170_401D55B607C2__INCLUDED_)
