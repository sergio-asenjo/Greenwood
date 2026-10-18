#ifndef SBGEO_INTERSECTION2D_H
#define SBGEO_INTERSECTION2D_H

#include "Decomp.h"

class SBGeoPoint2D;
class RHMobileUnk006100e0;

// SIZE 0x0c
class RHUnk0060fbf0
{
public:
    RHUnk0060fbf0();
    RHUnk0060fbf0(const RHUnk0060fbf0 &other);
    RHUnk0060fbf0(const RHMobileUnk006100e0 &line);
    ~RHUnk0060fbf0();
    void FUN_0060fa20();
    void FUN_0060fa30(const RHUnk0060fbf0 &other);
    RHUnk0060fbf0 &FUN_0060fca0(const RHUnk0060fbf0 &other);
    unsigned short FUN_0060fcc0() const;
    unsigned short FUN_0060fcd0() const;
    void FUN_0060fce0();
    void FUN_0060fdb0();
    void FUN_0060fdc0(const SBGeoPoint2D &point);
    void FUN_0060fe20(const RHMobileUnk006100e0 &line);
    undefined m_0; // 0x00
    undefined m_1; // 0x01
    undefined2 m_2; // 0x02
    undefined2 m_4; // 0x04
    undefined2 m_6; // 0x06
    void *m_8; // 0x08
};

#endif
