#ifndef RHMENUMISSIONDESCRIPTION_H
#define RHMENUMISSIONDESCRIPTION_H

#include "RHMenuFocusClass.h"
#include "rhuirenderer_005cb420.h"
#include "RHMenuShortMissionTitle.h"
#include "RHMenuShortMissionBlazons.h"

class RHMission;

// VTABLE: GAME 0x006793f0
class RHMissionDescriptionTextBase : public RHGameWidgetLifetimeBase
{
public:
    RHMissionDescriptionTextBase() {}
    ~RHMissionDescriptionTextBase() {}
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
    bool m_dirtyFirst;
    bool m_dirtySecond;
};

// VTABLE: GAME 0x00679678
class RHMenuMissionDescription : public RHMenuWindowFocus
{
public:
    RHMenuMissionDescription(RHMenuWindow *parent, RHMenuWindowScreen *screen, RHMission *mission);
    ~RHMenuMissionDescription();
    void *FUN_00534580(unsigned flags);
    bool Create();
    void RouteEvent(struct RHMenuEvent *event);
    bool HandleEvent(struct RHMenuEvent *event);
    static unsigned long FUN_00535620(const RHMission *mission);
    int GetUserChoice() const;
    bool FUN_005357e0(int message, void *widget, void *data);
    bool FUN_00535800(int message, void *widget, void *data);
    bool FUN_005358d0(int message, void *widget, void *data);
    bool FUN_00535910(int message, void *widget, void *data);

    RHPortraitButton m_buy;
    RHPortraitButton m_start;
    RHPortraitButton m_accept;
    RHPortraitButton m_cancel;
    RHPortraitButton m_close;
    RHGameLifetime00515f00 m_picture;
    RHMenuShortMissionTitle m_title;
    RHMissionDescriptionText m_text;
    RHMission *m_mission;
    RHMenuShortMissionBlazons *m_930;
    int m_choice;
};

#endif
