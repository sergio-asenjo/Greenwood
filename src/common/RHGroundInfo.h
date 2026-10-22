#ifndef RHGROUNDINFO_H
#define RHGROUNDINFO_H

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif

class RHUnk00606040 : public SBGeoPoint2D
{
public:
    RHUnk00606040() {}
    RHUnk00606040(const RHUnk00606040 &other);
    ~RHUnk00606040() {}
    void *Destroy(unsigned flags);
    unsigned short m_a;
    unsigned short m_b;
};

typedef RHUnk00606040 RHGroundInfo;

#endif
