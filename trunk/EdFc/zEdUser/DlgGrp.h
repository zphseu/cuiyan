#if !defined(AFX_DLGGRP_H__6F2292BE_F3F6_4916_94DA_940AD43F0072__INCLUDED_)
#define AFX_DLGGRP_H__6F2292BE_F3F6_4916_94DA_940AD43F0072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGrp dialog
#include "SetGrp.h"
#include "resource.h"
#include "STabDialog.h"

class CDlgGrp : public CSTabDialog, public tagGrp
{
// Construction
public:
	void ResetInputCtrls();
	bool IsNameExist(CString &strName);
	CDlgGrp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGrp)
	enum { IDD = IDD_SETUPGRP };
	CListCtrl	m_lstCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGrp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ValidateInput();
	BOOL LoadData();

	// Generated message map functions
	//{{AFX_MSG(CDlgGrp)
	afx_msg void OnDel();
	afx_msg void OnSave();
	afx_msg void OnclkList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGRP_H__6F2292BE_F3F6_4916_94DA_940AD43F0072__INCLUDED_)
