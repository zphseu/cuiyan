#if !defined(AFX_DLGUSER_H__AE180FC6_F3D6_43F7_B460_0A74F9B47198__INCLUDED_)
#define AFX_DLGUSER_H__AE180FC6_F3D6_43F7_B460_0A74F9B47198__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUser dialog
#include "STabCtrl.h"

#include "DlgRes.h"
#include "DlgUsr.h"
#include "DlgGrp.h"
#include "DlgUsrCfg.h"

class CDlgUser : public CDialog
{
// Construction
public:
	CDlgUser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUser)
	enum { IDD = IDD_EDUSER };
	CSTabCtrl	m_ctlTab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDlgRes m_dlgRes;
	CDlgUsr m_dlgUsr;
	CDlgGrp m_dlgGrp;
	CDlgUsrCfg m_dlgUsrCfg;

	// Generated message map functions
	//{{AFX_MSG(CDlgUser)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSER_H__AE180FC6_F3D6_43F7_B460_0A74F9B47198__INCLUDED_)
