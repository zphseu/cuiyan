// PtEmtHsPpg.cpp : Implementation of the CPtEmtHsPropPage property page class.

#include "stdafx.h"
#include "PtEmt.h"
#include "PtEmtHsPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPtEmtHsPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPtEmtHsPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CPtEmtHsPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPtEmtHsPropPage, "PTEMT.PtEmtHsPropPage.1",
	0x3c960158, 0xaa25, 0x469c, 0x83, 0xc5, 0x7c, 0xc0, 0xa2, 0xd, 0xdb, 0x33)


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsPropPage::CPtEmtHsPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CPtEmtHsPropPage

BOOL CPtEmtHsPropPage::CPtEmtHsPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_PTEMTHS_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsPropPage::CPtEmtHsPropPage - Constructor

CPtEmtHsPropPage::CPtEmtHsPropPage() :
	COlePropertyPage(IDD, IDS_PTEMTHS_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CPtEmtHsPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsPropPage::DoDataExchange - Moves data between page and properties

void CPtEmtHsPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CPtEmtHsPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsPropPage message handlers
