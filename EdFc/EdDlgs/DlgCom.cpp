// DlgCom.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgCom.h"

// CDlgCom 对话框

IMPLEMENT_DYNAMIC(CDlgCom, CDialog)
CDlgCom::CDlgCom(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCom::IDD, pParent)
{
}

CDlgCom::~CDlgCom()
{
}

void CDlgCom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCom, CDialog)
END_MESSAGE_MAP()


// CDlgCom 消息处理程序
