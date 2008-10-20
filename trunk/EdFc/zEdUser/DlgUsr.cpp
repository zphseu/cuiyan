// DlgUsr.cpp : implementation file
//

#include "stdafx.h"
#include "DlgUsr.h"
#include "FCS32.h"
#include "EdMod1Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" CDatabase* GetDB();
extern CEdMod1Ini g_ini;
/////////////////////////////////////////////////////////////////////////////
// CDlgUsr dialog
CDlgUsr::CDlgUsr(CWnd* pParent /*=NULL*/)
	: CSTabDialog(CDlgUsr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUsr)
	m_csHandset = _T("");
	m_csName = _T("");
	m_csPos = _T("");
	m_pwd2 = _T("");
	m_csPwd = _T("");
	m_csTel = _T("");
	m_csCmt = _T("");
	//}}AFX_DATA_INIT
	m_csTitle = _T("�û�����");		
}

void CDlgUsr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUsr)
	DDX_Control(pDX, IDC_LIST, m_lstCtrl);
	DDX_Text(pDX, IDC_HANDSET, m_csHandset);
	DDX_Text(pDX, IDC_NAME, m_csName);
	DDX_Text(pDX, IDC_POSITION, m_csPos);
	DDX_Text(pDX, IDC_CONFIM, m_pwd2);
	DDX_Text(pDX, IDC_PWD, m_csPwd);
	DDX_Text(pDX, IDC_TELPHONE, m_csTel);
	DDX_Text(pDX, IDC_COMMENT, m_csCmt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUsr, CDialog)
	//{{AFX_MSG_MAP(CDlgUsr)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnclkList)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUsr message handlers

BOOL CDlgUsr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_lstCtrl.SetExtendedStyle( m_lstCtrl.GetExtendedStyle()
		| LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );
		
	LPSTR szCaption[] = {
		"����", "ְ��", "�绰", "�ֻ�", "��ע", NULL
	};

	int nCaption[] = { 8, 1, 1, 1, 2, 3	};

	LV_COLUMN Column;
	Column.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	Column.fmt = LVCFMT_LEFT;
	
	CRect rt;
	m_lstCtrl.GetClientRect(&rt);
	nCaption[0] = rt.Width() / nCaption[0];
	for (int i = 0; szCaption[i]; i++)
	{
		Column.cx = nCaption[0] * nCaption[i+1];
		Column.pszText = szCaption[i];
		m_lstCtrl.InsertColumn(i, &Column);
	}

	return TRUE;
}

BOOL CDlgUsr::LoadData()
{
	BOOL bRet = FALSE;
	CSetUsr rs(GetDB());

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
			m_lstCtrl.SetItemText(item_.iItem, 1, rs.m_csPos);
			m_lstCtrl.SetItemText(item_.iItem, 2, rs.m_csTel);
			m_lstCtrl.SetItemText(item_.iItem, 3, rs.m_csHandset);
			m_lstCtrl.SetItemText(item_.iItem, 4, rs.m_csCmt);
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
	
//	RedrawWindow();
	return bRet;
}

void CDlgUsr::OnclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nItem = m_lstCtrl.GetNextItem(-1, LVNI_SELECTED);
	*pResult = 0;	
	
	if ( nItem < 0 )
		return;
	
	CSetUsr rs(GetDB());
	
	try
	{
		m_csName = m_lstCtrl.GetItemText(nItem, 0);
		rs.m_strFilter.Format("AA='%s'", m_csName);
		rs.Open();
		
		if (!rs.IsEOF())
		{
			*(tagUsr*)this = (tagUsr)rs;
			m_csPwd = _T("");
			m_pwd2 = _T("");
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

void CDlgUsr::OnDel() 
{
	UpdateData();
	
	if( (m_csName.GetLength()) > 32 || (m_csName.GetLength())<1)
	{
		MessageBox("�û����Ƴ��ȱ�����32�ַ�֮���Ҳ���Ϊ��!","ע��",MB_OK);
		GetDlgItem(IDC_NAME)->SetFocus();
		return ;
	}


	if(!IsNameExist(m_csName))
	{
		MessageBox("�����ڸ����Ƶ��û����޷�ɾ��!", _T("��Ϣ"), MB_OK );
		return;
	}

	CString csTmp;
	csTmp.Format("ȷ��ɾ���û� %s ��", m_csName);
	if (MessageBox(csTmp, _T("��Ϣ"), MB_YESNO ) == IDNO)
		return;
	
	CSetUsr rs(GetDB());
	
	try
	{
		rs.m_strFilter.Format("AA='%s'", m_csName);
		rs.Open();
		
		if( rs.IsEOF( ) || !rs.CanUpdate( ))
			throw -1;
		
		rs.Delete( );
		
		//Ϊ��ά�����ݿ��һ����,ɾ���û���,ɾ���������ѵǼǵĸ��û���¼
		csTmp.Format("DELETE FROM ZED004 WHERE AB='%s'", m_csName);
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

void CDlgUsr::OnSave() 
{
	if (! ValidateInput())
		return;

	if (m_csPwd != m_pwd2)
	{
		MessageBox( _T("������������벻��ͬ"), _T("����"), MB_OK );
		return;
	}

	BOOL bNew = FALSE;
	CSetUsr rs(GetDB());
	try
	{
 		rs.m_strFilter.Format("AA='%s'", m_csName);
		rs.Open();

		bNew = rs.IsEOF();
		CString csOldPwd = rs.m_csPwd;
		
		if(bNew)			
			rs.AddNew();
		else
			rs.Edit();
		
		*(tagUsr*)&rs = *(tagUsr*)this;

		if (! bNew && rs.m_csPwd.IsEmpty() && MessageBox(_T("����Ϊ�գ��Ƿ񱣴�Ϊԭ�е����룿"), _T("��Ϣ"),
			MB_YESNO) == IDYES)
		{
			rs.m_csPwd = csOldPwd;
		}
		else
		{
			CFCS32 fcs;
			rs.m_csPwd = fcs.fcs32((LPCSTR)rs.m_csPwd);
		}
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
	
	// �������û�ʱ,��Ҫ���������ļ���DefGroup
	// �����������һ��ȱʡ����,�Ի����Դ
	if (bNew && !g_ini.m_csDefGrp.IsEmpty())
	{
		CString strSQL;
		strSQL.Format("INSERT INTO ZED004 VALUES('%s','%s')", 
			g_ini.m_csDefGrp, m_csName);
		try
		{
			GetDB()->ExecuteSQL(strSQL);	
		}
		catch(CDBException e)
		{
			//Do nothing
		}
	}
	
	LoadData();
	return;	
}

void CDlgUsr::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (bShow)
		LoadData();		
}

BOOL CDlgUsr::ValidateInput()
{
	UpdateData();
	
	if( (m_csName.GetLength() > 32)  || (m_csName.GetLength() <1))
	{
		MessageBox("���Ƴ��ȱ�����32�ַ�֮���Ҳ���Ϊ��!","ע��",MB_OK);
		GetDlgItem(IDC_NAME)->SetFocus();
		return FALSE;
	}
	if( (m_csPwd.GetLength() > 32) )
	{
		MessageBox("���볤�ȱ�����32�ַ�֮��!","ע��",MB_OK);
		GetDlgItem(IDC_PWD)->SetFocus();
		return FALSE;
	}
	
	if( m_pwd2.Compare(m_csPwd) != 0 )  
	{
		MessageBox("ȷ����������벻һ��,����������!","ע��",MB_OK);
		GetDlgItem(IDC_CONFIM)->SetFocus();
		return FALSE;
	}
	
	if( m_csPos.GetLength() > 32) 
	{
		MessageBox("ְ����Ϣ���ȱ�����32�ַ�֮��","ע��",MB_OK);
		GetDlgItem(IDC_POSITION)->SetFocus();
		return FALSE;
	}

	if( (m_csTel.GetLength()>32))
	{
		MessageBox("�绰���ȱ�����32�ַ�֮��!","ע��",MB_OK);
		GetDlgItem(IDC_TELPHONE)->SetFocus();
		return FALSE;
	}
	else
	{
		//��֤�Ƿ������ֻ�'-',���������ֻ�'-'
		for(int i=0;i<m_csTel.GetLength ();i++)
		{
			TCHAR ch=m_csTel.GetAt(i);
			if( ((ch>'9') || (ch<'0')) && (ch!='-') )
			{
				MessageBox("�绰����ֻ�ܰ������ֻ�'-'!","ע��",MB_OK);
				return FALSE;
			}
		}

	}
	

	if( (m_csHandset.GetLength() > 11))
	{
		MessageBox("�ֻ����ȱ�����11�ַ�֮��!","ע��",MB_OK);
		GetDlgItem(IDC_HANDSET)->SetFocus();
		return FALSE;
	}
	else
	{
		//��֤�Ƿ�������,�ֻ�����������
		for(int i=0;i<m_csHandset.GetLength ();i++)
		{
			TCHAR ch=m_csHandset.GetAt(i);
			if( (ch>'9') || (ch<'0') )
			{
				MessageBox("�ֻ�����ֻ�ܰ�������!","ע��",MB_OK);
				return FALSE;
			}
		}
	}
	
	if( (m_csCmt.GetLength() > 255))
		m_csCmt = m_csCmt.Left(255);
	
	return TRUE;
}


	
bool CDlgUsr::IsNameExist(CString &strName)
{
	bool bExist=true;
	CSetUsr rs(GetDB());
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

void CDlgUsr::ResetInputCtrls()
{
	SetDlgItemText(IDC_NAME,"");
	SetDlgItemText(IDC_PWD,"");
	SetDlgItemText(IDC_COMMENT,"");
	SetDlgItemText(IDC_CONFIM,"");
	SetDlgItemText(IDC_TELPHONE,"");
	SetDlgItemText(IDC_HANDSET,"");
	SetDlgItemText(IDC_POSITION,"");
}

