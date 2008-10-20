// Template.cpp: implementation of the CEdStatTpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdStatTpl.h"
#include "iniFile.h"

#define COMMON _T("COMMON")
#define TIME _T("TIME")
#define DATABASE _T("DATABASE")
#define DATA _T("DATA")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdStatTpl::CEdStatTpl()
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
BOOL CEdStatTpl::LoadFrom(LPCSTR lpszFileName)
{
	SetDefault();

	BOOL bRet = TRUE;

	CIniFile f;
	try
	{
		if (!f.OpenIniFileForRead(lpszFileName ? lpszFileName : GetDefName()))
			return FALSE;

		// get [COMMON]
		f.GetItemString(COMMON, _T("Title"),	szTitle);
		f.GetItemString(COMMON, _T("ODBC"),		szODBC);
		f.GetItemString(COMMON, _T("Format"),	szFormat);
		f.GetItemString(COMMON, _T("ColWidth"), szColWidth);
		f.GetItemString(COMMON, _T("VerUint"),	szVerUint);
		f.GetItemString(COMMON, _T("HorUint"),	szHorUint);
		f.GetItemString(COMMON, _T("FootTitle"),szFootTitle);
		f.GetItemString(COMMON, _T("Where"),	szWhere);
		f.GetItemString(COMMON, _T("TextWhere"),szTextWhere);
		f.GetItemInt(COMMON,	_T("FootSum"),	bFootSum);
		f.GetItemInt(COMMON,	_T("RightSum"), bRightSum);
		
		if (szFormat.IsEmpty())
			szFormat = _T("%10.2f");
		else
		{
			double f = atof(szFormat);
			szFormat.Format("%8.1ff", f);
			szFormat.TrimLeft();
			szFormat.TrimRight();
			szFormat = _T("%") + szFormat;
		}

		// get [DATA]
		f.GetItemInt(DATA, _T("RowNum"), nRows);
		f.GetItemInt(DATA, _T("ColNum"), nCols);
		if (nRows > 0 && nCols > 0)
		{
			CString csTmp, csValue;
			for (int i = 0; i < nRows; i++)
			{
				csTmp.Format(_T("RowName%d"), i);
				f.GetItemString(DATA, csTmp, csValue);
				arRowsName.Add(csValue);
			}
			
			for (i = 0; i < nCols + 1; i++)
			{
				csTmp.Format(_T("ColName%d"), i);
				f.GetItemString(DATA, csTmp, csValue);
				arColsName.Add(csValue);
			}
			
			float fTmp;
			for (i = 0; i < nCols; i++)
			{
				for (int j = 0; j < nRows; j++)
				{
					csTmp.Format(_T("Data(%d/%d)"), j, i);
					f.GetItemString(DATA, csTmp, csValue);
					fTmp = (float) atof (csValue);
					arData.Add(fTmp);
				}
			}
		}
		
		// get [TIME]
		int nTime = (int)tmTime.GetTime();
		f.GetItemInt(TIME, _T("Type"), (int&)type);
		f.GetItemString(TIME, _T("Table"), szTable);
		f.GetItemString(TIME, _T("Field"), szField);
		
		COleDateTime tm;
		CString szTime;
		f.GetItemString(TIME, _T("Time"), szTime);
		tmTime = CTime::GetCurrentTime();
		
		if (!szTime.IsEmpty())
		{
			tm.ParseDateTime(szTime, VAR_DATEVALUEONLY);
		
			if (tm.GetYear() >= 1970 && tm.GetYear() <= 2038 &&
				tm.GetMonth() >= 1 && tm.GetMonth() <= 12 && tm.GetDay() >= 1 && tm.GetDay() <= 31)
				tmTime = CTime(tm.GetYear(), tm.GetMonth(), tm.GetDay(), 0, 0, 0);
		}

		// get [DATABASE]
		f.GetItemString(DATABASE, _T("DataSQL"),	szSQL);
		f.GetItemString(DATABASE, _T("PointSQL"),	szPointSQL);
		f.GetItemString(DATABASE, _T("GroupSQL"),	szGroupSQL);
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
BOOL CEdStatTpl::SaveTo(LPCSTR lpszFileName)
{
	BOOL bRet = TRUE;
	
	CIniFile f;
	try
	{
		if (!f.OpenIniFileForWrite(lpszFileName ? lpszFileName : GetDefName()))
			return FALSE;
		
		// set [COMMON]
		f.WriteSection(COMMON);
		f.WriteItemString(_T("Title"),	szTitle);
		f.WriteItemString(_T("ODBC"),	szODBC);
		f.WriteItemString(_T("ColWidth"),szColWidth);
		f.WriteItemString(_T("VerUint"),szVerUint);
		f.WriteItemString(_T("HorUint"),szHorUint);
		f.WriteItemString(_T("FootTitle"),szFootTitle);
		f.WriteItemString(_T("Where"),	szWhere);
		f.WriteItemString(_T("TextWhere"),szTextWhere);
		f.WriteItemInt(_T("FootSum"),	bFootSum);
		f.WriteItemInt(_T("RightSum"), bRightSum);
		
		CString csTmp(szFormat);
		szFormat.TrimLeft("%");
		double d = atof(szFormat);
		csTmp.Format("%8.1f", d);
		csTmp.TrimLeft();
		f.WriteItemString(_T("Format"),	csTmp);
		
		// set [DATA]
		f.WriteString("\n\r");
		f.WriteSection(DATA);
		f.WriteItemInt(_T("RowNum"), nRows);
		f.WriteItemInt(_T("ColNum"), nCols);
		if (nRows > 0 && nCols > 0)
		{
			CString csTmp;
			for (int i = 0; i < nRows; i++)
			{
				csTmp.Format(_T("RowName%d"), i);
				f.WriteItemString(csTmp, arRowsName[i]);
			}
			
			for (i = 0; i < nCols + 1; i++)
			{
				csTmp.Format(_T("ColName%d"), i);
				f.WriteItemString(csTmp, arColsName[i]);
			}
			
			CString csValue;
			for (i = 0; i < nCols; i++)
			{
				for (int j = 0; j < nRows; j++)
				{
					csTmp.Format(_T("Data[%d/%d]"), j, i);
					csValue.Format(_T("%f"), arData[nCols * i + j]);
					f.WriteItemString(csTmp, csValue);
				}
			}
		}
		
		// get [TIME]
		f.WriteString("\n\r");
		f.WriteSection(TIME);
		f.WriteItemInt(_T("Type"), (int&)type);
		f.WriteItemString(_T("Table"), szTable);
		f.WriteItemString(_T("Field"), szField);
		f.WriteItemString(_T("Time"), tmTime.Format("%Y/%m/%d"));
		
		// get [DATABASE]
		f.WriteString("\n\r");
		f.WriteSection(DATABASE);
		f.WriteItemString(_T("DataSQL"),	szSQL);
		f.WriteItemString(_T("PointSQL"),	szPointSQL);
		f.WriteItemString(_T("GroupSQL"),	szGroupSQL);
	}
	catch (...) 
	{
		bRet = FALSE;
	}
	
	f.CloseIniFile();
	return bRet;		
}

LPCTSTR CEdStatTpl::GetDefName()
{
	static TCHAR szTmpPath[MAX_PATH];
	GetTempPath(MAX_PATH, szTmpPath);
	strcat(szTmpPath, _T("GraphTm.fmt"));
	return szTmpPath;
}

void CEdStatTpl::SetDefault()
{
	//////////////////////////////////////////////////////////////////////////
	szTitle = "统计表名";
	szODBC = _T("");
	szFormat = _T("%10.2f");
	szColWidth = _T("13;10;10;10;10;10;10");
	bFootSum = FALSE;
	bRightSum = FALSE;
	szVerUint = _T("");
	szHorUint = _T("");	
	szFootTitle = _T("");
	szWhere = _T("");
	szTextWhere = _T("");

	//////////// 1 ///////////////////////////////////////////////////////
	arRowsName.RemoveAll();	
	arColsName.RemoveAll();
	arData.RemoveAll();
	nRows = 0;
	nCols = 0;

	///////////// 2 /////////////////////////////////////////////////////
	type = non;
	szTable = _T("");
	szField = _T("");
	tmTime = CTime::GetCurrentTime();

	///////////// 3 /////////////////////////////////////////////////////
	szSQL = _T("");
	szGroupSQL = _T("");	
	szPointSQL = _T("");
}
