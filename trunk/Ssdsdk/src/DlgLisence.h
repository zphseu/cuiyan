// DlgLisence.h: interface for the CDlgLisence class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGLISENCE_H__4AA32FEF_B6FB_453D_8360_F9FDDEEEB298__INCLUDED_)
#define AFX_DLGLISENCE_H__4AA32FEF_B6FB_453D_8360_F9FDDEEEB298__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DynDialogEx.h"

class CDlgLisence : public CDynDialogEx  
{
public:
	CDlgLisence(CWnd* pParent = NULL);
	virtual ~CDlgLisence();
	// Dialog Data
	//{{AFX_DATA(CDlgDlg)
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDlg)
public:
	virtual int DoModal(LPCSTR sinfo, DWORD nsecond = 5);
protected:
	//}}AFX_VIRTUAL	// Overrides
	
	// Implementation
protected:
	static UINT OnTimer(LPVOID pParam);
	// Generated message map functions
	//{{AFX_MSG(CListDynDialogEx)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif // !defined(AFX_DLGLISENCE_H__4AA32FEF_B6FB_453D_8360_F9FDDEEEB298__INCLUDED_)
