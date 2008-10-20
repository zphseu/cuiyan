// EdPrint.cpp : Implementation of CEdPrintApp and DLL registration.

#include "stdafx.h"
#include "EdPrint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CEdPrintApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x734aa901, 0x7066, 0x4095, { 0xa4, 0x6b, 0x41, 0xf2, 0x2a, 0xa6, 0x83, 0x31 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

//////////////////////////////////////////////////////////////////////////
#include <comcat.h>
#include <objsafe.h>

static HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription) 
{ 	
    ICatRegister* pcr = NULL ; 
    HRESULT hr = S_OK ; 
	
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr); 
    if (FAILED(hr)) 
		return hr; 
	
    // Make sure the HKCR\Component Categories\{..catid...} 
    // key is registered 
    CATEGORYINFO catinfo; 
    catinfo.catid = catid; 
    catinfo.lcid = 0x0409 ; // english 
	
    // Make sure the provided description is not too long. 
    // Only copy the first 127 characters if it is 
    int len = wcslen(catDescription); 
    if (len>127) 
		len = 127; 
    wcsncpy(catinfo.szDescription, catDescription, len); 
    // Make sure the description is null terminated 
    catinfo.szDescription[len] = '\0'; 
	
    hr = pcr->RegisterCategories(1, &catinfo); 
    pcr->Release(); 
	
    return hr; 
} 

static HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid) 
{ 
    // Register your component categories information. 
    ICatRegister* pcr = NULL ; 
    HRESULT hr = S_OK ; 
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr); 
    if (SUCCEEDED(hr)) 
    { 
		// Register this category as being "implemented" by 
		// the class. 
		CATID rgcatid[1] ; 
		rgcatid[0] = catid; 
		hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid); 
    } 
	
    if (pcr != NULL) 
		pcr->Release(); 
	
    return hr; 
} 

static HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid) 
{ 
    ICatRegister* pcr = NULL ; 
    HRESULT hr = S_OK ; 
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr); 
    if (SUCCEEDED(hr)) 
    { 
		// Unregister this category as being "implemented" by 
		// the class. 
		CATID rgcatid[1] ; 
		rgcatid[0] = catid; 
		hr = pcr->UnRegisterClassImplCategories(clsid, 1, rgcatid); 
    } 
	
    if (pcr != NULL) 
		pcr->Release(); 
	
    return hr; 
} 
////////////////////////////////////////////////////////////////////////////
// CEdPrintApp::InitInstance - DLL initialization

BOOL CEdPrintApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CEdPrintApp::ExitInstance - DLL termination

int CEdPrintApp::ExitInstance()
{
	delete CDocManager::pStaticDocManager;
	delete CDocManager::pStaticList;
	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry
//cycy start: copy from EdChartCtl.cpp & EdGridCtl.cpp
const IID BASED_CODE IID_Chart =
	{ 0xd294db4a, 0x1a1a, 0x4461, {0x85, 0x48, 0x8d, 0xda, 0x92, 0xbb, 0x66, 0xdd } };

const IID BASED_CODE IID_Grid =
	{ 0xe9bfb9f4, 0xc756, 0x48aa, {0xbf, 0x27, 0x1c, 0x6e, 0xc9, 0xb3, 0xc7, 0x12 } };
//cycy end;

#define CHECKHRESULT(hr) if(FAILED(hr)) return (hr);

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	//////////////////////////////////////////////////////////////////////////
	CHECKHRESULT(CreateComponentCategory(CATID_SafeForInitializing,
		L"EdChartCtrl safely initializable from persistent data!"));
	CHECKHRESULT(RegisterCLSIDInCategory(IID_Chart, CATID_SafeForInitializing));
	CHECKHRESULT(CreateComponentCategory(CATID_SafeForScripting, 
		L"EdChartCtrl safely scriptable!"));
	CHECKHRESULT(RegisterCLSIDInCategory(IID_Chart, CATID_SafeForScripting));

	CHECKHRESULT(CreateComponentCategory(CATID_SafeForInitializing,
		L"EdGridCtrl safely initializable from persistent data!"));
	CHECKHRESULT(RegisterCLSIDInCategory(IID_Grid, CATID_SafeForInitializing));
	CHECKHRESULT(CreateComponentCategory(CATID_SafeForScripting, 
		L"EdGridCtrl safely scriptable!"));
	CHECKHRESULT(RegisterCLSIDInCategory(IID_Grid, CATID_SafeForScripting));
	//////////////////////////////////////////////////////////////////////////
	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);
	
	//////////////////////////////////////////////////////////////////////////
	CHECKHRESULT(UnRegisterCLSIDInCategory(IID_Chart, CATID_SafeForScripting));
    CHECKHRESULT(UnRegisterCLSIDInCategory(IID_Chart, CATID_SafeForInitializing));
	CHECKHRESULT(UnRegisterCLSIDInCategory(IID_Grid, CATID_SafeForScripting));
    CHECKHRESULT(UnRegisterCLSIDInCategory(IID_Grid, CATID_SafeForInitializing));
	//////////////////////////////////////////////////////////////////////////
	
	return NOERROR;
}


#include <winspool.h>

HDC GetPrintHDC(COleControl* pCtrl, LPCTSTR lpszPrinterName)
{
	HDC hDC = NULL;
	ASSERT(pCtrl);
	
	CString csPrinterName(lpszPrinterName);
	if (csPrinterName.IsEmpty())
	{	
		CPrintDialog printDlg(FALSE);
		if (printDlg.DoModal() == IDOK)             // Get printer settings from user
			hDC = printDlg.GetPrinterDC();
	}
	else if (csPrinterName.CompareNoCase(_T("Default")) == 0)
	{
		CPrintDialog printDlg(FALSE);
		if( printDlg.GetDefaults() )
			hDC = printDlg.GetPrinterDC();
	}
	else
	{
		HANDLE hprinter = NULL;
		
		if ( !OpenPrinter(csPrinterName.GetBuffer(0), &hprinter,NULL) ) 
			return NULL;
		
		LONG rc = DocumentProperties(NULL, hprinter, csPrinterName.GetBuffer(0), NULL, NULL, 0);
		if (rc < 0)
			return NULL;
		
		byte* hDevMode = new byte[rc + 1];
		ZeroMemory(hDevMode, rc + 1);
		
		rc = DocumentProperties(pCtrl->m_hWnd, hprinter, csPrinterName.GetBuffer(0), (DEVMODE *)hDevMode, NULL, DM_OUT_BUFFER);
		if (rc > 0)
			hDC = CreateDC(_T("WINSPOOL"), csPrinterName, NULL, (DEVMODE *)hDevMode); 
		
		delete [] hDevMode;
	}
	
	return hDC;	
}
