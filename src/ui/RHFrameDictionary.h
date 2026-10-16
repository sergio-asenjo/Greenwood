#ifndef RHFRAMEDICTIONARY_H
#define RHFRAMEDICTIONARY_H

#include "Decomp.h"

class SBFile;

class RHUnk005069a0
{
public:
    RHUnk005069a0();
    RHUnk005069a0(const RHUnk005069a0 &value);
    RHUnk005069a0(const RHUnk005069a0 &value, int mode);
    ~RHUnk005069a0();
    RHUnk005069a0 &FUN_005069b0(const RHUnk005069a0 &value);
    RHUnk005069a0 &operator=(const RHUnk005069a0 &value) { return FUN_005069b0(value); }
    void FUN_005069d0(unsigned short, SBFile &);
    void FUN_00506a70(const RHUnk005069a0 &value);
    bool FUN_00506b40();
    void FUN_00506b90(SBFile &file);
    bool FUN_00504b80(unsigned short);
    void *FUN_00509c10(unsigned flags);
    undefined2 m_00;
    undefined2 m_02;
    undefined4 m_04;
    undefined4 m_08;
    undefined2 m_0c;
    undefined m_0e[6];
};

typedef RHUnk005069a0 RHUnk005068e0;

#endif
