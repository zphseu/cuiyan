// Template.h: interface for the CTemplate class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_TEMPLATE_H_INCLUDED_
#define AFX_TEMPLATE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

/**
 *  ��ӡ����ģ��ӿ���. 
 */
class CEdRptTpl  
{
public:
	/**
	 *  ����Ϣ. 
	 *  More detailed description this:	
	 */
	struct COLFMT{
		int width;	/**<  �п�ȣ���������.  */
		CString name;	/**<  ������.  */
		CString format;	/**<  ��ʽ.  */

		COLFMT() : width(100) {}
	};

	CArray<COLFMT, COLFMT> m_ColFmt;	/**<  ����Ϣ����.  */

	CString m_szTitle;		/**<  ��ӡ�ı���.  */
	CString m_szHeadRight;	/**<  ��ӡ����ע��.  */
	CString m_szFootRight;	/**<  ��ӡ���ҽ�ע.  */
	CString m_szFootLeft;	/**<  ��ӡ�����ע.  */
	CString m_szSQL;		/**<  ��ѯSQL.  */
	BOOL	m_bFootSum;		/**< ʹ�õײ�ͳ�� */
	CString m_szODBCLink;	/**<  ���ݿ�������.  */
	BOOL	m_bFirstColFixed;	/**<  �����Ƿ�̶����.  */
	BOOL	m_bDefaultPrint;	/**<  �Ƿ�ʹ��Ĭ�ϴ�ӡ��.  */
	UINT	m_nMaxRecordNum;	/**<  �趨������ӡ��¼��.  */

	CStringArray m_arData;
	CString	m_csFileName;
	int		m_nRows;
	int		m_nCols;
public:
	CEdRptTpl();
	BOOL LoadFrom(LPCSTR lpszFileName = NULL);
	LPCTSTR GetDefName();
	
protected:
	BOOL SaveTo(LPCSTR lpszFileName = NULL);
	void SetDefault();
};

#endif // !defined(AFX_TEMPLATE_H_INCLUDED_)
