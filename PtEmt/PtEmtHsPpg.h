#if !defined(AFX_PTEMTHSPPG_H__2C0EC423_493D_4F4E_906F_DBFDF288F451__INCLUDED_)
#define AFX_PTEMTHSPPG_H__2C0EC423_493D_4F4E_906F_DBFDF288F451__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PtEmtHsPpg.h : Declaration of the CPtEmtHsPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CPtEmtHsPropPage : See PtEmtHsPpg.cpp.cpp for implementation.

class CPtEmtHsPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CPtEmtHsPropPage)
	DECLARE_OLECREATE_EX(CPtEmtHsPropPage)

// Constructor
public:
	CPtEmtHsPropPage();

// Dialog Data
	//{{AFX_DATA(CPtEmtHsPropPage)
	enum { IDD = IDD_PROPPAGE_PTEMTHS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CPtEmtHsPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTEMTHSPPG_H__2C0EC423_493D_4F4E_906F_DBFDF288F451__INCLUDED)
