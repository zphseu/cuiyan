#if !defined(AFX_GRIDPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742F__INCLUDED_)
#define AFX_GRIDPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ViewPrintPreview.h : header file
//

#include "EdGridCtl.h"
/////////////////////////////////////////////////////////////////////////////
// CGridPreview view

class CGridPreview : public CView
{
protected:
	CGridPreview();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGridPreview)

// Attributes
public:
	CEdGridCtrl*	m_pCtrl;

// Operations
public:
	BOOL	m_bPrintDirect;
	virtual void OnFilePrintPreview();
	virtual void OnFilePrint();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridPreview)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL


// Implementation
protected:
	virtual ~CGridPreview();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CGridPreview)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742F__INCLUDED_)
