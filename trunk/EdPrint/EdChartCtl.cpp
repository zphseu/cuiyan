// ChartCtl.cpp : Implementation of the CEdChartCtrl ActiveX Control class.

#include "stdafx.h"
#include "EdPrint.h"
#include "EdChartCtl.h"
#include "EdChartPpg.h"
#include "ChartPreview.h"
#include "Chart7/och2dMFC.cpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// Static Functions
BOOL CEdChartCtrl::GetSubString(CString& sc, LPCTSTR s, int n, TCHAR ch)
{
	CString str(s);
	
	int nStart = 0;
	for (int i = 0; i < n; i++)
	{
		nStart = str.Find(ch, nStart);
		if (nStart < 0)
			return FALSE;
		else
			nStart++;
	}

	int nStop = str.Find(ch, nStart);
	if (nStop < 0)
		nStop = str.GetLength();

	sc = str.Mid(nStart, nStop - nStart);

	return TRUE;
}

LPTSTR CEdChartCtrl::GetConfigStr(LPCTSTR lpszFileName, LPCTSTR str, INT n, LPCTSTR sdef)
{	
	CString s;
	static CString sc;
	BOOL bFind = FALSE;
	
	CStdioFile f(lpszFileName, CFile::modeRead);	
	sc.Format(_T("#%s="), str);
	while (!bFind && f.ReadString(s))
	{
		s.TrimLeft();
		bFind = s.Find(sc) == 0;
	}	
	
	f.Close();
	
	if (bFind && s.GetLength() > sc.GetLength())
	{
		s.Delete(0, sc.GetLength());
		if (n < 0)
		{
			sc = s;
			return sc.GetBuffer(0);
		}

		if ( GetSubString(sc, s, n, _T('~') ) && !sc.IsEmpty())
			return sc.GetBuffer(0);
	}
	
	return (LPTSTR)sdef;
}

LPTSTR* CEdChartCtrl::GetConfigStrs(LPCTSTR str)
{
	CString s(str), sc;
	m_ar.RemoveAll();
	for (int i = 0; GetSubString(sc, s, i, '~'); i++)
		m_ar.Add(sc);
	
	int nCount = m_ar.GetSize();
	delete [] m_pStrs;
	m_pStrs = NULL;
	m_pStrs = new LPTSTR [nCount + 1];
	for (i = 0; i < nCount; i++)
		m_pStrs[i] = m_ar[i].GetBuffer(0);
	m_pStrs[nCount] = NULL;
	
	return m_pStrs;	
}


DWORD CEdChartCtrl::GetConfigColor(LPCTSTR lpszFileName, int n, LPCTSTR sdef)
{
	DWORD dwColor;
	static TCHAR lpColor[7];
	_tcsncpy(lpColor, GetConfigStr(lpszFileName, _T("COLOR"), n, sdef), 6);
	lpColor[7] = NULL;
	
	TCHAR lpx = lpColor[0];
	lpColor[0] = lpColor[4];
	lpColor[4] = lpx;
	
	lpx = lpColor[1];
	lpColor[1] = lpColor[5];
	lpColor[5] = lpx;
	
	_stscanf(lpColor, _T("%lx"), &dwColor);
	
	return dwColor;
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CEdChartCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CEdChartCtrl, COleControl)
	//{{AFX_MSG_MAP(CEdChartCtrl)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map
BEGIN_DISPATCH_MAP(CEdChartCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CEdChartCtrl)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "HeaderFont", m_csHeaderFont, OnHeaderFontChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "HeaderStr", m_csHeaderStr, OnHeaderStrChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "FooterFont", m_csFooterFont, OnFooterFontChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "FooterStr", m_csFooterStr, OnFooterStrChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "XTitle", m_csXTitle, OnXTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "YTitle", m_csYTitle, OnYTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "LengendTitle", m_csLengendTitle, OnLengendTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "BackColor", m_clrBack, OnBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "GraphBackColor", m_clrGraphBack, OnGraphBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "AreaColor", m_clrArea, OnAreaColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "XPointNames", m_csXPointNames, OnXPointNamesChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "InvertOrientation", m_bInvertOrientation, OnInvertOrientationChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "Style3D", m_bStyle3D, OnStyle3DChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "ChartType", m_lChartType, OnChartTypeChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "YSetNames", m_csYSetNames, OnYSetNamesChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CEdChartCtrl, "AlarmZone", m_bAlarmZone, OnAlarmZoneChanged, VT_BOOL)
	DISP_FUNCTION(CEdChartCtrl, "doPrint", doPrint, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CEdChartCtrl, "doPrintPreview", doPrintPreview, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CEdChartCtrl, "ReadFile", ReadFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CEdChartCtrl, "SaveAs", SaveAs, VT_I4, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CEdChartCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CEdChartCtrl, COleControl)
	//{{AFX_EVENT_MAP(CEdChartCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CEdChartCtrl, 1)
	PROPPAGEID(CEdChartPropPage::guid)
END_PROPPAGEIDS(CEdChartCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CEdChartCtrl, "EdPrint.EdChartCtrl.1",
	0xd294db4a, 0x1a1a, 0x4461, 0x85, 0x48, 0x8d, 0xda, 0x92, 0xbb, 0x66, 0xdd)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CEdChartCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DChart =
		{ 0xa709ffab, 0x2b60, 0x47fa, { 0x9a, 0x19, 0x77, 0xd, 0xe7, 0x81, 0x4b, 0x6d } };
const IID BASED_CODE IID_DChartEvents =
		{ 0x1984c117, 0x4bc2, 0x4b32, { 0xb8, 0xfa, 0xe0, 0x9e, 0xcc, 0x8f, 0x3c, 0xd2 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwChartOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CEdChartCtrl, IDS_EDCHART, _dwChartOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CEdChartCtrl::CEdChartCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CEdChartCtrl

BOOL CEdChartCtrl::CEdChartCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_EDCHART,
			IDB_EDCHART,
			afxRegApartmentThreading,
			_dwChartOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CEdChartCtrl::CEdChartCtrl - Constructor

CEdChartCtrl::CEdChartCtrl() : m_sdTemplate(IDR_MAINFRAME, NULL, RUNTIME_CLASS(CFrameWnd), RUNTIME_CLASS(CChartPreview))
{
	InitializeIIDs(&IID_DChart, &IID_DChartEvents);
	m_pData = NULL;
	m_lChartType = XRT_TYPE_BAR;
	m_bInvertOrientation = FALSE;
	m_bAlarmZone = FALSE;
	m_bStyle3D = FALSE;
	m_pStrs = NULL;

	m_csHeaderFont = _T("Arial, 18, Bold");
	m_csHeaderStr = _T("EdChart Header");
	m_csFooterFont = _T("Arial, 10, Bold");
	m_csFooterStr = _T("EdChart Footer");
	m_csXTitle = _T("X Tilte");
	m_csYTitle = _T("Y Title");
	m_csLengendTitle = _T("Lengend");
	m_csXPointNames = _T("");
	m_clrBack = 0xCCBBAA;
	m_clrGraphBack = 0xDDCCBB;
	m_clrArea = 0xEEDDDD;
}


/////////////////////////////////////////////////////////////////////////////
// CEdChartCtrl::~CEdChartCtrl - Destructor

CEdChartCtrl::~CEdChartCtrl()
{
	m_ar.RemoveAll();
	delete m_pData;
	delete m_pStrs;
}


/////////////////////////////////////////////////////////////////////////////
// CEdChartCtrl::OnDraw - Drawing function
int CEdChartCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	RECT rectClient;
	GetClientRect(&rectClient);
	
	if (!m_Chart.Create(NULL, WS_CHILD | WS_VISIBLE, rectClient, this, 0))
	{
		DestroyWindow();
		return -1;
	}

	m_Chart.SetType((XrtType)m_lChartType);	
	m_Chart.SetAxisBoundingBox(TRUE);
	m_Chart.SetXAnnotationMethod(XRT_ANNO_POINT_LABELS);
	m_Chart.SetHeaderAdjust(XRT_ADJUST_CENTER);
	m_Chart.SetFooterAdjust(XRT_ADJUST_LEFT);
	
	return 0;
}

void CEdChartCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	OnPropertyChanged();
}

LRESULT CEdChartCtrl::OnOC2PaletteChanged(WPARAM, LPARAM)
{
    SendMessage(WM_QUERYNEWPALETTE, 0, 0);
	CFrameWnd* pParentWnd = GetParentFrame();
	if (pParentWnd && :: IsWindow(pParentWnd->m_hWnd))
		pParentWnd->SendMessage(WM_PALETTECHANGED, (WPARAM)(GetSafeHwnd()), 0);
	return 0;
}

LRESULT CEdChartCtrl::OnOC2Repaint(WPARAM wParam, LPARAM lParam)
{
    if (IsWindow(m_Chart.m_hWnd)) {
		
        RECT rect, chartRect;
        int nWidth, nHeight;
		
        /* make the chart fill the windows client area */
        GetClientRect(&rect);
        ::GetClientRect(m_Chart.m_hWnd, &chartRect);
        nWidth = chartRect.right;
        nHeight = chartRect.bottom;
		
        if (nWidth != rect.right || nHeight != rect.bottom) {
            /* adjust the window size to fit the chart */
            GetParent()->SetWindowPos(&wndTop, 0, 0, nWidth, nHeight, SWP_NOMOVE | SWP_NOZORDER);
        }
    }
	
    return TRUE;
}

void CEdChartCtrl::OnPaletteChanged(CWnd* pFocusWnd) 
{
	COleControl::OnPaletteChanged(pFocusWnd);
	m_Chart.SendMessage(WM_PALETTECHANGED, (WPARAM)pFocusWnd->GetSafeHwnd(), 0);
}

BOOL CEdChartCtrl::OnQueryNewPalette() 
{	
	return m_Chart.SendMessage(WM_QUERYNEWPALETTE, 0, 0) && COleControl::OnQueryNewPalette();
}

void CEdChartCtrl::PaintChildWindows(HWND hWndParent, CDC* pDC, CPoint ptOffset)
{
	for (HWND hWndChild = ::GetTopWindow(hWndParent);
	hWndChild != NULL; hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
	{
		CRect rect;
		::GetWindowRect(hWndChild, rect);       // window rect in screen coords
		ScreenToClient(&rect);                  // relative to this view
		
		HDC hdcOut = pDC->m_hDC;
#ifdef _DEBUG
		CPoint pt = pDC->GetWindowOrg();
		ASSERT(pt.x == 0 && pt.y == 0);
#endif
		
		DWORD dwStyle = ::GetWindowLong(hWndChild, GWL_STYLE);
		if (dwStyle & (WS_HSCROLL|WS_VSCROLL))
		{
			TRACE(_T("Warning: printing control with scrollbars not supported\n"));
		}
		if (dwStyle & WS_BORDER)
		{
			// the only case we special case handle - manually drawn border
			::Rectangle(hdcOut, rect.left, rect.top, rect.right, rect.bottom);
			rect.InflateRect(-1,-1);        // 1 logical pixel
		}
		
		pDC->SaveDC();
		{
			CPoint pt(ptOffset.x + rect.left, ptOffset.y + rect.top);
			pDC->LPtoDP(&pt);
			pDC->OffsetViewportOrg(pt.x, pt.y);
			::SendMessage(hWndChild, WM_PAINT, (WPARAM)hdcOut, 0L);
		}
		pDC->RestoreDC(-1);
		
		if (::GetTopWindow(hWndChild) != NULL)
			PaintChildWindows(hWndChild, pDC, ptOffset);
	}
}

void CEdChartCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
    if (::IsWindow(m_Chart.m_hWnd))
        m_Chart.SetWindowPos(&wndTop, 0, 0, cx, cy, SWP_NOZORDER);
}

/////////////////////////////////////////////////////////////////////////////
// CEdChartCtrl::DoPropExchange - Persistence support

void CEdChartCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
}


/////////////////////////////////////////////////////////////////////////////
// CEdChartCtrl::OnResetState - Reset control to default state

void CEdChartCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}


/////////////////////////////////////////////////////////////////////////////
// CEdChartCtrl::AboutBox - Display an "About" box to the user

void CEdChartCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_EDCHART);
	dlgAbout.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CEdChartCtrl message handlers

void CEdChartCtrl::doPrint(LPCTSTR lpszPrinterName) 
{
	HDC hDC = GetPrintHDC(this, lpszPrinterName);
	
	if (NULL == hDC)
		return;
	
	CDC dc;
	dc.Attach(hDC);         // attach a printer DC
	dc.m_bPrinting = TRUE;
	
	DOCINFO di;                                 // Initialise print doc details
	memset(&di, 0, sizeof (DOCINFO));
	di.cbSize = sizeof (DOCINFO);
	di.lpszDocName = m_csHeaderStr;
	
	BOOL bPrintingOK = dc.StartDoc(&di);        // Begin a new print job
	
	CPrintInfo Info;
	Info.m_rectDraw.SetRect(0,0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));
	Info.SetMaxPage(0);	
	
	dc.StartPage();                         // begin new page
	Info.m_nCurPage = 1;

	CRect rect;
	int  nPageWidth,  nPageHeight;
	int  nChartWidth, nChartHeight;
	
	m_Chart.GetClientRect(rect);	
	dc.SetMapMode(MM_ANISOTROPIC);
	
	nPageWidth   = dc.GetDeviceCaps(HORZRES);
	nPageHeight  = dc.GetDeviceCaps(VERTRES);
	nChartWidth  = rect.right  - rect.left;
	nChartHeight = rect.bottom - rect.top;
	
	dc.SetWindowExt(nChartWidth, nChartHeight);
	dc.SetViewportExt(nPageWidth, nPageHeight);
	::LPtoDP(dc.m_hDC, (POINT*)(&rect), 2);
	m_Chart.DrawToDC(dc.m_hDC, XRT_DRAW_ENHMETAFILE, XRT_DRAWSCALE_TOMAX, 
		rect.left, rect.top, (rect.right-rect.left), (rect.bottom-rect.top));
	bPrintingOK = (dc.EndPage() > 0);       // end page
	
	if (bPrintingOK)
		dc.EndDoc();                            // end a print job
	else
		dc.AbortDoc();                          // abort job.
	
	dc.Detach();                                // detach the printer DC
}

void CEdChartCtrl::doPrintPreview() 
{
	CFrameWnd * pFrameWnd = m_sdTemplate.CreateNewFrame( NULL, NULL );
	m_sdTemplate.InitialUpdateFrame( pFrameWnd, NULL, FALSE );
	CChartPreview* pView= (CChartPreview*) pFrameWnd->GetActiveView();
	pView->ShowWindow(SW_HIDE);
	pView->m_pChart = &m_Chart;
	AfxGetApp()->m_pMainWnd = pFrameWnd;
	pFrameWnd->SetWindowText(m_csHeaderStr);
	pFrameWnd->ShowWindow(SW_SHOWMAXIMIZED);
	pView->OnFilePrintPreview();
}

/**
 *  $(Desp).
 *  $(Detail).
 *
 *  @param  -[in,out]  LPCTSTR  lpszFileName: [comment]
 *  @return 1 - Chart2dData 'new' error.
 *	@return 2 - 无法打开文件或文件无效
 *
 *  @version  07/12/2004  cuiyan  Initial Version.
 */
long CEdChartCtrl::ReadFile(LPCTSTR lpszFileName) 
{
	delete m_pData;
	CString csFileName(lpszFileName);
	m_pData = new CChart2DData(csFileName.GetBuffer(0));
	if (m_pData == NULL)
		return 1;

	if (m_pData->GetNPoints(0) < 1 || m_pData->GetNSets() < 1)
		return 2;

	m_Chart.SetRepaint(FALSE);
	m_Chart.SetGraphBorder(XRT_BORDER_SHADOW);
	m_Chart.SetGraphBorderWidth(5);
	
	// set Header
	m_csHeaderFont = GetConfigStr(lpszFileName, _T("FONT"), 0, _T("Arial, 18, Bold"));
	m_Chart.SetPropString(XRT_HEADER_FONT, m_csHeaderFont.GetBuffer(0));
	m_csHeaderStr = GetConfigStr(lpszFileName, _T("HEADER"), -1, _T("EdChart Header"));
	m_Chart.SetHeaderStrings(GetConfigStrs(m_csHeaderStr));
		
	// set Footer
	m_csFooterFont = GetConfigStr(lpszFileName, _T("FONT"), 1, _T("Arial, 10, Bold"));
	m_Chart.SetPropString(XRT_FOOTER_FONT, m_csFooterFont.GetBuffer(0));
	m_csFooterStr = GetConfigStr(lpszFileName, _T("FOOTER"), -1, _T("EdChart Footer"));
	m_Chart.SetFooterStrings(GetConfigStrs(m_csFooterStr));
	
	m_csXTitle = GetConfigStr(lpszFileName, _T("TITLE"), 0, _T("X Axis"));
	m_Chart.SetXTitle(m_csXTitle.GetBuffer(0));
	m_csYTitle = GetConfigStr(lpszFileName, _T("TITLE"), 1, _T("Y Axis"));
	m_Chart.SetYTitle(m_csYTitle.GetBuffer(0));
	m_csLengendTitle = GetConfigStr(lpszFileName, _T("TITLE"), 2, _T("Legend"));
	m_Chart.SetLegendTitle(m_csLengendTitle.GetBuffer(0));
	
	m_clrBack = GetConfigColor(lpszFileName, 0, _T("FFFFFF"));
	m_Chart.SetBackgroundColor(m_clrBack);
	m_clrGraphBack = GetConfigColor(lpszFileName, 1, _T("FFFFFF"));
	m_Chart.SetGraphBackgroundColor(m_clrGraphBack);
	m_clrArea = GetConfigColor(lpszFileName, 2, _T("FFFFFF"));
	m_Chart.SetDataAreaBackgroundColor(m_clrArea);
	m_Chart.SetFooterX(m_Chart.GetGraphX());
	
	m_Chart.SetData(*m_pData);
	
	m_csXPointNames = GetConfigStr(lpszFileName, _T("POINT"), -1, _T(""));
	m_csYSetNames = GetConfigStr(lpszFileName, _T("SET"), -1, _T(""));
	
	CString csTmp;
	for (int i=0; i < m_pData->GetNPoints(0); i++) 
	{
		if (!GetSubString(csTmp, m_csXPointNames, i, _T('~')) || csTmp.IsEmpty())
			csTmp.Format( _T("Point %d"), i + 1);
		m_Chart.SetNthPointLabel(i, csTmp.GetBuffer(0));
	}
	
	for (i=0; i<m_pData->GetNSets(); i++) 
	{
		if (!GetSubString(csTmp, m_csYSetNames, i, _T('$')) || csTmp.IsEmpty())
			csTmp.Format( _T("Set %d"), i + 1);
		m_Chart.SetNthSetLabel(i, csTmp.GetBuffer(0));
	}
	
	m_Chart.SetRepaint(TRUE);
	
	return 0;
}

void CEdChartCtrl::OnPropertyChanged()
{
	if (::IsWindow(m_Chart.m_hWnd))
		m_Chart.InvalidateRect(NULL, FALSE);
}

void CEdChartCtrl::OnHeaderFontChanged()
{
	m_Chart.SetPropString(XRT_HEADER_FONT, m_csHeaderFont.GetBuffer(0));
	OnPropertyChanged();	
} 

void CEdChartCtrl::OnHeaderStrChanged()
{
	m_Chart.SetHeaderStrings(GetConfigStrs(m_csHeaderStr));
	OnPropertyChanged();
}

void CEdChartCtrl::OnFooterFontChanged()
{
	m_Chart.SetPropString(XRT_FOOTER_FONT, m_csFooterFont.GetBuffer(0));
	OnPropertyChanged();
} 

void CEdChartCtrl::OnFooterStrChanged()
{
	m_Chart.SetFooterStrings(GetConfigStrs(m_csFooterStr));
	OnPropertyChanged();
} 

void CEdChartCtrl::OnXTitleChanged()
{
	m_Chart.SetXTitle(m_csXTitle.GetBuffer(0));
	OnPropertyChanged();
} 

void CEdChartCtrl::OnYTitleChanged()
{
	m_Chart.SetYTitle(m_csYTitle.GetBuffer(0));
	OnPropertyChanged();
} 

void CEdChartCtrl::OnLengendTitleChanged()
{
	m_Chart.SetLegendTitle(m_csLengendTitle.GetBuffer(0));
	OnPropertyChanged();
} 

void CEdChartCtrl::OnBackColorChanged()
{
	m_Chart.SetBackgroundColor(m_clrBack);
	OnPropertyChanged();
} 

void CEdChartCtrl::OnGraphBackColorChanged()
{
	m_Chart.SetGraphBackgroundColor(m_clrGraphBack);
	OnPropertyChanged();
} 

void CEdChartCtrl::OnAreaColorChanged()
{
	m_Chart.SetDataAreaBackgroundColor(m_clrArea);
	OnPropertyChanged();
} 

void CEdChartCtrl::OnXPointNamesChanged()
{
	CString csTmp;
	for (int i=0; i < m_pData->GetNPoints(0); i++) 
	{
		if (!GetSubString(csTmp, m_csXPointNames, i, _T('~')) || csTmp.IsEmpty())
			csTmp.Format( _T("Point %d"), i + 1);
		m_Chart.SetNthPointLabel(i, csTmp.GetBuffer(0));
	}
	
} 

void CEdChartCtrl::OnYSetNamesChanged() 
{
	CString csTmp;
	for (int i=0; i<m_pData->GetNSets(); i++) 
	{
		if (!GetSubString(csTmp, m_csYSetNames, i, _T('~')) || csTmp.IsEmpty())
			csTmp.Format( _T("Set %d"), i + 1);
		m_Chart.SetNthSetLabel(i, csTmp.GetBuffer(0));
	}
}

void CEdChartCtrl::OnInvertOrientationChanged()
{
	m_Chart.SetInvertOrientation(m_bInvertOrientation);
	OnPropertyChanged();
} 

void CEdChartCtrl::OnStyle3DChanged()
{
	int u3d = (m_bStyle3D) ? 15 : 0;
	m_Chart.SetGraphDepth(u3d);
	m_Chart.SetGraphInclination(u3d);
	m_Chart.SetGraphRotation(u3d);
	OnPropertyChanged();
} 

void CEdChartCtrl::OnChartTypeChanged()
{
	if (m_lChartType > XRT_TYPE_BUBBLE)
		m_lChartType = XRT_TYPE_BUBBLE;
	
	if (m_lChartType < XRT_TYPE_PLOT)
		m_lChartType = XRT_TYPE_PLOT;
	
	m_Chart.SetType(XrtType(m_lChartType));
	OnPropertyChanged();
} 


void CEdChartCtrl::OnAlarmZoneChanged() 
{
	m_Chart.SetRepaint(FALSE);
	if(m_Chart.GetAlarmZoneList() == 0)
	{
		const int nzones = 5;
		double lower = m_Chart.GetYAxisMin();
		double upper = m_Chart.GetYAxisMax();
		double inc = (upper - lower) / nzones;
		for(int i=0; i < nzones; i++)
		{
			COLORREF color = m_Chart.GetDataAreaBackgroundColor();
			color -= 0x101010 * i;
			
			CString name;
			name.Format(_T("%3d%%"), i);
			
			m_Chart.SetAlarmZone(name, TRUE, lower, lower+inc,
				XRT_DEFAULT_COLOR, color, XRT_FPAT_SOLID);
			lower += inc;
		}
	}
	else
	{
		m_Chart.RemoveAllAlarmZones();
	}
	m_Chart.SetRepaint(TRUE);
	
	OnPropertyChanged();
}

BOOL CEdChartCtrl::SaveAs(LPCTSTR lpszFileName) 
{
	return m_Chart.DrawToFile((LPTSTR)lpszFileName);
}
