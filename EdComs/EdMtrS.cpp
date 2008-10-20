// EdMtr.cpp: implementation of the CEdMtrS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdMtrS.h"
#include "EdFuncs.h"

extern void TESTHR(HRESULT hr);

#define HEADER_HEIGHT       2
#define FOOTER_HEIGHT       2
#define LEFT_MARGIN         4
#define RIGHT_MARGIN        4
#define GAP                 1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdMtrS::CEdMtrS()
{
	m_lCols = m_lRows = 0;
	m_lFixedCols = 1;
}

CEdMtrS::~CEdMtrS()
{
	m_arlWidth.clear();
	m_arstrMtrData.clear();
}

BOOL CEdMtrS::readFile_Header(IXMLDOMDocumentPtr& pXDoc, long &lFixedCols)
{		
	IXMLDOMNodePtr pNode = pXDoc->selectSingleNode(_T("//HTML/HEAD/TITLE"));
	if (pNode)
	{
		_variant_t v = pNode->firstChild->nodeValue;
		if (v.vt != VT_EMPTY && v.vt != VT_NULL)
			m_csTitle = (LPCTSTR)(_bstr_t)v;
	}

	IXMLDOMNodeListPtr pNodeList = pXDoc->selectNodes(_T("//HTML/HEAD/META"));
	if (pNodeList)
		return TRUE;

	_variant_t v;
	string csName, csContent;
	for( long i = 0; i < pNodeList->length; i++)
	{
		pNode = pNodeList->item[i]->attributes->getNamedItem(_T("CONTENT"));
		if (NULL == pNode)
			continue;

		v = pNode->nodeValue;
		if (v.vt == VT_EMPTY || v.vt == VT_NULL)
			continue;

		csContent = (LPCTSTR)(_bstr_t)v;
		
		pNode = pNodeList->item[i]->attributes->getNamedItem(_T("NAME"));
		if (NULL == pNode)
			continue;
		
		v = pNode->nodeValue;
		if (v.vt == VT_EMPTY || v.vt == VT_NULL)
			continue;

		csName = (LPCTSTR)(_bstr_t)v;
		
		TCHAR* pStop = NULL;
		if (csName.compare(_T("FontName")) == 0)
			m_csFontName = csContent;
		else if (csName.compare(_T("HeadRight")) == 0)
			m_csHeadRight = csContent;			
		else if (csName.compare(_T("FootLeft")) == 0)
			m_csFootLeft = csContent;
		else if (csName.compare(_T("FootRight")) == 0)
			m_csFootRight = csContent;
		else if (csName.compare(_T("FixedCols")) == 0)
			lFixedCols = _tcstol((LPTSTR)csContent.c_str(), &pStop, 10);
		else;
	}
	
	return TRUE;
}

IXMLDOMNodePtr CEdMtrS::readFile_FindTable(IXMLDOMNodeListPtr& pParent, BSTR bstrNodeName)
{
	IXMLDOMNodePtr pNode = NULL;

	for (long i = 0; i < pParent->length; i++)
	{
		pNode = pParent->item[i];
		if (pNode->nodeName == _bstr_t(_T("TABLE")))
		{
			_bstr_t s(_T(""));
			IXMLDOMNodePtr pNodeAttr = pNode->attributes->getNamedItem(_T("NAME"));
			if (NULL != pNodeAttr)		{
				_variant_t v = pNodeAttr->nodeValue;
				if (v.vt != VT_EMPTY && v.vt != VT_NULL)
					s = (LPTSTR)(_bstr_t)v;
			}

			if (s == _bstr_t(bstrNodeName))
				return pNode;
		}

		if (pNode->hasChildNodes())
		{
			pNode = readFile_FindTable(pNode->childNodes, bstrNodeName);
			if (pNode != NULL)
				return pNode;
		}
	}
		
	return NULL;
}

/**
 *  Read Data From File.
 *
 *  @param  -[in]  LPCTSTR  lpszFileName: [FileName]
 *  @param  -[in]  LPCTSTR  lpszTableName: [TableName]
 *  @return 0 - success.
 *  @return 1 - can not create MSXML.DOMDocument.
 *  @return 2 - xml parse error.
 *  @return 3 - html flag is not exist and config infomation can not be received.
 *  @return 4 - can not fine the table.
 *  @return 5 - col or row is zero.
 *  @return 6 - the File is not exist.
 *
 *  @version  07/10/2004  cuiyan  Initial Version.
 */
HRESULT CEdMtrS::readFile(BSTR bstrFileName, BSTR bstrTableName)
{
	HRESULT hr = S_OK;
	IXMLDOMDocumentPtr plDomDocument = NULL;

	try		{
		hr = 1;	TESTHR(plDomDocument.CreateInstance(CLSID_DOMDocument));

		CEdFuncs func;
		string str;
		BOOL bRead = func.GetFile((LPCTSTR)(_bstr_t)bstrFileName, str);
		if (!bRead)
			bRead = func.GetHttpPage((LPCTSTR)(_bstr_t)bstrFileName, str);
		if (!bRead)
			bRead = func.GetFtpFile((LPCTSTR)(_bstr_t)bstrFileName, str);
		if (!bRead)
			throw (hr = 6);

		int len = str.find(_T("</HTML>")) + _tcslen(_T("</HTML>"));
		str.erase(len, str.length() - len);
		
		_bstr_t bstr(str.c_str());
		if (!plDomDocument->loadXML(bstr))
			throw (hr = 2);
		if (plDomDocument->GetchildNodes()->Getlength() < 2)
			throw (hr = 2);
		
		if (!readFile_Header(plDomDocument, m_lFixedCols))
			throw (hr = 3);

		IXMLDOMNodePtr pTableNode = readFile_FindTable(plDomDocument->documentElement->childNodes, bstrTableName);
		if (pTableNode == NULL)
			throw (hr = 4);

		//////////////////////////////////////////////////////////////////////////
		IXMLDOMNodeListPtr pNodeList = pTableNode->selectNodes(_T("TR"));
		if (pNodeList != NULL)
			m_lRows = pNodeList->length;
		
		pNodeList = pTableNode->selectNodes(_T("TR/TH"));
		if (pNodeList != NULL)
			m_lCols = pNodeList->length;
		
		m_arstrMtrData.clear();
		m_arlWidth.clear();
		if (m_lCols == 0 || m_lRows == 0)
		{
			m_lRows = m_lCols = 0;
			throw (hr = 5);
		}
		
		long lWidth = 100;
		_variant_t v;
		IXMLDOMNodePtr pNode = NULL;
		for (long i = 0; i < m_lCols; i++)
		{
			pNode = pNodeList->item[i];
			v = pNode->firstChild->nodeValue;
			if (v.vt != VT_EMPTY && v.vt != VT_NULL)				
				m_arstrMtrData.push_back((LPCTSTR)(_bstr_t)v);
			else
				m_arstrMtrData.push_back(_T(""));

			string s;
			TCHAR*	pStop;
			pNode = pNode->attributes->getNamedItem(_T("WIDTH"));
			if (NULL != pNode)		{
				v = pNode->nodeValue;
				if (v.vt != VT_EMPTY && v.vt != VT_NULL)	{
					s = (LPTSTR)(_bstr_t)v;
					lWidth = _tcstol(s.c_str(), &pStop, 10);
				}	
			}
			
			m_arlWidth.push_back(lWidth);			
		}
		
		pNodeList = pTableNode->selectNodes(_T("TR/TD"));
		for (i = 0; i < pNodeList->length; i++)
		{
			v = pNodeList->item[i]->firstChild->nodeValue;
			if (v.vt != VT_EMPTY && v.vt != VT_NULL)				
				m_arstrMtrData.push_back((LPCTSTR)(_bstr_t)v);
			else
				m_arstrMtrData.push_back(_T(""));
		}
		
		hr = S_OK;
	} catch (...) {
		;
	}
	
	return hr;
}

/**
 *  Read data from database.
 *
 *  @param  -[in]  LPCTSTR  bstrConnect: [ConnectString]
 *  @param  -[in]  LPCTSTR  bstrSQL: [RecordSource]
 *
 *  @return 0 - success.
 *  @return 1 - Connection can not be created.
 *  @return 2 - Recordset can not be created.
 *  @return 3 - Connection can not be opened.
 *  @return 4 - Recordset can not be opened.
 *  @return 5 - Datasize is not devide by lCols.
 *
 *  @version  07/10/2004  cuiyan  Initial Version.
 */
HRESULT CEdMtrS::readDB(BSTR bstrConnect, BSTR bstrSQL)
{
	HRESULT bRet = 0;
	_ConnectionPtr pConnection = NULL;
	_RecordsetPtr pRecordset = NULL;

	try		{

		bRet = 1;	TESTHR(pConnection.CreateInstance(__uuidof(Connection)));
		bRet = 2;	TESTHR(pRecordset.CreateInstance(__uuidof(Recordset)));
		bRet = 3;	TESTHR(pConnection->Open(bstrConnect, _T(""), _T(""), adModeUnknown));
		bRet = 4;	TESTHR(pRecordset->Open(bstrSQL, pConnection.GetInterfacePtr(), 
			adOpenForwardOnly, adLockReadOnly, adCmdText));
		
		m_arstrMtrData.clear();
		m_arlWidth.clear();
		
		m_lCols = pRecordset->Fields->Count;		
		for (long l = 0; l < m_lCols; l++)		{
			m_arstrMtrData.push_back((LPCTSTR)pRecordset->Fields->Item[l]->Name);
			m_arlWidth.push_back(100);
		}
		
		_variant_t  v;
		while (!pRecordset->adoEOF)		{
			for (l = 0; l < m_lCols; l++)	{
				v = pRecordset->Collect[l];
				if (v.vt == VT_EMPTY || v.vt == VT_NULL)
					m_arstrMtrData.push_back(_T(""));
				else
					m_arstrMtrData.push_back((LPCTSTR)(_bstr_t)v);
			}
			pRecordset->MoveNext();
		}
		
		bRet = S_OK;
	}	catch(...)	{
		;
	}
	
	if (pRecordset->State)
		pRecordset->Close();
	
	if(pConnection->State)
		pConnection->Close();
	
	if (m_lCols != 0 && m_arstrMtrData.size() % m_lCols != 0)
		bRet = 5;
	
	if (bRet != S_OK)	{
		m_lRows = m_lCols = 0;
		m_arstrMtrData.clear();
	}	else	{
		m_lRows = m_arstrMtrData.size() / m_lCols; // not include Header
	}
	
	return bRet;
}

HRESULT CEdMtrS::setParams(BSTR bstrTitle, BSTR bstrHeadRight, BSTR bstrFootLeft, 
						  BSTR bstrFootRight, BSTR bstrFontName, BSTR bstrColsWidthStr, 
						  long lFixedCols)
{
	m_csTitle = (_bstr_t)bstrTitle;
	m_csHeadRight = (_bstr_t)bstrHeadRight;
	m_csFootLeft = (_bstr_t)bstrFootLeft;
	m_csFootRight = (_bstr_t)bstrFootRight;
	m_csFontName = (_bstr_t)bstrFontName;
	m_lFixedCols = lFixedCols;
	
	m_arlWidth.clear();
	
	_bstr_t strColsWidthStr(bstrColsWidthStr);
	TCHAR* pStop = strColsWidthStr;
	
	long l = 0;
	while(1)
	{
		l = _tcstol(pStop, &pStop, 10);
		pStop++;
		
		if (l < 0)
			l = -l;
		else if (l == 0)
			break;
		else;
		
		m_arlWidth.push_back(l);
	}
	
	l = m_arlWidth[0];
	while(m_arlWidth.size() < m_lCols)
		m_arlWidth.push_back(l);
	
	return S_OK;
}

BOOL CEdMtrS::DrawCell(HDC hDC, int nRow, int nCol, RECT rect)
{
    int nSavedDC = SaveDC(hDC);
    SetBkMode(hDC, TRANSPARENT);
	
	COLORREF clr = RGB(214, 235, 255);
	if (nRow % 2 != 0)
		clr = ::GetSysColor(COLOR_WINDOW);
	
	if (nCol < m_lFixedCols)
		clr = ::GetSysColor(COLOR_3DFACE);
	
	HBRUSH hBrush = CreateSolidBrush(clr);
	rect.right++; rect.bottom++;    // FillRect doesn't draw RHS or bottom
	FillRect(hDC, &rect, hBrush);
	rect.right--; rect.bottom--;
	SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));
    DrawText(hDC, m_arstrMtrData[nRow * m_lCols + nCol].c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RestoreDC(hDC, nSavedDC);
	DeleteObject(hBrush);	
    return TRUE;
}

BOOL CEdMtrS::DrawFixedCell(HDC hDC, int nRow, int nCol, RECT rect)
{
	HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	FillRect(hDC, &rect, hBrush);
    SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));
    
    int nSavedDC = SaveDC(hDC);
	GetCurrentObject(hDC, OBJ_PEN);
	HPEN hLightPen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DHIGHLIGHT));
	HPEN hDarkPen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW));
	
	HPEN hOldPen = (HPEN)SelectObject(hDC, hLightPen);
	MoveToEx(hDC, rect.right, rect.top, NULL);
	LineTo(hDC, rect.left, rect.top);
	LineTo(hDC, rect.left, rect.bottom);
	
	SelectObject(hDC, hDarkPen);
	MoveToEx(hDC, rect.right, rect.top, NULL);
	LineTo(hDC, rect.right, rect.bottom);
	LineTo(hDC, rect.left, rect.bottom);
	
	SelectObject(hDC, hOldPen);
	rect.top++;rect.left++;
	rect.bottom--;rect.right--;
    SetBkMode(hDC, TRANSPARENT);
    DrawText(hDC, m_arstrMtrData[nRow * m_lCols + nCol].c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	
    RestoreDC(hDC, nSavedDC);
	
	DeleteObject(hDarkPen);
	DeleteObject(hLightPen);
	DeleteObject(hBrush);
	
    return TRUE;
}

void CEdMtrS::PrintColumnHeadings(HDC hDC)
{
    HFONT hOldFont = (HFONT)SelectObject(hDC, m_hPrinterFont);

    RECT rect;
    rect.bottom = -1;
    for (int row = 0; row < 1; row++)
    {
        rect.top = rect.bottom+1;
        rect.bottom = rect.top + (m_CharSize.cy + 2) - 1;

        rect.right = -1;
        for (int col = 0; col < m_lCols; col++)
        {
            rect.left = rect.right+1;
            rect.right = rect.left + m_arlWidth[col] - 1;

            DrawFixedCell(hDC, row, col, rect);

			int Overlap = (col == 0)? 0:1;
			MoveToEx(hDC, rect.left-Overlap, rect.bottom, NULL);
			LineTo(hDC, rect.right, rect.bottom);
			if (row == 0) {
				MoveToEx(hDC, rect.left-Overlap, rect.top, NULL);
				LineTo(hDC, rect.right, rect.top);
			}

			Overlap = (row == 0)? 0:1;
			MoveToEx(hDC, rect.right, rect.top-Overlap, NULL);
			LineTo(hDC, rect.right, rect.bottom);
			if (col == 0) {
				MoveToEx(hDC, rect.left, rect.top-Overlap, NULL);
				LineTo(hDC, rect.left, rect.bottom);
			}
        }
    }

    SelectObject(hDC, hOldFont);
}

void CEdMtrS::PrintHeader(HDC hDC)
{
    RECT   rc(m_rectDraw);

    string strCenter = m_csTitle;
	if (strCenter.size() == 0)
		strCenter = _T("EdMtrData Printer");

    //create bold font for header and footer
    LOGFONT lf;
	if (!GetObject(m_hPrinterFont, sizeof(lf), &lf))
		return;

    lf.lfWeight = FW_BOLD;
    HFONT hBoldFont = CreateFontIndirect(&lf);
	lf.lfHeight = LONG(lf.lfHeight * 1.5);
	lf.lfWeight = LONG(lf.lfWeight * 1.5);
    HFONT hBigFont = CreateFontIndirect(&lf);
	
    HFONT hNormalFont = (HFONT)SelectObject(hDC, hBigFont);
    int nPrevBkMode = SetBkMode(hDC, TRANSPARENT);

    // print parent window title in the centre (Gert Rijs)

    if( strCenter.size() != 0)
        DrawText( hDC, strCenter.c_str(), -1,  &rc, DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);

    SelectObject(hDC, hBoldFont);
    if( m_csHeadRight.size() != 0 )
        DrawText( hDC, m_csHeadRight.c_str(), -1, &rc, DT_RIGHT | DT_SINGLELINE | DT_NOPREFIX | DT_BOTTOM);

    SetBkMode(hDC,nPrevBkMode);
    SelectObject(hDC, hNormalFont);
	DeleteObject(hBigFont);
    DeleteObject(hBoldFont);

	HPEN hPen = CreatePen(PS_SOLID, 1, 0xFFFFFFF);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
    MoveToEx(hDC, rc.left, rc.bottom, NULL);
    LineTo(hDC, rc.right, rc.bottom);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

//print footer with a line and date, and page number
void CEdMtrS::PrintFooter(HDC hDC)
{
    RECT rc(m_rectDraw);

    //draw line
    MoveToEx(hDC, rc.left, rc.top, NULL);
    LineTo(hDC,rc.right, rc.top);

	// draw page number
	TCHAR tmpbuf[128];
    string strLeft = m_csFootLeft;
	if (strLeft.size() == 0)
	{
		_sntprintf(tmpbuf, 128, _T("Page %d of %d"), m_nCurPage, m_nMaxPages);
		strLeft = tmpbuf;
	}
	
    string strRight = m_csFootRight;
	if (strRight.size() == 0)
	{
		_tstrdate(tmpbuf);
		strRight += tmpbuf;
		strRight += _T(" ");
		_tstrtime(tmpbuf);
		strRight += tmpbuf;
	}
	
    //create bold font for header and footer
    LOGFONT lf;
	if (!GetObject(m_hPrinterFont, sizeof(lf), &lf))
		return;
	
    lf.lfWeight = FW_BOLD;
    HFONT   hBoldFont = CreateFontIndirect(&lf);
    HFONT hNormalFont = (HFONT)SelectObject(hDC, hBoldFont);
    int nPrevBkMode = SetBkMode(hDC, TRANSPARENT);
	
    if( strLeft.size() != 0 )
        DrawText(hDC, strLeft.c_str(), -1, &rc, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);
    if( strRight.size() != 0 )
        DrawText(hDC, strRight.c_str(), -1, &rc, DT_RIGHT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);

    SetBkMode(hDC, nPrevBkMode);
    SelectObject(hDC, hNormalFont);
	DeleteObject(hBoldFont);
}

void CEdMtrS::OnBeginPrinting(HDC hDC)
{
    // Get a DC for the current window (will be a screen DC for print previewing)
    HDC HCurDC = ::GetDC(NULL);        // will have dimensions of the client area
    if (NULL == HCurDC) return;

    SIZE PaperPixelsPerInch = { GetDeviceCaps(hDC, LOGPIXELSX), GetDeviceCaps(hDC, LOGPIXELSY) };
    SIZE ScreenPixelsPerInch = {GetDeviceCaps(HCurDC, LOGPIXELSX), GetDeviceCaps(HCurDC, LOGPIXELSY) };

    // Create the printer font
    m_hPrinterFont = CreateFont(-9, 0,0,0, FW_NORMAL, 0,0,0, DEFAULT_CHARSET,
                             OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
                             DEFAULT_PITCH | FF_DONTCARE, m_csFontName.c_str());
            
    HFONT hOldFont = (HFONT)SelectObject(hDC, m_hPrinterFont);

    // Get the average character width (in GridCtrl units) and hence the margins
	GetTextExtentPoint(hDC, _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSATUVWXYZ"), 52, &m_CharSize);
    m_CharSize.cx /= 52;
    
	int nMargins = (LEFT_MARGIN + RIGHT_MARGIN)*m_CharSize.cx;

    // Get the page sizes (physical and logical)
    m_PaperSize.cx = GetDeviceCaps(hDC, HORZRES);
	m_PaperSize.cy = GetDeviceCaps(hDC, VERTRES);


	int nTotalWidth = 0;
	for (int i = 0; i < m_lCols; i++)
		nTotalWidth += m_arlWidth[i];
    m_LogicalPageSize.cx = nTotalWidth + nMargins;

    m_LogicalPageSize.cy = MulDiv(m_LogicalPageSize.cx, m_PaperSize.cy, m_PaperSize.cx);
	
    m_nPageHeight = m_LogicalPageSize.cy - (m_CharSize.cy + 2)
                       - (HEADER_HEIGHT+FOOTER_HEIGHT + 2*GAP)*m_CharSize.cy;

    // Set up the print info
	m_nMaxPages = (m_CharSize.cy + 2) * m_lRows / m_nPageHeight + 1;
    m_nCurPage = 1;                        // start printing at page# 1

    ReleaseDC(NULL, HCurDC);
    SelectObject(hDC, hOldFont);
}

void CEdMtrS::OnPrint(HDC hDC)
{
    HFONT hOldFont = (HFONT)SelectObject(hDC, m_hPrinterFont);	

    // Set the page map mode to use GridCtrl units, and setup margin
    SetMapMode(hDC, MM_ANISOTROPIC);
    SetWindowExtEx(hDC, m_LogicalPageSize.cx, m_LogicalPageSize.cy, NULL);
    SetViewportExtEx(hDC, m_PaperSize.cx, m_PaperSize.cy, NULL);
    SetWindowOrgEx(hDC, -LEFT_MARGIN*m_CharSize.cx, 0, NULL);

    // Header
    m_rectDraw.top    = 0;
    m_rectDraw.left   = 0;
    m_rectDraw.right  = m_LogicalPageSize.cx - (LEFT_MARGIN+RIGHT_MARGIN)*m_CharSize.cx;
    m_rectDraw.bottom = HEADER_HEIGHT*m_CharSize.cy;
    PrintHeader(hDC);
    OffsetWindowOrgEx(hDC, 0, -HEADER_HEIGHT*m_CharSize.cy, NULL);

    // Gap between header and column headings
    OffsetWindowOrgEx(hDC, 0, -GAP*m_CharSize.cy, NULL);

    // Print the column headings
    m_rectDraw.bottom = (m_CharSize.cy + 2);
    PrintColumnHeadings(hDC);
    OffsetWindowOrgEx(hDC, 0, -(m_CharSize.cy + 2), NULL);

    // We need to find out which row to start printing for this page.
    int nTotalRowHeight = 0;
    UINT nNumPages = 1;
    int nCurrPrintRow = 1;

    while (nCurrPrintRow < m_lRows && nNumPages < m_nCurPage)
    {
        nTotalRowHeight += (m_CharSize.cy + 2);
        if (nTotalRowHeight > m_nPageHeight) {
            nNumPages++;
            if (nNumPages == m_nCurPage) break;
            nTotalRowHeight = (m_CharSize.cy + 2);
        }
        nCurrPrintRow++;
    }
    if (nCurrPrintRow >= m_lRows) return;

    // Draw as many rows as will fit on the printed page.
    // Clip the printed page so that there is no partially shown
    // row at the bottom of the page (the same row which will be fully
    // shown at the top of the next page).

    BOOL bFirstPrintedRow = TRUE;

    RECT rect;
    rect.bottom = -1;
    while (nCurrPrintRow < m_lRows)
    {
        rect.top = rect.bottom+1;
        rect.bottom = rect.top + (m_CharSize.cy + 2) - 1;

        if (rect.bottom > m_nPageHeight) break;            // Gone past end of page

        rect.right = -1;
        for (int col = 0; col < m_lCols; col++)
        {
            rect.left = rect.right+1;
            rect.right = rect.left + m_arlWidth[col] - 1;

            DrawCell(hDC, nCurrPrintRow, col, rect);

			int Overlap = (col == 0)? 0:1;
			MoveToEx(hDC, rect.left-Overlap, rect.bottom, NULL);
			LineTo(hDC, rect.right, rect.bottom);
			if (nCurrPrintRow == 0) {
				MoveToEx(hDC, rect.left-Overlap, rect.top, NULL);
				LineTo(hDC, rect.right, rect.top);
			}
			
			Overlap = (bFirstPrintedRow)? 0:1;
			MoveToEx(hDC, rect.right, rect.top-Overlap, NULL);
			LineTo(hDC, rect.right, rect.bottom);    
			if (col == 0) {
				MoveToEx(hDC, rect.left, rect.top-Overlap, NULL);
				LineTo(hDC, rect.left, rect.bottom);    
			}
        }

        nCurrPrintRow++;
        bFirstPrintedRow = FALSE;
    }

    // Footer
    m_rectDraw.bottom = FOOTER_HEIGHT*m_CharSize.cy;
    SetWindowOrgEx(hDC, -LEFT_MARGIN*m_CharSize.cx, -m_LogicalPageSize.cy + FOOTER_HEIGHT*m_CharSize.cy, NULL);
    PrintFooter(hDC);

    // SetWindowOrg back for next page
    SetWindowOrgEx(hDC, 0, 0, NULL);

    SelectObject(hDC, hOldFont);
}

void CEdMtrS::OnEndPrinting()
{
    DeleteObject(m_hPrinterFont);
}


void CEdMtrS::print(HDC hDC)
{	
	if (NULL == hDC)	return;
    int nMaxRowCount = m_lRows;
    if (nMaxRowCount < 1) return;
	if (m_arlWidth.size() != m_lCols) return;
		
    string strTitle(m_csTitle);
	if (strTitle.size() == 0)
		strTitle = _T("EdMtrData Printer Title");
	//strTitle.LoadString(AFX_IDS_APP_TITLE);
	
    DOCINFO di;                                 // Initialise print doc details
    memset(&di, 0, sizeof (DOCINFO));
    di.cbSize = sizeof (DOCINFO);
    di.lpszDocName = strTitle.c_str();
	
    BOOL bPrintingOK = StartDoc(hDC, &di);        // Begin a new print job
	
    m_rectDraw.top = 0;
	m_rectDraw.left= 0;
	m_rectDraw.right = GetDeviceCaps(hDC, HORZRES);
	m_rectDraw.bottom= GetDeviceCaps(hDC, VERTRES);
	
    OnBeginPrinting(hDC);                // Initialise printing
    for (UINT page = 1; page <= m_nMaxPages && bPrintingOK; page++)
    {
        StartPage(hDC);                         // begin new page
        m_nCurPage = page;
        OnPrint(hDC);                    // Print page
        bPrintingOK = (EndPage(hDC) > 0);       // end page
    }
    OnEndPrinting();                  // Clean up after printing
	
    if (bPrintingOK)
        EndDoc(hDC);                            // end a print job
    else
        AbortDoc(hDC);                          // abort job.
	
    DeleteDC(hDC);                                // detach the printer DC
	
	return;
}

string CEdMtrS::getData(long row, long col) const
{ 
	if (row < m_lRows && col < m_lCols)
		return m_arstrMtrData[row * m_lCols + col];
	else
		return _T("");
}

void CEdMtrS::setSize(long row, long col)
{ 
	m_arstrMtrData.clear(); 
	m_arlWidth.clear();
	
	m_lRows = row;
	m_lCols = col;
	for (long i = 0; i < col; i++)	{
		m_arlWidth.push_back(100);
		for(long j = 0; j < row; j++)
			m_arstrMtrData.push_back(_T(""));
	}
}

void CEdMtrS::setData(long row, long col, BSTR bstrData)
{
	if (row <  m_lRows && col < m_lCols)
		m_arstrMtrData[row * m_lCols + col] = (LPCTSTR)(_bstr_t)bstrData;
}