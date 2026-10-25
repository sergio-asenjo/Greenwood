#ifndef RHSOUNDGEOMETRYCALLS_H
#define RHSOUNDGEOMETRYCALLS_H

class SBGeoPoint2D;
#include "Decomp.h"


// SIZE 0x50
struct RHUnk005a7220
{
    undefined m_00[8]; // 0x00
    int m_08; // 0x08
    unsigned long m_0c; // 0x0c
    bool m_10; // 0x10
    undefined m_11; // 0x11
    unsigned short m_12; // 0x12
    unsigned short m_14; // 0x14
    undefined m_16[2]; // 0x16
    unsigned short m_18; // 0x18
    unsigned short m_1a; // 0x1a
    undefined m_1c[4]; // 0x1c
    SBGeoPoint2D *m_20; // 0x20
    SBGeoPoint2D *m_24; // 0x24
    undefined m_28[0x18]; // 0x28
    int m_40; // 0x40
    unsigned short m_44; // 0x44
    unsigned short m_46; // 0x46
    unsigned short m_48; // 0x48
    unsigned short m_4a; // 0x4a
    bool m_4c; // 0x4c
    undefined m_4d[3]; // 0x4d
};

// SIZE 0x10
struct RHUnk005b2410
{
    RHUnk005b2410(float, float, float, float);
    float m_00; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
    float m_0c; // 0x0c
};

class RHUnk005b35e0
{
public:
    void FUN_005b35e0(unsigned int count, const SBGeoPoint2D &value);
};

#endif
