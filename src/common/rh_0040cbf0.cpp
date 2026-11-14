#include "RHActorWorldPoint.h"
#include "Decomp.h"
#include <stddef.h>

DECOMP_SIZE_ASSERT(RHUnk004237d0, 0x54)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004237d0, m_50) == 0x50)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004237d0Holder, m_10) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHUnk004237d0Holder, m_14) == 0x14)

// FUNCTION: GAME 0x004237d0
SBGeoPoint2D RHUnk004237d0::FUN_004237d0()
{
    return SBGeoPoint2D(m_50->m_10, m_50->m_14);
}
