// DlgUsrCfg.cpp : implementation file
//

#include "stdafx.h"
#include "SetGrp.h"
#include "DlgUsrCfg.h"
#include "EdMod1Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" CDatabase* GetDB();
extern CEdMod1Ini g_ini;

/////////////////////////////////////////////////////////////////////////////
// CDlgUsrCfg dialog

CDlgUsrCfg::CDlgUsrCfg(CWnd* pParent /*=NULL*/)
	: CSTabDialog(CDlgUsrCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUsrCfg)
	//}}AFX_DATA_INIT
	m_nCurSel = 0;
	m_csTitle = _T("È¨ÏÞ·ÖÅä");
}

void CDlgUsrCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUsrCfg)
	DDX_Control(pDX, IDC_OUTUSR, m_outUsrCtrl);
	DDX_Control(pDX, IDC_INUSR, m_inUsrCtrl);
	DDX_Control(pDX, IDC_OUTRES, m_outResCtrl);
	DDX_Control(pDX, IDC_INRES, m_inResCtrl);
	DDX_Control(pDX, IDC_GRP, m_cbCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUsrCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgUsrCfg)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_USRTO, OnUsrto)
	ON_BN_CLICKED(IDC_USROUT, OnUsrout)
	ON_BN_CLICKED(IDC_RESTO, OnResto)
	ON_BN_CLICKED(IDC_RESOUT, OnResout)
	ON_CBN_SELCHANGE(IDC_GRP, OnSelchangeGrp)
	ON_LBN_DBLCLK(IDC_INRES, OnDblclkInres)
	ON_LBN_DBLCLK(IDC_INUSR, OnDblclkInusr)
	ON_LBN_DBLCLK(IDC_OUTRES, OnDblclkOutres)
	ON_LBN_DBLCLK(IDC_OUTUSR, OnDblclkOutusr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUsrCfg message handlers

BOOL CDlgUsrCfg::LoadData()
{
	BOOL bRet = FALSE;
	
	try
	{		
#define CLEAN_CTRL(Ctrl)  while (Ctrl.GetCount() > 0)  Ctrl.DeleteString(0)
		CLEAN_CTRL(m_cbCtrl);
		CLEAN_CTRL(m_inResCtrl);
		CLEAN_CTRL(m_outResCtrl);
		CLEAN_CTRL(m_inUsrCtrl);
		CLEAN_CTRL(m_outUsrCtrl);

		CString csTmp, csCurGrp;
		// get group names
		{
			CSetGrp rs(GetDB());
			rs.Open(rs.forwardOnly);
			while (!rs.IsEOF())
			{
				rs.GetFieldValue(short(0), csTmp);
				m_cbCtrl.AddString(csTmp);
				rs.MoveNext();
			}
			rs.Close();

			if (m_cbCtrl.GetCount() < 1)
				throw -1;
			else
			{
				m_cbCtrl.SetCurSel(m_nCurSel);
				m_cbCtrl.GetLBText(m_nCurSel, csCurGrp);
			}
		}
		
		// get Usr names
		{
			CRecordset rs(GetDB());
			CString csSql;
			csSql.Format("SELECT AB FROM ZED004 WHERE AA='%s'", csCurGrp);
			rs.Open(rs.forwardOnly, csSql);
			while (!rs.IsEOF())
			{
				rs.GetFieldValue(short(0), csTmp);
				m_inUsrCtrl.AddString(csTmp);
				rs.MoveNext();
			}
			rs.Close();

			rs.Open(rs.forwardOnly, "SELECT DISTINCT AA FROM ZED001");
			while (!rs.IsEOF()) 
			{
				rs.GetFieldValue(short(0), csTmp);
				if (m_inUsrCtrl.FindString(0, csTmp) == LB_ERR)
					m_outUsrCtrl.AddString(csTmp);
				rs.MoveNext();
			}
			rs.Close();
		}

		// get Res names
		{
			CRecordset rs(GetDB());
			CString csSql;
			csSql.Format("SELECT AB FROM ZED003 WHERE AA='%s'", csCurGrp);
			rs.Open(rs.forwardOnly, csSql);
			while (!rs.IsEOF())
			{
				rs.GetFieldValue(short(0), csTmp);
				m_inResCtrl.AddString(csTmp);
				rs.MoveNext();
			}
			rs.Close();
			
			rs.Open(rs.forwardOnly, "SELECT DISTINCT AA FROM ZED000");
			while (!rs.IsEOF()) 
			{
				rs.GetFieldValue(short(0), csTmp);
				if (m_inResCtrl.FindString(0, csTmp) == LB_ERR)
					m_outResCtrl.AddString(csTmp);
				rs.MoveNext();
			}
			rs.Close();			
		}
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
	}
	catch (...) 
	{
	}
	
//	RedrawWindow();
	return bRet;
}

void CDlgUsrCfg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (bShow)
		LoadData();	
}

#include "SetGrpUsr.h"
void CDlgUsrCfg::OnUsrto() 
{
	int nList = m_outUsrCtrl.GetCurSel();
	int nCb = m_cbCtrl.GetCurSel();
	if (nList == LB_ERR || nCb == CB_ERR )
		return;

	CString csUsr, csGrp;
	m_outUsrCtrl.GetText(nList, csUsr);
	m_cbCtrl.GetLBText(nCb, csGrp);

	CSetGrpUsr rs(GetDB());

	try
	{
		rs.Open();
		rs.AddNew();
		rs.m_csGrp = csGrp;
		rs.m_csUsr = csUsr;
		rs.Update();
		LoadData();
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
	}
	
	rs.Close();
	return;
}

void CDlgUsrCfg::OnUsrout() 
{
	int nList = m_inUsrCtrl.GetCurSel();
	int nCb = m_cbCtrl.GetCurSel();
	if (nList == LB_ERR || nCb == CB_ERR )
		return;
	
	CString csUsr, csGrp;
	m_inUsrCtrl.GetText(nList, csUsr);
	m_cbCtrl.GetLBText(nCb, csGrp);
	
	CSetGrpUsr rs(GetDB());

	try
	{
		rs.m_strFilter.Format("AA='%s' AND AB='%s'", csGrp, csUsr);
		rs.Open();
		if (!rs.IsEOF())
		{
			rs.Delete();
			LoadData();
		}
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
	}
	
	rs.Close();
	return;
}

#include "SetGrpRes.h"
void CDlgUsrCfg::OnResto() 
{
	int nList = m_outResCtrl.GetCurSel();
	int nCb = m_cbCtrl.GetCurSel();
	if (nList == LB_ERR || nCb == CB_ERR )
		return;
	
	CString csRes, csGrp;
	m_outResCtrl.GetText(nList, csRes);
	m_cbCtrl.GetLBText(nCb, csGrp);
	
	CSetGrpRes rs(GetDB());
	
	try
	{
		rs.Open();
		rs.AddNew();
		rs.m_csGrp = csGrp;
		rs.m_csRes = csRes;
		rs.Update();
		LoadData();
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
	}
	
	rs.Close();
	return;	
}

void CDlgUsrCfg::OnResout() 
{
	int nList = m_inResCtrl.GetCurSel();
	int nCb = m_cbCtrl.GetCurSel();
	if (nList == LB_ERR || nCb == CB_ERR )
		return;
	
	CString csRes, csGrp;
	m_inResCtrl.GetText(nList, csRes);
	m_cbCtrl.GetLBText(nCb, csGrp);
	
	CSetGrpRes rs(GetDB());
	
	try
	{
		rs.m_strFilter.Format("AA='%s' AND AB='%s'", csGrp, csRes);
		rs.Open();
		if (!rs.IsEOF())
		{
			rs.Delete();
			LoadData();
		}
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
	}
	
	rs.Close();
	return;
}

void CDlgUsrCfg::OnSelchangeGrp() 
{
	m_nCurSel = m_cbCtrl.GetCurSel();
	LoadData();
}

void CDlgUsrCfg::OnDblclkInres() 
{
	OnResout();
}

void CDlgUsrCfg::OnDblclkInusr() 
{
	OnUsrout();
}

void CDlgUsrCfg::OnDblclkOutres() 
{
	OnResto();
}

void CDlgUsrCfg::OnDblclkOutusr() 
{
	OnUsrto();
}

BOOL CDlgUsrCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (g_ini.GetVisable(4))
	{
		m_inResCtrl.ShowWindow(SW_HIDE);
		m_outResCtrl.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESTO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESOUT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
	}
	
	return TRUE;
}
