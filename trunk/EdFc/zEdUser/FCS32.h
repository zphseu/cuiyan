// FCS32.h: interface for the CFCS32 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FCS32_H__C9244867_1E93_4019_AE83_A1ABBAFAEF09__INCLUDED_)
#define AFX_FCS32_H__C9244867_1E93_4019_AE83_A1ABBAFAEF09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFCS32  
{
public:
	CString fcs32(const char *psz);

protected:
	void init(unsigned long fcs32);
	const unsigned long final();
	void update(const char *pBuffer, unsigned long uBufSize);
	static const unsigned long fcs32tab[256];
	unsigned long uFcs32;
};

#endif // !defined(AFX_FCS32_H__C9244867_1E93_4019_AE83_A1ABBAFAEF09__INCLUDED_)
