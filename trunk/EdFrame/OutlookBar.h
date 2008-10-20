// OutlookBar.h: interface for the COutlookBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTLOOKBAR_H__A7213018_27D1_44FB_8078_C67375E11CFE__INCLUDED_)
#define AFX_OUTLOOKBAR_H__A7213018_27D1_44FB_8078_C67375E11CFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "scbarg.h"
#include "XTOutBarCtrl.h"

class COutlookBar : public CSizingControlBarG  
{
public:
	COutlookBar();
	virtual ~COutlookBar();

protected:
	CUIntArray		m_arStart;
	CStringArray	m_arFolder;
	CStringArray	m_arFiles;
	CStringArray	m_arTexts;
	CImageList		m_ImageLarge;
	CImageList		m_ImageSmall;
	CXTOutBarCtrl	m_wndChild;
	CArray<HINSTANCE, HINSTANCE> m_arHandles;
	
	BOOL GetFromXML(LPCTSTR szFile);
	BOOL GetFromPath(LPCTSTR szPath);
	
protected:
	CString GetModuleProductName(LPSTR szFileName);
	void Clean(BOOL bDelDocManager = TRUE);

	afx_msg LRESULT OnOutbarNotify(WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CReportBar)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_OUTLOOKBAR_H__A7213018_27D1_44FB_8078_C67375E11CFE__INCLUDED_)
