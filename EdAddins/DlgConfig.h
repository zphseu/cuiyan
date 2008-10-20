#if !defined(AFX_DLGAUTOSAVE_H__23B9FC52_BFA6_41CA_B8EE_54EC9D44603A__INCLUDED_)
#define AFX_DLGAUTOSAVE_H__23B9FC52_BFA6_41CA_B8EE_54EC9D44603A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAutoSave.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgConfig dialog

class CDlgConfig : public CDialog
{
// Construction
public:
	CDlgConfig(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CDlgConfig)
	enum { IDD = IDD_DLGCONFIG };
	BOOL	m_bSaveDSW;
	BOOL	m_bSaveFiles;
	UINT	m_nSaveTime;
	BOOL	m_bByDialog;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConfig)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUTOSAVE_H__23B9FC52_BFA6_41CA_B8EE_54EC9D44603A__INCLUDED_)
