#pragma once


// CDlgCom �Ի���
#include "Resource.h"

class CDlgCom : public CDialog
{
	DECLARE_DYNAMIC(CDlgCom)

public:
	CDlgCom(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCom();

// �Ի�������
	enum { IDD = IDD_COM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
