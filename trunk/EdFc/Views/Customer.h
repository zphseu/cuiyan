#if !defined(AFX_CUSTOMERCONTACT_H__152609BB_2715_4E40_B931_306D4B0CD6B6__INCLUDED_)
#define AFX_CUSTOMERCONTACT_H__152609BB_2715_4E40_B931_306D4B0CD6B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomerContact.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomerContact form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class CCustomer : public CFormView
{
protected:
	CCustomer();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCustomer)

// Form Data
public:
	//{{AFX_DATA(CCustomerContact)
	enum { IDD = IDD_VIEWS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomerContact)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBar m_wndToolBar;
	virtual ~CCustomer();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCustomerContact)
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMERCONTACT_H__152609BB_2715_4E40_B931_306D4B0CD6B6__INCLUDED_)
