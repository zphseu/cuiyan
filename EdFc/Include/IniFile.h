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
#include <iostream>
//##ModelId=3F5296110073
class CIniFile  
{
	//all private variables
private:
	//get value(CString) from str
	//##ModelId=3F5296110074
	CString GetValueString(LPCSTR sz);

	//find Section in ini file
	//##ModelId=3F529611007D
	BOOL FindSection(LPCSTR Section);

	//ini file
	//##ModelId=3F5296110080
	CStdioFile IniFile;

	//public variables
public:

	//public functions
public:
	
	//read value of int from ini file
	//##ModelId=3F5296110087
	BOOL GetItemInt(LPCSTR Section,LPCSTR Item,int & Value);
	
	//read value of CString from ini file
	//##ModelId=3F529611008B
	BOOL GetItemString(LPCSTR Section,LPCSTR Item,CString & Value);
	
	//write any string to ini file,"\n"
	//##ModelId=3F5296110093
	BOOL WriteString(LPCSTR str);
	
	//write Section to ini file
	//##ModelId=3F5296110095
	BOOL WriteSection(LPCSTR Section);
	
	//write Item and value of int to ini file
	//##ModelId=3F529611009B
	BOOL WriteItemInt(LPCSTR Item, int Value);
	
	//write Item and value of CString to ini file
	//##ModelId=3F529611009E
	BOOL WriteItemString(LPCSTR Item, LPCSTR Value);
	
	//open ini file for read
	//##ModelId=3F52961100A6
	BOOL OpenIniFileForRead(LPCSTR szName);
	
	//open ini file for write
	//##ModelId=3F52961100A8
	BOOL OpenIniFileForWrite(LPCSTR szName);
	
	//close ini file
	//##ModelId=3F52961100AF
	virtual void CloseIniFile(void);
	
	//default constructor
	//##ModelId=3F52961100B2
	CIniFile();
	
	//default destructor
	//##ModelId=3F52961100B3
	virtual ~CIniFile();

};

#endif // !defined(AFX_INIFILE_H__D6BE0D97_13A8_11D4_A5D2_002078B03530__INCLUDED_)
