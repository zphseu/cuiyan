#if !defined(_EDHTMLVIEW_INCLUDE_)
#define _EDHTMLVIEW_INCLUDE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BSHtmlView.h : header file
//
#include <afxhtml.h>
/////////////////////////////////////////////////////////////////////////////
// CEdHtmlView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "resource.h"

class CEdHtmlView : public CHtmlView
{
protected:
	CEdHtmlView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEdHtmlView)
	
protected:
// Attributes
public:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdHtmlView)
	public:
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
protected:
	LPCSTR m_szHome;
	void OnButton(UINT id);
	virtual ~CEdHtmlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEdHtmlView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_EDHTMLVIEW_INCLUDE_)
