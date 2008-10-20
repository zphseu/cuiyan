// w3cView.h : interface of the CW3CView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_W3CVIEW_H__B2F86201_85A6_4E93_AADE_F21A82B1A80F__INCLUDED_)
#define AFX_W3CVIEW_H__B2F86201_85A6_4E93_AADE_F21A82B1A80F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxhtml.h>
#include "W3CDoc.h"

class CW3CView : public CHtmlView
{
protected: // create from serialization only
	CW3CView();
	DECLARE_DYNCREATE(CW3CView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CW3CView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CW3CView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void OnButton(UINT id);
	CString	m_szHome;
	
	//{{AFX_MSG(CW3CView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_W3CVIEW_H__B2F86201_85A6_4E93_AADE_F21A82B1A80F__INCLUDED_)
