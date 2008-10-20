#if !defined(AFX_GRIDCTL_H__DB4FB00B_E1C9_4E98_A488_B55388ABCC9A__INCLUDED_)
#define AFX_GRIDCTL_H__DB4FB00B_E1C9_4E98_A488_B55388ABCC9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GridCtl.h : Declaration of the CEdGridCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CEdGridCtrl : See GridCtl.cpp for implementation.
#include "Markup.h"
#include "MSFlexGrid.h"

class CGridPreview;
class CEdGridCtrl : public COleControl
{
	friend class CGridPreview;
	DECLARE_DYNCREATE(CEdGridCtrl)
		
private:
	CSingleDocTemplate m_sdTemplate;
	
// Constructor
public:
	CEdGridCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdGridCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid) {};
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CEdGridCtrl();

	DECLARE_OLECREATE_EX(CEdGridCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CEdGridCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CEdGridCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CEdGridCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CEdGridCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CEdGridCtrl)
	long m_lVisualWidth;
	CString m_csFontName;
	CString m_csTitle;
	CString m_csHeadRight;
	CString m_csFootLeft;
	CString m_csFootRight;
	CString m_csColsWidthStr;
	afx_msg void OnColsWidthStrChanged();
	afx_msg long GetFixedCols();
	afx_msg void SetFixedCols(long nNewValue);
	afx_msg long ReadFile(LPCTSTR lpszFileName, LPCTSTR lpszTableName);
	afx_msg long ReadDB(LPCTSTR lpszConnectString, LPCTSTR lpszUserName, LPCTSTR lpszPassword, LPCTSTR lpszRecordSource);
	afx_msg void doPrint(LPCTSTR lpszPrinterName);
	afx_msg void doPrintPreview();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CEdGridCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CEdGridCtrl)
	dispidVisualWidth = 1L,
	dispidFontName = 2L,
	dispidTitle = 3L,
	dispidHeadRight = 4L,
	dispidFootLeft = 5L,
	dispidFootRight = 6L,
	dispidFixedCols = 8L,
	dispidColsWidthStr = 7L,
	dispidReadFile = 9L,
	dispidReadDB = 10L,
	dispidDoPrint = 11L,
	dispidDoPrintPreview = 12L,
	//}}AFX_DISP_ID
	};

private:
	BOOL readFileHead(CMarkup &xml, long &lFixedCols);
	BOOL readFileFindTable(CMarkup& xml, CString& csTableName);

	BOOL IsVScrollBar(int yLogical, int cy);
	void SetStyle();
    void OnMyBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
    void OnMyPrint(CDC *pDC, CPrintInfo *pInfo);
    void OnMyEndPrinting(CDC *pDC, CPrintInfo *pInfo);	
	long GetColsWidth();
	long GetRowHeight(long i);
	long GetFixedRowHeight();
    void PrintColumnHeadings(CDC *pDC, CPrintInfo *pInfo);
    void PrintHeader(CDC *pDC, CPrintInfo *pInfo);
    void PrintFooter(CDC *pDC, CPrintInfo *pInfo);
    BOOL  DrawFixedCell(CDC* pDC, int nRow, int nCol, CRect rect);
    BOOL  DrawCell(CDC* pDC, int nRow, int nCol, CRect rect);

	CMSFlexGrid m_Grid;
    CFont       m_PrinterFont;  // for the printer
    int         m_nPageHeight;
    CSize       m_CharSize;
	CSize		m_PaperSize;            // Page size in device units.
    CSize       m_LogicalPageSize;      // Page size in gridctrl units.

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCTL_H__DB4FB00B_E1C9_4E98_A488_B55388ABCC9A__INCLUDED)
