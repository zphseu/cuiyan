// DSAddIn.h : header file
//

#if !defined(AFX_DSADDIN_H__3EFDD44F_09F9_4CD7_B56B_ECC3D010066C__INCLUDED_)
#define AFX_DSADDIN_H__3EFDD44F_09F9_4CD7_B56B_ECC3D010066C__INCLUDED_

#include "commands.h"

// {40F66C8F-5552-49F5-BFC9-9767C63A5231}
DEFINE_GUID(CLSID_DSAddIn,
0x40f66c8f, 0x5552, 0x49f5, 0xbf, 0xc9, 0x97, 0x67, 0xc6, 0x3a, 0x52, 0x31);

/////////////////////////////////////////////////////////////////////////////
// CDSAddIn

class CDSAddIn : 
	public IDSAddIn,
	public CComObjectRoot,
	public CComCoClass<CDSAddIn, &CLSID_DSAddIn>
{
public:
	DECLARE_REGISTRY(CDSAddIn, "EdAddins.DSAddIn.1",
		"EDADDINS Developer Studio Add-in", IDS_EDADDINS_LONGNAME,
		THREADFLAGS_BOTH)

	CDSAddIn() {}
	BEGIN_COM_MAP(CDSAddIn)
		COM_INTERFACE_ENTRY(IDSAddIn)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CDSAddIn)

// IDSAddIns
public:
	STDMETHOD(OnConnection)(THIS_ IApplication* pApp, VARIANT_BOOL bFirstTime,
		long dwCookie, VARIANT_BOOL* OnConnection);
	STDMETHOD(OnDisconnection)(THIS_ VARIANT_BOOL bLastTime);

protected:
	CCommandsObj* m_pCommands;
	DWORD m_dwCookie;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSADDIN_H__3EFDD44F_09F9_4CD7_B56B_ECC3D010066C__INCLUDED)
