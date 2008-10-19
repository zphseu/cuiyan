// Controls_DemoDlg.h : header file
//

#if !defined(AFX_CONTROLS_DEMODLG_H__610791B5_6673_47F7_BE43_66DFBA309EB0__INCLUDED_)
#define AFX_CONTROLS_DEMODLG_H__610791B5_6673_47F7_BE43_66DFBA309EB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Page3.h"
#include "Page4.h"
/////////////////////////////////////////////////////////////////////////////
// CControls_DemoDlg dialog

class CControls_DemoDlg : public CDialog
{
// Construction
public:
	CControls_DemoDlg(CWnd* pParent = NULL);	// standard constructor
	CPropertySheet	m_sheet;
	CPage3 m_page3;
	CPage4 m_page4;

// Dialog Data
	//{{AFX_DATA(CControls_DemoDlg)
	enum { IDD = IDD_CONTROLS_DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControls_DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CControls_DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLS_DEMODLG_H__610791B5_6673_47F7_BE43_66DFBA309EB0__INCLUDED_)
