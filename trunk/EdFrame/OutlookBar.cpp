// OutlookBar.cpp: implementation of the COutlookBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdFrame.h"
#include "OutlookBar.h"
#include <ssdsdk.h>
#include <atlbase.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#pragma comment(lib, "Version.lib")

#define FreeLib(p)		{ if (p) FreeLibrary(p); (p) = NULL; }

const char* const EDVFCREGPATH = "SOFTWARE\\Edson\\EdFrame";

COutlookBar::COutlookBar()
{

}

COutlookBar::~COutlookBar()
{
	Clean(FALSE);
}

BEGIN_MESSAGE_MAP(COutlookBar, CSizingControlBarG)
	//{{AFX_MSG_MAP(CReportBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTWM_OUTBAR_NOTIFY, OnOutbarNotify)	
END_MESSAGE_MAP()

int COutlookBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	// Create the image lists used by the outlook bar.
	m_ImageSmall.Create (16, 16, ILC_COLOR16 | ILC_MASK, 2, 1);
	m_ImageLarge.Create (32, 32, ILC_COLOR16 | ILC_MASK, 2, 1);
	
	if (CSizingControlBarG::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);
	
	if (!m_wndChild.Create( WS_CHILD | WS_VISIBLE | WS_BORDER,
		CRect(0, 0, 0, 0), this, 0))
		return -1;
	
	m_wndChild.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	m_wndChild.SetImageList(&m_ImageLarge, OBS_XT_LARGEICON);
	m_wndChild.SetImageList(&m_ImageSmall, OBS_XT_SMALLICON);	
	
	// We want to receive notification messages.
	m_wndChild.SetOwner(this);
	
	// Set the background and text color of the outlook bar.
	m_wndChild.SetBackColor(RGB(0x3a,0x6e,0xa5));
	m_wndChild.SetTextColor(RGB(0xff,0xff,0xff));
	
	//////////////////////////////////////////////////////////////////////////
	CRegKey reg;
	enum { LOADFROMXML, LOADFROMPATH };
	DWORD	bLoadStyle = LOADFROMPATH;
	if (reg.Open(HKEY_LOCAL_MACHINE, EDVFCREGPATH) != ERROR_SUCCESS || reg.QueryValue(bLoadStyle, "LoadStyle") != ERROR_SUCCESS)
	{
		if (reg.Create(HKEY_LOCAL_MACHINE, EDVFCREGPATH) == ERROR_SUCCESS)
			reg.SetValue(LOADFROMPATH, "LoadStyle");
	}
	
	reg.Close();

	if (bLoadStyle == LOADFROMXML)
		GetFromXML(NULL);
	else
	{
		CString sPath = AfxGetApp()->m_pszHelpFilePath;
		sPath = sPath.Left(sPath.ReverseFind('\\'));
		GetFromPath(sPath);
	}
	//////////////////////////////////////////////////////////////////////////
	
	for (int iFolder = 0; iFolder < m_arFolder.GetSize() ; iFolder++)
	{
		m_wndChild.AddFolder(m_arFolder[iFolder], iFolder+1);

		int nCount = m_arStart[iFolder+1] - m_arStart[iFolder];
		int nStart = m_arStart[iFolder];
		for (int iItem = 0; iItem < nCount; iItem++)
			m_wndChild.InsertItem(iFolder, iItem + 1, iItem + nStart, 
				m_arTexts[iItem + nStart], 
				m_arFiles[iItem + nStart]);
	}
	
	// Select the first folder in the bar.
	if (m_wndChild.GetFolderCount() > 0)
		m_wndChild.SetSelFolder(0);
	
	return 0;
}

LRESULT COutlookBar::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
	int nBarAction = (int)wParam;
	XT_OUTBAR_INFO* pOBInfo = (XT_OUTBAR_INFO*)lParam;
	
	switch (nBarAction)
	{
	case OBN_XT_ITEMCLICK:
		if (CHECKVALIDATE)
			AfxGetMainWnd()->SendMessage(WM_USER, WPARAM(pOBInfo->lpszData), LPARAM(1));
		break;
		
	default:		
		break;
	}
	
	return TRUE;
}


BOOL COutlookBar::GetFromXML(LPCTSTR szFile)
{
	Clean();
	CString sFile = szFile;
	if (szFile == NULL)
	{
		sFile = AfxGetApp()->m_pszHelpFilePath;
		sFile.Delete(sFile.GetLength() - 3, 3);
		sFile += _T("manifest");
	}

	

	return TRUE;
}

BOOL COutlookBar::GetFromPath(LPCTSTR szPath)
{
	Clean();

	// get so file and their Handle
	CStringArray arFiles;	
	{
		CFileFind ff;
		CString csPath = szPath;
		csPath.TrimRight("\\");
		csPath += _T("\\*.so");
		csPath.TrimLeft("\\");
		
		BOOL b = ff.FindFile(csPath);
		while (b)
		{
			b = ff.FindNextFile();
			if (ff.IsDots() || ff.IsDirectory()) continue;
			arFiles.Add(ff.GetFilePath());
		}
	}
	
	m_arStart.Add(0);
	
	// get so files Handle
	for (int i = arFiles.GetSize() - 1; i >= 0; i--)
	{
		HINSTANCE hDLL = LoadLibrary(arFiles[i]);
		if( !hDLL )	continue;

		// get function point;
		typedef int (*LPDLLFUNC) (CMultiDocTemplate** &);
		LPDLLFUNC lpDllFunc = (LPDLLFUNC)::GetProcAddress(hDLL, "GetDocTemplates");
		if ( !lpDllFunc )
		{
			FreeLibrary(hDLL);
			continue;
		}
		
		// get document templates and their number;
		CMultiDocTemplate** pTemplates = NULL;
		CString sName("");
		int nTemplate = lpDllFunc(pTemplates);
		
		// check so file has doctemplates
		if (!pTemplates || nTemplate <= 0)  
		{
			FreeLibrary(hDLL);
			continue;
		}
		
		m_arHandles.Add(hDLL);
		sName= GetModuleProductName(arFiles[i].GetBuffer(0));
		m_arFolder.Add(sName);
		
		for (int j = 0; j < nTemplate; j++)
		{
			CMultiDocTemplate* pCurTpl = pTemplates[j];

			// get Document Template Resource ID
			UINT uIconID = *(UINT*)((char*)pCurTpl + 64);

			// Load ICON
			HICON hIcon = ::LoadIcon(hDLL, MAKEINTRESOURCE(uIconID));
			if (hIcon == NULL)
				hIcon = AfxGetApp()->LoadIcon(IDR_EDFRAMETYPE);
			m_ImageSmall.Add(hIcon);
			m_ImageLarge.Add(hIcon);

			// Load FileExts, Texts
			static TCHAR szMain[MAX_PATH*2];
			CString sDocExt(""), sTplName("");
			::LoadString(hDLL, uIconID, szMain, MAX_PATH*2);
			sName = szMain + 1; //leave the first \n

			sTplName = sName.Left(sName.Find('\n'));
			m_arTexts.Add(sTplName);
			
			for (int k = 0; k < 3; k++)
				sName = sName.Right(sName.GetLength() - sName.Find('\n', 0) - 1);
			sDocExt = sName.Left(sName.Find('\n'));
			m_arFiles.Add(sDocExt);

			// Add document template
			AfxGetApp()->AddDocTemplate(pCurTpl);
		}

		m_arStart.Add(m_arTexts.GetSize());
	}

	return TRUE;
}

void COutlookBar::Clean(BOOL bDelDocManager)
{
	if (bDelDocManager)
	{
		CDocManager* pDocManager = AfxGetApp()->m_pDocManager;
		delete pDocManager;
		pDocManager = NULL;
	}

	while (m_ImageLarge.GetImageCount() > 0) m_ImageLarge.Remove(0);
	while (m_ImageSmall.GetImageCount() > 0) m_ImageSmall.Remove(0);
	
	for (int i  = m_arHandles.GetSize() - 1; i >= 0; i--)
		FreeLib(m_arHandles[i]);	
	m_arHandles.RemoveAll();

	m_arStart.RemoveAll();
	m_arFiles.RemoveAll();
	m_arTexts.RemoveAll();
	m_arFolder.RemoveAll();
}

CString COutlookBar::GetModuleProductName(LPSTR szFileName)
{
	void * VerData = NULL;
	CString sRet("");
	try 
	{		
		DWORD   hInfo;
		DWORD   dwLen;
		dwLen = GetFileVersionInfoSize(szFileName, &hInfo);
		
		if (dwLen == 0)
			throw(0); //AfxThrowUserException();
		
		VerData = (void *) new char[dwLen];
		if (VerData == NULL)
			throw(0); //AfxThrowMemoryException();
		
		if (!GetFileVersionInfo(szFileName, hInfo,  dwLen, VerData))
			throw(0);
		
		struct {
			WORD    first;
			WORD    second;
		} *lpBuffer;
		
		VerQueryValue(VerData, _T("\\VarFileInfo\\Translation"),
            (LPVOID*) &lpBuffer,(unsigned int *) &dwLen);
		
		if (dwLen==0)
			throw(0); //AfxThrowUserException();
		
		unsigned int    uSize;
		LPCTSTR         pBuffer;
		CString			sBlock;
		sBlock.Format(_T("\\StringFileInfo\\%04x%04x\\ProductName"), lpBuffer->first, lpBuffer->second);		
		if ( VerQueryValue(VerData, (char *)((LPCTSTR) sBlock), (void**)&pBuffer, &uSize) )
			sRet = pBuffer;
		
	}
	catch (int) {
		;
	}
	
	if (VerData) 
		delete VerData;

	return sRet;
}
