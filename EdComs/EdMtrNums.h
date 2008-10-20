// EdMtrNums.h : Declaration of the CEdMtrNums

#ifndef __EDMTRNUMS_H_
#define __EDMTRNUMS_H_

#include "resource.h"       // main symbols

#include "EdMtrT.h"

/////////////////////////////////////////////////////////////////////////////
// CEdMtrNums
class ATL_NO_VTABLE CEdMtrNums : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEdMtrNums, &CLSID_EdMtrNums>,
	public IDispatchImpl<IEdMtrNums, &IID_IEdMtrNums, &LIBID_EDCOMSLib>,
	public CEdMtrT
{
public:
	CEdMtrNums()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EDMTRNUMS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEdMtrNums)
	COM_INTERFACE_ENTRY(IEdMtrNums)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEdMtrNums
public:
	STDMETHOD(Save)(/*[in]*/BSTR bstrFileName);
	STDMETHOD(SetRowNames)(/*[in]*/BSTR bstrRowNames);
	STDMETHOD(SetColNames)(/*[in]*/BSTR bstrColNames);
	STDMETHOD(SetSize)(/*[in]*/long row, /*[in]*/long col);
	STDMETHOD(get_Rows)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Cols)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Data)(long row, long col, /*[out, retval]*/ double *pVal);
	STDMETHOD(put_Data)(long row, long col, /*[in]*/ double newVal);
	STDMETHOD(get_RowName)(long row, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_RowName)(long row, /*[in]*/ BSTR newVal);
	STDMETHOD(get_ColName)(long col, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ColName)(long col, /*[in]*/ BSTR newVal);
	STDMETHOD(ReadDB)(/*[in]*/BSTR bstrConnect, /*[in]*/BSTR bstrDataSQL,
		/*[in]*/BSTR bstrPointSQL, /*[in]*/BSTR bstrGroupSQL);
	STDMETHOD(ReadFile)(/*[in]*/BSTR bstrFileName, /*[in]*/BSTR bstrTableName);

};

#endif //__EDMTRNUMS_H_
