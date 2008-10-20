/*
 * An implementation of the ARC4 algorithm,
 * by Christophe Devine <devine@cr0.net>;
 * this program is licensed under the GPL.
 */

#include "stdafx.h"
#include "rc4.h"

RC4::RC4(CString key)
{
    int j, k, a;
    x = y = 0;
    j = k = 0;

    for(int i = 0; i < 256; i++ )
        m[i] = i;

    for(i = 0; i < 256; i++ )
    {
        a = m[i];
        j = ( j + a + key[k] ) & 0xFF;
        m[i] = m[j]; m[j] = a;
        if( ++k >= key.GetLength() ) k = 0;
    }
}

BOOL RC4::Crypt(CString &data)
{
    int a, b, nSize = data.GetLength();
	TCHAR ch;

    for(int i = 0; i < data.GetLength(); i++ )
    {
		x = ( x + 1 ) & 0xFF; a = m[x];
        y = ( y + a ) & 0xFF;
        m[x] = b = m[y];
        m[y] = a;

        ch = data[i];
        ch ^= m[( a + b ) & 0xFF];
		data.SetAt(i, ch);
    }

	// cover bin data to ASCII string

	TCHAR *pASCII = new TCHAR [nSize * sizeof(TCHAR) * 2 + 1];
    if (!pASCII)
		return FALSE;
	
    for (int l=0;  l < nSize;  l++)
        wsprintf((TCHAR *)&(pASCII)[l*2], "%02X", data[l]);
    
	data = pASCII;
	delete pASCII;
	return TRUE;
}

