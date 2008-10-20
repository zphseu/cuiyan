#if !defined(AFX_DLGCHM_H__B09BFDB7_258C_4D8A_A619_25C832079C6E__INCLUDED_)
#define AFX_DLGCHM_H__B09BFDB7_258C_4D8A_A619_25C832079C6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChm dialog

class CDlgChm : public CDialog
{
// Construction
public:
	CDlgChm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChm)
	enum { IDD = IDD_DLGCHM };
	BOOL	m_bPrivate;
	BOOL	m_bStatic;
	int		m_nLanguage;
	BOOL	m_bOpen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChm)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHM_H__B09BFDB7_258C_4D8A_A619_25C832079C6E__INCLUDED_)
