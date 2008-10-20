// EdUsr.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE EdUsrDLL = { NULL, NULL };

#include "EdMod1Ini.h"
#include "EduserCfg.h"

HINSTANCE	g_hInstance = NULL;
static CDatabase g_db;
CEdMod1Ini	g_ini;
tagUsr		g_usr;
CMapStringToPtr g_mapCurUsrRes;

/////////////////////////////////////////////////////////////////////////

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// ���ʹ�� lpReserved���뽫���Ƴ�
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("EdUsr.DLL ���ڳ�ʼ����\n");
		
		// ��չ DLL һ���Գ�ʼ��
		if (!AfxInitExtensionModule(EdUsrDLL, hInstance))
			return 0;

		g_hInstance = hInstance;
		
		if (!g_ini.ReadConfig())
			g_ini.WriteConfig();

		new CDynLinkLibrary(EdUsrDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("EdUsr.DLL ������ֹ��\n");

		g_mapCurUsrRes.RemoveAll();
		AfxTermExtensionModule(EdUsrDLL);
	}
	return 1;   // ȷ��
}

#include "EdUserView.h"

extern "C" BOOL GetView(LPCSTR szView, LPCSTR szData, CRuntimeClass*& pView, UINT& nToolBarRes, UINT &nToolBarBmp)
{
	pView = RUNTIME_CLASS(CEdUserView);
	nToolBarRes = 0;
	nToolBarBmp = 0;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////

extern "C" CDatabase* GetDB()
{
	int nCount = 2;
	
	try
	{
		while (nCount > 0) 
		{
			if (!g_db.IsOpen())
			{
				g_db.OpenEx(g_ini.m_csConStr, CDatabase::useCursorLib);
				if (!g_db.IsOpen())
					throw new CException;
			}
			
			CRecordset rs(&g_db);
			rs.Open(rs.forwardOnly, "SELECT AA FROM ZED001");
			if (!rs.IsOpen()) 
			{
				g_db.Close();
				continue;
			}
			nCount--;
			rs.Close();
			return &g_db;
		}
	}
	catch (CException *e) 
	{
		AfxMessageBox("���ݿ����ô����޷���ָ�������ݿ⣡");
		e->Delete();
	}
	
	return NULL;
}

#include "DlgLogin.h"
extern "C" BOOL Login()
{
	BOOL bRet = TRUE;
	CDlgLogin dlg;
	CEdUserCfg uc;
	
	int nCount = 3;
	
	if (g_ini.m_bUseDB && GetDB() == NULL)
		nCount = -1;		
	
	HINSTANCE hInstOld=AfxGetResourceHandle();
    AfxSetResourceHandle(g_hInstance);
	
	while (nCount > 0)
	{
		if (dlg.DoModal() != IDOK)
		{
			nCount = 0;
			continue;
		}
		
		if (!uc.ReadUsrCfg(dlg.m_csUID, dlg.m_csPwd))
		{
			nCount--;
			continue;
		}
		else
			break;
	};
	
	AfxSetResourceHandle(hInstOld);
	
	if (nCount <= 0)
	{
		g_mapCurUsrRes.RemoveAll();
		bRet = FALSE;
	}

	return bRet;
}

extern "C" void Logout()
{
	if (g_db.IsOpen())
		g_db.Close();
	
	g_mapCurUsrRes.RemoveAll();
}

#include "DlgUser.h"
extern "C" int DoCfgDlg()
{
	HINSTANCE hInsOld = AfxGetResourceHandle();
	AfxSetResourceHandle(g_hInstance);
	CDlgUser dlg;
	int nResponse = dlg.DoModal();
	AfxSetResourceHandle(hInsOld);
	return nResponse;
}

extern "C" LPCTSTR GetCurUser()
{
	return g_usr.m_csName;
}

extern "C" BOOL Validate(LPCSTR szRes)
{
	void *p = NULL;
	return (g_usr.m_csName.CompareNoCase("EDSON@EYOU.COM") == 0 || g_mapCurUsrRes.Lookup(szRes, p) );
}