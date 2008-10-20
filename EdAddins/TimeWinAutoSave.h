#if !defined(AFX_TIMEWINAUTOSAVE_H__3A4CDE96_8654_4FB4_8A88_0982009A759E__INCLUDED_)
#define AFX_TIMEWINAUTOSAVE_H__3A4CDE96_8654_4FB4_8A88_0982009A759E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeWinAutoSave.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeWinAutoSave frame

class CTimeWinAutoSave : public CFrameWnd
{
	DECLARE_DYNCREATE(CTimeWinAutoSave)
public:
	CTimeWinAutoSave();           // protected constructor used by dynamic creation
	virtual ~CTimeWinAutoSave();

private:
	bool m_bregister;
	BOOL m_saveFiles;
	BOOL m_saveWorkspace;
	UINT m_period;
	UINT m_timer;
	IApplication *m_pApplication;

	// Attributes
public:
	BOOL  getByDialog()						{ return m_bByDialog;}
	BOOL  getSaveFiles()					{ return m_saveFiles;}
	BOOL  getSaveWorkspace()				{ return m_saveWorkspace;}
	UINT  getPeriod()						{ return m_period;}
	void  setApplication(IApplication *app) { m_pApplication = app;}

// Operations
public:
	BOOL m_bByDialog;
	void SetByBialog(BOOL enable);
	void setSaveWorkspace(BOOL enable);
	void setSaveFiles(BOOL enable);
	void setPeriod(UINT period);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeWinAutoSave)
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SaveParameters();
	void ParameterChanged();

	// Generated message map functions
	//{{AFX_MSG(CTimeWinAutoSave)
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEWINAUTOSAVE_H__3A4CDE96_8654_4FB4_8A88_0982009A759E__INCLUDED_)
