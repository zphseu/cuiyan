// DlgMsgBoxWiz.cpp : implementation file
//

#include "stdafx.h"
#include "EdAddins.h"
#include "DlgMsgBoxWiz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgBoxWiz dialog

CDlgMsgBoxWiz::CDlgMsgBoxWiz(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMsgBoxWiz::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMsgBoxWiz)
	m_bmsg = TRUE;
	m_bcaption = TRUE;
	m_value = _T("");
	m_text = _T("");
	m_equ = _T("");
	m_caption = _T("");
	m_btn = _T("");
	m_modality = _T("");
	m_symbol = _T("");
	m_type = _T("");
	m_defbtn = _T("");
	//}}AFX_DATA_INIT
}


void CDlgMsgBoxWiz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMsgBoxWiz)
	DDX_Control(pDX, IDC_COMBOCONDITION, m_ccondition);
	DDX_Check(pDX, IDC_MSGVAR, m_bmsg);
	DDX_Check(pDX, IDC_CAPTIONVAR, m_bcaption);
	DDX_CBString(pDX, IDC_COMBOVALUE, m_value);
	DDX_Text(pDX, IDC_TEXT, m_text);
	DDX_CBString(pDX, IDC_COMBOEQU, m_equ);
	DDX_CBString(pDX, IDC_CAPTION, m_caption);
	DDX_CBString(pDX, IDC_COMBOBTN, m_btn);
	DDX_CBString(pDX, IDC_COMBOMODALITY, m_modality);
	DDX_CBString(pDX, IDC_COMBOSYMBOL, m_symbol);
	DDX_CBString(pDX, IDC_COMBOTYPE, m_type);
	DDX_CBString(pDX, IDC_COMBODEFBTN, m_defbtn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMsgBoxWiz, CDialog)
	//{{AFX_MSG_MAP(CDlgMsgBoxWiz)
	ON_BN_CLICKED(IDTEST, OnTest)
	ON_CBN_SELCHANGE(IDC_COMBOBTN, OnSelchangeCombobtn)
	ON_BN_CLICKED(IDVIEW, OnView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgBoxWiz message handlers

void CDlgMsgBoxWiz::OnTest() 
{
	UpdateData();

	if (!m_bcaption)
		m_caption = "$(" + m_caption + ")";
	
	if (!m_bmsg)
		m_text = "$(" + m_text + ")";

	UINT style = getStyle(m_symbol) | getStyle(m_defbtn) | 
		getStyle(m_btn) | getStyle(m_modality);

	switch ( ((CComboBox*)GetDlgItem(IDC_COMBOTYPE))->GetCurSel() )
	{
	case 2:	//AfxMessageBox
		AfxMessageBox(m_text, style);
		break;

	case 1:	//::MessageBox
		::MessageBox(NULL, m_text, m_caption, style);
		break;

	default:	//CWnd::MessageBox
		MessageBox(m_text, m_caption, style);
		break;
	}
}

void CDlgMsgBoxWiz::OnOK() 
{
	UpdateData();
	m_msgbox = GetMsgBoxStr();
	CDialog::OnOK();
}


BOOL CDlgMsgBoxWiz::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CComboBox*)GetDlgItem(IDC_COMBOTYPE))->SetCurSel(2);
	((CComboBox*)GetDlgItem(IDC_COMBOSYMBOL))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBOBTN))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_CAPTION))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBODEFBTN))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBOMODALITY))->SetCurSel(0);
	m_ccondition.SetCurSel(1);
	((CComboBox*)GetDlgItem(IDC_COMBOEQU))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBOVALUE))->SetCurSel(0);
	
	return TRUE;
}


void CDlgMsgBoxWiz::OnSelchangeCombobtn() 
{
	CString RETURN_TYPE[7] = { _T("IDOK"), _T("IDYES"), _T("IDABORT"), _T("IDRETRY"),
		_T("IDCANCEL"), _T("IDNO"), _T("IDIGNORE")};
	static BTN_TYPE[6] = { 1, 1+10*5, 4+10*5, 2+10*6, 2+10*6+100*5, 3+10*4+100*5 };

	CComboBox* pA = (CComboBox*)GetDlgItem(IDC_COMBOBTN);
	CComboBox* pB = (CComboBox*)GetDlgItem(IDC_COMBOVALUE);
	UINT n = BTN_TYPE[pA->GetCurSel()];

	
	for (int i = pB->GetCount() -1; i >= 0; i--)
		pB->DeleteString(i);

	while(n)
	{
		UINT m = n%10 - 1;
		n /= 10;
		pB->AddString(RETURN_TYPE[m]);
	}
	pB->SetCurSel(0);
}

CString CDlgMsgBoxWiz::GetMsgBoxStr()
{
	CString str = _T("");

	CString tmp;
	if (m_bcaption)
	{
		tmp.Format("_T(\"%s\")", m_caption);
		m_caption = tmp;
	}
	
	if (m_bmsg)
	{
		tmp.Format("_T(\"%s\")", m_text);
		m_text = tmp;
	}
	
	
	CString m_style(_T("MB_") + m_btn);

	if (!m_symbol.IsEmpty())
		m_style += _T(" | MB_ICON") + m_symbol;

	if (!m_modality.IsEmpty())
		m_style += _T(" | MB_") + m_modality;

	if (!m_defbtn.IsEmpty())
		m_style += _T(" | MB_DEF") + m_defbtn;


	CString m_condition;
	switch ( ((CComboBox*)GetDlgItem(IDC_COMBOTYPE))->GetCurSel() )
	{
	case 2:	//AfxMessageBox
		switch(m_ccondition.GetCurSel())
		{
		case 0:
			m_condition = _T("%s(%s, %s);");
			break;
		case 1:
			m_condition = _T("if( %s( %s, %s ) %s %s )\n{\n}\n");
			break;
		default:
			m_condition = _T("if( %s( %s, %s ) %s %s )\n{\n}\nelse\n{\n}\n");
			break;
		}
		str.Format(m_condition, m_type, m_text, m_style, m_equ, m_value);
		break;

	case 1:	//::MessageBox
		switch(m_ccondition.GetCurSel())
		{
		case 0:
			m_condition = _T("%s(NULL, %s, %s, %s);");
			break;
		case 1:
			m_condition = _T("if(%s( NULL, %s, %s, %s ) %s %s)\n{\n}\n");
			break;
		default:
			m_condition = _T("if(%s( NULL, %s, %s, %s ) %s %s)\n{\n}\nelse\n{\n}\n");
			break;
		}
		str.Format(m_condition, m_type, m_text, m_caption, m_style, m_equ, m_value);		
		break;
	default:	//CWnd::MessageBox
		switch(m_ccondition.GetCurSel())
		{
		case 0:
			m_condition = _T("%s( %s, %s, %s );");
			break;
		case 1:
			m_condition = _T("if(%s( %s, %s, %s ) %s %s)\n{\n}\n");
			break;
		default:
			m_condition = _T("if(%s (%s, %s, %s ) %s %s)\n{\n}\nelse\n{\n}\n");
			break;
		}
		str.Format(m_condition, m_type, m_text, m_caption, m_style, m_equ, m_value);
		break;
	}
	
	return str;
}

void CDlgMsgBoxWiz::OnView() 
{
	UpdateData();
	AfxMessageBox( GetMsgBoxStr() );	
}

UINT CDlgMsgBoxWiz::getStyle(CString szStyle)
{
	UINT bRet = 0;

	if (szStyle.CompareNoCase("OK") == 0)
		bRet = MB_OK;
	else if (szStyle.CompareNoCase("OKCANCEL") == 0)
		bRet = MB_OKCANCEL;
	else if (szStyle.CompareNoCase("RETRYCANCEL") == 0)
		bRet = MB_RETRYCANCEL;
	else if (szStyle.CompareNoCase("YESNO") == 0)
		bRet = MB_YESNO;
	else if (szStyle.CompareNoCase("YESNOCANCEL") == 0)
		bRet = MB_YESNOCANCEL;
	else if (szStyle.CompareNoCase("APPLMODAL") == 0)
		bRet = MB_APPLMODAL;
	else if (szStyle.CompareNoCase("SYSTEMMODAL") == 0)
		bRet = MB_SYSTEMMODAL;
	else if (szStyle.CompareNoCase("TASKMODAL") == 0)
		bRet = MB_TASKMODAL;
	else if (szStyle.CompareNoCase("EXCLAMATION") == 0)
		bRet = MB_ICONEXCLAMATION;
	else if (szStyle.CompareNoCase("INFORMATION") == 0)
		bRet = MB_ICONINFORMATION;
	else if (szStyle.CompareNoCase("QUESTION") == 0)
		bRet = MB_ICONQUESTION;
	else if (szStyle.CompareNoCase("STOP") == 0)
		bRet = MB_ICONSTOP;
	else if (szStyle.CompareNoCase("BUTTON1") == 0)
		bRet = MB_DEFBUTTON1;
	else if (szStyle.CompareNoCase("BUTTON2") == 0)
		bRet = MB_DEFBUTTON2;
	else if (szStyle.CompareNoCase("BUTTON3") == 0)
		bRet = MB_DEFBUTTON3;
	else
		bRet = MB_OK;
	
	return bRet;
}
