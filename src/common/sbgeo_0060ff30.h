#ifndef SBGEO_0060FF30_H
#define SBGEO_0060FF30_H

#include "Decomp.h"

#define SBGEO_POINT2D_VIEW

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    SBGeoPoint2D(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    float m_x; // 0x00
    float m_y; // 0x04
};

class RHMobileUnk006100e0;

#include "SBGeoIntersection2D.h"

#include "RHMobileUnk006100e0.h"

#endif
