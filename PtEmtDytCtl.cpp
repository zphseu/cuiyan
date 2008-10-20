// PtEmtDytCtl.cpp : Implementation of the CPtEmtDytCtrl ActiveX Control class.

#include "stdafx.h"
#include "PtEmt.h"
#include "PtEmtDytCtl.h"
#include "PtEmtDytPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CONST static SHORT		lColorNum = 16;	
CONST static COLORREF	lColorEnd = 0x0101;
CONST static COLORREF	lColorBegin = 0xFF0000;

CONST static FLOAT PIE = 3.1415926535898f;
CONST static FLOAT PipeRadius = 0.035f;		//radius of the pipe line
CONST static FLOAT DetectorRadius = 0.038422f;	//radius of the detector position
CONST static FLOAT ScreenRadius = 0.06f;		//radius of the screen wall
CONST static FLOAT DetectorAngle = 33.0f;		// the angle of the detector 

IMPLEMENT_DYNCREATE(CPtEmtDytCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPtEmtDytCtrl, COleControl)
	//{{AFX_MSG_MAP(CPtEmtDytCtrl)
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CPtEmtDytCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CPtEmtDytCtrl)
	DISP_FUNCTION(CPtEmtDytCtrl, "PFile2Picture", PFile2Picture, VT_I4, VTS_BSTR VTS_I2 VTS_I2 VTS_I2 VTS_R4 VTS_R4)
	DISP_FUNCTION(CPtEmtDytCtrl, "SavePicture", SavePicture, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CPtEmtDytCtrl, "FFile2Picture", FFile2Picture, VT_I4, VTS_BSTR VTS_I2 VTS_I2)
	DISP_FUNCTION(CPtEmtDytCtrl, "GFile2Picture", GFile2Picture, VT_I4, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CPtEmtDytCtrl, COleControl)
	//{{AFX_EVENT_MAP(CPtEmtDytCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CPtEmtDytCtrl, 1)
	PROPPAGEID(CPtEmtDytPropPage::guid)
END_PROPPAGEIDS(CPtEmtDytCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPtEmtDytCtrl, "PTEMT.PtEmtDytCtrl.1",
	0x11d06f82, 0x3393, 0x48c4, 0xb0, 0x45, 0x90, 0xdb, 0x5, 0xce, 0xae, 0xa8)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CPtEmtDytCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DPtEmtDyt =
		{ 0xac8b021b, 0xdb57, 0x48cf, { 0xbf, 0x71, 0x95, 0xaf, 0x43, 0xb8, 0xd3, 0xb } };
const IID BASED_CODE IID_DPtEmtDytEvents =
		{ 0xf993bcb8, 0x651a, 0x473f, { 0xb9, 0x79, 0x9a, 0x5c, 0x6e, 0x3d, 0x31, 0xb } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwPtEmtDytOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CPtEmtDytCtrl, IDS_PTEMTDYT, _dwPtEmtDytOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytCtrl::CPtEmtDytCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CPtEmtDytCtrl

BOOL CPtEmtDytCtrl::CPtEmtDytCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (TRUE == bRegister) {
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_PTEMTDYT,
			IDB_PTEMTDYT,
			afxRegApartmentThreading,
			_dwPtEmtDytOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	}	else	{
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytCtrl::CPtEmtDytCtrl - Constructor

CPtEmtDytCtrl::CPtEmtDytCtrl()
{
	InitializeIIDs(&IID_DPtEmtDyt, &IID_DPtEmtDytEvents);
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytCtrl::~CPtEmtDytCtrl - Destructor

CPtEmtDytCtrl::~CPtEmtDytCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytCtrl::OnDraw - Drawing function

void CPtEmtDytCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	pdc->FillRect(rcBounds.operator LPCRECT(), CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	if (FALSE == m_PtEmt.IsGrayOK())	{
		pdc->SetTextAlign(TA_CENTER|TA_BASELINE);
		CString pszText = _T("PtEmtDyt");
		pdc->TextOut(rcBounds.Width() / 2, rcBounds.Height() / 2, pszText);
	}	else	{
		CRect rect(rcBounds);

		FLOAT winDiameter = rect.Width() * 1.0f;
		
		if (rect.Width() > rect.Height()) {
			winDiameter = rect.Height() * 1.0f;
		}

		winDiameter *= 0.9f;
		const FLOAT Diameter = 0.13f;
		m_Scale = winDiameter /Diameter;
		m_Center = CPoint(rect.right / 2, rect.bottom / 2);
		
		FLOAT mingray(1e20f), maxgray(-1e20f);
		
		for(SHORT i = 0; i < TotalElement; i++)
		{
			maxgray = max(maxgray, m_PtEmt.GetMGray(i));
			mingray = min(mingray, m_PtEmt.GetMGray(i));
		}
		
		TEXTMETRIC tm;
		CString str;
		CRgn rgn;
		CBrush br;	
		pdc->GetTextMetrics(&tm);
		CPoint ColorBarPoint(10, int(m_Center.y * 2.0 / 3 + 10 * tm.tmHeight));
		for(i = 0; i < lColorNum ;i++)
		{
			CRect rt(ColorBarPoint.x, ColorBarPoint.y-tm.tmHeight,
				ColorBarPoint.x+20, ColorBarPoint.y);
			br.CreateSolidBrush(lColorBegin + lColorEnd * (lColorNum-i-1) * lColorNum);
			pdc->FillRect(rt.operator LPCRECT(), &br);
			FLOAT ruler = mingray + (maxgray-mingray)*FLOAT(i)/(lColorNum - 1);
			str.Format(_T("%e"), ruler);
			ColorBarPoint.y -= tm.tmHeight;
			pdc->TextOut(ColorBarPoint.x + 23, ColorBarPoint.y, str);
			br.DeleteObject();
		}
		
		// Draw Gray Picture
		for (i = 0 ; i < InsideElement; i++)
		{
			if (fabs(m_PtEmt.GetMGray(i)) > 0.000001) 
			{
				CPoint point[4];
				for(SHORT j = 0; j < 4; j++)	{
					point[j] = _PToL(m_PtEmt.GetNodes(i, j));
				}
				
				SHORT clrLevel = SHORT((lColorNum-1) * (m_PtEmt.GetMGray(i)-mingray) / (maxgray-mingray));
				rgn.CreatePolygonRgn(point,4, ALTERNATE); 
				br.CreateSolidBrush(lColorBegin + lColorEnd * (lColorNum-clrLevel-1) * lColorNum);
				pdc->FillRgn(&rgn, &br);
				br.DeleteObject();
				rgn.DeleteObject();
			}
		}
		
		for (i=0; i < DetectorNum; i++)
		{
			FLOAT startangle,stopangle;
			POINT startpoint,stoppoint;
			COMPLEX startnode,stopnode;
			int CurDR = int(DetectorRadius * m_Scale);
			
			startangle = FLOAT(PIE*(2*i+1)/DetectorNum-DetectorAngle/2.0*PIE/180.0);
			stopangle = FLOAT(startangle+DetectorAngle*PIE/180.0);		
			startnode = COMPLEX(DetectorRadius*cos(startangle), DetectorRadius*sin(startangle));
			stopnode = COMPLEX(DetectorRadius*cos(stopangle), DetectorRadius*sin(stopangle));
			startpoint = _PToL(startnode);
			stoppoint = _PToL(stopnode);
			pdc->Arc(m_Center.x-CurDR + 60,m_Center.y-CurDR,m_Center.x+CurDR + 60,m_Center.y+CurDR,
				startpoint.x,startpoint.y,stoppoint.x,stoppoint.y);
		}
		
		CPoint pul, plr, pst;
		pul = _PToL(COMPLEX(-PipeRadius, -PipeRadius));
		plr = _PToL(COMPLEX(PipeRadius, PipeRadius));
		pst = _PToL(COMPLEX(PipeRadius, 0.0));
		pdc->Arc(pul.x,pul.y,plr.x,plr.y,pst.x,pst.y,pst.x,pst.y);
		
		pul = _PToL(COMPLEX(-ScreenRadius, -ScreenRadius));
		plr = _PToL(COMPLEX(ScreenRadius, ScreenRadius));
		pst = _PToL(COMPLEX(ScreenRadius, 0.0));
		pdc->Arc(pul.x,pul.y,plr.x,plr.y,pst.x,pst.y,pst.x,pst.y);			
	}
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytCtrl::DoPropExchange - Persistence support

void CPtEmtDytCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytCtrl::OnResetState - Reset control to default state

void CPtEmtDytCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CPtEmtDytCtrl message handlers

long CPtEmtDytCtrl::PFile2Picture(LPCTSTR sPFileName, SHORT iType, SHORT iMethodType, SHORT dParam1, FLOAT dParam2, FLOAT dParam3) 
{
	if (FALSE == m_PtEmt.LoadPFile(sPFileName)) {
		return S_FALSE;
	}
	
	m_PtEmt.SetFieldType((FIELDTYPE)iType);
	switch(iMethodType) {
	case 0:	//LDWB
		m_PtEmt.LDWB(dParam1, (FLOAT)dParam2, (FLOAT)dParam3);
		break;
	case 1: //MNR
		m_PtEmt.MNR(dParam1, (FLOAT)dParam2, (FLOAT)dParam3);
		break;
	default: //LBP
		m_PtEmt.LBP();
	}
	
	Invalidate();
	return !m_PtEmt.IsGrayOK();	//成功返回零
}

long CPtEmtDytCtrl::SavePicture(LPCTSTR sPicFileName) 
{
	return 0;
}

long CPtEmtDytCtrl::FFile2Picture(LPCTSTR sFFileName, SHORT iType, SHORT iMethodType) 
{
	return 0;
}

long CPtEmtDytCtrl::GFile2Picture(LPCTSTR szFileName) 
{
	m_PtEmt.LoadGrayFile(szFileName);
	Invalidate();
	return !m_PtEmt.IsGrayOK();	//成功返回零
}

CPoint CPtEmtDytCtrl::_PToL(COMPLEX nd)
{
	return CPoint(int(m_Center.x + nd.real() * m_Scale +  60), 
		int(m_Center.y - nd.imag() * m_Scale));
}
