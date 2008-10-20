// PtEmtHsCtl.cpp : Implementation of the CPtEmtHsCtrl ActiveX Control class.

#include "stdafx.h"
#include "PtEmt.h"
#include "PtEmtHsCtl.h"
#include "PtEmtHsPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPtEmtHsCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPtEmtHsCtrl, COleControl)
	//{{AFX_MSG_MAP(CPtEmtHsCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CPtEmtHsCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CPtEmtHsCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CPtEmtHsCtrl, COleControl)
	//{{AFX_EVENT_MAP(CPtEmtHsCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CPtEmtHsCtrl, 1)
	PROPPAGEID(CPtEmtHsPropPage::guid)
END_PROPPAGEIDS(CPtEmtHsCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPtEmtHsCtrl, "PTEMT.PtEmtHsCtrl.1",
	0xc138f85, 0x8086, 0x444d, 0x86, 0xfa, 0xa9, 0x37, 0x15, 0x78, 0x6b, 0xfa)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CPtEmtHsCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DPtEmtHs =
		{ 0x1decb36a, 0x9ef3, 0x4771, { 0x8d, 0x27, 0xa1, 0x69, 0xc6, 0x90, 0, 0x47 } };
const IID BASED_CODE IID_DPtEmtHsEvents =
		{ 0xb1bc8f15, 0xb3b1, 0x436b, { 0x8a, 0x50, 0x5a, 0xb6, 0xf2, 0xf6, 0x24, 0x6a } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwPtEmtHsOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CPtEmtHsCtrl, IDS_PTEMTHS, _dwPtEmtHsOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsCtrl::CPtEmtHsCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CPtEmtHsCtrl

BOOL CPtEmtHsCtrl::CPtEmtHsCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_PTEMTHS,
			IDB_PTEMTHS,
			afxRegApartmentThreading,
			_dwPtEmtHsOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsCtrl::CPtEmtHsCtrl - Constructor

CPtEmtHsCtrl::CPtEmtHsCtrl()
{
	InitializeIIDs(&IID_DPtEmtHs, &IID_DPtEmtHsEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsCtrl::~CPtEmtHsCtrl - Destructor

CPtEmtHsCtrl::~CPtEmtHsCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsCtrl::OnDraw - Drawing function

void CPtEmtHsCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsCtrl::DoPropExchange - Persistence support

void CPtEmtHsCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsCtrl::OnResetState - Reset control to default state

void CPtEmtHsCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHsCtrl message handlers
