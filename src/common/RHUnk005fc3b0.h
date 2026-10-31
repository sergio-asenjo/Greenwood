#ifndef RHUNK005FC3B0_H
#define RHUNK005FC3B0_H
#define RHUNK005FC3B0_VIEW

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
    RHUnk005fc3b0 &FUN_005fc5b0(float factor);
    bool IsZero() const { return m_x == 0.0f && m_y == 0.0f; }
    void FUN_005fc7c0(float scale);
    float Unk005fc6a0(float scale);
    unsigned char FUN_005fcc50(float scale) const;
    SBGeoVector2D FUN_005fc8f0(bool direction, float scale) const;
    RHUnk005fc3b0 FUN_005fc9e0(float angle, float scale);
    float FUN_005fc680(const RHUnk005fc3b0 &other, float scale) const;
};

#endif
