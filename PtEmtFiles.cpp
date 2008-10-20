// PtEmtFiles.cpp: implementation of the PtEmtFiles class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PtEmtFiles.h"
#ifdef _AFXDLL
#include "PtEmt.h"
extern CPtEmtApp theApp;
#define INSTANCE	theApp.m_hInstance
#else
#define INSTANCE	_Module.m_hInst
#endif

//const SHORT PSCO = 0;
//const FLOAT ConveyGray = 1.0;
//const FLOAT SpaceGray = 0.0;

PtEmtFiles::A_COMPLEX	PtEmtFiles::m_Nodes;
PtEmtFiles::A_ELEMENT	PtEmtFiles::m_Element;
PtEmtFiles::AA_COMPLEX	PtEmtFiles::m_PscoEmp[FIELDSIZE];
PtEmtFiles::AA_COMPLEX	PtEmtFiles::m_PscoFul[FIELDSIZE];
PtEmtFiles::AA_COMPLEX	PtEmtFiles::m_SData[FIELDSIZE];

BOOL PtEmtFiles::LoadFileData()
{
	if (TRUE == m_HasLoad) {
		return TRUE;
	}

	TCHAR szFileName[MAX_PATH];
	GetTempPath(MAX_PATH, szFileName);
	GetTempFileName(szFileName, _T("PtEmtDyt"), 0, szFileName);
	
	// COORD DATA
	LoadResFile(szFileName, _T("FILE_COORD"));
	LoadCoordFile(szFileName);

	// TOPO DATA
	LoadResFile(szFileName, _T("FILE_TOPO"));
	LoadTopoFile(szFileName);

	// PAL EMP DATA
	LoadResFile(szFileName, _T("FILE_PSCOEMP"));
	LoadPSCOFile(szFileName, m_PscoEmp[PARALLEL]);
	// PAL FUL DATA
	LoadResFile(szFileName, _T("FILE_PSCOFUL"));
	LoadPSCOFile(szFileName, m_PscoFul[PARALLEL]);
	// QUA-PAL EMP DATA
	LoadResFile(szFileName, _T("FILE_PSCOEMP_Q"));
	LoadPSCOFile(szFileName, m_PscoEmp[QUASIPARALLEL]);
	// QUA-PAL FUL DATA
	LoadResFile(szFileName, _T("FILE_PSCOFUL_Q"));
	LoadPSCOFile(szFileName, m_PscoFul[QUASIPARALLEL]);

	// PAL SENSITIVITY DATA
	LoadResFile(szFileName, _T("FILE_S"));
	LoadSensFile(szFileName, m_SData[PARALLEL]);

	// QUA-PAL SENSITIVITY DATA
	LoadResFile(szFileName, _T("FILE_S_Q"));
	LoadSensFile(szFileName, m_SData[QUASIPARALLEL]);

	DeleteFile(szFileName);

	for (SHORT i = 0; i < TotalElement; i++)
		m_MGray.push_back(0);

	return TRUE;
}

BOOL PtEmtFiles::LoadCoordFile(LPCTSTR szFileName)
{
	FILE *fp = _tfopen(szFileName, _T("rb"));
	FLOAT real, imag;
	m_Nodes.clear();
	for(SHORT i = 0; i < TotalNode; i++)	{
		fread(&real, sizeof(float), 1, fp);
		fread(&imag, sizeof(float), 1, fp);			
		m_Nodes.push_back(COMPLEX(real, imag));
	}
	fclose(fp);
	return TRUE;
}


BOOL PtEmtFiles::LoadTopoFile(LPCTSTR szFileName)
{
	tagElement t;
	m_Element.clear();
	FILE *fp = _tfopen(szFileName, _T("rb"));
	for(SHORT i = 0; i < TotalElement; i++) {
		fread(&t, sizeof(tagElement), 1, fp);
		m_Element.push_back(t);
	}
	fclose(fp);
	return TRUE;
}

BOOL PtEmtFiles::LoadResFile(LPCTSTR szFileName, LPCTSTR szResName)
{
	BOOL bReturn = FALSE;
	HRSRC res = FindResource (INSTANCE, szResName, _T("PtEmtFile"));
	HGLOBAL gl = LoadResource (INSTANCE, res);
	LPVOID lp = LockResource(gl);
	HANDLE fp = CreateFile(szFileName ,GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	DWORD len = SizeofResource (INSTANCE, res);
	bReturn = WriteFile (fp,lp, len, &len, NULL);
	CloseHandle (fp);
	FreeResource (gl);
	return bReturn;
}

BOOL PtEmtFiles::LoadPFile(LPCTSTR szFileName)
{
	FILE *fp = _tfopen(szFileName, _T("rt"));
	if (NULL == fp)	{
		return FALSE;
	}
	
	FLOAT real, imag;
	m_PData.clear();
	for(SHORT i = 0; i < TotalDirNum; i++)	{
		A_COMPLEX ATemp;
		for(SHORT j = 0; j < DetectorNum; j++)	{
			_ftscanf(fp, _T("%f,%f\n"), &real, &imag);
			ATemp.push_back(COMPLEX(real, imag));
		}
		m_PData.push_back(ATemp);
	}
	fclose(fp);
	return TRUE;
}

BOOL PtEmtFiles::LoadGrayFile(LPCTSTR szFileName)
{
	m_bGrayOK = FALSE;
	FILE *fp = _tfopen(szFileName, _T("rt"));
	if (NULL == fp)	{
		return FALSE;
	}
	
	UINT temp;
	FLOAT fTemp;
	m_MGray.clear();
	for (SHORT i = 0; i < TotalElement; i++) {
		_ftscanf(fp, _T("%d    %f\n"), &temp, &fTemp);
		if (fTemp < 0)	{
			fTemp = 0.0;
		}
		m_MGray.push_back(fTemp);
	}
	fclose(fp);

	m_bGrayOK = TRUE;
	return m_bGrayOK;
}

BOOL PtEmtFiles::LoadPSCOFile(LPCTSTR szFileName, AA_COMPLEX& psco)
{
	FILE *fp = _tfopen(szFileName, _T("rb"));
	FLOAT real, imag;
	psco.clear();
	for(SHORT i = 0; i < TotalDirNum; i++)	{
		A_COMPLEX ATemp;
		for(SHORT j = 0; j < DetectorNum; j++)	{
			fread(&real, sizeof(float), 1, fp);
			fread(&imag, sizeof(float), 1, fp);
			ATemp.push_back(COMPLEX(real, imag));
		}
		psco.push_back(ATemp);
	}
	fclose(fp);
	return TRUE;
}

BOOL PtEmtFiles::LoadSensFile(LPCTSTR szFileName, AA_COMPLEX& SData)
{
	FILE *fp = _tfopen(szFileName, _T("rb"));
	FLOAT real, imag;
	SData.clear();
	for(SHORT i = 0; i < InsideElement; i++)	{
		A_COMPLEX ATemp;
		for(SHORT j = 0; j < TotalDetectNum; j++)	{
			fread(&real, sizeof(float), 1, fp);
			fread(&imag, sizeof(float), 1, fp);
			ATemp.push_back(COMPLEX(real, imag));
		}
		SData.push_back(ATemp);
	}
	fclose(fp);
	return TRUE;
}

BOOL PtEmtFiles::LBP()
{
	m_bGrayOK = FALSE;

	COMPLEX NormP[TotalDirNum][DetectorNum];
	for(SHORT j = 0; j < TotalDirNum; j++) 
	{
		for(SHORT k = 0; k < DetectorNum; k++)
		{
			COMPLEX T1 = m_PscoEmp[m_FieldType][j][k];
			COMPLEX T2 = m_PscoFul[m_FieldType][j][k];
			NormP[j][k] = (m_PData[j][k] - T1) / (T2 - T1);
		}
	}
		
	FLOAT temp1=0, temp2=0;
	COMPLEX temp= COMPLEX(0.0, 0.0);
	for(SHORT i = 0; i< TotalElement; i++)
	{
		m_MGray[i] = 0;
		if(i < InsideElement)
		{
			temp1 = temp2 = 0;
			for(SHORT j = 0;j < TotalDirNum; j++)	
			{
				for(SHORT k= 0;k < DetectorNum; k++)		
				{
					temp = m_SData[m_FieldType][i][j*DetectorNum+k];
					temp1 += real(NormP[j][k] * temp);
					temp2 += abs(temp);
				}
			}

			temp1 /= temp2;
			if (temp1 < 0)	{
				temp1 = 0.0;
			}
			m_MGray [i] = temp1;
		}
	}

	m_bGrayOK = TRUE;
	return m_bGrayOK;
}

BOOL PtEmtFiles::LDWB(SHORT Mi, FLOAT Delta, FLOAT Larmat)
{
	m_bGrayOK = FALSE;
	COMPLEX pdif1[TotalDetectNum], pdif0[TotalDetectNum], NormP[TotalDetectNum];

	for(SHORT i = 0 ; i < TotalElement; i++)
		m_MGray[i] = 0;

	for(i = 0 ; i < TotalDetectNum; i++)
		pdif0[i] = pdif1[i] = NormP[i] = 0;
	
	for(i =0; i < TotalDetectNum; i++)
	{
		for(SHORT j = 0; j < TotalDirNum; j++)
		{
			for(SHORT k = 0; k < DetectorNum; k++)
			{
				COMPLEX T1 = m_PscoEmp[m_FieldType][j][k];
				COMPLEX T2 = m_PscoFul[m_FieldType][j][k];
				NormP[i] = (m_PData[j][k]-T1) / (T2 - T1);
			}
		}
	}
	
	for(SHORT l = 1; l <= Mi; l++)
	{
		for(SHORT j=0 ; j < TotalDetectNum; j++)
		{
			COMPLEX sum = COMPLEX(0.0, 0.0);
			for(i=0 ; i < InsideElement; i++)
				sum += m_SData[m_FieldType][i][j] * m_MGray[i];
			pdif1[j] = NormP[j] - sum; //better
		}
		
		FLOAT Qdif = 0;
		for(j = 0; j < TotalDetectNum; j++)
		{
			FLOAT tt = abs(pdif1[j] - pdif0[j]);
			tt = tt * tt;
			Qdif += tt;
		}
		
		if(l >= Mi)	{
			break;
		}

		if(Qdif <= Delta * Delta)	{
			break;
		}

		for(j = 0; j < TotalDetectNum; j++)
			pdif0[j] = pdif1[j];
		
		for(i = 0; i < InsideElement; i++)
		{
			COMPLEX sum = COMPLEX(0.0, 0.0);
			FLOAT sum1 = 0;
			for(j = 0; j < TotalDetectNum; j++)
			{
				sum = sum + m_SData[m_FieldType][i][j] * pdif1[j];
				sum1 += abs(m_SData[m_FieldType][i][j]);
			}
			m_MGray[i] += Larmat * real(sum)/sum1;  //(4) similar with (1)
			if(m_MGray[i] < 0)	{
				m_MGray[i] = 0.0;
			}	else if (m_MGray[i] > 1.0)	{
				m_MGray[i] = 1.0;
			}
		}
	}
	
	m_bGrayOK = TRUE;
	return m_bGrayOK;
}

BOOL PtEmtFiles::MNR(SHORT Mi, FLOAT Delta, FLOAT Larmat)
{	
	m_bGrayOK = FALSE;
	//////////////////////////////////////////////////////////////////////////
//	COMPLEX pdif1[TotalDetectNum], pdif0[TotalDetectNum], NormP[TotalDetectNum];
	float Delta_Gray[InsideElement];//hm add
	COMPLEX Delta_P[TotalDetectNum], S_Multi_ST[InsideElement][InsideElement], S_Mul_ST_Inv[InsideElement][InsideElement]; //hm add
	COMPLEX S_ST_Inv_S[InsideElement][TotalDetectNum];//hm add

	for(SHORT i = 0 ; i < TotalElement; i++)
		m_MGray[i] = 0;

//	for(i = 0 ; i < TotalDetectNum; i++)
//		pdif0[i] = pdif1[i] = NormP[i] = 0;
	
/*	for(i =0; i < TotalDetectNum; i++)
	{
		for(SHORT j = 0; j < TotalDirNum; j++)
		{
			for(SHORT k = 0; k < DetectorNum; k++)
			{
				COMPLEX T1 = m_PscoEmp[m_FieldType][j][k];
				COMPLEX T2 = m_PscoFul[m_FieldType][j][k];
				NormP[i] = (m_PData[j][k]-T1) / (T2 - T1);
			}
		}
	}*/
	
	//hm add: to give initial value to Delta_P
	for(i =0; i < TotalDetectNum; i++)
	{
		Delta_P[i] = m_PData[i];
	}

	for(SHORT l = 1; l <= Mi; l++)
	{
			
		FLOAT Qdif = 0;
		for(SHORT j = 0; j < TotalDetectNum; j++)
		{
			FLOAT tt = abs(Delta_P[j]);
			tt = tt * tt;
			Qdif += tt;
		}
		
		if(l >= Mi)	{
			break;
		}

		if(Qdif <= Delta * Delta)	{
			break;
		}


	//	for(j = 0; j < TotalDetectNum; j++)
	//		pdif0[j] = pdif1[j];
		
		for(i = 0; i < InsideElement; i++)
		{
			for(j = 0; j < InsideElement; j++)
			{
				for(SHORT k=0; k < TotalDetectNum; k++)
				{
					S_Multi_ST[i][j] += m_SData[m_FieldType][i][k] * m_SData[j][k];
				}
			}
			S_Multi_ST[i][i] += Larmat;		
		}//hm 求St*S+rI存于S_Multi_ST中, 1024*1024
		
		//求上述矩阵的逆，可引用求逆过程，结果存于S_Mul_ST_Inv, 1024*1024
		for()
		{

		}
		
		//S_ST_Inv_S:1024*128
		for(i = 0; i < InsideElement; i++)
		{
			for(j = 0; j < TotalDetectNum; j++)
			{
				for(k = 0; k < InsideElement; k++)
				{
					S_ST_Inv_S[i][j] += S_Mul_ST_Inv[i][k] * m_SData[m_FieldType][k][j];
				}
			}
			
		}
	
		//Delta_P:128*1
		for(i =0; i < TotalDetectNum; i++)
		{
			COMPLEX temp = COMPLEX(0.0, 0.0);
			for(k =0; k < InsideElement; k++)
			{
				temp += m_SData[m_FieldType][k][i] * m_MGray[k]; 
			}
			Delta_P[i] = temp - m_PData[i];
		}
		
		for(i = 0; i < InsideElement; i++)
		{
			for(j =0; j < TotalDetectNum; j++)
			{
				Delta_Gray[i] += - S_ST_Inv_S[i][j] * Delta_P[j];
			}
			m_MGray[i] += Delta_Gray[i]; 
		}

		if(m_MGray[i] < 0)	{
			m_MGray[i] = 0.0;
			}	else if (m_MGray[i] > 1.0)	{
			m_MGray[i] = 1.0;
			}
	}
	
	//////////////////////////////////////////////////////////////////////////
	m_bGrayOK = TRUE;
	return m_bGrayOK;
}
