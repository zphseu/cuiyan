// PtEmtFiles.h: interface for the PtEmtFiles class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PTEMTFILES_H__5C6FC062_0202_43A8_B40D_2749A4C88DD0__INCLUDED_)
#define AFX_PTEMTFILES_H__5C6FC062_0202_43A8_B40D_2749A4C88DD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning(disable: 4786)

#include <complex>
#include <vector>
using namespace std;

#include "PtEmtDef.h"

enum FIELDTYPE { PARALLEL = 0, QUASIPARALLEL = 1, FIELDSIZE = 2 };

typedef complex<FLOAT> COMPLEX;

class PtEmtFiles  
{
public:
	PtEmtFiles() { 
		m_bGrayOK = FALSE;
		m_HasLoad = FALSE;
		m_FieldType = PARALLEL;
		m_HasLoad = LoadFileData();	
	}
	
	struct tagElement {
		short m_Position;
		short m_Material;
		short m_NodeIds[4];
	};
	
	typedef vector<FLOAT>	A_FLOAT;
	typedef vector<COMPLEX> A_COMPLEX;
	typedef vector<tagElement> A_ELEMENT;
	
	BOOL LBP();
	BOOL MNR(SHORT Mi, FLOAT Delta, FLOAT Larmat);
	BOOL LDWB(SHORT Mi, FLOAT Delta, FLOAT Larmat);
	BOOL LoadPFile(LPCTSTR szFileName);
	BOOL LoadGrayFile(LPCTSTR szFileName);
	BOOL IsGrayOK() { return m_bGrayOK; }
	
	FLOAT GetMGray(SHORT i) { 
		if (i < 0 || i >= m_MGray.size())	{
			i = 0;
		}
		return m_MGray[i]; 
	}

	COMPLEX&	GetNodes(SHORT elementId, SHORT nodeId)	{
		//拓扑文件中每一个单元都有四个节点，这四个节点的编号是
		//从1－1857（这是存在拓扑文件中的），而节点矩阵m_Nodes的
		//实际标号是从0-1856,因此引用时需要减去1。
		if (elementId < 0 || elementId >= m_Element.size())	{
			elementId = 0;
		}

		if (nodeId < 0 || nodeId >= 4)	{
			nodeId = 0;
		}

		return m_Nodes[m_Element[elementId].m_NodeIds[nodeId] - 1];
	}

	void SetFieldType(FIELDTYPE aType) {
		if (aType >= PARALLEL && aType < FIELDSIZE)	{
			m_FieldType = aType;
		}	else	{
			m_FieldType = PARALLEL;
		}
	}

protected:
	BOOL		m_bGrayOK;
	BOOL		m_HasLoad;
	FIELDTYPE	m_FieldType;
	typedef vector<A_COMPLEX> AA_COMPLEX;
	
	static A_COMPLEX	m_Nodes;
	static A_ELEMENT	m_Element;
	static AA_COMPLEX	m_PscoEmp[FIELDSIZE];
	static AA_COMPLEX	m_PscoFul[FIELDSIZE];
	static AA_COMPLEX	m_SData[FIELDSIZE];
	A_FLOAT		m_MGray;	
	AA_COMPLEX m_PData;	
	
	BOOL LoadFileData();
	BOOL LoadResFile(LPCTSTR szFileName, LPCTSTR szResName);
	BOOL LoadSensFile(LPCTSTR szFileName, AA_COMPLEX &pSData);
	BOOL LoadPSCOFile(LPCTSTR szFileName, AA_COMPLEX &pPsco);
	BOOL LoadCoordFile(LPCTSTR szFileName);
	BOOL LoadTopoFile(LPCTSTR szFileName);	
};

#endif // !defined(AFX_PTEMTFILES_H__5C6FC062_0202_43A8_B40D_2749A4C88DD0__INCLUDED_)
