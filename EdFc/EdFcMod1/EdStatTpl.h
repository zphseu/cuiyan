/**************************************************************
 *  Filename:    GraphTempl.h
 *  Copyright:   Shanghai Baosight Software Co., Ltd.
 *
 *  Description: 图表统计模块接口类.
 *
 *  @author:     cuiyan
 *  @version     10/08/2003  cuiyan  Initial Version
 *  @version	 08/29/2003  cuiyan  modify for new szPointSQL and szGroupSQL.
 *           1. szGroupSQL和szPointSQL, 可以使用edson:m1;m2;m3; ... m31形式
 *           2. szGroupSQL的m1, 用于报表的一行一列的信息，因此不参加分组。
**************************************************************/
#ifndef _GRAPH_INCLUDE_
#define  _GRAPH_INCLUDE_

#include <afxtempl.h>

struct  CEdStatTpl
{
public:
	/************************************************************************/
	/*	通用属性															*/
	/*	[Common]															*/
	/************************************************************************/
	CString szTitle;		/**<  统计表名.  */
	CString szODBC;			/**<  ODBC连接字串.  */
	
	CString szColWidth;		/**<  报表列宽度.  */
	CString szFormat;		/**<  报表数字显示格式.  */
	
	BOOL	bFootSum;		/**<  在报表右侧使用总计.  */
	BOOL	bRightSum;		/**<  在报表底部使用总计.  */
	
	CString szVerUint;		/**<  纵坐标单位 */
	CString szHorUint;		/**<  横坐标单位 */

	CString szFootTitle;	/**<  注脚 */
	CString szWhere;		/**<  条件 */
	CString szTextWhere;	/**<  查询语句的文字版，用于显示；如果不赋值省却为szWhere.  */	
	
	/************************************************************************/
	/*	时间统计类型														*/
	/*	[Time]																*/
	/************************************************************************/

	/**
	 *  时间统计类型. 
	 *  More detailed description this: 
	 */
	enum TIMETYPE { 
		non, 	/**<  无效.    */
		day, 	/**<  日统计.  */
		month, 	/**<  月统计.  */
		year	/**<  年统计.  */
	};
	TIMETYPE  type;	/**<  时间统计类型.  */
	
	// 为开发简便，对经常使用的年报、月报、周报和日报，使用简单的方法。
	CString	szTable;	/**< 表名  */
	CString	szField;	/**<  时间字段名.  */
	CTime	tmTime;		/**<  查询的时间.  */

	/************************************************************************/
	/*	数据库查询															*/
	/*	[Database]															*/
	/************************************************************************/
	//对于广泛的使用
	CString szSQL;			/**<  数据查询语句.  */

	/**
	 *  指定是否数据查询记录集的第二列使用分组. 
	 *  空，不分组；不空，为分组的集合，<BR>也可以使用edson:m1;m2;m3; ... m31形式。
	 */
	CString szGroupSQL;	
	/**
	 *  指定是否数据查询记录集的第一列使用填充.
	 *  空，不填充，直接使用；不空，填充为空的数据为零。
	 */
	CString szPointSQL;	
	
	/************************************************************************/
	/*	数据																*/
	/*	[Data]																*/
	/************************************************************************/
	/**
	 * 数据结构为：<P>
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
	
	int		nRows;		/**<  arData的行数.  */
	int		nCols;		/**<  arData的列数.  */
	
public:
	CEdStatTpl();
	BOOL LoadFrom(LPCSTR lpszFileName = NULL);
	LPCTSTR GetDefName();
	
protected:
	void SetDefault();
	BOOL SaveTo(LPCSTR lpszFileName = NULL);
};

#endif // _GRAPH_INCLUDE_

