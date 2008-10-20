#if !defined(AFX_T2VIEW_H__25878123_0115_48CE_BFA6_A2CE6C0D3FF5__INCLUDED_)
#define AFX_T2VIEW_H__25878123_0115_48CE_BFA6_A2CE6C0D3FF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// T2View.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CT2View view
#include <afxcview.h>

class CT2View : public CListView
{
protected:
	CT2View();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CT2View)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT2View)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CT2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CT2View)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T2VIEW_H__25878123_0115_48CE_BFA6_A2CE6C0D3FF5__INCLUDED_)
