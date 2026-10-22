#ifndef RHMENUBUYBLAZONS_H
#define RHMENUBUYBLAZONS_H

#include <string>
#include "RHMenuFocusClass.h"
#include "RHGameWidgetLifetime.h"

// VTABLE: GAME 0x00679150
class RHMenuBuyBlazons : public RHMenuWindowFocus
{
public:
    RHMenuBuyBlazons(RHMenuWindow *parent, RHMenuWindowScreen *screen);
    ~RHMenuBuyBlazons();
    void *FUN_00524cf0(unsigned flags);
    bool Create(class RHMission *mission, class RHMenuShortMissionBlazons *blazons);
    RHPortraitButton m_ok;
    RHPortraitButton m_cancel;
    RHGameLifetime00525560 m_title;
    unsigned m_440;
    unsigned m_444;
    void *m_448;
};

#endif
