// BSExport.h: interface for the CEdRptExport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSEXPORT_H__F5E2E030_0AC0_42D1_9540_AC0CA973C1AC__INCLUDED_)
#define AFX_BSEXPORT_H__F5E2E030_0AC0_42D1_9540_AC0CA973C1AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream>
#include "EdRptDoc.h"
#include "ZipArc.h"

using namespace std;

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

class CEdRptExport
{
public:
	CEdRptExport(CEdRptDoc *pDoc, LPCTSTR szExpName = NULL, LPCTSTR szImDir = NULL);
	BOOL DoImporting();
	BOOL DoExporting();
	virtual ~CEdRptExport();

protected:
	static BOOL OnPrepareExporting(LPCSTR szFmtName, LPCSTR szExpName);
	static VOID OnBeginExporting();
	static VOID OnExport();
	static VOID OnEndExporting();
	
	static BOOL OnPrepareImporting(LPCSTR szExpName, LPCSTR szImDir);
	static VOID OnBeginImporting()	{}
	static VOID OnImport()			{}
	static VOID OnEndImporting()	{}
	VOID Initialize();

	static CString			m_szExpName;
	static CString			m_szPath;
	static CString			m_szImDir;
	static CZipArc			m_ZipArc;
	static CEdRptDoc*		m_pDoc;

	typedef BOOL (*TypeBOOL)(LPCSTR,LPCSTR);
	typedef VOID (*TypeVOID)();
	static TypeBOOL m_pExPrepare, m_pImPrepare;
	static TypeVOID m_pExBegin, m_pExport, m_pExEnd;
	static TypeVOID m_pImBegin, m_pImport, m_pImEnd;


private:
	static BOOL	ExportGridData(ofstream& htm, ofstream& txt);
	static BOOL ExportDBData(ofstream& htm, ofstream& txt);

	static VOID TxtToHtml(CString& str);
	static LPCTSTR GetPicExtName(LPCTSTR szTypeFlag);
	static CString GetPicFile(CLongBinary* pVar, UINT nCounter);
	static VOID	DeletePathFile(CString strPath);

	HINSTANCE	m_Instance;
};

#endif // !defined(AFX_BSEXPORT_H__F5E2E030_0AC0_42D1_9540_AC0CA973C1AC__INCLUDED_)
