// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "OraSQL.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_FILE_RUN, OnFileRun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_pInView = NULL;
	m_pOutView= NULL;
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// CG: The following block was added by the Splitter Bar component.
	if (!m_wndSplitter.CreateStatic(this, 2, 1))
	{
		TRACE0("Failed to create splitter bar ");
		return FALSE;    // failed to create
	}

	CRect rt;
	GetClientRect(rt);

	if(!m_wndSplitter.CreateView(0, 0, pContext->m_pNewViewClass,
		CSize(0, rt.Height() / 4), pContext))
	{
		TRACE0("Failed to create CDiagramView ");
		return FALSE;    // failed to create
	}
	
	if(!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(COraOutView), 
		CSize(0, 0), pContext))
	{
		TRACE0("Failed to create CDiagramView ");
		return FALSE;    // failed to create
	}
	
	m_pInView  = (COraInView*) m_wndSplitter.GetPane(0, 0);
	m_pOutView = (COraOutView*)m_wndSplitter.GetPane(1, 0);

	return TRUE;
}

void CMainFrame::OnFileRun() 
{
	CString csCommand;
	CEdit &Ctrl = m_pInView->GetEditCtrl();
	
	Ctrl.GetWindowText( csCommand );
	HRESULT hr = RunCommand( csCommand );
	//if ( SUCCEEDED(hr) )
	//	Ctrl.SetWindowText( "" );
	Ctrl.SetFocus();	
}

//##ModelId=3EE85AFE0222
HRESULT CMainFrame::RunCommand( CString csCommandLine ) 
{
	// Array of commands
	// This makes it very easy to add commands with required arguments and defaults
	// Arguments are comma delimited, use the last argument to receive values with commas
	CStringArray arOut;
	static const char* szaCommandDefns[] =
	{
		// Database commands
		"db.connect connectstring=/#user/password@host",
		"db.disconnect",
		"db.exec sql#explicit execute",
		"db.select sql#select a set of records",
			
		// Miscellaneous commands
		"misc.about",
		"misc.? command=*",
		"misc.help#instructions for using Osql",
		"misc.clear",
		"misc.max max=1#maximize dialog, specify 0 to restore",
			
		// Terminator
		""
	};
	
	// Parse command line
	m_cmd.ParseCommandLine( csCommandLine, szaCommandDefns );
	CString csCommand = m_cmd.GetCommand();
	CString csTmp = "COMMAND: ";
	csTmp += m_cmd.GetCommandLine();
	arOut.Add( csTmp );
	CString csService = m_cmd.GetService();
	CStringArray& csaArgs = *m_cmd.GetArgs();
	
	// Check command
	if ( csCommand.IsEmpty() )
	{
		// Command not recognized, pretend it was exec
		csCommand = "exec";
		csaArgs.Add( csCommandLine );
		csService = "db";
	}
	else if ( ! m_cmd.GetSyntaxError().IsEmpty() )
	{
		// Syntax error
		arOut.Add( m_cmd.GetSyntaxError() );
		csCommand.Empty();
	}
	
	// Prepare to do command
	CWaitCursor wait;
	HRESULT hr = 0;
	
	// Non-db commands
	if ( csCommand == "?" )
	{
		// Output help directly to the control
		// If csCommand is *, show help on all commands in aCommandDefns
		BOOL bAll = csaArgs[0] == "*";
		int iCmd = 0;
		CString csServiceHeading;
		for ( iCmd = 0; szaCommandDefns[iCmd][0]; ++iCmd )
		{
			CSQLCmd::ParsedCommand parsed;
			CSQLCmd::ParseCommandDefn( szaCommandDefns[iCmd], &parsed );
			if ( bAll || csCommand == parsed.csCommand || csCommand == parsed.csService )
			{
				// Service heading if needed
				if ( parsed.csService != csServiceHeading )
				{
					csServiceHeading = parsed.csService;
					CString csServiceTitle;
					csServiceTitle.Format( "%s commands\n", csServiceHeading );
					arOut.Add( csServiceTitle );
				}
				
				// Line containing syntax and description
				CString csLine,csDescription;
				if ( ! parsed.csDescription.IsEmpty() )
					csDescription.Format( " (%s)", parsed.csDescription );
				csLine.Format( "%s %s%s", parsed.csCommand, parsed.csArgDefns, csDescription );
				arOut.Add( csLine );
			}
		}
		Output(arOut);
		return 0;
	}
	else if ( csCommand == "max" )
	{
		if ( atoi(csaArgs[0]) )
			ShowWindow( SW_MAXIMIZE );
		else
			ShowWindow( SW_RESTORE );
	}
	else if ( csCommand == "about" )
		About();
	else if ( csCommand == "help" )
		Help();
	else if ( csCommand == "clear" )
	{
		CListCtrl& Ctrl = m_pOutView->GetListCtrl();
		while (Ctrl.DeleteItem(0));
	}
	// Database
	else if ( csCommand == "connect" )
	{
		m_db.StartLog();
		hr = m_db.Open( csaArgs[0] );
		arOut.Add( m_db.GetLog() );
	}
	else if ( csCommand == "disconnect" )
		hr = m_db.Close();
	else if ( csCommand == "exec" )
		hr = m_db.Exec( csaArgs[0] );
	else if ( csCommand == "select" )
	{
		// Set SQL in recordset and run it
		CString csSelect( csaArgs[0] );
		if ( csSelect.GetLength() < 7 || csSelect.Left(7) != "select " )
			csSelect = "select " + csSelect;
		hr = m_db.Select( csSelect );
		arOut.Add( m_db.GetTitles() );
		// Loop through results
		while ( SUCCEEDED(hr) && ! m_db.IsEOS() )
		{
			//arOut.Add( m_db.GetResults() );
			CString s = m_db.GetRows(); 
			arOut.Add( m_db.GetRows() );
			m_db.FetchNext();
			hr = 0;
		}
	}
	
	if ( csService == "db" )
		arOut.Add( m_db.GetErrorDescription() );

	Output(arOut);
	return hr;
}

//##ModelId=3EE85AFE01A5
void CMainFrame::About()
{
	LPCSTR szAbout[] = {
		"OraSQL 1.1.0 is a command line graphical user interface that helps you use PL/SQL to access Oracle",
		"databases. The source code features Ben Bryant's COdb class which is a simple C++ wrapper for the",
		"Oracle Call Interface (OCI). ",
		" ",
		"Copyright (C) 2003 Edson Cy edson@eyou.com",
		"Thanks for Ben Bryant bcbryant@firstobject.com",
		NULL
	};
	
	Output(szAbout);
}

//##ModelId=3EE85AFE0186
void CMainFrame::Help()
{
	LPCSTR szHelp[] = {
		"You can immediately connect to an Oracle database, select from",
		"tables and execute SQL statements, much as you would in SQL*Plus ",
		"without the semi-colons. As in SQL*Plus, there are also some non-SQL ",
		"commands. Type a question mark to see a list of the commands available ",
		"in OraSQL. Each command is listed with its named arguments and defaults ",
		"if any. Only use semi-colons where they are required in PL/SQL blocks. "
		"If you enter something that does not start with any of these OraSQL ",
		"commands, OraSQL tries to execute it as an SQL statement.",
		" ",
		"The interface for re-using and modifying chunks of commands and pl/sql ",
		"blocks is handy. If you right click in the output area you can copy text ",
		"to the command entry box or immediately run it. The command entry box ",
		"resizes to fit multiple lines of text when you paste in a large pl/sql ",
		"block or use ctrl-enter to start a new line. The escape key exits the ",
		"program (closing the session if open). The first command you will need ",
		"is the connect command. It works like SQL*Plus 8.0 and uses your Net80 ",
		"configuration to connect to the Oracle database. No host name is ",
		"necessary if the database is on the same machine.",
		" ",
		"connect scott/tiger@host",
		"One of the differences from SQL*Plus is that semi-colons are not allowed ",
		"except after anonymous blocks. This corresponds to what the OCI expects ",
		"in an Execute statement. If you have the necessary permissions, you can ",
		"try copying and pasting the following commands into OraSQL, one create ",
		"command at a time:",
		" ",
		"create table table1 (n NUMBER(22), d date, c VARCHAR2(80) )",
		"create sequence sequence1",
		"create or replace package package1 is",
		"function add_entry (c in VARCHAR2 ) return NUMBER;",
		"end package1;"
		" ",
		"create or replace package body package1 is",
		"  function add_entry (c in VARCHAR2 ) return NUMBER is",
		"  n NUMBER(22);",
		"  begin",
		"    select sequence1.nextval into n from dual;",
		"    insert into table1 values ( n, sysdate, c );",
		"    return n;",
		"  end add_entry;",
		"end package1;",
		" ",
		"After you have created these objects, you can try them out using the ",
		"following commands:",
		" declare n number(22); begin n := package1.add_entry( 'something' ); end;",
		" select * from table1",
		"Have Fun!!!",
		NULL
	};
	
	Output(szHelp);
}

void CMainFrame::Output( LPCTSTR csOut[] )
{
	CListCtrl& Ctrl = m_pOutView->GetListCtrl();

	for (int nLines = 0;  csOut[nLines] != NULL; nLines++);
	LPCSTR szLine = 
"-----------------------------------------------------------------------------------------------------";
	Ctrl.InsertItem(0, szLine);
	Ctrl.InsertItem(0, "");
	for (int i = nLines - 1; i >= 0; i--)
		Ctrl.InsertItem(0, csOut[i]);
}

void CMainFrame::Output(CStringArray &arOut)
{
	CListCtrl& Ctrl = m_pOutView->GetListCtrl();
	LPCSTR szLine = 
"-----------------------------------------------------------------------------------------------------";
	Ctrl.InsertItem(0, szLine);
	Ctrl.InsertItem(0, "");
	CString csLine, csFull;
	for (int i = arOut.GetSize() - 1; i >= 0; i--)
	{
		csFull = arOut[i];
		if (csFull.CompareNoCase("NO_DATA") == 0)
			continue;
		
		int	i = csFull.Find('\n');
		while (i > 0)
		{
			csLine = csFull.Left(i + 1);
			csFull.Replace(csLine, "");
			csLine.TrimRight('\n');
			Ctrl.InsertItem(0, csLine);
			i = csFull.Find('\n');
		}
		
		Ctrl.InsertItem(0, csFull);
	}
	
}
