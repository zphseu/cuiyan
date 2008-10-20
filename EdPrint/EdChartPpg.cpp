// ChartPpg.cpp : Implementation of the CEdChartPropPage property page class.

#include "stdafx.h"
#include "EdPrint.h"
#include "EdChartPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CEdChartPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CEdChartPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CEdChartPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CEdChartPropPage, "EdPrint.ChartPropPage.1",
	0x771cd4f7, 0xc4f0, 0x470b, 0x94, 0x5e, 0x6, 0xd3, 0x88, 0x78, 0x60, 0x21)


/////////////////////////////////////////////////////////////////////////////
// CEdChartPropPage::CEdChartPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CEdChartPropPage

BOOL CEdChartPropPage::CEdChartPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_EDCHART_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CEdChartPropPage::CEdChartPropPage - Constructor

CEdChartPropPage::CEdChartPropPage() :
	COlePropertyPage(IDD, IDS_EDCHART_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CEdChartPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CEdChartPropPage::DoDataExchange - Moves data between page and properties

void CEdChartPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CEdChartPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CEdChartPropPage message handlers
