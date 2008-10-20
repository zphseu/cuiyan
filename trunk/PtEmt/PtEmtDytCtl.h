#if !defined(AFX_PTEMTDYTCTL_H__DDE57C3B_7B14_443C_BEB6_152A09BC8285__INCLUDED_)
#define AFX_PTEMTDYTCTL_H__DDE57C3B_7B14_443C_BEB6_152A09BC8285__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PtEmtDytCtl.h : Declaration of the CPtEmtDytCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytCtrl : See PtEmtDytCtl.cpp for implementation.
#include "PtEmtFiles.h"

class CPtEmtDytCtrl : public COleControl
{
	DECLARE_DYNCREATE(CPtEmtDytCtrl)

// Constructor
public:
	CPtEmtDytCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPtEmtDytCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

protected:
// Implementation
	PtEmtFiles	m_PtEmt;
	CPoint m_Center;
	FLOAT m_Scale;
protected:
	CPoint _PToL(COMPLEX nd);
	~CPtEmtDytCtrl();

	DECLARE_OLECREATE_EX(CPtEmtDytCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CPtEmtDytCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CPtEmtDytCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CPtEmtDytCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CPtEmtDytCtrl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CPtEmtDytCtrl)
	afx_msg long PFile2Picture(LPCTSTR sPFileName, SHORT iType, SHORT iMethodType, SHORT dParma1, FLOAT dParam2, FLOAT dParam3);
	afx_msg long SavePicture(LPCTSTR sPicFileName);
	afx_msg long FFile2Picture(LPCTSTR sFFileName, SHORT iType, SHORT iMethodType);
	afx_msg long GFile2Picture(LPCTSTR szFileName);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CPtEmtDytCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CPtEmtDytCtrl)
	dispidPFile2Picture = 1L,
	dispidSavePicture = 2L,
	dispidFFile2Picture = 3L,
	dispidGFile2Picture = 4L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTEMTDYTCTL_H__DDE57C3B_7B14_443C_BEB6_152A09BC8285__INCLUDED)
