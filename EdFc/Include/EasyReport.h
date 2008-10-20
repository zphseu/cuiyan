
/*******************************************************************************
 * EasyReport.h: interface for the CElement class.
 *
 * MFC Easy! Report class
 *
 * Written by Vipul Lal <vipul@hotmail.com>
 * Copyright (c) 2000-2002. All Rights Reserved.
 *
 * This code may be used in compiled form in any way you desire. This
 * file may be redistributed unmodified by any means PROVIDING it is 
 * not sold for profit without the authors written consent, and 
 * providing that this notice and the authors name and all copyright 
 * notices remains intact. 
 *
 * An email letting me know how you are using it would be nice too. 
 *
 * This file is provided "as is" with no expressed or implied warranty.
 * The author accepts no liability for any damage/loss of business that
 * this product may cause.
 *
 *
 *******************************************************************************/


#if !defined(_EasyReport_H_65D16A04_6617_45DA_AE5C_B625482F7098)
#define _EasyReport_H_65D16A04_6617_45DA_AE5C_B625482F7098


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CEasyReport : public CObject  
{

public:

	// Struct CColInfo defines columns in a tabular section.
	struct CColInfo
	{
		enum eAlignType { eLeft, eCenter, eRight, eDecimal };

		const char *m_Heading;
		int			m_CharCount;
		eAlignType	m_align;
	};


protected:
	DECLARE_SERIAL( CEasyReport)
	void	Serialize(CArchive &);

// Data members
	// Page Stats...
	int				m_PageHeight;	// height of the entire page
	int				m_PageWidth;
	int				m_TopMargin;	// page top margin
	int				m_BottomMargin;
	int				m_LeftMargin;
	int				m_RightMargin;

	// Standard fonts and styles...
	enum eFontIndex { eCaptionFont, eColHeadingFont, eDataFont, eTextFont };
	enum { eMaxStyles = eTextFont + 1 };

	CFont		*m_Fonts[ eMaxStyles ];
	CSize		m_TextSizes[ eMaxStyles ];
	CPen		m_StdPen;

	// printer device context. Valid only while printing
	HDC				m_PrinterDC;

	// Page
	int				m_MaxCol;
	int				m_PageCount;
	int				m_CurPage;		// current page on display
	int				m_DataTop;		// top of the data area on this page.

	// Report generation
	CPtrArray		m_ReportItems;
	CWordArray		m_PageItems;	// for preview

	// Table support
	CWordArray		m_TabStops;			// array of tab stops for the columns
	CColInfo		*m_DataCols;		// Array of column info items in the table
	int				m_NumDataCols;		// # of columns in the table

	bool			m_RepeatTblHdr;		// repeat this header on every page
	bool			m_RedrawTblHdr;		// set after EjectPage and reset with AtCol
	bool			m_SuppressBlankTbl;	// Suppress table header if table is blank

	int				m_TableHeadingHt;	// for multi-row headings
	TCHAR			m_BreakChar;		// for word wrapping.

	// headers and footers
	int				m_ReportHdrHt;	// height of the report header
	int				m_ReportFtrHt;	// height of the report footer
	int				m_PageHdrHt;	// height of the page header
	int				m_PageFtrHt;	// height of the page footer
	
	// Standard items used in a report
	CString			m_CompanyName;		// name of this company
	CString			m_ReportTitle;		// report title
	CString			m_ReportDate;		// report date

	// protected members
	void	SetupRectForCol(int inTabStop, CRect &outRect);
	void	WriteParagraph(const char *inText);


public:
	CEasyReport();
	virtual ~CEasyReport();
	virtual void	DoCleanup();

	// Functionality
	void	Start(void);
	void	End();
	void	DrawCurrentPage(CDC *inDC);

	// setters...
	void	SetCompanyName(const char *inStr)		{ m_CompanyName = inStr;}
	void	SetReportTitle(const char *inStr)		{ m_ReportTitle = inStr;}

	void	AtTab(int,const char *);	// print something at tab(n)
	void	AtTab(int,double,bool inInsertCommas = true);
	void	NextRow();					// position to next row
	void	SetDataCols(CColInfo *inCols = NULL, int nCols=0);
	void	WriteTableHeader();

	bool	EjectPage(bool inIsLastPage = false);

	// override to customize
	virtual	void	WriteReportHeader(CRect inRect);
	virtual	void	WriteReportFooter(CRect inRect);
	virtual	void	WritePageHeader(CRect inRect);
	virtual	void	WritePageFooter(CRect inRect);
	virtual	void	SetupTextStyles(HDC inDC);

	// rendered report
	int		GetPageCount()			{return m_PageCount;}
	int		GetCurPage()			{ return m_CurPage;}

	void	GotoPage(int inPage)	
	{ 
		if(inPage < m_PageCount)
			m_CurPage = inPage;
	}


	// page stats
	int		GetPageWidth(void)		{return m_PageWidth;}
	int		GetPageHeight(void)		{return m_PageHeight;}
	int		GetLeftMargin(void)		{return m_LeftMargin;}
	int		GetTopMargin(void)		{return m_TopMargin;}
	int		GetRightMargin(void)	{return m_RightMargin;}
	int		GetBottomMargin(void)	{return m_BottomMargin;}
	int		GetRightEdge(void)		{return m_PageWidth - m_RightMargin;}
	int		GetBottomEdge(void)		{return m_PageHeight - m_BottomMargin;}

	const CPen  *GetPen(int)
	{
		return &m_StdPen;	// only one pen style supported for now
	}

	const CFont	*GetStyle(int inStyleIndex);


	const CSize &  GetCaptionFontSize()
	{
		return m_TextSizes[ eCaptionFont ];
	}

	const CSize &  GetHeadingFontSize()
	{
		return m_TextSizes[ eColHeadingFont ];
	}


	const CSize &  GetDataFontSize()
	{
		return m_TextSizes[ eDataFont ];
	}

};



#endif // !defined(_EasyReport_H_65D16A04_6617_45DA_AE5C_B625482F7098)

