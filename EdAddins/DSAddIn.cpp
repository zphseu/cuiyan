// AddInMod.cpp : implementation file
//

#include "stdafx.h"
#include "EdAddins.h"
#include "DSAddIn.h"
#include "Commands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "TimeWinAutoSave.h"
CTimeWinAutoSave *gTimeWin = NULL;

// This is called when the user first loads the add-in, and on start-up
//  of each subsequent Developer Studio session
STDMETHODIMP CDSAddIn::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime,
		long dwCookie, VARIANT_BOOL* OnConnection)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	// Store info passed to us
	IApplication* pApplication = NULL;
	if (FAILED(pApp->QueryInterface(IID_IApplication, (void**) &pApplication))
		|| pApplication == NULL)
	{
		*OnConnection = VARIANT_FALSE;
		return S_OK;
	}

	m_dwCookie = dwCookie;

	// Create command dispatch, send info back to DevStudio
	CCommandsObj::CreateInstance(&m_pCommands);
	m_pCommands->AddRef();

	// The QueryInterface above AddRef'd the Application object.  It will
	//  be Release'd in CCommand's destructor.
	m_pCommands->SetApplicationObject(pApplication);

	// (see stdafx.h for the definition of VERIFY_OK)

	VERIFY_OK(pApplication->SetAddInInfo((long) AfxGetInstanceHandle(),
		(LPDISPATCH) m_pCommands, IDR_TOOLBAR_MEDIUM, IDR_TOOLBAR_LARGE, m_dwCookie));

	// Inform DevStudio of the commands we implement

	// TODO: Replace the AddCommand call below with a series of calls,
	//  one for each command your add-in will add.

	// The command name should not be localized to other languages.  The 
	//  tooltip, command description, and other strings related to this
	//  command are stored in the string table (IDS_CMD_STRING) and should
	//  be localized.

	LPCTSTR szCommand;
	VARIANT_BOOL bRet;
	CString strCmdString;
	INT nBtn = 0;
	{
		szCommand = _T("InsertCommentFile");
		strCmdString.LoadString(IDS_CMD_INSCMTFILE);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(_T("InsertCommentFile"));
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, nBtn++, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		if (bFirstTime == VARIANT_TRUE)
		{
			VERIFY_OK(pApplication->
				AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		}
	}

	{
		szCommand = _T("InsertCommentFun");
		strCmdString.LoadString(IDS_CMD_INSCMTFUN);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(_T("InsertCommentFun"));
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, nBtn++, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		if (bFirstTime == VARIANT_TRUE)
		{
			VERIFY_OK(pApplication->
				AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		}
	}

	{
		szCommand = _T("InsertCommentHis");
		strCmdString.LoadString(IDS_CMD_INSCMTHIS);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(_T("InsertCommentHis"));
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, nBtn++, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		if (bFirstTime == VARIANT_TRUE)
		{
			VERIFY_OK(pApplication->
				AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		}
	}

	{
		szCommand = _T("InsertCommentSX");
		strCmdString.LoadString(IDS_CMD_INSCMTSX);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(_T("InsertCommentSX"));
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, nBtn++, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		if (bFirstTime == VARIANT_TRUE)
		{
			VERIFY_OK(pApplication->
				AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		}
	}

	{
		szCommand = _T("InsertCommentSMore");
		strCmdString.LoadString(IDS_CMD_INSCMTSM);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(_T("InsertCommentSMore"));
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, nBtn++, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		if (bFirstTime == VARIANT_TRUE)
		{
			VERIFY_OK(pApplication->
				AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		}
	}

	{
		szCommand = _T("InsertCommentSLine");
		strCmdString.LoadString(IDS_CMD_INSCMTSLINE);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(_T("InsertCommentSLine"));
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, nBtn++, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		if (bFirstTime == VARIANT_TRUE)
		{
			VERIFY_OK(pApplication->
				AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		}
	}

	{
		szCommand = _T("SwitchCmt");
		strCmdString.LoadString(IDS_CMD_SWITCHCMT);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(_T("SwitchCmt"));
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, nBtn++, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		if (bFirstTime == VARIANT_TRUE)
		{
			VERIFY_OK(pApplication->
				AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		}
	}

	{
		szCommand = _T("CreateHelpHtml");
		strCmdString.LoadString(IDS_CMD_CREATEHTML);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(_T("CreateHelpHtml"));
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, nBtn++, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		if (bFirstTime == VARIANT_TRUE)
		{
			VERIFY_OK(pApplication->
				AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		}
	}

	{
		szCommand = _T("Config");
		strCmdString.LoadString(IDS_CMD_CONFIG);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(_T("Config"));
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, nBtn++, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		if (bFirstTime == VARIANT_TRUE)
		{
			VERIFY_OK(pApplication->
				AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		}
	}

	{
		szCommand = _T("MsgBoxWiz");
		strCmdString.LoadString(IDS_CMD_MSGBOXWIZ);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(_T("MsgBoxWiz"));
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, nBtn++, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		if (bFirstTime == VARIANT_TRUE)
		{
			VERIFY_OK(pApplication->
				AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		}
	}

	{
		szCommand = _T("LineCount");
		strCmdString.LoadString(IDS_CMD_LINECOUNT);
		strCmdString = szCommand + strCmdString;
		CComBSTR bszCmdString(strCmdString);
		CComBSTR bszMethod(_T("LineCount"));
		CComBSTR bszCmdName(szCommand);
		VERIFY_OK(pApplication->AddCommand(bszCmdString, bszMethod, nBtn++, m_dwCookie, &bRet));
		if (bRet == VARIANT_FALSE)
		{
			*OnConnection = VARIANT_FALSE;
			return S_OK;
		}
		if (bFirstTime == VARIANT_TRUE)
		{
			VERIFY_OK(pApplication->
				AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
		}
	}

	gTimeWin = new CTimeWinAutoSave;
	gTimeWin->setApplication(pApplication);
	gTimeWin->Create(NULL, "AutoSave Timer Window", WS_OVERLAPPEDWINDOW & ~WS_VISIBLE);
	
	*OnConnection = VARIANT_TRUE;
	return S_OK;

}

// This is called on shut-down, and also when the user unloads the add-in
STDMETHODIMP CDSAddIn::OnDisconnection(VARIANT_BOOL bLastTime)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_pCommands->UnadviseFromEvents();
	m_pCommands->Release();
	m_pCommands = NULL;

	// TODO: Perform any cleanup work here
	gTimeWin->DestroyWindow();
	return S_OK;
}

