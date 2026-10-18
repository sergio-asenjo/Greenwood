#ifndef RHUNK0060C2XX_H
#define RHUNK0060C2XX_H

#include "sbgeo_00610600.h"

class RHUnk0060c2xx : public SBGeoPolyLine2DList
{
public:
    unsigned long FUN_0060c250() const;
    void FUN_0060c260(const SBGeoPoint2D &point);
    void FUN_0060c280();
    void FUN_0060c290(unsigned long index);
    const SBGeoPoint2D &FUN_0060c2b0(unsigned long index) const;

    short m_28;
    short m_2a;
    bool m_2c;
    bool m_2d;
};

#endif
