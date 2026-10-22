#include "RHDrawManager.h"

// Target 0x0060fc90.
RHUnk0060fbf0::~RHUnk0060fbf0() {}

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
};

// FUNCTION: GAME 0x006092c0
SBGeoBoundingBox2D SBGeoBoundingBox2D::FUN_006092c0(const SBGeoBoundingBox2D &other) const
{
    SBGeoBoundingBox2D result;
    ((RHMobileUnk00607da0 *)&result)->FUN_00607da0((const RHMobileUnk00607da0 &)other);
    if (!m_10 || ((RHUnk00608f10 *)this)->FUN_006082a0(&result))
    {
        result.FUN_00607d90();
        return result;
    }
    if (result.m_min.m_x < m_min.m_x) result.m_min.m_x = m_min.m_x;
    if (result.m_max.m_x > m_max.m_x) result.m_max.m_x = m_max.m_x;
    if (result.m_min.m_y < m_min.m_y) result.m_min.m_y = m_min.m_y;
    if (result.m_max.m_y > m_max.m_y) result.m_max.m_y = m_max.m_y;
    return result;
}

RHUnk0060fbf0 SBGeoBoundingBox2D::FUN_00609440(const RHMobileUnk006100e0 &, double, double) const { return RHUnk0060fbf0(); }

// Target 0x005e61e0.

// Target 0x005ecbd0.
bool SBDrawManager::FUN_005ecbd0(unsigned long, const SBGeoPoint2D &, const SBGeoPoint2D &, unsigned short) { return false; }
