#ifndef RHMOBILESEGMENTCALLS_H
#define RHMOBILESEGMENTCALLS_H

class SBGeoPoint2D;
class RHMobileUnk006100e0;
class RHUnk0060fbf0;
class SBGeoSegment2D;

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include "RHMobileUnk006100e0.h"

class RHMobileUnk0060a820 : public RHMobileUnk006100e0
{
public:
    RHMobileUnk0060a820(const RHMobileUnk0060a820 &other);
    ~RHMobileUnk0060a820();
    RHMobileUnk0060a820 &FUN_006158b0(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    RHMobileUnk0060a820 &FUN_006158f0(const RHMobileUnk006100e0 &other);
    bool FUN_00615910(const SBGeoSegment2D &segment) const;
    RHUnk0060fbf0 FUN_00615ca0(const SBGeoSegment2D &segment) const;
};

#endif
