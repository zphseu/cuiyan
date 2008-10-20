// EdStatDoc.cpp : implementation file
//

#include "stdafx.h"
#include "EdStatDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "GraphData.h"
#include "resource.h"

#define LINECELL 6
/////////////////////////////////////////////////////////////////////////////
// CEdStatDoc

CEdStatDoc::CEdStatDoc()
{
	m_bLoaded = FALSE;
	m_szNames = NULL;
	m_fValues = NULL;
	m_szGpNames = NULL;
	m_pColInfo = NULL;
	m_nCols = 0;
	m_nRows = 0;
}

CEdStatDoc::~CEdStatDoc()
{
	Clear();
	delete []m_pColInfo;
}

/////////////////////////////////////////////////////////////////////////////
// CEdStatDoc commands
void CEdStatDoc::SetCutPie(BOOL bCutPie)
{
	string s = " " ;
	m_Graph.CutPie(m_fValues, m_nRows, m_szNames, &s, bCutPie ? true : false);
}

BOOL CEdStatDoc::GetData()
{
	try {
		if (!m_Templ.LoadFrom())
			throw _T("δ�ܼ���ģ���ļ���");

		Clear();
		
		if (m_Templ.nCols > 0 && m_Templ.nRows > 0)
		{
			m_nRows = m_Templ.nRows;
			m_nCols = m_Templ.nCols;
			m_fValues = new double[m_nRows * m_nCols];
			
			for (int i = 0; i < m_nRows * m_nCols; i++)
				m_fValues[i] = m_Templ.arData[i];
			
			m_szGpNames = new string[m_nCols + 1];
			
			for (i = 0; i < m_nCols + 1; i++)
				m_szGpNames[i] = m_Templ.arColsName[i];
			
			m_szNames = new string[m_nRows];
			for (i = 0; i < m_nRows; i++)
				m_szNames[i] = m_Templ.arRowsName[i];			
		}
		else
		{
			CDatabase db;
			if (!db.OpenEx(m_Templ.szODBC, CDatabase::openReadOnly))
				throw _T("û�и������ݿ�ָ�룬Ҳû��ָ�������֣�");
			
			if (m_Templ.type != CEdStatTpl::non)
				GetTimeData(db);
			else 
			{
				if (!GetMultiData(db))
					throw -1;
			}
		}

		m_szTitle = m_Templ.szTitle;
		m_Graph.SetUint(m_Templ.szVerUint, m_Templ.szHorUint);		
		m_Graph.Title(m_szTitle);
		m_Graph.SetData(m_fValues, m_nCols, m_nRows, m_szGpNames + 1, m_szNames);
		SetReportData();		
		
		m_bLoaded = TRUE;

	} catch (LPCSTR szMsg) {
		Clear();
		::MessageBox(NULL, szMsg, "����ͨ��ͳ�����", MB_OK);
	} catch (CDBException *e) {
		e->ReportError();
		e->Delete();
		Clear();
	} catch (...) {
		::MessageBox(NULL, "�쳣�����޷�������ݣ�", "����ͨ��ͳ�����", MB_OK);
		Clear();
	}
	
	return m_bLoaded;
}

void CEdStatDoc::SetSize()
{
	// m_nRows has set in GetSQL
	if (m_nCols <= 0 )
		throw _T("��ѯû�����ݣ�");
	
	if (m_nRows < 2) //m_nRowsΪ1ʱҲ���ִ���
		throw _T("��������С��1�������SQL�����SQL��");
	
	m_szGpNames = new string[m_nCols + 1];
	m_szNames = new string[m_nRows];
	m_fValues = new double [m_nCols * m_nRows];
	
	if (!m_fValues || !m_szGpNames || !m_szNames) 
		throw _T("�ڴ����⣬�޷��������ݣ�");

	ZeroMemory(m_fValues, sizeof(float) * m_nRows * m_nCols);
}

void CEdStatDoc::SetReportData()
{
	try
	{
		m_Report.SetCompanyName(m_szTitle);
		
		CString szWhere = m_Templ.szTextWhere;
		if (!szWhere.IsEmpty())
			szWhere = _T("��ѯ������") + szWhere;

		m_Report.SetReportTitle(szWhere);
		m_Report.m_ReportDate = m_szFootLeft;
		
		m_Report.DoCleanup();
		m_Report.Start();
		
		delete [] m_pColInfo;
		int nCurCols = (m_Templ.bRightSum) ? m_nCols + 1 : m_nCols;

		m_pColInfo = new CEasyReport::CColInfo [nCurCols + 1];
		
		if (m_pColInfo == NULL)
			throw _T("CColInfoû�����ɣ��ڴ����⣡");

		const int nMAXWIDTH = 77; //�������в��Է������Ϊ73���ַ���
		m_Templ.szColWidth.TrimLeft();
		m_Templ.szColWidth.TrimRight();
		int nCols = 0;

		if (m_Templ.szColWidth.IsEmpty())
		{
			const int nHead = 13;
			const int nCell = 10;
			nCols = (nMAXWIDTH - nHead) / nCell;
			if (nCurCols <= nCols)
				nCols = nCurCols;
			else
				::MessageBox(NULL, "�����ʾ��������!", "", MB_OK);
			
			m_pColInfo[0].m_CharCount = nHead;
			
			for (int i = 1; i < nCols + 1; i++)
				m_pColInfo[i].m_CharCount = nCell;
		}
		else
		{
#define		MAX_COLNUM	100
			int nWidths[MAX_COLNUM];

			CString csTmp(m_Templ.szColWidth), csWidth;
			csTmp.TrimLeft(";");
			csTmp += ";";
			int nFind = csTmp.Find(";");
			for (int i = 0; nFind > 0 && i < nCurCols + 1 && i < MAX_COLNUM; i++)
			{
				csWidth = csTmp.Left(nFind);
				csTmp.Delete(0, nFind+1);
				nWidths[i] = atoi(csWidth);
				nCols++;
			}

			int nTmp = nMAXWIDTH;
			for (i = 0; i < nCols && nTmp > 0; i++)
				nTmp -= nWidths[i];
			nCols = i - 1;

			if (nTmp < 0)
				nWidths[nCols] += nTmp;

			for (i = 0; i < nCols + 1; i++)
				m_pColInfo[i].m_CharCount = nWidths[i];
		}

		m_pColInfo[0].m_Heading = m_szGpNames[0].c_str();
		m_pColInfo[0].m_align = CEasyReport::CColInfo::eLeft;

		int nTmp = nCols + 1;
		if (m_Templ.bRightSum)
		{
			m_pColInfo[nCols].m_Heading = "�ܼ�";
			m_pColInfo[nCols].m_align = CEasyReport::CColInfo::eRight;
			nTmp = nCols;
		}

		for (int i = 1; i < nTmp; i++)
		{
			m_pColInfo[i].m_Heading = m_szGpNames[i].c_str();
			m_pColInfo[i].m_align = CEasyReport::CColInfo::eRight;
		}
		
		m_Report.SetDataCols(m_pColInfo, nCols + 1);
		CString str;
		double fFootSum[MAX_COLNUM];
		ZeroMemory(fFootSum, sizeof(fFootSum));
		for (i = 0; i < m_nRows; i++)
		{
			m_Report.AtTab(0, m_szNames[i].c_str());

			double fRightSum = 0;
			for (int j = 1; j < nTmp; j++)
			{
				double f = m_fValues[(j - 1) * m_nRows + i];
				fFootSum[j-1] += f;
				fRightSum += f;

				if (fabs(f) > 0.0001)
					str.Format(m_Templ.szFormat, f);
				else
					str.Format(m_Templ.szFormat, 0);

				m_Report.AtTab(j, str);
			}

			if (m_Templ.bRightSum)
			{
				str.Format(m_Templ.szFormat, fRightSum);
				m_Report.AtTab(j, str);
				fFootSum[j-1]+= fRightSum;
			}
			
			m_Report.NextRow();
		}

		if (m_Templ.bFootSum)
		{
			m_Report.AtTab(0, "�ϼ�");

			for (int j = 0; j < nTmp - 1; j++)
			{
				if (fabs(fFootSum[j]) > 0.0001)
					str.Format(m_Templ.szFormat, fFootSum[j]);
				else
					str.Format(m_Templ.szFormat, 0);
				
				m_Report.AtTab(j+1, str);				
			}
			
			if (m_Templ.bRightSum)
			{
				str.Format(m_Templ.szFormat, fFootSum[j]);
				m_Report.AtTab(j+1, str);
			}
		}
		
	} catch (const char *szMsg) {
		::MessageBox(NULL, szMsg, "", MB_OK);
		m_Report.End();
		return;
	} catch (...) {
		::MessageBox(NULL, "�쳣�����޷����ñ���������ݣ�", "����ͨ��ͳ�����", MB_OK);
	}

	m_Report.End();		// close report
	m_Report.GotoPage(0);	
}

int CEdStatDoc::Clear()
{
	m_bLoaded = FALSE;

	delete [] m_szNames;
	m_szNames = NULL;
	delete [] m_fValues;
	m_fValues = NULL;
	delete [] m_szGpNames;
	m_szGpNames = NULL;
	m_nCols = 0;
	m_nRows = 0;
	m_szTitle = _T("");
	m_szFootLeft = _T("");
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// ����±��ȡ�
//////////////////////////////////////////////////////////////////////////
void CEdStatDoc::GetTimeData(CDatabase &db)
{
	CString szSQL = GetTimeSQL();	// set m_nCols, m_nRows and SQL
	SetSize();

	CRecordset rc(&db);
	rc.Open(CRecordset::snapshot, szSQL);
	m_nCols = rc.GetODBCFieldCount() - 1;
	
	int nStart = 1; //Сʱ����ʼΪ�㣬���µ���ʼΪ1��
	switch(m_Templ.type) {
	case CEdStatTpl::day:
		m_szGpNames[0] = "ʱ";
		nStart = 0;
		break;
	case CEdStatTpl::month:
		m_szGpNames[0] = "��";
		break;
	case CEdStatTpl::year:
		m_szGpNames[0] = "��";
		break;
	default:
		m_szGpNames[0] = " ";
	}
	
	m_szGpNames[1] = "�ܼ�";

	// get name and value
	CString value;
	for (int i = 0; i < m_nRows; i++)
	{	
		value.Format("%d", i + nStart);
		m_szNames[i] = value;
	}
	
	while (!rc.IsEOF()) 
	{
		rc.GetFieldValue(short(0), value);
		int x = atoi(value);
		for (short j = 0; j < m_nCols; j++)
		{
			rc.GetFieldValue(j + 1, value);
			m_fValues[( x - nStart ) * m_nCols + j] += (float)atof(value);
		}
		
		rc.MoveNext();
	}
}

CString CEdStatDoc::GetTimeSQL()
{
	CString szSQL, szTmp, szTmFlag, szTmWhere;
	
	m_nCols = 1;
	m_Templ.szVerUint = _T("��");
	switch(m_Templ.type) 
	{
	case CEdStatTpl::day : 
		m_nRows = 24;
		szTmFlag = _T("HH24");
		m_szFootLeft.Format("%4d��%2d��%2d�� ͳ���ձ�", m_Templ.tmTime.GetYear(), 
			m_Templ.tmTime.GetMonth(), m_Templ.tmTime.GetDay());
		
		szTmWhere.Format(" where to_char(%s, 'YYYYMMDD') = '%04d%02d%02d' ", 
			m_Templ.szField, m_Templ.tmTime.GetYear(), m_Templ.tmTime.GetMonth(),
			m_Templ.tmTime.GetDay() );
		m_Templ.szHorUint = _T("ʱ");
		break;

	case CEdStatTpl::month :
		m_nRows = GetMonthDays(m_Templ.tmTime);
		szTmFlag = _T("DD");
		m_szFootLeft.Format("%4d��%2d�� ͳ���±�", m_Templ.tmTime.GetYear(), 
			m_Templ.tmTime.GetMonth());
		
		szTmWhere.Format(" where to_char(%s, 'YYYYMM') = '%04d%02d' ", 
			m_Templ.szField, m_Templ.tmTime.GetYear(), m_Templ.tmTime.GetMonth() );
		m_Templ.szHorUint = _T("��");
		break;
	
	case CEdStatTpl::year :
		m_nRows = 12;
		szTmFlag = _T("MM");
		m_szFootLeft.Format("%4d�� ͳ���걨", m_Templ.tmTime.GetYear());
		szTmWhere.Format(" where to_char(%s, 'YYYY') = '%04d' ", 
			m_Templ.szField, m_Templ.tmTime.GetYear() );
		m_Templ.szHorUint = _T("��");
		break;
	default: // tagTempl::non
		throw _T("��Чͳ�����ͣ�");
	}	
	
	m_Templ.szWhere.TrimLeft();
	m_Templ.szWhere.TrimRight();
	if (!m_Templ.szWhere.IsEmpty())
		szTmWhere += _T(" AND ") + m_Templ.szWhere;
	
	szTmp.LoadString(IDS_TIMESTAT_SQL);
	szSQL.Format(szTmp, m_Templ.szField, szTmFlag, m_Templ.szTable, 
		szTmWhere, m_Templ.szField, szTmFlag);

	return szSQL;
}

int CEdStatDoc::GetMonthDays(CTime tm)
{
	CTime tmNextMonthDay(tm.GetYear(), tm.GetMonth() + 1, tm.GetDay(), 
		tm.GetHour(), tm.GetMinute(), tm.GetSecond());
	
	CTimeSpan tms = tmNextMonthDay - tm;
	
	return (int)tms.GetDays();
}

BOOL CEdStatDoc::GetMultiData(CDatabase &db)
{
	if (m_Templ.szSQL.IsEmpty())
		throw _T("û�и��������ݲ�ѯSQL��");

	CRecordset rc(&db);
	if (!rc.Open(CRecordset::snapshot, m_Templ.szSQL))
		throw _T("��Ч����SQL������!");

	BOOL bNoRecord = rc.IsEOF();

	bool bGroup = false;
	LPCSTR szFLAG = _T("edson:");
	
	//////////////////////////////////////////////////////////////////////////
	// ��÷�����
	if (m_Templ.szGroupSQL.Left((int)_tcslen(szFLAG)).CompareNoCase(szFLAG) == 0) // ʱ������
	{
		
		bGroup = true;
		CString csStr = m_Templ.szGroupSQL;
		csStr.Delete(0, (int)_tcslen(szFLAG));
		
		CStringArray arGroup;
		GetCSArray(csStr, arGroup);
		m_nCols = (int)arGroup.GetSize() - 1;
		
		m_szGpNames = new string [m_nCols + 1];
		for (int i = 0; i < m_nCols + 1; i++)
			m_szGpNames[i] = arGroup[i];
	}
	else if (!m_Templ.szGroupSQL.IsEmpty()) // default group, no change
	{
		CRecordset rcy(&db);
		if (!rcy.Open(CRecordset::snapshot, m_Templ.szGroupSQL))
			throw _T("��Ч����SQL������!");
		
		bGroup = true;
		for (m_nCols = 0; !rcy.IsEOF(); m_nCols++)
			rcy.MoveNext();
		
		if (m_nCols <= 0)
			throw _T("��Ϣ����Ϊ�㣬��������SQL��");

		m_szGpNames = new string [m_nCols + 1];
		if (!m_szGpNames)
			throw _T("�ڴ����⣬�޷��������ݣ�");

		CODBCFieldInfo fi;
		rc.GetODBCFieldInfo(short(0), fi);
		m_szGpNames[0] = fi.m_strName;

		CString strValue;
		rcy.MoveFirst();
		for (int i = 0; i < m_nCols && !rcy.IsEOF(); i++)
		{
			rcy.GetFieldValue(short(0), strValue);
			m_szGpNames[i + 1] = strValue;
			rcy.MoveNext();
		}
		
		rcy.Close();
	}
	else
	{
		m_nCols = rc.GetODBCFieldCount() - 1;
		m_szGpNames = new string [m_nCols + 1];
		if (!m_szGpNames)
			throw _T("�ڴ����⣬�޷��������ݣ�");

		bGroup = false;

		// ��÷�������
		CODBCFieldInfo fi;
		for(int i = 0; i < m_nCols + 1; i++)
		{
			CODBCFieldInfo fi;
			rc.GetODBCFieldInfo(i, fi);
			m_szGpNames[i] = fi.m_strName;		
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// 
	CStringArray pCompName;
	
	if (m_Templ.szPointSQL.Left((int)_tcslen(szFLAG)).CompareNoCase(szFLAG) == 0) // ʱ������
	{
		CString szPointSQL = m_Templ.szPointSQL;
		szPointSQL.Delete(0, (int)_tcslen(szFLAG));
		
		GetCSArray(szPointSQL, pCompName);
		m_nRows = (int)pCompName.GetSize();
		
		m_szNames = new string [m_nRows];
		for (int i = 0; i < m_nRows; i++)
			m_szNames[i] = pCompName[i];
	}
	else if (!m_Templ.szPointSQL.IsEmpty())	//default, no change;
	{
		CRecordset rcx(&db), *pRcx = &rc;
		
		if (bGroup && m_Templ.szPointSQL.IsEmpty())
			throw _T("�������ָ�����SQL������!");
		
		if (!m_Templ.szPointSQL.IsEmpty())
		{
			if (!rcx.Open(CRecordset::snapshot, m_Templ.szPointSQL))
				throw _T("��Ч���SQL������!");
			pRcx = &rcx;
		}
		
		for (m_nRows = 0; !pRcx->IsEOF(); m_nRows++)
			pRcx->MoveNext();
		
		if (m_nRows < 2)	//Ϊ1ʱҲ���ִ���
			throw _T("��������С��1�������SQL�����SQL��");
		
		m_szNames = new string [m_nRows];
		pCompName.SetSize(m_nRows);
		if (!m_szNames)
			throw _T("�ڴ����⣬�޷��������ݣ�");
		
		CString strValue;
		pRcx->MoveFirst();
		
		// ����Ƿ���rcx�а��������������Ϣ��
		BOOL bName2Col =  rcx.IsOpen() && rcx.GetODBCFieldCount() > 1;
		
		for (int i = 0; i < m_nRows && !pRcx->IsEOF(); i++)
		{
			pRcx->GetFieldValue(short(0), strValue);
			pCompName[i] = strValue;
			
			if (bName2Col)
			{
				pRcx->GetFieldValue(short(1), strValue);
				m_szNames[i] = strValue;
			}
			else
				m_szNames[i] = strValue;
			
			pRcx->MoveNext();
		}
		
		if (rcx.IsOpen())
			rcx.Close();
	}
	//////////////////////////////////////////////////////////////////////////
	// �������

	//cycyc [20031014]
	if (m_nRows == 0 || m_nCols == 0)
		return FALSE;

	m_fValues = new double [m_nRows * m_nCols];
	if (!m_fValues)
		throw _T("�ڴ����⣬�޷��������ݣ�");
	ZeroMemory(m_fValues, sizeof(float) * m_nRows * m_nCols);

	// �Ȼ��CMap��Ϊ�˸���Ĳ�ѯ
	CMapStringToString mapy(m_nRows);
	CString strValue;
	for (int i = 0; i < m_nRows; i++)
	{
		strValue.Format("%d", i);
		mapy.SetAt(pCompName[i], strValue);
	}
	
	if (!bNoRecord)
		rc.MoveFirst();
	
	if (bGroup)
	{
		CMapStringToString mapx(m_nCols);
		for (i = 0; i < m_nCols; i++)
		{
			strValue.Format("%d", i);
			mapx.SetAt(m_szGpNames[i + 1].c_str(), strValue);
		}

		if (rc.GetODBCFieldCount() < 3)
			throw _T("��Ч����SQL��ʹ�÷��鷽ʽ���ֶ���С��3������!");
		
		while (!rc.IsEOF())
		{
			CString sx, sy, sxInt, syInt;
			rc.GetFieldValue(short(0), sy);
			rc.GetFieldValue(short(1), sx);
			rc.GetFieldValue(short(2), strValue);
			mapy.Lookup(sy, syInt);
			mapx.Lookup(sx, sxInt);

			if (!syInt.IsEmpty() && !sxInt.IsEmpty())
			{
				int x = atoi(sxInt);
				int y = atoi(syInt);
				m_fValues[x * m_nRows + y] = atof(strValue);
			}
			
			rc.MoveNext();
		}			
	}
	else
	{
		while(!rc.IsEOF()) 
		{
			CString s, sInt;
			rc.GetFieldValue(short(0), s);
			mapy.Lookup(s, sInt);
			int x = atoi(sInt);
			if (x < m_nRows && !sInt.IsEmpty())
			{
				for (short j = 1; j < m_nCols + 1; j++)
				{
					rc.GetFieldValue(j, strValue);
					m_fValues[(j - 1) * m_nRows + x] += atof(strValue);
				}
			}
			
			rc.MoveNext();
		}
	}

	rc.Close();

	m_szFootLeft = m_Templ.szFootTitle;
	return TRUE;
}


void CEdStatDoc::GetCSArray(CString csStr, CStringArray &arStr)
{
	csStr.TrimLeft();
	csStr.TrimRight(";");
	
	CString csTmp;
	while(csStr.Find(';') >= 0)
	{
		csTmp = csStr.Left(csStr.Find(';'));
		csStr.Delete(0, csTmp.GetLength() + 1);
		if (!csTmp.IsEmpty())
			arStr.Add(csTmp);
	}
	
	if (!csStr.IsEmpty())
		arStr.Add(csStr);
}

