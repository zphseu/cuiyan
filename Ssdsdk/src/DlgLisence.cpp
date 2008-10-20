// DlgLisence.cpp: implementation of the CDlgLisence class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DlgLisence.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static CWnd*pBtnOK = NULL;

CDlgLisence::CDlgLisence(CWnd* pParent)
: CDynDialogEx(pParent)
{
	m_bAddSystemButtons = FALSE;
}

CDlgLisence::~CDlgLisence()
{
	
}

BEGIN_MESSAGE_MAP(CDlgLisence, CDynDialogEx)
//{{AFX_MSG_MAP(CListDynDialogEx)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

UINT CDlgLisence::OnTimer(LPVOID pParam)
{
	DWORD nSecond = (DWORD)pParam;
	Sleep(nSecond * 1000);
	pBtnOK->EnableWindow();
	return 0;
}

int CDlgLisence::DoModal(LPCSTR sInfo, DWORD nsecond)
{
	SetWindowTitle(_T("Dialog Lisence"));
	AddDlgControl(STATICTEXT, sInfo, STYLE_STATIC, EXSTYLE_STATIC, CRect(10, 10, 120, 90));
	AddDlgControl(BUTTON, _T("OK"), STYLE_BUTTON | WS_DISABLED, EXSTYLE_BUTTON, CRect(10, 97, 115, 110), NULL, IDOK);
	pBtnOK = m_arrDlgItemPtr[1];
	AfxBeginThread(OnTimer, LPVOID(nsecond));
	return CDynDialogEx::DoModal();
}
