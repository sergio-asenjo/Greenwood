#include "RHDrawManager.h"

#include "RHMobileUnk00607da0.h"

// FUNCTION: GAME 0x006092c0
SBGeoBoundingBox2D SBGeoBoundingBox2D::FUN_006092c0(const SBGeoBoundingBox2D &other) const
{
    SBGeoBoundingBox2D result;
    ((RHMobileUnk00607da0 *)&result)->FUN_00607da0((const RHMobileUnk00607da0 &)other);
    if (!m_flag || ((RHUnk00608f10 *)this)->FUN_006082a0(&result))
    {
        result.FUN_00607d90();
        return result;
    }
    if (result.m_p0.m_x < m_p0.m_x) result.m_p0.m_x = m_p0.m_x;
    if (result.m_p1.m_x > m_p1.m_x) result.m_p1.m_x = m_p1.m_x;
    if (result.m_p0.m_y < m_p0.m_y) result.m_p0.m_y = m_p0.m_y;
    if (result.m_p1.m_y > m_p1.m_y) result.m_p1.m_y = m_p1.m_y;
    return result;
}


// Target 0x005e61e0.
