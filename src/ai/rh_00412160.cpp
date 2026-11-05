#include "sbgeo_0060ff30.h"

#include "RHWaypoint.h"
#include "RHArtificialIntelligenceCore.h"

// FUNCTION: GAME 0x00412160
SBGeoPoint2D RHArtificialIntelligence::FUN_00412160(const RHWaypoint *source)
{
    return SBGeoPoint2D((float)source->m_64, (float)source->m_66);
}
