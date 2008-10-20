// SSD.cpp: implementation of the CSSD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysInfo.h"
#include "SSD.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//following emuu CRYPTTYPE
LPCTSTR CSSD::szCryptType[] = {
	"WINCRYPTAPI",
	"CRYPTRC4",
	"CRC_ADLER",
	NULL
};

CSSD::CSSD(CRYPTTYPE crypt, BOOL inSysInfo) : m_Crypt(crypt)
{ 
	m_ssd.m_szProduct = GetProductInfo();
	m_inSysInfo = inSysInfo;
	if (m_inSysInfo) {
		CSysInfo si;
		m_ssd.m_szSysInfo = si.GetSysInfo();
	}
}

CSSD::CSSD(SSD ssd, CRYPTTYPE crypt, BOOL inSysInfo) : m_Crypt(crypt), m_ssd(ssd)
{ 
	m_ssd.m_szProduct = GetProductInfo(); 
	m_inSysInfo = inSysInfo;
	if (m_inSysInfo) {
		CSysInfo si;
		m_ssd.m_szSysInfo = si.GetSysInfo();
	}
}

#include "Registry.h"
BOOL CSSD::SaveToReg(CString RegPath)
{
	CRegistry Reg;
	
	if (RegPath.IsEmpty())
		RegPath = GetRegPath();

	if (m_ssd.m_szName.IsEmpty() || m_ssd.m_szEmail.IsEmpty() 
		|| m_ssd.m_szSerial.IsEmpty())
		return FALSE;

	if (!Reg.VerifyKey(HKEY_LOCAL_MACHINE, RegPath) &&
		!Reg.CreateKey(HKEY_LOCAL_MACHINE, RegPath) )
			return FALSE;
	
	if (!Reg.Open(HKEY_LOCAL_MACHINE, RegPath))
		return FALSE;

	if (!Reg.WriteString(_T("Name"), m_ssd.m_szName) ||
		!Reg.WriteString(_T("Email"), m_ssd.m_szEmail) ||
		!Reg.WriteString(_T("SSD"), m_ssd.m_szSerial) )
		return FALSE;
	
	Reg.Close();

	return TRUE;
}

BOOL CSSD::LoadFromReg(CString RegPath)
{
	CRegistry Reg;
	
	if (RegPath.IsEmpty())
		RegPath = GetRegPath();

	if (!Reg.Open(HKEY_LOCAL_MACHINE, RegPath))
		return FALSE;
	
	if (!Reg.ReadString(_T("Name"), m_ssd.m_szName) ||
		!Reg.ReadString(_T("Email"), m_ssd.m_szEmail) ||
		!Reg.ReadString(_T("SSD"), m_ssd.m_szSerial) )
		return FALSE;

	Reg.Close();
	
	return TRUE;
}

#define ARACKEY _T("SSDSDKISASECURITYMETHODTOSAFEGUARDSOFTWARE!")
#include "ARACrypt.h"
BOOL CSSD::SaveToFile(CString fn)
{
	ARACrypt arac;
	CString szKey = ARACKEY;
	arac.TransformString(ARACKEY, szKey);

	SSD ssd = m_ssd;
	try 
	{
		CFile f(fn, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		CArchive ar(&f, CArchive::store);
		
		arac.TransformString(szKey, ssd.m_szName);
		arac.TransformString(szKey, ssd.m_szEmail);
		arac.TransformString(szKey, ssd.m_szProduct);
		arac.TransformString(szKey, ssd.m_szSysInfo);
		arac.TransformString(szKey, ssd.m_szSerial);

		ar	<< (int)m_Crypt;
		ar	<< ssd.m_szName << ssd.m_szEmail << ssd.m_szProduct 
			<< ssd.m_szSysInfo << ssd.m_szSerial;

		ar.Close();
		f.Close();
	}
	catch (CException *e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CSSD::LoadFromFile(CString fn)
{
	ARACrypt arac;
	CString szKey = ARACKEY;
	arac.TransformString(ARACKEY, szKey);
	
	try 
	{
		CFile f(fn, CFile::modeRead | CFile::typeBinary);
		CArchive ar(&f, CArchive::load);
		
		int crypt;
		ar	>> crypt; m_Crypt = (CRYPTTYPE) crypt;
		ar	>> m_ssd.m_szName >> m_ssd.m_szEmail >> m_ssd.m_szProduct 
			>> m_ssd.m_szSysInfo >> m_ssd.m_szSerial;
		
		arac.TransformString(szKey, m_ssd.m_szName);
		arac.TransformString(szKey, m_ssd.m_szEmail);
		arac.TransformString(szKey, m_ssd.m_szProduct);
		arac.TransformString(szKey, m_ssd.m_szSysInfo);
		arac.TransformString(szKey, m_ssd.m_szSerial);
		
		ar.Close();
		f.Close();
	}
	catch (CException *e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
	return TRUE;
}

#include "RC4.h"
#include "Crc32.h"
#include "CryptString.h"
BOOL CSSD::CheckValidate()
{
	BOOL bRet = FALSE;

	switch(m_Crypt)
	{
	case WINCRYPTAPI: {
		CCryptString szCrypt = m_ssd.m_szSerial;
		szCrypt.InDecrypt();
		bRet = (szCrypt.Compare(m_ssd.m_szName 
				+ m_ssd.m_szProduct + m_ssd.m_szEmail + m_ssd.m_szSysInfo)== NULL);
		break;
		}
		
	default: {// CRC_ADLER, CRYPTRC4
		CString Serial = m_ssd.m_szSerial;
		GenSerial();
		bRet = (Serial == m_ssd.m_szSerial);
		m_ssd.m_szSerial = Serial;
		break;
		}
	}

	return bRet;
}

BOOL CSSD::GenSerial()
{
	switch(m_Crypt)
	{
	case WINCRYPTAPI: {	// WINCRYPT
		CCryptString str = m_ssd.m_szName + m_ssd.m_szProduct + m_ssd.m_szEmail
			 + m_ssd.m_szSysInfo;
		str.InCrypt();
		m_ssd.m_szSerial = str;
		break;
		}

	case CRYPTRC4: {	// RC4
		m_ssd.m_szSerial = m_ssd.m_szName + m_ssd.m_szEmail;
		RC4 rc4(m_ssd.m_szProduct + m_ssd.m_szSysInfo);
		rc4.Crypt(m_ssd.m_szSerial);
		break;
		}

	default: { // CRC_ALDER
		CCRC32 crc;
		crc.From(m_ssd.m_szName, m_ssd.m_szName.GetLength());
		crc.From(m_ssd.m_szEmail, m_ssd.m_szEmail.GetLength(), true);
		crc.From(m_ssd.m_szProduct, m_ssd.m_szProduct.GetLength(), true);
		crc.From(m_ssd.m_szSysInfo, m_ssd.m_szSysInfo.GetLength(), true);

		CAdler32 adler;
		crc.From(m_ssd.m_szSysInfo, m_ssd.m_szSysInfo.GetLength());
		adler.From(m_ssd.m_szProduct, m_ssd.m_szProduct.GetLength(), true);
		adler.From(m_ssd.m_szEmail, m_ssd.m_szEmail.GetLength(), true);
		adler.From(m_ssd.m_szName, m_ssd.m_szName.GetLength(), true);
		m_ssd.m_szSerial.Format("%02X-%02X", crc.GetCRC(), adler.GetAdler32());
		break;
		}
	}

	return TRUE;
}

#include "ProductInfo.h"
CString CSSD::GetRegPath()
{
	CProductInfo pi;
	CString RegPath;
	if (pi.GetCompanyName().IsEmpty()) {
		if  (pi.GetProductName().IsEmpty())
			RegPath.Format(_T("Software\\SSDSSK%d"), rand() % 1000);
		else
			RegPath.Format(_T("Software\\%s"), pi.GetProductName());
	} else {
		if (pi.GetProductName().IsEmpty())
			RegPath.Format(_T("Software\\%s"), pi.GetCompanyName());
		else
			RegPath.Format(_T("Software\\%s\\%s"), pi.GetCompanyName(), pi.GetProductName());
	}
	
	ASSERT(!RegPath.IsEmpty());
	return RegPath;
}

CString CSSD::GetProductInfo()
{
	CProductInfo pi;
	CString szProduct;
	szProduct.Format(_T("%s %s %s"), pi.GetProductName(), pi.GetVersion(),
		pi.GetSpecBuild());

	ASSERT(!szProduct.IsEmpty());
	return szProduct;
}

#include "DlgUsrReg.h"
BOOL CSSD::LoadFromDlg()
{
	CWnd* pParentWnd = AfxGetMainWnd();
	CDlgUsrReg dlg(pParentWnd);
	dlg.m_User = m_ssd;
	if (dlg.DoModal() == IDOK)	{
		m_ssd = dlg.m_User;
		SaveToReg();
		if (CheckValidate())
			return TRUE;
		else
			AfxMessageBox(_T("This is a invalid key"));
	}
	
	return FALSE;
}

#include "DlgSend.h"
BOOL CSSD::DlgSendForKey(CString email)
{
	CWnd* pParentWnd = AfxGetMainWnd();
	CDlgSend dlg(pParentWnd);
	dlg.m_User = m_ssd;
	if (dlg.DoModal() == IDOK)	{
		m_ssd = dlg.m_User;

		TCHAR lpBuffer[MAX_PATH];
		//GetTempPath(MAX_PATH, lpBuffer);
		GetModuleFileName(NULL, lpBuffer, MAX_PATH);
		CString szFileName = lpBuffer;
		szFileName = szFileName.Left(szFileName.ReverseFind('\\') + 1);
		szFileName += m_ssd.m_szName;
		szFileName += _T(".forkey");
		
		if (!SaveToFile(szFileName))
			return FALSE;
		
		return SendMail(email, szFileName);
		DeleteFile(szFileName);

		return TRUE;
	}
	
	return FALSE;
}

#include "DlgLoad.h"
BOOL CSSD::DlgLoadFromFile()
{
	CWnd* pParentWnd = AfxGetMainWnd();
	CDlgLoad dlg(pParentWnd);
	if (dlg.DoModal() == IDOK )
		return LoadFromFile(dlg.m_FileName);

	return FALSE;
}

#include "DlgOptReg.h"
BOOL CSSD::verify(CString email)
{
	if (LoadFromReg() && CheckValidate())
		return TRUE;
	
	BOOL bRet = FALSE;
	CDlgOptReg dlg;
	if (dlg.DoModal() == IDOK) {
		switch(dlg.m_nOption) {
		case 0:
			if (LoadFromDlg() && CheckValidate())	bRet = TRUE;
			break;
		case 1:
			if (DlgLoadFromFile() && CheckValidate())	bRet = TRUE;
			break;
		case 2:
			if (DlgSendForKey(email))	bRet = FALSE;
			break;
		default:
			bRet = FALSE;
			break;
		}
		SaveToReg();
	}

	return bRet;
}

#include <mapi.h>
BOOL CSSD::SendMail(CString email, CString attachmentfile)
{
	HMODULE hMod=LoadLibrary("MAPI32.DLL"); 
	if(hMod == NULL) 
		return FALSE;
	
	try
	{
		ULONG (PASCAL *lpfnSendMail) (ULONG, ULONG, MapiMessage*, FLAGS, ULONG); 
		(FARPROC &)lpfnSendMail= GetProcAddress(hMod, "MAPISendMail"); 
		if(lpfnSendMail == NULL) 
			throw -1;
		
		MapiFileDesc attachment= 	{ 
			0,				// ulReserved, must be 0 
			0,				// no flags; this is a data file 
			(ULONG) - 1,	// position not specified 
			attachmentfile.GetBuffer(0),		// pathname, if original filename is NULL, this is the filename 
			NULL,			// original filename 
			NULL 
		}; // MapiFileTagExt unused 
		
		CString szUser = email;
		szUser = szUser.Left(szUser.Find('@'));
		MapiRecipDesc recip={ 0, MAPI_TO, szUser.GetBuffer(0), email.GetBuffer(0), 0, NULL }; 
		
		MapiMessage message= { 
			0,		// reserved, must be 0 
			"forkey", // subject 
			"send this mail for key.", // note text 
			NULL,	// NULL = interpersonal message 
			NULL,	// no date; MAPISendMail ignores it 
			NULL,	// no conversation ID 
			0L,		// no flags, MAPISendMail ignores it 
			NULL,	// no originator, this is ignored too 
			1,		// recipients 
			&recip, // recipient array 
			1,		// one attachment 
			&attachment // the attachment structure 
		}; 
		
		int nError=lpfnSendMail(0, 0, &message, MAPI_LOGON_UI | MAPI_DIALOG, 0); 
		// done before the MAPI call. 
		if(nError != SUCCESS_SUCCESS && nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
			throw -2;
	}
	catch (int) {
	}

	FreeLibrary(hMod);
	return TRUE;
}
