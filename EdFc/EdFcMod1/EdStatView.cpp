// EdStatView.cpp : implementation file
//

#include "stdafx.h"
#include "EdStatDoc.h"
#include "EdStatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int QueryDialog(HWND);
/////////////////////////////////////////////////////////////////////////////
// CEdStatView
IMPLEMENT_DYNCREATE(CEdStatView, CView)

CEdStatView::CEdStatView()
{
	//{{AFX_DATA_INIT(CEdStatView)
	//}}AFX_DATA_INIT
	m_GraphType = LINE;
}

CEdStatView::~CEdStatView()
{
}

BEGIN_MESSAGE_MAP(CEdStatView, CView)
	ON_COMMAND_RANGE(ID_LINE, ID_CUTPIE, OnTypeDraw)
	ON_UPDATE_COMMAND_UI_RANGE(ID_LINE, ID_CUTPIE, OnUpdateTypeDraw)
	//{{AFX_MSG_MAP(CEdStatView)
	ON_COMMAND(ID_QUERY, OnQuery)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdStatView diagnostics

#ifdef _DEBUG
void CEdStatView::AssertValid() const
{
	CView::AssertValid();
}

void CEdStatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////
void CEdStatView::OnDraw(CDC* pDC) 
{	
	if (m_bFirstDraw)
	{
		m_bFirstDraw = FALSE;
		OnQuery();
	}
	
	if(!m_Doc.IsLoaded())
		return;

	CRect rect;	
	
	if (pDC->IsPrinting())
	{
		rect.left = rect.top = 0;
		rect.right  = pDC->GetDeviceCaps(HORZRES);
		rect.bottom = pDC->GetDeviceCaps(VERTRES);
		m_Doc.m_Graph.SetPrintScale(pDC->m_hDC, rect);
	}
	else
	{
		GetClientRect(rect);
		m_Doc.m_Graph.RecalcRects(rect);
	}

	m_Doc.m_Graph.BeginDraw(pDC->m_hDC);
	m_Doc.m_Graph.SetBackColor(RGB(255,255,255));	
	m_Doc.m_Graph.SetTitleColor(RGB(0,0,0));
	m_Doc.m_Graph.Title(m_Doc.GetTitle());
	m_Doc.m_Graph.DrawBoundary(RGB(0,0,0), 2);
	m_Doc.m_Graph.EnableLegend();
	
	switch(m_GraphType)
	{
	case LINE:
		m_Doc.m_Graph.Line(true, PS_SOLID, 1);
		break;
	case BAR:
		m_Doc.m_Graph.Bar(TRUE,TRUE);
		break;
	case BAR3D:
		m_Doc.m_Graph.Bar3D(TRUE,TRUE);
		break;
	case PIE:
		m_Doc.SetCutPie(FALSE);
		break;
	case CUTPIE:
		m_Doc.SetCutPie(TRUE);
		break;
	default:
		return;
	}
 	
	if (m_GraphType == LINE || m_GraphType == BAR || m_GraphType == BAR3D)
	{
		for (int i = 0; i < m_Doc.GetCols(); i++)
		m_Doc.m_Graph.ShowValues(i);
	}

	m_Doc.m_Graph.EndDraw(pDC->m_hDC);
 	
	PrintQueryCondition(pDC, rect, m_Doc.GetFootLeft());
}

void CEdStatView::PrintQueryCondition(CDC *pDC, CRect rect, LPCSTR strDesc)
{
	// print query condition description text	
	int nLogPixelSy = pDC->GetDeviceCaps(LOGPIXELSY);
	int x = rect.left + nLogPixelSy / 2;
	int y = rect.bottom * 24 / 25;
	int nFontSize = rect.bottom / 48;
	
	TEXTMETRIC tm;
	ZeroMemory(&tm, sizeof(TEXTMETRIC));
	pDC->GetTextMetrics(&tm);
	
	nFontSize = nFontSize > 6 ? nFontSize - 4 : 3;

	if (pDC->IsPrinting())
	{
		y = rect.bottom - nLogPixelSy / 3;
		//nFontSize = nLogPixelSy / 5;
	}
	
	COLORREF PreColorRef = ::SetTextColor(pDC->m_hDC, RGB(0, 0, 0));
	CString szWhere = m_Doc.m_Templ.szTextWhere;
	if (!szWhere.IsEmpty())
	{
		HFONT  hFontText = ::CreateFont(-nFontSize, 0, 0, 0, 400, FALSE, FALSE, 0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS, "Times New Roman");
		HFONT hOldFontText = (HFONT)::SelectObject(pDC->m_hDC, hFontText);

		CRect rc (x, y, x + rect.Width() - 10 , y + int(tm.tmHeight * 1.5));
		int i = pDC->DrawText(szWhere, &rc, DT_TOP | DT_LEFT | DT_SINGLELINE );		
		::DeleteObject(hFontText);
		::SelectObject(pDC->m_hDC, hOldFontText);
	}

	if (strDesc != NULL)
	{
		y -= int(tm.tmHeight * 1.5);
		HFONT  hFontText = ::CreateFont(-nFontSize, 0, 0, 0, 400, FALSE, FALSE, 0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS, "Times New Roman");
		HFONT hOldFontText = (HFONT)::SelectObject(pDC->m_hDC, hFontText);
		
		CRect rc (x, y, x + rect.Width() - 10 , y + int(tm.tmHeight * 1.5));
		DrawText(pDC->m_hDC, strDesc, (int)_tcslen(strDesc), &rc, DT_TOP | DT_LEFT | DT_SINGLELINE);		
		::DeleteObject(hFontText);
		::SelectObject(pDC->m_hDC, hOldFontText);
	}	

	::SetTextColor(pDC->m_hDC, PreColorRef);
}


BOOL CEdStatView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

VOID CEdStatView::OnTypeDraw(UINT ID)
{
	m_GraphType = GRAPHTYPE(ID - ID_LINE);
	Invalidate();
}

VOID CEdStatView::OnUpdateTypeDraw(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck((m_GraphType + ID_LINE) == pCmdUI->m_nID);
	pCmdUI->Enable(m_Doc.IsLoaded());	
}

void CEdStatView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pDC->IsPrinting())
	{
		CWinApp* pApp = AfxGetApp();
		if(!pApp->GetPrinterDeviceDefaults(&pInfo->m_pPD->m_pd) || 
			pInfo->m_pPD->m_pd.hDevMode == NULL)
		{
			DoPreparePrinting(pInfo);
			return;
		}
		
		HGLOBAL hDevMode = pInfo->m_pPD->m_pd.hDevMode;
		DEVMODE* pDevMode = (DEVMODE*) ::GlobalLock(hDevMode);
		m_Doc.m_Graph.m_nPrinterDPI = pDevMode->dmPrintQuality;
		::GlobalUnlock(hDevMode);
	}
	
	CView::OnPrepareDC(pDC, pInfo);	
}

void CEdStatView::OnQuery() 
{
	if (QueryDialog(m_hWnd) == IDOK && m_Doc.GetData())
		Invalidate();
}

void CEdStatView::OnAppAbout() 
{
	CDialog dlg(IDD_ESSTATABOUTBOX);
	dlg.DoModal();
}


int CEdStatView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bFirstDraw = TRUE;	
	
	return 0;
}
