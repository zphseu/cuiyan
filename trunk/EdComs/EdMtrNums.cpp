// EdMtrNums.cpp : Implementation of CEdMtrNums
#include "stdafx.h"
#include "EdComs.h"
#include "EdMtrNums.h"
#include "EdMtrData.h"

/////////////////////////////////////////////////////////////////////////////
// CEdMtrNums

STDMETHODIMP CEdMtrNums::ReadFile(BSTR bstrFileName, BSTR bstrTableName)
{
	return CEdMtrT::readFile(bstrFileName, bstrTableName);
}

STDMETHODIMP CEdMtrNums::ReadDB(BSTR bstrConnect, BSTR bstrDataSQL, BSTR bstrPointSQL, 
								BSTR bstrGroupSQL)
{
	return CEdMtrT::readDB(bstrConnect, bstrDataSQL, bstrPointSQL, bstrGroupSQL);
}

STDMETHODIMP CEdMtrNums::get_ColName(long col, BSTR *pVal)
{
	*pVal = (_bstr_t)CEdMtrT::getColName(col).c_str();
	return S_OK;
}

STDMETHODIMP CEdMtrNums::put_ColName(long col, BSTR newVal)
{
	CEdMtrT::setColName(col, newVal);
	return S_OK;
}

STDMETHODIMP CEdMtrNums::get_RowName(long row, BSTR *pVal)
{
	*pVal = (_bstr_t)CEdMtrT::getRowName(row).c_str();
	return S_OK;
}

STDMETHODIMP CEdMtrNums::put_RowName(long row, BSTR newVal)
{
	CEdMtrT::setRowName(row, newVal);
	return S_OK;
}

STDMETHODIMP CEdMtrNums::get_Data(long row, long col, double *pVal)
{
	*pVal = CEdMtrT::getData(row, col);
	return S_OK;
}

STDMETHODIMP CEdMtrNums::put_Data(long row, long col, double newVal)
{
	CEdMtrT::setData(row, col, newVal);
	return S_OK;
}

STDMETHODIMP CEdMtrNums::get_Cols(long *pVal)
{
	*pVal = CEdMtrT::getCols();
	return S_OK;
}

STDMETHODIMP CEdMtrNums::get_Rows(long *pVal)
{
	*pVal = CEdMtrT::getRows();
	return S_OK;
}

STDMETHODIMP CEdMtrNums::SetSize(long row, long col)
{
	CEdMtrT::setSize(row, col);
	return S_OK;
}

STDMETHODIMP CEdMtrNums::SetColNames(BSTR bstrColNames)
{
	CEdMtrT::setColNames(bstrColNames);
	return S_OK;
}

STDMETHODIMP CEdMtrNums::SetRowNames(BSTR bstrRowNames)
{
	CEdMtrT::setRowNames(bstrRowNames);
	return S_OK;
}

STDMETHODIMP CEdMtrNums::Save(BSTR bstrFileName)
{
	return CEdMtrT::saveFile(bstrFileName);
}
