// Odb.cpp
//
// Release 1, Copyright (C) 1999 Ben Bryant
// This is sample source code, nothing more is implied. Use it only as such.
// This software is provided 'as-is', without warranty. In no event will the
// author be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose.
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software. Altered source versions must be plainly
// marked as such, and must not be misrepresented as being the original software.
// Ben Bryant bcbryant@firstobject.com

#include "stdafx.h"
#include "Odb.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////
// Oracle Call Interface (OCI) Wrapper
//
#ifdef __STDC__
#include <oci.h>
#else
#define __STDC__ 1
#include <oci.h>
#undef __STDC__
#endif

//////////////////////////////////////////////////////////////////////
// COdb::OdbField
//////////////////////////////////////////////////////////////////////
#include <io.h>

//##ModelId=3EE85054032C
struct COdb::OdbField
{
	//
	// This structure maintains an OCI field/column/variable
	//
		//##ModelId=3EE85054033D
	CString csName;
		//##ModelId=3EE85054034C
	dvoid* pBuffer;
		//##ModelId=3EE850540351
	ub2 wType;
		//##ModelId=3EE85054035C
	ub2 wSize;
		//##ModelId=3EE85054036C
	ub2 wLen;
		//##ModelId=3EE85054037B
	sb2 nInd;
		//##ModelId=3EE85054038A
	BOOL bQuotedOnUpdate;

	// Methods
		//##ModelId=3EE850540399
	OdbField();
		//##ModelId=3EE8505403A9
	~OdbField();
		//##ModelId=3EE8505403AA
	void SetSize( ub2 w );
		//##ModelId=3EE8505403BA
	void Set( CString cs );
		//##ModelId=3EE8505403D8
	CString Get() const;
		//##ModelId=3EE8505403DA
	void Free();
};

//##ModelId=3EE850540399
COdb::OdbField::OdbField()
{
	pBuffer = NULL;
	wType = SQLT_STR;
	wSize = 0;
	wLen = 0;
	nInd = 0;
	bQuotedOnUpdate = TRUE;
}

//##ModelId=3EE8505403A9
COdb::OdbField::~OdbField()
{
	Free();
}

//##ModelId=3EE8505403AA
void COdb::OdbField::SetSize( ub2 w )
{
	//
	// Make sure buffer is at least size w
	//
	if ( w > wSize || ! pBuffer )
	{
		Free();
		pBuffer = (dvoid*) new char[w];
		wSize = w;
	}
}

//##ModelId=3EE8505403BA
void COdb::OdbField::Set( CString cs )
{
	//
	// Set buffer to hold CString
	//
	wLen = cs.GetLength() + 1;
	SetSize( wLen );
	strcpy( (char*)pBuffer, cs );
}

//##ModelId=3EE8505403D8
CString COdb::OdbField::Get() const
{
	//
	// All fields are converted to strings by the OCI
	// because SQLT_STR and SQLT_LNG are specified when binding fields
	// Copy from buffer into a string
	//
	CString csResult;
	csResult.Format("%.*s", wLen, (const char*)pBuffer);
	csResult.TrimRight();
	return csResult;
}

//##ModelId=3EE8505403DA
void COdb::OdbField::Free()
{
	//
	// Free field's allocated buffer
	//
	if ( pBuffer )
	{
		delete pBuffer;
		pBuffer = NULL;
	}
}

//////////////////////////////////////////////////////////////////////
// COdb::OdbRecordSet
//////////////////////////////////////////////////////////////////////

//##ModelId=3EE85055000F
struct COdb::OdbRecordSet
{
	//
	// This structure maintains a recordset
	// A recordset holds a row of select results
	//
		//##ModelId=3EE850550020
	CPtrArray paFields;
		//##ModelId=3EE85055002E
	int m_nRows;
		//##ModelId=3EE85055002F
	CString m_csStatement;

	// Methods
		//##ModelId=3EE85055003E
	OdbRecordSet();
		//##ModelId=3EE85055003F
	~OdbRecordSet();
		//##ModelId=3EE85055004E
	int Find( const CString& csName );
		//##ModelId=3EE85055005D
	void RemoveAll();
};

//##ModelId=3EE85055003E
COdb::OdbRecordSet::OdbRecordSet()
{
}

//##ModelId=3EE85055003F
COdb::OdbRecordSet::~OdbRecordSet()
{
	RemoveAll();
}

//##ModelId=3EE85055005D
void COdb::OdbRecordSet::RemoveAll()
{
	//
	// Remove fields
	//
	for ( int iField=0; iField<paFields.GetSize(); ++iField )
		delete (OdbField*)paFields[iField];
	paFields.RemoveAll();
}

//##ModelId=3EE85055004E
int COdb::OdbRecordSet::Find( const CString& csName )
{
	//
	// Return iField or -1 if name not found
	//
	for ( int iField=0; iField<paFields.GetSize(); ++iField )
	{
		OdbField* pField = (OdbField*)paFields.GetAt( iField );
		if ( pField->csName == csName )
			return iField;
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////
// OdbContext
//////////////////////////////////////////////////////////////////////

//##ModelId=3EE85055006D
struct COdb::OdbContext
{
	//
	// This structure maintains all of the OCI variables
	// It is declared here rather than in the header
	// to isolate OCI from COdb clients
	//
		//##ModelId=3EE85055007E
	OdbContext();
		//##ModelId=3EE85055008C
	void Clear();
		//##ModelId=3EE85055008D
	char szError[512];
		//##ModelId=3EE85055009C
	HRESULT hr;
		//##ModelId=3EE8505500AC
	OCIEnv* hpEnv;
		//##ModelId=3EE8505500B1
	OCIServer* hpServer;
		//##ModelId=3EE8505500BE
	OCIError* hpErr;
		//##ModelId=3EE8505500CC
	OCISvcCtx* hpContext;
		//##ModelId=3EE8505500DB
	OCIStmt *hpSelect;
		//##ModelId=3EE8505500EB
	OdbRecordSet rsSelect;
};

//##ModelId=3EE85055007E
COdb::OdbContext::OdbContext()
{
	Clear();
}

//##ModelId=3EE85055008C
void COdb::OdbContext::Clear()
{
	hr = OCI_SUCCESS;
	hpEnv = NULL;
	hpErr = NULL;
	hpServer = NULL;
	hpContext = NULL;
	hpSelect = NULL;
	szError[0] = '\0';
}

//////////////////////////////////////////////////////////////////////
// COdb
//////////////////////////////////////////////////////////////////////

//##ModelId=3EE850540272
COdb::COdb()
{
	m_po = new OdbContext;
}

//##ModelId=3EE850540280
COdb::~COdb()
{
	Close();
	delete m_po;
}

//##ModelId=3EE8505402FE
void COdb::CheckErr( short status )
{
	//
	// This sets the OCI error string
	// Later, this might be made to generate an exception
	// The table of codes and strings is kept here in a static array
	//
	static struct CErrorPair
	{
		sword w;
		const char* szText;
	}
		epaErrors[] =
	{
		OCI_SUCCESS, "SUCCESS",
		OCI_SUCCESS_WITH_INFO, "SUCCESS_WITH_INFO",
		OCI_NEED_DATA, "NEED_DATA",
		OCI_NO_DATA, "NO_DATA",
		OCI_INVALID_HANDLE, "INVALID_HANDLE",
		OCI_STILL_EXECUTING, "STILL_EXECUTE",
		OCI_CONTINUE, "CONTINUE",
	};

	// Check status
	m_po->hr = status;
	if ( m_po->hr == OCI_ERROR )
	{
		// for the special case OCI_ERROR, call OCIErrorGet for the string
		sb4 errcode = 0;
	    OCIErrorGet(m_po->hpErr, 1, NULL, &errcode, (unsigned char*)m_po->szError, sizeof(m_po->szError), OCI_HTYPE_ERROR);
	}
	else
	{
		// Look for description in static array
		DWORD nTotalResultCodes = sizeof(epaErrors) / sizeof(CErrorPair);
		for ( int iPos = 0; iPos < sizeof(epaErrors); ++ iPos )
		{
			if ( epaErrors[iPos].w == m_po->hr )
			{
				strcpy( m_po->szError, epaErrors[iPos].szText );
				break;
			}
		}
	}
}

//##ModelId=3EE8505402A1
CString COdb::GetErrorDescription()
{
	return m_po->szError;
}

HRESULT COdb::Open( const CString csConnect )
{
	//
	// This opens a connection with the database
	// Connect string format is user/password@host
	//
	CString csUser, csPassword, csServer;
	int iSlash = csConnect.Find("/");
	if ( iSlash > -1 )
	{
		csUser = csConnect.Left(iSlash);
		csPassword = csConnect.Mid(iSlash + 1);
		int iAt = csConnect.Find("@");
		if ( iAt > iSlash )
		{
			csPassword = csConnect.Mid( iSlash + 1, iAt - iSlash - 1 );
			csServer = csConnect.Mid(iAt + 1);
		}
	}
	else
	{
		csUser = csConnect;
	}
	if ( csUser.IsEmpty() && csPassword.IsEmpty() )
	{
		// For default OS logon, specify slash for user name and password
		csUser = "/";
		csPassword = "/";
	}

	// First, we make sure its closed
	Close();

	// Initialize OCI DLL specifying the mode
	CheckErr( OCIInitialize( OCI_OBJECT, NULL, NULL, NULL, NULL ) );
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	// Note an alternative is to use the OCILogon/Logoff functions
	// Here we allocate all of the handles explicitly
	// Initialize the environment handle
	CheckErr( OCIEnvInit( &m_po->hpEnv, OCI_DEFAULT, 0, NULL ) );
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	// Allocate error, server, and service context handles
	OCIHandleAlloc( m_po->hpEnv, (void**)&m_po->hpErr, OCI_HTYPE_ERROR, 0, NULL );
	OCIHandleAlloc( m_po->hpEnv, (void**)&m_po->hpServer, OCI_HTYPE_SERVER, 0, NULL );
	OCIHandleAlloc( m_po->hpEnv, (void**)&m_po->hpContext, OCI_HTYPE_SVCCTX, 0, NULL );

	// Associate TNS with server handle
	CheckErr( OCIServerAttach( m_po->hpServer,
		m_po->hpErr,
		(unsigned char*)(const char*)csServer,
		csServer.GetLength(),
		0 )
		);
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	// Get server version string
	const nVersionLength = 1024;
	CString csVersion;
	CheckErr( OCIServerVersion( m_po->hpServer,
		m_po->hpErr,
		(text*)csVersion.GetBuffer(nVersionLength),
		nVersionLength,
		OCI_HTYPE_SERVER )
		);
	if ( FAILED(m_po->hr) )
		return m_po->hr;
	csVersion.ReleaseBuffer();
	m_csLog += csVersion + "\n";

	// Specify server handle to service context
	CheckErr( OCIAttrSet( m_po->hpContext,
		OCI_HTYPE_SVCCTX,
		m_po->hpServer,
		0,
		OCI_ATTR_SERVER,
		m_po->hpErr )
		);
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	// Allocate a session handle
	OCISession *hpSession = NULL;
	OCIHandleAlloc( m_po->hpEnv, (void**)&hpSession, OCI_HTYPE_SESSION, 0, NULL);

	// Associate username with session handle
	OCIAttrSet( hpSession,
		OCI_HTYPE_SESSION,
		(void*)(const char*)csUser,
		csUser.GetLength(),
		OCI_ATTR_USERNAME,
		m_po->hpErr
		);

	// Associate password with session handle
	OCIAttrSet( hpSession,
		OCI_HTYPE_SESSION,
		(void*)(const char*)csPassword,
		csPassword.GetLength(),
		OCI_ATTR_PASSWORD,
		m_po->hpErr
		);

	// Open session using service context and session handle
	CheckErr( OCISessionBegin( m_po->hpContext,
		m_po->hpErr,
		hpSession,
		OCI_CRED_RDBMS,
		OCI_DEFAULT )
		);
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	// Specify session handle to service context
	OCIAttrSet( m_po->hpContext,
		OCI_HTYPE_SVCCTX,
		hpSession,
		0,
		OCI_ATTR_SESSION,
		m_po->hpErr
		);

	// Change date format
	if ( SUCCEEDED(m_po->hr) )
	{
		CString csSQL = "alter session set nls_date_format = 'yyyy-mm-dd hh24:mi:ss'";
		m_po->hr = Exec( csSQL );
	}

	return m_po->hr;
}

//##ModelId=3EE850540284
HRESULT COdb::Close()
{
	//
	// This closes and/or cleans up the connection
	// It should work even if the connection is closed or partly open
	//
	m_po->hr = OCI_SUCCESS;

	// Free select statement handle
	if (m_po->hpSelect)
		OCIHandleFree( m_po->hpSelect, OCI_HTYPE_STMT );

	// Detach server from server handle
	if (m_po->hpErr)
		OCIServerDetach( m_po->hpServer, m_po->hpErr, OCI_DEFAULT );

	// Free server handle
	if (m_po->hpServer)
		CheckErr( OCIHandleFree(m_po->hpServer, OCI_HTYPE_SERVER) );

	// Free service context
	if (m_po->hpContext)
		OCIHandleFree( m_po->hpContext, OCI_HTYPE_SVCCTX);

	// Free error handle
	if (m_po->hpErr)
		OCIHandleFree( m_po->hpErr, OCI_HTYPE_ERROR );

	// Free enviroment handle
	if (m_po->hpEnv)
		CheckErr( OCIHandleFree( m_po->hpEnv, OCI_HTYPE_ENV));
	
	m_po->Clear();
	return m_po->hr;
}

HRESULT COdb::Exec( const CString csStatement )
{
	//
	// Execute statement
	//
	m_csLog += csStatement + "\n";

	// Allocate statement handle
	OCIStmt *hpStatement = NULL;
	CheckErr( OCIHandleAlloc( m_po->hpEnv,
		(void**)&hpStatement,
		OCI_HTYPE_STMT,
		0,
		NULL )
		);

	// Associate statement string with handle
	CString csCleanStatement = csStatement;
	CleanWhitespace( csCleanStatement );
	CheckErr( OCIStmtPrepare( hpStatement,
		m_po->hpErr,
		(text *)csCleanStatement.GetBuffer(0),
		csCleanStatement.GetLength(),
		OCI_NTV_SYNTAX,
		OCI_DEFAULT )
		);

	// Execute statement
	CheckErr( OCIStmtExecute( m_po->hpContext,
		hpStatement,
		m_po->hpErr,
		1, // iters
		0, // row offset
		NULL, NULL, // snapshot in/out
		OCI_DEFAULT )
		);

	// Free statement handle
	if ( hpStatement )
		OCIHandleFree( hpStatement, OCI_HTYPE_STMT );

	return m_po->hr;
}

HRESULT COdb::Select( const CString csStatement )
{
	//
	// Execute select statement and parse the select list description
	// Use member recordset rsSelect
	// See also Get, FetchNext, IsEOS
	//
	m_csLog += csStatement + "\n";

	// Free previous select handle and remove fields
	m_po->rsSelect.m_nRows = 0;
	m_po->rsSelect.RemoveAll();
	if (m_po->hpSelect)
		OCIHandleFree( m_po->hpSelect, OCI_HTYPE_STMT );

	// Allocate statement handle
	CheckErr( OCIHandleAlloc( m_po->hpEnv,
		(void**)&m_po->hpSelect, // ref to statement handle pointer
		OCI_HTYPE_STMT, // type of handle being allocated
		0,
		NULL )
		);

	// Associate statement string with handle
	m_po->rsSelect.m_csStatement = csStatement;
	CleanWhitespace( m_po->rsSelect.m_csStatement );
	CheckErr( OCIStmtPrepare( m_po->hpSelect,
		m_po->hpErr, // error handle pointer
		(text *)m_po->rsSelect.m_csStatement.GetBuffer(0), // statement string
		m_po->rsSelect.m_csStatement.GetLength(),
		OCI_NTV_SYNTAX, // specify native syntax
		OCI_DEFAULT )
		);

	// Execute but don't fetch yet
	CheckErr( OCIStmtExecute( m_po->hpContext,
		m_po->hpSelect, // prepared by previous function calls
		m_po->hpErr,
		0, // 'iters' i.e. max rows to fetch during this call
		0, 
		NULL, NULL, OCI_DEFAULT )
		);

	// If it returns OCI_NO_DATA then no need to define recordset
	if ( m_po->hr == OCI_NO_DATA || FAILED(m_po->hr) )
	{
		return m_po->hr;
	}

	// Load the types into recordset
	int nColumnCount = 0;
	CStringArray arName, arData;
	CStringArray arFieldName;
	
	while ( m_po->hr == OCI_SUCCESS )
	{
		// Get pointer to column
		void* pFieldAttr = NULL;
		HRESULT hrGetNext;
		hrGetNext = OCIParamGet( m_po->hpSelect, OCI_HTYPE_STMT,
			m_po->hpErr,
			&pFieldAttr,
			nColumnCount+1 // position
			);
		if ( hrGetNext != OCI_SUCCESS )
			break;

		// Increment column count and allocate an OdbField structure
		++nColumnCount;
		OdbField* pField = new OdbField;
		m_po->rsSelect.paFields.Add( pField );

		// Get data type
		CheckErr( OCIAttrGet( pFieldAttr, OCI_DTYPE_PARAM,
			&pField->wType,
			0,
			OCI_ATTR_DATA_TYPE,
			m_po->hpErr )
			);

		// Get data size
		CheckErr( OCIAttrGet( pFieldAttr, OCI_DTYPE_PARAM,
			&pField->wSize,
			0,
			OCI_ATTR_DATA_SIZE,
			m_po->hpErr )
			);

		// Type conversions
		switch (pField->wType)
		{
		case SQLT_LNG: 
			pField->wSize = 32760; 
			break;
			
		case SQLT_DAT: 
			pField->wType = SQLT_STR;
			pField->wSize = 50;
			break;

		case SQLT_NUM:
			pField->wType = SQLT_STR;
			pField->wSize += 1; // allow for null-terminator
			break;

		default:
			break;
		}

		// Get column name
		text* pName;
		ub4 nNameLen;
		CheckErr( OCIAttrGet( pFieldAttr, OCI_DTYPE_PARAM,
			(void**)&pName,
			&nNameLen,
			OCI_ATTR_NAME,
			m_po->hpErr )
			);

		// Set size and name
		pField->SetSize( pField->wSize );
		pField->csName.Format( "%.*s", nNameLen, pName );
		arFieldName.Add(pField->csName);
		
		switch(pField->wType) {
		case SQLT_BLOB:
			arName.Add(pField->csName);
			arData.Add("'BLOB'");
			break;
		case SQLT_CLOB:
			arName.Add(pField->csName);
			arData.Add("'CLOB'");
			break;
		case SQLT_BFILEE:
			arName.Add(pField->csName);
			arData.Add("'BFILE'");
			break;
		case SQLT_CFILEE:
			arName.Add(pField->csName);
			arData.Add("'CFILE'");
			break;
		default:
			break;
		}			
	}
	
	if (arName.GetSize() > 0)
	{
		CString csSQL = csStatement;
		CString csOldSQL = csStatement;
		csSQL.MakeLower();
		csSQL = csStatement.Left(csSQL.Find("from"));
		
		CString csTmp = csSQL;	
		if (csSQL.Replace(".*", ".X") > 0)
		{
			strcpy(m_po->szError, "这样带有.*并且包含LOB字段的语句。\n    SELECT A.* FROM A\n无法查询形如");
			return OCI_INVALID_HANDLE;
		}
		
		csTmp = csSQL;
		if (csTmp.Replace(" * ", " X "))
		{
			csSQL = " ";
			for (int i = 0; i < arFieldName.GetSize(); i++)
				csSQL += arFieldName[i] + CString(", ");
			csSQL = csSQL.Left(csSQL.GetLength() - 2) + CString(" ");
			
			csOldSQL.Replace(" * ", csSQL);
		}

		csSQL = csOldSQL;
		csSQL.MakeLower();
		CString csFrom = csOldSQL.Right(csSQL.GetLength() - csSQL.Find("from"));
		csSQL = csOldSQL.Left(csOldSQL.GetLength() - csFrom.GetLength());
		for (int i = 0; i < arName.GetSize(); i++)
		{
			csSQL.Replace(arName[i] + CString(' '), arData[i] + " As " + arName[i] + CString(' '));
			csSQL.Replace(arName[i] + CString(','), arData[i] + " As " + arName[i] + CString(','));
		}
		
		return Select(csSQL + csFrom);
	}

	// Bind storage for receiving input variables
	OCIDefine *pDefn; // to hold pointer to field definition
	m_csTitles = _T("");
	int iField;
	for ( iField=0; iField<m_po->rsSelect.paFields.GetSize(); ++iField )
	{
		// Get pointer to field structure
		OdbField* pField = (OdbField*)m_po->rsSelect.paFields[iField];

		// Bind
		pDefn = NULL;
		CheckErr( OCIDefineByPos( m_po->hpSelect,
			&pDefn, // function allocs and gives back a pointer to field definition
			m_po->hpErr,
			iField+1, // position in select starting at 1
			pField->pBuffer, // storage area for field result
			pField->wSize, // sizeof storage area
			pField->wType, // field type
			&pField->nInd, // indp, null indicator
			&pField->wLen, // rlenp
			NULL,
			OCI_DEFAULT )
			);

		m_csTitles += pField->csName;
		m_csTitles += ' ';
	}

	// Fetch
	FetchNext();

	return m_po->hr;
}

//##ModelId=3EE85054029F
HRESULT COdb::FetchNext()
{
	//
	// Fetch next row of select statement and parse the select list description
	//
	CheckErr( OCIStmtFetch( m_po->hpSelect,
		m_po->hpErr,
		1, // 'nrows' i.e. max rows
		OCI_FETCH_NEXT, 
		OCI_DEFAULT )
		);

	// Set result to 0 if no data returned
	m_csResults = "";
	m_csRows = "";
	m_po->rsSelect.m_nRows = 0;
	if ( SUCCEEDED(m_po->hr) && m_po->hr != OCI_NO_DATA )
	{
		// Set number of rows to 1 so IsEOS() will fail
		m_po->rsSelect.m_nRows = 1;

		// TEMPORARY: create a results string
		for ( int iField=0; iField<m_po->rsSelect.paFields.GetSize(); ++iField )
		{
			OdbField* pField = (OdbField*)m_po->rsSelect.paFields[iField];
			if ( ! m_csResults.IsEmpty() )
				m_csResults += ", ";
			m_csResults += pField->csName + "=" + GetField( iField );
			m_csRows += GetField( iField );
			m_csRows += ' ';			
		}
	}

	return m_po->hr;
}

//##ModelId=3EE8505402A0
BOOL COdb::IsEOS()
{
	//
	// Return FALSE if m_nRows is 1, otherwise TRUE
	//
	BOOL bIsEOS = TRUE;
	if ( m_po->rsSelect.m_nRows )
		bIsEOS = FALSE;
	return bIsEOS;
}

//##ModelId=3EE8505402B1
CString COdb::GetField( int iField )
{
	//
	// Return string from indexed field in rsSelect
	//
	if ( iField >= 0 && iField < m_po->rsSelect.paFields.GetSize() )
	{
		OdbField* pField= (OdbField*)m_po->rsSelect.paFields.GetAt( iField );
		return pField->Get();
	}
	return "";
}

//##ModelId=3EE8505402B3
CString COdb::GetField( CString csName )
{
	//
	// Return string from named field in rsSelect
	//
	for ( int iField = 0; iField < m_po->rsSelect.paFields.GetSize(); ++iField )
	{
		OdbField* pField= (OdbField*)m_po->rsSelect.paFields.GetAt( iField );
		if ( pField->csName.CompareNoCase(csName) == 0 )
			return pField->Get();
	}
	return "";
}

//##ModelId=3EE8505402C0
BOOL COdb::GetField( int iField, CString& csName, CString& csValue, BOOL bQuotesIfValueRequires )
{
	//
	// Return TRUE if iField in range, otherwise FALSE if iField is invalid
	// Get name and value, surround value with quotes if flag set
	//
	if ( iField >= 0 && iField < m_po->rsSelect.paFields.GetSize() )
	{
		OdbField* pField= (OdbField*)m_po->rsSelect.paFields.GetAt( iField );
		if ( bQuotesIfValueRequires && pField->bQuotedOnUpdate )
			csValue = "'" + ProcessQuotes(pField->Get()) + "'";
		else
			csValue = pField->Get();
		csName = pField->csName;
		return TRUE;
	}
	return FALSE;
}

//##ModelId=3EE85054030E
void COdb::CleanWhitespace( CString& csStatement )
{
	//
	// Sometimes crlfs can make a statement execute improperly
	// Replace whitespace with spaces because Exec and Select balk at crlfs etc
	//
	char* pStatement = csStatement.GetBuffer(0);
	while ( *pStatement )
	{
		if ( strchr( "\r\n ", *pStatement ) )
			*pStatement = ' ';
		++pStatement;
	}
	csStatement.ReleaseBuffer();
}

//##ModelId=3EE8505402AF
CString COdb::ProcessQuotes( CString csValue )
{
	//
	// If there is any chance the value contains quotes...
	// call this before placing quotes around the value
	//
	LPCTSTR szQuote = "\'";

	// Does the string contain any single quotes?
	if ( csValue.Find( szQuote ) >= 0 )
	{
		// Loop through every occurence of szQuote
		int n = csValue.SpanExcluding(szQuote).GetLength();
		while ( n < csValue.GetLength() )
		{
			// Insert the extra quote
			csValue = csValue.Left(n) + csValue[n] + csValue.Mid(n);

			// Increment n past the two quotes
			// This is where we start the next search from
			n += 2;

			// Note that csValue is now a char longer!
			// Check in case quote was the last char in the string
			if ( n >= csValue.GetLength() )
				break;

			// Increment span count to next quote or end of string
			n += csValue.Mid(n).SpanExcluding(szQuote).GetLength();
		}
	}

	return csValue;
}


#define DATA_SIZE 4096

HRESULT COdb::InsertImage(char *filename, CString Bcode, int tag, CString strDes)
{
	ub4 fsize;
	sword result;
	char *data_in;
	ub4 remainingSize = 0;
	ub4 amtp;
	FILE *input;

	OCIStmt  *p_sql;
	OCILobLocator *blob;
	OCIDefine  *p_Define = (OCIDefine *) 0;

	char Sql[256];

	sprintf(Sql,"INSERT INTO IMAGE(ID, TAG, IMAGE, DES) \
		VALUES(%d, %d, EMPTY_BLOB(), '%s')", atoi(Bcode), tag, strDes);
	
	CheckErr(OCIDescriptorAlloc(
		m_po->hpEnv, 
		(dvoid **)&blob, 
		OCI_DTYPE_LOB, 
		(size_t) 0, 
		(dvoid **) 0));
	if ( FAILED(m_po->hr) )
		return m_po->hr;
	
	CheckErr(OCIHandleAlloc(
		m_po->hpEnv, 
		(dvoid **)&p_sql, 
		OCI_HTYPE_STMT, 
		(size_t) 0, 
		(dvoid **) 0));
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	CheckErr(OCIStmtPrepare(
		p_sql, 
		m_po->hpErr, 
		(unsigned char *)Sql, 
		(ub4)strlen(Sql), 
		OCI_NTV_SYNTAX, 
		OCI_DEFAULT));
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	CheckErr(OCIStmtExecute(
		m_po->hpContext, 
		p_sql, 
		m_po->hpErr, 
		(ub4) 1, 
		(ub4) 0, 
		(OCISnapshot *)NULL, 
		(OCISnapshot *) NULL, 
		(ub4)OCI_COMMIT_ON_SUCCESS));
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	// Select For Update to Insert the BLOB  	
	sprintf(Sql,"SELECT IMAGE FROM IMAGE\
		WHERE ID=%d AND TAG=%d FOR UPDATE", atoi(Bcode), tag);

	// Preparing the Update...
	CheckErr(OCIStmtPrepare(
		p_sql, 
		m_po->hpErr, 
		(unsigned char *)Sql, 
		(ub4)strlen(Sql), 
		OCI_NTV_SYNTAX, 
		OCI_DEFAULT));
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	CheckErr(OCIDefineByPos(
		p_sql, 
		&p_Define, 
		m_po->hpErr, 
		1, 
		(dvoid *) &blob, 
		(sb4) -1, 
		(ub2) SQLT_BLOB, 0, 0, 0, OCI_DEFAULT));
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	CheckErr(OCIStmtExecute(
		m_po->hpContext, 
		p_sql, 
		m_po->hpErr, 
		(ub4) 1, 
		(ub4) 0,
		(OCISnapshot *) NULL, 
		(OCISnapshot *) NULL,(ub4) OCI_DEFAULT));
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	if( (input = fopen(filename,"rb")) == NULL ) {
			AfxMessageBox("The Imagefile failed to open");
			return FALSE;
	}
	
	fsize = _filelength(fileno(input));  //get total file size

	data_in = (char *)malloc(DATA_SIZE); //initial memory
	memset(data_in, 0, DATA_SIZE);
	fread(data_in,  1, DATA_SIZE, input); //get first chunk
	remainingSize = fsize;
	amtp = fsize;

	result = OCILobWrite(
		m_po->hpContext, 
		m_po->hpErr, 
		blob, 
		&amtp, 
		(ub4) 1, 
		data_in, 
		(DATA_SIZE > fsize) ? fsize:DATA_SIZE, 
		(DATA_SIZE > fsize) ?OCI_ONE_PIECE : OCI_FIRST_PIECE,
		(dvoid *) 0, NULL, (ub2) 0, (ub1) 0);
	if ( FAILED(m_po->hr) ){
		fclose(input);
		return m_po->hr;
	}

	if (result == OCI_NEED_DATA) 
	{
		remainingSize -= DATA_SIZE;
		while (remainingSize > DATA_SIZE)
		{
			memset(data_in, 0, DATA_SIZE);
			fread(data_in,  1, DATA_SIZE, input); //get next chunk
			
			CheckErr(OCILobWrite(
				m_po->hpContext, 
				m_po->hpErr, 
				blob, 
				&amtp, 
				(ub4)1, 
				data_in, 
				DATA_SIZE, 
				OCI_NEXT_PIECE, 
				(dvoid *) 0, NULL, (ub2) 0, (ub1) 0));
			if ( FAILED(m_po->hr) ){
				fclose(input);
				return m_po->hr;
			}

			remainingSize -= DATA_SIZE;
		}

		memset(data_in, 0, DATA_SIZE);
		fread(data_in,  1, remainingSize, input); 
		
		CheckErr(OCILobWrite(
			m_po->hpContext, 
			m_po->hpErr, 
			blob, 
			&amtp, (ub4) 1,
			data_in, 
			remainingSize, 
			OCI_LAST_PIECE,
			(dvoid *) 0, 
			NULL, (ub2) 0, (ub1)0));
		if ( FAILED(m_po->hr) ){
			fclose(input);
			return m_po->hr;
		}
	}
	else if (result != OCI_SUCCESS)
	{
		fclose(input);
		return m_po->hr;
	}
	
	fclose(input);

	return m_po->hr;
}

/*
  char query[MAXBUFLEN];

  // Pass query that locate the right record   	
  sprintf(query,"SELECT SONG FROM TESTBIN WHERE KEY='whistle' " );
  HRESULT rs = db.SaveImage(query,"whistleout.bmp");
  if (FAILED(rs))
	Output("Read BLOB whistleout failed\n");
  else 
	Output("Read BLOB whistleout succeded\n");	
 */
HRESULT COdb::SaveImage(char *Sql, char *filename)
{
	sword result;
	char *data_out;
	ub4 remainingSize = 0;
	ub4 amtp;
	FILE *output;

	OCIStmt  *p_sql;
	OCILobLocator *blob;
	OCIDefine  *p_Define = (OCIDefine *) 0;


	CheckErr(OCIDescriptorAlloc(
		m_po->hpEnv, 
		(dvoid **)&blob, 
		OCI_DTYPE_LOB, 
		(size_t) 0, 
		(dvoid **) 0));
	if ( FAILED(m_po->hr) )
		return m_po->hr;
	
	CheckErr(OCIHandleAlloc(
		m_po->hpEnv, 
		(dvoid **)&p_sql, 
		OCI_HTYPE_STMT, 
		(size_t) 0, 
		(dvoid **) 0));
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	// Preparing the Select...
	CheckErr(OCIStmtPrepare(
		p_sql, 
		m_po->hpErr, 
		(unsigned char *)Sql, 
		(ub4)strlen(Sql), 
		OCI_NTV_SYNTAX, 
		OCI_DEFAULT));
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	CheckErr(OCIDefineByPos(
		p_sql, 
		&p_Define, 
		m_po->hpErr, 
		1, 
		(dvoid *) &blob, 
		(sb4) -1, 
		(ub2) SQLT_BLOB, 0, 0, 0, OCI_DEFAULT));
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	// Select the record that hold the BLOB 
	CheckErr(OCIStmtExecute(
		m_po->hpContext, 
		p_sql, 
		m_po->hpErr, 
		(ub4) 1, 
		(ub4) 0,
		(OCISnapshot *) NULL, 
		(OCISnapshot *) NULL,(ub4) OCI_DEFAULT));
	if ( FAILED(m_po->hr) )
		return m_po->hr;

	if( (output = fopen(filename,"wb")) == NULL ) {
			printf("The wav file  failed to open %d",output);
			return FALSE;
	}

	data_out = (char *)malloc(DATA_SIZE); //initial memory
	memset(data_out, 0, DATA_SIZE);

	amtp = 0; // => read in streamed mode

	result = OCILobRead(
		m_po->hpContext, 
				m_po->hpErr, 
				blob, 
				&amtp, 
				(ub4)1, 
				data_out, 
				DATA_SIZE, 
				(dvoid *) 0, 
				NULL, (ub2) 0, (ub1)0);

	if ( FAILED(m_po->hr) ){
		fclose(output);
		return m_po->hr;
	}


//	Check if read last piece of BLOB
	while (result == OCI_NEED_DATA)
	{
		fwrite(data_out,  1, DATA_SIZE, output); //write next chunk	
		memset(data_out, 0, DATA_SIZE);
		amtp = 0;  // read on streamed mode
		result = OCILobRead(
				m_po->hpContext, 
				m_po->hpErr, 
				blob, 
				&amtp, 
				(ub4)1, 
				data_out, 
				DATA_SIZE, 
				(dvoid *) 0, 
				NULL, (ub2) 0, (ub1)0);
		if ( FAILED(m_po->hr) ){
			fclose(output);
			return m_po->hr;
		}
	}
	remainingSize = amtp;
	fwrite(data_out,  1, remainingSize, output); //write last chunk into output file
	
	fclose(output);

	return m_po->hr;

}
