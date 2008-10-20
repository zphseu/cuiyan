// EdMtr.h: interface for the CEdMtrS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDMTRS_H__3467BDA8_6EE0_448A_88CC_979EDF66FD43__INCLUDED_)
#define AFX_EDMTRS_H__3467BDA8_6EE0_448A_88CC_979EDF66FD43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>

using namespace std;
#ifdef _UNICODE
#define string wstring
#endif

class CEdMtrS
{
public:
	CEdMtrS();
	virtual ~CEdMtrS();

public:
	typedef vector<string>	astring;
	typedef vector<long>	along;

	string	getData(long row, long col) const;	
	long	getCols() const { return m_lCols; }
	long	getRows() const { return m_lRows; }
	void	setSize(long row, long col);
	void	setData(long row, long col, BSTR bstrData);

	void	print(HDC hDC);
	HRESULT readFile(BSTR bstrFileName, BSTR bstrTableName);
	HRESULT readDB(BSTR bstrConnect, BSTR bstrSQL);
	HRESULT setParams(BSTR bstrTitle, BSTR bstrHeadRight, BSTR bstrFootLeft, 
		BSTR bstrFootRight, BSTR bstrFontName, BSTR bstrColsWidthStr, long lFixedCols);
	
protected:
	astring	m_arstrMtrData;
	long	m_lCols;
	long	m_lRows;
	along	m_arlWidth;
	
	long	m_lFixedCols;
	string	m_csTitle;
	string	m_csHeadRight;
	string	m_csFootLeft;
	string	m_csFootRight;
	string	m_csFontName;

	BOOL readFile_Header(IXMLDOMDocumentPtr& pXDoc, long &lFixedCols);
	IXMLDOMNodePtr readFile_FindTable(IXMLDOMNodeListPtr& pParent, BSTR bstrNodeName);

protected:
    BOOL DrawFixedCell(HDC hDC, int nRow, int nCol, RECT rect);
    BOOL DrawCell(HDC hDC, int nRow, int nCol, RECT rect);
	void PrintColumnHeadings(HDC hDC);
	void PrintHeader(HDC hDC);
	void PrintFooter(HDC hDC);
    void OnBeginPrinting(HDC hDC);
    void OnPrint(HDC hDC);
    void OnEndPrinting();
	
	HFONT	m_hPrinterFont;	// for the printer
    int     m_nPageHeight;
	RECT	m_rectDraw;
	long	m_nCurPage;
	long	m_nMaxPages;
    SIZE	m_CharSize;
	SIZE	m_PaperSize;           // Page size in device units.
    SIZE	m_LogicalPageSize;      // Page size in gridctrl units.	
};

#endif // !defined(AFX_EDMTRS_H__3467BDA8_6EE0_448A_88CC_979EDF66FD43__INCLUDED_)
