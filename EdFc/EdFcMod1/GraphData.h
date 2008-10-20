#ifndef GRAPHDATA_H_INCLUDED_
#define GRAPHDATA_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
const CString GRAPHFMTFLAG = _T("This is Graph Data File!"); //文件标签

/**
 *  图表统计模块接口类0. 
 *  先调用本类，再调用CGraphTempl。
 */
class CGraphData
{
public:
	CGraphData()
	{
		char szTmpPath[MAX_PATH];
		GetTempPath(MAX_PATH, szTmpPath);
		szFileName = szTmpPath;
		szFileName += _T("GraphTm.fmt");
	}

	/**
	 *  加在数据.
	 *
	 *  @return 如果成功，返回真.
	 *
	 *  @version  10/08/2003  cuiyan  Initial Version.
	 */
	BOOL Load()
	{
		try {
			CFile f( szFileName,  CFile::modeRead);
			CArchive ar(&f, CArchive::load);
			
			CString csTmp;
			ar >> csTmp;
			if (csTmp != GRAPHFMTFLAG)
			{
				TRACE1("ERROR: %s is not a BSStat.dll's file %s\n", ar.GetFile()->GetFilePath());
				return FALSE;
			}
			
			arRowsName.RemoveAll();
			arColsName.RemoveAll();
			
			ar >> szName;
			ar >> nRows >> nCols;
			for (int i = 0; i < nRows; i++)
			{
				ar >> csTmp;
				arRowsName.Add(csTmp);
			}
			
			for (i = 0; i < nCols + 1; i++)
			{
				ar >> csTmp;
				arColsName.Add(csTmp);
			}
			
			float fTmp;
			for (i = 0; i < nRows*nCols; i++)
			{
				ar >> fTmp;
				arData.Add(fTmp);
			}
			
			ar.Close();
			f.Close();
			
		} catch (CException *e) {
			//e->ReportError();
			e->Delete();
			return FALSE;
		}
		
		return TRUE;
	}

	/**
	 *  保存数据.
	 *
	 *  @return 如果成功，返回真.
	 *
	 *  @version  10/08/2003  cuiyan  Initial Version.
	 */
	BOOL Save()
	{
		try {
			CFile f( szFileName, CFile::modeCreate | CFile::modeWrite);
			CArchive ar(&f, CArchive::store);

			
			ar << GRAPHFMTFLAG;
			ar << szName;
			ar << nRows << nCols;
			for (int i = 0; i < nRows; i++)
				ar << arRowsName[i];
			
			for (i = 0; i < nCols + 1; i++)
				ar << arColsName[i];
			
			for (i = 0; i < nRows*nCols; i++)
				ar << arData[i];		

			ar.Close();
			f.Close();
			
		} catch (CException *e) {
			e->ReportError();
			e->Delete();
			return FALSE;
		}
		
		return TRUE;		
	}

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

	CString szName;		/**<  图表名称.  */		
	CString szVerUint;	/**<  纵轴单位.  */
	CString szHorUint;	/**<  横轴单位.  */

protected:
	CString szFileName;
};

#endif // !defined(GRAPHDATA_H_INCLUDED_)
