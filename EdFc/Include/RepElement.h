

/*******************************************************************************
 * RepElement.h: interface for the CElement class.
 *
 * MFC Quick! report class
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
 * For use with RTElement.h v1.00
 *
 *******************************************************************************/



#if !defined(_REPELEMENT_H_B1A00117_DB1B_4E6F_832F_D1394FCF5CF6)
#define _REPELEMENT_H_B1A00117_DB1B_4E6F_832F_D1394FCF5CF6

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/***********************************************************************
 *
 * CElement class encapsulates the functionality required for an 
 * element in a report. 
 *
 **********************************************************************/
class CElement : public CObject  
{
		DECLARE_SERIAL( CElement )
		virtual void Serialize(CArchive & ar);
	protected:
		CEasyReport	*m_DocPtr;	// ptr to the document
		CRect		m_Frame;	// frame within which we have to draw
		CElement();
	public:
		CElement(CRect *inFrame);
		virtual ~CElement();
		virtual	void	SetDocPtr(CEasyReport *inDoc)
		{
			m_DocPtr = inDoc;
		}
		virtual	void	Draw(CDC *inDC);
};


/***********************************************************************
 *
 * CTextBox class is a text element in the report
 *
 **********************************************************************/
class CTextBox : public CElement
{
		DECLARE_SERIAL( CTextBox )
		virtual void Serialize(CArchive & ar);
	protected:
		CTextBox();	// default constructor is protected and used only while seralizing
		int			m_FontIndex;
		CString		m_Text;
		int			m_Align;
	public:
		CTextBox( CRect *inRect, const char *inStr, int inFontIndex, int inAlign = DT_LEFT )
		: CElement(inRect), m_Text(inStr), m_FontIndex(inFontIndex)
		{
			m_Align = inAlign;
		}
		virtual ~CTextBox();
		void	SetAlign(int inAlign)	{ m_Align = inAlign;}
		virtual	void	Draw(CDC *inDC);
};


/***********************************************************************
 *
 * CPageNum class is a page number field in the report
 *
 **********************************************************************/
class CPageNum : public CTextBox
{
		DECLARE_SERIAL( CPageNum )
		virtual void Serialize(CArchive & ar);
	protected:
		CPageNum();	// default constructor is protected and used only while seralizing
	public:
		CPageNum( CRect *inRect, int inFontIndex, int inAlign = DT_CENTER )
		: CTextBox(inRect, "", inFontIndex, inAlign )
		{
		}
		virtual ~CPageNum();
		virtual	void	Draw(CDC *inDC);
};


/***********************************************************************
 *
 * CHline class is a horizontal line on the report
 *
 **********************************************************************/
class CHline : public CElement
{
		DECLARE_SERIAL( CHline )
		virtual void Serialize(CArchive & ar);
	protected:
		CHline();	// default constructor is protected and used only while seralizing
		int			m_PenStyle;
	public:
		CHline( CRect *inRect, int inStyle )
		: CElement(inRect),
		m_PenStyle(inStyle)
		{
		}

		virtual ~CHline();
		virtual	void	Draw(CDC *inDC);
};

#endif // !defined(_REPELEMENT_H_B1A00117_DB1B_4E6F_832F_D1394FCF5CF6)

