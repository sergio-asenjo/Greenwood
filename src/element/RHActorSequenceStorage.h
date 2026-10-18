#ifndef RHACTORSEQUENCESTORAGE_H
#define RHACTORSEQUENCESTORAGE_H

#include "Decomp.h"

class RHActorPCBoxCalls
{
public:
    RHActorPCBoxCalls();
    ~RHActorPCBoxCalls();
    undefined m_0[0x14];
};

class RHUnk0045aaf0
{
public:
    RHUnk0045aaf0();
    bool FUN_0045abc0(unsigned short value, int first, int second);
    undefined4 m_0;
    undefined4 m_4;
    undefined m_8[8];
    RHActorPCBoxCalls m_10;
    undefined m_24[0x10];
    SBGeoPoint2D m_34;
};

#endif
