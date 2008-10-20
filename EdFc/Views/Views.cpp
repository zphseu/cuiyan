// Views.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE ViewsDLL = { NULL, NULL };

extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// 如果使用 lpReserved，请将此移除
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Views.DLL 正在初始化！\n");
		
		// 扩展 DLL 一次性初始化
		if (!AfxInitExtensionModule(ViewsDLL, hInstance))
			return 0;

		// 将此 DLL 插入到资源链中
		// 注意: 如果此扩展 DLL 由
		//  MFC 规则 DLL(如 ActiveX 控件)隐式链接到
		//  而不是由 MFC 应用程序链接到，则需要
		//  将此行从 DllMain 中移除并将其放置在一个
		//  从此扩展 DLL 导出的单独的函数中。使用此扩展 DLL 的
		//  规则 DLL 然后应显式
		//  调用该函数以初始化此扩展 DLL。否则，
		//  CDynLinkLibrary 对象不会附加到
		//  规则 DLL 的资源链，并将导致严重的
		//  问题。

		new CDynLinkLibrary(ViewsDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Views.DLL 正在终止！\n");

		// 在调用析构函数之前终止该库
		AfxTermExtensionModule(ViewsDLL);
	}
	return 1;   // 确定
}

#include "Customer.h"
#include "MyListView.h"

CString g_csData;

extern "C" BOOL GetView(LPCSTR szView, LPCSTR szData, CRuntimeClass*& pView, UINT& nToolBarRes, UINT &nToolBarBmp)
{
	BOOL bRet = TRUE;
	g_csData = szData;
	pView = NULL;
	nToolBarRes = 0;

	CString csView = szView;
	if (csView.CompareNoCase("custom") == 0)
	{
		pView = RUNTIME_CLASS(CCustomer);
		nToolBarRes = IDR_CUSTOM;
	}
	else if (csView.CompareNoCase("ListView") == 0)
	{
		pView = RUNTIME_CLASS(CMyListView);
		nToolBarRes = IDR_LISTVIEW;
	}
	else
		bRet = FALSE;

	return bRet;
}
