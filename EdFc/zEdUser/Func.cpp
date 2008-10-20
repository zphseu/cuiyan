// Func.cpp: implementation of the CFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Func.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void CFunc::SetColumnList(CListCtrl &lstCtrl, LPSTR *szCaption, int *nCaption)
{
	lstCtrl.SetExtendedStyle( lstCtrl.GetExtendedStyle()
		| LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );
	
	LV_COLUMN Column;
	Column.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	Column.fmt = LVCFMT_LEFT;
	
	CRect rt;
	lstCtrl.GetClientRect(&rt);
	nCaption[0] = rt.Width() / nCaption[0];
	int nw = 0;
	for (int i = 0; szCaption[i]; i++)
	{
		Column.cx = nCaption[0] * nCaption[i+1];
		nw += Column.cx;
		Column.pszText = szCaption[i];
		lstCtrl.InsertColumn(i, &Column);
	}
	lstCtrl.SetColumnWidth(i - 1, Column.cx + rt.Width() - nw);
}
