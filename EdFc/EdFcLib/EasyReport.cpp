/*******************************************************************************
 * EasyReport.cpp: implementation of the CEasyReport class.
 *
 * MFC Easy! Report class
 *
 * Written by Vipul Lal <VipulLal@hotmail.com> or <vipul@del2.vsnl.net.in>
 * Copyright (c) 2000-2002. All Rights Reserved.
 *
 * This code may be used in compiled form in any way you desire. This
 * file may be redistributed unmodified by any means PROVIDING it is 
 * not sold for profit without the authors written consent, and 
 * providing that this notice and the authors name and all copyright 
 * notices remains intact. 
 *
 * An email letting me know how you are using it would be nice. 
 *
 * This file is provided "as is" with no expressed or implied warranty.
 * The author accepts no liability for any damage/loss of business that
 * this product may cause.
 *
 * Description:
 * This class encapsulates the functionality required for most reports. 
 * We could have derived this class from CDocument, but that would not 
 * have been as flexible as a stand alone class. 
 *
 *
 *
 *******************************************************************************/

#include "stdafx.h"
#include "EasyReport.h"
#include "RepElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_SERIAL(CEasyReport, CObject,1);

void	CEasyReport::Serialize(CArchive & inAr)
{
	// no serialize yet !
}


/*****************************************************************
 * 
 * method :CEasyReport::CEasyReport()
 *
 * parameters : None
 *
 * returns : Nothing
 *
 * description: Constructor. Set up page sizes, initalize pointers
 * to null etc.
 *
 ****************************************************************/
CEasyReport::CEasyReport()
{
	int		i;
	for(i=0;i < eMaxStyles ;i++)
	{
		m_Fonts[i]= NULL;
	}

	// print device context...
	m_PrinterDC = NULL;

	// No data columns as yet..
	m_NumDataCols = 0;
	m_DataCols = NULL;


	// setup page defaults. Note: The report used the LO_METRIC
	// unit of measurement. Thus, 1 inch = 2.54 cms = 25.4 mm =
	// 254 LO_METRIC units.
	m_PageHeight = 11 * 254;	// height of the entire page
	m_PageWidth = (int)(8.5 * 254);
	m_TopMargin = 127;		// Half inch margin all around
	m_BottomMargin = 127;
	m_LeftMargin = 15;
	m_RightMargin = 127;

	// headers and footers. By default, ReportHeader and ReportFooter
	// are set to .5". The default report header consists of the 
	// company name centered on the page. The default page header
	// contains the report name and the date. The default page
	// footer contains the page number centered within the margins.
	// These are defaults. You can override these in derived classes
	// or set these directly. For instance, to customize the default 
	// report header, override the WriteReportHeader() virtual. Ditto 
	// for other headers and footers.
	m_PageHdrHt = 100;		// height of the page header is 1cm
	m_PageFtrHt = 100;		// height of the page footer is 1cm
	m_CurPage = m_PageCount = 0;

	// The m_SuppressBlankTbl, if true, will suppress a table header from 
	// appearing on the report unless something is written to one of the 
	// columns. The RepeatTblHdr flag forces the system to repeat the 
	// column headings on every page.
	m_SuppressBlankTbl = true;	// do not write the column headings if no data is written to the column
	m_RepeatTblHdr = false;		// do not repeat column headings on every page

	// Default report heading contains the company name
	m_CompanyName = "";	// replace with your company name !
	m_ReportHdrHt = 200;	// 2 cm high
	m_ReportFtrHt = 0;		// no report footer

	m_StdPen.CreatePen(PS_SOLID,2, RGB(0,0,0));
}

/*****************************************************************
 * 
 * method :void	CEasyReport::SetupTextStyles(CDC *inDC)
 *
 * parameters : inDC: Handle to the printer device context
 *
 * returns : Nothing.
 *
 * description: Set up the fonts required for the report. This is a
 * virtual function, so if you override in derived classes, you can 
 * modify the default fonts. Actually, it might have been better if
 * we had individual virtual functions, like "CreateHeadingFont" etc
 * which would enable the user to override individual font styles
 * per report. Maybe we can implement this in a later version!
 *
 * The Caption font is used for the report title.
 * The ColHeading font is used for column headings.
 * The DataFont is used for the data in columns
 * The TextFont is used for paragraphs of text.
 *
 ****************************************************************/
void	CEasyReport::SetupTextStyles(HDC  inDC)
{
	// create default fonts...
	LOGFONT			aFont;
	CPoint			aPoint;
	
	// The caption font is 20 point bold, italics
	aPoint.y = (20 * GetDeviceCaps(inDC, LOGPIXELSY))/72;
	DPtoLP(inDC, &aPoint,1);
	memset(&aFont,0,sizeof(aFont));
	aFont.lfHeight = aPoint.y;
	aFont.lfWeight = FW_BOLD;
	aFont.lfItalic = 1;
	aFont.lfOutPrecision = OUT_STROKE_PRECIS; // Truetype font
	aFont.lfQuality = PROOF_QUALITY;
	aFont.lfPitchAndFamily = FF_ROMAN | VARIABLE_PITCH;
	m_Fonts[ eCaptionFont ] = new CFont();
	m_Fonts[ eCaptionFont ]->CreateFontIndirect(&aFont);

	// the column heading font is 10-point bold, italic
	aPoint.y = (10 * GetDeviceCaps(inDC,LOGPIXELSY))/72;
	DPtoLP(inDC,&aPoint,1);
	memset(&aFont,0,sizeof(aFont));
	aFont.lfHeight = aPoint.y;
	aFont.lfItalic = 1;
	aFont.lfWeight = FW_BOLD;
	aFont.lfOutPrecision = OUT_TT_PRECIS ; // Truetype font
	aFont.lfQuality = PROOF_QUALITY;
	aFont.lfPitchAndFamily = FF_SWISS | VARIABLE_PITCH;
	m_Fonts[ eColHeadingFont ] = new CFont();
	m_Fonts[ eColHeadingFont ]->CreateFontIndirect(&aFont);

	// the data font is 10 point regular
	aPoint.y = (10 * GetDeviceCaps(inDC,LOGPIXELSY))/72;
	::DPtoLP(inDC,&aPoint,1);
	memset(&aFont,0,sizeof(aFont));
	aFont.lfHeight = aPoint.y;
	aFont.lfWeight = FW_REGULAR;
	aFont.lfOutPrecision = OUT_TT_PRECIS; // Truetype font
	aFont.lfQuality = PROOF_QUALITY;
	aFont.lfPitchAndFamily = FF_ROMAN | FIXED_PITCH;
	m_Fonts[ eDataFont ] = new CFont();
	m_Fonts[ eDataFont ]->CreateFontIndirect(&aFont);

	// the text font is ansi variable font
	m_Fonts[ eTextFont ] = new CFont();
	m_Fonts[ eTextFont ]->CreateStockObject(ANSI_VAR_FONT);
	
	// determine the cell sizes for the fonts...
	TEXTMETRIC		aTM;

	SelectObject(inDC,(HFONT)(*m_Fonts[eCaptionFont]));
	GetTextMetrics( inDC, &aTM );
	m_TextSizes[ eCaptionFont].cx = aTM.tmAveCharWidth;
	m_TextSizes[ eCaptionFont].cy = aTM.tmHeight;

	SelectObject(inDC,(HFONT)(*m_Fonts[eColHeadingFont]));
	GetTextMetrics( inDC, &aTM );
	m_TextSizes[ eColHeadingFont].cx = aTM.tmAveCharWidth;
	m_TextSizes[ eColHeadingFont].cy = aTM.tmHeight;

	SelectObject(inDC,(HFONT)(*m_Fonts[eDataFont]));
	GetTextMetrics(inDC,&aTM );
	m_TextSizes[ eDataFont].cx = aTM.tmAveCharWidth;
	m_TextSizes[ eDataFont].cy = aTM.tmHeight;

	SelectObject(inDC,(HFONT)(*m_Fonts[eTextFont]));
	GetTextMetrics(inDC,&aTM );
	m_TextSizes[ eTextFont].cx = aTM.tmAveCharWidth;
	m_TextSizes[ eTextFont].cy = aTM.tmHeight+ aTM.tmExternalLeading;
	m_BreakChar = aTM.tmBreakChar;
}


/*****************************************************************
 * 
 * method :CEasyReport::~CEasyReport()
 *
 * parameters : 
 *
 * returns : 
 *
 * description: Destructor. Clean up the resources we allocated.
 *
 ****************************************************************/
CEasyReport::~CEasyReport()
{
	DoCleanup();
}


/*****************************************************************
 * 
 * method :void	CEasyReport::DoCleanup()
 *
 * parameters : 
 *
 * returns : 
 *
 * description: Clean up all the resources we allocated
 *
 *
 ****************************************************************/
void	CEasyReport::DoCleanup()
{
	int			i;
	CElement	*aElem;

	for(i=0; i<	m_ReportItems.GetSize();i++)
	{
		aElem = (CElement *) m_ReportItems[i];
		delete aElem;
	}
	m_ReportItems.RemoveAll();	// clear counts...

	for(i=0;i< eMaxStyles;i++)
	{
		delete m_Fonts[i];
		m_Fonts[i]=NULL;
	}
	m_PageItems.RemoveAll();
}


/*****************************************************************
 * 
 * method :void	SetupRectForCol(int inTabStop, CRect &outRect)
 *
 * parameters : 
 *
 * returns : 
 *
 * description: set up rectangle so that the printing can happen only 
 * within the tab stop and the next tab stop, or up the edge of the 
 * right margin
 *
 ****************************************************************/
void	CEasyReport::SetupRectForCol(int inTabStop, CRect &outRect)
{
	outRect.top = m_DataTop;
	outRect.bottom = outRect.top + m_TextSizes[eDataFont].cy;
	if( inTabStop <= 0 )
	{
		// rectangle extends from the left edge upto the first tab stop
		outRect.left = m_LeftMargin;
		outRect.right = m_TabStops[1];
		return;
	}
	// If inTab is after the last valid tab, trim it to be within the right margin.
	if( inTabStop > m_TabStops.GetSize()-1)
	{
		// inTabStop = m_TabStops.GetSize()-1;
		// set to the last tab
		outRect.left = m_TabStops[ m_TabStops.GetSize() - 2 ];
		outRect.right = m_PageWidth - m_RightMargin;
		return;
	}
	outRect.left = m_TabStops[inTabStop];
	outRect.right = m_TabStops[inTabStop+1];
}


/*****************************************************************
 * 
 * method :void		WriteParagraph(const char *inText)
 *
 * parameters : inText: Long text which may be word wrapped
 *
 * returns : nothing
 *
 * description: Write a paragraph of text. If the text extends 
 * beyond the right edge, the text is wrapped around. Note: This 
 * function is not called directly, but through AtTab with tabs
 * set to NULL.
 *
 ****************************************************************/
void	CEasyReport::WriteParagraph(const char *inText)
{
	int			aAbsBottom, aAbsWidth;
	int			aCurPos, aLen, aRight;
	char		aTempStr[128];	// non portable (should be TCHAR etc)!
	CRect		aRect;
	CSize		aSize;
	CTextBox	*aBox;
	
	aRect.left = m_LeftMargin;
	aRect.right = m_PageWidth - m_RightMargin;

	aAbsBottom = m_PageHeight - ( m_BottomMargin + m_PageFtrHt );
	aAbsWidth = m_PageWidth - ( m_LeftMargin + m_RightMargin);

	aLen = (int)_tcslen(inText);
	aCurPos = 0;
	::SelectObject(m_PrinterDC,(HFONT)m_Fonts[eTextFont]);
	::SetTextCharacterExtra(m_PrinterDC,0);
	while(inText[aCurPos])
	{
		if( m_DataTop + m_TextSizes[eTextFont].cy > aAbsBottom )
		{
			EjectPage(false);
			aAbsBottom = m_PageHeight - ( m_BottomMargin + m_PageFtrHt );
		}

		// see if the remainder of the string will fit into the right margin
		::SetTextJustification(m_PrinterDC,0,0);
		::GetTextExtentExPoint(m_PrinterDC, inText + aCurPos, aLen - aCurPos, aAbsWidth, &aRight,NULL, &aSize);

		if( inText[aCurPos+aRight] != 0 )
		{
			while( inText [aCurPos + aRight ] != m_BreakChar )
			{
				--aRight;
				if( aRight <= 0 )
				{
					// Hopeless, the entire string is one big word !
					::GetTextExtentExPoint(m_PrinterDC, inText + aCurPos, aLen - aCurPos, aAbsWidth, &aRight,NULL, &aSize);
					--aRight;
					break;
				}
			}
		}

		ASSERT(aRight < sizeof(aTempStr));	// Warning ! this check is at compile time only !
		strncpy( aTempStr, inText + aCurPos, aRight);
		aTempStr[aRight] = 0;

		aRect.top = m_DataTop;
		aRect.bottom = aRect.top + m_TextSizes[eTextFont].cy;
		aBox = new CTextBox(&aRect, aTempStr, eTextFont);
		aBox->SetDocPtr( this );
		m_ReportItems.Add(aBox);
		if( inText[ aCurPos + aRight] == m_BreakChar)
			++aRight;
		aCurPos += aRight;
		m_DataTop += m_TextSizes[eTextFont].cy;
	}
}


/*****************************************************************
 * 
 * method :void	CEasyReport::AtTab(int inTabStop, const char *inText)
 *
 * parameters : inTabStop
 *				char *inText: text to display
 *
 * returns : nothing
 *
 * description: If a tabular section is in place (ie if m_NumDataCols
 * is non-zero, then we assume that this is a text area and we write
 * out a paragraph. If a tabular section is in place, we write the
 * data into the indicated column.
 *
 *
 ****************************************************************/
void	CEasyReport::AtTab(int inTabStop, const char *inText)
{
	CRect	aRect;

	if( m_NumDataCols == 0)
	{
		WriteParagraph(inText);
	}
	else
	{
		if( m_RedrawTblHdr )
		{
			if( m_DataTop + m_TableHeadingHt + GetDataFontSize().cy > (GetBottomEdge() - m_PageFtrHt) )
				EjectPage(false);
			if( !m_RepeatTblHdr )
				WriteTableHeader();
			m_RedrawTblHdr = false;
		}
		SetupRectForCol(inTabStop, aRect);

		CTextBox	*aBox = new CTextBox(&aRect,inText,eDataFont);
		aBox->SetDocPtr(this);

		ASSERT( inTabStop < m_NumDataCols);
		switch( m_DataCols[inTabStop].m_align)
		{
			case CColInfo::eLeft:
				aBox->SetAlign(DT_LEFT);
				break;
			case CColInfo::eDecimal:
			case CColInfo::eRight:

				// for fixed width fonts, if you control the format of data, then
				// simply aligning the text right aligns the decimal places. For 
				// propotional fonts, you will have to adjust the left edge of
				// the box.

				aBox->SetAlign(DT_RIGHT);
				break;
			case CColInfo::eCenter:
				aBox->SetAlign( DT_CENTER );
				break;
		}
		m_ReportItems.Add( aBox );
	}
}


/*****************************************************************
 * 
 * method :void	CEasyReport::SetDataCols(CColInfo  *inCols, int inColCount)
 *
 * parameters : inCols : Array of CColInfo structur
 *				inColCount: # of columns.
 *
 * returns : Nothing
 *
 * description: Use this function to start a new tabular section
 * on the report. If inCols == NULL (ie if the user wants a non tabular
 * section) the tab stops are set to every 8 characters and the word
 * wrap feature is enabled. 
 *
 * If inCols is not NULL, then the colum start positions are 
 * calculated based on the character counts of the column. 
 * 
 * The algorithm supports multiple row headings - simply put a
 * '\n' into the heading string. See example in SampleReportDoc.cpp
 *
 * Note: The colum width is in number of characters, which is easy,
 * since typically, a database column width is specified in # of 
 * characters. However, with True-type fonts and propotional spacing,
 * the display may be truncated. To eliminate this problem, you might
 * want to modify the code to either use MaxCharWidth for the font or
 * you might want to specify the column with in LogicalUnits. Since 
 * MM_LOMETRIC unit is used in the report, the column width would be 
 * the size in mm * 10.
 *
 ****************************************************************/
void	CEasyReport::SetDataCols(CColInfo  *inCols, int inColCount)
{
	int			i, aLeft, aMax, aCharWidth;
	int			nRows,nMaxRows;
	const char	*s;
	CColInfo	*aCol;

	m_TabStops.RemoveAll();
	if( inCols == NULL || inColCount == 0)
	{
		aCharWidth = m_TextSizes[ eTextFont].cx;
		m_DataCols = NULL;
		m_NumDataCols = 0;
		m_TableHeadingHt = 0;

		// Set up tabs at every 8 characters...
		aMax = (m_PageWidth - m_RightMargin) / 8;
		for(i=0; i <= aMax; i++)
			m_TabStops.Add((WORD)(m_LeftMargin + i * 8 * aCharWidth) );
		return;
	}
	aCharWidth = m_TextSizes[ eDataFont].cx;
	m_DataCols = inCols;
	m_NumDataCols = inColCount;

	
	nRows = nMaxRows = 1;
	aLeft = m_LeftMargin;
	aMax = m_PageWidth - m_RightMargin;
	i = 0;
	do
	{
		m_TabStops.Add( (WORD)aLeft );
		aCol = inCols + i;
		aLeft += aCol->m_CharCount * m_TextSizes[eDataFont].cx;
		ASSERT(aLeft < aMax);	// check that we do not overflow the right edge

		// Calculate the height of this heading text...
		nRows = 1;
		s = aCol->m_Heading;
		if( s)
		{
			do
			{
				s = strchr(s,TCHAR('\n'));
				if(s==NULL)
					break;
				++s;		// past the '\n'
				++nRows;	// bump row count
			}
			while(1);
		}
		if( nRows > nMaxRows )
			nMaxRows = nRows;
		++i;
	}
	while(i < inColCount );
	m_TabStops.Add( (WORD)aLeft );
	m_TableHeadingHt = nMaxRows * m_TextSizes[ eColHeadingFont ].cy;

	if( !m_SuppressBlankTbl )
	{
		// We need to draw the heading. Check if there is enough room
		// on this page to draw the headings.
		if( m_DataTop + m_TableHeadingHt + GetDataFontSize().cy > (GetBottomEdge() - m_PageFtrHt) )
			EjectPage(false);
		if( !m_RepeatTblHdr )
			WriteTableHeader();
	}
	else
	{
		// deffer drawing the columns till something is written to this table
		m_RedrawTblHdr = true; 
	}
}




/*****************************************************************
 * 
 * method :void	CEasyReport::EjectPage(bool inIsLastPage)
 *
 * parameters : inIsLastPage : true if this is the last page
 * of the report.
 *
 * returns : nothing
 *
 * description: Call this function to eject the current page. if this
 * is the last page, we print the report footer. If there
 * is a page footer defined, it will be printed before starting the 
 * new page. 
 *
 ****************************************************************/
bool	CEasyReport::EjectPage(bool inIsLastPage)
{
	CRect	aRect;
	int		aRequiredHt, aAbsBottom;
	bool	aAllPrinted = true;


	aRect.left = m_LeftMargin;
	aRect.right = m_PageWidth - m_RightMargin;
	aAbsBottom = m_PageHeight - m_BottomMargin;

	if(inIsLastPage)
	{
		// check to see if the PageFooter and the ReportFooter 
		// will fit on to the remaining area on this page. If so, 
		// print the page footer and the report footer. 
		aRequiredHt = m_PageFtrHt + m_ReportFtrHt;
		if( m_DataTop + aRequiredHt <= aAbsBottom )
		{
			aRect.top = aAbsBottom - (m_PageFtrHt+ m_ReportFtrHt);
			aRect.bottom = aRect.top + m_PageFtrHt;
			WritePageFooter(aRect);
			if( m_ReportFtrHt)
			{
				aRect.top = aRect.bottom;
				aRect.bottom += m_ReportFtrHt;
				WriteReportFooter(aRect);
			}
		}
		else
		{
			aRect.top = aAbsBottom - m_PageFtrHt;
			aRect.bottom = aRect.top + m_PageFtrHt;
			WritePageFooter(aRect);
			aAllPrinted = (m_ReportFtrHt >0 ? false : true);
		}
	}
	else
	{
		// not the last page of the report. Simply draw the page 
		// footer bottom aligned on the page
		if(m_PageFtrHt > 0 )
		{
			// bottom align the page footer on the page
			aRect.top = aAbsBottom - m_PageFtrHt;
			aRect.bottom = aRect.top + m_PageFtrHt;
			WritePageFooter(aRect);
		}
	}

	m_PageItems.Add((WORD)m_ReportItems.GetSize());
	++m_PageCount;

	m_DataTop = m_TopMargin;

	// If not the last page, then print the page header if there
	// is a page header.
	if( !inIsLastPage && m_PageHdrHt > 0 )
	{
		aRect.top = m_DataTop;
		aRect.bottom = aRect.top + m_PageHdrHt;
		WritePageHeader(aRect);
		m_DataTop += m_PageHdrHt;
	}

	// Print the table header only if needed
	// m_RedrawTblHdr = false;	
	if( !inIsLastPage && m_RepeatTblHdr && m_NumDataCols != 0 )
	{
		if( !m_SuppressBlankTbl )
			WriteTableHeader();
		else
			m_RedrawTblHdr = true;
	}
	return aAllPrinted;
}



/*****************************************************************
 * 
 * method :void	CEasyReport::WriteTableHeader(void)
 *
 * parameters : 
 *
 * returns : 
 *
 * description: If a tabular section is in place, write the table
 * header.
 *
 ****************************************************************/
void	CEasyReport::WriteTableHeader(void)
{
	int		i;
	CRect	aRect;

	m_RedrawTblHdr = false;
	aRect.top = aRect.bottom = m_DataTop;
	aRect.bottom += m_TableHeadingHt;
	aRect.left= m_LeftMargin;
	for(i=0;i < m_NumDataCols; i++)
	{
		CColInfo	*aCol = m_DataCols+i;
		aRect.right = aRect.left + aCol->m_CharCount * m_TextSizes[eDataFont].cx;
		CTextBox	*aBox = new CTextBox(&aRect, aCol->m_Heading, eColHeadingFont);
		switch( aCol->m_align)
		{
			case CColInfo::eLeft:
				aBox->SetAlign(DT_LEFT);
				break;
			case CColInfo::eDecimal:
			case CColInfo::eRight:

				// for fixed width fonts, if you control the format of data, then
				// simply aligning the text right aligns the decimal places. For 
				// propotional fonts, you will have to adjust the left edge of
				// the box. Decimal cols will be supported in a later version

				aBox->SetAlign(DT_RIGHT);
				break;
			case CColInfo::eCenter:
				aBox->SetAlign( DT_CENTER );
				break;
		}

		aBox->SetDocPtr(this);
		m_ReportItems.Add(aBox);
		aRect.left = aRect.right;
	}
	m_DataTop += m_TableHeadingHt;
}

/*****************************************************************
 * 
 * method :void	CEasyReport::NextRow()
 *
 * parameters : 
 *
 * returns : 
 *
 * description: Advance the current point by one row height
 * If this moves the current point below the page margin, call 
 * EjectPage. EjectPage will automatically write the page footer 
 * and start a new page
 *
 ****************************************************************/
void	CEasyReport::NextRow()
{
	m_DataTop += m_TextSizes[eDataFont].cy;
	// see if at least one data row will fit into the remaining
	// space on the page. If it does not, call EjectPage
	if( m_DataTop + m_TextSizes[eDataFont].cy + m_PageFtrHt > GetBottomEdge())
		EjectPage();
}


/*****************************************************************
 * 
 * method :void	CEasyReport::Start(void)
 *
 * parameters : none
 *
 * returns : 
 *
 * description: Start the report generation. Create all the fonts, etc
 * Try and get the printer device context, If no printer is set up as 
 * the default printer on the system, create a screen device context. 
 *
 ****************************************************************/
void	CEasyReport::Start()
{

	ASSERT( m_PrinterDC == NULL );
	DoCleanup();
	
	// set up a print date ..
	if (m_ReportDate.IsEmpty())
	{
		CTime		aNow = CTime::GetCurrentTime();
		m_ReportDate.Format("Date: %2d/%2d/%4d", aNow.GetMonth(), aNow.GetDay(), aNow.GetYear());
	}

	// NOTE: The following is most certainly not correct if there is 
	// no default printer defined ! If you do not have ANY printer, then
	// you might install a Fax printer (eg Microsoft Fax or Bitware etc)
	CPrintDialog	aPD(false);

	if(aPD.GetDefaults())
	{
		m_PrinterDC = aPD.m_pd.hDC;
	}
	else
	{
		m_PrinterDC = ::GetDC(NULL);	// get the screen device context
	}

	//::SetMapMode(m_PrinterDC, MM_ANISOTROPIC);
	//::SetWindowExtEx( m_PrinterDC, 254,254,NULL);
	//::SetViewportExtEx(m_PrinterDC, GetDeviceCaps(m_PrinterDC,LOGPIXELSX),GetDeviceCaps(m_PrinterDC,LOGPIXELSY),NULL);
	SetMapMode( m_PrinterDC, MM_LOMETRIC);
	SetupTextStyles( m_PrinterDC );

	m_DataTop = m_TopMargin;
	m_PageCount = 0;
	m_CurPage = 0;

	CRect		aRect;

	// Write the report header...
	if( m_ReportHdrHt > 0 )
	{
		aRect.SetRect(m_LeftMargin, m_TopMargin, m_PageWidth - m_RightMargin,m_TopMargin + m_ReportHdrHt );

		aRect.bottom = aRect.top + m_ReportHdrHt;
		WriteReportHeader(aRect);
		m_DataTop += m_ReportHdrHt;
	}

	if( m_PageHdrHt > 0)
	{
		aRect.SetRect(m_LeftMargin, m_DataTop, m_PageWidth - m_RightMargin, m_DataTop + m_PageHdrHt);
		WritePageHeader(aRect);
		m_DataTop += m_PageHdrHt;
	}
}

/*****************************************************************
 * 
 * method :void		CEasyReport::End()
 *
 * parameters : 
 *
 * returns : 
 *
 * description: End the report
 *
 ****************************************************************/
void		CEasyReport::End()
{
	EjectPage(true);
	m_CurPage = 0;

	DeleteDC(m_PrinterDC);
	m_PrinterDC = NULL;
}



/*****************************************************************
 * 
 * method :void		WriteReportHeader(CRect inRect)
 *
 * parameters : 
 *
 * returns : 
 *
 * description: Write the default report header, which is a 
 * simply the CompanyName centered across the page. You might 
 * want to add the address, etc.
 *
 ****************************************************************/
void	CEasyReport::WriteReportHeader(CRect inRect)
{
	CTextBox	*aBox = new CTextBox(&inRect, m_CompanyName, eCaptionFont, DT_CENTER);
	aBox->SetDocPtr(this);
	m_ReportItems.Add(aBox);

}

/*****************************************************************
 * 
 * method :void	CEasyReport::WriteReportFooter(CRect inRect)
 *
 * parameters : 
 *
 * returns : 
 *
 * description: Write the report footer. The default Report footer
 * is blank.
 *
 *
 ****************************************************************/
void	CEasyReport::WriteReportFooter(CRect inRect)
{
//	CTextBox	*aBox = new CTextBox(&inRect, "Report Footer", eCaptionFont);
//	aBox->SetDocPtr(this);
//	m_ReportItems.Add(aBox);
}

/*****************************************************************
 * 
 * method :void		WritePageHeader(CRect inRect)
 *
 * parameters : 
 *
 * returns : 
 *
 * description: Write the default page header. By default, this
 * contains the report title (centered) and date field, 
 * right aligned
 *
 ****************************************************************/
void	CEasyReport::WritePageHeader(CRect inRect)
{
	CRect		aRect(inRect);
	CTextBox	*aBox;

	aRect.bottom = aRect.top + GetHeadingFontSize().cy;
	aBox = new CTextBox(&aRect,m_ReportTitle,eColHeadingFont);
	aBox->SetDocPtr(this);
	m_ReportItems.Add(aBox);

	// make a text area 1/4 of the page width
	aRect.right = inRect.right;
	aRect.left = inRect.right - inRect.Width()/4;
	aBox = new CTextBox(&aRect, m_ReportDate, eColHeadingFont, DT_LEFT);
	aBox->SetDocPtr(this);
	m_ReportItems.Add(aBox);

	aRect.top = inRect.bottom-10;	// 1mm from the bottom
	aRect.bottom = inRect.bottom;
	aRect.left = inRect.left;
	aRect.right = inRect.right;
	CHline	*aLine = new CHline(&aRect,0);
	aLine->SetDocPtr(this);
	m_ReportItems.Add(aLine);
}

/*****************************************************************
 * 
 * method :void	CEasyReport::WritePageFooter(CRect inRect)
 *
 * parameters : 
 *
 * returns : 
 *
 * description: Write the page footer
 *
 ****************************************************************/
void	CEasyReport::WritePageFooter(CRect inRect)
{
	CRect	aRect(inRect);

	aRect.top = aRect.bottom = inRect.top +10;	// 1mm below 
	CHline	*aLine = new CHline(&aRect,0);
	aLine->SetDocPtr(this);
	m_ReportItems.Add(aLine);

	aRect.top += 10;	// 1mm
	aRect.bottom = aRect.top + GetHeadingFontSize().cy;
	CPageNum	*aPgNumField = new CPageNum(&aRect,eColHeadingFont);
	aPgNumField->SetDocPtr(this);
	m_ReportItems.Add(aPgNumField);
}



/*****************************************************************
 * 
 * method :void		DrawCurrentPage(CDC *inDC)
 *
 * parameters : inCDC a device context
 *
 * returns : nothing
 *
 * description: Draw the current page
 *
 *
 ****************************************************************/
void		CEasyReport::DrawCurrentPage(CDC *inDC)
{
	int			i,aStart, aMax;
	CElement	*aElem;
	
	if( m_CurPage != 0 )
		aStart = m_PageItems[m_CurPage-1];
	else
		aStart = 0;
	aMax = m_PageItems[m_CurPage];
	for( i =aStart;i< aMax;i++)
	{
		aElem = (CElement *)m_ReportItems[i];
		aElem->Draw(inDC);
	}


/*	
	CRect	aRect(m_LeftMargin, -m_TopMargin, 
				m_PageWidth - m_RightMargin, -(m_PageHeight-m_BottomMargin));
	inDC->MoveTo(aRect.left, aRect.top);
	inDC->LineTo(aRect.right,aRect.top);
	inDC->LineTo(aRect.right, aRect.bottom);
	inDC->LineTo(aRect.left, aRect.bottom);
	inDC->LineTo(aRect.left, aRect.top);
*/	
}


/*****************************************************************
 * 
 * method :const CFont	*GetStyle(int inStyleIndex)
 *
 * parameters : inStyleIndex: integer 
 *
 * returns : CFont *
 *
 * description: Return a pointer to the font, NULL if the index
 * is out of range.
 *
 *
 ****************************************************************/
const CFont	*CEasyReport::GetStyle(int inStyleIndex)
{
	ASSERT(inStyleIndex >=0 && inStyleIndex < eMaxStyles );
	if( inStyleIndex < eMaxStyles )
		return m_Fonts[ inStyleIndex ];
	else
		return NULL;
}



//**** end of EasyReport.cpp
