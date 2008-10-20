// OraDB.cpp: implementation of the COraDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OraDB.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COraDB::COraDB()
{
	Clear();
}

COraDB::~COraDB()
{
	Close();
}

void COraDB::Clear()
{
	hr = OCI_SUCCESS;
	hpEnv = NULL;
	hpErr = NULL;
	hpServer = NULL;
	hpContext = NULL;
	hpSelect = NULL;
	szError[0] = '\0';
}

HRESULT COraDB::Open(LPCTSTR csServer, LPCTSTR csUser, LPCTSTR csPassword)
{
	// First, we make sure its closed
	Close();

	// Initialize OCI DLL specifying the mode
	CheckErr( OCIInitialize( OCI_OBJECT, NULL, NULL, NULL, NULL ) );
	if ( FAILED(hr) )
		return hr;

	// Note an alternative is to use the OCILogon/Logoff functions
	// Here we allocate all of the handles explicitly
	// Initialize the environment handle
	CheckErr( OCIEnvInit( &hpEnv, OCI_DEFAULT, 0, NULL ) );
	if ( FAILED(hr) )
		return hr;

	// Allocate error, server, and service context handles
	OCIHandleAlloc( hpEnv, (void**)&hpErr, OCI_HTYPE_ERROR, 0, NULL );
	OCIHandleAlloc( hpEnv, (void**)&hpServer, OCI_HTYPE_SERVER, 0, NULL );
	OCIHandleAlloc( hpEnv, (void**)&hpContext, OCI_HTYPE_SVCCTX, 0, NULL );

	// Associate TNS with server handle
	CheckErr( OCIServerAttach( hpServer,
		hpErr,
		(unsigned char *)csServer,
		_tcslen(csServer),
		0 )
		);
	if ( FAILED(hr) )
		return hr;

	// Get server version string
	const nVersionLength = 1024;
	CString csVersion;
	CheckErr( OCIServerVersion( hpServer,
		hpErr,
		(text*)csVersion.GetBuffer(nVersionLength),
		nVersionLength,
		OCI_HTYPE_SERVER )
		);
	if ( FAILED(hr) )
		return hr;
	csVersion.ReleaseBuffer();
	m_csLog += csVersion + "\n";
	
	// Specify server handle to service context
	CheckErr( OCIAttrSet( hpContext,
		OCI_HTYPE_SVCCTX,
		hpServer,
		0,
		OCI_ATTR_SERVER,
		hpErr )
		);
	if ( FAILED(hr) )
		return hr;

	// Allocate a session handle
	OCISession *hpSession = NULL;
	OCIHandleAlloc( hpEnv, (void**)&hpSession, OCI_HTYPE_SESSION, 0, NULL);

	// Associate username with session handle
	OCIAttrSet( hpSession,
		OCI_HTYPE_SESSION,
		(void*)(const char*)csUser,
		_tcslen(csUser),
		OCI_ATTR_USERNAME,
		hpErr
		);

	// Associate password with session handle
	OCIAttrSet( hpSession,
		OCI_HTYPE_SESSION,
		(void*)(const char*)csPassword,
		_tcslen(csPassword),
		OCI_ATTR_PASSWORD,
		hpErr
		);

	// Open session using service context and session handle
	CheckErr( OCISessionBegin( hpContext,
		hpErr,
		hpSession,
		OCI_CRED_RDBMS,
		OCI_DEFAULT )
		);
	if ( FAILED(hr) )
		return hr;

	// Specify session handle to service context
	OCIAttrSet( hpContext,
		OCI_HTYPE_SVCCTX,
		hpSession,
		0,
		OCI_ATTR_SESSION,
		hpErr
		);

	return hr;
}

HRESULT COraDB::Close()
{
	//
	// This closes and/or cleans up the connection
	// It should work even if the connection is closed or partly open
	//
	hr = OCI_SUCCESS;
	
	// Free select statement handle
	if (hpSelect)
		OCIHandleFree( hpSelect, OCI_HTYPE_STMT );
	
	// Detach server from server handle
	if (hpErr)
		OCIServerDetach( hpServer, hpErr, OCI_DEFAULT );
	
	// Free server handle
	if (hpServer)
		CheckErr( OCIHandleFree(hpServer, OCI_HTYPE_SERVER) );
	
	// Free service context
	if (hpContext)
		OCIHandleFree( hpContext, OCI_HTYPE_SVCCTX);
	
	// Free error handle
	if (hpErr)
		OCIHandleFree( hpErr, OCI_HTYPE_ERROR );
	
	Clear();
	return hr;	
}

COraDB::CheckErr(short status)
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
	hr = status;
	if ( hr == OCI_ERROR )
	{
		// for the special case OCI_ERROR, call OCIErrorGet for the string
		sb4 errcode = 0;
		OCIErrorGet(hpErr, 1, NULL, &errcode, (unsigned char*)szError, sizeof(szError), OCI_HTYPE_ERROR);
	}
	else
	{
		// Look for description in static array
		DWORD nTotalResultCodes = sizeof(epaErrors) / sizeof(CErrorPair);
		for ( int iPos = 0; iPos < sizeof(epaErrors); ++ iPos )
		{
			if ( epaErrors[iPos].w == hr )
			{
				strcpy( szError, epaErrors[iPos].szText );
				break;
			}
		}
	}	
}
