// EdMtrData.h : Declaration of the CEdMtrData

#ifndef __EDMTRDATA_H_
#define __EDMTRDATA_H_

#include "resource.h"       // main symbols
#include "EdMtrS.h"
/////////////////////////////////////////////////////////////////////////////
// CEdMtrData
class ATL_NO_VTABLE CEdMtrData : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEdMtrData, &CLSID_EdMtrData>,
	public IDispatchImpl<IEdMtrData, &IID_IEdMtrData, &LIBID_EDCOMSLib>,
	public CEdMtrS
{
public:
	CEdMtrData()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EDMTRDATA)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEdMtrData)
	COM_INTERFACE_ENTRY(IEdMtrData)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEdMtrData
public:
	STDMETHOD(SetSize)(/*[in]*/long row, /*[in]*/long col);
	STDMETHOD(get_Data)(long row, long col, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Data)(long row, long col, /*[in]*/ BSTR newVal);
	STDMETHOD(get_Rows)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Cols)(/*[out, retval]*/ long *pVal);
	STDMETHOD(DoPrint)(/*[in]*/BSTR bstrPrinterName);
	STDMETHOD(SetParams)(/*[in]*/BSTR bstrTitle, /*[in]*/BSTR bstrHeadRight, /*[in]*/BSTR bstrFootLeft, /*[in]*/BSTR bstrFootRight, /*[in]*/BSTR bstrFontName, /*[in]*/BSTR bstrColsWidthStr, /*[in]*/long lFixedCols);
	STDMETHOD(ReadDB)(/*[in]*/BSTR bstrConnect, /*[in]*/BSTR bstrSQL);
	STDMETHOD(ReadFile)(/*[in]*/BSTR bstrFileName, /*[in]*/BSTR bstrTableName);
};

#endif //__EDMTRDATA_H_
