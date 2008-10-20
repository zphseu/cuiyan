// GridPpg.cpp : Implementation of the CEdGridPropPage property page class.

#include "stdafx.h"
#include "EdPrint.h"
#include "EdGridPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CEdGridPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CEdGridPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CEdGridPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CEdGridPropPage, "EdPrint.EdGridPropPage.1",
	0x9cfe6cce, 0xbbb, 0x4537, 0x88, 0x8c, 0x17, 0x97, 0x1a, 0xb2, 0xd9, 0xe9)


/////////////////////////////////////////////////////////////////////////////
// CEdGridPropPage::CEdGridPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CEdGridPropPage

BOOL CEdGridPropPage::CEdGridPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_EDGRID_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CEdGridPropPage::CEdGridPropPage - Constructor

CEdGridPropPage::CEdGridPropPage() :
	COlePropertyPage(IDD, IDS_EDGRID_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CEdGridPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CEdGridPropPage::DoDataExchange - Moves data between page and properties

void CEdGridPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CEdGridPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CEdGridPropPage message handlers
