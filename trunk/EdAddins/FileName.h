// FileName.h: interface for the CFileName class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FILENAME_INCLUDED_)
#define _FILENAME_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileName  
{
protected:
	CString m_strExt;
	CString m_strfn;
	CString m_strName;
	CString m_strTitle;
	CString m_strPath;

public:
	void SetPathName(CString fn);
	CFileName();
	CString GetPathName()	{ return m_strfn; };
	CString GetPath()		{ return m_strPath;	};
	CString GetFileTitle()	{ return m_strTitle;};
	CString GetFileName()	{ return m_strName;	};
	CString GetFileExt()	{ return m_strExt;	};

public:
	UINT	lines;
	UINT	commentlines;
	UINT	codelines;
	UINT	mixedlines;
	UINT	blanklines;
};


#endif // !defined(_FILENAME_INCLUDED_)
