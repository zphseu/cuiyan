// PtEmt.cpp : Implementation of CPtEmtApp and DLL registration.

#include "stdafx.h"
#include "PtEmt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CPtEmtApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x5123d834, 0x1aa3, 0x486a, { 0xb9, 0x44, 0x65, 0x5a, 0xd6, 0x5, 0x2b, 0xd7 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CPtEmtApp::InitInstance - DLL initialization

BOOL CPtEmtApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (TRUE == bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CPtEmtApp::ExitInstance - DLL termination

int CPtEmtApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (FALSE == AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid)) {
		return ResultFromScode(SELFREG_E_TYPELIB);
	}

	if (FALSE == COleObjectFactoryEx::UpdateRegistryAll(TRUE)) {
		return ResultFromScode(SELFREG_E_CLASS);
	}

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (FALSE == AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor)) {
		return ResultFromScode(SELFREG_E_TYPELIB);
	}

	if (FALSE == COleObjectFactoryEx::UpdateRegistryAll(FALSE)) {
		return ResultFromScode(SELFREG_E_CLASS);
	}

	return NOERROR;
}
