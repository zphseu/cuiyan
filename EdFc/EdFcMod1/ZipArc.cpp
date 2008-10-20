// ZipArc.cpp: implementation of the CZipArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZipArc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//##ModelId=3F4187E60130
CZipArc::CZipArc()
{

}

//##ModelId=3F4187E60131
CZipArc::~CZipArc()
{

}

/**
 *  add file to zip package.
 *  add apoint file to zip package.
 *
 *  @param  -[in]  LPCTSTR  szFileName: [the name of file to add this package.]
 *  @return if success, return true.
 *
 *  @version  05/22/2003  cuiyan  Initial Version.
 */
//##ModelId=3F4187E6012D
BOOL CZipArc::AddFileToZip(LPCTSTR szFileName)
{
	BOOL bAfterException = FALSE;

	try
	{
		AddNewFile(szFileName, -1, FALSE);
	}
	catch (CException* e)
	{
		e->Delete();
		bAfterException = TRUE;
	}
	catch(...) // thrown in the STL version
	{
		bAfterException = TRUE;
	}
	
	if (bAfterException)
	{
		TRACE("Zip File Error!\n");
		CloseZip();
	}

	return (!bAfterException);
}

//##ModelId=3F4187E6012F
BOOL CZipArc::CloseZip()
{
	BOOL bAfterException = FALSE;
	
	try
	{
		Close();
	}
	catch (CException* e)
	{
		e->Delete();
		bAfterException = TRUE;
	}
	catch(...) // thrown in the STL version
	{
		bAfterException = TRUE;		
	}
	
	if (bAfterException)
	{
		TRACE("Close Zip File Error!\n");
	}

	return (!bAfterException);
}

//##ModelId=3F4187E60124
BOOL CZipArc::CreateZip(CString szZipFn, CString szPw)
{
	BOOL bAfterException = FALSE;

	try
	{
		Open(szZipFn, CZipArchive::create);
		if ( !szPw.IsEmpty() )
			SetPassword(szPw);
	}
	catch (CException* e)
	{
		e->Delete();
		bAfterException = TRUE;
	}
	catch(...) // thrown in the STL version
	{
		bAfterException = TRUE;
	}
	
	if (bAfterException)
	{
		TRACE("Close Zip File Error!\n");
		CloseZip();
	}


	return (!bAfterException);
}
