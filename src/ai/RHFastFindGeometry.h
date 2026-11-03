#ifndef RHFASTFINDGEOMETRY_H
#define RHFASTFINDGEOMETRY_H

#include "SB.h"

#include "SBGeoPoint2D.h"
#include "SBGeoVector2D.h"

class RHUnk005fc3b0 : public SBGeoVector2D
{
public:
    RHUnk005fc3b0() {}
    ~RHUnk005fc3b0() {}
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other)
    {
        return (RHUnk005fc3b0 &)SBGeoVector2D::operator=((const SBGeoVector2D &)other);
    }
    float Unk005fc6a0(float value);
    void FUN_005fc7c0(float value);
    RHUnk005fc3b0 &FUN_005fc4d0(float factor);
    unsigned char FUN_005fcc50(float value) const;
    SBGeoVector2D FUN_005fc8f0(bool direction, float value) const;
    RHUnk005fc3b0(float x, float y);
    float FUN_005fc680(const RHUnk005fc3b0 &other, float value) const;
};

#endif
