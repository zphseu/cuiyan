// Odb.h: interface for the COdb class.
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
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODB_H__6B1568A3_A4E0_11D2_A0C3_00105A27C570__INCLUDED_)
#define AFX_ODB_H__6B1568A3_A4E0_11D2_A0C3_00105A27C570__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=3EE850540271
class COdb  
{
public:
	HRESULT SaveImage(char *Sql, char *filename);
	HRESULT InsertImage(char *filename, CString Bcode, int tag, CString strDes);
	//##ModelId=3EE850540272
	COdb();
	//##ModelId=3EE850540280
	virtual ~COdb();

	// Public methods
	//##ModelId=3EE850540282
	HRESULT Open( CString csConnect );
	//##ModelId=3EE850540284
	HRESULT Close();
	//##ModelId=3EE850540290
	HRESULT Exec( CString csStatement );
	//##ModelId=3EE850540292
	HRESULT Select( CString csStatement );
	//##ModelId=3EE85054029F
	HRESULT FetchNext();
	//##ModelId=3EE8505402A0
	BOOL IsEOS();
	//##ModelId=3EE8505402A1
	CString GetErrorDescription();
	//##ModelId=3EE8505402AF
	CString ProcessQuotes( CString csValue );
	//##ModelId=3EE8505402B1
	CString GetField( int iField );
	//##ModelId=3EE8505402B3
	CString GetField( CString csName );
	//##ModelId=3EE8505402C0
	BOOL GetField( int iField, CString& csName, CString& csValue, BOOL bQuotesIfValueRequires = FALSE );
	//##ModelId=3EE8505402CF
	CString GetResults(){ return m_csResults; };
	CString GetRows()	{ return m_csRows; };
	CString GetTitles() { return m_csTitles; };
	//##ModelId=3EE8505402D0
	void StartLog() { m_csLog.Empty(); };
	//##ModelId=3EE8505402D1
	CString GetLog() { return m_csLog; };

protected:
	// These structs are defined in the cpp	because they use oci.h types
	struct OdbContext; // status of the instantiated COdb
	struct OdbRecordSet; // defines select list and holds the results
	struct OdbField; // name, type, and result value of a field

	// Protected members
	//##ModelId=3EE8505402EF
	OdbContext* m_po;
	//##ModelId=3EE8505402F3
	CString m_csResults; // fetch row
	CString m_csTitles;
	CString m_csRows;
	//##ModelId=3EE8505402FD
	CString m_csLog; // PL/SQL statement log

	// Internal functions
	//##ModelId=3EE8505402FE
	void CheckErr( short status );
	//##ModelId=3EE85054030E
	static void CleanWhitespace( CString& csStatement );
};

#endif // !defined(AFX_ODB_H__6B1568A3_A4E0_11D2_A0C3_00105A27C570__INCLUDED_)
