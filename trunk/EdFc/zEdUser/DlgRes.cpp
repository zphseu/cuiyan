// DlgRes.cpp : implementation file
//

#include "stdafx.h"
#include "DlgRes.h"
#include "Func.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern "C" CDatabase* GetDB();
/////////////////////////////////////////////////////////////////////////////
// CDlgRes dialog

CDlgRes::CDlgRes(CWnd* pParent /*=NULL*/)
	: CSTabDialog(CDlgRes::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRes)
	m_csCmt = _T("");
	m_csMod = _T("");
	m_csName = _T("");
	//}}AFX_DATA_INIT
	m_csTitle = _T("资源管理");
}

void CDlgRes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRes)
	DDX_Control(pDX, IDC_LIST, m_lstCtrl);
	DDX_Text(pDX, IDC_COMMENT, m_csCmt);
	DDX_Text(pDX, IDC_MODULE, m_csMod);
	DDX_Text(pDX, IDC_NAME, m_csName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRes, CDialog)
	//{{AFX_MSG_MAP(CDlgRes)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(ID_DEL, OnDel)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnclkList)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRes message handlers

void CDlgRes::OnSave() 
{
	UpdateData();
	if(!ValidateInput())
		return;
	CSetRes	rs(GetDB());
	try
	{
		rs.m_strFilter.Format("AA='%s'", m_csName);
		rs.Open();
		
		if (rs.IsEOF())
			rs.AddNew();
		else
			rs.Edit();
		
		*(tagRes*)&rs = *(tagRes*)this;
		rs.Update();
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
	}
	catch (...) 
	{
	}
	
	rs.Close();
	LoadData();
	return;	
}

void CDlgRes::OnDel() 
{
	UpdateData();
	
	if( (m_csName.GetLength()) > 32 || (m_csName.GetLength()) <1) 
	{
		MessageBox("资源名称长度必须在32字符之内且不能为空!","注意",MB_OK);
		GetDlgItem(IDC_NAME)->SetFocus();
		return ;
	}


	if(!IsNameExist(m_csName))
	{
		MessageBox("不存在该名称的资源，无法删除!", _T("信息"), MB_OK );
		return;
	}

	CString csTmp;
	csTmp.Format("确认删除资源：%s 吗？", m_csName);
	if (MessageBox(csTmp, _T("信息"), MB_YESNO ) == IDNO)
		return;

	CSetRes rs(GetDB());
	
	try
	{
		rs.m_strFilter.Format("AA='%s'", m_csName);
		rs.Open();
		
		if( rs.IsEOF( ) || !rs.CanUpdate( ))
			throw -1;
		
		rs.Delete( );
		
		//为了维护数据库的一致性,删除资源后,删除各群组中已登记的该资源记录
		csTmp.Format("DELETE FROM ZED003 WHERE AB='%s'",m_csName);
		GetDB()->ExecuteSQL(csTmp);	
		ResetInputCtrls();
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
	}
	catch (...) 
	{
	}
	
	rs.Close();
	LoadData();
	return;
}

void CDlgRes::OnclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nItem = m_lstCtrl.GetNextItem(-1, LVNI_SELECTED);
	*pResult = 0;	
	
	if ( nItem < 0 )
		return;
	
	CSetRes rs(GetDB());
	
	try
	{
		m_csName = m_lstCtrl.GetItemText(nItem, 0);
		rs.m_strFilter.Format("AA='%s'", m_csName);
		rs.Open();
		
		if (!rs.IsEOF())
		{
			*(tagRes*)this = (tagRes)rs;
			UpdateData(FALSE);
		}
		
		rs.Close();
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
	}
}

BOOL CDlgRes::LoadData()
{
	BOOL bRet = FALSE;
	CSetRes rs(GetDB());

	try
	{
		rs.Open();
		
		m_lstCtrl.DeleteAllItems();
		
		CString csTmp;
		LV_ITEM item_;
		item_.state = 0;
		item_.stateMask = 0;
		item_.iImage = 0;
		item_.iItem = 0;
		item_.iSubItem = 0;
		while (!rs.IsEOF())
		{
			m_lstCtrl.InsertItem(&item_);
			m_lstCtrl.SetItemText(item_.iItem, 0, rs.m_csName);
			m_lstCtrl.SetItemText(item_.iItem, 1, rs.m_csMod);
			m_lstCtrl.SetItemText(item_.iItem, 2, rs.m_csCmt);
			item_.iItem++;			
			rs.MoveNext();
		}
		
		bRet = TRUE;
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
	}
	catch (...) 
	{
	}
	
	rs.Close();

	return bRet;
}

BOOL CDlgRes::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LPSTR szCaption[] = {
		"名称", "模块", "备注", NULL
	};
	
	int nCaption[] = { 4, 1, 1, 2 };
	CFunc::SetColumnList(m_lstCtrl, szCaption, nCaption);

	return TRUE;
}

void CDlgRes::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (bShow)
		LoadData();
}

BOOL CDlgRes::ValidateInput()
{	
	UpdateData();
	if( (m_csName.GetLength()) > 32 || (m_csName.GetLength()) <1) 
	{
		MessageBox("资源名称长度必须在32字符之内且不能为空!","注意",MB_OK);
		GetDlgItem(IDC_NAME)->SetFocus();
		return FALSE;
	}

	if( (m_csMod.GetLength()) > 32 || (m_csMod.GetLength()) <1 )
	{
		MessageBox("模块名称长度必须在32字符之内且不能为空!","注意",MB_OK);
		GetDlgItem(IDC_MODULE)->SetFocus();
		return FALSE;
	}
	
	if( (m_csCmt.GetLength() > 255))
		m_csCmt = m_csCmt.Left(255);
	
	return TRUE;	
}

bool CDlgRes::IsNameExist(CString &strName)
{
	bool bExist=true;
	CSetRes rs(GetDB());
	try
	{
		rs.m_strFilter.Format("AA='%s'", strName);
		rs.Open();
		if( rs.IsEOF( ))
		{
			rs.Close ();
			return !bExist;
		}
	}
	catch (CException *e) 
	{
		e->ReportError();
		e->Delete();
		if(rs.IsOpen() )
			rs.Close ();
		bExist=!bExist;
	}
	if(rs.IsOpen() )
		rs.Close ();
	return bExist;
}

void CDlgRes::ResetInputCtrls()
{
	SetDlgItemText(IDC_NAME,"");
	SetDlgItemText(IDC_MODULE,"");
	SetDlgItemText(IDC_COMMENT,"");
}
