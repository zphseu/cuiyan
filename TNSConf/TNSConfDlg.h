// TNSConfDlg.h : header file
//

#if !defined(AFX_TNSCONFDLG_H__238DFD3D_9DFC_4DC0_BBF2_68EFA5A9DE80__INCLUDED_)
#define AFX_TNSCONFDLG_H__238DFD3D_9DFC_4DC0_BBF2_68EFA5A9DE80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTNSConfDlg dialog
#include "TNSNamesFile.h"

class CTNSConfDlg : public CDialog   
{
// Construction
public:
	CTNSConfDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTNSConfDlg)
	enum { IDD = IDD_TNSCONF_DIALOG };
	CListBox	m_ctlList;
	CString	m_szHost;
	CString	m_szSvr;
	CString	m_szTns;
	CString	m_szPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTNSConfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bToSave;
	void Freshlist(int nSel = 0);
	UINT m_uCurSel;
	BOOL m_bChange;
	BOOL m_bError;
	CTnsNamesFile	m_File;
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CTNSConfDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnDel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchangeList();
	afx_msg void OnChanged();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TNSCONFDLG_H__238DFD3D_9DFC_4DC0_BBF2_68EFA5A9DE80__INCLUDED_)
