#ifndef RHUNKSECTORPOINTS_H
#define RHUNKSECTORPOINTS_H

#include "Decomp.h"

class SBGeoPoint2D;

class RHUnkSectorPoints
{
public:
    unsigned int Unk0060ce80();
    SBGeoPoint2D &Unk0060cef0(unsigned int index);
    void Unk0060ced0(const SBGeoPoint2D &point, unsigned int index);
    SBGeoPoint2D &FUN_006112c0(unsigned int index);
    void FUN_006112a0(const SBGeoPoint2D &point, unsigned int index);
    void FUN_0060ce90(const SBGeoPoint2D &point, unsigned int index);
    void FUN_0060ceb0(const SBGeoPoint2D &point);
    void FUN_0060c2e0();
    undefined m_00[0x24];
    unsigned short m_24;
    unsigned short m_26;
    undefined m_28;
    undefined m_29;
    undefined m_2a[2];
};

#endif
