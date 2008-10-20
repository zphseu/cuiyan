// CryptString.cpp: implementation of the CCryptString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CryptString.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCryptString::CCryptString() : CString()
#ifdef _CRYPT_FLAG_	
	, m_IsCryto(FALSE)
#endif
	{}

CCryptString::CCryptString( const CString& stringSrc ) : CString(stringSrc)
#ifdef _CRYPT_FLAG_	
	, m_IsCryto(FALSE)
#endif
	{}

CCryptString::CCryptString( TCHAR ch, int nRepeat ) : CString(ch, nRepeat)
#ifdef _CRYPT_FLAG_	
	, m_IsCryto(FALSE)
#endif
	{}

CCryptString::CCryptString( LPCTSTR lpch, int nLength ) : CString(lpch, nLength)
#ifdef _CRYPT_FLAG_	
	, m_IsCryto(FALSE)
#endif
	{}

CCryptString::CCryptString( const unsigned char* psz ) : CString(psz)
#ifdef _CRYPT_FLAG_	
	, m_IsCryto(FALSE)
#endif
	{}

CCryptString::CCryptString( LPCWSTR lpsz ) : CString(lpsz)
#ifdef _CRYPT_FLAG_	
	, m_IsCryto(FALSE)
#endif
	{}

CCryptString::CCryptString( LPCSTR lpsz ) : CString(lpsz)
#ifdef _CRYPT_FLAG_	
	, m_IsCryto(FALSE)
#endif
	{}

CCryptString::~CCryptString() {}

#ifdef _CRYPT_FLAG_	
BOOL CCryptString::Crypt()
{
	if (m_IsCryto)	return TRUE;
	return m_IsCryto = InCrypt();
}

BOOL CCryptString::Decrypt()
{
	if (!m_IsCryto)	return TRUE;
	return m_IsCryto = !InDecrypt();
}
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 5000
#endif

#include <stdio.h>
#include <objbase.h>
#include <wincrypt.h>

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "User32.lib")

/**
 * decrypt buffer
 * @param pIn - [in]pointer to memory to decrypt
 * @param pIn - [out]decrypted memory block
 * @param plSize - [in]pointer to long which hold pIn size in bytes
 * @param plSize - [out]size of decrypted memory
 */
BOOL CCryptString::InDecrypt()
{
	long lSize = GetLength();
	// convert ASCII string generated by Bin2ASCII() to binary data.
	char szBuf[3];
    unsigned char *pIn = new unsigned char [lSize];
    if (!pIn)
		return FALSE;
	
    szBuf[2] = '\0';
    for (long l=0;  l < lSize;  l++) {
        szBuf[0]    = m_pchData[l*2];
        szBuf[1]    = m_pchData[(l*2)+1];
        pIn[l] = (unsigned char)strtoul(szBuf, NULL, 16);
	}
    
	lSize /= 2;
	pIn[lSize] = 0;

	// Decrypt ...
	HCRYPTPROV hProv = 0;
	HCRYPTKEY hKey = 0;
	DWORD dwCount;
	
	BYTE *pbKeyBlob = NULL;
	DWORD dwBlobLen;
	
	// Get a handle to the default provider.
	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0))
		return FALSE;
	
	// Read the key blob length from the source and          // init pointer
	memcpy(&dwBlobLen, pIn, sizeof(DWORD));
	pbKeyBlob = (BYTE *)&pIn[sizeof(DWORD)];
	
	// Import the key blob into the CSP.
	if (!CryptImportKey(hProv, pbKeyBlob, dwBlobLen, 0, 0, &hKey))
		return FALSE;
	
	// decrypt all
	dwCount = lSize - (sizeof(DWORD)+dwBlobLen);
	if (!CryptDecrypt(hKey, 0, TRUE, 0, &pIn[sizeof(DWORD)+dwBlobLen],  &dwCount))
		return FALSE;
	
    // inform user about the lenght of decrypted data
    memmove(pIn, &pIn[sizeof(DWORD)+dwBlobLen], dwCount);
    lSize = dwCount;
	
	// Destroy the session key.
	if(hKey != 0) CryptDestroyKey(hKey);
	
	// Release the provider handle.
	if(hProv != 0) CryptReleaseContext(hProv, 0);
	
	Init();
	*this = pIn;
	delete pIn;
	return TRUE;
}

/**
 * crypt memory block via random key (generated every time)
 * this key is also crypted and saved with the body BUT!
 * you dont neede password! why?
 * becouse you enter the password in login procedure!
 * yes this function takes the logged user key to crypt.
 *
 * @param pIn      - [in]buffer to crypt
 * @param plSize   - [in]size of data to crypt (buffer)
 * @param plSize   - [out]size of crypted data
 * @param ppOut    - [out]pointer to pointer which will hold crypted             
 *                    data (bigger than data at in!)
 */
BOOL CCryptString::InCrypt()
{
	unsigned char *pIn = (unsigned char *)m_pchData;
	unsigned char *pOut = NULL;
	long lSize = GetLength();

	HCRYPTPROV hProv = 0;
	HCRYPTKEY hKey = 0;
	HCRYPTKEY hXchgKey = 0;
	
	DWORD dwCount, dwNewBufLen;
	
	BYTE *pbKeyBlob = NULL;
	DWORD dwBlobLen;
	
	// Get a handle to the default provider.
	if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) {
        // Some sort of error occured, create default key container.
        if (!CryptAcquireContext( &hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
            // Error creating key container!
            return FALSE;
        }
	}

	// Get a handle to key exchange key.
	if (!CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hXchgKey)) {
		if (GetLastError()==NTE_NO_KEY)	{
			// Create key exchange key pair.
			if (!CryptGenKey(hProv,AT_KEYEXCHANGE,0,&hKey)) {
				// Error during CryptGenKey!
				CryptReleaseContext(hProv, 0);
				return FALSE;
			} else {
				CryptDestroyKey(hKey);
				CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hXchgKey);
			}
		}
		else
			return FALSE;
	}

    // Create a random block cipher session key.
    if (!CryptGenKey(hProv, CALG_RC2, CRYPT_EXPORTABLE, &hKey))
		return FALSE; 

    // Determine the size of the key blob and allocate memory.
    if (!CryptExportKey( hKey, hXchgKey, SIMPLEBLOB, 0, NULL, &dwBlobLen))
		return FALSE;
    if ((pbKeyBlob = (unsigned char *)malloc(dwBlobLen)) == NULL)
		return FALSE;

    // Export the key into a simple key blob.
    if (!CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, pbKeyBlob, &dwBlobLen))	{
		free(pbKeyBlob);
		return FALSE;
	}

	// how much memory neede for ciphered block?
	dwCount = lSize;
	if (!CryptEncrypt(hKey, 0, TRUE, 0, NULL, &dwCount, 0))
		return FALSE;

	// put on output the len, key blob, and alloc memory
	pOut = new unsigned char [sizeof(dwBlobLen) + dwBlobLen + dwCount];
	if (!pOut)
		return FALSE;
	memcpy(pOut, &dwBlobLen, sizeof(dwBlobLen));
	memcpy(&(pOut)[sizeof(dwBlobLen)], pbKeyBlob,   dwBlobLen);

	// Free memory.
	free(pbKeyBlob);
	
	// finally crypt!
	memcpy(&(pOut)[sizeof(dwBlobLen)+dwBlobLen], pIn, lSize);
	dwNewBufLen = dwCount;
	dwCount = lSize;
	if (!CryptEncrypt(hKey, 0, TRUE, 0, &(pOut)[sizeof(dwBlobLen)+dwBlobLen], &dwCount, dwNewBufLen))
		return FALSE;
	
	// update output size
	lSize = sizeof(dwBlobLen) + dwBlobLen + dwCount;
	
	// Destroy the session key.
	if(hKey != 0) CryptDestroyKey(hKey);
	
	// Destroy the key exchange key.
	if(hXchgKey != 0) CryptDestroyKey(hXchgKey);
	
	// Release the provider handle.
	if(hProv != 0) CryptReleaseContext(hProv, 0);
	
	// cover bin data to ASCII string
	unsigned char *pASCII = new unsigned char [(lSize*2)+1];
    if (!pASCII)
		return FALSE;
	
    for (long l=0;  l<lSize;  l++)
        wsprintf((char *)&(pASCII)[l*2], "%02X", pOut[l]);
    
	delete pOut;
	Init();
	*this = pASCII;
	delete pASCII;

	return TRUE;
}
