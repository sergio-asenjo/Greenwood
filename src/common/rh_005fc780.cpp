#include "SBGeoVector2D.h"

// FUNCTION: GAME 0x005fc780
float SBGeoVector2D::FUN_005fc780(float divisor) const
{
    float b = m_y / divisor;
    if (m_x > 0.0f)
    {
        if (b > 0.0f)
            return m_x + b;
        return m_x - b;
    }
    if (b > 0.0f)
        return b - m_x;
    return -m_x - b;
}

void EmitRHUnk005fc780(SBGeoVector2D *self)
{
    float (SBGeoVector2D::*f)(float) const = &SBGeoVector2D::FUN_005fc780;
    (self->*f)(1.0f);
}
