#ifndef RHELEMENTGRID_H
#define RHELEMENTGRID_H

#include "Decomp.h"

class SBGeoPoint2D;

class RHElementGrid
{
public:
    void FUN_004e89d0(void *list, int cell, unsigned mask);
    short FUN_004e8fc0(const SBGeoPoint2D &point, const SBGeoPoint2D &origin, short layer, void *&sector);
    undefined m_00[0x3e98];
    unsigned short m_3e98;
    unsigned short m_3e9a;
    undefined m_3e9c[0x1a0];
    undefined *m_403c;
    undefined m_4040[0x148];
    void *m_4188;
};

#endif
