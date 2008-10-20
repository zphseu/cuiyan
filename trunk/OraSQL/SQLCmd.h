// SQLCmd.h: interface for the CSQLCmd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLCMD_H__78B402EF_7F5A_4600_929C_B674C1B4E77D__INCLUDED_)
#define AFX_SQLCMD_H__78B402EF_7F5A_4600_929C_B674C1B4E77D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSQLCmd  
{
public:
	CSQLCmd();
	virtual ~CSQLCmd();
	CString GetCommand()	{ return m_parsedcommand.csCommand; };
	CString GetService()	{ return m_parsedcommand.csService; };
	CString GetCommandLine(){ return m_csProcessedCommandLine; };
	CStringArray* GetArgs() { return &m_csaArgs; };
	CString GetSyntaxError(){ return m_csSyntaxError; };
	
	void ParseCommandLine( LPCTSTR szCommand, const char* szaCommandDefns[] );	
	static CString GetTimeDate();

	friend class CMainFrame;
	
protected:
	CString m_csProcessedCommandLine;
	CStringArray m_csaArgs;
	CString m_csSyntaxError;
	struct ParsedCommand
	{
		CString csService;
		CString csCommand;
		CString csArgDefns;
		CString csDescription;
	} m_parsedcommand;

	static void ParseCommandDefn( CString csDefn, ParsedCommand* pCmd );
};

#endif // !defined(AFX_SQLCMD_H__78B402EF_7F5A_4600_929C_B674C1B4E77D__INCLUDED_)
