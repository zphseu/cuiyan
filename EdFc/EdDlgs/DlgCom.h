#pragma once


// CDlgCom 对话框
#include "Resource.h"

class CDlgCom : public CDialog
{
	DECLARE_DYNAMIC(CDlgCom)

public:
	CDlgCom(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCom();

// 对话框数据
	enum { IDD = IDD_COM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
