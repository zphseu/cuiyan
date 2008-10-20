#if !defined(AFX_CHARTPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742F__INCLUDED_)
#define AFX_CHARTPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ViewPrintPreview.h : header file
//

#include "Chart7/och2dMFC.h"
/////////////////////////////////////////////////////////////////////////////
// CChartPreview view

class CChartPreview : public CView
{
protected:
	CChartPreview();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CChartPreview)

// Attributes
public:
	CChart2D*	m_pChart;

// Operations
public:
	BOOL	m_bPrintDirect;
	virtual void OnFilePrintPreview();
	virtual void OnFilePrint();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartPreview)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL


// Implementation
protected:
	virtual ~CChartPreview();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CChartPreview)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTPREVIEW_H__137FC880_1607_11D3_9317_8F51A5F9742F__INCLUDED_)
