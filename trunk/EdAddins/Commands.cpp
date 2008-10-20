// Commands.cpp : implementation file
//

#include "stdafx.h"
#include "EdAddins.h"
#include "Commands.h"

#include "CommentData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CCommentData cmtData;

/////////////////////////////////////////////////////////////////////////////
// CCommands

CCommands::CCommands()
{
	m_pApplication = NULL;
	m_pApplicationEventsObj = NULL;
	m_pDebuggerEventsObj = NULL;
}

CCommands::~CCommands()
{
	ASSERT (m_pApplication != NULL);
	m_pApplication->Release();
}

void CCommands::SetApplicationObject(IApplication* pApplication)
{
	// This function assumes pApplication has already been AddRef'd
	//  for us, which CDSAddIn did in its QueryInterface call
	//  just before it called us.
	m_pApplication = pApplication;

	// Create Application event handlers
	XApplicationEventsObj::CreateInstance(&m_pApplicationEventsObj);
	m_pApplicationEventsObj->AddRef();
	m_pApplicationEventsObj->Connect(m_pApplication);
	m_pApplicationEventsObj->m_pCommands = this;

	// Create Debugger event handler
	CComPtr<IDispatch> pDebugger;
	if (SUCCEEDED(m_pApplication->get_Debugger(&pDebugger)) 
		&& pDebugger != NULL)
	{
		XDebuggerEventsObj::CreateInstance(&m_pDebuggerEventsObj);
		m_pDebuggerEventsObj->AddRef();
		m_pDebuggerEventsObj->Connect(pDebugger);
		m_pDebuggerEventsObj->m_pCommands = this;
	}
}

void CCommands::UnadviseFromEvents()
{
	ASSERT (m_pApplicationEventsObj != NULL);
	m_pApplicationEventsObj->Disconnect(m_pApplication);
	m_pApplicationEventsObj->Release();
	m_pApplicationEventsObj = NULL;

	if (m_pDebuggerEventsObj != NULL)
	{
		// Since we were able to connect to the Debugger events, we
		//  should be able to access the Debugger object again to
		//  unadvise from its events (thus the VERIFY_OK below--see stdafx.h).
		CComPtr<IDispatch> pDebugger;
		VERIFY_OK(m_pApplication->get_Debugger(&pDebugger));
		ASSERT (pDebugger != NULL);
		m_pDebuggerEventsObj->Disconnect(pDebugger);
		m_pDebuggerEventsObj->Release();
		m_pDebuggerEventsObj = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Event handlers

// TODO: Fill out the implementation for those events you wish handle
//  Use m_pCommands->GetApplicationObject() to access the Developer
//  Studio Application object

// Application events

HRESULT CCommands::XApplicationEvents::BeforeBuildStart()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BuildFinish(long nNumErrors, long nNumWarnings)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeApplicationShutDown()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentOpen(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeDocumentClose(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentSave(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewDocument(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowActivate(IDispatch* theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowDeactivate(IDispatch* theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceOpen()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceClose()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewWorkspace()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

// Debugger event

HRESULT CCommands::XDebuggerEvents::BreakpointHit(IDispatch* pBreakpoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CCommands methods

#include "dlgmsgboxwiz.h"
STDMETHODIMP CCommands::MsgBoxWiz()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));

	CDlgMsgBoxWiz dlg;
	if (dlg.DoModal() == IDOK)		//Insert MsgBox text
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
			VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
		
		IGenericDocument* pDoc;
		m_pApplication->get_ActiveDocument((IDispatch**)&pDoc);		
		if (!pDoc)
		{
			VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
			return S_OK;
		}
		
		ITextSelection* pSel;
		((ITextDocument*)pDoc)->get_Selection((IDispatch**)&pSel);
		if (!pSel)
		{
			pDoc->Release();
			VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
			return S_OK;
		}
		
		CComBSTR bstr;
		pSel->get_Text(&bstr);
		bstr = dlg.m_msgbox.AllocSysString();
		pSel->put_Text(bstr);
		
		pSel->Release();
		pDoc->Release();
		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
		return S_OK;

	}
	
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	return S_OK;
}

#include "DlgCountRep.h"
STDMETHODIMP CCommands::LineCount()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (EDADDINS_SSDSDK)
	{
		CString wsName;
		
		AfxGetApp()->GetMainWnd()->GetWindowText(wsName);
		int npos = wsName.Find(" - Microsoft Visual C++");
		if (npos > 0)
		{
			wsName = wsName.Left(npos) + ".dsw";
			CDlgCountRep dlg(m_pApplication);
			dlg.SetWsName(wsName);
			dlg.DoModal();
		}
		else	
			AfxMessageBox("please open a file of this workspace firstly");
	}
	
	return S_OK;
}


#include "dlgconfig.h"
STDMETHODIMP CCommands::Config()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CDlgConfig dlg;
	dlg.DoModal();

	return S_OK;
}

VOID CCommands::InsertComments(CString type)
{	
	IGenericDocument* pDoc = NULL;
	m_pApplication->get_ActiveDocument((IDispatch**)&pDoc);		
	if (!pDoc)
	{
		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
		return;
	}
	
	CComBSTR bstr = "";
	pDoc->get_Name( &bstr );
	CString strTmp = bstr;
	strTmp.MakeLower();
	if ( !( strTmp.Find(".cpp") > 0 || strTmp.Find(".c") > 0 || strTmp.Find(".cxx") > 0 ||
			strTmp.Find(".hpp") > 0 || strTmp.Find(".h") > 0 || strTmp.Find(".hxx") > 0 ||
			strTmp.Find(".rc") > 0 || strTmp.Find(".odl") > 0 || strTmp.Find(".idl")> 0 ||
			strTmp.Find(".inl") > 0 ) )
	{
		return;
	}

	ITextSelection* pSel = NULL;
	((ITextDocument*)pDoc)->get_Selection((IDispatch**)&pSel);
	if (!pSel)
	{
		pDoc->Release();
		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
		return;
	}

	bstr = "";
	pSel->put_Text(bstr);
	
	// set line and indentsize
	long line, column, indentsize;
	pSel->get_CurrentLine(&line);
	pSel->get_CurrentColumn(&column);
	((ITextDocument*)pDoc)->get_IndentSize(&indentsize);
	CString strTab;
	// Sameline comment not to indent.
	if ( type.Find("commentSameLine") < 0)
	{
		for (int i = 0; i < column / indentsize; i++)
		{
			strTab += '\t';
		}
	}
	
	// file commeent not to indent
	if ( type.Find("cppHeaderFile") >= 0)
	{
		line = 1;
		strTab = _T("");
		CComVariant varSelMode = dsMove;
		pSel->GoToLine(line, varSelMode);
	}

	// get comment
	if (!cmtData.GetComments(m_pApplication, type ) )
		return;

	POSITION pos = cmtData.m_szlComments.GetHeadPosition();
	
	strTmp = _T("");
	while(pos)
	{
		strTmp +=  cmtData.m_szlComments.GetNext(pos) + strTab ;
	}
	
	bstr = strTmp.AllocSysString();
	pSel->put_Text(bstr);

		if ( type.Find("commentSameLine") >= 0 )
	{
		CComVariant varDelMode = dsVertical;
		pSel->DeleteWhitespace(varDelMode);		
	}

	CComVariant varSelMode = dsMove;
	pSel->GoToLine(line, varSelMode);

	pSel->Release();
	pDoc->Release();
}

STDMETHODIMP CCommands::InsertCommentFile()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));

	InsertComments( _T("cppHeaderFile") );

	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));

	return S_OK;
}

STDMETHODIMP CCommands::InsertCommentFun()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (EDADDINS_SSDSDK)
	{
		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
		InsertComments( _T("cppMethod") );
		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	}

	return S_OK;
}

STDMETHODIMP CCommands::InsertCommentHis()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));

	InsertComments( _T("cRevisionHistory") );

	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));

	return S_OK;
}

STDMETHODIMP CCommands::InsertCommentSx()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));

	InsertComments( _T("commentSX") );

	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	return S_OK;
}

STDMETHODIMP CCommands::InsertCommentSMore()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));

	InsertComments( _T("commentSMore") );

	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	return S_OK;
}

STDMETHODIMP CCommands::InsertCommentSLine()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));

	InsertComments( _T("commentSameLine") );

	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	return S_OK;
}

// for doxylib 
#include <process.h>
#include <comdef.h>
#include "DlgChm.h"
STDMETHODIMP CCommands::CreateHelpHtml()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	if (!EDADDINS_SSDSDK)
		return S_FALSE;

	CDlgChm dlg;
	dlg.m_bOpen = cmtData.m_bOpen;
	if (dlg.DoModal() == IDOK)
	{
		cmtData.m_strPrivate = (dlg.m_bPrivate) ? _T("YES") : _T("NO");
		cmtData.m_strStatic = (dlg.m_bStatic) ? _T("YES") : _T("NO");
		cmtData.m_strLanguage = (dlg.m_nLanguage == 0) ? _T("English") : _T("Chinese");
		cmtData.m_bOpen = dlg.m_bOpen;
	}
	else
		return S_OK;

	if (!cmtData.GetComments(m_pApplication, "BSDOXYFILE" ) )
	{
		AfxMessageBox("Can not get Doxygen Infomation!");
		return S_OK;
	}

	// Save the files (if enabled)
	IDocuments *pDocuments;
	m_pApplication->get_Documents((IDispatch **)&pDocuments);
	if (pDocuments)
	{
		DsSaveStatus saved;
		pDocuments->SaveAll(_variant_t(false), &saved);
	}
	pDocuments->Release();

	AfxBeginThread(CreateChmThread, NULL);
	
	return S_OK;
}

BOOL CCommands::DeletePathFile(CString strPath)
{
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strPath);
	CString strFilename;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		DeleteFile(finder.GetFilePath());
	}

	return TRUE;
}

STDMETHODIMP CCommands::SwitchCmt()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	IGenericDocument* pDoc = NULL;
	m_pApplication->get_ActiveDocument((IDispatch**)&pDoc);		
	if (!pDoc)
	{
		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
		return S_OK;
	}
	
	CComBSTR bstr = "";
	pDoc->get_Name( &bstr );
	CString strTmp = bstr;
	strTmp.MakeLower();
	if ( !( strTmp.Find(".cpp") > 0 || strTmp.Find(".c") > 0 || strTmp.Find(".cxx") > 0 ||
			strTmp.Find(".hpp") > 0 || strTmp.Find(".h") > 0 || strTmp.Find(".hxx") > 0 ||
			strTmp.Find(".rc") > 0 || strTmp.Find(".odl") > 0 || strTmp.Find(".idl")> 0 ||
			strTmp.Find(".inl") > 0 ) )
	{
		return S_OK;
	}

	ITextSelection* pSel = NULL;
	((ITextDocument*)pDoc)->get_Selection((IDispatch**)&pSel);
	if (!pSel)
	{
		pDoc->Release();
		VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
		return S_OK;
	}

	pSel->get_Text( &bstr);
	CString strCode = bstr;
	strTmp = strCode;
	strTmp.TrimLeft();

	if (strTmp.IsEmpty())
		return S_OK;

	if (strTmp.Find("// ") == 0)
	{
		strCode = strCode.Right(strCode.GetLength() - 3);
		strCode.Replace(CString(TCHAR(10)) + CString("// "), CString(TCHAR(10)));
	}
	else
	{
		strCode = CString("// ") + strCode;
		strCode.Replace(CString(TCHAR(10)), CString(TCHAR(10)) + CString("// "));
		strCode.Replace(CString("// //"), CString("// "));
	}

	bstr = strCode.AllocSysString();
	pSel->put_Text( bstr );
		
	return S_OK;
}

BOOL CCommands::Wait(CString szCmdLine)
{
    LPTHREADINFO pThreadInfo = new THREADINFO;
    CEvent *pThreadEvent = new CEvent(FALSE, TRUE); 
    ASSERT_VALID(pThreadEvent);
    if(pThreadInfo)
    {
        pThreadInfo->pTermThreadEvent = pThreadEvent;
        pThreadInfo->szCmdLine = szCmdLine;

        AfxBeginThread(LaunchAndWait, pThreadInfo);
        WaitForSingleObject(pThreadEvent->m_hObject, INFINITE);
        return TRUE;
    }
    return FALSE;
}

UINT CCommands::LaunchAndWait(LPVOID pParam)
{
    LPTHREADINFO pThreadInfo = (LPTHREADINFO) pParam;

	PROCESS_INFORMATION processInfo;
	STARTUPINFO startInfo;
	GetStartupInfo( &startInfo ); 
	startInfo.dwFlags = STARTF_USESHOWWINDOW;
	startInfo.wShowWindow = SW_HIDE;

	LPTSTR lpszExe = (char *)pThreadInfo->szCmdLine.operator LPCTSTR();
	BOOL bRet = CreateProcess(NULL, lpszExe, NULL, NULL, TRUE, 
		CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS,
		NULL, NULL, &startInfo, &processInfo);

    if( bRet )
    {
        HANDLE hThreads[2];
        hThreads[0] = pThreadInfo->pTermThreadEvent->m_hObject;
        hThreads[1] = processInfo.hProcess;
        DWORD dwIndex = WaitForMultipleObjects(2, hThreads, FALSE, INFINITE);
        CloseHandle(processInfo.hThread);
        CloseHandle(processInfo.hProcess);
        pThreadInfo->pTermThreadEvent->SetEvent();
        if(pThreadInfo)
            delete pThreadInfo;
    }
    else
        pThreadInfo->pTermThreadEvent->SetEvent();
    return 0;
}

UINT CCommands::CreateChmThread(LPVOID pParam)
{

	CString doxyFileName = cmtData.m_szPrjDocPath
						+ cmtData.m_szPrjFileName 
						+ CString(".dox");

	// clean docs
	CreateDirectory(cmtData.m_szPrjDocPath, NULL);
	DeletePathFile(cmtData.m_szPrjDocPath + "*.*");
	
	// create doxygen config file
	CStdioFile doxyfile;
	if (!doxyfile.Open(doxyFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		AfxMessageBox("Can not create Doxygen config file!");
		return S_OK;
	}

	POSITION pos = cmtData.m_szlComments.GetHeadPosition();
	CString strTmp;
	while(pos)
	{
		strTmp =  cmtData.m_szlComments.GetNext(pos);
		doxyfile.WriteString(strTmp);
	}
	
	doxyfile.Close();
	
	// set command line
	CString doxyExec = cmtData.m_szCmtFileName;
	strTmp = AfxGetApp()->m_pszProfileName;
	strTmp.MakeLower();
	doxyExec.Replace(strTmp, _T("Doxygen.exe\" "));
	doxyExec = CString ("\"") + doxyExec + CString ("\"") + doxyFileName + CString ("\"");
	//system(doxyExec);
	Wait(doxyExec);

	CString strHhp = cmtData.m_szPrjDocPath + "index.hhp";
	if (!doxyfile.Open(strHhp, CFile::modeRead))
	{
		AfxMessageBox("Can not Create Html files");
		return S_OK;
	}
	doxyfile.Close();

	// create chm file
	CString hhcExec = cmtData.m_szCmtFileName;
	hhcExec.Replace(strTmp, _T("hhc.exe\" "));
	hhcExec = CString ("\"") + hhcExec + CString ("\"") + strHhp + CString ("\"");
	//system(hhcExec);
	Wait(hhcExec);

	CString strChm = cmtData.m_szPrjDocPath + "index.chm";
	if (!doxyfile.Open(strChm, CFile::modeRead))
	{
		AfxMessageBox("Can not Create CHM file");
		return S_OK;
	}
	doxyfile.Close();

	CString strPrjChm = cmtData.m_szPrjPath 
						+ cmtData.m_szPrjFileName 
						+ CString(".chm");
	if ( CopyFile(strChm, strPrjChm, FALSE) && cmtData.m_bOpen )
	{
		ShellExecute(NULL, "open", strPrjChm, NULL, NULL, SW_RESTORE);
	}

#ifndef _DEBUG
	DeletePathFile(cmtData.m_szPrjDocPath + "*.*");
	RemoveDirectory(cmtData.m_szPrjDocPath);
#endif

	return S_OK;
}
