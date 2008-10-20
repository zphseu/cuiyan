#if !defined(AFX_DLGCMTNOR_H__1ADC25E2_91D2_412B_B30E_1052E3DFA873__INCLUDED_)
#define AFX_DLGCMTNOR_H__1ADC25E2_91D2_412B_B30E_1052E3DFA873__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCmtNor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCmtNor dialog

class CDlgCmtNor : public CDialog
{
// Construction
public:
	CDlgCmtNor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCmtNor)
	enum { IDD = IDD_DLGCMTNOR };
	CString	m_szDesp;
	CString	m_szDetail;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCmtNor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCmtNor)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCMTNOR_H__1ADC25E2_91D2_412B_B30E_1052E3DFA873__INCLUDED_)
