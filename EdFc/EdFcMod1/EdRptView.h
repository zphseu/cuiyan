#if !defined(_EDRPTVIEW_INCLUDE_)
#define _EDRPTVIEW_INCLUDE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BSRpterView.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CEdRptView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"
#include "EdRptDoc.h"
#include "ProgressCtrlX.h"

class CEdRptView : public CView
{
protected: 
	CEdRptView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEdRptView)

protected:
	CToolBar*	m_pWndToolBar;
	CEdRptDoc	doc;
	BOOL		m_bFirstDraw;
	
// Operations
public:
	void DestroyProgress();
	void StepProgress(int n, int i, BOOL bExport = FALSE);
	BOOL CreateProgress(int n);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdRptView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEdRptView();
	CProgressCtrlX*	m_pProgress;
	CStatusBar*		m_pStatusBar;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEdRptView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFileAbout();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnFileImport();
	afx_msg void OnFileExport();
	afx_msg void OnFileQuery();
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()

private:
	void ChangeWidth();      
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_EDRPTVIEW_INCLUDE_)
