// BSRpterDoc.cpp : implementation file
//

#include "stdafx.h"
#include "EdRptDoc.h"
#include "EdRptView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString getDBDriver(LPCSTR szLink);
extern void ShowMessage(HWND hWnd, LPCTSTR fmt, ...);
/////////////////////////////////////////////////////////////////////////////
// CEdRptDoc

CEdRptDoc::CEdRptDoc()
{
	m_nRecCount = 0;
	m_nFieldCount = 0;
	m_hWnd = NULL;
	m_FileData = 0;
}

CEdRptDoc::~CEdRptDoc()
{
}


/////////////////////////////////////////////////////////////////////////////
BOOL CEdRptDoc::GetData()
{
	BOOL bRet = FALSE;
	m_FileData = 0;

	if ( m_nRows > 0 &&  m_nCols > 0)
	{
		m_nFieldCount = m_nCols;
		bRet = GetDataFromFile();
		m_FileData = bRet ? 1 : 0;
	}
	else
	{
		bRet = GetDataFromDB();
		m_FileData = bRet ? 2 : 0;
	}

	m_Grid.SetTitle(m_szTitle, m_szHeadRight, m_szFootLeft, m_szFootRight);
	m_Grid.SetEditable(FALSE);
	m_Grid.EnableDragAndDrop(FALSE);
	m_Grid.SetRowResize(FALSE);
	m_Grid.EnableSelection(FALSE);

	m_Grid.SetFixedRowCount(1);	
	if (m_bFirstColFixed)
		m_Grid.SetFixedColumnCount(1);
	
	// set backup color
	for (int row = m_Grid.GetFixedRowCount(); row < m_Grid.GetRowCount(); row++)
	{
		if (row % 2 == 1) 
			continue;
		for (int col = m_bFirstColFixed; col < m_Grid.GetColumnCount(); col++)
			m_Grid.SetItemBkColour(row, col, RGB(214, 235, 255));
	}
	
	COLORREF clrBkFixed = m_Grid.GetFixedBkColor();
	for (int col = 0; col < m_Grid.GetFixedColumnCount(); col++)
	{
		for (row = 0; row < m_Grid.GetRowCount(); row++)
			m_Grid.SetItemBkColour(row, col, clrBkFixed);
	}

	m_ColFmt.FreeExtra();

	return bRet;
}

BOOL CEdRptDoc::GetDataFromFile(void)
{
	m_nRecCount = m_nRows - 1;

	while (m_ColFmt.GetSize() > m_nFieldCount && m_nFieldCount > 1)
		m_ColFmt.RemoveAt(m_ColFmt.GetSize() - 1);

	COLFMT cf;
	while (m_ColFmt.GetSize() < m_nFieldCount)
		m_ColFmt.Add(cf);

	m_Grid.DeleteAllItems();
	int nRowCount = m_nRecCount + (m_bFootSum ? 2 : 1);
	m_Grid.SetRowCount(nRowCount);
	m_Grid.SetColumnCount(m_nFieldCount);

	if (m_hWnd != NULL && m_nRecCount > 0)
		::SendMessage(m_hWnd, WM_CREATEPROGRESS, m_nRecCount, 0);

	// set ColumName;
	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;	
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
	Item.row = 0;

	for (Item.col = 0; Item.col < m_nFieldCount; Item.col++)
	{
		Item.szText = m_ColFmt[Item.col].name;
		m_Grid.SetItem(&Item);
	}
	
	for(Item.row = 0; Item.row < m_nRows; Item.row++)
	{
		for (Item.col = 0; Item.col < m_nCols; Item.col++)
		{
			Item.szText = m_arData[m_nCols * Item.row + Item.col];
			m_Grid.SetItem(&Item);
		}

		if (m_hWnd != NULL)
			::SendMessage(m_hWnd, WM_STEPPROGRESS, m_nRecCount, Item.row);
	}

	if (m_bFootSum)
	{
		Item.row = m_Grid.GetRowCount() - 1;	
		Item.col = 0;
		Item.szText = "总计";
		m_Grid.SetItem(&Item);

		CString csTmp;
		for (int i = 1; i < m_Grid.GetColumnCount(); i++)
		{
			double fSum = 0.0;
			for (int j = 1; j < m_Grid.GetRowCount() - 1; j++)
			{
				csTmp = m_Grid.GetItemText(j, i);
				fSum += atof(csTmp);
			}

			if (!m_ColFmt[i-1].format.IsEmpty() && m_ColFmt[i-1].format.Find("%") >= 0)
			{
				if (m_ColFmt[i-1].format.FindOneOf("dioux") > 0)
					Item.szText.Format(m_ColFmt[i-1].format, (int) fSum);
				else if (m_ColFmt[i-1].format.FindOneOf("eEfgG") > 0)
					Item.szText.Format(m_ColFmt[i-1].format, fSum);
				else
					Item.szText = "--:--";
			}
			else if (fabs(fSum) > 0.0001)
				Item.szText = _T("请在ColFmt中填入格式");
			else
				Item.szText = "--:--";

			Item.col = i;
			Item.szText.TrimLeft();
			Item.szText.TrimRight();
			m_Grid.SetItem(&Item);
		}
	}

	if (m_hWnd != NULL)
		::SendMessage(m_hWnd, WM_DESTROYPROGRESS, 0, 0);

	return TRUE;
}

BOOL CEdRptDoc::GetDataFromDB()
{
	CDatabase db;
	BOOL bRet = FALSE;
	try 
	{
		if (m_szODBCLink.IsEmpty())
		{
			ShowMessage(m_hWnd, "没有给定数据库指针，也没有指定链接字！");
			return FALSE;
		}

		if (!db.OpenEx(m_szODBCLink, CDatabase::openReadOnly | CDatabase::noOdbcDialog))
		{
			ShowMessage(m_hWnd, "无法打开数据库连接 %s", m_szODBCLink);
			return FALSE;
		}

		m_nRecCount = GetRecordCount(db);
		CRecordset rc(&db);
		
		CString szSQL = m_szSQL;
		CString csHeadRight = m_szHeadRight;
		if (m_nRecCount > (int)m_nMaxRecordNum)
		{
			CString str;
			str.Format(_T("共有 %d 条记录，但模版设计最大记录数为 %d，\n是否只 %d 条记录？\n"
				"注意：如何选否，会给数据库很大压力，甚至取消操作！"), 
				m_nRecCount, m_nMaxRecordNum, m_nMaxRecordNum);
			
			UINT ulSelect = IDNO;
			if (m_hWnd)
				ulSelect = MessageBox(m_hWnd, str, _T("BSRpter"), MB_YESNOCANCEL);

			if (ulSelect == IDNO)
				;
			else if (ulSelect == IDCANCEL)
				return FALSE;
			else // IDYES
			{
				csHeadRight.Format(_T("  %d条记录未打印"), m_nRecCount - m_nMaxRecordNum);
				m_nRecCount = m_nMaxRecordNum;
				
				CString csDBDrv = getDBDriver(m_szODBCLink);
				csDBDrv.MakeLower();
				if (csDBDrv.Find("oracle") >= 0)
				{
					CString szTmp = szSQL;
					szTmp.MakeLower();
					int nFind = szTmp.Find(" where ");
					if (nFind > 0)
					{
						szTmp.Format("ROWNUM <= %d AND ", m_nMaxRecordNum);
						szSQL.Insert(nFind + (int)_tcslen(" where "), (LPCSTR)szTmp);
					}
					else
					{
						szTmp.Format(" WHERE ROWNUM <= %d ", m_nMaxRecordNum);
						szSQL += szTmp;
					}
				}
				else if (csDBDrv.Find("mysql") >= 0)
				{
					CString szTmp;
					szTmp.Format(" Limit 0, %d ", m_nMaxRecordNum);
					szSQL += szTmp;
				}
				else
				{
					CString str;
					str.Format(_T("[ %s ] 数据库无法使用修改SQL的方法限制记录个数，"
						"而打开大数据集可能会出现异常\n，是否先修改查询条件，再进行打印？")
						, csDBDrv);
					if (m_hWnd != NULL && MessageBox(m_hWnd, str,_T("EdFc"), MB_YESNO) == IDYES)
						return FALSE;
				}
			}
		}

		rc.Open(CRecordset::forwardOnly, szSQL);
		m_nFieldCount = rc.GetODBCFieldCount();
		
		while (m_ColFmt.GetSize() > m_nFieldCount && m_nFieldCount > 1)
			m_ColFmt.RemoveAt(m_ColFmt.GetSize() - 1);
		
		COLFMT cf;
		while (m_ColFmt.GetSize() < m_nFieldCount)
			m_ColFmt.Add(cf);
				
		m_Grid.DeleteAllItems();
		int nRowCount = m_nRecCount + (m_bFootSum ? 2 : 1);
		m_Grid.SetRowCount(nRowCount);
		m_Grid.SetColumnCount(m_nFieldCount);
		
		// set ColumName;
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;	
		Item.row = 0;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
		for (Item.col = 0; Item.col < m_nFieldCount; Item.col++)
		{	
			m_Grid.SetColumnWidth(Item.col, m_ColFmt[Item.col].width);
			Item.szText = m_ColFmt[Item.col].name;			

			if (m_ColFmt[Item.col].name.IsEmpty())
			{
				CODBCFieldInfo fi;
				rc.GetODBCFieldInfo(Item.col, fi);
				Item.szText = fi.m_strName;
			}

			m_Grid.SetItem(&Item);
		}

		if (m_hWnd != NULL && m_nRecCount > 0)
			::SendMessage(m_hWnd, WM_CREATEPROGRESS, m_nRecCount, 0);

		CDBVariant varValue;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
		for(int row = 0; row < m_nRecCount; row ++)
		{
			for (int col = 0; col < m_nFieldCount; col ++)
			{
				rc.GetFieldValue(col, varValue);
				Item.row = row + 1;
				Item.col = col;
				Item.szText = GetVarStr(&varValue, m_ColFmt[col].format);
				m_Grid.SetItem(&Item);	
				varValue.Clear();
			}
			
			if (m_hWnd != NULL)
				::SendMessage(m_hWnd, WM_STEPPROGRESS, m_nRecCount, row);
			
			rc.MoveNext();
		}
		
		if (m_bFootSum)
			GetStaticData(rc);
		
		rc.Close();	
		

		if (m_hWnd != NULL)
			::SendMessage(m_hWnd, WM_DESTROYPROGRESS, 0, 0);

		bRet = TRUE;
	}
	catch(CException *edb)
	{
		static TCHAR lpszError[MAX_PATH];
		CString csError;

		if (edb->GetErrorMessage(lpszError, MAX_PATH))
			csError = lpszError;

		if (csError.GetLength() <= 0)
			csError = _T("无法获得数据！");
		
		ShowMessage(m_hWnd, csError);

		edb->Delete();
	}
	catch(...)
	{
		ShowMessage(m_hWnd, _T("无法获得数据！"));
	}

	return bRet;
}

/**
 *  fill grid cell by type.
 *  following type to fil grid cell.
 *  <PRE>
 *	 TYPE  FORMAT RULE
 *	 TIME    CTime
 *	 BOOL   "Yes No"
 *  </PRE>
 *  @param  -[in]  int  col: [column num]
 *  @param  -[in]  int  row: [row num]
 *  @param  -[in]  CDBVariant*  pVar: [argment]
 *
 *  @version  05/09/2003  cuiyan  Initial Version.
 */
CString CEdRptDoc::GetVarStr(CDBVariant* pVar, CString format)
{
	CString str;

	switch(pVar->m_dwType)
	{
	case DBVT_BOOL: 
		if (format.IsEmpty())
			str = pVar->m_boolVal ? _T("Y") : _T("N");
		else {
			str = pVar->m_boolVal ? 
				format.Left(format.Find(' ')) :
				format.Right(format.GetLength() - format.Find(' ') - 1);
			str.TrimLeft();
			str.TrimRight();
		}
		break;

	case DBVT_UCHAR:
		if (format.IsEmpty())
			str.Format("%c", pVar->m_chVal);
		else
			str.Format(format, pVar->m_chVal);
		break;

	case DBVT_SHORT:
		if (format.IsEmpty())
			str.Format("%d", pVar->m_iVal);
		else
			str.Format(format, pVar->m_iVal);
		break;

	case DBVT_LONG:
		if (format.IsEmpty())
			str.Format("%ld", pVar->m_lVal);
		else
			str.Format(format, pVar->m_lVal);
		break;

	case DBVT_SINGLE:
		if (format.IsEmpty())
			str.Format("%g", pVar->m_fltVal);
		else
			str.Format(format, pVar->m_fltVal);
		break;

	case DBVT_DOUBLE:
		if (format.IsEmpty())
			str.Format("%g", pVar->m_dblVal);
		else
			str.Format(format, pVar->m_dblVal);
		break;

	case DBVT_DATE:	{
		CTime tm(pVar->m_pdate->year, pVar->m_pdate->month,	pVar->m_pdate->day, 
			pVar->m_pdate->hour, pVar->m_pdate->minute, pVar->m_pdate->second, pVar->m_pdate->fraction);

		if (format.IsEmpty())
			str = tm.Format("%Y/%m/%d %H:%M:%S");
		else
			str = tm.Format(format);
		}
		break;

	case DBVT_STRING:
		if (format.IsEmpty())
			str = *pVar->m_pstring;
		else
			str.Format(format, *pVar->m_pstring);

		str.TrimRight();
		break;

	case DBVT_BINARY:
		str = _T("Binary");
		break;
	default:
		str = _T("");
		break;
	}

	return str;
}

#include "winspool.h"
#include "edrptdoc.h"
#define MAXLEN  MAX_PATH * 4

BOOL CEdRptDoc::PrintAuto(CPrintDialog *pPntDlg)
{
	// 严禁在不使用省却打印机情况下不指定打印机
	ASSERT(m_bDefaultPrint || pPntDlg);
	
	// get default print
	CPrintDialog defaultDlg (FALSE, PD_RETURNDC );
	AfxGetApp()->GetPrinterDeviceDefaults( &defaultDlg.m_pd );	

	if (!pPntDlg)
		pPntDlg = &defaultDlg;
	
	HDC hdc = pPntDlg->CreatePrinterDC();
	ASSERT(hdc);
	CDC dc;
	dc.Attach( hdc );
	
    dc.m_bPrinting = TRUE;
	
    CString strTitle = m_szTitle;
	if (strTitle.IsEmpty())
		strTitle.LoadString(AFX_IDS_APP_TITLE);
		
    DOCINFO di;                                 // Initialise print doc details
    memset(&di, 0, sizeof (DOCINFO));
    di.cbSize = sizeof (DOCINFO);
    di.lpszDocName = strTitle;
	
    BOOL bPrintingOK = dc.StartDoc(&di);        // Begin a new print job
	
    CPrintInfo Info;
    Info.m_rectDraw.SetRect(0,0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));
	
    m_Grid.OnBeginPrinting(&dc, &Info);                // Initialise printing
	m_Grid.SetFocus();
    for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++)
    {
        dc.StartPage();                         // begin new page
        Info.m_nCurPage = page;
        m_Grid.OnPrint(&dc, &Info);                    // Print page
        bPrintingOK = (dc.EndPage() > 0);       // end page
    }
    m_Grid.OnEndPrinting(&dc, &Info);                  // Clean up after printing
	
    if (bPrintingOK)
        dc.EndDoc();                            // end a print job
    else
        dc.AbortDoc();                          // abort job.
	
    dc.Detach();                                // detach the printer DC
	
	DeleteDC(hdc);

	return TRUE;
}


/**
 *  Get Record count.
 *
 *  @return return record num.
 *
 *  @version  05/09/2003  cuiyan  Initial Version.
 *  @version  09/01/2003  cuiyan  多表联合查询时有问题. 参见test\db1.rar 中的
 *				查询2，关键在于Group by
 *  @version  09/02/2003  cuiyan  考虑大记录集问题，综合两个因素.
 */
int CEdRptDoc::GetRecordCount(CDatabase& db)
{
	int bRet = 0;

	CString szTmp = m_szSQL;
	CString szFrom = m_szSQL;
	szTmp.MakeLower();
	szFrom = szFrom.Right( szTmp.GetLength() - szTmp.Find("from") );
	CString szCountSQL = "SELECT COUNT(*) " + szFrom;
	
	CRecordset rc(&db);
	rc.Open(CRecordset::forwardOnly, szCountSQL);

	if (IsGroup(szCountSQL))
	{
		for (bRet = 0; !rc.IsEOF(); bRet++)
			rc.MoveNext();
	}
	else
	{
		rc.GetFieldValue(short(0), szCountSQL);		
		bRet = atoi(szCountSQL.GetBuffer(0));
	}

	rc.Close();

	return bRet;
}

void CEdRptDoc::GetStaticData(CRecordset &rc)
{
	if (!rc.IsOpen())
		return;

	CString csTmp;

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;	
	Item.row = m_Grid.GetRowCount() - 1;	
	Item.col = 0;
	Item.szText = "总计";
	m_Grid.SetItem(&Item);

	CString csFormat;
	CODBCFieldInfo fi;
	for (Item.col = 1; Item.col < m_ColFmt.GetSize(); Item.col++)
	{
		if (m_ColFmt[Item.col].format.IsEmpty())
		{
			rc.GetODBCFieldInfo(short(Item.col), fi);
			if (fi.m_nSQLType == SQL_NUMERIC || fi.m_nSQLType == SQL_DECIMAL)
			{
				if (fi.m_nScale == 0)
				{
					fi.m_nSQLType = SQL_INTEGER;
					csFormat.Format("%%%dd", fi.m_nPrecision);				
				}
				else
				{
					fi.m_nSQLType = SQL_FLOAT;
					csFormat.Format("%%%d.%df", fi.m_nPrecision, fi.m_nScale);				
				}
			}
		}
		else
		{
			csFormat = m_ColFmt[Item.col].format;
			if (csFormat.FindOneOf("dioux") > 0)
				fi.m_nSQLType = SQL_INTEGER;
			else if (csFormat.FindOneOf("eEfgG") > 0)
				fi.m_nSQLType = SQL_FLOAT;
			else
				fi.m_nSQLType = SQL_DATETIME;
		}

		switch(fi.m_nSQLType)
		{
		case SQL_INTEGER:
		case SQL_SMALLINT:
		case SQL_TINYINT:
		case SQL_BIGINT:
			fi.m_nSQLType = SQL_INTEGER;
			if (csFormat.IsEmpty())
				csFormat = _T("%d");
			break;

		case SQL_FLOAT:
		case SQL_REAL:
		case SQL_DOUBLE:
			fi.m_nSQLType = SQL_FLOAT;
			if (csFormat.IsEmpty())
				csFormat = _T("%f");
			break;
		default:
			break;
		}
		
		double fSum = 0.0;
		if (fi.m_nSQLType == SQL_INTEGER || fi.m_nSQLType == SQL_FLOAT)
		{
			CString csTmp;
			for (int j = 1; j < m_Grid.GetRowCount() - 1; j++)
			{
				csTmp = m_Grid.GetItemText(j, Item.col);
				fSum += atof(csTmp);
			}
		}
		
		if (fi.m_nSQLType == SQL_INTEGER)
			Item.szText.Format(csFormat, (int)fSum);
		else if (fi.m_nSQLType == SQL_FLOAT)
			Item.szText.Format(csFormat, fSum);
		else
			Item.szText = "--:--";

		Item.szText.TrimLeft();
		Item.szText.TrimRight();
		m_Grid.SetItem(&Item);	
	}
	
}


BOOL CEdRptDoc::IsGroup(LPCSTR lpszSql)
{
	CString strSQL;
	CString strTemp;
	int nBracketNum;
	int nBracketPos;
	int nGroupPos;
	
	strSQL = lpszSql;
	strTemp = lpszSql;
	strSQL = strSQL.Right(strTemp.GetLength()-strTemp.Find("from"));
	strSQL.MakeLower();
	nGroupPos = strSQL.Find("group");
	while (nGroupPos!=-1)
	{
		strTemp=strSQL.Left(nGroupPos);
		
		nBracketNum=0;
		nBracketPos=strTemp.Find("(");
		while (nBracketPos!=-1)
		{
			nBracketNum++;
			nBracketPos=strTemp.Find("(",nBracketPos+1);
		}
		
		nBracketPos=strTemp.Find(")");
		while (nBracketPos!=-1)
		{
			nBracketNum--;
			nBracketPos=strTemp.Find(")",nBracketPos+1);
		}
		
		if (nBracketNum==0)
		{
			return TRUE;
		}
		
		nGroupPos=strSQL.Find("group",nGroupPos+3);
	}
	
	return FALSE;
}

