/**************************************************************
 *  Filename:    GraphTempl.h
 *  Copyright:   Shanghai Baosight Software Co., Ltd.
 *
 *  Description: ͼ��ͳ��ģ��ӿ���.
 *
 *  @author:     cuiyan
 *  @version     10/08/2003  cuiyan  Initial Version
 *  @version	 08/29/2003  cuiyan  modify for new szPointSQL and szGroupSQL.
 *           1. szGroupSQL��szPointSQL, ����ʹ��edson:m1;m2;m3; ... m31��ʽ
 *           2. szGroupSQL��m1, ���ڱ����һ��һ�е���Ϣ����˲��μӷ��顣
**************************************************************/
#ifndef _GRAPH_INCLUDE_
#define  _GRAPH_INCLUDE_

#include <afxtempl.h>

struct  CEdStatTpl
{
public:
	/************************************************************************/
	/*	ͨ������															*/
	/*	[Common]															*/
	/************************************************************************/
	CString szTitle;		/**<  ͳ�Ʊ���.  */
	CString szODBC;			/**<  ODBC�����ִ�.  */
	
	CString szColWidth;		/**<  �����п��.  */
	CString szFormat;		/**<  ����������ʾ��ʽ.  */
	
	BOOL	bFootSum;		/**<  �ڱ����Ҳ�ʹ���ܼ�.  */
	BOOL	bRightSum;		/**<  �ڱ���ײ�ʹ���ܼ�.  */
	
	CString szVerUint;		/**<  �����굥λ */
	CString szHorUint;		/**<  �����굥λ */

	CString szFootTitle;	/**<  ע�� */
	CString szWhere;		/**<  ���� */
	CString szTextWhere;	/**<  ��ѯ�������ְ棬������ʾ���������ֵʡȴΪszWhere.  */	
	
	/************************************************************************/
	/*	ʱ��ͳ������														*/
	/*	[Time]																*/
	/************************************************************************/

	/**
	 *  ʱ��ͳ������. 
	 *  More detailed description this: 
	 */
	enum TIMETYPE { 
		non, 	/**<  ��Ч.    */
		day, 	/**<  ��ͳ��.  */
		month, 	/**<  ��ͳ��.  */
		year	/**<  ��ͳ��.  */
	};
	TIMETYPE  type;	/**<  ʱ��ͳ������.  */
	
	// Ϊ������㣬�Ծ���ʹ�õ��걨���±����ܱ����ձ���ʹ�ü򵥵ķ�����
	CString	szTable;	/**< ����  */
	CString	szField;	/**<  ʱ���ֶ���.  */
	CTime	tmTime;		/**<  ��ѯ��ʱ��.  */

	/************************************************************************/
	/*	���ݿ��ѯ															*/
	/*	[Database]															*/
	/************************************************************************/
	//���ڹ㷺��ʹ��
	CString szSQL;			/**<  ���ݲ�ѯ���.  */

	/**
	 *  ָ���Ƿ����ݲ�ѯ��¼���ĵڶ���ʹ�÷���. 
	 *  �գ������飻���գ�Ϊ����ļ��ϣ�<BR>Ҳ����ʹ��edson:m1;m2;m3; ... m31��ʽ��
	 */
	CString szGroupSQL;	
	/**
	 *  ָ���Ƿ����ݲ�ѯ��¼���ĵ�һ��ʹ�����.
	 *  �գ�����䣬ֱ��ʹ�ã����գ����Ϊ�յ�����Ϊ�㡣
	 */
	CString szPointSQL;	
	
	/************************************************************************/
	/*	����																*/
	/*	[Data]																*/
	/************************************************************************/
	/**
	 * ���ݽṹΪ��<P>
	 * <table>
	 * <tr>
	 *	<td>colsName0</td>       <td>colsName1</td>     <td>colsname2</td>      <td>...	...</td>   <td>colsname(ncols + 1)</td>
	 * </tr><tr>
	 *  <td>rowsname0</td>       <td>data(0)</td>       <td>data(1*nrows)</td>  <td>...	...</td>   <td>data((ncols-1)*nrows)</td>
	 * </tr><tr>
	 *	<td>rowsname1</td>       <td>data(1)</td>       <td>data(1*nrows+1)</td><td>...	...</td>   <td>...	...</td>
	 * </tr><tr>
	 *  <td>... ...</td>         <td>data(...)</td>     <td>data(...)</td>      <td>data(...)</td> <td>data(...)</td>
	 * </tr><tr>
	 *  <td>rowsname(nrows)</td> <td>data(nrows-1)</td> <td>...	...</td>        <td>...	...</td>   <td>data(ncols*nrows)</td>
	 * </tr>
	 */
	CStringArray arRowsName;	
	CStringArray arColsName;
	CArray<float, float> arData;
	
	int		nRows;		/**<  arData������.  */
	int		nCols;		/**<  arData������.  */
	
public:
	CEdStatTpl();
	BOOL LoadFrom(LPCSTR lpszFileName = NULL);
	LPCTSTR GetDefName();
	
protected:
	void SetDefault();
	BOOL SaveTo(LPCSTR lpszFileName = NULL);
};

#endif // _GRAPH_INCLUDE_

