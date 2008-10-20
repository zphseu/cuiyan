#if !defined(AFX_BSRPTERDOC_H__CE410BA4_4D40_4733_BE40_287E4F1D5291__INCLUDED_)
#define AFX_BSRPTERDOC_H__CE410BA4_4D40_4733_BE40_287E4F1D5291__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BSRpterDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEdRptDoc document

#include "EdRptTpl.h"
#include "GridCtrl.h"

#define WM_CREATEPROGRESS  WM_USER+130
#define WM_STEPPROGRESS    WM_USER+131
#define WM_DESTROYPROGRESS WM_USER+132

class CEdRptDoc : public CEdRptTpl
{	
	friend class CEdRptExport;
public:
	CEdRptDoc();           // protected constructor used by dynamic creation
	virtual ~CEdRptDoc();
	HWND	SetHWnd(HWND hWnd) { return m_hWnd = hWnd; }
	CONST HWND GetHWnd() { return m_hWnd; }
	int  IsLoad() { return m_FileData; }
	BOOL GetData();
	const int GetFieldCount() { return m_nFieldCount; }

	CGridCtrl m_Grid;

public:
	BOOL PrintAuto(CPrintDialog *pPntDlg);
	
// Operations
protected:
	HWND	m_hWnd;
	int		m_nRecCount;
	int		m_nFieldCount;
	int		m_FileData;	// 0, not load data; 1, load from file; 2, load from database.

	int GetRecordCount(CDatabase& db);

protected:
	BOOL IsGroup(LPCSTR lpszSql);
	void GetStaticData(CRecordset &rc);
	BOOL GetDataFromDB();
	CString GetVarStr(CDBVariant *pVar, CString format);
	BOOL GetDataFromFile(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BSRPTERDOC_H__CE410BA4_4D40_4733_BE40_287E4F1D5291__INCLUDED_)
