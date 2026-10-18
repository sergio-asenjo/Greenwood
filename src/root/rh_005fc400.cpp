#include "SBGeoPoint2D.h"

#include "RHUnk005fc400.h"

// FUNCTION: GAME 0x005fc400
RHUnk005fc400::RHUnk005fc400(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
    : SBGeoPoint2D(second.m_x - first.m_x, second.m_y - first.m_y)
{
}
