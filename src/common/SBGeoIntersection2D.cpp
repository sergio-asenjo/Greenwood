#include "sbgeo_0060ff30.h"
#include <new>
#include "SBGeoSegment2D.h"

void EmitSBGeoIntersection2D(RHUnk0060fbf0 *intersection, const SBGeoPoint2D &point, const RHMobileUnk006100e0 &line)
{
    intersection->FUN_0060fdc0(point);
    intersection->FUN_0060fe20(line);
    RHUnk0060fbf0 copy(line);
}

// FUNCTION: GAME 0x0060fc20
RHUnk0060fbf0::RHUnk0060fbf0(const RHMobileUnk006100e0 &line)
{
    m_0 = 4;
    m_2 = 0;
    m_4 = 0;
    m_8 = new SBGeoSegment2D(*(const SBGeoSegment2D *)&line);
}

// FUNCTION: GAME 0x0060fdc0
void RHUnk0060fbf0::FUN_0060fdc0(const SBGeoPoint2D &point)
{
    FUN_0060fce0();
    m_0 = 1;
    m_8 = new SBGeoPoint2D(point);
}

// FUNCTION: GAME 0x0060fe20
void RHUnk0060fbf0::FUN_0060fe20(const RHMobileUnk006100e0 &line)
{
    FUN_0060fce0();
    m_0 = 4;
    m_8 = new SBGeoSegment2D(*(const SBGeoSegment2D *)&line);
}
