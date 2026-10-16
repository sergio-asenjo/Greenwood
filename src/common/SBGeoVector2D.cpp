#include "RHSprite_calls.h"

// FUNCTION: GAME 0x005fc5b0
RHUnk005fc3b0 &RHUnk005fc3b0::FUN_005fc5b0(float factor)
{
    m_x /= factor;
    m_y /= factor;
    return *this;
}

// FUNCTION: GAME 0x005fc660
float SBGeoVector2D::FUN_005fc660(const SBGeoPoint2D &other) const
{
    return other.m_y * m_y + other.m_x * m_x;
}
