#ifndef RHPLANECALLS_H
#define RHPLANECALLS_H

class SBGeoPoint3D;
class SBGeoPoint2D;
class RHUnk00613e90;

class RHUnk005df860
{
public:
    RHUnk005df860();
    void Unk005df860(const SBGeoPoint3D &first, const SBGeoPoint3D &second, const SBGeoPoint3D &third);
    void FUN_005df8b0();
    void FUN_005df900();
    void FUN_005df9a0();
    void FUN_005df9c0();
    void Unk005dfa00();
    void FUN_005dfa20(const RHUnk00613e90 &offset);
    void FUN_005dfaa0(const SBGeoPoint2D &offset);
    char m_00[0x58];
};

#endif
