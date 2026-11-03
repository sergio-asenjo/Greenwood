#ifndef RHAMBUSHPOINT_H
#define RHAMBUSHPOINT_H

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

class SBFile;

class RHUnk00521550Part
{
public:
    RHUnk00521550Part();
    float m_0;
    float m_4;
    float m_8;
};

// VTABLE: GAME 0x00679130
class RHUnk00521550
{
public:
    RHUnk00521550();
    virtual ~RHUnk00521550();
    void FUN_005215f0(SBFile &file);
    float m_4;
    float m_8;
    void *m_c;
    unsigned short m_10;
    RHUnk00521550Part m_14;
    SBGeoBoundingBox2D m_20;
    unsigned short m_34;
};

#endif
