// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__825ABC01_61C8_11D6_B538_0050BAC89A64__INCLUDED_)
#define AFX_MAINFRM_H__825ABC01_61C8_11D6_B538_0050BAC89A64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OutlookBar.h"
#include "afxcmn.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetDefaultView();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar		m_wndStatusBar;	
	COutlookBar		m_wndOutlookBar;
	CToolBar		m_wndToolBar;
	CToolBar		m_wndBmpBar;
	int				m_nCurBar;
	HINSTANCE		m_hDLL;	
	CView*			m_pDefView;
	
protected:
	#define WM_LOAD_VIEW WM_USER
	#define WM_GETTOOLBAR WM_USER+1
	HRESULT MsgLoadView(WPARAM wParam, LPARAM lParam);		
	HRESULT MsgGetToolBar(WPARAM wParam, LPARAM lParam);
	
protected:
	int GetBarType(UINT nToolBarRes, UINT nToolBarBmp);
	void EableToolBarMenu(UINT nToolBarRes, UINT nToolBarBmp);
	HRESULT OnLoadView(WPARAM wParam, LPARAM lParam);
	HRESULT LoadView(LPCSTR szDll, LPCSTR szView, LPCSTR szData);
	void ShowMessage(const char *fmt, ...);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewOutlookBar();
	afx_msg void OnUpdateViewOutlookBar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void MakeToolbarImageList(UINT inBitmapID , CImageList& imglst);
	void ReplaceBackgroundColor(CBitmap& bm);
	CImageList *m_ptbImages;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__825ABC01_61C8_11D6_B538_0050BAC89A64__INCLUDED_)
