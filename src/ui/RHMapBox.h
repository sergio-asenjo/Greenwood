#ifndef RHMAPBOX_H
#define RHMAPBOX_H

#ifndef SBGEO_POINT2D_VIEW
#include "RHRendererGeometry.h"
#endif

class RHMapBox
{
public:
    RHMapBox(float, float, float, float);
    ~RHMapBox() {}
    SBGeoPoint2D m_0;
    SBGeoPoint2D m_8;
    bool m_10;
};

#endif
