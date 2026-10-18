#include "sbgeo_0060ff30.h"

struct RHUnk00412160Source
{
    char m_00[0x64];
    short m_64;
    short m_66;
};

// FUNCTION: GAME 0x00412160
SBGeoPoint2D __stdcall FUN_00412160(const RHUnk00412160Source *source)
{
    return SBGeoPoint2D((float)source->m_64, (float)source->m_66);
}
