#if !defined(AFX_PAGE4_H__9998AC56_F1BB_4D91_9F77_43040079A795__INCLUDED_)
#define AFX_PAGE4_H__9998AC56_F1BB_4D91_9F77_43040079A795__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage4 dialog

class CPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage4)

// Construction
public:
	CPage4();
	~CPage4();

// Dialog Data
	//{{AFX_DATA(CPage4)
	enum { IDD = IDD_PAGE4 };
	CStatic	m_csp4;
	CStatic	m_csp3;
	CStatic	m_csp2;
	CScrollBar	m_cScrollBar;
	CComboBox	m_ctrlCombo;
	CTreeCtrl	m_cTree;
	CStatic	m_csp1;
	CButton	m_cbStop;
	CButton	m_cbStart;
	CStatic	m_csDisp;
	CSpinButtonCtrl	m_cs1;
	CSliderCtrl	m_csld;
	CRichEditCtrl	m_cRichEdit;
	CProgressCtrl	m_cp1;
	CMonthCalCtrl	m_cMonth;
	CListCtrl	m_cList;
	CIPAddressCtrl	m_cIp;
	CEdit	m_ce1;
	CDateTimeCtrl	m_cDt;
	CString	m_strEdit3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon1;
	// Generated message map functions
	//{{AFX_MSG(CPage4)
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonBold();
	afx_msg void OnButtonUline();
	afx_msg void OnButtonItalic();
	afx_msg void OnButtonLage();
	afx_msg void OnButtonSmall();
	afx_msg void OnButtonList();
	afx_msg void OnButtonReport();
	afx_msg void OnFieldchangedIpaddress2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnRadio9();
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bInAction;
	CImageList m_ImgSmallList;
	CImageList m_ImgLargeList;
	CImageList m_imgTree;
	BOOL m_b1,m_b2,m_b3,m_bMenu;
	int m_nInt;
	int m_ntimer;
	CString m_strInfo;  //定时器里的变量
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE4_H__9998AC56_F1BB_4D91_9F77_43040079A795__INCLUDED_)
