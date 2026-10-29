#ifndef RHUNK0060BD40_H
#define RHUNK0060BD40_H

#include "sbgeo_00610600.h"

class RHUnk0060bd40 : public SBGeoPolyLine2DList
{
public:
    RHUnk0060bd40();
    RHUnk0060bd40(const RHUnk0060bd40 &other);
    RHUnk0060bd40(const RHUnkSectorPoints &other);
    void FUN_0060bc80(const RHUnk0060bd40 &other);
    void FUN_0060bce0(const RHUnkSectorPoints &other);
    short m_28;
    short m_2a;
    char m_2c;
    char m_2d;
};

#endif
