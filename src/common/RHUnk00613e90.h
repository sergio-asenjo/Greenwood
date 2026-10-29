#ifndef RHUNK00613E90_H
#define RHUNK00613E90_H

#include <math.h>

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    RHUnk00613e90(float x, float y, float z);
    RHUnk00613e90(const RHUnk00613e90 &from, const RHUnk00613e90 &to);
    void FUN_00467990(float x, float y, float z);
    RHUnk00613e90 FUN_005df550(const RHUnk00613e90 &other) const;
    RHUnk00613e90 FUN_005df5a0(const RHUnk00613e90 &other) const;
    RHUnk00613e90 FUN_005df610(const RHUnk00613e90 &other) const;
    float FUN_005df5f0(const RHUnk00613e90 &other) const;
    float FUN_005df680() const;
    RHUnk00613e90 DistanceVectorToLine(const RHUnk00613e90 &first, const RHUnk00613e90 &second);
    float Norm() const
    {
        return (float)sqrt(x * x + y * y + z * z);
    }
    RHUnk00613e90 Scaled(const float &scale) const
    {
        RHUnk00613e90 result;
        result.x = x * scale;
        result.y = y * scale;
        result.z = z * scale;
        return result;
    }
    float ScaledY(float scale) const
    {
        return y * scale;
    }
    union { float x; float m_0; };
    union { float y; float m_4; };
    union { float z; float m_8; };
};

#endif
