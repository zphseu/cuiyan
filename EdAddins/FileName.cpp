// FileName.cpp: implementation of the CFileName class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileName.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CFileName::CFileName()
{
	blanklines = 0;
	codelines = 0;
	commentlines = 0;
	mixedlines = 0;
	lines = 0;
	m_strfn = _T("");
}

void CFileName::SetPathName(CString fn)
{
	CString tmp = m_strfn = fn;
	int i = 0;

	if (tmp.Find('.') != -1)
	{
		i = m_strfn.GetLength() - m_strfn.ReverseFind('.') - 1;
		m_strExt = tmp.Right(i);
	}
	
	if (tmp.Find('\\') != -1 || tmp.Find('/') != -1)
	{
		int i1 = m_strfn.GetLength() - m_strfn.ReverseFind('\\') - 1;
		int i2 = m_strfn.GetLength() - m_strfn.ReverseFind('/') - 1;
		i = (i1 < i2) ? i1 : i2;
		m_strName = tmp.Right(i);
	}
	else
		m_strName = m_strfn;
	
	
	i = m_strName.GetLength() - m_strExt.GetLength() - 1;
	m_strTitle = (i > 0) ? m_strName.Left(i) : _T("");

	i = m_strfn.GetLength() - m_strName.GetLength();
	m_strPath = (i > 0) ? m_strfn.Left(i) : _T("");

}
