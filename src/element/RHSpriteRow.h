#ifndef RHSPRITEROW_H
#define RHSPRITEROW_H

#include <vector>
#include "Decomp.h"
#ifndef SBGEO_VECTOR2D_VIEW
#include "SBGeoVector2D.h"
#endif

struct RHUnkSpriteRow
{
    RHUnkSpriteRow();
    undefined2 m_00;
    float m_04;
    SBGeoPoint2D m_position;
    undefined2 m_10;
    std::vector<int> m_resources;
    std::vector<unsigned short> m_frames;
    std::vector<unsigned short> m_rates;
    std::vector<SBGeoVector2D> m_positions;
    std::vector<unsigned short> m_flags;
};

#endif
