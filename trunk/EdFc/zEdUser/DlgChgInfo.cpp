// DlgChgInfo.cpp : implementation file
//

#include "stdafx.h"
#include "DlgChgInfo.h"
#include "EdUserCfg.h"
#include "FCS32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" CDatabase *GetDB();
/////////////////////////////////////////////////////////////////////////////
// CDlgChgInfo dialog

CDlgChgInfo::CDlgChgInfo(LPCSTR szUid, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChgInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChgInfo)
	m_cmt = _T("");
	m_pwd2 = _T("");
	m_handset = _T("");
	m_pwd = _T("");
	m_oldpwd = _T("");
	m_tel = _T("");
	m_uid = szUid;
	//}}AFX_DATA_INIT
}

void CDlgChgInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChgInfo)
	DDX_Text(pDX, IDC_COMMENT, m_cmt);
	DDX_Text(pDX, IDC_CONFIRMPSW, m_pwd2);
	DDX_Text(pDX, IDC_HANDSET, m_handset);
	DDX_Text(pDX, IDC_NEWPSW, m_pwd);
	DDX_Text(pDX, IDC_OLDPSW, m_oldpwd);
	DDX_Text(pDX, IDC_TEL, m_tel);
	DDX_Text(pDX, IDC_USER, m_uid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChgInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgChgInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChgInfo message handlers

void CDlgChgInfo::OnOK() 
{
	if(!ValidateInput()) 
		return;
	//Verify user have rights
	CEdUserCfg uc;
	if(!uc.ValidateUsr(m_uid, m_oldpwd))
	{
		MessageBox("无此用户或密码不正确!","注意",MB_OK);
		return ;
	}
	
	//refresh database table
	BOOL bSuccess = FALSE;
	CSetUsr rs(GetDB());
	try
	{
		rs.m_strFilter.Format("AA='%s'", m_uid);
		rs.Open();
		
		if (!rs.IsEOF())
		{
			rs.Edit();
			CFCS32 fcs;
			rs.m_csPwd = fcs.fcs32((LPCSTR)rs.m_csPwd);
			rs.m_csCmt = m_cmt ;
			rs.m_csHandset = m_handset ;
			rs.m_csPwd = m_pwd ;
			rs.m_csTel = m_tel ;
			rs.Update();	
		}
		else
		{
			MessageBox("无此用户，修改失败！", "注意", MB_OK);
			rs.Close();
			EndDialog(IDCANCEL);
		}
		
		bSuccess = TRUE;
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
	MessageBox(bSuccess ? "修改成功！" : "修改失败！", "注意", MB_OK);
	EndDialog(IDOK);
}

BOOL CDlgChgInfo::ValidateInput()
{
	UpdateData();
	
	if( (m_pwd.GetLength() > 32) )
	{
		MessageBox("密码长度必须在32字符之内!","注意",MB_OK);
		GetDlgItem(IDC_NEWPSW)->SetFocus();
		return FALSE;
	}

	if( m_pwd2.Compare(m_pwd) != 0 )  
	{
		MessageBox("确认密码和密码不一致,请重新输入!","注意",MB_OK);
		GetDlgItem(IDC_CONFIRMPSW)->SetFocus();
		return FALSE;
	}
	
	if( (m_tel.GetLength()>32))
	{
		MessageBox("电话长度必须在32字符之内!","注意",MB_OK);
		GetDlgItem(IDC_TEL)->SetFocus();
		return FALSE;
	}
	
	if( (m_handset.GetLength() > 11))
	{
		MessageBox("手机长度必须在32字符之内!","注意",MB_OK);
		GetDlgItem(IDC_HANDSET)->SetFocus();
		return FALSE;
	}

	if( (m_oldpwd.GetLength()>32))
	{
		MessageBox("旧密码长度必须在32字符之内!","注意",MB_OK);
		GetDlgItem(IDC_OLDPSW)->SetFocus();
		return FALSE;
	}
	
	if( (m_cmt.GetLength() > 255))
		m_cmt = m_cmt.Left(255);

	return TRUE;	
}
