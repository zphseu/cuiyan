// EdFun.h : Declaration of the CEdFun

#ifndef __EDFUN_H_
#define __EDFUN_H_

#include "resource.h"       // main symbols
#include "EdFuncs.h"
/////////////////////////////////////////////////////////////////////////////
// CEdFun
class ATL_NO_VTABLE CEdFun : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEdFun, &CLSID_EdFun>,
	public IDispatchImpl<IEdFun, &IID_IEdFun, &LIBID_EDCOMSLib>,
	public CEdFuncs
{
public:
	CEdFun()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EDFUN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEdFun)
	COM_INTERFACE_ENTRY(IEdFun)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEdFun
public:
	STDMETHOD(SendMsg)(/*[in]*/long ip, /*[in]*/BSTR from, /*[in]*/BSTR machine, /*[in]*/BSTR msg);
	STDMETHOD(UrlEncode)(/*[in]*/BSTR bstrIn, /*[out]*/BSTR* bstrOut);
	STDMETHOD(GetFtpFile)(/*[in]*/BSTR bstrUrl, /*[out]*/BSTR* bstrData);
	STDMETHOD(GetHttpPage)(/*[in]*/BSTR bstrUrl, /*[out]*/BSTR* bstrData);
	STDMETHOD(GetFile)(/*[in]*/BSTR btrFileName, /*[out]*/BSTR* bstrData);
	STDMETHOD(GetPrintHDC)(/*[in]*/BSTR bstrPrinterName, /*[out]*/long* hDC);
};

#endif //__EDFUN_H_
