#ifndef SB_GEO_BOUNDING_BOX_2D_H
#define SB_GEO_BOUNDING_BOX_2D_H

#define SBGEO_BOUNDINGBOX2D_VIEW

#include "SB.h"

#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
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
#endif

#include "RHMobileUnk006100e0.h"

#include "SBGeoSegment2D.h"
#include "SBGeoBoxLine.h"

class SBUIInputFieldBoxCalls
{
public:
    SBUIInputFieldBoxCalls &FUN_0060a860(const RHMobileUnk006100e0 &other);
};

class RHUnk0060fbf0;
class RHMobileUnk00611360;
class RHUnkSectorPoints;

class SBGeoBoundingBox2D
{
public:
    bool Serialize(SBFile &file);
    void FUN_00607d90();
    bool FUN_00607f00(const RHMobileUnk006100e0 &) const;
    bool FUN_00608040(const RHMobileUnk006100e0 &) const;
    bool FUN_00608180(const RHMobileUnk006100e0 &) const;
    bool FUN_006083b0(const SBGeoPoint2D &) const;
    bool FUN_006085a0(const SBGeoPoint2D &) const;
    bool FUN_00608400(const SBGeoPoint2D &) const;
    bool FUN_00608650(const RHMobileUnk006100e0 &) const;
    bool FUN_00608730(const RHMobileUnk006100e0 &) const;
    bool FUN_00608c70(const RHMobileUnk00611360 &) const;
    bool FUN_00608d60(const RHUnkSectorPoints &) const;
    RHUnk0060fbf0 FUN_006093f0(const RHMobileUnk006100e0 &segment) const;
    RHUnk0060fbf0 FUN_00609440(const RHMobileUnk006100e0 &segment, double first, double last) const;
    char m_00[0x14];
};

class RHUnk00608f10
{
public:
    bool FUN_006082a0(void *);
};

#endif
