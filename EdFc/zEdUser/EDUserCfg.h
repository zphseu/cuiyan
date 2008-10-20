#if !defined(AFX_BSUSERCFG_H__B6E17D8D_6225_42E5_9414_947F150A2401__INCLUDED_)
#define AFX_BSUSERCFG_H__B6E17D8D_6225_42E5_9414_947F150A2401__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SetUsr.h"

class CEdUserCfg  
{
public:
	BOOL ReadUsrCfg(LPCSTR szUsrName, LPCSTR szPassword);
	BOOL ValidateUsr(LPCSTR szUID, LPCSTR szPWD);
protected:
	BOOL ReadUsrCfgFile();
	BOOL ReadUsrCfgDB();
	BOOL ReadUsr(tagUsr &usr);
	BOOL ReadUsrDB(tagUsr &usr);
	BOOL ReadUsrFile(tagUsr &usr);
};

#endif // !defined(AFX_BSUSERCFG_H__B6E17D8D_6225_42E5_9414_947F150A2401__INCLUDED_)
