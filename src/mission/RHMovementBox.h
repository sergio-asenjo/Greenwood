#ifndef RHMOVEMENTBOX_H
#define RHMOVEMENTBOX_H

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif

struct RHMovementBox
{
    void Center(SBGeoPoint2D &point) const
    {
        point.m_x = (m_0c + m_04) * 0.5f;
        point.m_y = (m_10 + m_08) * 0.5f;
    }
    char m_00[4];
    float m_04;
    float m_08;
    float m_0c;
    float m_10;
};

#endif
