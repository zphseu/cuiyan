//CRC32.h
#ifndef CRC32h
#define CRC32h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
CRC is a "digital fingerprint" of a file.
With CRC32 you can get a single 32-bit number that represents a string or file (of any size).
If the file data changes in any way (even a single bit) the CRC32 calculation would yield a completely different value.
This algorithm is used by WinZip and PKZIP (ie the same numbers are generated) so:
pkunzip.exe -vt File.zip gives the same CRC value as you get by giving the file to this code.

A single 1kB table is allocated while instances of CCRC32 exist.

Usage:
  DWORD CRC=CCRC32().From(Buffer,Size);

or use one instance for several CRCs:
  CCRC32 CRC32;
  DWORD CRC1=CRC32.From(Buffer1,Size1);
  DWORD CRC2=CRC32.From(Buffer2,Size2);

or if reading data in blocks:
  int OK;
  CCRC32 CRC32;
  BYTE Buffer[1024];
  FILE* File=fopen("C:\\CheckMe.txt","rb");
  if(File) do CRC32.From(Buffer, OK=fread(Buffer, 1, 1024, File), true); while(OK);
  fclose(File);
  DWORD CRC=CRC32.GetCRC();

But since we want the fastest routines we should use CreateFile
and thats what the class uses internally for retrieving the CRC32 of a file:
  DWORD CRC=CCRC32().From("C:\\CheckMe.txt");

Test CRC numbers:
resume = 60C1D0A0
resumé = 84CF1FAB
*/
class CCRC32 {
  DWORD*  Tbl; //These let us use the static variables in the constructor without having to have a .cpp file to instantiate the statics
  int*    Instances;
  DWORD   LastCRC;
public:
  CCRC32() {
    static DWORD* StaticTbl=0;       // Table of CRC values for every possible BYTE
    static int    StaticInstances=0; // Count of references to Tbl (Instances of CCRC32)
    Tbl=StaticTbl;
    Instances=&StaticInstances;
    if(Tbl) ++Instances;
    else {
      LastCRC=-1;
      *Instances=0;
      Tbl=new DWORD[256];
      if(!Tbl) return;
      *Instances=1;
      DWORD* ptr=Tbl;
      for(DWORD n=0; n<256; ++n){
        DWORD c=n;
        for(int k=0; k<8; ++k) c=(c&1 ? 0xEDB88320^(c>>1) : c>>1);
        *ptr++=c;
    } }
  }
  virtual ~CCRC32() {
    if(*Instances) --*Instances;
    if(*Instances) return;
    delete[] Tbl;
    Tbl=0;
  }
  DWORD GetCRC() const {return ~LastCRC;}

  DWORD From(const char* Path, bool Partial=false) {
    if(!Partial) Reset();
    DWORD OK;
    char Buffer[1024];
    HANDLE File=CreateFile(Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(File) do {
      ReadFile(File, Buffer, sizeof(Buffer), &OK, NULL);
      From(Buffer, OK, true);
    }while(OK);
    CloseHandle(File);
    return GetCRC();
  }

  void Reset() {LastCRC=-1;} //Only use this to use one CRC32 class for a whole new checksum when only using From(...) with Partial=true.

//Since all that happens with the Buffer is an Exclusive OR operation, it doesn't matter if Buffer holds signed or unsigned chars.
  DWORD From(const char* Buffer, int   Len, bool Partial=false) {return From(Buffer, (DWORD)Len, Partial);}
  DWORD From(const char* Buffer, DWORD Len, bool Partial=false) {
    if(!Len || !Tbl || !Buffer) return 0;
    register DWORD CRC=(Partial ? LastCRC : LastCRC=-1);
    while(Len--) CRC=(CRC>>8)^Tbl[(CRC^(*Buffer++))&0xFF]; //Modern processors will NOT benefit from coded loop optimisation techniques (unrolling)!
    return ~(LastCRC=CRC);
  }
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Adler32 Checksum <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
Adler32 is another checksum alogorithm that is used as a "quick and dirty" version of the CRC32 algorithm (it was invented by Mark Adler).
You get a single 32-bit number that represents a block of data (of any size but >128 bytes preferably).
If the data changes in any way (even a single bit) the Adler32 calculation would yield a completely different value.
It may comfort you to know that this document contains 32 occurances of the word Adler32... or not!

Usage:
  int Adler32=CAdler32().From(Buffer,Size);

or use one instance for several Adler32s:
  CAdler32 Adler32;
  int Adler32a=Adler32.From(Buffer1,Size1);
  int Adler32b=Adler32.From(Buffer2,Size2);

or if reading a file in blocks:
  CAdler32 Adler32;
  while(Read(Buffer, Size)) Adler32.From(Buffer, Size, true);
  int MyAdler32=Adler32.GetAdler32();
  }

Test Adler32 numbers:
resume = 152371858
resumé = 161022742
*/
class CAdler32 {
  DWORD LastAdler32;
public:
  CAdler32() { Reset(); }
  virtual ~CAdler32() {}
  DWORD GetAdler32() const {return LastAdler32;}

  DWORD From(const char* Path) {
    DWORD OK;
    char Buffer[1024];
    HANDLE File=CreateFile(Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(File) do {
      ReadFile(File, Buffer, sizeof(Buffer), &OK, NULL);
      From(Buffer, OK, true);
    }while(OK);
    CloseHandle(File);
    return GetAdler32();
  }

  void Reset() {LastAdler32=1;} //Only use this to use one Adler32 class for a whole new checksum when only using From(...) with Partial=true.

  DWORD From(const char* Buffer, DWORD Len, bool Partial=false) {
    if(!Len || !Buffer) return 0;
    register DWORD Adler32=(Partial ? LastAdler32 : LastAdler32=1);
    register DWORD s1=Adler32 & 0xFFFF;
    register DWORD s2=Adler32 >> 16;
    while(Len>0) {
      int k=(Len<5552 ? Len : 5552); //5552 is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1
      Len-=k;
      while(k--) {s1+=*Buffer++; s2+=s1;} //Modern processors will NOT benefit from coded loop optimisation techniques (unrolling)!
      s1%=65521; // 65521 is the largest prime smaller than 65536
      s2%=65521;
    }
    return LastAdler32=(s2<<16)|s1;
  }
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Fast Rolling Checksum <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
The following algorithm is from a program called rsync which compares blocks of data using this very fast, rollable checksum.
Blocks of data are compared using their checksums.
This is a weak checksum and is used as a first pass before using a stronger checksum to ensure that any two blocks are identical.
Having got the checksum of a block of data, you can scroll the block one Byte by telling the Roller what character to remove fro the beginning of the block and what character to append to the end (if any).
The data block does not need rescanning - the checksum updates itself using just the two changed Bytes.
As with Adler32, it gives better results the larger the block size and 128 Bytes is a good minimum.

Test numbers:
resume = 169870047
resumé = 178520931

RSync has 0 instead of 13 giving the following Checksums:
resume = 151978641
resumé = 160629525

Heres an example:
All you know of the "OtherFile" is a Roller (weak) checksum and an MD5 (strong) checksum for each 512 Byte block...
    CFile File;
    if(!File.Open(Path, CFile::modeRead)) return;
    BYTE Buffer[512];
    CRoller Roller;
    DWORD Bytes;
    do {
      Bytes=File.Read(Buffer, sizeof(Buffer));
      Roller.Set(Buffer, Bytes);
      while(Bytes && !OtherFile.Find(Roller.Get()) { // Try to find a block with this checksum
        char Old=Buffer[0]; //If we didn't find a matching block, move 1 Byte and retry
        memcpy(Buffer, Buffer+1, --Bytes); // Scroll the Buffer 1 Byte:
        Bytes+=File.Read(Buffer+Bytes, 1);
        Roller.Roll(Old, Bytes, Bytes==sizeof(Buffer), Buffer[Bytes-1]);
      }
      ... //Either finished the file (Bytes==0) or found a block.
    }while(Bytes);
*/

class CRoller {
  DWORD s1;
  DWORD s2;
public:
  CRoller() {}
  virtual ~CRoller() {}
  CRoller(const BYTE* Buffer, DWORD Bytes) {Set(Buffer, Bytes);}
  DWORD Get() const {return (s1 & 0xFFFF)+(s2<<16);}
  void Set(const BYTE* Buffer, DWORD Bytes) {for(DWORD i=s1=s2=0; i++<Bytes; s2+=s1+=13+*Buffer++);}
  void Set(DWORD Roller) {
    s1=Roller & 0xFFFF;
    s2=Roller>>16;
  }
  void Trim(BYTE Old, DWORD Bytes) {
    s1-=Old+=13;
    s2-=Old*Bytes;
  }
  void Append(BYTE New) {s2+=s1+=13+New;}
  void Roll(BYTE Old, DWORD Bytes, bool append, BYTE New) {
    Trim(Old, Bytes);
    if(append) Append(New);
  }
};

#endif //ndef CRC32h
