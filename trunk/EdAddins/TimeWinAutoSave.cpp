// TimeWinAutoSave.cpp : implementation file
//

#include "stdafx.h"
#include "EdAddins.h"
#include "TimeWinAutoSave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeWinAutoSave

IMPLEMENT_DYNCREATE(CTimeWinAutoSave, CFrameWnd)

CTimeWinAutoSave::CTimeWinAutoSave()
{
	m_saveFiles = true;
	m_saveWorkspace = true;
	m_bregister = false;
	m_period = 10;
	m_timer = 0;

	// Read the initial values from the registry
	CRegKey reg;
	// If it's the first time, an AddIns subkey may not exist, so we need to create it
	if (reg.Create(HKEY_CURRENT_USER, gKeyAddIns) == ERROR_SUCCESS)
	{
		HKEY key = reg.Detach();
		if (reg.Create(key, gKeyEdAddins) == ERROR_SUCCESS)
		{
			DWORD val;
			if (reg.QueryValue(val, "SaveFilesEnable") == ERROR_SUCCESS)
				m_saveFiles = val != 0;
			if (reg.QueryValue(val, "SaveWorkspaceEnable") == ERROR_SUCCESS)
				m_saveWorkspace = val != 0;
			if (reg.QueryValue(val, "ByDialog") == ERROR_SUCCESS)
				m_bByDialog = val != 0;
			if (reg.QueryValue(val, "SavePeriod") == ERROR_SUCCESS)
				m_period = val;
		}
		reg.Close();
		reg.Attach(key);
	}
}

CTimeWinAutoSave::~CTimeWinAutoSave()
{
	// Save the final parameters in the registry
	SaveParameters();
}

BEGIN_MESSAGE_MAP(CTimeWinAutoSave, CFrameWnd)
	//{{AFX_MSG_MAP(CTimeWinAutoSave)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeWinAutoSave message handlers

void CTimeWinAutoSave::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	if (m_timer)
	{
		KillTimer(m_timer);
		m_timer = 0;
	}	

	KillTimer(2);
}

int CTimeWinAutoSave::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	ParameterChanged();
	SetTimer(2, 5 * 60000, NULL);
	
	return 0;
}

void CTimeWinAutoSave::ParameterChanged()
{
	if (m_timer && ((!m_saveFiles && !m_saveWorkspace) || !m_period))
	{
		// Stop saving
		KillTimer(m_timer);
		m_timer = 0;
	}
	else if ((m_saveFiles || m_saveWorkspace) && m_period)
	{
		// Kill the previous timer
		if (m_timer)
		{
			KillTimer(m_timer);
			m_timer = 0;
		}

		// Start generating save events (time is calculated in minutes)
		m_timer = SetTimer(1, m_period * 60000, NULL);
	}

	// Store the changed parameters in the registry
	SaveParameters();

}

void CTimeWinAutoSave::SaveParameters()
{
	// Save the final parameters in the registry
	CRegKey reg;
	if (reg.Create(HKEY_CURRENT_USER, gKeyFull) == ERROR_SUCCESS)
	{
		reg.SetValue(m_saveFiles ? 1 : 0, "SaveFilesEnable");
		reg.SetValue(m_saveWorkspace ? 1 : 0, "SaveWorkspaceEnable");
		reg.SetValue(m_bByDialog ? 1 : 0, "ByDialog");
		reg.SetValue(m_period, "SavePeriod");
	}
}

void CTimeWinAutoSave::setPeriod(UINT period)
{
	if (m_period == period)
		return;

	m_period = period;
	ParameterChanged();
}

void CTimeWinAutoSave::setSaveFiles(BOOL enable)
{
	if (m_saveFiles == enable)
		return;

	m_saveFiles = enable;
	ParameterChanged();
}

void CTimeWinAutoSave::setSaveWorkspace(BOOL enable)
{
	if (m_saveWorkspace == enable)
		return;

	m_saveWorkspace = enable;
	ParameterChanged();
}

#include "dlglisence.h"
#include <comdef.h>
void CTimeWinAutoSave::OnTimer(UINT nIDEvent) 
{
	CFrameWnd::OnTimer(nIDEvent);
	
	switch(nIDEvent) {
	case 1:
		// Save the files (if enabled)
		if (m_saveFiles)
		{
			IDocuments *pDocuments;
			m_pApplication->get_Documents((IDispatch **)&pDocuments);
			if (pDocuments)
			{
				DsSaveStatus saved;
				pDocuments->SaveAll(_variant_t(false), &saved);
			}
			pDocuments->Release();
		}
		
		// Save the workspace (if enabled)
		if (m_saveWorkspace)
		{
			IGenericProject *pProject = NULL;
			m_pApplication->get_ActiveProject((IDispatch **)&pProject);
			if (pProject)
			{
				m_pApplication->ExecuteCommand(L"WorkspaceSave");
				pProject->Release();
			}
		}

		break;
	case 2:
		EDADDINS_SSDSDK;
		break;
	default:
		;
	}
}

void CTimeWinAutoSave::SetByBialog(BOOL enable)
{
	if (m_bByDialog == enable)
		return;
	
	m_bByDialog = enable;
	ParameterChanged();
}
