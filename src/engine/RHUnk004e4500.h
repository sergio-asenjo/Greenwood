#ifndef RH_UNK_004E4500_H
#define RH_UNK_004E4500_H

#include "Decomp.h"
#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include "SBGeoSegment2D.h"
#include <vector>

// SIZE 0x2c
class RHUnk004e4500
{
public:
    RHUnk004e4500();
    ~RHUnk004e4500();
    std::vector<SBGeoSegment2D> m_segments; // 0x00
    undefined4 m_10; // 0x10
    bool m_dirty; // 0x14
    undefined m_15[7]; // 0x15
    SBGeoSegment2D m_1c; // 0x1c
};

DECOMP_SIZE_ASSERT(RHUnk004e4500, 0x2c)

// FUNCTION: GAME 0x004e4500
inline RHUnk004e4500::RHUnk004e4500()
    : m_dirty(true), m_1c(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f))
{
}

#endif
