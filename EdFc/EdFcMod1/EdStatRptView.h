#if !defined(AFX_EDSTATRPTVIEW_H__E31E762A_6272_4E4B_A71D_2A259C0D0223__INCLUDED_)
#define AFX_EDSTATRPTVIEW_H__E31E762A_6272_4E4B_A71D_2A259C0D0223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EdStatRptView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEdStatRptView view
#include "EdStatDoc.h"

class CEdStatRptView : public CScrollView
{
protected:
	CEdStatRptView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEdStatRptView)
	
	CEdStatDoc m_Doc;
	BOOL m_bFirstDraw;
// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdStatRptView)
	protected:
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnDraw(CDC* pDC);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEdStatRptView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEdStatRptView)
	afx_msg void OnFirstpage();
	afx_msg void OnUpdateFirstpage(CCmdUI* pCmdUI);
	afx_msg void OnLastpage();
	afx_msg void OnUpdateLastpage(CCmdUI* pCmdUI);
	afx_msg void OnNextpage();
	afx_msg void OnUpdateNextpage(CCmdUI* pCmdUI);
	afx_msg void OnPrepage();
	afx_msg void OnUpdatePrepage(CCmdUI* pCmdUI);
	afx_msg void OnQuery();
	afx_msg void OnAppAbout();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDSTATRPTVIEW_H__E31E762A_6272_4E4B_A71D_2A259C0D0223__INCLUDED_)
