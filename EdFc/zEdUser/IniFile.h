// IniFile.h: interface for the CIniFile class.
// Written by: Gao Tong
// Email: martianfighter@yahoo.com.cn
// You may use this class/code as you wish in your programs.  Feel free to distribute it, and
// email suggested changes to me.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__D6BE0D97_13A8_11D4_A5D2_002078B03530__INCLUDED_)
#define AFX_INIFILE_H__D6BE0D97_13A8_11D4_A5D2_002078B03530__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include <iostream.h>
class CIniFile  
{
	//all private variables
private:
	//get value(CString) from str
	CString GetValueString(LPCSTR sz);

	//find Section in ini file
	BOOL FindSection(LPCSTR Section);

	//ini file
	CStdioFile IniFile;

	//public variables
public:

	//public functions
public:
	
	//read value of int from ini file
	BOOL GetItemInt(LPCSTR Section,LPCSTR Item,int & Value);
	
	//read value of CString from ini file
	BOOL GetItemString(LPCSTR Section,LPCSTR Item,CString & Value);
	
	//write any string to ini file,"\n"
	BOOL WriteString(LPCSTR str);
	
	//write Section to ini file
	BOOL WriteSection(LPCSTR Section);
	
	//write Item and value of int to ini file
	BOOL WriteItemInt(LPCSTR Item, int Value);
	
	//write Item and value of CString to ini file
	BOOL WriteItemString(LPCSTR Item, LPCSTR Value);
	
	//open ini file for read
	BOOL OpenIniFileForRead(LPCSTR szName);
	
	//open ini file for write
	BOOL OpenIniFileForWrite(LPCSTR szName);
	
	//close ini file
	virtual void CloseIniFile(void);
	
	//default constructor
	CIniFile();
	
	//default destructor
	virtual ~CIniFile();

};

#endif // !defined(AFX_INIFILE_H__D6BE0D97_13A8_11D4_A5D2_002078B03530__INCLUDED_)
