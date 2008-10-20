#if !defined(AFX_DLGREPORT_H__A7697D0E_F2C3_4FEB_8C21_86E9559B1597__INCLUDED_)
#define AFX_DLGREPORT_H__A7697D0E_F2C3_4FEB_8C21_86E9559B1597__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgReport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgReport dialog

#include <afxmt.h>

class CDlgReport : public CDialog
{
// Construction
public:
	CDlgReport(CWnd* pParent = NULL);   // standard constructor
public:
// Dialog Data
	//{{AFX_DATA(CDlgReport)
	enum { IDD = IDD_REPORT };
	CListBox	m_ctlList;
	//}}AFX_DATA
	CString sArgs;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgReport)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static UINT LaunchAndWait(LPVOID pParam);
	static UINT ReadPipeThreadProc(LPVOID pParam);

	struct THREADINFO 
	{
		CEvent*	pTermThreadEvent;
		CString strArgs;
		CDlgReport *pView;
	};
	
	HANDLE hChildStdoutRd;
	HANDLE hChildStdoutWr;
	HANDLE hSaveStdout;
	CWinThread*	m_pReadThread;
	DWORD dwProcessId;

	// Generated message map functions
	//{{AFX_MSG(CDlgReport)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DoDestroyPipe();
	int DoCreatePipe();
	CStringArray m_arInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREPORT_H__A7697D0E_F2C3_4FEB_8C21_86E9559B1597__INCLUDED_)
