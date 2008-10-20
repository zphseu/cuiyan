// EdMtrT.h: interface for the CEdMtrT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDMTRT_H__D1B5DEB8_3705_43A1_8DAB_A48F610DFC8E__INCLUDED_)
#define AFX_EDMTRT_H__D1B5DEB8_3705_43A1_8DAB_A48F610DFC8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "EdMtrS.h"

#include <string>
#include <vector>
#include <map>

using namespace std;
#ifdef _UNICODE
#define string wstring
#endif


class CEdMtrT
{
public:
	CEdMtrT();
	virtual ~CEdMtrT();

protected:
	HRESULT saveFile(BSTR bstrFileName);
	void setRowNames(BSTR bstrRowNames);
	void setColNames(BSTR bstrColNames);
	void setRowName(long row, BSTR bstrRowName);
	void setColName(long col, BSTR bstrColName);
	string getRowName(long row) const;	
	string getColName(long col) const;

	HRESULT readDB (BSTR bstrConnect, BSTR bstrDataSQL, BSTR bstrRowSQL, BSTR bstrColSQL);
	HRESULT readFile(BSTR bstrFileName, BSTR bstrTableName);

	double	getData(long row, long col) const;
	long	getCols() const { return m_arstrColNames.size(); }
	long	getRows() const { return m_arstrRowNames.size(); }
	
	void	setSize(long row, long col);
	void	setData(long row, long col, double dData);
	
protected:
	typedef map<string, long>	namepairs;
	typedef map<string, double> datapairs;
	typedef vector<double>		matrixdata;
	typedef vector<string>		names;

	void BreakStrName(BSTR bstrNames, names& ar);
	void MtrToMtrNums(CEdMtrS& mtr);
	
	matrixdata	m_ardData;
	names		m_arstrColNames;
	names		m_arstrRowNames;
	string		m_sTitle;
};

#endif // !defined(AFX_EDMTRT_H__D1B5DEB8_3705_43A1_8DAB_A48F610DFC8E__INCLUDED_)
