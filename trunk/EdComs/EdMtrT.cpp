// EdMtrT.cpp: implementation of the CEdMtrT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdMtrT.h"
#include <fstream>

extern void TESTHR(HRESULT hr);
#define LINKSTR	_T(" #@!@# ")
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdMtrT::CEdMtrT()
{
}

CEdMtrT::~CEdMtrT()
{
	m_arstrRowNames.clear();
	m_arstrColNames.clear();
	m_ardData.clear();
}

double CEdMtrT::getData(long row, long col) const
{ 
	if (row < getRows()  && col < getCols())
		return m_ardData[row * getCols() + col];
	else
		return 0.0;
}

void CEdMtrT::setSize(long row, long col)
{ 
	m_ardData.resize(row * col, 0.0);
	m_arstrColNames.resize(col, _T(""));
	m_arstrRowNames.resize(row, _T(""));
}

string CEdMtrT::getRowName(long row) const
{
	return (row < getRows()) ? m_arstrRowNames[row] : _T("");
}

string CEdMtrT::getColName(long col) const
{
	return (col < getCols()) ? m_arstrColNames[col] : _T("");
}

void CEdMtrT::setRowName(long row, BSTR bstrRowName)
{
	if (row < getRows()) 
		m_arstrRowNames[row] = (LPCTSTR)(_bstr_t)bstrRowName;
}

void CEdMtrT::setColName(long col, BSTR bstrColName)
{
	if (col < getCols()) 
		m_arstrColNames[col] = (LPCTSTR)(_bstr_t)bstrColName;
}


void CEdMtrT::BreakStrName(BSTR bstrNames, names &ar)
{
	string s((LPCTSTR)(_bstr_t)bstrNames);
	ar.clear();
	
	if (s[s.length()] != _T(';'))
		s += _T(';');
	
	int iPos = 0, len = 0;
	TCHAR szNAME[MAX_PATH + 1];
	while ((iPos = s.find_first_of(_T(';'), 0)) > 0)	{
		len = (iPos > MAX_PATH)	? MAX_PATH : iPos;
		ZeroMemory(szNAME, sizeof(szNAME));
		s.copy(szNAME, len);
		s.erase(0, iPos + 1);
		ar.push_back(szNAME);
	}
	
	setSize(getRows(), getCols());	
}

void CEdMtrT::setRowNames(BSTR bstrRowNames)
{
	BreakStrName(bstrRowNames, m_arstrRowNames);
}

void CEdMtrT::setColNames(BSTR bstrColNames)
{
	BreakStrName(bstrColNames, m_arstrColNames);
}

void CEdMtrT::setData(long row, long col, double dData)
{
	if (row < getRows() && col < getCols())
		m_ardData[row * getCols() + col] = dData;
}

void CEdMtrT::MtrToMtrNums(CEdMtrS& mtr)
{
	m_sTitle = mtr.getData(0, 0);
	
	for (long i = 1; i < mtr.getCols(); i++)
		m_arstrColNames.push_back(mtr.getData(0, i));
	
	for (i = 1; i < mtr.getRows(); i++)
		m_arstrRowNames.push_back(mtr.getData(i, 0));
	
	LPTSTR pStop;
	for (i = 1; i < mtr.getRows(); i++)	{
		for (long j = 1; j < mtr.getCols(); j++)
			m_ardData.push_back(_tcstod(mtr.getData(i, j).c_str(), &pStop));
	}	
}

HRESULT CEdMtrT::readFile(BSTR bstrFileName, BSTR bstrTableName)
{
	CEdMtrS mtr;
	HRESULT hr = mtr.readFile(bstrFileName, bstrTableName);
	if (hr != S_OK)
		return hr;
	
	MtrToMtrNums(mtr);
	return S_OK;	
}

HRESULT CEdMtrT::readDB(BSTR bstrConnect, BSTR bstrDataSQL, BSTR bstrRowSQL, BSTR bstrColSQL)
{
	HRESULT bRet = 0;
	_ConnectionPtr pConnection = NULL;
	_RecordsetPtr pRecordset = NULL;
	
	try		{
		
		bRet = 1;	TESTHR(pConnection.CreateInstance(__uuidof(Connection)));
		bRet = 2;	TESTHR(pRecordset.CreateInstance(__uuidof(Recordset)));
		bRet = 3;	TESTHR(pConnection->Open(bstrConnect, _T(""), _T(""), adModeUnknown));

		//////////////////////////////////////////////////////////////////////////
		_bstr_t bstrTmp(bstrColSQL);
		if (bstrTmp.length() > 12)	{	//"SELECT FROM "
			bRet = 4;	TESTHR(pRecordset->Open(bstrColSQL, pConnection.GetInterfacePtr(), 
				adOpenForwardOnly, adLockReadOnly, adCmdText));
			
			_variant_t v;
			while (!pRecordset->adoEOF)		{
				v = pRecordset->Collect[0l];
				if (v.vt != VT_EMPTY && v.vt != VT_NULL)
					m_arstrColNames.push_back((LPCTSTR)(_bstr_t)v);
				pRecordset->MoveNext();
			}
			
			pRecordset->Close();
		}

		//////////////////////////////////////////////////////////////////////////
		bstrTmp = bstrRowSQL;
		if (bstrTmp.length() > 12)	{	//"SELECT FROM "
			bRet = 5;	TESTHR(pRecordset->Open(bstrRowSQL, pConnection.GetInterfacePtr(), 
				adOpenForwardOnly, adLockReadOnly, adCmdText));
			
			_variant_t v;
			while (!pRecordset->adoEOF)		{
				v = pRecordset->Collect[0l];
				if (v.vt != VT_EMPTY && v.vt != VT_NULL)
					m_arstrRowNames.push_back((LPCTSTR)(_bstr_t)v);
				pRecordset->MoveNext();
			}
			
			pRecordset->Close();
		}
		
		//////////////////////////////////////////////////////////////////////////
		datapairs mydata;
		namepairs mycol, myrow;
		bRet = 6;	TESTHR(pRecordset->Open(bstrDataSQL, pConnection.GetInterfacePtr(), 
			adOpenForwardOnly, adLockReadOnly, adCmdText));
		
		_variant_t vCol, vRow, vValue;
		long nRow = 0;
		long nCol = (pRecordset->Fields->Count > 2) ? 1 : -1;
		long nValue = (pRecordset->Fields->Count > 2) ? 2 : 1;
		_bstr_t sCol, sRow;
		TCHAR *pStop = NULL;

		while (!pRecordset->adoEOF)		{
			vRow = pRecordset->Collect[nRow];
			vValue = pRecordset->Collect[nValue];
			if (nCol > 0) vCol = pRecordset->Collect[nCol];

			if (vRow.vt == VT_EMPTY || vRow.vt == VT_NULL || 
				vValue.vt == VT_EMPTY || vValue.vt == VT_NULL ||
				vCol.vt == VT_NULL)
				continue;
			
			sRow = vRow;	sCol = vCol;
			mycol[(LPCTSTR)sCol] = 0;
			myrow[(LPCTSTR)sRow] = 0;
			mydata[(LPCTSTR)(sRow + LINKSTR + sCol)] = _tcstod((LPCTSTR)(_bstr_t)vValue, &pStop);
			
			pRecordset->MoveNext();
		}
		
		pRecordset->Close();

		//////////////////////////////////////////////////////////////////////////
		if (m_arstrColNames.size() == 0)	{
			long l = 0;
				for (namepairs::iterator _i = mycol.begin(); _i != mycol.end(); _i++)	{
					m_arstrColNames.push_back(_i->first);
					_i->second = l++;
				}
		}

		if (m_arstrRowNames.size() == 0)	{
			long l = 0;
			for (namepairs::iterator _i = myrow.begin(); _i != myrow.end(); _i++)	{
				m_arstrRowNames.push_back(_i->first);
				_i->second = l++;
			}
		}

		m_ardData.clear();
		for (long i = 0; i < getRows(); i++)	{
			for (long j = 0; j < getCols(); j++)
				m_ardData.push_back(mydata[ m_arstrRowNames[i] + LINKSTR + m_arstrColNames[j] ]);
		}

		bRet = S_OK;
	}	catch(...)	{
		;
	}
	
	if (pRecordset->State)
		pRecordset->Close();
	
	if(pConnection->State)
		pConnection->Close();
	
	if (bRet != S_OK)	{
		m_ardData.clear();
		m_arstrRowNames.clear();
		m_arstrColNames.clear();
	}
	
	return bRet;
}

HRESULT CEdMtrT::saveFile(BSTR bstrFileName)
{
	HRESULT hr = S_OK;

#ifndef _UNICODE
	ofstream ofs;

	try	{
		ofs.open((LPCSTR)(_bstr_t)bstrFileName);
		if (ofs.fail())
			throw (hr = 1);

		ofs << m_sTitle.c_str() << "\t";
		for (int i = 0; i < getCols(); i++)
			ofs << m_arstrColNames[i].c_str() << "\t";


		for (i = 0; i < getRows(); i++)
		{
			ofs << endl;
			ofs << m_arstrRowNames[i].c_str() << "\t";

			for (int j = 0; j < getCols(); j++)
				ofs << getData(i, j) <<  "\t";
		}

		hr = S_OK;
	}
	catch (...) {
		;
	}

	if (ofs.is_open())
		ofs.close();

#endif
	
	return hr;
}
