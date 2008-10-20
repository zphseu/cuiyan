// DlgLoad.h: interface for the CDlgLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGLOAD_H__16E5E216_D722_42D5_AEC1_D3BF5973AC39__INCLUDED_)
#define AFX_DLGLOAD_H__16E5E216_D722_42D5_AEC1_D3BF5973AC39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DynDialogEx.h"

class CDlgLoad : public CDynDialogEx  
{
public:
	CDlgLoad(CWnd* pParent = NULL);
	virtual ~CDlgLoad();
	CString m_FileName;
	// Dialog Data
	//{{AFX_DATA(CDlgDlg)
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void OnOK();
	//}}AFX_VIRTUAL	// Overrides

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CListDynDialogEx)
	afx_msg void OnBrower();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_DLGLOAD_H__16E5E216_D722_42D5_AEC1_D3BF5973AC39__INCLUDED_)
