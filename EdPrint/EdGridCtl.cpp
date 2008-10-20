// GridCtl.cpp : Implementation of the CEdGridCtrl ActiveX Control class.

#include "stdafx.h"
#include "EdPrint.h"
#include "EdGridCtl.h"
#include "EdGridPpg.h"

#include "GridPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define HEADER_HEIGHT       2
#define FOOTER_HEIGHT       2
#define LEFT_MARGIN         4
#define RIGHT_MARGIN        4
#define GAP                 1

IMPLEMENT_DYNCREATE(CEdGridCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CEdGridCtrl, COleControl)
	//{{AFX_MSG_MAP(CEdGridCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CEdGridCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CEdGridCtrl)
	DISP_PROPERTY(CEdGridCtrl, "VisualWidth", m_lVisualWidth, VT_I4)
	DISP_PROPERTY(CEdGridCtrl, "FontName", m_csFontName, VT_BSTR)
	DISP_PROPERTY(CEdGridCtrl, "Title", m_csTitle, VT_BSTR)
	DISP_PROPERTY(CEdGridCtrl, "HeadRight", m_csHeadRight, VT_BSTR)
	DISP_PROPERTY(CEdGridCtrl, "FootLeft", m_csFootLeft, VT_BSTR)
	DISP_PROPERTY(CEdGridCtrl, "FootRight", m_csFootRight, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CEdGridCtrl, "ColsWidthStr", m_csColsWidthStr, OnColsWidthStrChanged, VT_BSTR)
	DISP_PROPERTY_EX(CEdGridCtrl, "FixedCols", GetFixedCols, SetFixedCols, VT_I4)
	DISP_FUNCTION(CEdGridCtrl, "ReadFile", ReadFile, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CEdGridCtrl, "ReadDB", ReadDB, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CEdGridCtrl, "doPrint", doPrint, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CEdGridCtrl, "doPrintPreview", doPrintPreview, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CEdGridCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CEdGridCtrl, COleControl)
	//{{AFX_EVENT_MAP(CEdGridCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CEdGridCtrl, 1)
	PROPPAGEID(CEdGridPropPage::guid)
END_PROPPAGEIDS(CEdGridCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CEdGridCtrl, "EdPrint.EdGridCtrl.1",
	0xe9bfb9f4, 0xc756, 0x48aa, 0xbf, 0x27, 0x1c, 0x6e, 0xc9, 0xb3, 0xc7, 0x12)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CEdGridCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DGrid =
		{ 0xeb4553d3, 0x3dc5, 0x460a, { 0x9f, 0x11, 0xe2, 0x3e, 0x9f, 0x72, 0x85, 0x70 } };
const IID BASED_CODE IID_DGridEvents =
		{ 0xd0b0c48e, 0xf79f, 0x4e06, { 0xb4, 0xe3, 0xf4, 0x50, 0xeb, 0xb4, 0xe, 0x8f } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwGridOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CEdGridCtrl, IDS_EDGRID, _dwGridOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CEdGridCtrl::CEdGridCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CEdGridCtrl

BOOL CEdGridCtrl::CEdGridCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_EDGRID,
			IDB_EDGRID,
			afxRegApartmentThreading,
			_dwGridOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CEdGridCtrl::CEdGridCtrl - Constructor

CEdGridCtrl::CEdGridCtrl() : m_sdTemplate(IDR_MAINFRAME, NULL, RUNTIME_CLASS(CFrameWnd), RUNTIME_CLASS(CGridPreview))
{
	InitializeIIDs(&IID_DGrid, &IID_DGridEvents);
	m_lVisualWidth = 500;
	m_csFontName = _T("Times New Roman");
}

/////////////////////////////////////////////////////////////////////////////
// CEdGridCtrl::~CEdGridCtrl - Destructor
CEdGridCtrl::~CEdGridCtrl()
{
	CDocManager::pStaticList;
	CDocManager::pStaticDocManager;
}

/////////////////////////////////////////////////////////////////////////////
// CEdGridCtrl::DoPropExchange - Persistence support

void CEdGridCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
}


/////////////////////////////////////////////////////////////////////////////
// CEdGridCtrl::OnResetState - Reset control to default state

void CEdGridCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}


/////////////////////////////////////////////////////////////////////////////
// CEdGridCtrl::AboutBox - Display an "About" box to the user

void CEdGridCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_EDGRID);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CEdGridCtrl message handlers
BOOL CEdGridCtrl::readFileHead(CMarkup &xml, long &lFixedCols)
{
	BOOL bRet = FALSE;

	xml.ResetPos();
	if (!xml.FindElem(_T("HTML")))
		return bRet; // _T("the root tag of manifest file root tag is not edfc!");	
	
	if (xml.FindChildElem(_T("HEAD")))
	{
		xml.IntoElem();
		
		if (xml.FindChildElem(_T("TITLE")))
		{
			xml.IntoElem();
			CString csTitle = xml.GetData();
			if (!csTitle.IsEmpty())
				m_csTitle = csTitle;
			xml.OutOfElem();
		}
		
		while (xml.FindChildElem(_T("META")))
		{
			xml.IntoElem();
			
			CString csName, csContent;
			csName = xml.GetAttrib(_T("NAME"));
			csContent = xml.GetAttrib(_T("CONTENT"));
			
			TCHAR* pStop = NULL;
			if (!csContent.IsEmpty())
			{
				if (csName.Compare(_T("FontName")) == 0)
					m_csFontName = csContent;
				else if (csName.Compare(_T("HeadRight")) == 0)
					m_csHeadRight = csContent;			
				else if (csName.Compare(_T("FootLeft")) == 0)
					m_csFootLeft = csContent;
				else if (csName.Compare(_T("FootRight")) == 0)
					m_csFootRight = csContent;
				else if (csName.Compare(_T("VisualWidth")) == 0)
					m_lVisualWidth = _tcstol(csContent, &pStop, 10);
				else if (csName.Compare(_T("FixedCols")) == 0)
					lFixedCols = _tcstol(csContent, &pStop, 10);
				else;
			}
			
			xml.OutOfElem();
		}
		
		xml.OutOfElem();	// out HEAD
		bRet = TRUE;
	}
	
	return bRet;	
}

BOOL CEdGridCtrl::readFileFindTable(CMarkup& xml, CString& csTableName)
{
	while (xml.FindChildElem())
	{
		if (xml.GetChildTagName().Compare(_T("TABLE")) == 0
			&& xml.GetChildAttrib(_T("NAME")).Compare(csTableName) == 0)
			return TRUE;

		xml.IntoElem();
		if (readFileFindTable(xml, csTableName))	return TRUE;		
		xml.OutOfElem();
	}

	return FALSE;
}

/**
 *  Read Data From File.
 *
 *  @param  -[in]  LPCTSTR  lpszFileName: [FileName]
 *  @param  -[in]  LPCTSTR  lpszTableName: [TableName]
 *  @return 0 - success.
 *  @return 1 - File is not exist.
 *  @return 2 - xml parse error.
 *  @return 3 - html flag is not exist and config infomation can not be received.
 *  @return 4 - can not fine the table.
 *  @return 5 - col or row is zero.
 *
 *  @version  07/10/2004  cuiyan  Initial Version.
 */
long CEdGridCtrl::ReadFile(LPCTSTR lpszFileName, LPCTSTR lpszTableName) 
{
	CMarkup xml;
	CString csDoc;
	try
	{
		CFile file( lpszFileName, CFile::modeRead ); 
		size_t nSize = (size_t)file.GetLength();
		BYTE* pBuffer = new BYTE [nSize + 1];
		nSize = file.Read( pBuffer, (UINT)nSize );
		file.Close();
		pBuffer[nSize] = '\0';
		csDoc  = (LPCSTR) pBuffer;
		delete [] pBuffer;
	}
	catch (...) 
	{
		return 1;
	}
	
	if (!xml.SetDoc( csDoc ))
		return 2; // _T("Parse manifest file Error!");

	long lFixedCols = 0;	
	if (!readFileHead(xml, lFixedCols))
		return 3;
	
	xml.ResetPos();
	CString csTableName(lpszTableName);

	if (!readFileFindTable(xml, csTableName))
		return 4;

	long lCols = 0, lRows = 0;
	xml.IntoElem(); // into First TABLE
	if (xml.FindChildElem(_T("TR")))
	{
		xml.IntoElem();
		lRows++;
		while (xml.FindChildElem(_T("TH")))
			lCols++;
		xml.OutOfElem();
	}
	
	while (xml.FindChildElem(_T("TR")))		lRows++;
	xml.OutOfElem();	// out First TABLE

	if (lCols == 0 || lRows == 0)
		return 5;
	
	m_Grid.Clear();
	m_Grid.SetCols(lCols);
	m_Grid.SetRows(lRows);
	m_Grid.SetFixedRows(1);
	SetFixedCols(lFixedCols);
	
	//////////////////////////////////////////////////////////////////////////
	xml.ResetPos();
	if (!readFileFindTable(xml, csTableName))
		return 4;
	
	lRows = 0;
	xml.IntoElem(); // into First TABLE
	xml.FindChildElem(_T("TR"));
	xml.IntoElem();
	for (lCols = 0; xml.FindChildElem(_T("TH")); lCols++)
	{
		TCHAR* pStop = NULL;
		m_Grid.SetTextMatrix(lRows, lCols, xml.GetChildData());
		long lWidth = _tcstol(xml.GetChildAttrib(_T("WIDTH")), &pStop, 10);
		
		if (lWidth < 0)		lWidth = 100;
		if (lWidth < 100)	lWidth *= 100;
		m_Grid.SetColWidth(lCols, lWidth);
	}
	xml.OutOfElem();
	lRows++;
			
	for (;xml.FindChildElem(_T("TR")); lRows++)
	{
		xml.IntoElem();
		for (lCols = 0; xml.FindChildElem(_T("TD")); lCols++)
			m_Grid.SetTextMatrix(lRows, lCols, xml.GetChildData());
		xml.OutOfElem();
	}

	xml.OutOfElem();	// out First TABLE

	SetStyle();
	
	return 0;
}

static inline void TESTHR(HRESULT x) {if FAILED(x) {_com_issue_error(x); throw(x); } };

/**
 *  Read data from database.
 *
 *  @param  -[in]  LPCTSTR  lpszConnectString: [ConnectString]
 *  @param  -[in]  LPCTSTR  lpszUserName: [UserName]
 *  @param  -[in]  LPCTSTR  lpszPassword: [Password]
 *  @param  -[in]  LPCTSTR  lpszRecordSource: [RecordSource]
 *
 *  @return 0 - success.
 *  @return 1 - Connection can not be created.
 *  @return 2 - Recordset can not be created.
 *  @return 3 - Connection can not be opened.
 *  @return 4 - Recordset can not be opened.
 *  @return 5 - Recordset can not be opened again.
 *
 *  @version  07/10/2004  cuiyan  Initial Version.
*/
long CEdGridCtrl::ReadDB(LPCTSTR lpszConnectString, LPCTSTR lpszUserName, 
						 LPCTSTR lpszPassword, LPCTSTR lpszRecordSource) 
{
	HRESULT hr = S_FALSE;
	long bRet = 0;
	
	_ConnectionPtr pConnection = NULL;
	_RecordsetPtr pRecordset = NULL;
	try
	{
		bRet = 1;	TESTHR(hr = pConnection.CreateInstance(__uuidof(Connection)));
		bRet = 2;	TESTHR(hr = pRecordset.CreateInstance(__uuidof(Recordset)));
		bRet = 3;	TESTHR(hr = pConnection->Open(lpszConnectString, lpszUserName, lpszPassword, 
			adModeUnknown));

		bRet = 4;	TESTHR(hr = pRecordset->Open(lpszRecordSource, pConnection.GetInterfacePtr(), 
			adOpenForwardOnly, adLockReadOnly, adCmdText));

		long lCols = pRecordset->Fields->Count;
		for (long lRows = 1; !pRecordset->adoEOF; lRows++)
			pRecordset->MoveNext();

		m_Grid.Clear();
		m_Grid.SetCols(lCols);
		m_Grid.SetRows(lRows);
		m_Grid.SetFixedRows(1);
		
		for (long l = 0; l < lCols; l++)
			m_Grid.SetTextMatrix(0, l, (LPCTSTR)pRecordset->Fields->Item[l]->Name);
		pRecordset->Close();

		bRet = 5;	TESTHR(hr = pRecordset->Open(lpszRecordSource, pConnection.GetInterfacePtr(), 
			adOpenForwardOnly, adLockReadOnly, adCmdText));
		
		_variant_t v;
		for (long lCurRow = 1; lCurRow < lRows; lCurRow++, pRecordset->MoveNext())
		{
			for (long l = 0; l < lCols; l++)
			{
				v = pRecordset->Collect[l];
				if (v.vt == VT_EMPTY || v.vt == VT_NULL)
					m_Grid.SetTextMatrix(lCurRow, l, _T(""));
				else
					m_Grid.SetTextMatrix(lCurRow, l,  (LPCTSTR)(_bstr_t)v);
			}
		}

		bRet = 0;
	}
	catch(...)
	{
		_com_error err(hr);
		AfxMessageBox(err.ErrorMessage());		
	}
	
	if (pRecordset->State)
		pRecordset->Close();
	
	if(pConnection->State)
		pConnection->Close();
	
	SetStyle();

	return bRet;
}

void CEdGridCtrl::doPrint(LPCTSTR lpszPrinterName) 
{
	HDC hDC = GetPrintHDC(this, lpszPrinterName);

	if (NULL == hDC)
		return;

    CDC dc;
    dc.Attach(hDC);         // attach a printer DC
    dc.m_bPrinting = TRUE;
	
    CString strTitle(m_csTitle);
	if (strTitle.IsEmpty())
		strTitle.LoadString(AFX_IDS_APP_TITLE);
	
    DOCINFO di;                                 // Initialise print doc details
    memset(&di, 0, sizeof (DOCINFO));
    di.cbSize = sizeof (DOCINFO);
    di.lpszDocName = strTitle;
	
    BOOL bPrintingOK = dc.StartDoc(&di);        // Begin a new print job
	
	CPrintInfo Info;
    Info.m_rectDraw.SetRect(0,0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));
	
    OnMyBeginPrinting(&dc, &Info);                // Initialise printing
    for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++)
    {
        dc.StartPage();                         // begin new page
        Info.m_nCurPage = page;
        OnMyPrint(&dc, &Info);                    // Print page
        bPrintingOK = (dc.EndPage() > 0);       // end page
    }
    OnMyEndPrinting(&dc, &Info);                  // Clean up after printing
	
    if (bPrintingOK)
        dc.EndDoc();                            // end a print job
    else
        dc.AbortDoc();                          // abort job.
	
    dc.Detach();                                // detach the printer DC
}

long CEdGridCtrl::GetFixedCols() 
{
	return m_Grid.GetFixedCols();
}

void CEdGridCtrl::SetFixedCols(long nNewValue) 
{
	if (nNewValue < 0)
		nNewValue = 0;
	else if (nNewValue >= m_Grid.GetCols())
		nNewValue = m_Grid.GetCols() - 1;
	else;
	
	m_Grid.SetFixedCols(nNewValue);
}

int CEdGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	RECT rectClient;
	GetClientRect(&rectClient);
	
	AfxEnableControlContainer();
	
	if (!m_Grid.Create(NULL, NULL, WS_VISIBLE | WS_CHILD, 
		rectClient, this, AFX_IDW_PANE_FIRST))
	{
		DestroyWindow();
		return -1;
	}
	
	m_Grid.SetScrollBars(2);
	m_Grid.SetCols(2);
	m_Grid.SetRows(10);	
	m_Grid.SetFixedRows(1);
	SetFixedCols(1);
	
	m_Grid.SetFixedRows(1);
	return 0;
}


BOOL CEdGridCtrl::IsVScrollBar(int yLogical, int cy)
{
	long lClientHeigth = cy * 1440 / yLogical;

	long lGridHeigth = 0;
	for (int i = 0; i < m_Grid.GetRows(); i++)
		lGridHeigth += m_Grid.GetRowHeight(i);

	return lClientHeigth < lGridHeigth;	
}

void CEdGridCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);

	if (::IsWindow(m_Grid.m_hWnd))
	{
		m_Grid.MoveWindow(0, 0, cx, cy);
	
		long lClientWidth = cx - m_Grid.GetCols() - 1;

		HDC screenDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
		int xLogical = GetDeviceCaps(screenDC, LOGPIXELSX);
		int yLogical = GetDeviceCaps(screenDC, LOGPIXELSY);
		DeleteDC(screenDC);

		if ( IsVScrollBar(yLogical, cy))
			lClientWidth -= GetSystemMetrics(SM_CXVSCROLL);
		
		lClientWidth *= (1440 / xLogical); //convert from pixel to twip

		long lWidth = GetColsWidth();
		for (int i = 0; i < m_Grid.GetCols(); i++)
			m_Grid.SetColWidth(i,  m_Grid.GetColWidth(i) * lClientWidth / lWidth);
	}
}

//////////////////////////////////////////////////////////////////////////
long CEdGridCtrl::GetRowHeight(long i)
{
	return m_CharSize.cy + 2;
}

long CEdGridCtrl::GetFixedRowHeight()
{
    return m_Grid.GetFixedRows() * GetRowHeight(0);
}

long CEdGridCtrl::GetColsWidth()
{
	long nWidth = 0;
	for (long i = 0; i < m_Grid.GetCols(); i++)
		nWidth += m_Grid.GetColWidth(i);

	return nWidth;
}

/////////////////////////////////////////////////////////////////////////////
// CEdGridCtrl printing overridables - for Doc/View print/print preview framework

void CEdGridCtrl::OnMyBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
    if (!pDC || !pInfo) return;

    int nMaxRowCount = m_Grid.GetRows() - m_Grid.GetFixedRows();
    if (nMaxRowCount < 1) return;

    // Get a DC for the current window (will be a screen DC for print previewing)
    CDC *pCurrentDC = GetDC();        // will have dimensions of the client area
    if (NULL == pCurrentDC) return;

    CSize PaperPixelsPerInch(pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY));
    CSize ScreenPixelsPerInch(pCurrentDC->GetDeviceCaps(LOGPIXELSX), pCurrentDC->GetDeviceCaps(LOGPIXELSY));

    // Create the printer font
    m_PrinterFont.CreateFont(-9, 0,0,0, FW_NORMAL, 0,0,0, DEFAULT_CHARSET,
                             OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
                             DEFAULT_PITCH | FF_DONTCARE, m_csFontName);
            
    CFont *pOldFont = pDC->SelectObject(&m_PrinterFont);

    // Get the average character width (in GridCtrl units) and hence the margins
	m_CharSize = pDC->GetTextExtent(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSATUVWXYZ"),52);
    m_CharSize.cx /= 52;
    
	int nMargins = (LEFT_MARGIN+RIGHT_MARGIN)*m_CharSize.cx;

    // Get the page sizes (physical and logical)
    m_PaperSize = CSize(pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
    m_LogicalPageSize.cx = m_lVisualWidth + nMargins;

    m_LogicalPageSize.cy = MulDiv(m_LogicalPageSize.cx, m_PaperSize.cy, m_PaperSize.cx);
	
    m_nPageHeight = m_LogicalPageSize.cy - GetFixedRowHeight()
                       - (HEADER_HEIGHT+FOOTER_HEIGHT + 2*GAP)*m_CharSize.cy;

    // Get the number of pages. Assumes no row is bigger than the page size.
    int nTotalRowHeight = 0;
    int nNumPages = 1;
    for (int row = m_Grid.GetFixedRows(); row < m_Grid.GetRows(); row++)
    {
        nTotalRowHeight += GetRowHeight(row);
        if (nTotalRowHeight > m_nPageHeight) {
            nNumPages++;
            nTotalRowHeight = GetRowHeight(row);
        }
    }

    // Set up the print info
    pInfo->SetMaxPage(nNumPages);
    pInfo->m_nCurPage = 1;                        // start printing at page# 1

    ReleaseDC(pCurrentDC);
    pDC->SelectObject(pOldFont);
}

void CEdGridCtrl::OnMyPrint(CDC *pDC, CPrintInfo *pInfo)
{
    if (!pDC || !pInfo) return;

    CFont *pOldFont = pDC->SelectObject(&m_PrinterFont);

    // Set the page map mode to use GridCtrl units, and setup margin
    pDC->SetMapMode(MM_ANISOTROPIC);
    pDC->SetWindowExt(m_LogicalPageSize);
    pDC->SetViewportExt(m_PaperSize);
    pDC->SetWindowOrg(-LEFT_MARGIN*m_CharSize.cx, 0);

    // Header
    pInfo->m_rectDraw.top    = 0;
    pInfo->m_rectDraw.left   = 0;
    pInfo->m_rectDraw.right  = m_LogicalPageSize.cx - (LEFT_MARGIN+RIGHT_MARGIN)*m_CharSize.cx;
    pInfo->m_rectDraw.bottom = HEADER_HEIGHT*m_CharSize.cy;
    PrintHeader(pDC, pInfo);
    pDC->OffsetWindowOrg(0, -HEADER_HEIGHT*m_CharSize.cy);

    // Gap between header and column headings
    pDC->OffsetWindowOrg(0, -GAP*m_CharSize.cy);

    // Print the column headings
    pInfo->m_rectDraw.bottom = GetFixedRowHeight();
    PrintColumnHeadings(pDC, pInfo);
    pDC->OffsetWindowOrg(0, -GetFixedRowHeight()); 

    // We need to find out which row to start printing for this page.
    int nTotalRowHeight = 0;
    UINT nNumPages = 1;
    int nCurrPrintRow = m_Grid.GetFixedRows();

    while (nCurrPrintRow < m_Grid.GetRows() && nNumPages < pInfo->m_nCurPage)
    {
        nTotalRowHeight += GetRowHeight(nCurrPrintRow);
        if (nTotalRowHeight > m_nPageHeight) {
            nNumPages++;
            if (nNumPages == pInfo->m_nCurPage) break;
            nTotalRowHeight = GetRowHeight(nCurrPrintRow);
        }
        nCurrPrintRow++;
    }
    if (nCurrPrintRow >= m_Grid.GetRows()) return;

    // Draw as many rows as will fit on the printed page.
    // Clip the printed page so that there is no partially shown
    // row at the bottom of the page (the same row which will be fully
    // shown at the top of the next page).

    BOOL bFirstPrintedRow = TRUE;
	long lWidth = GetColsWidth();
    CRect rect;
    rect.bottom = -1;
    while (nCurrPrintRow < m_Grid.GetRows())
    {
        rect.top = rect.bottom+1;
        rect.bottom = rect.top + GetRowHeight(nCurrPrintRow) - 1;

        if (rect.bottom > m_nPageHeight) break;            // Gone past end of page

        rect.right = -1;
        for (int col = 0; col < m_Grid.GetCols(); col++)
        {
            rect.left = rect.right+1;
            rect.right = rect.left + m_Grid.GetColWidth(col) * m_lVisualWidth / lWidth - 1;

            DrawCell(pDC, nCurrPrintRow, col, rect);

			int Overlap = (col == 0)? 0:1;
			pDC->MoveTo(rect.left-Overlap, rect.bottom);
			pDC->LineTo(rect.right, rect.bottom);
			if (nCurrPrintRow == 0) {
				pDC->MoveTo(rect.left-Overlap, rect.top);
				pDC->LineTo(rect.right, rect.top);
			}
			
			Overlap = (bFirstPrintedRow)? 0:1;
			pDC->MoveTo(rect.right, rect.top-Overlap);
			pDC->LineTo(rect.right, rect.bottom);    
			if (col == 0) {
				pDC->MoveTo(rect.left, rect.top-Overlap);
				pDC->LineTo(rect.left, rect.bottom);    
			}
        }

        nCurrPrintRow++;
        bFirstPrintedRow = FALSE;
    }

    // Footer
    pInfo->m_rectDraw.bottom = FOOTER_HEIGHT*m_CharSize.cy;
    pDC->SetWindowOrg(-LEFT_MARGIN*m_CharSize.cx, -m_LogicalPageSize.cy + FOOTER_HEIGHT*m_CharSize.cy);
    PrintFooter(pDC, pInfo);

    // SetWindowOrg back for next page
    pDC->SetWindowOrg(0,0);

    pDC->SelectObject(pOldFont);
}

void CEdGridCtrl::OnMyEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    m_PrinterFont.DeleteObject();
}

void CEdGridCtrl::PrintColumnHeadings(CDC *pDC, CPrintInfo* /*pInfo*/)
{
    CFont *pOldFont = pDC->SelectObject(&m_PrinterFont);

    CRect rect;
	long  lWidth = GetColsWidth();
    rect.bottom = -1;
    for (int row = 0; row < m_Grid.GetFixedRows(); row++)
    {
        rect.top = rect.bottom+1;
        rect.bottom = rect.top + GetRowHeight(row) - 1;

        rect.right = -1;
        for (int col = 0; col < m_Grid.GetCols(); col++)
        {
            rect.left = rect.right+1;
            rect.right = rect.left + m_Grid.GetColWidth(col) * m_lVisualWidth / lWidth - 1;

            DrawFixedCell(pDC, row, col, rect);

			int Overlap = (col == 0)? 0:1;
			pDC->MoveTo(rect.left-Overlap, rect.bottom);
			pDC->LineTo(rect.right, rect.bottom);
			if (row == 0) {
				pDC->MoveTo(rect.left-Overlap, rect.top);
				pDC->LineTo(rect.right, rect.top);
			}

			Overlap = (row == 0)? 0:1;
			pDC->MoveTo(rect.right, rect.top-Overlap);
			pDC->LineTo(rect.right, rect.bottom);    
			if (col == 0) {
				pDC->MoveTo(rect.left, rect.top-Overlap);
				pDC->LineTo(rect.left, rect.bottom);    
			}
        }
    }

    pDC->SelectObject(pOldFont);
}

void CEdGridCtrl::PrintHeader(CDC *pDC, CPrintInfo *pInfo)
{
    CRect   rc(pInfo->m_rectDraw);

    CString strCenter = m_csTitle;
	if (strCenter.IsEmpty())
	{
		CWnd *pParentWnd = GetParent();
		while (pParentWnd)
		{
			pParentWnd->GetWindowText(strCenter);
			if (strCenter.GetLength())  // can happen if it is a CView, CChildFrm has the title
				break;
			pParentWnd = pParentWnd->GetParent();
		}
	}

    //create bold font for header and footer
    CFont   BigFont, BoldFont;
    LOGFONT lf;
    VERIFY(m_PrinterFont.GetLogFont(&lf));

    lf.lfWeight = FW_BOLD;
	VERIFY(BoldFont.CreateFontIndirect(&lf));
	
	lf.lfHeight = LONG(lf.lfHeight * 1.5);
	lf.lfWeight = LONG(lf.lfWeight * 1.5);
    VERIFY(BigFont.CreateFontIndirect(&lf));
	
    CFont *pNormalFont = pDC->SelectObject(&BigFont);
    int nPrevBkMode = pDC->SetBkMode(TRANSPARENT);

    // print parent window title in the centre (Gert Rijs)

    if( !strCenter.IsEmpty() )
        pDC->DrawText( strCenter, &rc, DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);

    pDC->SelectObject(&BoldFont);
    if( !m_csHeadRight.IsEmpty() )
        pDC->DrawText( m_csHeadRight, &rc, DT_RIGHT | DT_SINGLELINE | DT_NOPREFIX | DT_BOTTOM);

    pDC->SetBkMode(nPrevBkMode);
    pDC->SelectObject(pNormalFont);
	BigFont.DeleteObject();
    BoldFont.DeleteObject();

    pDC->SelectStockObject(BLACK_PEN);
    pDC->MoveTo(rc.left, rc.bottom);
    pDC->LineTo(rc.right, rc.bottom);
}

//print footer with a line and date, and page number
void CEdGridCtrl::PrintFooter(CDC *pDC, CPrintInfo *pInfo)
{
    CRect rc(pInfo->m_rectDraw);

    //draw line
    pDC->MoveTo(rc.left, rc.top);
    pDC->LineTo(rc.right, rc.top);

	// draw page number
    CString strLeft = m_csFootLeft;
	if (strLeft.IsEmpty())
		strLeft.Format(_T("Page %d of %d"), pInfo->m_nCurPage, pInfo->GetMaxPage() );
	
    CString strRight = m_csFootRight;
	if (strRight.IsEmpty())
	{
		CTime t = CTime::GetCurrentTime();
		strRight = t.Format(_T("%c"));
	}
	
    //create bold font for header and footer
    CFont   BoldFont;
    LOGFONT lf;
    VERIFY(m_PrinterFont.GetLogFont(&lf));
    lf.lfWeight = FW_BOLD;
    VERIFY(BoldFont.CreateFontIndirect(&lf));
    CFont *pNormalFont = pDC->SelectObject(&BoldFont);
    int nPrevBkMode = pDC->SetBkMode(TRANSPARENT);
	
    if( !strLeft.IsEmpty() )
        pDC->DrawText( strLeft, &rc, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);
    if( !strRight.IsEmpty() )
        pDC->DrawText( strRight, &rc, DT_RIGHT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);

    pDC->SetBkMode(nPrevBkMode);
    pDC->SelectObject(pNormalFont);
	BoldFont.DeleteObject();
}

BOOL CEdGridCtrl::DrawCell(CDC* pDC, int nRow, int nCol, CRect rect)
{
    int nSavedDC = pDC->SaveDC();
    pDC->SetBkMode(TRANSPARENT);
	
	COLORREF clr = RGB(214, 235, 255);
	if (nRow % 2 != 0)
		clr = ::GetSysColor(COLOR_WINDOW);

	if (nCol < m_Grid.GetFixedCols())
		clr = ::GetSysColor(COLOR_3DFACE);

	CBrush brush(clr);
	rect.right++; rect.bottom++;    // FillRect doesn't draw RHS or bottom
	pDC->FillRect(rect, &brush);
	rect.right--; rect.bottom--;
	pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
    pDC->DrawText(m_Grid.GetTextMatrix(nRow, nCol), -1, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    pDC->RestoreDC(nSavedDC);
    return TRUE;
}

BOOL CEdGridCtrl::DrawFixedCell(CDC* pDC, int nRow, int nCol, CRect rect)
{
	CBrush brush(::GetSysColor(COLOR_3DFACE));
	pDC->FillRect(rect, &brush);
    pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
    
    int nSavedDC = pDC->SaveDC();
	CPen lightpen(PS_SOLID, 1,  ::GetSysColor(COLOR_3DHIGHLIGHT)),
		darkpen(PS_SOLID,  1, ::GetSysColor(COLOR_3DDKSHADOW)),
		*pOldPen = pDC->GetCurrentPen();
	
	pDC->SelectObject(&lightpen);
	pDC->MoveTo(rect.right, rect.top);
	pDC->LineTo(rect.left, rect.top);
	pDC->LineTo(rect.left, rect.bottom);
	
	pDC->SelectObject(&darkpen);
	pDC->MoveTo(rect.right, rect.top);
	pDC->LineTo(rect.right, rect.bottom);
	pDC->LineTo(rect.left, rect.bottom);
	
	pDC->SelectObject(pOldPen);
	rect.DeflateRect(1,1);
    pDC->SetBkMode(TRANSPARENT);
    pDC->DrawText(m_Grid.GetTextMatrix(nRow, nCol), -1, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	
    pDC->RestoreDC(nSavedDC);
	
    return TRUE;
}

void CEdGridCtrl::SetStyle()
{
	m_Grid.ShowWindow(SW_HIDE);
	for (long row = m_Grid.GetFixedRows() + 1; row < m_Grid.GetRows(); row += 2)
	{
		for (long col = m_Grid.GetFixedCols(); col < m_Grid.GetCols(); col++)
		{
			m_Grid.SetRow(row);
			m_Grid.SetCol(col);			
			m_Grid.SetCellBackColor(RGB(214, 235, 255));
		}
	}

	for (long col = 0; col < m_Grid.GetCols(); col++)
		m_Grid.SetColAlignment(col, 4);

	CRect rt;
	GetClientRect(rt);
	SendMessage(WM_SIZE, SIZE_RESTORED, MAKELONG(rt.Width(), rt.Height()));
	m_Grid.ShowWindow(SW_SHOW);
}

void CEdGridCtrl::doPrintPreview() 
{
 	CFrameWnd * pFrameWnd = m_sdTemplate.CreateNewFrame( NULL, NULL );
 	m_sdTemplate.InitialUpdateFrame( pFrameWnd, NULL, FALSE );
 	CGridPreview* pView= (CGridPreview*) pFrameWnd->GetActiveView();
 	pView->ShowWindow(SW_HIDE);
 	pView->m_pCtrl = this;
 	AfxGetApp()->m_pMainWnd = pFrameWnd;
 	pFrameWnd->SetWindowText(m_csTitle);
 	pFrameWnd->ShowWindow(SW_SHOWMAXIMIZED);
 	pView->OnFilePrintPreview();
 }
 
 void CEdGridCtrl::OnColsWidthStrChanged() 
 {
 	CUIntArray arWidth;
 	TCHAR* pStop = m_csColsWidthStr.GetBuffer(0);
 
 	while(1)
 	{
 		long l = _tcstol(pStop, &pStop, 10);
 		pStop++;
 		
 		if (l < 0)
 			l = -l;
 		else if (l == 0)
 			break;
 		else;
 
 		arWidth.Add(l);
 	}
 
 	long l = arWidth[0];
 	while(arWidth.GetSize() < m_Grid.GetCols())
 		arWidth.Add(l);
 
 	m_Grid.ShowWindow(SW_HIDE);
 	for (l = 0; l < m_Grid.GetCols(); l++)
 		m_Grid.SetColWidth(l, arWidth[l]);
 
 	CRect rt;
	GetClientRect(rt);
	SendMessage(WM_SIZE, SIZE_RESTORED, MAKELONG(rt.Width(), rt.Height()));
	m_Grid.ShowWindow(SW_SHOW);
}
