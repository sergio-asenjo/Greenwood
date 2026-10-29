#ifndef RHMOBILEVECTORARRAY_H
#define RHMOBILEVECTORARRAY_H

#include "RHFastFindGeometry.h"
#include <vector>

// SIZE 0x24
class RHMobileVectorArray : public std::vector<SBGeoVector2D>
{
public:
    RHMobileVectorArray() : m_14(true) {}
    ~RHMobileVectorArray();
    void Destroy() { clear(); }
    unsigned m_10;
    bool m_14;
    unsigned m_18;
    SBGeoVector2D m_1c;
};

#endif
