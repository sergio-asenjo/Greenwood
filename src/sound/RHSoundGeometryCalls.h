#ifndef RHSOUNDGEOMETRYCALLS_H
#define RHSOUNDGEOMETRYCALLS_H

class SBGeoPoint2D;
struct RHUnk005a7220;

// SIZE 0x10
struct RHUnk005b2410
{
    RHUnk005b2410(float, float, float, float);
    float m_00; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
    float m_0c; // 0x0c
};

class RHUnk005b2ff0Geometry
{
public:
    float FUN_005b2510(float, const RHUnk005b2410 &);
    float FUN_005b2560(const SBGeoPoint2D &, const RHUnk005b2410 &);
    float FUN_005b25e0(const RHUnk005b2410 &);
    float FUN_005b27e0(const RHUnk005b2410 &);
    void FUN_005b2a30(RHUnk005a7220 *, RHUnk005b2410 &);
};

#endif
