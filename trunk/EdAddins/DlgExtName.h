#if !defined(AFX_DLGEXTNAME_H__29CBAC1D_A7AA_4FD8_BD05_F634EDC1B1ED__INCLUDED_)
#define AFX_DLGEXTNAME_H__29CBAC1D_A7AA_4FD8_BD05_F634EDC1B1ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgExtName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgExtName dialog

class CDlgExtName : public CDialog
{
// Construction
public:
	CDlgExtName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgExtName)
	enum { IDD = IDD_DLGEXTNAME };
	CString	m_extname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgExtName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgExtName)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXTNAME_H__29CBAC1D_A7AA_4FD8_BD05_F634EDC1B1ED__INCLUDED_)
