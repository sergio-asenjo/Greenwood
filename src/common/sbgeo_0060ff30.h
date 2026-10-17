#ifndef SBGEO_0060FF30_H
#define SBGEO_0060FF30_H

#include "Decomp.h"

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

// SIZE 0x10
class RHMobileUnk006100e0 : public SBGeoPoint2D
{
public:
    ~RHMobileUnk006100e0();
    void FUN_00578c50();
    void FUN_0060ff30(const RHMobileUnk006100e0 &other);
    RHMobileUnk006100e0 &FUN_00610140(const RHMobileUnk006100e0 &other);
    void FUN_00610160(const SBGeoPoint2D &vector);
    RHUnk0060fbf0 FUN_006101c0(const RHMobileUnk006100e0 &other) const;
    float FUN_006104f0(float y);
    float FUN_00610520(float x);
    SBGeoPoint2D m_8; // 0x08
};

#endif
