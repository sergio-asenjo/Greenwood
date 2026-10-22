#ifndef SB_GEO_BOX_LINE_H
#define SB_GEO_BOX_LINE_H

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif

#include "RHMobileUnk006100e0.h"

class RHBoxLine00610070 : public RHMobileUnk006100e0
{
public:
    RHBoxLine00610070(const RHMobileUnk006100e0 &segment);
    ~RHBoxLine00610070() {}
};

class RHBoxIntersection00608800
{
public:
    bool FUN_00608800(const RHBoxLine00610070 &line) const;
};

#endif
