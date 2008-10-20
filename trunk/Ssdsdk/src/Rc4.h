#ifndef _RC4_H
#define _RC4_H

class RC4
{
private:
    int x, y, m[256];
public:
	RC4(CString key);
	BOOL Crypt(CString &data);
};

#endif /* rc4.h */