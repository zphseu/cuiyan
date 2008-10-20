#if !defined(AFX_DLGUSRCFG_H__A0879FBF_259D_4ABC_B7BC_2A6F095BCFFE__INCLUDED_)
#define AFX_DLGUSRCFG_H__A0879FBF_259D_4ABC_B7BC_2A6F095BCFFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUsrCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUsrCfg dialog
#include "resource.h"
#include "STabDialog.h"

class CDlgUsrCfg : public CSTabDialog
{
// Construction
public:
	BOOL LoadData();
	CDlgUsrCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUsrCfg)
	enum { IDD = IDD_GRPCFG };
	CListBox	m_outUsrCtrl;
	CListBox	m_inUsrCtrl;
	CListBox	m_outResCtrl;
	CListBox	m_inResCtrl;
	CComboBox	m_cbCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUsrCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nCurSel;
	// Generated message map functions
	//{{AFX_MSG(CDlgUsrCfg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUsrto();
	afx_msg void OnUsrout();
	afx_msg void OnResto();
	afx_msg void OnResout();
	afx_msg void OnSelchangeGrp();
	afx_msg void OnDblclkInres();
	afx_msg void OnDblclkInusr();
	afx_msg void OnDblclkOutres();
	afx_msg void OnDblclkOutusr();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSRCFG_H__A0879FBF_259D_4ABC_B7BC_2A6F095BCFFE__INCLUDED_)
