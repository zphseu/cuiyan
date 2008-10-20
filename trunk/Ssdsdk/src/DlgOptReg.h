// DlgOptReg.h: interface for the CDlgOptReg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGOPTREG_H__51BE973B_B597_4F3A_9F58_E2A6ED450814__INCLUDED_)
#define AFX_DLGOPTREG_H__51BE973B_B597_4F3A_9F58_E2A6ED450814__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DynDialogEx.h"

class CDlgOptReg : public CDynDialogEx  
{
public:
	CDlgOptReg(CWnd* pParent = NULL);
	virtual ~CDlgOptReg();
	int m_nOption;
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

#endif // !defined(AFX_DLGOPTREG_H__51BE973B_B597_4F3A_9F58_E2A6ED450814__INCLUDED_)
