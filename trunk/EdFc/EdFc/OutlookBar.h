#pragma once

#include "scbarg.h"
#include "XTOutBarCtrl.h"

#define IDM_LOADVIEW WM_USER + 130

class COutlookBar :
	public CSizingControlBarG
{
public:
	COutlookBar();
	virtual ~COutlookBar();
	CString m_csEdFcName;

protected:
	BOOL LoadFromXML();
	CImageList		m_ImageLarge;
	CImageList		m_ImageSmall;
	CXTOutBarCtrl	m_wndChild;

	afx_msg LRESULT OnOutbarNotify(WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CReportBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};