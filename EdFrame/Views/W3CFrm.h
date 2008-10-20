// W3CFrm.h : interface of the CW3CFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_W3CFRM_H__D0C94568_64B1_474C_826A_9A94B1FF2CC5__INCLUDED_)
#define AFX_W3CFRM_H__D0C94568_64B1_474C_826A_9A94B1FF2CC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CW3CFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CW3CFrame)
public:
	CW3CFrame();

// Attributes
protected:
	CToolBar    m_wndToolBar;
	CImageList	m_ToolbarImages;

public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CW3CFrame)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CW3CFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	void ReplaceBackgroundColor(CBitmap& bm);
	void MakeToolbarImageList(UINT inBitmapID, CImageList& imglst);
	//{{AFX_MSG(CW3CFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_W3CFRM_H__D0C94568_64B1_474C_826A_9A94B1FF2CC5__INCLUDED_)
