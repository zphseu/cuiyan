// DlgUsrReg.h: interface for the CDlgUsrReg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGUSRREG_H__26214EF1_3A96_4AAC_988C_89EAEC78B2BE__INCLUDED_)
#define AFX_DLGUSRREG_H__26214EF1_3A96_4AAC_988C_89EAEC78B2BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DynDialogEx.h"
#include "ssd.h"

class CDlgUsrReg : public CDynDialogEx
{
public:
	CDlgUsrReg(CWnd* pParent = NULL);
	virtual ~CDlgUsrReg();
	
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

#endif // !defined(AFX_DLGUSRREG_H__26214EF1_3A96_4AAC_988C_89EAEC78B2BE__INCLUDED_)
