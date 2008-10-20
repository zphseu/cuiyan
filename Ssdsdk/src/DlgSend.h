// DlgSend.h: interface for the CDlgSend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGSEND_H__228FFC94_4641_49FF_A01F_1E82B5B2E073__INCLUDED_)
#define AFX_DLGSEND_H__228FFC94_4641_49FF_A01F_1E82B5B2E073__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DynDialogEx.h"
#include "ssd.h"

class CDlgSend : public CDynDialogEx  
{
public:
	CDlgSend(CWnd* pParent = NULL);
	virtual ~CDlgSend();
	SSD m_User;
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_DLGSEND_H__228FFC94_4641_49FF_A01F_1E82B5B2E073__INCLUDED_)
