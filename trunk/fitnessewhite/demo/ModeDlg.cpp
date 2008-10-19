// ModeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "controls_demo.h"
#include "ModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModeDlg dialog


CModeDlg::CModeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModeDlg, CDialog)
	//{{AFX_MSG_MAP(CModeDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModeDlg message handlers
