#ifndef SB_GEO_BOUNDING_BOX_2D_H
#define SB_GEO_BOUNDING_BOX_2D_H

#include "SB.h"

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    float m_x;
    float m_y;
};

class RHMobileUnk006100e0 : public SBGeoPoint2D
{
public:
    ~RHMobileUnk006100e0();
    char m_08[8];
};

class RHMobileUnk0060a820
{
public:
    RHMobileUnk0060a820 &FUN_0060a820(const SBGeoPoint2D &, const SBGeoPoint2D &);
};

class SBUIInputFieldBoxCalls
{
public:
    void FUN_0060a860(const RHMobileUnk006100e0 &);
};

class SBGeoBoundingBox2D
{
public:
    bool Serialize(SBFile &file);
    void FUN_00607d90();
    bool FUN_00607f00(const RHMobileUnk006100e0 &) const;
    bool FUN_00608040(const RHMobileUnk006100e0 &) const;
    bool FUN_00608180(const RHMobileUnk006100e0 &) const;
    bool FUN_006083b0(const SBGeoPoint2D &) const;
    char m_00[0x14];
};

class RHUnk00608f10
{
public:
    bool FUN_006082a0(void *);
};

#endif
