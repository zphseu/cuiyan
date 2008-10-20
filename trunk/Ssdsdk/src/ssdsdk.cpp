#include "stdafx.h"
#include "ssd.h"
#include "DlgLisence.h"

BOOL IsTimeOut(CString errMsg, CTime tm)
{
	ASSERT(!errMsg.IsEmpty());
	if (CTime::GetCurrentTime() >= tm) {
		AfxMessageBox(errMsg);
		return FALSE;
	}
	return TRUE;
}

BOOL IsRegisted(CString email, CRYPTTYPE crypt)
{
	CSSD x(crypt);
	return x.verify(email);
}

BOOL IsDlgLisence(LPCSTR sInfo)
{
	CDlgLisence dlg;
	return dlg.DoModal(sInfo) == IDOK;
}
