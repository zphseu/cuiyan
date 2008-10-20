// EdSPath.h : Declaration of the CEdSPath

#ifndef __EDSPATH_H_
#define __EDSPATH_H_

#include "resource.h"       // main symbols
#include "SPATH\fgmap.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// CEdSPath
class ATL_NO_VTABLE CEdSPath : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEdSPath, &CLSID_EdSPath>,
	public IDispatchImpl<IEdSPath, &IID_IEdSPath, &LIBID_EDCOMSLib>
{
public:
	CEdSPath()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EDSPATH)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEdSPath)
	COM_INTERFACE_ENTRY(IEdSPath)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEdSPath
public:
	STDMETHOD(GetLinks)(/*[in]*/long op, /*[in]*/long dp, /*[in]*/unsigned int n, /*[out]*/BSTR* pShortLink, /*[out]*/BSTR* pShortNode, /*[out]*/BSTR* pPathW);
	STDMETHOD(SetW)(/*[in]*/long lSize, /*[in, size_is(lSize)]*/ long *lW);
	STDMETHOD(SetMapDb)(BSTR strDbLk, BSTR strLkSql, BSTR strNdSql, BSTR strNRl);
	STDMETHOD(GetLink)(/*[in]*/BSTR nds, /*[in]*/unsigned int n, /*[out]*/BSTR* pShortLink, /*[out]*/BSTR* pShortNode);
	STDMETHOD(SetMapFile)(BSTR mpfn);
	
protected:
	_fgmap m_fmap;
};

#endif //__EDSPATH_H_
