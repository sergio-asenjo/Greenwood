#ifndef RHPATHOBSTACLEGRID_H
#define RHPATHOBSTACLEGRID_H

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

class RHPathObstacleGrid
{
public:
    bool FUN_004f5750(SBGeoBoundingBox2D &box, unsigned short sector);
    bool FUN_004f5890(SBGeoBoundingBox2D &box, unsigned short sector);
    bool FUN_004f9260(const SBGeoPoint2D &first, const SBGeoPoint2D &last, unsigned short layer);
    char m_00[0x3e84];
    SBGeoBoundingBox2D m_3e84;
};

#endif
