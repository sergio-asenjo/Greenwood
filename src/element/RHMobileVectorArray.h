#ifndef RHMOBILEVECTORARRAY_H
#define RHMOBILEVECTORARRAY_H

#if !defined(RHFASTFINDGEOMETRY_H) && !defined(SBGEO_VECTOR2D_VIEW)
#include "SBGeoVector2D.h"
#endif
#include <vector>

// SIZE 0x24
class RHMobileVectorArray : public std::vector<SBGeoVector2D>
{
public:
    RHMobileVectorArray() : m_14(true) {}
    // FUNCTION: GAME 0x004afac0
    ~RHMobileVectorArray() { Destroy(); }
    void Destroy() { clear(); }
    unsigned m_10;
    bool m_14;
    unsigned m_18;
    SBGeoVector2D m_1c;
};

#endif
