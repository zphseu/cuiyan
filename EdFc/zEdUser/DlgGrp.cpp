// DlgGrp.cpp : implementation file
//

#include "stdafx.h"
#include "DlgGrp.h"
#include "Func.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern "C" CDatabase *GetDB();
/////////////////////////////////////////////////////////////////////////////
// CDlgGrp dialog

CDlgGrp::CDlgGrp(CWnd* pParent /*=NULL*/)
	: CSTabDialog(CDlgGrp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGrp)
	//}}AFX_DATA_INIT
	m_csTitle = _T("组群管理");
}

void CDlgGrp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGrp)
	DDX_Control(pDX, IDC_LIST, m_lstCtrl);
	DDX_Text(pDX, IDC_COMMENT, m_csCmt);
	DDX_Text(pDX, IDC_NAME, m_csName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGrp, CDialog)
	//{{AFX_MSG_MAP(CDlgGrp)
	ON_BN_CLICKED(ID_DEL, OnDel)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnclkList)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGrp message handlers

void CDlgGrp::OnDel() 
{
	UpdateData();
	if(!ValidateInput()) 
	return;
	
	
	if(!IsNameExist(m_csName))
	{
		MessageBox("不存在该名称的组群，无法删除!", _T("信息"), MB_OK );
		return;
	}

	CString csTmp;
	csTmp.Format("确认删除组群：%s 吗？", m_csName);
	if (MessageBox(csTmp, _T("信息"), MB_YESNO ) == IDNO)
		return;

	CSetGrp rs(GetDB());
	
	try
	{
		rs.m_strFilter.Format("AA='%s'", m_csName);
		rs.Open();
		
		if( rs.IsEOF( ) || !rs.CanUpdate( ))
			throw -1;
		
		rs.Delete( );

		//为了维护数据库的一致性,删除群组时，要删除该群组的资源纪录
		csTmp.Format("DELETE FROM ZED003 WHERE AA='%s'",m_csName);
		GetDB()->ExecuteSQL(csTmp);
		//为了维护数据库的一致性,删除群组时，要删除该群组的用户纪录
		csTmp.Format("DELETE FROM ZED004 WHERE AA='%s'",m_csName);
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


void CDlgGrp::OnSave() 
{
	if(!ValidateInput()) 
		return;
	
	CSetGrp	rs(GetDB());
	try
	{
		rs.m_strFilter.Format("AA='%s'", m_csName);
		rs.Open();
		
		if (rs.IsEOF())
			rs.AddNew();
		else
			rs.Edit();
		
		*(tagGrp*)&rs = *(tagGrp*)this;
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

void CDlgGrp::OnclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nItem = m_lstCtrl.GetNextItem(-1, LVNI_SELECTED);
	*pResult = 0;	
	
	if ( nItem < 0 )
		return;
	
	CSetGrp rs(GetDB());
	
	try
	{
		m_csName = m_lstCtrl.GetItemText(nItem, 0);
		rs.m_strFilter.Format("AA='%s'", m_csName);
		rs.Open();
		
		if (!rs.IsEOF())
		{
			*(tagGrp*)this = (tagGrp)rs;
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

BOOL CDlgGrp::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LPSTR szCaption[] = {
		"名称", "备注", NULL
	};
	
	int nCaption[] = { 3, 1, 2 };
	CFunc::SetColumnList(m_lstCtrl, szCaption, nCaption);


	return TRUE;
}

BOOL CDlgGrp::LoadData()
{
	BOOL bRet = FALSE;
	CSetGrp rs(GetDB());
	
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
			m_lstCtrl.SetItemText(item_.iItem, 1, rs.m_csCmt);
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

void CDlgGrp::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (bShow)
		LoadData();	
}

BOOL CDlgGrp::ValidateInput()
{
	UpdateData();
	if( (m_csName.GetLength()) > 32 || (m_csName.GetLength())<1)
	{
		MessageBox("组群名称长度必须在32字符之内且不能为空!","注意",MB_OK);
		GetDlgItem(IDC_NAME)->SetFocus();
		return FALSE;
	}

	if( (m_csCmt.GetLength() > 255))
		m_csCmt = m_csCmt.Left(255);
	
	return TRUE;
}

bool CDlgGrp::IsNameExist(CString &strName)
{
	bool bExist=true;
	CSetGrp rs(GetDB());
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

void CDlgGrp::ResetInputCtrls()
{
	this->SetDlgItemText(IDC_NAME,"");
	this->SetDlgItemText(IDC_COMMENT,"");
}
