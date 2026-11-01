#ifndef RHBONUSPROJECTION_H
#define RHBONUSPROJECTION_H

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

class RHSector;

struct RHBonusProjection
{
    unsigned m_0;
    unsigned short Flags() const { return (unsigned short)(m_0 >> 2); }
    bool Inside(const SBGeoPoint2D &point) const { return m_38.FUN_00608400(point); }
    char m_pad4[0x1c];
    float m_20;
    char m_pad24[0x14];
    SBGeoBoundingBox2D m_38;
    char m_pad4c[0x148];
    RHSector *m_194;
};

#endif
