// STabDialog.cpp: implementation of the CSTabDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "STabDialog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//##ModelId=3F6E58AE01EF
CSTabDialog::CSTabDialog(UINT nIDTemplate, CWnd* pParentWnd) 
  : CDialog(nIDTemplate, pParentWnd), m_csTitle(_T("请在构造函数中修改标题")), m_nIDD(nIDTemplate)
{
}

//##ModelId=3F6E58AE01F0
CSTabDialog::~CSTabDialog()
{

}


BEGIN_MESSAGE_MAP(CSTabDialog, CDialog)
	//{{AFX_MSG_MAP(CSTabDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//##ModelId=3F6E5D4803D3
BOOL CSTabDialog::Create(CWnd *pParentWnd)
{
	return CDialog::Create(IDD, pParentWnd);
}
