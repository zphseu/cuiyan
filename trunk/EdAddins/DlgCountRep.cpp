// DlgCountRep.cpp : implementation file
//

#include "stdafx.h"
#include "EdAddins.h"
#include "DlgCountRep.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCountRep dialog


CDlgCountRep::CDlgCountRep(IApplication* pApp, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCountRep::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCountRep)
	//}}AFX_DATA_INIT
	m_wsStat.GetParam(gKeyFull);
	if (m_wsStat.srcext.IsEmpty())
		m_wsStat.srcext = _T("cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h;hpp;hxx;hm;inl;");
	m_pApplication = pApp;
}


void CDlgCountRep::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCountRep)
	DDX_Control(pDX, IDC_RESULTLIST, m_ListCtrl);
	DDX_Control(pDX, IDC_COMBO, m_combo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCountRep, CDialog)
	//{{AFX_MSG_MAP(CDlgCountRep)
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
	ON_BN_CLICKED(IDOPTION, OnOption)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCountRep message handlers
#include <afxdlgs.h>
#include <fstream.h>
void CDlgCountRep::OnExport() 
{
	CString fn;
	CFileDialog dlg(FALSE, ".html", "Report.html", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Html Files (*.html)|*.html|All Files (*.*)|*.*||");
	if (dlg.DoModal() != IDOK)
		return;

	fn = dlg.GetPathName();
	CFileName fnTmp;
	fnTmp.SetPathName(fn);
	if (fnTmp.GetFileExt() != _T(".html"))
		fn = fnTmp.GetPath() + fnTmp.GetFileTitle() + _T(".html");

	ofstream f(fn, ios::out);
	if (!f.good())
	{
		AfxMessageBox("Couln not create " + fn + " file.", MB_OK);
		return;
	}
	
	f << "<html><head><title>EdAddins LineCounter Report</title></head><body>\n"
	  << "<H1>EdAddins LineCounter Report----" 
	  << m_wsStat.GetFileName() << "</H1><HR>\n";
	
	CDevPrjFile * pP;
	for (int i = 0; i < m_wsStat.numProj; i++)
	{
		pP = &(m_wsStat.pProjlist[i]);
		f<< "<TABLE border=1 >\n"
			"<CAPTION><H3>" << pP->GetFileName() << "</H3></CAPTION>\n"
			"<TR><TH align=left width=25%>FileName"
			"<TD width=10%>lines"
			"<TD width=10%>code lines"
			"<TD width=10%>comment lines"
			"<TD width=10%>blank lines"
			"<TD width=10%>mixed lines"
			"<TD>path\n";
        CDevSrcFile *pF;
		for(UINT j = 0; j < pP->numFile; j++)
		{
			pF = &(pP->pFilelist[j]);
			f<< "<TR><TH align=left>"  << pF->GetFileName()
			 << "<TD>"		<< pF->lines
			 << "<TD>"		<< pF->codelines
			 << "<TD>"		<< pF->commentlines
			 << "<TD>"		<< pF->blanklines
			 << "<TD>"		<< pF->mixedlines
			 << "<TD>"		<< pF->GetPath() << "&nbsp;"
			 << "\n";
		}
		f    << "<TR><TH align=left>"  << "Total"
			 << "<TD>"		<< pP->lines
			 << "<TD>"		<< pP->codelines
			 << "<TD>"		<< pP->commentlines
			 << "<TD>"		<< pP->blanklines
			 << "<TD>"		<< pP->mixedlines
			 << "<TD>"		<< pP->GetPath() << "&nbsp;"
			 << "\n"		<< "</Table><P>\n";
	}
	
	f<< "<TABLE border=1 >\n"
		"<CAPTION><H3>" << m_wsStat.GetFileName() << "</H3></CAPTION>\n"
		"<TR><TH align=left width=25%>FileName"
		"<TD width=10%>lines"
		"<TD width=10%>code lines"
		"<TD width=10%>comment lines"
		"<TD width=10%>blank lines"
		"<TD width=10%>mixed lines"
		"<TD>path\n";
	f<< "<TR><TH align=left>"  << "Total"
	 << "<TD>"		<< m_wsStat.lines
	 << "<TD>"		<< m_wsStat.codelines
	 << "<TD>"		<< m_wsStat.commentlines
	 << "<TD>"		<< m_wsStat.blanklines
	 << "<TD>"		<< m_wsStat.mixedlines
	 << "<TD>"		<< m_wsStat.GetPath() << "&nbsp;"
	 << "\n"		<< "</Table><P>\n";
	
	f << "</body></html>";
	f.close();
	ShellExecute(NULL, _T("open"), fn, NULL,NULL, SW_MAXIMIZE);
}

void CDlgCountRep::OnSelchangeCombo() 
{
	int total, code, blank, com, mixed, pos;
	CString str;
	m_combo.GetWindowText(str);
	if (str.Find("Project: ") == 0)
	{
		pos = m_combo.GetCurSel();
		total = m_wsStat.pProjlist[pos].lines;
		code = m_wsStat.pProjlist[pos].codelines;
		blank = m_wsStat.pProjlist[pos].blanklines;
		com = m_wsStat.pProjlist[pos].commentlines;
		mixed = m_wsStat.pProjlist[pos].mixedlines;
	}
	else
	{
		pos = -1;
		total = m_wsStat.lines;
		code = m_wsStat.codelines;
		blank = m_wsStat.blanklines;
		com = m_wsStat.commentlines;
		mixed = m_wsStat.mixedlines;
	}

	SetPair(IDC_LINESC,    IDC_LINESP,      total,         total);
	SetPair(IDC_CODEC,     IDC_CODEP,       code,          total);
	SetPair(IDC_BLANKC,    IDC_BLANKP,      blank,  total);
	SetPair(IDC_COMMENTSC, IDC_COMMENTSP,   com,    total);
	SetPair(IDC_MIXEDC,    IDC_MIXEDP,      mixed,  total);

	SetListData(pos);
}

BOOL CDlgCountRep::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_wsStat.RefreshFileList(m_pApplication);
	m_wsStat.GetStat();

    LPCTSTR     sColumns[] = {_T("File Name"), _T("Lines"),
                              _T("Code"), _T("Comments"), 
                              _T("Mixed"), _T("Blank"), _T("Path")};
    int         lColumns[] = {40, 10, 25, 5, 5, 15, 15};
	
	m_ListCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, 
        (LPARAM) LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP |
        m_ListCtrl.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE));

    LVCOLUMN    lvc;
    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

    for(UINT i = 0; i < sizeof(lColumns)/sizeof(int); i++)
    {
        lvc.iSubItem = i;
        lvc.pszText = (char *)sColumns[i];
        lvc.cx = m_ListCtrl.GetStringWidth(lvc.pszText) + lColumns[i] + 15;
        if (lvc.cx < 40) lvc.cx = 40;
        lvc.fmt = (i >= 2)? LVCFMT_RIGHT : LVCFMT_LEFT;
        m_ListCtrl.InsertColumn(i, &lvc);
    }

	if (m_wsStat.numProj == 1)
		m_combo.AddString("Project: " + m_wsStat.pProjlist[0].GetFileTitle());
	else
	{
		for (long i = 0; i < m_wsStat.numProj; i++)
			m_combo.AddString("Project: " + m_wsStat.pProjlist[i].GetFileTitle());
		m_combo.AddString("WorkSpace: " + m_wsStat.GetFileTitle());
	}

	m_combo.SetCurSel(m_combo.GetCount() - 1);
	OnSelchangeCombo();

	return TRUE;
}

void CDlgCountRep::SetPair(int idc, int idp, int count, int tot)
{
    SetNum(idc, count);
    if (tot)
        SetNum(idp, (count * 100) / tot, '%');
    else
        SetNum(idp, 0);
}

void CDlgCountRep::SetNum(int id, int num, TCHAR suffix)
{
	CString cStr = NumStr(num);
	if (suffix)
        cStr += suffix;
    GetDlgItem(id)->SetWindowText(cStr);
}

void CDlgCountRep::SetListData(int proj)
{
    LV_ITEM lvi;
    CString cStr;
    lvi.mask = LVIF_TEXT | LVIF_PARAM;
    lvi.iItem = m_ListCtrl.GetItemCount();
	lvi.iSubItem = 0;

	m_ListCtrl.DeleteAllItems();
	if (proj >= 0)	//is project
	{
		CDevSrcFile *p;
		for (UINT i = 0; i < m_wsStat.pProjlist[proj].numFile; i++)
		{
			p =  &(m_wsStat.pProjlist[proj].pFilelist[i]);
			m_ListCtrl.InsertItem(i, p->GetFileName());
			m_ListCtrl.SetItemText(i, 1, NumStr(p->lines));
			m_ListCtrl.SetItemText(i, 2, NumStr(p->codelines));
			m_ListCtrl.SetItemText(i, 3, NumStr(p->commentlines));
			m_ListCtrl.SetItemText(i, 4, NumStr(p->mixedlines));
			m_ListCtrl.SetItemText(i, 5, NumStr(p->blanklines));
			m_ListCtrl.SetItemText(i, 6, p->GetPath());
		}
	}
	else	//is workspace
	{
		CDevPrjFile * p;
		for (long i = 0; i < m_wsStat.numProj; i++)
		{
			p = &(m_wsStat.pProjlist[i]);
			m_ListCtrl.InsertItem(i, p->GetFileName());
			m_ListCtrl.SetItemText(i, 1, NumStr(p->lines));
			m_ListCtrl.SetItemText(i, 2, NumStr(p->codelines));
			m_ListCtrl.SetItemText(i, 3, NumStr(p->commentlines));
			m_ListCtrl.SetItemText(i, 4, NumStr(p->mixedlines));
			m_ListCtrl.SetItemText(i, 5, NumStr(p->blanklines));
			m_ListCtrl.SetItemText(i, 6, p->GetPath());
		}
	}
}

CString CDlgCountRep::NumStr(int num)
{
	CString cStr;
    cStr.Format("%d", num);
    int pos = cStr.GetLength() - 1;
    while (pos >= 3)
    {
        cStr = cStr.Left(pos - 2) + "," + cStr.Mid(pos - 2);
        pos -= 3;
    }
	return cStr;
}

void CDlgCountRep::SetWsName(CString wsName)
{
	m_wsStat.SetPathName(wsName);
}

#include "DlgCountOpt.h"
void CDlgCountRep::OnOption() 
{
	CDlgCountOpt dlg(m_wsStat.srcext);
	if (dlg.DoModal() == IDOK)
	{
		m_wsStat.srcext = dlg.m_exts;
		m_wsStat.SetParam(gKeyFull);
	}	
}
