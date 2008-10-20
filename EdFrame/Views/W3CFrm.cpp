// W3CFrm.cpp : implementation of the CW3CFrame class
//

#include "stdafx.h"
#include "W3CFrm.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CW3CFrame

IMPLEMENT_DYNCREATE(CW3CFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CW3CFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CW3CFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CW3CFrame construction/destruction

CW3CFrame::CW3CFrame()
{
}

CW3CFrame::~CW3CFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
// CW3CFrame diagnostics

#ifdef _DEBUG
void CW3CFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CW3CFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);    
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CW3CFrame message handlers

int CW3CFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE |CBRS_TOP|CBRS_GRIPPER
		|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_W3CTYPE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	MakeToolbarImageList(IDR_W3CTYPE, m_ToolbarImages);
	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ToolbarImages);
	
	//add your toolbar here
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	
	return 0;
}

void CW3CFrame::MakeToolbarImageList(UINT inBitmapID, CImageList &imglst)
{
	CBitmap	bm;
	
	VERIFY (bm.Attach (::LoadImage (::AfxFindResourceHandle(
		MAKEINTRESOURCE (inBitmapID), RT_BITMAP),
		MAKEINTRESOURCE (inBitmapID), IMAGE_BITMAP, 0, 0,
		(LR_DEFAULTSIZE | LR_CREATEDIBSECTION))));
	
	// figure out how many pixels there are in the bitmap
	BITMAP		bmInfo;
	VERIFY (bm.GetBitmap (&bmInfo));
	
	ReplaceBackgroundColor(bm);
	
	VERIFY (imglst.Create (bmInfo.bmHeight, bmInfo.bmHeight, 
		bmInfo.bmBitsPixel, bmInfo.bmWidth / bmInfo.bmHeight, 0));
	
	// attach the bitmap to the image list
	VERIFY (imglst.Add (&bm, RGB (0, 0, 0)) != -1);
}

void CW3CFrame::ReplaceBackgroundColor(CBitmap &bm)
{
	BITMAP		bmInfo;
	VERIFY (bm.GetBitmap (&bmInfo));
	
	const UINT numPixels (bmInfo.bmHeight * bmInfo.bmWidth);
	const COLORREF	buttonColor (::GetSysColor (COLOR_BTNFACE));
	
	DIBSECTION  ds;
	VERIFY (bm.GetObject (sizeof (DIBSECTION), &ds) == sizeof (DIBSECTION));
	
	switch (bmInfo.bmBitsPixel)
	{
	case 8:
		{
			TCHAR userBackgroundColor = TCHAR(77);
			
			VERIFY (bmInfo.bmWidthBytes == bmInfo.bmWidth);
			TCHAR*	pixels = reinterpret_cast<TCHAR*>(ds.dsBm.bmBits);
			VERIFY (pixels != NULL);
			for (UINT i = 1; i < numPixels; ++i)
			{
				if (pixels [i] == pixels [0])
				{
					pixels [i] = userBackgroundColor;
				}
			}
			pixels[0] = userBackgroundColor;
		}
		break;
		
	case 24:
		{
			VERIFY (bmInfo.bmWidthBytes == (bmInfo.bmWidth * 3));
			RGBTRIPLE*	pixels = reinterpret_cast<RGBTRIPLE*>(ds.dsBm.bmBits);
			VERIFY (pixels != NULL);
			// get the user's preferred button color from the system
			const RGBTRIPLE	userBackgroundColor = {
				GetBValue (buttonColor), 
					GetGValue (buttonColor), 
					GetRValue (buttonColor)
			};
			for (UINT i = 1; i < numPixels; ++i)
			{
				if (pixels [i].rgbtBlue == pixels [0].rgbtBlue &&
					pixels [i].rgbtGreen == pixels [0].rgbtGreen &&
					pixels [i].rgbtRed == pixels [0].rgbtRed)
				{
					pixels [i] = userBackgroundColor;
				}
			}
			pixels[0] = userBackgroundColor;
		}
		break;
		
	default:
		break;
	}
}

void CW3CFrame::ActivateFrame(int nCmdShow) 
{
	if (nCmdShow == -1) 
		nCmdShow = SW_SHOWMAXIMIZED; 	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}
