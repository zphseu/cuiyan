// EdFcMod1.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include <afxdllx.h>

// for string can not complie.
// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif

static AFX_EXTENSION_MODULE EdFcMod1DLL = { NULL, NULL };

HINSTANCE	g_hInstance = NULL;
CString		g_csData;
CString		g_csPath;
CString		g_csModuleName;

#include "DlgImport.h"
#include "EdRptExport.h"
#include "EdStat2View.h"
#include "EdHtmlView.h"
#include "EdRptView.h"
#include "EdStatView.h"
#include "EdStatRptView.h"
//////////////////////////////////////////////////////////////////////////

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// 如果使用 lpReserved，请将此移除
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("EdFcMod1.DLL 正在初始化！\n");
		
		// 扩展 DLL 一次性初始化
		if (!AfxInitExtensionModule(EdFcMod1DLL, hInstance))
			return 0;

		g_hInstance = hInstance;
		TCHAR szPath[MAX_PATH];
		GetModuleFileName(hInstance, szPath, MAX_PATH);
		g_csPath = szPath;
		g_csPath = g_csPath.Left(g_csPath.ReverseFind('\\'));
		g_csPath += _T("\\");

		g_csModuleName = szPath;
		g_csPath = g_csPath.Left(g_csPath.ReverseFind('.'));
		
		new CDynLinkLibrary(EdFcMod1DLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("EdFcMod1.DLL 正在终止！\n");
		AfxTermExtensionModule(EdFcMod1DLL);
	}
	return 1;   // 确定
}

#include <atlbase.h>
CString getDBDriver(LPCSTR szLink)
{
	CString csLink(szLink), csTmp(szLink);
	
	csTmp.MakeLower();
	int nFind = csTmp.Find(_T("driver="));
	if (nFind >= 0) // long constring
	{
		csLink.Delete(0, nFind + (int)_tcslen(_T("driver=")));
		nFind = csLink.Find(_T(';'));
		if (nFind > 0)
			csLink = csLink.Left(nFind);
		return csLink;
	}
	
	// DSN short constring
	nFind = csTmp.Find(_T("dsn="));
	// szLink is not a constring
	if (nFind < 0)
		return _T("");
	
	csLink.Delete(0, nFind + (int)_tcslen(_T("dsn=")));
	nFind = csLink.Find(_T(';'));
	if (nFind > 0)
		csLink = csLink.Left(nFind);
	
	TCHAR strTmp[MAX_PATH];
	DWORD dwLen = MAX_PATH;
	CRegKey reg;
	csTmp = csLink;
	csLink = _T("");
	
#ifdef _MSVC6_
#define QUEEYSTRINGVALUE() QueryValue(strTmp, csTmp, &dwLen)
#else
#define QUEEYSTRINGVALUE() QueryStringValue(csTmp, strTmp, &dwLen)
#endif
	// get ODBC Driver from HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\ODBC Data Sources
	if (reg.Open(HKEY_CURRENT_USER, _T("Software\\ODBC\\ODBC.INI\\ODBC Data Sources")) == ERROR_SUCCESS)
	{
		ZeroMemory(strTmp, MAX_PATH);
		dwLen = MAX_PATH;
		if (reg.QUEEYSTRINGVALUE() == ERROR_SUCCESS)
			csLink = strTmp;
		reg.Close();
	}
	
	if (!csLink.IsEmpty())
		return csLink;
	
	// get ODBC Driver from HKEY_LOCAL_MACHINE\Software\ODBC\ODBC.INI\ODBC Data Sources
	if (reg.Open(HKEY_LOCAL_MACHINE, _T("Software\\ODBC\\ODBC.INI\\ODBC Data Sources")) == ERROR_SUCCESS)
	{
		ZeroMemory(strTmp, MAX_PATH);
		dwLen = MAX_PATH;
		if (reg.QUEEYSTRINGVALUE() == ERROR_SUCCESS)
			csLink = strTmp;
		reg.Close();
	}
	
	return csLink;
}

void ShowMessage(HWND hWnd, LPCTSTR fmt, ...)
{
	static TCHAR str[2048];
	va_list ap;
	va_start(ap, fmt);
	vsprintf(str, fmt, ap);
	va_end(ap);

	if ( hWnd )
		MessageBox(hWnd, str, "EdFc", MB_OK);

	TRACE(str);

	FILE *fp = fopen(g_csModuleName + _T(".log"), "at+");
	if (fp != NULL)
	{
		fprintf(fp, "%s %s\n", CTime::GetCurrentTime().Format("%m/%d/%y %H:%M:%S  "), str);
		fclose(fp);
	}
	else
		TRACE("无法设置log文件！\n");
}

/////////////////////////////////////////////////////////////////////////
BOOL GetSubString(CString& strSub, LPCTSTR lpszFullString, int iFullStringLen, int iSubString, TCHAR chSep, TCHAR chMagic)
{
	int iPos, iPosOrig, iStartPos, iEndPos, iNumMagics;
	TCHAR* pcSubString;
	
	if((lpszFullString == NULL) || (iFullStringLen == 0))
		return FALSE;
	
	// Find substring begin
	for(iStartPos = 0; (iStartPos < iFullStringLen) && (iSubString > 0); iStartPos++)
	{
		// May be separator ?
		if(*(lpszFullString + iStartPos) == chSep)
		{
			if(((iStartPos > 0) && (*(lpszFullString + iStartPos - 1) != chMagic)) ||
				(iStartPos == 0))
			{
				// Sure it is a separator !
				iSubString--;
			}
		}
	}
	
	// Return empty string when nothing found
	if(iSubString > 0)
	{
		strSub.Empty();
		return FALSE;
	}
	
	// Find substring end
	iNumMagics = 0;
	for(iEndPos = iStartPos; iEndPos < iFullStringLen; iEndPos++)
	{
		// Count magics
		if(*(lpszFullString + iEndPos) == chMagic)
		{
			iNumMagics++;
		}
		
		// May be separator ?
		if(*(lpszFullString + iEndPos) == chSep)
		{
			if(((iEndPos > 0) && (*(lpszFullString + iEndPos - 1) != chMagic)) ||
				(iEndPos == 0))
			{
				// Sure it is the end !
				break;
			}
		}
	}
	
	// Copy substring
	pcSubString = strSub.GetBufferSetLength(iEndPos - iStartPos - iNumMagics);
	iPosOrig = iStartPos;
	iEndPos -= iStartPos;
	if(pcSubString != NULL)
	{
		for(iPos = 0; iPos < iEndPos; iPos += sizeof(TCHAR))
		{
			if(*(lpszFullString + iPosOrig) != chMagic)
			{
				*(pcSubString + iPos) = *(lpszFullString + iPosOrig);
			}
			else
			{
				iPos -= sizeof(TCHAR);
				iEndPos -= sizeof(TCHAR);
			}
			iPosOrig += sizeof(TCHAR);
		}
		*(pcSubString + iPos) = 0;
		return TRUE;
	}
	return FALSE;
}; 

int QueryDialog(HWND hWnd)
{
	int nRet = IDCANCEL;

	try 
	{
		CString szDlgInfo (g_csData);
		
		if (szDlgInfo.IsEmpty())
			throw CString("配置文件中没有有效的查询对话框描述！");
		
		CString szDlgDllName, szDlgName;
		int nLen = szDlgInfo.GetLength();
		GetSubString(szDlgDllName, szDlgInfo, nLen, 1, ';', '~');
		GetSubString(szDlgName, szDlgInfo, nLen, 2, ';', '~');
		
		if (szDlgDllName.IsEmpty())
			throw CString("配置文件中没有指明对话框模块名称！");
		
		szDlgDllName = g_csPath + szDlgDllName;
		HINSTANCE hDLL = ::LoadLibrary(szDlgDllName);

		if (hDLL == NULL)
			ShowMessage(hWnd, "EdFc.manifest中指明对话框模块 %s 名称无效！", szDlgDllName);

		typedef INT_PTR (*GETDIALOG)(LPCTSTR, HWND);	
		GETDIALOG pDlgFun = (GETDIALOG) ::GetProcAddress(hDLL,"GetDialog");
		if (pDlgFun == NULL)
		{
			::FreeLibrary(hDLL);
			throw szDlgDllName + CString("中无对话框模块的 GetDialog 函数接口！");
		}
		
		HINSTANCE hOld = AfxGetResourceHandle();
		
		AfxSetResourceHandle(hDLL);
		
		nRet = pDlgFun(szDlgName, hWnd);
		
		AfxSetResourceHandle(hOld);
		
		::FreeLibrary(hDLL);
	}
	catch (CString msg)
	{
		ShowMessage(hWnd, msg);
	}

	return nRet;
}

BOOL AutoRpt(LPCTSTR szFile, CPrintDialog *pPntDlg = NULL)
{
	CEdRptDoc doc;
	return (doc.LoadFrom(szFile) && doc.GetData()&& doc.PrintAuto(pPntDlg));
}

BOOL AutoExport(LPCTSTR szFmtName, LPCTSTR szExpName)
{
	CEdRptDoc doc;

	if (!doc.LoadFrom(szFmtName))
	{
		ShowMessage(NULL, "无法打开格式文件 %s 。", szFmtName);
		return FALSE;
	}
	
	doc.m_csFileName = szFmtName;
	CEdRptExport bsExport(&doc, szExpName);
	bsExport.DoExporting();
	
	return TRUE;
}

BOOL AutoImport(LPCTSTR szExpName, LPCTSTR szImDir)
{
	CEdRptDoc doc;	
	CEdRptExport bsImport(&doc, szExpName, szImDir);
	bsImport.DoImporting();
	
	return TRUE;
}

UINT BSImportDlg()
{
	HINSTANCE hOld = AfxGetResourceHandle();
	AfxSetResourceHandle(g_hInstance);
	CDlgImport dlg;
	UINT nResponse = (UINT)dlg.DoModal();
	AutoImport(dlg.m_szFile, dlg.m_szDir);
	AfxSetResourceHandle(hOld);
	return nResponse;
}

extern "C" BOOL GetView(LPCSTR szView, LPCSTR szData, CRuntimeClass*& pView, UINT& nToolBarRes, UINT &nToolBarBmp)
{
	BOOL bRet = TRUE;
	g_csData = szData;
	pView = NULL;
	nToolBarRes = 0;
	nToolBarBmp = 0;
	
	CString szToolbarFlag, csView = szView;
	GetSubString(szToolbarFlag, g_csData, g_csData.GetLength(), 0, ';', '~');
	szToolbarFlag.MakeLower();
	
	if (csView.CompareNoCase(_T("Stat2")) == 0 )
	{
		pView =  RUNTIME_CLASS(CEdStat2View);
		nToolBarRes = IDR_EDSTAT2D;
		if (szToolbarFlag == _T("manager"))
			nToolBarRes = IDR_EDSTAT2M;
		else if (szToolbarFlag == _T("supper"))
			nToolBarRes = IDR_EDSTAT2S;
	}
	else if (csView.CompareNoCase(_T("Stat")) == 0 )
	{
		pView =  RUNTIME_CLASS(CEdStatView);
		nToolBarRes = IDR_EDSTATD;
		if (szToolbarFlag == _T("manager"))
			nToolBarRes = IDR_EDSTATM;
	}
	else if (csView.CompareNoCase(_T("StatRpt")) == 0 )
	{
		pView =  RUNTIME_CLASS(CEdStatRptView);
		nToolBarRes = IDR_EDSTATRPT;
	}
	else if (csView.CompareNoCase(_T("Report")) == 0)
	{
		pView =  RUNTIME_CLASS(CEdRptView);
		nToolBarRes = IDR_EDRPTD;
		if (szToolbarFlag == _T("manager"))
		{
			nToolBarRes = IDR_EDRPTM;
			nToolBarBmp = IDB_EDRPTM;
		}
		else if (szToolbarFlag == _T("bigbar"))
		{
			nToolBarRes = IDR_EDRPTL;
			nToolBarBmp = IDB_EDRPTL;
		}
		else if (szToolbarFlag == _T("smallbar"))
		{
			nToolBarRes = IDR_EDRPTS;
			nToolBarBmp = IDB_EDRPTS;
		}
	}
	else if (csView.CompareNoCase(_T("Html")) == 0)
	{
		pView = RUNTIME_CLASS(CEdHtmlView);
		nToolBarRes = IDR_EDHTML;
		nToolBarBmp = IDB_EDHTML;
	}
	else
		bRet = FALSE;
	
	return bRet;
}