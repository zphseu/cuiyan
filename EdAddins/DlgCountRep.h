#if !defined(AFX_DLGCOUNTREP_H__1E9FD94B_FF44_41C7_923F_6D7122E7BCDF__INCLUDED_)
#define AFX_DLGCOUNTREP_H__1E9FD94B_FF44_41C7_923F_6D7122E7BCDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCountRep.h : header file
//
#include "DevWsFile.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgCountRep dialog

class CDlgCountRep : public CDialog
{
// Construction
public:
	void SetWsName(CString wsName);
	CDlgCountRep(IApplication* pApp, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCountRep)
	enum { IDD = IDD_DLGCOUNTREP };
	CListCtrl	m_ListCtrl;
	CComboBox	m_combo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCountRep)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString NumStr(int num);
	void SetListData(int proj);
	void SetNum(int id, int num, TCHAR suffix = '\0');
	void SetPair(int idc, int idp, int count, int tot);
	CDevWsFile m_wsStat;
	IApplication* m_pApplication;

	// Generated message map functions
	//{{AFX_MSG(CDlgCountRep)
	afx_msg void OnExport();
	afx_msg void OnSelchangeCombo();
	virtual BOOL OnInitDialog();
	afx_msg void OnOption();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOUNTREP_H__1E9FD94B_FF44_41C7_923F_6D7122E7BCDF__INCLUDED_)
