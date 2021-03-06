// IniFile.cpp: implementation of the CIniFile class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"
#include <fstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////

//default constructor
//##ModelId=3F52961100B2
CIniFile::CIniFile()
{
}

//default destructor
//##ModelId=3F52961100B3
CIniFile::~CIniFile()
{
}

/////////////////////////////////////////////////////////////////////
// Public Functions
/////////////////////////////////////////////////////////////////////

//open ini file for read
//##ModelId=3F52961100A6
BOOL CIniFile::OpenIniFileForRead(LPCSTR szName)
{
	return IniFile.Open(szName, CFile::modeRead); 
}

//open ini file for write
//##ModelId=3F52961100A8
BOOL CIniFile::OpenIniFileForWrite(LPCSTR szName)
{
	return IniFile.Open(szName, CFile::modeCreate | CFile::modeWrite);
}

//##ModelId=3F52961100AF
void CIniFile::CloseIniFile()
{
	IniFile.Close();
}

//find Section in ini file
//##ModelId=3F529611007D
BOOL CIniFile::FindSection(LPCSTR Section)
{
	IniFile.SeekToBegin();
	CString str, csSection;
	csSection.Format("[%s]", Section);
	csSection.MakeLower();

	BOOL bFind=FALSE;
	BOOL bEnd=IniFile.ReadString(str);
	while(!bFind && bEnd)
	{
		str.MakeLower();
		str.TrimLeft();

		if(str.Find(csSection) ==0)
		{
			bFind=TRUE;
			break;
		}
		bEnd=IniFile.ReadString(str);
	}
	return bFind;
}

//write Section to ini file
//##ModelId=3F5296110095
BOOL CIniFile::WriteSection(LPCSTR Section)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		CString csTmp;
		csTmp.Format("[%s]\n", Section);
		IniFile.WriteString(csTmp);
		return TRUE;
	}
	else
		return FALSE;
}

//write Item and value of int to ini file
//##ModelId=3F529611009B
BOOL CIniFile::WriteItemInt(LPCSTR Item, int Value)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		CString str;
		str.Format("%s=%d\n",Item, Value);
		IniFile.WriteString(str);
		return TRUE;
	}
	else
		return FALSE;
}

//write Item and value of CString to ini file
//##ModelId=3F529611009E
BOOL CIniFile::WriteItemString(LPCSTR Item, LPCSTR Value)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		CString str;
		str.Format("%s=%s\n", Item, Value);
		IniFile.WriteString(str);
		return TRUE;
	}
	else
		return FALSE;
}

//read value of int from ini file
//##ModelId=3F5296110087
BOOL CIniFile::GetItemInt(LPCSTR Section, LPCSTR Item, int &Value)
{
	CFileStatus status;
	CString csItem(Item);
	csItem.MakeLower();

	if(IniFile.GetStatus(status))
	{
		if(FindSection(Section))
		{
			CString buf, sub, comsub;
			BOOL bFind=FALSE;
			BOOL bEnd=IniFile.ReadString(buf);
			while(!bFind && bEnd)
			{
				if (buf.GetLength() > 0 && buf[0] != ';')
				{
					sub=buf.Left(buf.Find("="));
					comsub = sub;
					comsub.MakeLower();
					
					if(buf.Find("[")<0 && !sub.IsEmpty() && comsub.Find(csItem)>=0)
					{
						sub=buf.Right(buf.GetLength()-buf.Find("=")-1);
						sub=GetValueString(sub);
						Value=atoi(sub);
						bFind=TRUE;
						break;
					}
				}

				bEnd=IniFile.ReadString(buf);
			}
			return bFind;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

//read value of CString from ini file
//##ModelId=3F529611008B
BOOL CIniFile::GetItemString(LPCSTR Section, LPCSTR Item, CString &Value)
{
	CFileStatus status;
	CString csItem(Item);
	csItem.MakeLower();
	
	if(IniFile.GetStatus(status))
	{
		if(FindSection(Section))
		{
			CString buf,sub, comsub;
			BOOL bFind=FALSE;
			BOOL bEnd=IniFile.ReadString(buf);
			while(!bFind && bEnd)
			{
				if (buf.GetLength() > 0 && buf[0] != ';')
				{				
					sub=buf.Left(buf.Find("="));
					comsub = sub;
					comsub.MakeLower();
					
					if(buf.Find("[")<0 && !sub.IsEmpty() && comsub.Find(csItem)>=0)
					{
						sub=buf.Right(buf.GetLength()-buf.Find("=")-1);
						Value=GetValueString(sub);
						bFind=TRUE;
						break;
					}
				}
				bEnd=IniFile.ReadString(buf);
			}
			
			return bFind;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

//get value(CString) from str
//##ModelId=3F5296110074
CString CIniFile::GetValueString(LPCSTR sz)
{
	CString str(sz);
	int length=str.GetLength();
	BOOL bSpace=TRUE;
	while(length && bSpace)
	{
		if(str[0]==' ')
			str=str.Right(--length);
		else
			bSpace=FALSE;
	}
	bSpace=TRUE;
	while(length && bSpace)
	{
		if(str[length-1]==' ')
			str=str.Left(--length);
		else
			bSpace=FALSE;
	}
	return str;
}

//write any string to ini file,"\n"
//##ModelId=3F5296110093
BOOL CIniFile::WriteString(LPCSTR str)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		IniFile.WriteString(str);
		return TRUE;
	}
	else
		return FALSE;
}


