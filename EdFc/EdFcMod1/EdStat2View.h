#if !defined(_EDSTAT2VIEW_INCLUDE_)
#define _EDSTAT2VIEW_INCLUDE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EdStat2View.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CEdStat2View form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "resource.h"
#include "Chart7/och2dMFC.h"

class CEdStat2View : public CView
{
protected:
	CEdStat2View();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEdStat2View)
	
protected:
	CChart2D		m_chart;
    CChart2DData*	m_pData;
	XrtType			m_uChartType;
	UINT			m_u3d;			// 0. no 3d, not zero. 3d
	BOOL			m_bInvert;

	TCHAR			m_szFileName[MAX_PATH];
	
	LPSTR			*m_pStrs;
	CStringArray	m_ar;
	BOOL		m_bFirstDraw;
public:

// Attributes
public:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdStat2View)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnDraw(CDC* pDC);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL GetData();
	void OnUpdateChangeType(CCmdUI *pCmdUI);
	void OnChangeType(UINT nID);
	void PaintChildWindows(HWND hWndParent, CDC* pDC, CPoint ptOffset);
	LRESULT OnOC2Repaint(WPARAM wParam, LPARAM lParam);
	LRESULT OnOC2PaletteChanged(WPARAM, LPARAM);
	virtual ~CEdStat2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	DWORD GetConfigColor(int n, LPCSTR sdef = NULL);
	LPSTR GetConfigStr(LPCSTR str, UINT n, LPCSTR sdef = NULL);
	LPSTR* GetConfigStrs(LPCSTR str);	
	// Generated message map functions
	//{{AFX_MSG(CEdStat2View)
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHelp();
	afx_msg void OnQuery();
	afx_msg void On3dstyle();
	afx_msg void OnUpdate3dstyle(CCmdUI* pCmdUI);
	afx_msg void OnAlarmzone();
	afx_msg void OnUpdateAlarmzone(CCmdUI* pCmdUI);
	afx_msg void OnInvert();
	afx_msg void OnUpdateInvert(CCmdUI* pCmdUI);
	afx_msg void OnExcel();
	afx_msg void OnSaveas();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_EDSTAT2VIEW_INCLUDE_)
