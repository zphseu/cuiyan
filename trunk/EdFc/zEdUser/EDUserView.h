#if !defined(_EDUSERVIEW_INCLUDE_)
#define _EDUSERVIEW_INCLUDE_

#include "DlgRes.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BSUserView.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CEdUserView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"
#include "STabCtrl.h"

#include "DlgRes.h"
#include "DlgUsr.h"
#include "DlgGrp.h"
#include "DlgUsrCfg.h"

class CEdUserView : public CFormView
{
protected:
	CEdUserView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEdUserView)	
protected:

// Form Data
public:
	//{{AFX_DATA(CEdUserView)
	enum { IDD = IDD_EDUSERVIEW };
	CSTabCtrl	m_ctlTab;
	//}}AFX_DATA
// Attributes
public:
	static CMapStringToPtr m_mapCurUsrRes;
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdUserView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDlgRes m_dlgRes;
	CDlgUsr m_dlgUsr;
	CDlgGrp m_dlgGrp;
	CDlgUsrCfg m_dlgUsrCfg;

	virtual ~CEdUserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEdUserView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_EDUSERVIEW_INCLUDE_)
