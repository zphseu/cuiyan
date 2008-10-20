#if !defined(AFX_DLGCMTHIS_H__36C29E17_2172_402F_9B30_7E48BEEBF7F2__INCLUDED_)
#define AFX_DLGCMTHIS_H__36C29E17_2172_402F_9B30_7E48BEEBF7F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCmtHis.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCmtHis dialog

class CDlgCmtHis : public CDialog
{
// Construction
public:
	CDlgCmtHis(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCmtHis)
	enum { IDD = IDD_DLGCMTHIS };
	CString	m_szDesp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCmtHis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCmtHis)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCMTHIS_H__36C29E17_2172_402F_9B30_7E48BEEBF7F2__INCLUDED_)
