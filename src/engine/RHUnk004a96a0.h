#ifndef RHUNK004A96A0_H
#define RHUNK004A96A0_H

#include "SBNullstr.h"

// SIZE 0x1c
struct RHShadowPolygonActorPosition
{
    undefined m_pad0[0x18]; // 0x00
    float m_18; // 0x18
};

// SIZE 0x54
class RHUnk004a96a0
{
public:
    undefined m_pad0[0x10]; // 0x00
    unsigned short m_10; // 0x10
    undefined m_pad12[0x3e]; // 0x12
    RHShadowPolygonActorPosition *m_50; // 0x50
    void FUN_004a96a0(void *, float, void *, bool);
};

#endif
