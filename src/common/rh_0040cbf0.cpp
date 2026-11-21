#include "RHElementCore.h"
#include "RHSpriteCore.h"
#include <stddef.h>

DECOMP_STATIC_ASSERT(offsetof(RHElement, m_50) == 0x50)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_c) == 0x10)

// FUNCTION: GAME 0x004237d0
SBGeoPoint2D RHElement::FUN_004237d0() const
{
    return SBGeoPoint2D(m_50->m_c.x, m_50->m_c.y);
}
