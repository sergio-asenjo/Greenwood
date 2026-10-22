#include "SBNullstr.h"
#include "sbgeo_00610600.h"

// FUNCTION: GAME 0x0060a840
SBGeoSegment2D::SBGeoSegment2D(const SBGeoSegment2D &other)
{
    ((RHMobileUnk0060a820 *)this)->FUN_006158b0(*(const SBGeoPoint2D *)&other,
        *(const SBGeoPoint2D *)((const char *)&other + 8));
}
bool RHMobileUnk0060a820::FUN_0060a990(const RHMobileUnk0060a820 &) const { return false; }
