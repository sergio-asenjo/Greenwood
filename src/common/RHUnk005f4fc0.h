#ifndef RHUNK005F4FC0_H
#define RHUNK005F4FC0_H

#include "SB.h"
#include "Decomp.h"
#include <stdio.h>
#include <string>

class RHProfileText;

class RHUnk005f4fc0 : public SBFile
{
public:
    RHUnk005f4fc0();
    ~RHUnk005f4fc0();
    int FUN_005f5090(const std::string &, int);
    int FUN_005f5090(const RHProfileText &, int);
    int FUN_005f5d60(const std::string &, int);
    FILE *FUN_005f58c0(const std::string &, const char *);
    void FUN_005f5290();
    bool FUN_005f6200(void *);
    int FUN_005f6220(std::string &);
    unsigned int Position() const { return *(const unsigned int *)((const char *)this + 0xc); }
    unsigned int Size() const { return *(const unsigned int *)((const char *)this + 8); }
    undefined m_14[4];
    std::string m_18;
    bool m_28;
    undefined m_29[7];
    undefined4 m_30;
    undefined4 m_34;
    undefined4 m_38;
    bool m_3c;
    undefined m_3d[0x1b];
};

#endif
