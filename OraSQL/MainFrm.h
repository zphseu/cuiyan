// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__B6651055_CD89_427A_A9E9_FC06706DC40C__INCLUDED_)
#define AFX_MAINFRM_H__B6651055_CD89_427A_A9E9_FC06706DC40C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Odb.h"
#include "OraInView.h"
#include "OraOutView.h"

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
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	void Output(CStringArray& arOut);
	CSplitterWnd m_wndSplitter;
	COraOutView*m_pOutView;
	COraInView*	m_pInView;
	CSQLCmd		m_cmd;
	COdb m_db;

	void Help();
	void About();
	void Output( LPCTSTR csOut[] );
	HRESULT RunCommand( CString csCommandLine );

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnFileRun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B6651055_CD89_427A_A9E9_FC06706DC40C__INCLUDED_)
