// Template.cpp: implementation of the CEdRptTpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdRptTpl.h"
#include "iniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define lpszCOMMON _T("COMMON")
#define lpszCOLFMT _T("COLFMT")
#define lpszDATA  _T("DATA")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CEdRptTpl::CEdRptTpl()
{
	SetDefault();
}

/**
 *  加在数据.
 *
 *  @return 如果成功，返回真.
 *
 *  @version  10/08/2003  cuiyan  Initial Version.
 */
BOOL CEdRptTpl::LoadFrom(LPCSTR lpszFileName)
{
	SetDefault();

	BOOL bRet = TRUE;

	CIniFile f;
	try
	{
		m_csFileName = lpszFileName ? lpszFileName : GetDefName();
		if (!f.OpenIniFileForRead(m_csFileName))
			return FALSE;

		// get [COMMON]
		f.GetItemString(lpszCOMMON, _T("Title"),		m_szTitle);
		f.GetItemString(lpszCOMMON, _T("ODBC"),			m_szODBCLink);
		f.GetItemString(lpszCOMMON, _T("DataSQL"),		m_szSQL);
		f.GetItemString(lpszCOMMON, _T("HeadRight"),	m_szHeadRight);
		f.GetItemString(lpszCOMMON, _T("FootRight"),	m_szFootRight);
		f.GetItemString(lpszCOMMON, _T("FootLeft"),		m_szFootLeft);
		f.GetItemInt   (lpszCOMMON,	_T("FirstColFixed"),m_bFirstColFixed);
		f.GetItemInt   (lpszCOMMON,	_T("DefaultPrint"), m_bDefaultPrint);
		f.GetItemInt   (lpszCOMMON,	_T("MaxRecordNum"), (int&)m_nMaxRecordNum);
		f.GetItemInt   (lpszCOMMON, _T("FootSum"),		m_bFootSum);

		if (m_nMaxRecordNum == 0)
			m_nMaxRecordNum = 1024;

		// get [COLFMT]
		int nColNum, nFind;
		COLFMT cf;
		CString csTmp, csValue;
		f.GetItemInt(lpszCOLFMT,	_T("ColNum"),	nColNum);
		for (int i = 0; i < nColNum; i++)
		{
			cf.width = 100;
			cf.format = _T("");
			cf.name = _T("");

			csTmp.Format("COLFMT%d", i);
			// get width
			f.GetItemString(lpszCOLFMT, csTmp, csValue);
			cf.width = atoi(csValue);
			// get name
			nFind = csValue.Find(";");
			if (nFind > 0)
			{
				csValue.Delete(0, csValue.Find(";") + 1);
				cf.name = csValue;
				nFind = csValue.Find(";");
				if (nFind > 0)
				{
					cf.name = csValue.Left(csValue.Find(";"));
					csValue.Delete(0, cf.name.GetLength() + 1);
					cf.format = csValue;
				}
			}
			m_ColFmt.Add(cf);
		}

		// get [DATA]
		f.GetItemInt(lpszDATA, _T("RowNum"), m_nRows);
		f.GetItemInt(lpszDATA, _T("ColNum"), m_nCols);
		for (i = 0; i < m_nRows; i++)
		{
			for (int j = 0; j < m_nCols; j++)
			{
				csTmp.Format(_T("Data(%d/%d)"), j, i);
				f.GetItemString(lpszDATA, csTmp, csValue);
				m_arData.Add(csValue);
			}
		}

	}
	catch (...) 
	{
		bRet = FALSE;
	}

	f.CloseIniFile();
	return bRet;
}


/**
 *  保存数据.
 *
 *  @return 如果成功，返回真.
 *
 *  @version  10/08/2003  cuiyan  Initial Version.
 */
BOOL CEdRptTpl::SaveTo(LPCSTR lpszFileName)
{
	BOOL bRet = TRUE;
	
	CIniFile f;
	try
	{
		if (!f.OpenIniFileForWrite(lpszFileName ? lpszFileName : GetDefName()))
			return FALSE;
		
		// set [COMMON]
		f.WriteSection(lpszCOMMON);
		f.WriteItemString(_T("Title"),		m_szTitle);
		f.WriteItemString(_T("ODBC"),		m_szODBCLink);
		f.WriteItemString(_T("DataSQL"),	m_szSQL);
		f.WriteItemString(_T("HeadRight"),	m_szHeadRight);
		f.WriteItemString(_T("FootRight"),	m_szFootRight);
		f.WriteItemString(_T("FootLeft"),	m_szFootLeft);
		f.WriteItemInt   (_T("FirstColFixed"),m_bFirstColFixed);
		f.WriteItemInt   (_T("DefaultPrint"), m_bDefaultPrint);
		f.WriteItemInt   (_T("MaxRecordNum"), m_nMaxRecordNum);
		
		// set [COLFMT]
		f.WriteString("\n\r");
		f.WriteSection(lpszCOLFMT);
		
		int nColNum = (int)m_ColFmt.GetSize();
		CString csTmp, csValue;
		f.WriteItemInt(_T("ColNum"),	nColNum);
		for (int i = 0; i < nColNum; i++)
		{
			csTmp.Format("COLFMT%d", i);
			csValue.Format("%d;%s;%s", m_ColFmt[i].width, m_ColFmt[i].name, m_ColFmt[i].format);
			f.WriteItemString(csTmp, csValue);
		}
		
		// get [DATA]
		f.WriteString("\n\r");
		f.WriteSection(lpszDATA);
		f.WriteItemInt(_T("RowNum"), m_nRows);
		f.WriteItemInt(_T("ColNum"), m_nCols);
		for (i = 0; i < m_nCols; i++)
		{
			for (int j = 0; j < m_nRows; j++)
			{
				csTmp.Format(_T("Data(%d/%d)"), j, i);
				f.WriteItemString(csTmp, m_arData[m_nCols * i + j]);
			}
		}
	}
	catch (...) 
	{
		bRet = FALSE;
	}
	
	f.CloseIniFile();
	return bRet;		
}

LPCTSTR CEdRptTpl::GetDefName()
{
	static TCHAR szTmpPath[MAX_PATH];
	GetTempPath(MAX_PATH, szTmpPath);
	strcat(szTmpPath, _T("PrintTm.fmt"));
	return szTmpPath;
}

void CEdRptTpl::SetDefault()
{
	m_szTitle = _T("");			/**<  打印的标题.  */
	m_szHeadRight = _T("");		/**<  打印的首注释.  */
	m_szFootRight = _T("");		/**<  打印的右脚注.  */
	m_szFootLeft = _T("");		/**<  打印的左脚注.  */
	m_szSQL = _T("");			/**<  查询SQL.  */
	m_szODBCLink = _T("");		/**<  数据库连接字.  */
	m_bFirstColFixed = TRUE;	/**<  首行是否固定变灰.  */
	m_bDefaultPrint = FALSE;	/**<  是否使用默认打印机.  */
	m_nMaxRecordNum = 1024;		/**<  设定的最大打印记录数.  */
	
	m_nRows = m_nCols = 0;
	m_ColFmt.RemoveAll();
	m_arData.RemoveAll();

}
