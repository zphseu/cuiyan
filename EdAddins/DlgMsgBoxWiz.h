#if !defined(AFX_DLGMSGBOXWIZ_H__5A050AA2_D68A_4A38_82C6_F7999851B84A__INCLUDED_)
#define AFX_DLGMSGBOXWIZ_H__5A050AA2_D68A_4A38_82C6_F7999851B84A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMsgBoxWiz.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgBoxWiz dialog

class CDlgMsgBoxWiz : public CDialog
{
// Construction
public:
	CDlgMsgBoxWiz(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMsgBoxWiz)
	enum { IDD = IDD_DLGMSGBOXWIZ };
	CComboBox	m_ccondition;
	BOOL	m_bmsg;
	BOOL	m_bcaption;
	CString	m_value;
	CString	m_text;
	CString	m_equ;
	CString	m_caption;
	CString	m_btn;
	CString	m_modality;
	CString	m_symbol;
	CString	m_type;
	CString	m_defbtn;
	//}}AFX_DATA
	CString m_msgbox;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMsgBoxWiz)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString GetMsgBoxStr();

	// Generated message map functions
	//{{AFX_MSG(CDlgMsgBoxWiz)
	afx_msg void OnTest();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombobtn();
	afx_msg void OnView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT getStyle(CString szStyle);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMSGBOXWIZ_H__5A050AA2_D68A_4A38_82C6_F7999851B84A__INCLUDED_)
