// PtEmtDytPpg.cpp : Implementation of the CPtEmtDytPropPage property page class.

#include "stdafx.h"
#include "PtEmt.h"
#include "PtEmtDytPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPtEmtDytPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPtEmtDytPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CPtEmtDytPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPtEmtDytPropPage, "PTEMT.PtEmtDytPropPage.1",
	0x93b155f3, 0xb6ed, 0x4d9c, 0x8e, 0x96, 0x4d, 0x9, 0xb9, 0x85, 0x6d, 0x1a)


/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytPropPage::CPtEmtDytPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CPtEmtDytPropPage

BOOL CPtEmtDytPropPage::CPtEmtDytPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_PTEMTDYT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytPropPage::CPtEmtDytPropPage - Constructor

CPtEmtDytPropPage::CPtEmtDytPropPage() :
	COlePropertyPage(IDD, IDS_PTEMTDYT_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CPtEmtDytPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytPropPage::DoDataExchange - Moves data between page and properties

void CPtEmtDytPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CPtEmtDytPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytPropPage message handlers
