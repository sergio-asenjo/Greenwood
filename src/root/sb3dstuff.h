#ifndef SB3DSTUFF_H
#define SB3DSTUFF_H

#include "SB.h"
#include "RHUnk00613e90.h"

#include "RHUnk005df510.h"

class RHUnk005dfd00
{
public:
    RHUnk005dfd00();
    void FUN_005dfc40(RHUnk00613e90 point);
    void FUN_005dfc60(RHUnk00613e90 point);
    void FUN_005dfc80(RHUnk00613e90 point);
    void Reset()
    {
        m_00 = 1.0e30f;
        m_04 = -1.0e30f;
        m_08 = 1.0e30f;
        m_0c = -1.0e30f;
        m_10 = 1.0e30f;
        m_14 = -1.0e30f;
    }
    float m_00;
    float m_04;
    float m_08;
    float m_0c;
    float m_10;
    float m_14;

    bool FUN_005dfd00(SBFile &file);
    void Emit(SBFile &file);
};

#endif
