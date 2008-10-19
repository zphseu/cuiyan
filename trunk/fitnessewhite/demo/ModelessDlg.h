#if !defined(AFX_MODELESSDLG_H__5A86BA60_0BCB_4E3C_8ED8_F0A7DA2B27FB__INCLUDED_)
#define AFX_MODELESSDLG_H__5A86BA60_0BCB_4E3C_8ED8_F0A7DA2B27FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModelessDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModelessDlg dialog

class CModelessDlg : public CDialog
{
// Construction
public:
	CModelessDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL Create();
// Dialog Data
	//{{AFX_DATA(CModelessDlg)
	enum { IDD = IDD_ModelessDlg };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModelessDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELESSDLG_H__5A86BA60_0BCB_4E3C_8ED8_F0A7DA2B27FB__INCLUDED_)
