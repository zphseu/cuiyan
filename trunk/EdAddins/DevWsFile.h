// DevWsFile.h: interface for the CDevWsFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVWSFILE_H__52D9F3D2_D5A4_484F_97BC_EAEF46EC44E4__INCLUDED_)
#define AFX_DEVWSFILE_H__52D9F3D2_D5A4_484F_97BC_EAEF46EC44E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileName.h"

class CDevSrcFile : public CFileName
{
protected:
	UINT FindComment(CString sLine, LPCTSTR sComment, BOOL bIgnoreSt = FALSE);
public:
	void GetStat();
	BOOL isSrcFile;
};

class CDevPrjFile : public CFileName
{
public:
	void GetStat();
	void RefreshFileList(CString exts);
	CDevPrjFile();
	~CDevPrjFile();

	UINT	numFile;
	CDevSrcFile* pFilelist;
};


class CDevWsFile : public CFileName  
{
public:
	BOOL GetParam(CString regkey);
	BOOL SetParam(CString regkey);
	void GetStat();
	void RefreshFileList(IApplication* pApp);
	CDevWsFile();
	~CDevWsFile();

	CString srcext;
	long	numProj;
	CDevPrjFile* pProjlist;
};

#endif // !defined(AFX_DEVWSFILE_H__52D9F3D2_D5A4_484F_97BC_EAEF46EC44E4__INCLUDED_)
