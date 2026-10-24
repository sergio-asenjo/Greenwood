#ifndef RHMOUSEMESSAGE_H
#define RHMOUSEMESSAGE_H

#include "RHMessage.h"
#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif

// SIZE 0x18
// VTABLE: GAME 0x00679b68
class RHUnk00549120 : public RHMessage
{
public:
    RHUnk00549120(int value, const SBGeoPoint2D &point);
    RHUnk00549120(int value, const SBGeoPoint2D &point, int extra);
    ~RHUnk00549120();
    void *FUN_00549180(unsigned flags);
    int m_0c;          // 0x0c
    SBGeoPoint2D m_10; // 0x10
};

#endif
