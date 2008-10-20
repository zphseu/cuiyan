// PtEmtHmCtl.cpp : Implementation of the CPtEmtHmCtrl ActiveX Control class.

#include "stdafx.h"
#include "PtEmt.h"
#include "PtEmtHmCtl.h"
#include "PtEmtHmPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPtEmtHmCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPtEmtHmCtrl, COleControl)
	//{{AFX_MSG_MAP(CPtEmtHmCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CPtEmtHmCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CPtEmtHmCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CPtEmtHmCtrl, COleControl)
	//{{AFX_EVENT_MAP(CPtEmtHmCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CPtEmtHmCtrl, 1)
	PROPPAGEID(CPtEmtHmPropPage::guid)
END_PROPPAGEIDS(CPtEmtHmCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPtEmtHmCtrl, "PTEMT.PtEmtHmCtrl.1",
	0x36bb9469, 0xb6bd, 0x4acf, 0xa4, 0xe, 0xb0, 0x9a, 0x7, 0x20, 0xe6, 0x7a)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CPtEmtHmCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DPtEmtHm =
		{ 0x3cfc25e5, 0x30d0, 0x4074, { 0xa9, 0x2f, 0x60, 0xa1, 0x7b, 0x1a, 0xb2, 0xa2 } };
const IID BASED_CODE IID_DPtEmtHmEvents =
		{ 0x1893a6c4, 0xc79d, 0x4196, { 0xaf, 0x5f, 0x56, 0xd, 0xe3, 0x9d, 0x49, 0xec } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwPtEmtHmOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CPtEmtHmCtrl, IDS_PTEMTHM, _dwPtEmtHmOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmCtrl::CPtEmtHmCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CPtEmtHmCtrl

BOOL CPtEmtHmCtrl::CPtEmtHmCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_PTEMTHM,
			IDB_PTEMTHM,
			afxRegApartmentThreading,
			_dwPtEmtHmOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmCtrl::CPtEmtHmCtrl - Constructor

CPtEmtHmCtrl::CPtEmtHmCtrl()
{
	InitializeIIDs(&IID_DPtEmtHm, &IID_DPtEmtHmEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmCtrl::~CPtEmtHmCtrl - Destructor

CPtEmtHmCtrl::~CPtEmtHmCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmCtrl::OnDraw - Drawing function

void CPtEmtHmCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmCtrl::DoPropExchange - Persistence support

void CPtEmtHmCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmCtrl::OnResetState - Reset control to default state

void CPtEmtHmCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtHmCtrl message handlers
