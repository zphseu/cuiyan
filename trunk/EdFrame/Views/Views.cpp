// Views.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "T1Frm.h"
#include "T1Doc.h"
#include "T1View.h"
#include "T2Doc.h"
#include "T2View.h"

#include "w3cfrm.h"
#include "w3cdoc.h"
#include "w3cview.h"

static CMultiDocTemplate** pTemplate = NULL;	//cycy
static AFX_EXTENSION_MODULE ViewsDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("VIEWS.DLL Initializing!\n");
		
		if (!AfxInitExtensionModule(ViewsDLL, hInstance))
			return 0;

		new CDynLinkLibrary(ViewsDLL);

		/////// cycy /////////////////////////////////////////////////
		pTemplate = new CMultiDocTemplate* [3];		
		pTemplate[0] = new CMultiDocTemplate(
			IDR_T1TYPE,
			RUNTIME_CLASS(CT1Doc),
			RUNTIME_CLASS(CT1Frame),
			RUNTIME_CLASS(CT1View));
		
		pTemplate[1] = new CMultiDocTemplate(
			IDR_T2TYPE,
			RUNTIME_CLASS(CT2Doc),
			RUNTIME_CLASS(CT1Frame),
			RUNTIME_CLASS(CT2View));
		
		pTemplate[2] = new CMultiDocTemplate(
			IDR_W3CTYPE,
			RUNTIME_CLASS(CW3CDoc),
			RUNTIME_CLASS(CW3CFrame),
			RUNTIME_CLASS(CW3CView));
		/////// cycy /////////////////////////////////////////////////
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("VIEWS.DLL Terminating!\n");
		AfxTermExtensionModule(ViewsDLL);

		delete []pTemplate;	//cycy
	}
	return 1;
}

/////// cycy /////////////////////////////////////////////////
extern "C" AFX_EXT_API int GetDocTemplates(CMultiDocTemplate** &pTempl)
{
	pTempl = pTemplate;
	return 3;
}
/////// cycy /////////////////////////////////////////////////