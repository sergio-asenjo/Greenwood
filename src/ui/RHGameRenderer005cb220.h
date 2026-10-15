#ifndef RHGAMERENDERER005CB220_H
#define RHGAMERENDERER005CB220_H

#include "Decomp.h"
#include "RHRendererGeometry.h"

class SBUIUnk006006f0;
class RHUnk005ef320;

class RHPictureRenderer0060d9f0
{
public:
    RHPictureRenderer0060d9f0();
    undefined4 m_vptr;
    SBUIUnk006006f0 *m_resource;
    SBGeoBoundingBox2D m_box;
    RHUnk005ef320 *m_draw;
    unsigned long m_target;
    undefined m_24[0x14];
    long m_resourceId;
    undefined m_3c[4];
    long m_40;
    long m_44;
    undefined m_48[4];
};

class RHGameRenderer005cb220 : public RHPictureRenderer0060d9f0
{
public:
    RHGameRenderer005cb220();
    ~RHGameRenderer005cb220();
    void *FUN_005cb240(unsigned flags);
    bool FUN_005cb270(unsigned id);
    void FUN_005cb2a0();
    void FUN_005cb2b0(int value);
    long m_alternate;
};

#endif
