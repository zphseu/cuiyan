#if !defined(AFX_DLGCOUNTOPT_H__36649712_AAA0_44BC_947E_A4579991DB1E__INCLUDED_)
#define AFX_DLGCOUNTOPT_H__36649712_AAA0_44BC_947E_A4579991DB1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCountOpt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCountOpt dialog

class CDlgCountOpt : public CDialog
{
// Construction
public:
	CString m_exts;
	CDlgCountOpt(CString exts, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCountOpt)
	enum { IDD = IDD_DLGCOUNTOPT };
	CListBox	m_clist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCountOpt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCountOpt)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnInsert();
	afx_msg void OnDelete();
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOUNTOPT_H__36649712_AAA0_44BC_947E_A4579991DB1E__INCLUDED_)
