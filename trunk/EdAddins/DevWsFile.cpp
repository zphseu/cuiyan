// DevWsFile.cpp: implementation of the CDevWsFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdAddins.h"
#include "DevWsFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CDevSrcFile
//////////////////////////////////////////////////////////////////////

UINT CDevSrcFile::FindComment(CString sLine, LPCTSTR sComment, BOOL bIgnoreStr)
{
    if (!bIgnoreStr)
    {
        int pos, len = sLine.GetLength();
        bool bIsStr = false;

        for (pos = 0; pos < len; pos++)
        {
            if (sLine[pos] == '\\')
            {
                sLine.SetAt(pos, '!');
                if (pos + 1 < len)
                    sLine.SetAt(++pos , '!');
            }
            else
                if (sLine[pos] == '"')
                    bIsStr = !bIsStr;
                else
                    if (bIsStr)
                        sLine.SetAt(pos, '!');
        }
    }

    return sLine.Find(sComment);
}

void CDevSrcFile::GetStat()
{
	CString cStr;

	if (!isSrcFile)
		return;

	
	CStdioFile f;
	if (!f.Open(m_strfn, CFile::modeRead | CFile::typeText))
	{
		AfxMessageBox("Can not open " + m_strfn + " file.", MB_OK);
		return;
	}

	bool bIsCodeLine, bIsCommentLine, bIsComment = false;
	int pos, pos2;
	while (f.ReadString(cStr))
	{
		lines++;
		bIsCodeLine = bIsCommentLine = false;
		
process:
		cStr.TrimLeft();
		cStr.TrimRight();
		if (cStr.IsEmpty())
		{
			if (bIsCodeLine  ||  bIsCommentLine)
			{
				if (bIsCodeLine)
				{
					codelines++;
					if (bIsCommentLine)
						mixedlines++;
				}
				if (bIsCommentLine)
					commentlines++;
			}
			else
				blanklines++;
		}
		else
		{
			if (bIsComment)
			{
				bIsCommentLine = true;
				if ((pos = FindComment(cStr, "*/", true)) >= 0)
				{
					bIsComment = false;
					cStr = cStr.Mid(pos + 2);
				}
				else
				{
					cStr.Empty();
				}
				goto process;
			}
			else
			{
				pos2 = FindComment(cStr, "//");
				if ((pos = FindComment(cStr, "/*")) >= 0  &&
					(pos2 < 0  ||  pos < pos2))
				{
					if (pos > 0)
					{
						bIsCodeLine = true;
					}
					bIsCommentLine = true;
					bIsComment = true;
					goto process;
				}
				else
				{
					if (pos2 >= 0)
					{
						if (pos2 > 0)
						{
							bIsCodeLine = true;
						}
						bIsCommentLine = true;
						cStr.Empty();
						goto process;
					}
					else
					{
						cStr.Empty();
						bIsCodeLine = true;
						goto process;
					}
				}
			}
		}
	}
	
	f.Close();	
	return;
}

//////////////////////////////////////////////////////////////////////
// CDevPrjFile
//////////////////////////////////////////////////////////////////////

CDevPrjFile::CDevPrjFile()
{
	numFile = 0;
	pFilelist = NULL;
}

CDevPrjFile::~CDevPrjFile()
{
	if (pFilelist != NULL)
		delete [] pFilelist;
}

void CDevPrjFile::RefreshFileList(CString exts)
{
	CStringList line;
	CString one;
	CStdioFile f;

	if (!f.Open(m_strfn, CFile::modeRead | CFile::typeText))
	{
		AfxMessageBox("Couln not open " + m_strfn + " file.", MB_OK);
		return;
	}
	
	CString flag = _T("SOURCE=");
	CString flagNo = _T("SOURCE=\"$(");
	while(f.ReadString(one))
	{
		if ( one.Find(flag) == 0 && one.Find(flagNo) != 0 )
			line.AddTail(one);
	}

	f.Close();
	pFilelist = new CDevSrcFile[line.GetCount()];
	POSITION pos = line.GetHeadPosition();
	numFile = line.GetCount();
	for (UINT i = 0; i < numFile; i++)
	{
		one = line.GetNext(pos);
		one = m_strPath + one.Right(one.GetLength() - flag.GetLength());
		one.Replace("\\.\\", "\\");
		while (one.Find("\\..\\") > 0)
		{
			int n = one.Find("\\..\\");
			CString tmp = one.Left(n);
			one = one.Right(one.GetLength() - n - 3);
			tmp = tmp.Left(tmp.ReverseFind('\\'));
			one = tmp + one;
		}
		pFilelist[i].SetPathName(one);
		CString tmp = pFilelist[i].GetFileExt() +";";
		pFilelist[i].isSrcFile = (exts.Find(tmp) >= 0);
	}
	return;
}

void CDevPrjFile::GetStat()
{
	for (UINT i = 0; i < numFile; i++)
		pFilelist[i].GetStat();
	
	for (i = 0; i < numFile; i++)
	{
		lines += pFilelist[i].lines;
		commentlines += pFilelist[i].commentlines;
		codelines += pFilelist[i].codelines;
		mixedlines += pFilelist[i].mixedlines;
		blanklines += pFilelist[i].blanklines;
	}
}

//////////////////////////////////////////////////////////////////////
// CDevWsFile
//////////////////////////////////////////////////////////////////////

CDevWsFile::CDevWsFile()
{
	numProj = 0;
	pProjlist = NULL;
	srcext = _T("");
}

CDevWsFile::~CDevWsFile()
{
	if (pProjlist != NULL)
		delete [] pProjlist;
}

BOOL CDevWsFile::SetParam(CString regkey)
{
	CRegKey reg;
	BOOL b = FALSE;
	if (reg.Create(HKEY_CURRENT_USER, regkey) == ERROR_SUCCESS)
	{
		reg.SetValue(srcext, "DevDswSrcExt");
		b = TRUE;
	}
	
	reg.Close();
	return b;
}

BOOL CDevWsFile::GetParam(CString regkey)
{
	CRegKey reg;
	BOOL b = FALSE;
	char tmp[2048];
	DWORD i;
	if ( reg.Create(HKEY_CURRENT_USER, regkey) == ERROR_SUCCESS
		&& reg.QueryValue(tmp, "DevDswSrcExt", &i) == ERROR_SUCCESS )
			srcext = tmp;
	
	reg.Close();
	return b;
}

void CDevWsFile::GetStat()
{
	for (long i = 0; i < numProj; i++)
		pProjlist[i].GetStat();
	
	for (i = 0; i < numProj; i++)
	{
		lines += pProjlist[i].lines;
		commentlines += pProjlist[i].commentlines;
		codelines += pProjlist[i].codelines;
		mixedlines += pProjlist[i].mixedlines;
		blanklines += pProjlist[i].blanklines;
	}
}


void CDevWsFile::RefreshFileList(IApplication* pApp)
{
	CComPtr<IDispatch> pDisp;
	CComQIPtr<IProjects, &IID_IProjects> pProjects;
	if(!SUCCEEDED(pApp->get_Projects(&pDisp)))
		return;
	
	pProjects = pDisp;
	pDisp = NULL;
	
	CString prjName;
	pProjects->get_Count(&numProj);
	pProjlist = new CDevPrjFile[numProj];
	
	CComPtr<IUnknown> pUnk;
	CComQIPtr<IEnumVARIANT, &IID_IEnumVARIANT> pNewEnum;
	if (!SUCCEEDED(pProjects->get__NewEnum(&pUnk)) || pUnk == NULL)
		return;
	
	pNewEnum = pUnk;
	VARIANT varProject;
	CComQIPtr<IGenericProject, &IID_IGenericProject> pProject;
	for(UINT i = 0; pNewEnum->Next(1, &varProject, NULL) == S_OK; i++)
	{
		ASSERT (varProject.vt == VT_DISPATCH);
		pProject = varProject.pdispVal;
		VariantClear(&varProject);
		CComBSTR bstrFullName;
		pProject->get_FullName(&bstrFullName);
		prjName = bstrFullName;
		pProjlist[i].SetPathName(prjName);
		pProjlist[i].RefreshFileList(srcext);
	}
	
	return;
}
