#ifndef RHUNK00613E90_H
#define RHUNK00613E90_H

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    RHUnk00613e90(float x, float y, float z);
    RHUnk00613e90(const RHUnk00613e90 &from, const RHUnk00613e90 &to);
    RHUnk00613e90 FUN_005df550(const RHUnk00613e90 &other) const;
    float FUN_005df680() const;
    float ScaledY(float scale) const
    {
        return y * scale;
    }
    float x;
    float y;
    float z;
};

#endif
