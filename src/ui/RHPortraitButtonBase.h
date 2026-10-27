#ifndef RHPORTRAITBUTTONBASE_H
#define RHPORTRAITBUTTONBASE_H

#include "RHGameWidgetLifetime.h"
#include "RHPortraitRenderer005cadc0.h"

// VTABLE: GAME 0x0067a0a8
class RHPortraitButtonBase : public RHGameWidgetLifetimeBase
{
public:
    RHPortraitButtonBase() {}
    ~RHPortraitButtonBase() {}
    void *FUN_005d24f0(unsigned flags);
    void FUN_005d24c0();
    void FUN_005d24e0();
    RHPortraitRenderer005cadc0 m_renderer;
};

#endif
