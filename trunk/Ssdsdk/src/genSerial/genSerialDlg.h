// genSerialDlg.h : header file
//

#if !defined(AFX_GENSERIALDLG_H__A41B7254_9250_46D0_A0E0_96B493C8B678__INCLUDED_)
#define AFX_GENSERIALDLG_H__A41B7254_9250_46D0_A0E0_96B493C8B678__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGenSerialDlg dialog
#include "..\ssd.h"



class CGenSerialDlg : public CDialog
{
// Construction
public:
	CGenSerialDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGenSerialDlg)
	enum { IDD = IDD_GENSERIAL_DIALOG };
	CComboBox m_Type;
	//}}AFX_DATA
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenSerialDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	class myssd : public CSSD {	friend class CGenSerialDlg;	} m_cssd;
	CString m_Path;
	// Generated message map functions
	//{{AFX_MSG(CGenSerialDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENSERIALDLG_H__A41B7254_9250_46D0_A0E0_96B493C8B678__INCLUDED_)
