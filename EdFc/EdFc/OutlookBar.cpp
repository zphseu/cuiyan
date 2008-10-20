#include "StdAfx.h"
#include "Markup.h"
#include "resource.h"
#include "outlookbar.h"

COutlookBar::COutlookBar()
{
	m_csEdFcName = _T("");
}

COutlookBar::~COutlookBar()
{

}

BEGIN_MESSAGE_MAP(COutlookBar, CSizingControlBarG)
	//{{AFX_MSG_MAP(CReportBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTWM_OUTBAR_NOTIFY, OnOutbarNotify)	
END_MESSAGE_MAP()

int COutlookBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSizingControlBarG::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	if (!m_wndChild.Create( WS_CHILD | WS_VISIBLE | WS_BORDER,
		CRect(0, 0, 0, 0), this, 0))
		return -1;

	m_wndChild.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

	// Create the image lists used by the outlook bar.
	m_ImageSmall.Create (16, 16, ILC_COLOR16 | ILC_MASK, 2, 1);
	m_ImageLarge.Create (32, 32, ILC_COLOR16 | ILC_MASK, 2, 1);

	// set the image lists for the outlook bar.
	m_wndChild.SetImageList(&m_ImageLarge, OBS_XT_LARGEICON);
	m_wndChild.SetImageList(&m_ImageSmall, OBS_XT_SMALLICON);

	// We want to receive notification messages.
	m_wndChild.SetOwner(this);

	if (!LoadFromXML())
		return -1;

	if (m_wndChild.GetFolderCount() > 0)
		m_wndChild.SetSelFolder(0);

	return 0;
}

LRESULT COutlookBar::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
	int nBarAction = (int)wParam;

	switch (nBarAction)
	{
	case OBN_XT_ITEMCLICK:
		AfxGetMainWnd()->SendMessage(IDM_LOADVIEW, wParam, lParam);
		break;

	default:		
		break;
	}

	return TRUE;
}

BOOL COutlookBar::LoadFromXML()
{
	CString szPath = AfxGetApp()->m_pszHelpFilePath;
	szPath = szPath.Left(szPath.ReverseFind('\\'));

	try 
	{
#ifdef _MSVC6_
		LPCTSTR lpszFN = _T( "\\EdFc6.manifest");
#else
		LPCTSTR lpszFN = _T( "\\EdFc.manifest");
#endif
		CMarkup xml;
		CFile file( szPath + lpszFN, CFile::modeRead );
		size_t nSize = (size_t)file.GetLength();

		// Allocate Buffer for Ansi file data
		BYTE* pBuffer = new BYTE [nSize + 1];
		nSize = file.Read( pBuffer, (UINT)nSize );
		file.Close();
		pBuffer[nSize] = '\0';

		// This should convert it to unicode if it has to
		CString csDoc ((const unsigned char*) pBuffer);
		delete [] pBuffer;

		if (!xml.SetDoc( csDoc ))
			throw _T("Parse manifest file Error!");

		xml.ResetPos();
		if (!xml.FindElem() || xml.GetTagName().Compare("edfc") != 0)
			throw _T("the root tag of manifest file root tag is not edfc!");

		COLORREF crText(16777215);
		COLORREF crBack(10841658);

		m_csEdFcName = xml.GetAttrib(_T("name"));

		CString csTmp = xml.GetAttrib(_T("textcolor"));
		if (!csTmp.IsEmpty())
			crText =  (COLORREF) _ttol(csTmp);
		m_wndChild.SetTextColor(crText);		

		csTmp = xml.GetAttrib(_T("bkcolor"));
		if (!csTmp.IsEmpty())
			crBack =  (COLORREF) _ttol(csTmp);
		m_wndChild.SetBackColor(crBack);


		int iCurFolder = -1;
		while (xml.FindChildElem() && xml.GetChildTagName().Compare(_T("folder")) == 0)
		{
			xml.IntoElem();
			m_wndChild.AddFolder(xml.GetAttrib(_T("name")), iCurFolder++);

			int iCurItem = 1;
			while (xml.FindChildElem() && xml.GetChildTagName().Compare(_T("item")) == 0)
			{
				xml.IntoElem();
				CString csText = xml.GetAttrib(_T("name"));
				CString csIcon, csData, csDll, csView;

				while (xml.FindChildElem())
				{
					xml.IntoElem();
					if (xml.GetTagName().Compare(_T("dll")) == 0)
						csDll = xml.GetData();
					else if (xml.GetTagName().Compare(_T("view")) == 0)
						csView = xml.GetData();
					else if (xml.GetTagName().Compare(_T("icon")) == 0)
						csIcon = xml.GetData();
					else if (xml.GetTagName().Compare(_T("data")) == 0)
						csData = xml.GetData();
					else
						;

					xml.OutOfElem();
				}

				HICON hIcon = (HICON)::LoadImage(NULL, szPath  + CString("\\icon\\") + csIcon, IMAGE_ICON, 32, 32, 
					LR_LOADFROMFILE | LR_DEFAULTSIZE);
				if (!hIcon)
					hIcon = (HICON)::LoadImage(NULL, csIcon, IMAGE_ICON, 32, 32, LR_LOADFROMFILE | LR_DEFAULTSIZE);
				if (!hIcon)
					hIcon = AfxGetApp()->LoadIcon(IDR_EDFCTYPE);

				m_ImageSmall.Add(hIcon);
				m_ImageLarge.Add(hIcon);
				::DestroyIcon(hIcon);

				m_wndChild.InsertItem(iCurFolder, iCurItem++, m_ImageSmall.GetImageCount() - 1, csText, csDll, csView, csData);

				xml.OutOfElem();
			}
			xml.OutOfElem();
		}
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
	catch (LPCTSTR msg)
	{
		AfxMessageBox(msg);
		return FALSE;
	}
	catch (...) 
	{
		return FALSE;
	}

	return TRUE;
}

