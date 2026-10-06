#ifndef RHPROFILEFILE_H
#define RHPROFILEFILE_H

#include "RHProfileManager.h"

class RHProfileFile : public SBFile
{
public:
    RHProfileFile();
    ~RHProfileFile();
    int FUN_005f5090(const RHProfileText &path, int mode);
    int FUN_005f5370(int offset, int origin);
    unsigned int Position() { return *(unsigned int *)((char *)this + 0xc); }
    unsigned int Size() { return *(unsigned int *)((char *)this + 8); }
    char m_14[0x44];
};

unsigned long FUN_005e1d00(SBFile &file);
void FUN_005e1d50(SBFile &file, unsigned long tag, int level);
bool FUN_005e2020(SBFile &file, unsigned long tag, int level);
void FUN_005e20c0(SBFile &file);
void FUN_005e2300(SBFile &file);
RHProfileText operator+(const RHProfileText &first, const RHProfileText &second);

#endif
