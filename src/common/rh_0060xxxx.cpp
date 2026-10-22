#include "SBGeoPoint2D.h"

#include "RHGroundInfo.h"

// FUNCTION: GAME 0x00606040
RHUnk00606040::RHUnk00606040(const RHUnk00606040 &other)
    : SBGeoPoint2D(other)
{
    m_a = other.m_a;
    m_b = other.m_b;
}
