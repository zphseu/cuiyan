// EdFun.cpp : Implementation of CEdFun
#include "stdafx.h"
#include "EdComs.h"
#include "EdFun.h"

/////////////////////////////////////////////////////////////////////////////
// CEdFun


STDMETHODIMP CEdFun::GetPrintHDC(BSTR bstrPrinterName, long *hDC)
{
	*hDC = (long)CEdFuncs::GetPrintHDC((LPCTSTR)(_bstr_t)bstrPrinterName);
	return S_OK;
}

STDMETHODIMP CEdFun::GetFile(BSTR btrFileName, BSTR* bstrData)
{
	string str;
	if (CEdFuncs::GetFile((LPCTSTR)(_bstr_t)btrFileName, str))	{
		*bstrData = (_bstr_t)str.c_str();
		return S_OK;
	}	else
		return S_FALSE;
}

STDMETHODIMP CEdFun::GetHttpPage(BSTR bstrUrl, BSTR *bstrData)
{
	string str;
	if (CEdFuncs::GetHttpPage((LPCTSTR)(_bstr_t)bstrUrl, str))	{
		*bstrData = (_bstr_t)str.c_str();
		return S_OK;
	}	else
		return S_FALSE;
}

STDMETHODIMP CEdFun::GetFtpFile(BSTR bstrUrl, BSTR *bstrData)
{
	string str;
	if (CEdFuncs::GetFtpFile((LPCTSTR)(_bstr_t)bstrUrl, str))	{
		*bstrData = (_bstr_t)str.c_str();
		return S_OK;
	}	else
		return S_FALSE;
}

STDMETHODIMP CEdFun::UrlEncode(BSTR bstrIn, BSTR *bstrOut)
{
	string sIn, sOut;
	sIn = (LPCTSTR)(_bstr_t)bstrIn;
	CEdFuncs::urlencode(sIn, sOut);
	*bstrOut = (_bstr_t)sOut.c_str();
	return S_OK;
}

STDMETHODIMP CEdFun::SendMsg(long ip, BSTR from, BSTR machine, BSTR msg)
{
	//sample sd(inet_addr("168.2.4.57"), "cuiyan", "", "Hello!");
	sd(ip, (LPCSTR)(_bstr_t)from, (LPCSTR)(_bstr_t)machine, (LPCSTR)(_bstr_t)msg);
	return S_OK;
}
