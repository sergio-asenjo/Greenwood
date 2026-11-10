#ifndef RHARCHERYPOINT_H
#define RHARCHERYPOINT_H

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif

class SBFile;

// VTABLE: GAME 0x00679140
// SIZE 0x1c
class RHUnk00522540 : public SBGeoPoint2D
{
public:
    RHUnk00522540();
    virtual ~RHUnk00522540();
    void Unk005225a0(SBFile &file);
    bool FUN_00522680(SBFile &file);
    undefined2 m_c;
    undefined2 m_e;
    void *m_10;
    undefined m_14;
    undefined m_15;
    undefined2 m_16;
    void *m_18;
};

#endif
