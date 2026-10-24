#ifndef RHMISSIONDESCRIPTIONTEXT_H
#define RHMISSIONDESCRIPTIONTEXT_H

#include "rhuirenderer_005cb420.h"
#include "RHGameWidgetLifetime.h"

// VTABLE: GAME 0x006793f0
class RHMissionDescriptionTextBase : public RHGameWidgetLifetimeBase
{
public:
    RHMissionDescriptionTextBase() {}
    ~RHMissionDescriptionTextBase() {}
    void *FUN_0052bdf0(unsigned flags);
    RHUnk005cba10 m_renderer;
};

class __declspec(novtable) RHMissionDescriptionText : public RHMissionDescriptionTextBase
{
public:
    RHMissionDescriptionText()
    {
        *(unsigned *)this = 0x006793b8;
        m_dirtyFirst = true;
        m_dirtySecond = true;
    }
    ~RHMissionDescriptionText()
    {
    }
    void *FUN_0052bec0(unsigned flags);
    bool m_dirtyFirst;
    bool m_dirtySecond;
};

#endif
