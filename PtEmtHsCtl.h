#if !defined(AFX_PTEMTHSCTL_H__BB873BD4_081C_4AED_A9A2_B5CB3F2F2222__INCLUDED_)
#define AFX_PTEMTHSCTL_H__BB873BD4_081C_4AED_A9A2_B5CB3F2F2222__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PtEmtHsCtl.h : Declaration of the CPtEmtHsCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsCtrl : See PtEmtHsCtl.cpp for implementation.

class CPtEmtHsCtrl : public COleControl
{
	DECLARE_DYNCREATE(CPtEmtHsCtrl)

// Constructor
public:
	CPtEmtHsCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPtEmtHsCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CPtEmtHsCtrl();

	DECLARE_OLECREATE_EX(CPtEmtHsCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CPtEmtHsCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CPtEmtHsCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CPtEmtHsCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CPtEmtHsCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CPtEmtHsCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CPtEmtHsCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CPtEmtHsCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTEMTHSCTL_H__BB873BD4_081C_4AED_A9A2_B5CB3F2F2222__INCLUDED)
