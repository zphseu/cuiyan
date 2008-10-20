/**************************************************************
 *  filename:    CommentData.cpp
 *  copyright:   Shanghai Baosight Software Co., Ltd.
 *
 *  description: to gen Comment data .
 *
 *  @author:     cuiyan
 *  history:
 *    1.  11/17/2002  cuiyan  Initial Version
 *
**************************************************************/
// CommentData.cpp: implementation of the CCommentData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdAddins.h"
#include "CommentData.h"
#include "LMCONS.H"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommentData::CCommentData()
{
	CTime time = CTime::GetCurrentTime();
	m_szAppPath = _T("");
	m_szDay = time.Format("%d");
	m_szMonth = time.Format("%m");
	m_szYear = time.Format("%Y");
	m_sz_ddmmyyyy = time.Format("%d/%m/%Y");
	m_sz_mmddyyyy = time.Format("%m/%d/%Y");

	m_bOpen = TRUE;
}

BOOL CCommentData::GetComments(IApplication* pApp, CString type)
{
	DWORD nSize = UNLEN;

	m_szPrjFileName = _T("");
	m_szPrjPath = _T("");
	m_szPrjDocPath= _T("");
	m_szDocFileName = _T("");
	m_szCompanyName = _T("");
	m_szTradeMark = _T("");
	m_szProductName = _T("");
	m_szComments = _T("");
	m_szVersion = _T("");
	m_szlComments.RemoveAll();

	char tmp[UNLEN + 1 ] = "";
	if ( !GetUserName(tmp, &nSize) )
	{
		AfxMessageBox("Can not get the current UserName!");
		return FALSE;
	}
	m_szUserName = tmp;

	if ( !GetMethodInfo(pApp, type) )
		return FALSE;

	if ( !GetInfoFromOpenPrj( pApp ) )
		return FALSE;

	if ( !GetCommentFromFile( type ) )
		return FALSE;
	
	if ( !Especial(type) )
		return FALSE;
	
	return TRUE;
}



BOOL CCommentData::GetInfoFromOpenPrj(IApplication *pApp)
{
	CComBSTR bstr;

	//GetProjectName
	IGenericProject* pPrj = NULL;
	pApp->get_ActiveProject((IDispatch**)&pPrj);
	if (pPrj)
	{	
		pPrj->get_Name( &bstr );
		m_szPrjFileName = bstr;
		
		//get Resource Name
		m_szCmtFileName = AfxGetApp()->m_pszHelpFilePath;
		m_szCmtFileName.MakeLower();
		m_szCmtFileName.Replace(".hlp", ".ini");

		pPrj->get_FullName( &bstr );
		CString strRcFileName = bstr;
		DWORD i = strRcFileName.ReverseFind('.');
		m_szPrjPath = strRcFileName.Left(strRcFileName.ReverseFind('\\') + 1);

#ifndef _DEBUG
		char chTempPath[MAX_PATH];
		GetTempPath(MAX_PATH, chTempPath);
		m_szPrjDocPath = CString(chTempPath) + CString("docs\\");
#else
		m_szPrjDocPath = m_szPrjPath + CString("docs\\");
#endif

		strRcFileName = strRcFileName.Left(i) + _T(".rc");

		pPrj->Release();
	}
	
	//GetDocName
	IGenericDocument* pDoc = NULL;
	pApp->get_ActiveDocument((IDispatch**)&pDoc);		
	if (!pDoc)
		return FALSE;

	pDoc->get_Name( &bstr );
	m_szDocFileName = bstr;
	pDoc->Release();
	
	return TRUE;
}


BOOL CCommentData::GetCommentFromFile(CString type)
{
	if (!Open(m_szCmtFileName, CFile::modeRead | CFile::typeText))
	{
		AfxMessageBox("Can not open the CommentWizard file: " + m_szCmtFileName);
		return FALSE;
	}
	
	CString s, sTrim;
	while(ReadString(s))
	{
		CString typeRight;
		sTrim = s;
		sTrim.TrimLeft();
		sTrim.TrimRight();
		int pos = sTrim.Find( type );
		typeRight = sTrim.Right(sTrim.GetLength() - pos - type.GetLength());
		if ( sTrim.Find( "#{" ) == 0 && pos >= 0 
			&& typeRight.IsEmpty())
			break;
	}

	while(ReadString(s))
	{
		sTrim = s;
		sTrim.TrimLeft();
		if ( sTrim.Find( "#}" ) == 0)
			break;
		ReplaceMacro(s);		
	}

	Close();
	
	return TRUE;
}

VOID CCommentData::ReplaceMacro(CString &s)
{
	while(s.Replace(_T("$(Private)"), m_strPrivate	) != 0);
	while(s.Replace(_T("$(Static)"), m_strStatic		) != 0);
	while(s.Replace(_T("$(Language)"), m_strLanguage	) != 0);

	while(s.Replace(_T("$(ActiveProject)"), m_szPrjFileName	) != 0);
	while(s.Replace(_T("$(ActiveProjectPath)"), m_szPrjPath ) != 0);
	while(s.Replace(_T("$(ActiveProjectDocPath)"), m_szPrjDocPath ) != 0);

	while(s.Replace(_T("$(FileName)"),		m_szDocFileName	) != 0);

	while(s.Replace(_T("$(UserName)"),		m_szUserName	) != 0);
	
	while(s.Replace(_T("$(CompanyName)"),	m_szCompanyName	) != 0);
	while(s.Replace(_T("$(Comments)"),		m_szComments	) != 0);
	while(s.Replace(_T("$(Trademark)"),		m_szTradeMark	) != 0);
	while(s.Replace(_T("$(ProductName)"),	m_szProductName	) != 0);
	while(s.Replace(_T("$(ProductVersion)"),m_szVersion		) != 0);

	while(s.Replace(_T("$(mm/dd/yyyy)"),	m_sz_mmddyyyy	) != 0);
	while(s.Replace(_T("$(dd/mm/yyyy)"),	m_sz_ddmmyyyy	) != 0);
	while(s.Replace(_T("$(Month)"),			m_szMonth		) != 0);
	while(s.Replace(_T("$(Day)"),			m_szDay			) != 0);
	while(s.Replace(_T("$(Year)"),			m_szYear		) != 0);

	while(s.Replace(_T("$(ClassName)"),		m_szClassName	) != 0);
	while(s.Replace(_T("$(MethodName)"),	m_szMethodName	) != 0);
	while(s.Replace(_T("$(ReturnType)"),	m_szReturnType	) != 0);
	while(s.Replace(_T("$(FunPrototype)"),	m_szFunPrototype) != 0);

	if (m_szAppPath.IsEmpty())
	{
		m_szAppPath = AfxGetApp()->m_pszHelpFilePath;
		m_szAppPath = m_szAppPath.Left(m_szAppPath.ReverseFind('\\'));
	}

	while(s.Replace(_T("$(APPPATH)"),	m_szAppPath) != 0);

	if (s.Find("$(Argument)") >= 0)
	{
		CString szArg;
		POSITION posArg = m_szlArgument.GetHeadPosition();
		while(posArg)
		{
			CString szTmp = s;
			szArg = m_szlArgument.GetNext(posArg);
			while(szTmp.Replace(_T("$(Argument)"), szArg) != 0);
			m_szlComments.AddTail( szTmp + "\n");
		}
	}
	else if (s.Find("$(Argument+Type)") >= 0)
	{
		POSITION posArg = m_szlArgument.GetHeadPosition();
		POSITION posArgType = m_szlArgumentType.GetHeadPosition();
		CString szArg, szArgType;
		while(posArg)
		{
			szArg = m_szlArgument.GetNext(posArg);
			szArgType = m_szlArgumentType.GetNext(posArgType);
			CString szTmp = s;
			CString stmp = szArgType + CString("  ") + szArg;
			while(szTmp.Replace(_T("$(Argument+Type)"), stmp) != 0);
			m_szlComments.AddTail( szTmp + "\n");
		}
	}
	else
		m_szlComments.AddTail( s + "\n");

}

BOOL CCommentData::GetInfoFromRcFile(CString rc)
{
	if (!Open(rc, CFile::modeRead | CFile::typeText))
	{
		AfxMessageBox("Can not open the Resource file: " + rc);
		return TRUE;
	}
	
	CString s;
	while(ReadString(s))
	{
		s.TrimLeft();
		if ( s.Find( "VS_VERSION_INFO" ) == 0 && s.Find( "VERSIONINFO" ) > 0 )
			break;
	}

	while(ReadString(s))
	{
		s.TrimLeft();
		if ( s.Find( "END" ) >= 0)
			break;
		
		GetStringFileInfo(m_szCompanyName,	_T("CompanyName"),		s);
		GetStringFileInfo(m_szTradeMark,	_T("ProductName"),		s);
		GetStringFileInfo(m_szProductName,	_T("LegalTrademarks"),	s);
		GetStringFileInfo(m_szComments,		_T("Comments"),			s);
		GetStringFileInfo(m_szVersion,		_T("ProductVersion"),	s);
	}
	
	Close();
	return TRUE;
}

VOID CCommentData::GetStringFileInfo(CString &sDec, CString sSearch, CString s)
{
	if ( s.Find(sSearch) > 0 && s.Find(_T("VALUE") > 0) )
	{
		int i = s.GetLength() - s.Find(',');
		s = s.Right(i);
		int iStart = s.Find('"') + 1;
		int iCount = s.ReverseFind('"') - iStart;
		sDec = s.Mid(iStart, iCount);
		sDec.Replace( _T("\\0"),  _T("") );
	}
}


//获得函数信息
BOOL CCommentData::GetMethodInfo(IApplication* pApp, CString type)
{
	CString szInfo;		//函数的行
	type.MakeLower();
	if (type != _T("cppmethod") )
		return TRUE;

	IGenericDocument* pDoc = NULL;
	pApp->get_ActiveDocument((IDispatch**)&pDoc);		
	if (!pDoc)
		return FALSE;
	
	ITextSelection* pSel = NULL;
	((ITextDocument*)pDoc)->get_Selection((IDispatch**)&pSel);
	if (!pSel)
	{
		pDoc->Release();
		return FALSE;
	}
	
	CComBSTR bStr;
	CString	szStr;
	long	nowLine, line, endpos = -1;
	
	pSel->get_CurrentLine(&nowLine);
	line = nowLine;
	CComVariant varSelMode = dsMove;
	while(endpos < 0)
	{
		pSel->SelectLine();
		pSel->get_Text(&bStr);
		szStr = bStr;
		endpos = szStr.FindOneOf("{");

		if (endpos >= 0)
			szStr = szStr.Left(endpos);
		
		szInfo += szStr;
		
		while (szInfo.Replace(0x0d, ' ') != 0);		// '\n'
		while (szInfo.Replace(0x0a, ' ') != 0);		// '\n'
		while (szInfo.Replace(0x09, ' ') != 0);		// '\t'
		while (szInfo.Replace("  ", " ") != 0);		// "  " to ' '
		while (szInfo.Replace("::  ", "::") != 0);		// "  " to ' '
		while (szInfo.Replace(" ::", "::") != 0);		// "  " to ' '

		pSel->GoToLine(++line, varSelMode);	
	}
	
	pSel->GoToLine(nowLine, varSelMode);		
	pSel->Release();
	pDoc->Release();

	m_szFunPrototype = szInfo;
	// 1st from ::
 	m_szMethodName = szInfo.Left(szInfo.Find("("));
	szInfo = szInfo.Right(szInfo.GetLength() - m_szMethodName.GetLength());
	
	// get ReturnType
	m_szMethodName.TrimLeft();
	m_szMethodName.TrimRight();
	int pos = m_szMethodName.ReverseFind(' ');
	if (pos > 0)
	{
		m_szReturnType = m_szMethodName.Left(pos);
		m_szMethodName = m_szMethodName.Right(m_szMethodName.GetLength() - pos);
		m_szMethodName.TrimLeft();
	}
	
	// get ClassName and MethodName
	pos = m_szMethodName.Find("::");
	if( pos > 0)
	{
		m_szClassName = m_szMethodName.Left(pos);
		m_szMethodName = m_szMethodName.Right(m_szMethodName.GetLength() - pos - 2);
	}
	

	// replace comments like "/* */" of argument section
	while (szInfo.Find("/*") > 0)
	{
		CString szLeft = szInfo.Left(szInfo.Find("/*"));
		CString szRight = szInfo.Right(szInfo.GetLength() - szLeft.GetLength() - 2);
		szRight = szInfo.Right(szRight.GetLength() - szRight.Find("*/") - 2);
		szInfo = szLeft + szRight;
	}

	//get Arguments section
	szInfo = szInfo.Left(szInfo.Find(')'));
	szInfo.Replace('(', ' ');
	szInfo.TrimLeft();
	szInfo.TrimRight();
	
	//no arguments
	m_szlArgument.RemoveAll();
	m_szlArgumentType.RemoveAll();
	if (szInfo.IsEmpty())		
		return TRUE;
	
	// for get the last argument
	szInfo += _T(",");
		
	//get each argument
	CString arg, argType;
	while (szInfo.Find(',') > 0)
	{
		argType = szInfo.Left(szInfo.Find(','));
		szInfo = szInfo.Right(szInfo.GetLength() - argType.GetLength() - 1);

		argType.TrimLeft();
		argType.TrimRight();

		arg = argType.Right(argType.GetLength() - argType.ReverseFind(' '));
		argType = argType.Left(argType.GetLength() - arg.GetLength());
		
		szInfo.TrimLeft();
		szInfo.TrimRight();

		arg.TrimLeft();
		arg.TrimRight();
		argType.TrimLeft();
		argType.TrimRight();

		if ( (arg.operator [](0) == '&') || (arg.operator [](0) == '*') )
		{
			argType += arg.operator [](0);
			arg = arg.Right(arg.GetLength() - 1);
		}

		if (!arg.IsEmpty())
		{
			m_szlArgument.AddTail(arg);
			m_szlArgumentType.AddTail(argType);
		}
	}
	
	return TRUE;
}

#include "DlgCmtFun.h"
#include "DlgCmtHis.h"
#include "DlgCmtNor.h"
#include "TimeWinAutoSave.h"
extern CTimeWinAutoSave* gTimeWin;

BOOL CCommentData::Especial(CString ctype)
{
	BOOL bRet = TRUE;
	int nSwitch = -1;
	if (ctype == _T("cppMethod"))
		nSwitch = 0;
	else if (ctype == _T("cRevisionHistory")
		|| ctype == _T("cppHeaderFile")
		|| ctype == _T("commentSameLine") )	
		nSwitch = 1;
	else if (ctype == _T("commentSX")
		|| ctype == _T("commentSMore") )
		nSwitch = 2;

	if (gTimeWin->m_bByDialog)
	{
		switch (nSwitch)
		{
		case 0:	//cppMethod
			{
				CDlgCmtFun dlg;
				if (dlg.DoModal() == IDOK)
				{
					ReplaceMacro("$(Desp)", dlg.m_szDesp);
					ReplaceMacro("$(Detail)", dlg.m_szDetail);
					ReplaceMacro("$(Return)", dlg.m_szReturn);
				}
				else
					bRet = FALSE;
			}
			break;
		case 1:
			{
				CDlgCmtHis dlg;
				if (dlg.DoModal() == IDOK)
					ReplaceMacro("$(Desp)", dlg.m_szDesp);
				else
					bRet = FALSE;
			}
			break;
		case 2:
			{
				CDlgCmtNor dlg;
				if (dlg.DoModal() == IDOK)
				{
					ReplaceMacro("$(Desp)", dlg.m_szDesp);
					ReplaceMacro("$(Detail)", dlg.m_szDetail);
				}
				else
					bRet = FALSE;
			}
			break;
		default:
			break;
		}
	}

	ReplaceMacro("\r\n", "$#!#$");
	ReplaceMacro("$#!#$", "\r\n *    ");
	return bRet;
}

/**
 *  Replace s with d in comment.
 *  Replace all s with d in list comment.
 *
 *  @param  -[in]  CString  s <comment>
 *  @param  -[in]  CString  d <comment>
 *
 *  @version  11/17/2002  cuiyan  Initial Version.
 *  @version  11/17/2002  cuiyan  cuiyan  modify for new usage.
 */
void CCommentData::ReplaceMacro(CString s, CString d)
{
	POSITION pos = m_szlComments.GetHeadPosition();
	while(pos)
	{
		CString &szTmp = m_szlComments.GetNext(pos);
		if (szTmp.Find(s) > 0)
		{
			if (d.IsEmpty())
			{
				POSITION curPos = pos;	// now it is next
				m_szlComments.GetPrev(curPos); // now it is cur
				m_szlComments.RemoveAt(curPos);
			}
			else
				while(szTmp.Replace(s, d) != 0);
		}
	}
}
