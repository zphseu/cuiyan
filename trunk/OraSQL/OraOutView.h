#if !defined(AFX_ORAOUTVIEW_H__08EA8696_7834_4D32_B0AC_EA3540ECFE22__INCLUDED_)
#define AFX_ORAOUTVIEW_H__08EA8696_7834_4D32_B0AC_EA3540ECFE22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OraOutView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COraOutView view

class COraOutView : public CListView
{
protected:
	COraOutView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COraOutView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COraOutView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COraOutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(COraOutView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORAOUTVIEW_H__08EA8696_7834_4D32_B0AC_EA3540ECFE22__INCLUDED_)
