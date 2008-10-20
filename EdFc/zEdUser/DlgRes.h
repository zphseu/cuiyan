#if !defined(AFX_DLGRES_H__2CF1469E_702C_4285_9BA3_8DBF923601C2__INCLUDED_)
#define AFX_DLGRES_H__2CF1469E_702C_4285_9BA3_8DBF923601C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRes dialog
#include "SetRes.h"
#include "resource.h"
#include "sTabdialog.h"


class CDlgRes : public CSTabDialog, public tagRes
{
// Construction
public:
	void ResetInputCtrls();
	bool IsNameExist(CString &strName);
	CDlgRes(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRes)
	enum { IDD = IDD_SETUPRES };
	CListCtrl	m_lstCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ValidateInput();
	BOOL LoadData();

	// Generated message map functions
	//{{AFX_MSG(CDlgRes)
	afx_msg void OnSave();
	afx_msg void OnDel();
	afx_msg void OnclkList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRES_H__2CF1469E_702C_4285_9BA3_8DBF923601C2__INCLUDED_)
