#ifndef RHUNK005FC3B0_H
#define RHUNK005FC3B0_H
#define RHUNK005FC3B0_VIEW

#ifndef SBGEO_VECTOR2D_VIEW
#include "SBGeoVector2D.h"
#endif

class RHUnk005fc3b0 : public SBGeoVector2D
{
public:
    RHUnk005fc3b0() {}
    RHUnk005fc3b0(float x, float y);
    ~RHUnk005fc3b0() {}
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other)
    {
        return (RHUnk005fc3b0 &)SBGeoVector2D::operator=((const SBGeoVector2D &)other);
    }
    RHUnk005fc3b0 &FUN_005fc5b0(float factor);
    RHUnk005fc3b0 &FUN_005fc4d0(float factor);
    SBGeoVector2D FUN_005fc5d0(float value);
    bool IsZero() const { return ((const float *)this)[0] == 0.0f && ((const float *)this)[1] == 0.0f; }
    void FUN_005fc7c0(float scale);
    float Unk005fc6a0(float scale);
    RHUnk005fc3b0 &Unk005fcd40(unsigned char direction, float length);
    unsigned char FUN_005fcc50(float scale) const;
    SBGeoVector2D FUN_005fc8f0(bool direction, float scale) const;
    RHUnk005fc3b0 FUN_005fc9e0(float angle, float scale);
    float FUN_005fc680(const RHUnk005fc3b0 &other, float scale) const;
    void Set(float x, float y) { ((float *)this)[0] = x; ((float *)this)[1] = y; }
};

#endif
