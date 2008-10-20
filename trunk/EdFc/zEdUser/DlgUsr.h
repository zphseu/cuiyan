#if !defined(AFX_DLGUSR_H__328F0886_0D40_472F_9F76_DED9BC47837C__INCLUDED_)
#define AFX_DLGUSR_H__328F0886_0D40_472F_9F76_DED9BC47837C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUsr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUsr dialog
#include "SetUsr.h"
#include "resource.h"
#include "stabdialog.h"

class CDlgUsr : public CSTabDialog, public tagUsr
{
// Construction
public:
	bool IsNameExist(CString &strName);
	CDlgUsr(CWnd* pParent = NULL);   // standard constructor
	void ResetInputCtrls();
// Dialog Data
	//{{AFX_DATA(CDlgUsr)
	enum { IDD = IDD_SETUPUSR };
	CListCtrl	m_lstCtrl;
	CString	m_pwd2;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUsr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ValidateInput();
	BOOL LoadData();
	// Generated message map functions
	//{{AFX_MSG(CDlgUsr)
	virtual BOOL OnInitDialog();
	afx_msg void OnDel();
	afx_msg void OnclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSave();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSR_H__328F0886_0D40_472F_9F76_DED9BC47837C__INCLUDED_)
