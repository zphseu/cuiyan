#if !defined(AFX_CHARTCTL_H__35A0C72B_724F_45EA_993A_9DE0357E5E70__INCLUDED_)
#define AFX_CHARTCTL_H__35A0C72B_724F_45EA_993A_9DE0357E5E70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ChartCtl.h : Declaration of the CEdChartCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CEdChartCtrl : See ChartCtl.cpp for implementation.
#include "Chart7/och2dMFC.h"

class CChartPreview;
class CEdChartCtrl : public COleControl
{
	friend class CChartPreview;

	DECLARE_DYNCREATE(CEdChartCtrl)

// Constructor
public:
	CEdChartCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdChartCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void PaintChildWindows(HWND hWndParent, CDC* pDC, CPoint ptOffset);
	LRESULT OnOC2Repaint(WPARAM wParam, LPARAM lParam);
	LRESULT OnOC2PaletteChanged(WPARAM, LPARAM);
	
	~CEdChartCtrl();

	DECLARE_OLECREATE_EX(CEdChartCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CEdChartCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CEdChartCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CEdChartCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CEdChartCtrl)
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CEdChartCtrl)
	CString m_csHeaderFont;
	afx_msg void OnHeaderFontChanged();
	CString m_csHeaderStr;
	afx_msg void OnHeaderStrChanged();
	CString m_csFooterFont;
	afx_msg void OnFooterFontChanged();
	CString m_csFooterStr;
	afx_msg void OnFooterStrChanged();
	CString m_csXTitle;
	afx_msg void OnXTitleChanged();
	CString m_csYTitle;
	afx_msg void OnYTitleChanged();
	CString m_csLengendTitle;
	afx_msg void OnLengendTitleChanged();
	OLE_COLOR m_clrBack;
	afx_msg void OnBackColorChanged();
	OLE_COLOR m_clrGraphBack;
	afx_msg void OnGraphBackColorChanged();
	OLE_COLOR m_clrArea;
	afx_msg void OnAreaColorChanged();
	CString m_csXPointNames;
	afx_msg void OnXPointNamesChanged();
	BOOL m_bInvertOrientation;
	afx_msg void OnInvertOrientationChanged();
	BOOL m_bStyle3D;
	afx_msg void OnStyle3DChanged();
	long m_lChartType;
	afx_msg void OnChartTypeChanged();
	CString m_csYSetNames;
	afx_msg void OnYSetNamesChanged();
	BOOL m_bAlarmZone;
	afx_msg void OnAlarmZoneChanged();
	afx_msg void doPrint(LPCTSTR lpszPrinterName);
	afx_msg void doPrintPreview();
	afx_msg long ReadFile(LPCTSTR lpszFileName);
	afx_msg BOOL SaveAs(LPCTSTR lpszFileName);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CEdChartCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CEdChartCtrl)
	dispidHeaderFont = 1L,
	dispidHeaderStr = 2L,
	dispidFooterFont = 3L,
	dispidFooterStr = 4L,
	dispidXTitle = 5L,
	dispidYTitle = 6L,
	dispidLengendTitle = 7L,
	dispidBackColor = 8L,
	dispidGraphBackColor = 9L,
	dispidAreaColor = 10L,
	dispidXPointNames = 11L,
	dispidInvertOrientation = 12L,
	dispidStyle3D = 13L,
	dispidChartType = 14L,
	dispidYSetNames = 15L,
	dispidAlarmZone = 16L,
	dispidDoPrint = 17L,
	dispidDoPrintPreview = 18L,
	dispidReadFile = 19L,
	dispidSaveAs = 20L,
	//}}AFX_DISP_ID
	};

private:
	void OnPropertyChanged();
	BOOL GetSubString(CString& sc, LPCTSTR s, int n, TCHAR ch);
	DWORD GetConfigColor(LPCTSTR lpszFileName, int n, LPCTSTR sdef = NULL);
	LPTSTR GetConfigStr(LPCTSTR lpszFileName, LPCTSTR str, INT n, LPCTSTR sdef = NULL);
	LPTSTR* GetConfigStrs(LPCTSTR str);	

	CChart2D		m_Chart;
    CChart2DData*	m_pData;

	CSingleDocTemplate m_sdTemplate;
	
	LPTSTR*			m_pStrs;
	CStringArray	m_ar;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTCTL_H__35A0C72B_724F_45EA_993A_9DE0357E5E70__INCLUDED)
