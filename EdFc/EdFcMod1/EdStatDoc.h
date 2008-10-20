#if !defined(AFX_EDSTATDOC_H__9D53912F_0CC1_45A3_800B_375E561FFF8D__INCLUDED_)
#define AFX_EDSTATDOC_H__9D53912F_0CC1_45A3_800B_375E561FFF8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EdStatDoc.h : header file
//

#include "Pie.h"
#include "EdStatTpl.h"
#include "EasyReport.h"

class CEdStatDoc
{
public:
	CEdStatDoc();           // protected constructor used by dynamic creation
	virtual ~CEdStatDoc();
	BOOL	IsLoaded() { return m_bLoaded; }	
	void SetCutPie(BOOL bCutPie);
	BOOL GetData();

	CPie<double> m_Graph;
	CEasyReport	m_Report;
	CEdStatTpl m_Templ;	
	
	const int	GetCols() { return m_nCols; }
	LPCTSTR GetTitle() { return m_szTitle;	}
	LPCTSTR GetFootLeft() { return m_szFootLeft; }
protected:

	int			m_nRows;
	int			m_nCols;
	BOOL		m_bLoaded;
	string*		m_szNames;
	string*		m_szGpNames;
	double*		m_fValues;
	CString		m_szFootLeft;
	CString		m_szTitle;
	
	CEasyReport::CColInfo *m_pColInfo;
	// table info 
	// name col1nm, col2nm, col3nm, ...		colynm
	// nm1  v11		v12		v13		...		v1y
	// nm2	v21		v22		v23		...		v2y
	// ...  ...
	// nmx	vx1		vx2		vx3		...		vxy
	
	// m_nCols = y			// 曲线图个数
	// m_nRows = x 			// 每组曲线的数据个数
	// m_szNames = nm1 ... nmx;						//count[m_nRows], FieldName
	// m_szGpNames = col1nm ... coly nm;			//count[m_nCols], zero no use.
	// m_fValuse = v11, v21, v31, ... v1y, v2y .. vxy;  //count[m_nRows * m_nCols]
	
	// Generated message map functions
protected:
	int GetMonthDays(CTime tm);
	CString GetTimeSQL();
	void GetTimeData(CDatabase &db);
	BOOL GetMultiData(CDatabase &db);
	void GetCSArray(CString csStr, CStringArray& arStr);
	void SetReportData();
	void SetSize();
	int Clear();
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDSTATDOC_H__9D53912F_0CC1_45A3_800B_375E561FFF8D__INCLUDED_)
