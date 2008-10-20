#if !defined(AFX_GRIDPPG_H__8BDDEC4A_C5BF_4578_8A79_EC12400B9EE3__INCLUDED_)
#define AFX_GRIDPPG_H__8BDDEC4A_C5BF_4578_8A79_EC12400B9EE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// GridPpg.h : Declaration of the CEdGridPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CEdGridPropPage : See GridPpg.cpp.cpp for implementation.

class CEdGridPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEdGridPropPage)
	DECLARE_OLECREATE_EX(CEdGridPropPage)

// Constructor
public:
	CEdGridPropPage();

// Dialog Data
	//{{AFX_DATA(CEdGridPropPage)
	enum { IDD = IDD_PROPPAGE_EDGRID };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CEdGridPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDPPG_H__8BDDEC4A_C5BF_4578_8A79_EC12400B9EE3__INCLUDED)
