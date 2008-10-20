// SSD.h: interface for the CSSD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SSD_H__9C0D810D_81C1_4DB3_B26F_6B7746F049B4__INCLUDED_)
#define AFX_SSD_H__9C0D810D_81C1_4DB3_B26F_6B7746F049B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum CRYPTTYPE {
	WINCRYPTAPI,
	CRYPTRC4,
	CRC_ADLER
};

struct SSD {
	CString m_szName;
	CString m_szEmail;
	CString m_szProduct;
	CString m_szSysInfo;
	CString m_szSerial;
};

class CSSD
{
public:
	BOOL verify(CString email);
	CSSD(CRYPTTYPE cryto = CRC_ADLER, BOOL inSysInfo = TRUE);
	CSSD(SSD ssd, CRYPTTYPE cryto = CRC_ADLER, BOOL inSysInfo = TRUE);
	BOOL LoadFromReg(CString RegPath = _T(""));
	BOOL SaveToReg(CString RegPath = _T(""));

	BOOL GenSerial();
	BOOL CheckValidate();
	
	BOOL LoadFromDlg(); //include serial

	BOOL DlgSendForKey(CString email);
	BOOL DlgLoadFromFile();

	static LPCTSTR szCryptType[];
protected:
	CString GetProductInfo();
	CString GetRegPath();
	
	BOOL LoadFromFile(CString fn);
	BOOL SaveToFile(CString fn);

	SSD	 m_ssd;
	CRYPTTYPE m_Crypt;
	BOOL m_inSysInfo;

private:
	BOOL SendMail(CString email, CString attachment);
};

#endif // !defined(AFX_SSD_H__9C0D810D_81C1_4DB3_B26F_6B7746F049B4__INCLUDED_)
