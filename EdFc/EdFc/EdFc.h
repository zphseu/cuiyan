// EdFc.h : EdFc Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CEdFcApp:
// �йش����ʵ�֣������ EdFc.cpp
//

class CEdFcApp : public CWinApp
{
public:
	CEdFcApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEdFcApp theApp;
