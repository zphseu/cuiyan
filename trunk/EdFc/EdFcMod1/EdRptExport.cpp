// BSExport.cpp: implementation of the CEdRptExport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdRptExport.h"

extern CString getDBDriver(LPCSTR szLink);
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUm_NEW
#endif

#include "ZipArc.h"
CString			CEdRptExport::m_szExpName = _T("");
CString			CEdRptExport::m_szPath	= _T("");
CString			CEdRptExport::m_szImDir	= _T("");
CZipArc			CEdRptExport::m_ZipArc;
CEdRptDoc*		CEdRptExport::m_pDoc = NULL;

CEdRptExport::TypeBOOL CEdRptExport::m_pExPrepare = NULL, CEdRptExport::m_pImPrepare = NULL;
CEdRptExport::TypeVOID CEdRptExport::m_pExBegin = NULL, CEdRptExport::m_pExport = NULL, CEdRptExport::m_pExEnd = NULL;
CEdRptExport::TypeVOID CEdRptExport::m_pImBegin = NULL, CEdRptExport::m_pImport = NULL, CEdRptExport::m_pImEnd = NULL;

extern CString g_csPath;
extern void ShowMessage(HWND hWnd, LPCTSTR fmt, ...);
#define PASSWORD _T("+cui*tiger&he.rabbit&")
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdRptExport::CEdRptExport(CEdRptDoc *pDoc, LPCTSTR szExpName, LPCTSTR szImDir)
{
	ASSERT(pDoc);
	m_pDoc = pDoc;
	m_Instance = NULL;
	m_szExpName = szExpName;
	m_szImDir = szImDir;

	TCHAR szTmpDir[MAX_PATH];
	ZeroMemory(szTmpDir, MAX_PATH);
	GetTempPath(MAX_PATH, szTmpDir);
	m_szPath = szTmpDir + CString(_T("BSExport\\"));
	Initialize();
}

VOID CEdRptExport::Initialize()
{
	// init function	
	try
	{
		if (m_Instance == NULL)
			m_Instance = ::LoadLibrary(g_csPath + _T("DBExport.dll"));
		if (m_Instance == NULL)
			throw 0;
		
		m_pExPrepare	= (TypeBOOL) GetProcAddress(m_Instance, _T("OnExPrepare"));
		m_pExBegin		= (TypeVOID) GetProcAddress(m_Instance, _T("OnExBegin"));
		m_pExport		= (TypeVOID) GetProcAddress(m_Instance, _T("OnExport"));
		m_pExEnd		= (TypeVOID) GetProcAddress(m_Instance, _T("OnExEnd"));
		
		m_pImPrepare	= (TypeBOOL) GetProcAddress(m_Instance, _T("OnImPrepare"));
		m_pImBegin		= (TypeVOID) GetProcAddress(m_Instance, _T("OnImBegin"));
		m_pImport		= (TypeVOID) GetProcAddress(m_Instance, _T("OnImport"));
		m_pImEnd		= (TypeVOID) GetProcAddress(m_Instance, _T("OnImEnd"));
		
		if (!(m_pExPrepare && m_pExBegin && m_pExport && m_pExEnd
			&&m_pImPrepare && m_pImBegin && m_pImport && m_pImEnd))
			throw 1;
	}
	catch(int e)
	{
		if (e == 1)
		{
			::FreeLibrary(m_Instance);
			m_Instance = NULL;
			ShowMessage(m_pDoc->GetHWnd(), "无法加载导入导出函数");
		}
		
		m_pExPrepare	= (TypeBOOL)OnPrepareExporting;
		m_pExBegin		= (TypeVOID)OnBeginExporting;
		m_pExport		= (TypeVOID)OnExport;
		m_pExEnd		= (TypeVOID)OnEndExporting;		
		
		m_pImPrepare	= (TypeBOOL)OnPrepareImporting;
		m_pImBegin		= (TypeVOID)OnBeginImporting;
		m_pImport		= (TypeVOID)OnImport;
		m_pImEnd		= (TypeVOID)OnEndImporting;		
	}
}

CEdRptExport::~CEdRptExport()
{
	if (m_Instance)
		::FreeLibrary(m_Instance);
}

//// Exporting //////////////////////////////////////////////////////////
BOOL CEdRptExport::DoExporting()
{
	if (!m_pExPrepare(m_pDoc->m_csFileName, m_szExpName))
		return FALSE;
	
	m_pExBegin();
	m_pExport();
	m_pExEnd();
	return TRUE;
}

BOOL CEdRptExport::OnPrepareExporting(LPCSTR szFmtName, LPCSTR szExpName)
{
	m_szExpName = szExpName;
	if (m_szExpName.IsEmpty() && m_pDoc->GetHWnd() != NULL)
	{
		CFileDialog dlg(FALSE, _T("bsexim"), g_csPath + _T(".bsexim"), 
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			_T("BSExport Files (*.bsexim)|*.bsexim|All Files (*.*)|*.*||"));
		
		if (dlg.DoModal() != IDOK)
			return FALSE;
		
		m_szExpName = dlg.GetPathName();
	}
	else
	{
		ASSERT("无视必须给出szExpName信息。");
	}
	
	if ( !m_ZipArc.CreateZip(m_szExpName, PASSWORD ) )
	{
		ShowMessage(m_pDoc->GetHWnd(), "无法打开文件 %s !\n", m_szExpName);
		return FALSE;
	}
	
	if (!m_ZipArc.AddFileToZip(m_pDoc->m_csFileName))
		return FALSE;

	return TRUE;
}

VOID CEdRptExport::OnBeginExporting()
{
	CreateDirectory(m_szPath, NULL);	
}

VOID CEdRptExport::OnExport()
{
	CString szFileHtm = m_szPath + _T("export.htm");
	ofstream htm((LPCTSTR)szFileHtm);
	CString szFileTxt = m_szPath + _T("export.txt");
	ofstream txt((LPCTSTR)szFileTxt);
	
	if (htm.fail() || txt.fail())
	{
		ShowMessage(m_pDoc->GetHWnd(), "无法生成导出文件！\n");
		return;
	}
	
	if (m_pDoc->IsLoad() == 1) // get file
		ExportGridData(htm, txt);
	else		// get database
		ExportDBData(htm, txt);
	
	htm.close();
	txt.close();

	m_ZipArc.AddFileToZip(szFileHtm);
	m_ZipArc.AddFileToZip(szFileTxt);
	DeleteFile(szFileHtm);
	DeleteFile(szFileTxt);
}

VOID CEdRptExport::OnEndExporting()
{
	DeletePathFile(m_szPath + "*.*");
	RemoveDirectory(m_szPath);

	m_ZipArc.CloseZip();
	
	// modify file head
	FILE *fp = fopen(m_szExpName, "r+");
	if (fp != NULL)
	{
		fputc('b', fp);
		fputc('s', fp);
	}
	fclose(fp);
}

BOOL CEdRptExport::ExportGridData(ofstream& htm, ofstream& txt)
{
	CGridCtrl &grid = m_pDoc->m_Grid;

	CString szTitle = m_pDoc->m_szTitle;
	TxtToHtml(szTitle);
	
	CString csHeadFile = m_pDoc->m_szHeadRight;
	TxtToHtml(csHeadFile);
	CString szHeadRight = m_pDoc->m_szHeadRight;
	TxtToHtml(szHeadRight);
	htm << "<html><head><title>" 
		<< (LPCTSTR)szTitle 
		<< "</title></head>"
		<< endl;
	
	htm << "<body>" << endl
		<< "<table width=100%>" << endl
		<< "<tr>" << endl
		<< "\t<td width=20%>&nbsp;</td>" << endl
		<< "\t<td width=60% align=center><font size=+3>" 
		<< (LPCTSTR)szTitle
		<< "</font></td>" << endl
		<< "\t<td width=20% align=right>"
		<< (LPCTSTR)csHeadFile
		<< "</td>" << endl 
		<< "</tr>" << endl
		<< "</table>" << endl;
	
	htm << "<table border=1 width=100%>" << endl
		<< "<tr>" << endl;
	
	
	UINT nFieldCount = grid.GetColumnCount();
	UINT nRecCount = grid.GetRowCount();
	
	int nWidth = 0;
	for (UINT col = 0; col < nFieldCount; col++)
		nWidth += m_pDoc->m_ColFmt[col].width;
	
	// set data;
	if (m_pDoc->GetHWnd() != NULL && nRecCount > 0)
		::SendMessage(m_pDoc->GetHWnd(), WM_CREATEPROGRESS, nRecCount, 0);
	
	CString str;
	for(UINT row = 0; row < nRecCount; row ++)
	{
		htm << "<tr>" << endl;
		
		for (UINT col = 0; col < nFieldCount; col ++)
		{
			str = grid.GetItemText(row, col);
			txt << "\"" << (LPCTSTR)str << "\"";
			
			TxtToHtml(str);
			if (row != 0)
				htm << "\t<td align=center>" << (LPCTSTR)str << "</td>" << endl;
			else
				htm << "\t<td  width=" << m_pDoc->m_ColFmt[col].width * 100 / nWidth
					<< "%  align=center>" << (LPCTSTR)str << "</td>" << endl;
			
			if (col == nFieldCount - 1)
			{
				txt << endl;
				htm << "</tr>" << endl;
			}
			else
				txt << ',';
		}
		
		if (m_pDoc->GetHWnd() != NULL)
			::SendMessage(m_pDoc->GetHWnd(), WM_STEPPROGRESS, nRecCount, row);
	}
	
	CString szFootLeft = m_pDoc->m_szFootLeft;
	TxtToHtml(szFootLeft);
	CString szFootRight = m_pDoc->m_szFootRight;
	if (szFootRight.IsEmpty())
		szFootRight = CTime::GetCurrentTime().Format("%m/%d/%y %H:%M:%S");
	TxtToHtml(szFootRight);
	
	htm << "</table>" << endl
		<< "<p>" << endl
		<< "<table width=100%>" << endl
		<< "<tr>" << endl 
		<< "\t<td width=50% align=left>"
		<< (LPCTSTR)szFootLeft
		<< "</td>" << endl
		<< "\t<td width=50% align=right>"
		<< (LPCTSTR)szFootRight
		<< "</td>" << endl
		<< "</table>" << endl;
	
	if (m_pDoc->GetHWnd() != NULL)
		::SendMessage(m_pDoc->GetHWnd(), WM_DESTROYPROGRESS, 0, 0);
	
	return TRUE;
}

BOOL CEdRptExport::ExportDBData(ofstream &htm, ofstream &txt)
{
	CDatabase db;
	BOOL bRet = FALSE;

	CString csHeadFile = m_pDoc->m_szHeadRight;
	if (m_pDoc->m_szODBCLink.IsEmpty())
	{
		ShowMessage(m_pDoc->GetHWnd(), "没有给定数据库指针，也没有指定链接字！");
		return FALSE;
	}

	if (!db.OpenEx(m_pDoc->m_szODBCLink, CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		ShowMessage(m_pDoc->GetHWnd(), "无法打开数据库连接 %s", m_pDoc->m_szODBCLink);
		return FALSE;
	}

	try 
	{
		UINT nRecCount = m_pDoc->GetRecordCount(db);

		CString szSQL = m_pDoc->m_szSQL;
		if (nRecCount > (int)m_pDoc->m_nMaxRecordNum)
		{
			CString str;
			str.Format(_T("共有 %d 条记录，但模版设计最大记录数为 %d，\n是否只 %d 条记录？\n"
				"注意：如何选否，会给数据库很大压力，甚至取消操作！"), 
				nRecCount, m_pDoc->m_nMaxRecordNum, m_pDoc->m_nMaxRecordNum);
			
			UINT ulSelect = IDNO;
			if (m_pDoc->GetHWnd())
				ulSelect = MessageBox(m_pDoc->GetHWnd(), str, _T("EdFc"), MB_YESNOCANCEL);
			
			if (ulSelect == IDNO)
				;
			else if (ulSelect == IDCANCEL)
				return FALSE;
			else // IDYES
			{
				csHeadFile.Format(_T("  %d条记录未导出"), nRecCount - m_pDoc->m_nMaxRecordNum);
				nRecCount = m_pDoc->m_nMaxRecordNum;
				
				CString csDBDrv = getDBDriver(m_pDoc->m_szODBCLink);
				csDBDrv.MakeLower();
				if (csDBDrv.Find("oracle") >= 0)
				{
					CString szTmp = szSQL;
					szTmp.MakeLower();
					int nFind = szTmp.Find(" where ");
					if (nFind > 0)
					{
						szTmp.Format(" ROWNUM <= %d AND ", m_pDoc->m_nMaxRecordNum);
						szSQL.Insert(nFind + (int)_tcslen(" where "), (LPCSTR)szTmp);
					}
					else
					{
						szTmp.Format(" WHERE ROWNUM <= %d ", m_pDoc->m_nMaxRecordNum);
						szSQL += szTmp;
					}
				}
				else if (csDBDrv.Find("mysql") >= 0)
				{
					CString szTmp;
					szTmp.Format(" Limit 0, %d ", m_pDoc->m_nMaxRecordNum);
					szSQL += szTmp;
				}
// 				else if (csDBDrv.IsEmpty())
// 					ShowMessage(m_pDoc->GetHWnd(), "报表打印组件无法判断该数据库的类型。");
				else
				{
					CString str;
					str.Format(_T("[ %s ] 数据库无法使用修改SQL的方法限制记录个数，而打开大数据集可能会出现异常\n，是否先修改查询条件，再进行打印？"), csDBDrv);
					if (m_pDoc->GetHWnd() && MessageBox(m_pDoc->GetHWnd(), str,_T("BSRpter"), MB_YESNO) == IDYES)
						return FALSE;
				}
			}
		}
		
		CRecordset rc(&db);
		rc.Open(CRecordset::forwardOnly, szSQL);
		UINT nFieldCount = rc.GetODBCFieldCount();
		
		CString szTitle = m_pDoc->m_szTitle;
		TxtToHtml(szTitle);

		CString szHeadRight = m_pDoc->m_szHeadRight;
		TxtToHtml(szHeadRight);
		htm << "<html><head><title>" 
			<< (LPCTSTR)szTitle 
			<< "</title></head>"
			<< endl;

		htm << "<body>" << endl
			<< "<table width=100%>" << endl
			<< "<tr>" << endl
			<< "\t<td width=20%>&nbsp;</td>" << endl
			<< "\t<td width=60% align=center><font size=+3>" 
			<< (LPCTSTR)szTitle
			<< "</font></td>" << endl
			<< "\t<td width=20% align=right>"
			<< (LPCTSTR)csHeadFile
			<< "</td>" << endl 
			<< "</tr>" << endl
			<< "</table>" << endl;

		htm << "<table border=1 width=100%>" << endl
			<< "<tr>" << endl;

		
		int nWidth = 0;
		for (UINT col = 0; col < nFieldCount; col++)
			nWidth += m_pDoc->m_ColFmt[col].width;

		CString str;
		for (col = 0; col < nFieldCount; col++)
		{	
			str = m_pDoc->m_ColFmt[col].name;

			if (str.IsEmpty())
			{
				CODBCFieldInfo fi;
				rc.GetODBCFieldInfo(col, fi);
				str = fi.m_strName;
			}

			txt << "\"" << (LPCTSTR)str << "\"";
			TxtToHtml(str);
			htm << "\t<td  width=" << m_pDoc->m_ColFmt[col].width * 100 / nWidth
				<< "%  align=center>" << (LPCTSTR)str << "</td>" << endl;
			
			if (col == nFieldCount - 1)
			{
				txt << endl;
				htm << "</tr>" << endl;
			}
			else
				txt << ',';
		}
		
		if (m_pDoc->GetHWnd())
			::SendMessage(m_pDoc->GetHWnd(), WM_CREATEPROGRESS, nRecCount, 0);

		CDBVariant varValue;
		CString strHtml;
		UINT nCount = 0;
		for(UINT row = 0; row < nRecCount; row ++)
		{
			htm << "<tr>" << endl;

			for (UINT col = 0; col < nFieldCount; col ++)
			{
				strHtml = _T("");
				rc.GetFieldValue(col, varValue);

				if (varValue.m_dwType == DBVT_BINARY)
				{
					str = GetPicFile(varValue.m_pbinary, nCount++);
					
					if (str.IsEmpty())	//error
						continue;
					
					m_ZipArc.AddFileToZip(str);
					DeleteFile(str);
					str = str.Right(str.GetLength() - str.ReverseFind('\\') - 1);
					strHtml.Format("<A href=%s>%s</A>", str, str);
				}
				else 
					str = m_pDoc->GetVarStr(&varValue, m_pDoc->m_ColFmt[col].format);

				varValue.Clear();
				
				txt << "\"" << (LPCTSTR)str << "\"";
				
				TxtToHtml(str);
				if (strHtml.IsEmpty())
					strHtml = str;
					
				htm << "\t<td align=center>" << (LPCTSTR)strHtml << "</td>" << endl;
				
				if (col == nFieldCount - 1)
				{
					txt << endl;
					htm << "</tr>" << endl;
				}
				else
					txt << ',';
			}

			if (m_pDoc->GetHWnd())
				::SendMessage(m_pDoc->GetHWnd(), WM_STEPPROGRESS, nRecCount, row);

			rc.MoveNext();
		}
		
		rc.Close();
	
		CString szFootLeft = m_pDoc->m_szFootLeft;
		TxtToHtml(szFootLeft);
		CString szFootRight = m_pDoc->m_szFootRight;
		if (szFootRight.IsEmpty())
			szFootRight = CTime::GetCurrentTime().Format("%m/%d/%y %H:%M:%S");
		TxtToHtml(szFootRight);

		htm << "</table>" << endl
			<< "<p>" << endl
			<< "<table width=100%>" << endl
			<< "<tr>" << endl 
			<< "\t<td width=50% align=left>"
			<< (LPCTSTR)szFootLeft
			<< "</td>" << endl
			<< "\t<td width=50% align=right>"
			<< (LPCTSTR)szFootRight
			<< "</td>" << endl
			<< "</table>" << endl
			
			<< "<p><hr>" << endl
			<< "<b>FmtFile Infomation</b><br>" << endl
			<< "<ul>" << endl
			<< "\t<li>ODBC: " << (LPCTSTR)m_pDoc->m_szODBCLink << "<br>" << endl
			<< "\t<li>SQL : " << (LPCTSTR)m_pDoc->m_szSQL
			<< "</ul>" << endl
			<< "</body>" << endl
			<< "</html>" << endl;
		
		if (m_pDoc->GetHWnd())
			::SendMessage(m_pDoc->GetHWnd(), WM_DESTROYPROGRESS, 0, 0);
		
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
		
		ShowMessage(m_pDoc->GetHWnd(), csError);

		edb->Delete();
		bRet = FALSE;
	}
	catch(...)
	{
		ShowMessage(m_pDoc->GetHWnd(), _T("无法获得数据！"));
		bRet = FALSE;
	}

	db.Close();

	return bRet;
}

// make a picture file
CString CEdRptExport::GetPicFile(CLongBinary* pVar, UINT nCounter)
{
	if (pVar->m_dwDataLength <= 0)
		return _T("");
	
	HGLOBAL hGlobal = NULL;
	CFile	fileImage;
	CString szName;
	
	try
	{	
		BYTE* buffer = (BYTE*)GlobalLock(pVar->m_hData);

		szName.Format("z@%06d", nCounter);
		szName = m_szPath + szName;
		szName += GetPicExtName( (LPCTSTR) buffer);

		if (!fileImage.Open(szName, CFile::modeWrite | CFile::modeCreate))
			return _T("");
		
		fileImage.Write(buffer, pVar->m_dwDataLength);
		throw 0;
	}
	catch(int)
	{
		fileImage.Close();
		GlobalUnlock(pVar->m_hData);
	}

	nCounter++;	
	return szName;
}

LPCTSTR CEdRptExport::GetPicExtName(LPCTSTR szTypeFlag)
{
	if (strncmp(szTypeFlag, "GIF89a", 6) == 0)
		return _T(".gif");
	else if (strncmp(szTypeFlag, "BM", 2) == 0)
		return _T(".bmp");
	else if (strncmp(szTypeFlag, "II", 2) == 0)
		return _T(".tif");
	else if (strncmp(szTypeFlag + 1, "png", 3) == 0)
		return _T(".png");
	else if (strncmp(szTypeFlag + 6, "JFIF", 4) == 0)
		return _T(".jpg");
	else
		return _T(".bin");
}

VOID CEdRptExport::DeletePathFile(CString strPath)
{
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strPath);
	CString strFilename;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		DeleteFile(finder.GetFilePath());
	}
}

VOID CEdRptExport::TxtToHtml(CString &str)
{
	str.Replace(_T("&"), _T("&amp;"));	// the first &
	str.Replace(_T(" "), _T("&nbsp;"));
	str.Replace(_T("@"), _T("&copy;"));
	str.Replace(_T("\""), _T("&quot;"));
	str.Replace(_T("<"), _T("&lt;"));
	str.Replace(_T(">"), _T("&gt;"));
	str.Replace(_T("\r\n"), _T("<br>"));
	str.Replace(_T("\n"), _T("<br>"));
	
	if (str.IsEmpty())
		str = _T("&nbsp;");
}

//// Importing //////////////////////////////////////////////////////////
BOOL CEdRptExport::DoImporting()
{
	if (!m_pImPrepare(m_szExpName, m_szImDir))
		return FALSE;
	
	m_pImBegin();
	m_pImport();
	m_pImEnd();
	return TRUE;
}

#include "DlgImport.h"
BOOL CEdRptExport::OnPrepareImporting(LPCSTR szExpName, LPCSTR szImDir)
{
	m_szExpName = szExpName;
	m_szImDir = szImDir;

	if ((m_szExpName.IsEmpty() || m_szImDir.IsEmpty()) && m_pDoc->GetHWnd()) 
	{
		CDlgImport dlg;
		if (dlg.DoModal() != IDOK)
			return FALSE;
		m_szExpName = dlg.m_szFile;
		m_szImDir = dlg.m_szDir;
	}
	else
	{
		ASSERT("无视必须给出szExpName和szImDir信息。");
	}
	
	CString m_szTmpFile;
	CZipArchive m_Zip;

	// modify file head
	TCHAR tmpPath[MAX_PATH];
	GetTempPath(MAX_PATH, tmpPath);
	m_szTmpFile = tmpPath + CString(_T("export.bsexim"));
	
	if (!CopyFile(m_szExpName, m_szTmpFile, FALSE))
		return FALSE;

	try
	{
		FILE *fp = fopen(m_szTmpFile, "r+");
		if (fp == NULL)
		{
			ShowMessage(m_pDoc->GetHWnd(), "无法打开文件 %s", m_szExpName);
			throw 0;
		}
		
		char ch[2];
		ch[0] = fgetc(fp);
		ch[1] = fgetc(fp);
		
		if (ch[0] != 'b' || ch[1] != 's')
		{
			ShowMessage(m_pDoc->GetHWnd(), "文件 %s 不是使用BSRpter的默认方式保存的", m_szExpName);
			throw 1;
		}
	
		rewind(fp);
		fputc('P', fp);
		fputc('K', fp);
		fclose(fp);

		m_Zip.Open(m_szTmpFile, CZipArchive::openReadOnly);
		m_Zip.SetPassword(PASSWORD);
	}
	catch (...)
	{
		DeleteFile(m_szTmpFile);
		return FALSE;
	}
	
	for(int i = 0; m_Zip.ExtractFile(i, m_szImDir, FALSE); i++);
	
	m_Zip.Close();
	DeleteFile(m_szTmpFile);	
	
	return TRUE;
}
