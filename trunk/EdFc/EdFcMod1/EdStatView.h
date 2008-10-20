#if !defined(AFX_TESTDLLVIEW_H__438E6EA3_49CA_4B2F_81AF_70D38E71C4B0__INCLUDED_)
#define AFX_TESTDLLVIEW_H__438E6EA3_49CA_4B2F_81AF_70D38E71C4B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EdStatView.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CEdStatView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"
#include "EdStatDoc.h"

class CEdStatView : public CView
{
protected:
	CEdStatView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEdStatView)
		enum GRAPHTYPE { 
		LINE,
		BAR, 
		BAR3D, 
		PIE, 
		CUTPIE, 
		EMPTY 
	} m_GraphType;	

protected:
	CEdStatDoc	m_Doc;
	BOOL m_bFirstDraw;
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdStatView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void PrintQueryCondition(CDC *pDC, CRect rect, LPCSTR strDesc);
	virtual ~CEdStatView();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEdStatView)
	afx_msg void OnQuery();
	afx_msg void OnAppAbout();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	
	//}}AFX_MSG
	afx_msg void OnTypeDraw(UINT ID);
	afx_msg void OnUpdateTypeDraw(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLLVIEW_H__438E6EA3_49CA_4B2F_81AF_70D38E71C4B0__INCLUDED_)
