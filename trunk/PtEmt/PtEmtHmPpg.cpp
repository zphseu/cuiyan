// PtEmtHmPpg.cpp : Implementation of the CPtEmtHmPropPage property page class.

#include "stdafx.h"
#include "PtEmt.h"
#include "PtEmtHmPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPtEmtHmPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPtEmtHmPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CPtEmtHmPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPtEmtHmPropPage, "PTEMT.PtEmtHmPropPage.1",
	0x94789765, 0xb380, 0x43ad, 0x8c, 0xff, 0x56, 0xf2, 0xf6, 0xcf, 0x3e, 0xbe)


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmPropPage::CPtEmtHmPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CPtEmtHmPropPage

BOOL CPtEmtHmPropPage::CPtEmtHmPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_PTEMTHM_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmPropPage::CPtEmtHmPropPage - Constructor

CPtEmtHmPropPage::CPtEmtHmPropPage() :
	COlePropertyPage(IDD, IDS_PTEMTHM_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CPtEmtHmPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmPropPage::DoDataExchange - Moves data between page and properties

void CPtEmtHmPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CPtEmtHmPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmPropPage message handlers
