// EdMtrData.cpp : Implementation of CEdMtrData
#include "stdafx.h"
#include "EdComs.h"
#include "EdMtrData.h"
#include "EdFuncs.h"
/////////////////////////////////////////////////////////////////////////////
// CEdMtrData

STDMETHODIMP CEdMtrData::DoPrint(BSTR bstrPrinterName)
{
	if (m_lRows < 1)  return S_FALSE;
	
	CEdFuncs fun;
	HDC hDC = fun.GetPrintHDC((LPCTSTR)(_bstr_t)bstrPrinterName);
	if (NULL == hDC)
		return S_FALSE;
	
	print(hDC);
	return S_OK;
}

STDMETHODIMP CEdMtrData::get_Cols(long *pVal)
{
	*pVal = m_lCols;
	return S_OK;
}

STDMETHODIMP CEdMtrData::get_Rows(long *pVal)
{
	*pVal = m_lRows;
	return S_OK;
}

STDMETHODIMP CEdMtrData::ReadFile(BSTR bstrFileName, BSTR bstrTableName)
{
	return CEdMtrS::readFile(bstrFileName, bstrTableName);
}

STDMETHODIMP CEdMtrData::SetParams(BSTR bstrTitle, BSTR bstrHeadRight, BSTR bstrFootLeft, BSTR bstrFootRight, BSTR bstrFontName, BSTR bstrColsWidthStr, long lFixedCols)
{
	return CEdMtrS::setParams(bstrTitle, bstrHeadRight, bstrFootLeft, bstrFootRight, 
		bstrFontName, bstrColsWidthStr, lFixedCols);
}

STDMETHODIMP CEdMtrData::ReadDB(BSTR bstrConnect, BSTR bstrSQL)
{
	return CEdMtrS::readDB(bstrConnect, bstrSQL);
}

STDMETHODIMP CEdMtrData::get_Data(long row, long col, BSTR *pVal)
{
	*pVal = (_bstr_t)CEdMtrS::getData(row, col).c_str();
	return S_OK;
}

STDMETHODIMP CEdMtrData::put_Data(long row, long col, BSTR newVal)
{
	CEdMtrS::setData(row, col, newVal);
	return S_OK;
}

STDMETHODIMP CEdMtrData::SetSize(long row, long col)
{
	CEdMtrS::setSize(row, col);
	return S_OK;
}
