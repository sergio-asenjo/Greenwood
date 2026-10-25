#ifndef RHUNK005FC3B0_H
#define RHUNK005FC3B0_H

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
    void FUN_005fc7c0(float value);
    SBGeoVector2D FUN_005fc8f0(bool direction, float value) const;
};

#endif
