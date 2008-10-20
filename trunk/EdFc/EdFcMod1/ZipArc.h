// ZipArc.h: interface for the CZipArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZIPARC_H__1ED983BA_BD64_499D_A4CA_32126B95B10D__INCLUDED_)
#define AFX_ZIPARC_H__1ED983BA_BD64_499D_A4CA_32126B95B10D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZipArchive.h"

class CZipArc : public CZipArchive  
{
public:
	BOOL CreateZip(CString szZipFn, CString szPw = _T(""));
	BOOL AddFileToZip(LPCTSTR szFileName);
	BOOL CloseZip();
	CZipArc();
	virtual ~CZipArc();
};

#endif // !defined(AFX_ZIPARC_H__1ED983BA_BD64_499D_A4CA_32126B95B10D__INCLUDED_)
