#if !defined(AFX_PTEMTDYTPPG_H__51C23A29_DA39_4F10_A8C1_3948AB6D32D0__INCLUDED_)
#define AFX_PTEMTDYTPPG_H__51C23A29_DA39_4F10_A8C1_3948AB6D32D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PtEmtDytPpg.h : Declaration of the CPtEmtDytPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CPtEmtDytPropPage : See PtEmtDytPpg.cpp.cpp for implementation.

class CPtEmtDytPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CPtEmtDytPropPage)
	DECLARE_OLECREATE_EX(CPtEmtDytPropPage)

// Constructor
public:
	CPtEmtDytPropPage();

// Dialog Data
	//{{AFX_DATA(CPtEmtDytPropPage)
	enum { IDD = IDD_PROPPAGE_PTEMTDYT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CPtEmtDytPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTEMTDYTPPG_H__51C23A29_DA39_4F10_A8C1_3948AB6D32D0__INCLUDED)
