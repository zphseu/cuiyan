#if !defined(AFX_PTEMTHMPPG_H__CFFB270E_59B6_4325_8DEF_BA670C843850__INCLUDED_)
#define AFX_PTEMTHMPPG_H__CFFB270E_59B6_4325_8DEF_BA670C843850__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PtEmtHmPpg.h : Declaration of the CPtEmtHmPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CPtEmtHmPropPage : See PtEmtHmPpg.cpp.cpp for implementation.

class CPtEmtHmPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CPtEmtHmPropPage)
	DECLARE_OLECREATE_EX(CPtEmtHmPropPage)

// Constructor
public:
	CPtEmtHmPropPage();

// Dialog Data
	//{{AFX_DATA(CPtEmtHmPropPage)
	enum { IDD = IDD_PROPPAGE_PTEMTHM };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CPtEmtHmPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTEMTHMPPG_H__CFFB270E_59B6_4325_8DEF_BA670C843850__INCLUDED)
