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
 *  打印报表模板接口类. 
 */
class CEdRptTpl  
{
public:
	/**
	 *  列信息. 
	 *  More detailed description this:	
	 */
	struct COLFMT{
		int width;	/**<  列宽度，必填数据.  */
		CString name;	/**<  列名称.  */
		CString format;	/**<  格式.  */

		COLFMT() : width(100) {}
	};

	CArray<COLFMT, COLFMT> m_ColFmt;	/**<  列信息集合.  */

	CString m_szTitle;		/**<  打印的标题.  */
	CString m_szHeadRight;	/**<  打印的首注释.  */
	CString m_szFootRight;	/**<  打印的右脚注.  */
	CString m_szFootLeft;	/**<  打印的左脚注.  */
	CString m_szSQL;		/**<  查询SQL.  */
	BOOL	m_bFootSum;		/**< 使用底部统计 */
	CString m_szODBCLink;	/**<  数据库连接字.  */
	BOOL	m_bFirstColFixed;	/**<  首行是否固定变灰.  */
	BOOL	m_bDefaultPrint;	/**<  是否使用默认打印机.  */
	UINT	m_nMaxRecordNum;	/**<  设定的最大打印记录数.  */

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
