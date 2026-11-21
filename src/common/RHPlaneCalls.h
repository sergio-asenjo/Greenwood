#ifndef RHPLANECALLS_H
#define RHPLANECALLS_H

#include "RHUnk00613e90.h"

class SBGeoPoint2D;

class RHUnk005df860
{
public:
    RHUnk005df860();
    void Unk005df860(const RHUnk00613e90 &first, const RHUnk00613e90 &second, const RHUnk00613e90 &third);
    void FUN_005df8b0();
    void FUN_005df900();
    void FUN_005df9a0();
    void FUN_005df9c0();
    void Unk005dfa00();
    void FUN_005dfa20(const RHUnk00613e90 &offset);
    void FUN_005dfaa0(const SBGeoPoint2D &offset);
    const RHUnk00613e90 &Normal() const;
    bool FUN_005dfb00(SBFile &file);
    void Emit(SBFile &file);
    RHUnk00613e90 m_00;
    RHUnk00613e90 m_0c;
    RHUnk00613e90 m_18;
    RHUnk00613e90 m_24;
    RHUnk00613e90 m_30;
    RHUnk00613e90 m_3c;
    int m_48;
    int m_4c;
    int m_50;
    int m_54;
};

#endif
