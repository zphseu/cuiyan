#if !defined(AFX_MODEDLG_H__D74885A6_A353_46F1_A01D_4EEDFF909968__INCLUDED_)
#define AFX_MODEDLG_H__D74885A6_A353_46F1_A01D_4EEDFF909968__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModeDlg dialog

class CModeDlg : public CDialog
{
// Construction
public:
	CModeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModeDlg)
	enum { IDD = IDD_ModeDlg };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModeDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODEDLG_H__D74885A6_A353_46F1_A01D_4EEDFF909968__INCLUDED_)
