#ifndef RHPROJECTILEVECTOR_H
#define RHPROJECTILEVECTOR_H

struct RHProjectileVector
{
    RHProjectileVector()
    {
        ((RHUnk00613e90 *)this)->RHUnk00613e90::RHUnk00613e90();
    }
    RHProjectileVector Scaled(const float &scale) const
    {
        RHProjectileVector result;
        result.x = x * scale;
        result.y = y * scale;
        result.z = z * scale;
        return result;
    }
    int FUN_004b7fc0(const RHProjectileVector &other) const;
    void FUN_004b8840(const RHProjectileVector &other);
    float x;
    float y;
    float z;
};

class RHProjectileThrowCalls
{
public:
    RHProjectileVector FUN_004b4260(const RHProjectileVector &direction, float distance, float gravity, unsigned short frames, const void *actor);
};

#endif
