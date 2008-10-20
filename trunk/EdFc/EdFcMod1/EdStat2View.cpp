// EdStat2View.cpp : implementation file
//

#include "stdafx.h"
#include "EdStat2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int QueryDialog(HWND);
extern void ShowMessage(HWND, LPCTSTR, ...);
extern BOOL GetSubString(CString&, LPCTSTR, int, int, TCHAR, TCHAR);
/////////////////////////////////////////////////////////////////////////////
// CEdStat2View
IMPLEMENT_DYNCREATE(CEdStat2View, CView)

CEdStat2View::CEdStat2View()
{
	//{{AFX_DATA_INIT(CEdStat2View)
	//}}AFX_DATA_INIT
    m_pData = NULL;	
	m_uChartType = XRT_TYPE_BAR;
	m_bInvert = FALSE;
	m_pStrs = NULL;
	m_u3d = 0;
	GetTempPath(MAX_PATH, m_szFileName);
	strcat(m_szFileName, _T("GraphTm2.fmt"));
}

CEdStat2View::~CEdStat2View()
{
    delete m_pData;
	delete []m_pStrs;
	m_ar.RemoveAll();
}

void CEdStat2View::OnDraw(CDC* pDC) 
{
	if (m_bFirstDraw)
	{
		m_bFirstDraw = FALSE;
		OnQuery();
	}

	m_chart.InvalidateRect(NULL, FALSE);
}


BEGIN_MESSAGE_MAP(CEdStat2View, CView)
	//{{AFX_MSG_MAP(CEdStat2View)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_SIZE()
	ON_COMMAND(ID_APP_ABOUT, OnHelp)
	ON_COMMAND(ID_QUERY, OnQuery)
	ON_COMMAND(ID_3DSTYLE, On3dstyle)
	ON_UPDATE_COMMAND_UI(ID_3DSTYLE, OnUpdate3dstyle)
	ON_COMMAND(ID_ALARMZONE, OnAlarmzone)
	ON_UPDATE_COMMAND_UI(ID_ALARMZONE, OnUpdateAlarmzone)
	ON_COMMAND(ID_INVERT, OnInvert)
	ON_UPDATE_COMMAND_UI(ID_INVERT, OnUpdateInvert)
	ON_COMMAND(ID_EXCEL, OnExcel)
	ON_COMMAND(ID_SAVEAS, OnSaveas)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(XRTN_PALETTECHANGED, OnOC2PaletteChanged)
    ON_MESSAGE(XRTN_REPAINTED, OnOC2Repaint)
	ON_COMMAND_RANGE(ID_LINE, ID_PIE, OnChangeType)
	ON_UPDATE_COMMAND_UI_RANGE(ID_LINE, ID_PIE, OnUpdateChangeType)
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdStat2View diagnostics

#ifdef _DEBUG
void CEdStat2View::AssertValid() const
{
	CView::AssertValid();
}

void CEdStat2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEdStat2View message handlers

void CEdStat2View::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{	
    if(bActivate) {
        // Realize the palette and tell all the other window about it.
        m_chart.SendMessage(WM_QUERYNEWPALETTE, 0, 0);
        AfxGetApp()->GetMainWnd()->SendMessage(WM_PALETTECHANGED, (WPARAM)(GetSafeHwnd()), 0);
    }
	
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


BOOL CEdStat2View::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
    return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext)
		&& m_chart.Create(_T(""), WS_CHILD | WS_VISIBLE, rect, this, 0);
}

LRESULT CEdStat2View::OnOC2PaletteChanged(WPARAM, LPARAM)
{
    SendMessage(WM_QUERYNEWPALETTE, 0, 0);
    GetParentFrame()->SendMessage(WM_PALETTECHANGED, (WPARAM)(GetSafeHwnd()), 0);
	return 0;
}

LRESULT CEdStat2View::OnOC2Repaint(WPARAM wParam, LPARAM lParam)
{
    if (IsWindow(m_chart.m_hWnd)) {
		
        RECT rect, chartRect;
        int nWidth, nHeight;
		
        /* make the chart fill the windows client area */
        GetClientRect(&rect);
        ::GetClientRect(m_chart.m_hWnd, &chartRect);
        nWidth = chartRect.right;
        nHeight = chartRect.bottom;
		
        if (nWidth != rect.right || nHeight != rect.bottom) {
            /* adjust the window size to fit the chart */
            GetParent()->SetWindowPos(&wndTop, 0, 0, nWidth, nHeight, SWP_NOMOVE | SWP_NOZORDER);
        }
    }
	
    return TRUE;
}

void CEdStat2View::OnPaletteChanged(CWnd* pFocusWnd) 
{
    m_chart.SendMessage(WM_PALETTECHANGED, (WPARAM)pFocusWnd->GetSafeHwnd(), 0);
}

BOOL CEdStat2View::OnQueryNewPalette() 
{
    return (BOOL)(m_chart.SendMessage(WM_QUERYNEWPALETTE, 0, 0));
}

void CEdStat2View::OnSize(UINT nType, int cx, int cy) 
{
    CView::OnSize(nType, cx, cy);
	
    if (IsWindow(m_chart.m_hWnd)) {
        // If the view has resize then resize the chart if it has been created
        m_chart.SetWindowPos(&wndTop, 0, 0, cx, cy, SWP_NOZORDER);
    }
}

// The following code shows the technique of setting up a CDC to do
//  the appropriate scaling for printing and print preview.
// The actual output HDC is then used to draw the individual controls.
// This technique sends the WM_PAINT message to the control passing
//  the HDC as the 'wParam'.  This is an alternative painting technique
//  that most Windows controls and all VB controls support.
// This technique has many caveats that make it inappropriate for some
//  cases.  If you find the general technique inappropriate, you can
//  add special case code to handle the printing of the troublesome
//  controls.
//  * If you are using non-VBX custom controls, that do not support
//     the WM_PAINT technique, they will not be printed
//  * Some controls may not result in the desired output format
//     since the controls print in the same fashion as they
//     are displayed on the screen.
//  * Some controls assume they are always being displayed on the
//     screen.  This sometimes results in incorrect fonts being
//     used and bitmaps drawn incorrectly.
//  * The implementation of control printing does not support
//     WS_VSCROLL and WS_HSCROLL styles correctly.
//  * Some printer drivers may fault when painting certain controls.

void CEdStat2View::PaintChildWindows(HWND hWndParent, CDC* pDC, CPoint ptOffset)
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
			// set the viewport origin so that the window origin
			//  can be changed by the control
			
			// draw it using a non-virtual HDC
			::SendMessage(hWndChild, WM_PAINT, (WPARAM)hdcOut, 0L);
		}
		pDC->RestoreDC(-1);
		
		if (::GetTopWindow(hWndChild) != NULL)
			PaintChildWindows(hWndChild, pDC, ptOffset);
	}
}

void CEdStat2View::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	On3dstyle();
	m_chart.SetType(m_uChartType);	
	m_chart.SetAxisBoundingBox(TRUE);
	m_chart.SetXAnnotationMethod(XRT_ANNO_POINT_LABELS);
	m_chart.SetHeaderAdjust(XRT_ADJUST_CENTER);
	m_chart.SetFooterAdjust(XRT_ADJUST_LEFT);	
}

void CEdStat2View::OnHelp() 
{
	CDialog dlg(IDD_EDSTAT2ABOUTBOX);
	dlg.DoModal();
}

void CEdStat2View::OnQuery() 
{
	if (QueryDialog(m_hWnd) == IDOK && GetData())
		Invalidate();
}

void CEdStat2View::OnChangeType(UINT nID)
{
	switch (nID)
	{
	case ID_LINE:
		m_uChartType = XRT_TYPE_PLOT;
		break;
	case ID_PIE:
		m_uChartType = XRT_TYPE_PIE;
		break;
	case ID_BAR:
		m_uChartType = XRT_TYPE_BAR;
		break;
	default:
		break;
	}

	m_chart.SetType(m_uChartType);
	Invalidate();
}

void CEdStat2View::OnUpdateChangeType(CCmdUI *pCmdUI)
{
	XrtType xThis = XRT_TYPE_PLOT;
	switch(pCmdUI->m_nID) {
		xThis = XRT_TYPE_PLOT;
		break;
	case ID_PIE:
		xThis = XRT_TYPE_PIE;
		break;
	case ID_BAR:
		xThis = XRT_TYPE_BAR;
		break;
	default:
		break;
	}
	pCmdUI->SetRadio(m_uChartType == xThis);
}

void CEdStat2View::On3dstyle() 
{
	m_u3d = (m_u3d == 0) ? 15 :  0;
	m_chart.SetGraphDepth(m_u3d);
	m_chart.SetGraphInclination(m_u3d);
	m_chart.SetGraphRotation(m_u3d);
}

void CEdStat2View::OnUpdate3dstyle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_u3d);
}

BOOL CEdStat2View::GetData()
{
	// set data
	delete m_pData;
	m_pData = new CChart2DData(m_szFileName);
	if (m_pData == NULL)
	{
		ShowMessage(m_hWnd, "Chart2dData 'new' error!");
		return FALSE;
	} 
	else if (m_pData->GetNPoints(0) < 1 || m_pData->GetNSets() < 1)
	{
		ShowMessage(m_hWnd, "无法打开文件或文件无效：%s ", m_szFileName);
		return FALSE;
	}

	m_chart.SetRepaint(FALSE);
	m_chart.SetGraphBorder(XRT_BORDER_SHADOW);
	m_chart.SetGraphBorderWidth(5);

	// set Header
	m_chart.SetPropString(XRT_HEADER_FONT, GetConfigStr("FONT", 0, _T("Arial, 18, Bold")));
	m_chart.SetHeaderStrings(GetConfigStrs("HEADER"));

	// set Footer
	m_chart.SetPropString(XRT_FOOTER_FONT, GetConfigStr("FONT", 1, _T("Arial, 10, Bold")));
	m_chart.SetFooterStrings(GetConfigStrs("FOOTER"));
	
	m_chart.SetXTitle(GetConfigStr("TITLE", 0, _T("X Axis")));
	m_chart.SetYTitle(GetConfigStr("TITLE", 1, _T("Y Axis")));
	m_chart.SetLegendTitle(GetConfigStr("TITLE", 2, _T("Legend")));
	
	m_chart.SetBackgroundColor(GetConfigColor(0, _T("FFFFFF")));
	m_chart.SetGraphBackgroundColor(GetConfigColor(1, _T("FFFFFF")));
	m_chart.SetDataAreaBackgroundColor(GetConfigColor(2, _T("FFFFFF")));
	m_chart.SetFooterX(m_chart.GetGraphX());
	
	m_chart.SetData(*m_pData);
	

	TCHAR buffer[30];
	for (int i=0; i < m_pData->GetNPoints(0); i++) {
		_stprintf(buffer, _T("Point %d"), i+1);
		m_chart.SetNthPointLabel(i, GetConfigStr("POINT", i, buffer));
	}
	for (i=0; i<m_pData->GetNSets(); i++) {
		_stprintf(buffer, _T("Set %d"), i+1);
		m_chart.SetNthSetLabel(i, GetConfigStr("SET", i, buffer));
	}
	
	m_chart.SetRepaint(TRUE);
	return TRUE;
}


LPSTR CEdStat2View::GetConfigStr(LPCSTR str, UINT n, LPCSTR sdef)
{	
	static CString sc;
	CString s;
	BOOL bFind = FALSE;

	CStdioFile f(m_szFileName, CFile::modeRead);	
	sc.Format("#%s=", str);
	while (f.ReadString(s))
	{
		s.TrimLeft();
		if (s.Find(sc) == 0)
		{
			bFind = TRUE;
			break;
		}
	}	

	f.Close();

	if (bFind)
	{
		s.Delete(0, sc.GetLength());
		if (GetSubString(sc, s, s.GetLength(), n, '~', 0x00))
			return sc.GetBuffer(0);
	}

	return (LPSTR)sdef;
}

LPSTR* CEdStat2View::GetConfigStrs(LPCSTR str)
{
	CString s, sc;
	BOOL bFind = FALSE;
	
	CStdioFile f(m_szFileName, CFile::modeRead);	
	sc.Format("#%s=", str);
	while (f.ReadString(s))
	{
		s.TrimLeft();
		if (s.Find(sc) == 0)
		{
			bFind = TRUE;
			break;
		}
	}
	f.Close();
	
	m_ar.RemoveAll();
	
	if (bFind)
	{
		s.Delete(0, sc.GetLength());
		for (int i = 0; GetSubString(sc, s, s.GetLength(), i, '~', 0x00); i++)
			m_ar.Add(sc);
	}

	int nCount = (int)m_ar.GetSize();
	delete [] m_pStrs;
	m_pStrs = NULL;
	m_pStrs = new LPSTR [nCount + 1];
	for (int i = 0; i < nCount; i++)
		m_pStrs[i] = m_ar[i].GetBuffer(0);
	m_pStrs[nCount] = NULL;
	
	return m_pStrs;	
}

DWORD CEdStat2View::GetConfigColor(int n, LPCSTR sdef)
{
	DWORD dwColor;
	static TCHAR lpColor[7];
	strncpy(lpColor, GetConfigStr("COLOR", n, sdef), 6);
	lpColor[7] = NULL;
	
	TCHAR lpx = lpColor[0];
	lpColor[0] = lpColor[4];
	lpColor[4] = lpx;
	
	lpx = lpColor[1];
	lpColor[1] = lpColor[5];
	lpColor[5] = lpx;

	sscanf(lpColor, "%lx", &dwColor);

	return dwColor;
}

void CEdStat2View::OnAlarmzone() 
{
	m_chart.SetRepaint(FALSE);
	if(m_chart.GetAlarmZoneList() == 0)
	{
		const int nzones = 5;
		double lower = m_chart.GetYAxisMin();
		double upper = m_chart.GetYAxisMax();
		double inc = (upper - lower) / nzones;
		for(int i=0; i < nzones; i++)
		{
			COLORREF color = m_chart.GetDataAreaBackgroundColor();
			color -= 0x101010 * i;
			
			TCHAR name[8];
			sprintf(name, _T("%3d%%"), i);
			
			m_chart.SetAlarmZone(name, TRUE, lower, lower+inc,
				XRT_DEFAULT_COLOR, color, XRT_FPAT_SOLID);
			lower += inc;
		}
	}
	else
	{
		m_chart.RemoveAllAlarmZones();
	}
	m_chart.SetRepaint(TRUE);
}

void CEdStat2View::OnUpdateAlarmzone(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_chart.GetAlarmZoneList() != 0);
}


void CEdStat2View::OnInvert() 
{
	m_bInvert = !m_bInvert;
	m_chart.SetInvertOrientation(m_bInvert);
}

void CEdStat2View::OnUpdateInvert(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_bInvert);
}

BOOL CEdStat2View::OnPreparePrinting(CPrintInfo* pInfo) 
{
	pInfo->SetMaxPage(0);	//cycy
    return DoPreparePrinting(pInfo);
}

void CEdStat2View::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CRect rect;
	int  nPageWidth,  nPageHeight;
	int  nChartWidth, nChartHeight;
	
	m_chart.GetClientRect(rect);	
	pDC->SetMapMode(MM_ANISOTROPIC);
	
	nPageWidth   = pDC->GetDeviceCaps(HORZRES);
	nPageHeight  = pDC->GetDeviceCaps(VERTRES);
	nChartWidth  = rect.right  - rect.left;
	nChartHeight = rect.bottom - rect.top;
	
	pDC->SetWindowExt(nChartWidth, nChartHeight);
	pDC->SetViewportExt(nPageWidth, nPageHeight);
	//pDC->SetViewportOrg(0, 0);
	
	::LPtoDP(pDC->m_hDC, (POINT*)(&rect), 2);
	m_chart.DrawToDC(pDC->m_hDC, XRT_DRAW_ENHMETAFILE, XRT_DRAWSCALE_TOMAX, 
		rect.left, rect.top, (rect.right-rect.left), (rect.bottom-rect.top));
}


void CEdStat2View::OnExcel() 
{
	CString sTmp = GetConfigStr("HEADER", 0, _T("Chart"));
	sTmp += ".xls";
	CFileDialog dlg(FALSE, _T("xls"), sTmp, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Excel Files (*.xls)|*.xls|All Files (*.*)|*.*||"));
	
	if (dlg.DoModal() != IDOK)
		return;

	CDatabase database;
	LPCSTR sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)";
	CString sSql, sExcelFile = dlg.GetPathName();

	TRY
	{
		// 创建进行存取的字符串
		sSql.Format("DRIVER={%s};DSN='''';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",
			sDriver, sExcelFile, sExcelFile);
		
		// 创建数据库 (既Excel表格文件)
		if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
		{
			CTime tm = CTime::GetCurrentTime();
			CString sTable = tm.Format("%Y%m%d%H%M%S");
			
			sSql.Format("CREATE TABLE %s ([组] TEXT, ", sTable);
			sTmp.Format("INSERT INTO %s ([组], ", sTable);

			for (int i = 0; i < m_pData->GetNPoints(0); i++)
			{
				sSql += "[";
				sTmp += "[";
				sSql += m_chart.GetNthPointLabel(i);
				sTmp += m_chart.GetNthPointLabel(i);
				sSql += "]";
				sTmp += "], ";
				sSql += " FLOAT, ";
			}
			sSql.Delete(sSql.ReverseFind(','), 2);
			sTmp.Delete(sTmp.ReverseFind(','), 2);
			sSql += ")";
			sTmp += " ) VALUES (";
			database.ExecuteSQL(sSql);
		
			// 插入数值
			for (i = 0; i < m_pData->GetNSets(); i++)
			{
				sSql = sTmp;
				sSql += "'";
				sSql += m_chart.GetNthSetLabel(i);
				sSql += "'";
				CString sTemp;
				for (int j = 0; j < m_pData->GetNPoints(0); j++)
				{
					sTemp.Format(", %f", m_pData->GetYElement(i, j));
					sSql += sTemp;
				}
				sSql += ")";

				database.ExecuteSQL(sSql);
			}
		}      
		
		// 关闭数据库
		database.Close();
	}
	CATCH_ALL(e)
	{
		ShowMessage(m_hWnd, "Excel驱动没有安装: MICROSOFT EXCEL DRIVER (*.XLS)");
	}
	END_CATCH_ALL;	
}

void CEdStat2View::OnSaveas() 
{
	CFileDialog dlg(FALSE, _T("bmp"), _T(".bmp"), 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"));
	
	if (dlg.DoModal() == IDOK)
		m_chart.DrawToFile(dlg.GetPathName().GetBuffer(0));
}


#include "Chart7/och2dMFC.cpp"

int CEdStat2View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bFirstDraw = TRUE;
	
	return 0;
}
