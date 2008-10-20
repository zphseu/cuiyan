// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "EdFc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FreeLib(hDLL)	{ if(hDLL) { FreeLibrary(hDLL); (hDLL)=NULL; } }
#define SAFE_DELWND(p)	{ if( p )  { (p)->DestroyWindow(); (p)=NULL; } }
#define SAFE_DELETE(p)  { if( p )  { delete (p); (p)=NULL; } }

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_OUTLOOK_BAR, OnViewOutlookBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTLOOK_BAR, OnUpdateViewOutlookBar)
	//}}AFX_MSG_MAP
	ON_MESSAGE(IDM_LOADVIEW, OnLoadView)	// for COutLookBar;
	ON_MESSAGE(WM_LOAD_VIEW, MsgLoadView)	// for Users' Views
	ON_MESSAGE(WM_GETTOOLBAR, MsgGetToolBar)	// for Users' Views
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_hDLL = NULL;
	m_pDefView = NULL;
	m_ptbImages = NULL;
}

CMainFrame::~CMainFrame()
{
	FreeLib(m_hDLL);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
	{
		TRACE0("Failed to create Toolbar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndBmpBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
	{
		TRACE0("Failed to create Toolbar\n");
		return -1;      // fail to create
	}
    
	if (!m_wndOutlookBar.Create(_T("Report Bar"), this, 0))
    {
        TRACE0("Failed to create Reportbar\n");
        return -1;      // fail to create
	}
	
    m_wndOutlookBar.SetBarStyle(m_wndOutlookBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
    m_wndOutlookBar.EnableDocking(CBRS_ALIGN_ANY);	
	EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndOutlookBar, AFX_IDW_DOCKBAR_LEFT);
	ShowControlBar(&m_wndOutlookBar, m_wndOutlookBar.IsVisible(), FALSE);

	m_nCurBar = 1;	
	EableToolBarMenu(0, 0);
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
VOID CMainFrame::ShowMessage(const char *fmt, ...)
{
	TCHAR str[2048];
	va_list ap;
	va_start(ap, fmt);
	vsprintf(str, fmt, ap);
	va_end(ap);
	AfxMessageBox(str);
}

HRESULT CMainFrame::LoadView(LPCSTR szDll, LPCSTR szView, LPCSTR szData)
{
	HRESULT nReturn = 0;
	CView *pNewView = NULL;
	CView *pOldView = GetActiveView();
	HINSTANCE hOldDLL = m_hDLL;

	try 
	{
		CString csDll = AfxGetApp()->m_pszHelpFilePath;
		csDll = csDll.Left(csDll.ReverseFind('\\')) + CString("\\bin\\");
		m_hDLL = LoadLibrary(csDll + szDll);
		
		if( !m_hDLL )
			m_hDLL = LoadLibrary(szDll);
		
		if( !m_hDLL) 	{
			ShowMessage("没有找到模块 [%s] 或 [%s] ！", szDll, csDll);
			throw -1;
		}
		
		typedef BOOL (*LPDLLFUNC) (LPCSTR, LPCSTR, CRuntimeClass*&, UINT&, UINT&);
		LPDLLFUNC lpfnDllFunc = (LPDLLFUNC)::GetProcAddress(m_hDLL, "GetView");
		if (!lpfnDllFunc)	{
			ShowMessage(" [%s] 不是EdFC模块！", szDll);
			throw -2;
		}
		
		CRuntimeClass* pNewViewClass = NULL;
		UINT nToolBarRes = 0;
		UINT nToolBarBmp = 0;
		
		if (!lpfnDllFunc(szView, szData, pNewViewClass, nToolBarRes, nToolBarBmp))
		{
			ShowMessage("模块 [%s] 中没有标识为 [%s] 的View！", szDll, szView);
			throw -3;
		}
		ASSERT(pNewViewClass);
		
		if (pOldView->IsKindOf(pNewViewClass))
		{
			EableToolBarMenu(nToolBarRes, nToolBarBmp);			
			throw -4;
		}
		
		CCreateContext context;
		context.m_pNewViewClass = pNewViewClass;
		context.m_pCurrentDoc = GetActiveDocument();
		
		pNewView = STATIC_DOWNCAST(CView, CreateView(&context));
		if (pNewView == NULL) {
			ShowMessage("无法创建模块 [%s] 中标识为 [%s] 的View！", szDll, szView);
			throw -5;
		}
		
		EableToolBarMenu(nToolBarRes, nToolBarBmp);	
		pNewView->OnInitialUpdate();
		::SetWindowLong(pOldView->m_hWnd, GWL_ID, 0);
		
		pOldView->ShowWindow(SW_HIDE);
		pNewView->ShowWindow(SW_SHOW);
		pNewView->RedrawWindow();
		SetActiveView(pNewView);
		
		if (pOldView != m_pDefView)
		{
			if(pOldView && ::IsWindow(pOldView->m_hWnd)) 
				SAFE_DELWND(pOldView);
		}
		FreeLib(hOldDLL);
	}
	catch (int i)
	{
		nReturn = i;
		FreeLib(m_hDLL);
	}
	
	RecalcLayout();
	return nReturn;
}

HRESULT CMainFrame::OnLoadView(WPARAM wParam, LPARAM lParam) 
{
	XT_OUTBAR_INFO* pOBInfo = (XT_OUTBAR_INFO*)lParam;
	if (pOBInfo != NULL)	
		return LoadView(pOBInfo->lpszDll, pOBInfo->lpszView, pOBInfo->lpszData);
	else
		return -1;
}

/**
 *  用于子窗口调用其他View.
 *  为框架的定义接口.
 *
 *  @param  -[in]  WPARAM  wParam: [为一个LPCSTR, szDll]
 *  @param  -[in]  LPARAM  lParam: [为一个LPCSTR，szView;szData]
 *
 *  @version  06/25/2003  cuiyan  Initial Version.
 */
HRESULT CMainFrame::MsgLoadView(WPARAM wParam, LPARAM lParam)
{
	CString strDll((LPCTSTR)wParam);
	CString strView((LPCTSTR)lParam);
	CString strData;
	
	int nFind = strView.ReverseFind(';');
	if (nFind > 0)
	{
		strData = strView.Right(strView.GetLength() - nFind - 1);
		strView = strView.Left(nFind);
	}
	
	return LoadView(strDll, strView, strData);
}

HRESULT CMainFrame::MsgGetToolBar(WPARAM wParam, LPARAM lParam)
{
	CToolBar* pWndCurBar = NULL;

	if (m_nCurBar == 1)
		pWndCurBar = &m_wndToolBar;
	else if (m_nCurBar == 2)
		pWndCurBar = &m_wndBmpBar;

	return (HRESULT)pWndCurBar;
}

void CMainFrame::OnViewOutlookBar() 
{
	ShowControlBar(&m_wndOutlookBar, !m_wndOutlookBar.IsVisible(), FALSE);
	GetActiveView()->RedrawWindow();
}

void CMainFrame::OnUpdateViewOutlookBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndOutlookBar.IsVisible());
}

void CMainFrame::EableToolBarMenu(UINT nToolBarRes, UINT nToolBarBmp)
{	
	CMenu* pMenu = GetMenu();
	if (!pMenu)	return;
	
 	CMenu* pSubMenu = pMenu->GetSubMenu(1);//??

	static CString csName;
	if (csName.IsEmpty())
		pSubMenu->GetMenuString(ID_VIEW_TOOLBAR, csName, MF_BYCOMMAND);

	int nNeedBar = GetBarType(nToolBarRes, nToolBarBmp);

	if ( nNeedBar &&  !m_nCurBar)
		pSubMenu->InsertMenu(0, MF_BYPOSITION, ID_VIEW_TOOLBAR, csName);
	else if ( !nNeedBar && m_nCurBar)
		pSubMenu->RemoveMenu(ID_VIEW_TOOLBAR, MF_BYCOMMAND);

	if (nNeedBar != m_nCurBar)
	{
		if (m_nCurBar == 1 && nNeedBar == 0)
			ShowControlBar(&m_wndToolBar, FALSE, FALSE);
		else if (m_nCurBar == 2 && nNeedBar == 0)
			ShowControlBar(&m_wndBmpBar, FALSE, FALSE);
		else if (m_nCurBar == 0 && nNeedBar == 1)
			ShowControlBar(&m_wndToolBar, TRUE, FALSE);
		else if (m_nCurBar == 0 && nNeedBar == 2)
			ShowControlBar(&m_wndBmpBar, TRUE, FALSE);
		else if ((m_nCurBar == 2 && nNeedBar == 1) || (m_nCurBar == 1 && nNeedBar == 2))
		{
			ShowControlBar(&m_wndToolBar, (nNeedBar == 1), FALSE);
			ShowControlBar(&m_wndBmpBar, (nNeedBar == 2), FALSE);		
		}
	}
	
	if (nNeedBar)
	{
		AfxSetResourceHandle(m_hDLL);
		
		if (nNeedBar == 2)
		{
			m_wndBmpBar.LoadToolBar(nToolBarRes);
			SAFE_DELETE(m_ptbImages);
			m_ptbImages = new CImageList;
 			MakeToolbarImageList(nToolBarBmp, *m_ptbImages);
			m_wndBmpBar.GetToolBarCtrl().SetImageList(m_ptbImages);
		}
		else
			m_wndToolBar.LoadToolBar(nToolBarRes);
		
		AfxSetResourceHandle(AfxGetInstanceHandle());
	}

	m_nCurBar = nNeedBar;
}

int CMainFrame::GetDefaultView()
{
	m_pDefView = GetActiveView();
	GetActiveDocument()->SetTitle( m_wndOutlookBar.m_csEdFcName );	
	return 0;
}

BOOL CMainFrame::DestroyWindow() 
{
	CView* pCurView = GetActiveView();
	if (pCurView != m_pDefView)
	{
		pCurView->ShowWindow(SW_HIDE);
		if(pCurView && ::IsWindow(pCurView->m_hWnd)) 
			SAFE_DELWND(pCurView);
	}
	
	SAFE_DELETE(m_ptbImages);
	FreeLib(m_hDLL);
	return CFrameWnd::DestroyWindow();
}

// create an image list for the specified BMP resource
void CMainFrame::MakeToolbarImageList(UINT inBitmapID , CImageList& imglst)
{
	CBitmap	bm;

	VERIFY (bm.Attach (::LoadImage (::AfxFindResourceHandle(
		MAKEINTRESOURCE (inBitmapID), RT_BITMAP),
		MAKEINTRESOURCE (inBitmapID), IMAGE_BITMAP, 0, 0,
		(LR_DEFAULTSIZE | LR_CREATEDIBSECTION))));

	// figure out how many pixels there are in the bitmap
	BITMAP		bmInfo;
	VERIFY (bm.GetBitmap (&bmInfo));

	ReplaceBackgroundColor(bm);

	VERIFY (imglst.Create (bmInfo.bmHeight, bmInfo.bmHeight, 
		bmInfo.bmBitsPixel, bmInfo.bmWidth / bmInfo.bmHeight, 0));

	// attach the bitmap to the image list
	VERIFY (imglst.Add (&bm, RGB (0, 0, 0)) != -1);
}

// replace the specified color in the bitmap with the user's
// button color. find every pixel of the default background color
// in the specified	bitmap and set each one to the user's button color.
void CMainFrame::ReplaceBackgroundColor(CBitmap& bm)
{
	BITMAP		bmInfo;
	VERIFY (bm.GetBitmap (&bmInfo));

	const UINT numPixels (bmInfo.bmHeight * bmInfo.bmWidth);
	const COLORREF	buttonColor (::GetSysColor (COLOR_BTNFACE));

	DIBSECTION  ds;
	VERIFY (bm.GetObject (sizeof (DIBSECTION), &ds) == sizeof (DIBSECTION));

	switch (bmInfo.bmBitsPixel)
	{
	case 8:
		{
			TCHAR userBackgroundColor = TCHAR(77);

			VERIFY (bmInfo.bmWidthBytes == bmInfo.bmWidth);
			TCHAR*	pixels = reinterpret_cast<TCHAR*>(ds.dsBm.bmBits);
			VERIFY (pixels != NULL);
			for (UINT i = 1; i < numPixels; ++i)
			{
				if (pixels [i] == pixels [0])
				{
					pixels [i] = userBackgroundColor;
				}
			}
			pixels[0] = userBackgroundColor;
		}
		break;

	case 24:
		{
			VERIFY (bmInfo.bmWidthBytes == (bmInfo.bmWidth * 3));
			RGBTRIPLE*	pixels = reinterpret_cast<RGBTRIPLE*>(ds.dsBm.bmBits);
			VERIFY (pixels != NULL);
			// get the user's preferred button color from the system
			const RGBTRIPLE	userBackgroundColor = {
				GetBValue (buttonColor), 
					GetGValue (buttonColor), 
					GetRValue (buttonColor)
			};
			for (UINT i = 1; i < numPixels; ++i)
			{
				if (pixels [i].rgbtBlue == pixels [0].rgbtBlue &&
					pixels [i].rgbtGreen == pixels [0].rgbtGreen &&
					pixels [i].rgbtRed == pixels [0].rgbtRed)
				{
					pixels [i] = userBackgroundColor;
				}
			}
			pixels[0] = userBackgroundColor;
		}
		break;

	default:
		break;
	}
}

int CMainFrame::GetBarType(UINT nToolBarRes, UINT nToolBarBmp)
{
	int nBarType = 0;
	if (nToolBarRes > 0 && nToolBarBmp > 0)
		nBarType = 2;
	else if (nToolBarRes > 0 &&  nToolBarBmp <= 0)
		nBarType = 1;
	return nBarType;
}

