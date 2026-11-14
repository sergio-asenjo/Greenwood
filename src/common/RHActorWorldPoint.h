#ifndef RHACTORWORLDPOINT_H
#define RHACTORWORLDPOINT_H

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif

struct RHUnk004237d0Holder
{
    char m_00[0x10];
    float m_10;
    float m_14;
};

class RHUnk004237d0
{
public:
    SBGeoPoint2D FUN_004237d0();
    char m_00[0x50];
    RHUnk004237d0Holder *m_50;
};

#endif
