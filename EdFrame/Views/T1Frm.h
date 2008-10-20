// T1Frm.h : interface of the CT1Frame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_T1FRM_H__41766C30_CDD9_465E_83AE_5AEDE8905020__INCLUDED_)
#define AFX_T1FRM_H__41766C30_CDD9_465E_83AE_5AEDE8905020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CT1Frame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CT1Frame)
public:
	CT1Frame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT1Frame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CT1Frame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	CToolBar    m_wndToolBar;
	
	//{{AFX_MSG(CT1Frame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T1FRM_H__41766C30_CDD9_465E_83AE_5AEDE8905020__INCLUDED_)
