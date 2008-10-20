#if !defined(AFX_DLGLISENCE_H__CEC61575_B639_4E12_81B8_42B10F3991A6__INCLUDED_)
#define AFX_DLGLISENCE_H__CEC61575_B639_4E12_81B8_42B10F3991A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLisence.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDlgLisence dialog

#include "HyperLink.h"

class CMyDlgLisence : public CDialog
{
// Construction
public:
	CMyDlgLisence(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlgLisence)
	enum { IDD = IDD_DLGLICENCE };
	CHyperLink	m_Email;
	CHyperLink	m_Url;
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
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLISENCE_H__CEC61575_B639_4E12_81B8_42B10F3991A6__INCLUDED_)
