// Soapcpp2view.h : interface of the CSoapcpp2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPCPP2VIEW_H__8CD6E39F_4DED_4DC2_9F31_C894A2062065__INCLUDED_)
#define AFX_SOAPCPP2VIEW_H__8CD6E39F_4DED_4DC2_9F31_C894A2062065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSoapcpp2View : public CFormView
{
protected: // create from serialization only
	CSoapcpp2View();
	DECLARE_DYNCREATE(CSoapcpp2View)

public:
	//{{AFX_DATA(CSoapcpp2View)
	enum { IDD = IDD_SOAPCPP2_FORM };
	BOOL	m_bC;
	BOOL	m_bH;
	BOOL	m_bM;
	BOOL	m_bW;
	BOOL	m_bServer;
	BOOL	m_bClient;
	int		m_nClient;
	int		m_nCompiler;
	int		m_nServer;
	int		m_nVersion;
	CString	m_csHeadFile;
	CString	m_csPrjName;
	CString	m_csPrjPath;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoapcpp2View)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSoapcpp2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSoapcpp2View)
	afx_msg void OnCheckClient();
	afx_msg void OnCheckServer();
	afx_msg void OnBtnBrowerHeadfile();
	afx_msg void OnBtnBrowerPath();
	afx_msg void OnBtnGenerate();
	afx_msg void OnRadioCompiler3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOAPCPP2VIEW_H__8CD6E39F_4DED_4DC2_9F31_C894A2062065__INCLUDED_)
