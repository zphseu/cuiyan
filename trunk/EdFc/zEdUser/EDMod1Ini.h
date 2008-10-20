// BSUserIni.h: interface for the CEdMod1Ini class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSUSERINI_H__3CB778C5_DB2D_4708_8B77_6829D2138C51__INCLUDED_)
#define AFX_BSUSERINI_H__3CB778C5_DB2D_4708_8B77_6829D2138C51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEdMod1Ini  
{
public:
	BOOL GetVisable(int index);
	BOOL WriteConfig();
	BOOL ReadConfig();
	CEdMod1Ini();
	virtual ~CEdMod1Ini();

	BOOL m_bUseDB;
	BOOL m_bNeedLogin;
	CString m_csConStr;
	CString m_csDefUser;
	CString m_csDefGrp; // 添加新用户缺省的组
	CString	m_csConfig;	//
		// 10000	权限分配不包括资源分配
		// 01000	权限分配
		// 00100	组群管理
		// 00010	资源管理
		// 00001	用户管理	
protected:
	CString GetIniFileName();
};

#endif // !defined(AFX_BSUSERINI_H__3CB778C5_DB2D_4708_8B77_6829D2138C51__INCLUDED_)
