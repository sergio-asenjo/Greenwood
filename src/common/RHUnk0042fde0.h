#ifndef RHUNK0042FDE0_H
#define RHUNK0042FDE0_H

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif

class SBGeoVector2D;

class RHUnk0042fde0
{
public:
    SBGeoVector2D FUN_0042fde0() const;
    bool FUN_0060b640(const SBGeoPoint2D &point) const;
    float FUN_0060b7a0(const SBGeoPoint2D &point) const;
    void FUN_0060b910(SBGeoPoint2D &output, const SBGeoPoint2D &point) const;
    float FUN_0060ba80(const SBGeoPoint2D &point) const;
    SBGeoPoint2D m_0;
    SBGeoPoint2D m_8;
};

#endif
