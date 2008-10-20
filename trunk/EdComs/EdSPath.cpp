// EdSPath.cpp : Implementation of CEdSPath
#include "stdafx.h"
#include "EdComs.h"
#include "EdSPath.h"

/////////////////////////////////////////////////////////////////////////////
// CEdSPath

#include <sstream>
#include <iterator>
#include <fstream>
using namespace std;

#include <assert.h>
#include <comdef.h>

extern void TESTHR(HRESULT hr);

STDMETHODIMP CEdSPath::SetMapFile(BSTR mpfn)
{
	HRESULT hr = S_FALSE;
	_bstr_t bstr(mpfn);
	ifstream iof;
	
	try	{
		int nLinkNum, nNodeNum, nNonRLs, index;
		unsigned short op, dp, l1, l2;
		double w, x, y, z;
		
		iof.open(bstr);
		if (iof.fail())
			throw (-1);
		
		iof >> nLinkNum;
		for (int i = 0; i < nLinkNum && !iof.eof(); i++) {
			iof >> index >> op >> dp >> w;
			m_fmap.set_ilink(index, op, dp, w);
		}
		
		iof >> nNodeNum;
		for (i = 0; i < nNodeNum && !iof.eof(); i++) {
			iof >> index >> x >> y >> z;
		}
		
		iof >> nNonRLs;
		for (i = 0; i < nNonRLs && !iof.eof(); i++) {
			iof >> l1 >> l2;
			m_fmap.set_inrlk(l1, l2);
		}
		
		hr = S_OK;
	}
	catch (...) {
	}
	
	if (iof.is_open())
		iof.close();
	
	return hr;
}

STDMETHODIMP CEdSPath::GetLink(BSTR nds, unsigned int n, BSTR *pShortLink, BSTR *pShortNode)
{
	_bstr_t bstr(nds);
	_fgmap::ids lk, nd;
	int len = m_fmap.getshortpath(bstr, lk, nd);
	
#ifdef _DEMO
	int num = lk.size() / 10;
	for (int i = 0; i < num; i++)
	{
		int t = rand() % lk.size();
		lk.erase(lk.begin() + t);
		t = rand() % nd.size();
		nd.erase(nd.begin() + t);
	}
#endif
	
	if (len > 0 || len < fmap::max_v)
	{
		CComBSTR str1(_fgmap::ids2str(lk).c_str());
		CComBSTR str2(_fgmap::ids2str(nd).c_str());
		*pShortLink = str1.m_str;
		*pShortNode = str2.m_str;	
	}
	
	return len;
}


static TCHAR* pStop = NULL;
static inline long GETLONGFIELD(_RecordsetPtr& pRecordset, long l)
{	return _tcstol((LPCTSTR)(_bstr_t)pRecordset->Collect[l], &pStop, 10);	}

/**
 *  Read data from database.
 *
 *  @param  -[in]  LPCTSTR  strDbLk: [strDbLk]
 *  @param  -[in]  LPCTSTR  strLkSql: [strLkSql]
 *  @param  -[in]  LPCTSTR  strNdSql: [strNdSql]
 *  @param  -[in]  LPCTSTR  strNRl: [strNRl]
 *
 *  @return 0 - success.
 *  @return 1 - Connection can not be created.
 *  @return 2 - Recordset can not be created.
 *  @return 3 - Connection can not be opened.
 *  @return 4 - Link Recordset can not be opened.
 *  @return 5 - Node Recordset can not be opened.
 *  @return 6 - Link Relation Recordset can not be opened.
 *
 *  @version  07/10/2004  cuiyan  Initial Version.
 *
 */
STDMETHODIMP CEdSPath::SetMapDb(BSTR strDbLk, BSTR strLkSql, BSTR strNdSql, BSTR strNRl)
{
	HRESULT hr = S_FALSE;
	
	_ConnectionPtr pConnection = NULL;
	_RecordsetPtr pRecordset = NULL;
	try
	{
		hr = 1; TESTHR(pConnection.CreateInstance(__uuidof(Connection)));
		hr = 2;	TESTHR(pRecordset.CreateInstance(__uuidof(Recordset)));
		hr = 3;	TESTHR(pConnection->Open(strDbLk, "", "", adModeUnknown));		
		
		// Read Node
		hr = 5;	TESTHR(pRecordset->Open(strNdSql, pConnection.GetInterfacePtr(),
			adOpenForwardOnly, adLockReadOnly, adCmdText));
		assert(pRecordset->Fields->Count > 4);
		while(!pRecordset->adoEOF)
		{
			m_fmap.set_inode(
				GETLONGFIELD(pRecordset, 0), 
				GETLONGFIELD(pRecordset, 1),
				GETLONGFIELD(pRecordset, 2), 
				GETLONGFIELD(pRecordset, 3));
			pRecordset->MoveNext();
		}
		pRecordset->Close();
		
		// Read Link
		hr = 4;	TESTHR(pRecordset->Open(strLkSql, pConnection.GetInterfacePtr(), 
			adOpenForwardOnly, adLockReadOnly, adCmdText));
		
		assert(pRecordset->Fields->Count > 4);
		while(!pRecordset->adoEOF)
		{
			m_fmap.set_ilink(
				GETLONGFIELD(pRecordset, 0), 
				GETLONGFIELD(pRecordset, 1),
				GETLONGFIELD(pRecordset, 2), 
				GETLONGFIELD(pRecordset, 3));
			pRecordset->MoveNext();
		}
		pRecordset->Close();
		
		// Read Link Relation
		hr = 6;	TESTHR(pRecordset->Open(strNRl, pConnection.GetInterfacePtr(),
			adOpenForwardOnly, adLockReadOnly, adCmdText));
		assert(pRecordset->Fields->Count > 2);
		while(!pRecordset->adoEOF)
		{
			m_fmap.set_inrlk(	
				GETLONGFIELD(pRecordset, 0), 
				GETLONGFIELD(pRecordset, 1));
			pRecordset->MoveNext();
		}
		pRecordset->Close();
	}
	catch(...)
	{
	}
	
	if (pRecordset->State)
		pRecordset->Close();
	
	if(pConnection->State)
		pConnection->Close();
	
	pRecordset->Release();
	pConnection->Release();
	
	return hr;
}

STDMETHODIMP CEdSPath::SetW(long lSize, long *lW)
{
	m_fmap.set_w(lSize, lW);
	return S_OK;
}

STDMETHODIMP CEdSPath::GetLinks(long op, long dp, unsigned int n, BSTR *pShortLink, BSTR *pShortNode, BSTR *pPathW)
{
	_fgmap::vs nv;
	_fgmap::mids mlids, mnids;
	
#ifdef _DEMO
	for (int j = 0; j < mlids.size(); j++)
	{
		_fgmap::ids &lk = mlids[j];
		_fgmap::ids &nd = mnids[j];
		int num = lk.size() / 10;
		for (int i = 0; i < num; i++)
		{
			int t = rand() % lk.size();
			lk.erase(lk.begin() + t);
			t = rand() % nd.size();
			nd.erase(nd.begin() + t);
		}
	}
#endif
	
	if (m_fmap.getmshortpath(op, dp, n, mlids, mnids, nv))
	{
		CComBSTR str1(_fgmap::mids2str(mlids).c_str());
		CComBSTR str2(_fgmap::mids2str(mnids).c_str());
		CComBSTR str3(_fgmap::vs2str(nv).c_str());
		*pShortLink = str1.m_str;
		*pShortNode = str2.m_str;
		*pPathW = str3.m_str;
	}
	
	return S_OK;
}
