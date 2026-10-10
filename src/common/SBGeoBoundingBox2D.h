#ifndef SB_GEO_BOUNDING_BOX_2D_H
#define SB_GEO_BOUNDING_BOX_2D_H

#include "SB.h"

class SBGeoBoundingBox2D
{
public:
    bool Serialize(SBFile &file);
    char m_00[0x14];
};

#endif
