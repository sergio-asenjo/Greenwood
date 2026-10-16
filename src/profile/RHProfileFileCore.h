#ifndef RHPROFILEFILECORE_H
#define RHPROFILEFILECORE_H

#include "SB.h"

class RHProfileText;

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

#endif
