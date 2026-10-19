#ifndef RHGAMERENDERER005CB220_H
#define RHGAMERENDERER005CB220_H

#include "Decomp.h"
#include "RHRendererGeometry.h"
#include "RHGameWidgetLifetime.h"

class RHGameRenderer005cb220 : public RHGameRenderer0060da10
{
public:
    RHGameRenderer005cb220();
    void *FUN_005cb240(unsigned flags);
    bool FUN_005cb270(unsigned id);
    void FUN_005cb2a0();
    void FUN_005cb2b0(int value);
    long m_alternate;
};

#endif
