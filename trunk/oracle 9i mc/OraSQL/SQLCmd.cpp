// SQLCmd.cpp: implementation of the CSQLCmd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OraSQL.h"
#include "SQLCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSQLCmd::CSQLCmd()
{

}

CSQLCmd::~CSQLCmd()
{

}


void CSQLCmd::ParseCommandDefn( CString csDefn, CSQLCmd::ParsedCommand* pCmd )
{
	// Is there a description?
	int nPoundOffset = csDefn.Find("#");
	if ( nPoundOffset >= 0 )
	{
		pCmd->csDescription = csDefn.Mid(nPoundOffset+1);
		csDefn = csDefn.Left(nPoundOffset);
	}

	// Separate service, command and args
	int nCommandOffset = csDefn.Find(".") + 1;
	int nArgsOffset = csDefn.Find(" ") + 1;
	if ( nCommandOffset == 0 || nCommandOffset == csDefn.GetLength() )
	{
		pCmd->csCommand = csDefn;
		return;
	}
	pCmd->csService = csDefn.Left( nCommandOffset - 1 );

	// Are there any arguments
	if ( nArgsOffset == 0 )
	{
		// No arguments
		pCmd->csCommand = csDefn.Mid( nCommandOffset );
	}
	else
	{
		// Has arguments
		pCmd->csArgDefns = csDefn.Mid( nArgsOffset );
		pCmd->csCommand = csDefn.Mid( nCommandOffset, nArgsOffset - nCommandOffset - 1 );
	}
}


void CSQLCmd::ParseCommandLine( LPCTSTR szCommand, const char* szaCommandDefns[] )
{
	//
	// Parse command according to command definitions
	// If it starts with a valid command, set csCommand
	// If the arguments do not fit the command's definition, set m_csSyntaxError
	// If there are arguments, fill m_csaArgs
	// Apply default arguments and set m_csProcessedCommandLine
	// If the command was not found, leave entire line in m_csProcessedCommandLine
	//
	m_parsedcommand = ParsedCommand(); // empty ParsedCommand member
	m_parsedcommand.csCommand = szCommand;
	m_parsedcommand.csCommand.TrimLeft();
	m_parsedcommand.csCommand.TrimRight();
	m_csSyntaxError.Empty();
	m_csaArgs.RemoveAll();

	// Separate command from operand
	CString csOperand;
	int iSpace = m_parsedcommand.csCommand.Find( " " );
	if ( iSpace > -1 && iSpace + 1 < m_parsedcommand.csCommand.GetLength() )
	{
		csOperand = m_parsedcommand.csCommand.Mid( iSpace + 1 );
		m_parsedcommand.csCommand = m_parsedcommand.csCommand.Left( iSpace );
		m_parsedcommand.csCommand.MakeLower();
	}

	// Look for command definition in array, set m_parsedcommand.csService etc
	int iCmd = 0;
	while ( szaCommandDefns[iCmd][0] )
	{
		ParsedCommand parsed;
		ParseCommandDefn( szaCommandDefns[iCmd], &parsed );
		if ( m_parsedcommand.csCommand == parsed.csCommand )
		{
			m_parsedcommand = parsed;
			break;
		}
		++iCmd;
	}

	// Command not found?
	if ( m_parsedcommand.csService.IsEmpty() )
	{
		m_csSyntaxError = "unknown command";
		m_csProcessedCommandLine = szCommand;
		m_parsedcommand.csCommand.Empty();
	}
	else
		m_csProcessedCommandLine = m_parsedcommand.csCommand;

	// Parse argument definitions plus user's arguments into m_csaArgs
	// Build m_csProcessedCommandLine
	CString csRemainingDefns = m_parsedcommand.csArgDefns;
	BOOL bEndOfDefns = FALSE;
	while ( ! m_parsedcommand.csService.IsEmpty() && ! bEndOfDefns )
	{
		// Get argument definition
		CString csDefn;
		int iComma = csRemainingDefns.Find( ',' );
		if ( iComma > -1 )
		{
			// take up to comma
			csDefn = csRemainingDefns.Left( iComma );
			csRemainingDefns = csRemainingDefns.Mid( iComma + 1 );
		}
		else
		{
			// last argument definition
			csDefn = csRemainingDefns;
			csRemainingDefns.Empty();
			bEndOfDefns = TRUE;
		}

		// Are there are no arguments in command?
		if ( csDefn.IsEmpty() )
		{
			// csOperand must be empty
			if ( ! csOperand.IsEmpty() )
			{
				m_csSyntaxError = "syntax: no arguments";
				m_parsedcommand.csService.Empty();
			}

			// Do not create any items in csaArgs[]
			break;
		}

		// Get user's argument
		CString csArg;
		iComma = csOperand.Find( ',' );
		if ( iComma > -1 && ! bEndOfDefns )
		{
			// take up to comma
			csArg = csOperand.Left( iComma );
			csOperand = csOperand.Mid( iComma + 1 );
		}
		else
		{
			// last argument
			csArg = csOperand;
			csOperand.Empty();
		}

		// Get argument default
		// Argument is required unless default is provided
		// For empty argument default in defn just specify =
		// empty user value for arg is not accepted unless default is empty
		CString csDefault;
		BOOL bRequired = TRUE;
		int iEqual = csDefn.Find('=');
		if ( iEqual > -1 )
		{
			csDefault = csDefn.Mid( iEqual + 1 );
			bRequired = FALSE;
		}

		// Make sure there is a value if required
		csArg.TrimLeft();
		csArg.TrimRight();
		if ( csArg.IsEmpty() && bRequired )
		{
			m_csSyntaxError.Format( "syntax: %s %s", m_parsedcommand.csCommand, m_parsedcommand.csArgDefns );
			m_parsedcommand.csService.Empty();
			break;
		}

		// Use default arg if none supplied by user
		if ( csArg.IsEmpty() )
			csArg = csDefault;

		// Add to arg array
		m_csaArgs.Add( csArg );

		// Add to parsed command string
		if ( m_csaArgs.GetSize() == 1 )
			m_csProcessedCommandLine += " ";
		else
			m_csProcessedCommandLine += ",";
		m_csProcessedCommandLine += csArg;
	}
}


CString CSQLCmd::GetTimeDate()
{
	SYSTEMTIME systemtime;
	GetLocalTime( &systemtime );
	CString csTimeDate;
	csTimeDate.Format( "%02d:%02d:%02d %s",
		systemtime.wHour,
		systemtime.wMinute,
		systemtime.wSecond,
		// systemtime.wMilliseconds,
		CTime::GetCurrentTime().Format("%b %d")
		);
	return csTimeDate;
}
