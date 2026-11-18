#ifndef RHUNKSECTORPOINTS_H
#define RHUNKSECTORPOINTS_H

#include "sbgeo_00610600.h"

class SBGeoPoint2D;

class RHUnkSectorPoints : public RHMobileUnk00611360
{
public:
    RHUnkSectorPoints();
    float FUN_0060cab0(const SBGeoPoint2D &point, float scale);
    unsigned int Unk0060ce80();
    SBGeoPoint2D &Unk0060cef0(unsigned int index);
    void Unk0060ced0(const SBGeoPoint2D &point, unsigned int index);
    void FUN_0060ce90(const SBGeoPoint2D &point, unsigned int index);
    void FUN_0060ceb0(const SBGeoPoint2D &point);
    unsigned short FUN_0060c2e0();
    unsigned short m_24;
    unsigned short m_26;
    bool m_28;
    bool m_29;
};

#endif
