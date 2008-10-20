// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__E901B0EE_E78F_4927_8DEF_B330504154FB__INCLUDED_)
#define AFX_MAINFRM_H__E901B0EE_E78F_4927_8DEF_B330504154FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OutLookbar.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	COutlookBar	m_wndOutlookBar;
	CStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	void OpenFile(WPARAM wParam, LPARAM lParam);
	CDocTemplate* GetBestTemplate(LPCTSTR lpszFileName);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewOutlookBar();
	afx_msg void OnUpdateViewOutlookBar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E901B0EE_E78F_4927_8DEF_B330504154FB__INCLUDED_)
