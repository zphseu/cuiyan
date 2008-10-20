// CryptString.h: interface for the CCryptString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTSTRING_H__5996D2E1_1915_4B23_BD9E_5932885364DF__INCLUDED_)
#define AFX_CRYPTSTRING_H__5996D2E1_1915_4B23_BD9E_5932885364DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#define _CRYPT_FLAG_

class CCryptString : public CString  
{
public:
	CCryptString();
	CCryptString( const CString& stringSrc );
	CCryptString( TCHAR ch, int nRepeat = 1 );
	CCryptString( LPCTSTR lpch, int nLength );
	CCryptString( const unsigned char* psz );
	CCryptString( LPCWSTR lpsz );
	CCryptString( LPCSTR lpsz );
	virtual ~CCryptString();

#ifdef _CRYPT_FLAG_
 	BOOL Crypt();
 	BOOL Decrypt();

protected:
 	BOOL m_IsCryto;
#endif

	BOOL InCrypt();
	BOOL InDecrypt();

};

#endif // !defined(AFX_CRYPTSTRING_H__5996D2E1_1915_4B23_BD9E_5932885364DF__INCLUDED_)
