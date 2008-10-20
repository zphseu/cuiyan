#if !defined(AFX_CHARTPPG_H__61AADFA6_72C9_4466_BB00_1A46FDD882E0__INCLUDED_)
#define AFX_CHARTPPG_H__61AADFA6_72C9_4466_BB00_1A46FDD882E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ChartPpg.h : Declaration of the CEdChartPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CEdChartPropPage : See ChartPpg.cpp.cpp for implementation.

class CEdChartPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEdChartPropPage)
	DECLARE_OLECREATE_EX(CEdChartPropPage)

// Constructor
public:
	CEdChartPropPage();

// Dialog Data
	//{{AFX_DATA(CEdChartPropPage)
	enum { IDD = IDD_PROPPAGE_EDCHART };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CEdChartPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTPPG_H__61AADFA6_72C9_4466_BB00_1A46FDD882E0__INCLUDED)
