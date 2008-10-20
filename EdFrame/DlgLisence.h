#if !defined(AFX_DLGLISENCE_H__5584C7E4_B913_44CB_86ED_46A0DFF17EA0__INCLUDED_)
#define AFX_DLGLISENCE_H__5584C7E4_B913_44CB_86ED_46A0DFF17EA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLisence.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDlgLisence dialog
#include "Hyperlink.h"

class CMyDlgLisence : public CDialog
{
// Construction
public:
	CMyDlgLisence(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgLisence)
	enum { IDD = IDD_DLGLICENCE };
	CHyperLink	m_Url;
	CHyperLink	m_Email;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlgLisence)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyDlgLisence)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLISENCE_H__5584C7E4_B913_44CB_86ED_46A0DFF17EA0__INCLUDED_)
