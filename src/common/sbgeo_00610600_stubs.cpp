#include "SBNullstr.h"
#include "sbgeo_00610600.h"

// FUNCTION: GAME 0x0060a840
SBGeoSegment2D::SBGeoSegment2D(const SBGeoSegment2D &other)
{
    reinterpret_cast<RHMobileUnk0060a820 *>(m_00)->RHMobileUnk0060a820::RHMobileUnk0060a820(other.First(), other.Second());
}
