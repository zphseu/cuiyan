// TnsNamesFile.h: interface for the CTnsNamesFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TNSNAMESFILE_H__EAEC2177_D59D_4CB7_B905_45CD8200FD05__INCLUDED_)
#define AFX_TNSNAMESFILE_H__EAEC2177_D59D_4CB7_B905_45CD8200FD05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OneTns.h"
#include <afxtempl.h>

class CTnsNamesFile
{
protected:
	BOOL Parse(CString& strFile);
	CString GetFileName();
	
public:
	BOOL Save();
	BOOL Load();
	CArray<COneTns, COneTns> Tns;
};

#endif // !defined(AFX_TNSNAMESFILE_H__EAEC2177_D59D_4CB7_B905_45CD8200FD05__INCLUDED_)
