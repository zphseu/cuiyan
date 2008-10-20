// Views.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE ViewsDLL = { NULL, NULL };

extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// ���ʹ�� lpReserved���뽫���Ƴ�
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Views.DLL ���ڳ�ʼ����\n");
		
		// ��չ DLL һ���Գ�ʼ��
		if (!AfxInitExtensionModule(ViewsDLL, hInstance))
			return 0;

		// ���� DLL ���뵽��Դ����
		// ע��: �������չ DLL ��
		//  MFC ���� DLL(�� ActiveX �ؼ�)��ʽ���ӵ�
		//  �������� MFC Ӧ�ó������ӵ�������Ҫ
		//  �����д� DllMain ���Ƴ������������һ��
		//  �Ӵ���չ DLL �����ĵ����ĺ����С�ʹ�ô���չ DLL ��
		//  ���� DLL Ȼ��Ӧ��ʽ
		//  ���øú����Գ�ʼ������չ DLL������
		//  CDynLinkLibrary ���󲻻ḽ�ӵ�
		//  ���� DLL ����Դ���������������ص�
		//  ���⡣

		new CDynLinkLibrary(ViewsDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Views.DLL ������ֹ��\n");

		// �ڵ�����������֮ǰ��ֹ�ÿ�
		AfxTermExtensionModule(ViewsDLL);
	}
	return 1;   // ȷ��
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
