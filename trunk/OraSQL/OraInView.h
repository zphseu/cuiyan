// OraInView.h : interface of the COraInView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORAINVIEW_H__0962B2A2_8AF0_4D05_B660_941403111954__INCLUDED_)
#define AFX_ORAINVIEW_H__0962B2A2_8AF0_4D05_B660_941403111954__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SQLCmd.h"
#include "OraSQLDoc.h"

class COraInView : public CEditView
{
protected: // create from serialization only
	COraInView();
	DECLARE_DYNCREATE(COraInView)

// Attributes
public:
	COraSQLDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COraInView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COraInView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COraInView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OraInView.cpp
inline COraSQLDoc* COraInView::GetDocument()
   { return (COraSQLDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORAINVIEW_H__0962B2A2_8AF0_4D05_B660_941403111954__INCLUDED_)
