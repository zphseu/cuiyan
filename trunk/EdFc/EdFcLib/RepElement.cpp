/*******************************************************************************
 * CElement.cpp: implementation of the report item classes.
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
 *******************************************************************************/

#include "stdafx.h"
#include "EasyReport.h"
#include "RepElement.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CElement
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL( CElement, CObject,1)
void	CElement::Serialize(CArchive & ar)
{
	if( ar.IsStoring())
		ar << m_Frame;
	else
		ar >> m_Frame;
}


CElement::CElement()
{
	m_Frame.SetRect(0,0,0,0);
	m_DocPtr = NULL;
}

CElement::CElement(CRect *inFrame)
:m_Frame(inFrame)
{
	m_DocPtr = NULL;
}

CElement::~CElement()
{
}

void	CElement::Draw(CDC *inDC)
{
	ASSERT( m_DocPtr != NULL);
	inDC->TextOut(0,0,_T("Must override draw method in derived classes"));
}



//////////////////////////////////////////////////////////////////////
// CTextBox
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CTextBox, CElement,1)
void	CTextBox::Serialize(CArchive & ar)
{
	if( ar.IsStoring())
	{
		ar << m_Text;
		ar << m_FontIndex;
	}
	else
	{
		ar >> m_Text;
		ar >> m_FontIndex;
	}
}

CTextBox::CTextBox()
{
	m_FontIndex = -1;
	m_Align = DT_LEFT;
}

CTextBox::~CTextBox()
{
}


void	CTextBox::Draw(CDC *inDC)
{
	ASSERT( m_DocPtr != NULL);
	ASSERT( m_FontIndex != -1);
	CRect	aTemp(m_Frame);
	aTemp.top = -aTemp.top;
	aTemp.bottom = -aTemp.bottom;
	inDC->SelectObject( (CFont *)m_DocPtr->GetStyle( m_FontIndex) );
	//inDC->Rectangle(&aTemp);
	inDC->DrawText(m_Text, aTemp, m_Align);
}



//////////////////////////////////////////////////////////////////////
// CPageNum
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CPageNum, CElement,1)
void	CPageNum::Serialize(CArchive & ar)
{
}

CPageNum::CPageNum()
{
}

CPageNum::~CPageNum()
{
}


void	CPageNum::Draw(CDC *inDC)
{
	m_Text.Format("Page: %d of %d",m_DocPtr->GetCurPage()+1, m_DocPtr->GetPageCount());
	CTextBox::Draw(inDC);
}


//////////////////////////////////////////////////////////////////////
// CHline
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CHline, CElement,1);

void	CHline::Serialize(CArchive & ar)
{
	CElement::Serialize(ar);
	if( ar.IsStoring())
		ar << m_PenStyle;
	else
		ar >> m_PenStyle;
}


CHline::CHline()
{
	m_PenStyle = -1;
}

CHline::~CHline()
{
}


void	CHline::Draw(CDC *inDC)
{
	ASSERT( m_DocPtr != NULL);
	ASSERT( m_PenStyle != -1);
	inDC->SelectObject( (CPen *)m_DocPtr->GetPen( m_PenStyle ) );
	inDC->MoveTo( m_Frame.left, -m_Frame.top);
	inDC->LineTo( m_Frame.right, -m_Frame.top);
}



