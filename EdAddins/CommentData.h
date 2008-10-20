// CommentData.h: interface for the CCommentData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMENTDATA_H__FE550379_D7F9_4942_B1F3_452AE251700D__INCLUDED_)
#define AFX_COMMENTDATA_H__FE550379_D7F9_4942_B1F3_452AE251700D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 *  comment gen class. 
 *  to gen comment for all types.
 */
class CCommentData : public CStdioFile  
{
public:
	BOOL GetComments(IApplication* pApp, CString type);
	CCommentData();
	CStringList m_szlComments;

	//get from open documents now
	CString m_strPrivate;
	CString m_strStatic;
	CString m_strLanguage;

	CString m_szCmtFileName;
	CString m_szPrjFileName;
	CString m_szPrjDocPath;
	CString m_szPrjPath;
	
	BOOL	m_bOpen;
protected:
	void ReplaceMacro(CString s, CString d);
	BOOL Especial(CString ctype);
	CString m_szFunPrototype;
	BOOL GetMethodInfo(IApplication* pApp, CString type);
	VOID GetStringFileInfo(CString& sDec, CString sSearch, CString s);
	BOOL GetInfoFromRcFile(CString rc);
	BOOL GetInfoFromOpenPrj(IApplication *pApp);
	VOID ReplaceMacro(CString &s);
	BOOL GetCommentFromFile(CString type);
	
	//get from regtable
	CString m_szUserName;
	
	CString m_szDocFileName;

	//get from resource file
	CString m_szCompanyName;
	CString m_szTradeMark;		//system name
	CString m_szProductName;	//subsystem name
	CString m_szComments;
	CString m_szVersion;

	//get from system
	CString m_sz_mmddyyyy;
	CString m_sz_ddmmyyyy;
	CString m_szMonth;
	CString m_szDay;
	CString m_szYear;

	//get from Method line
	CString m_szAppPath;
	CString m_szClassName;
	CString m_szMethodName;
	CString m_szReturnType;
	CStringList m_szlArgument;
	CStringList m_szlArgumentType;
};

#endif // !defined(AFX_COMMENTDATA_H__FE550379_D7F9_4942_B1F3_452AE251700D__INCLUDED_)
