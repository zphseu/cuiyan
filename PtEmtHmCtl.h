#if !defined(AFX_PTEMTHMCTL_H__DF2013D6_B12F_4A43_9935_6DD004BF3F62__INCLUDED_)
#define AFX_PTEMTHMCTL_H__DF2013D6_B12F_4A43_9935_6DD004BF3F62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PtEmtHmCtl.h : Declaration of the CPtEmtHmCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmCtrl : See PtEmtHmCtl.cpp for implementation.

class CPtEmtHmCtrl : public COleControl
{
	DECLARE_DYNCREATE(CPtEmtHmCtrl)

// Constructor
public:
	CPtEmtHmCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPtEmtHmCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CPtEmtHmCtrl();

	DECLARE_OLECREATE_EX(CPtEmtHmCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CPtEmtHmCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CPtEmtHmCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CPtEmtHmCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CPtEmtHmCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CPtEmtHmCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CPtEmtHmCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CPtEmtHmCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTEMTHMCTL_H__DF2013D6_B12F_4A43_9935_6DD004BF3F62__INCLUDED)
