#include "RHMenuMissionDescription.h"
#include "RHGameMenuCalls.h"
#include "RHGame.h"
#include "RHEngine.h"
#include "RHMission.h"
#include "RHMenuCloseCalls.h"
#include "RHMenuBuyBlazons.h"
#include "RHGameCampaignView.h"
#include "RHGameBlazonWidget.h"
#include "RHMapWindowClass.h"

struct RHMenuEvent
{
    int m_type;
    void *m_widget;
    void *m_data;
};

class RHUnk0048a970
{
public:
    void Unk(int);
};

class RHUnk00452030;
extern RHUnk0048a970 *g_unk0x6c0b3c;
extern RHUnk00452030 *g_unk0x6c07fc;
extern RHEngine *g_pEngine;

DECOMP_SIZE_ASSERT(RHMenuMissionDescription, 0x938)

// FUNCTION: GAME 0x00534300
void RHMenuMissionDescription::RouteEvent(RHMenuEvent *event)
{
    if (HandleEvent(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x00534320
bool RHMenuMissionDescription::HandleEvent(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x540)
        handled = ((RHMenuCloseCalls *)this)->FUN_0052b520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x340)
        handled = FUN_005357e0(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x140)
        handled = FUN_00535800(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x240)
        handled = FUN_005358d0(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x440)
        handled = FUN_00535910(2, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x005343e0
RHMenuMissionDescription::RHMenuMissionDescription(RHMenuWindow *parent, RHMenuWindowScreen *screen, RHMission *mission)
    : RHMenuWindowFocus(parent, screen, 0x93, 1, false), m_mission(mission), m_930(0), m_choice(2)
{
    m_930 = new RHMenuShortMissionBlazons(mission, this);
}

// FUNCTION: GAME 0x00534580
void *RHMenuMissionDescription::FUN_00534580(unsigned flags)
{
    this->~RHMenuMissionDescription();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005345a0
RHMenuMissionDescription::~RHMenuMissionDescription()
{
    delete m_930;
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_buy);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_start);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_accept);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_cancel);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_close);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_picture);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_title);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_text);
}

// FUNCTION: GAME 0x00535620
unsigned long RHMenuMissionDescription::FUN_00535620(const RHMission *mission)
{
    RHDialogueSet *resources = g_pEngine->GetDynResources(*(unsigned long *)mission->m_profile);
    if (resources)
        return *(unsigned long *)((char *)resources + 4);
    return 0xa4;
}

// FUNCTION: GAME 0x005357d0
int RHMenuMissionDescription::GetUserChoice() const
{
    return m_choice;
}

// FUNCTION: GAME 0x005357e0
bool RHMenuMissionDescription::FUN_005357e0(int, void *, void *)
{
    m_choice = 1;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}

// FUNCTION: GAME 0x00535800
bool RHMenuMissionDescription::FUN_00535800(int, void *, void *)
{
    RHMenuBuyBlazons menu((RHMenuWindow *)this, m_screen);
    menu.Create(m_mission, m_930);
    menu.FUN_00544b80(true, true);
    menu.FUN_00544300();
    ((RHGameBlazonValue *)m_930)->FUN_0044f960(0);
    *(volatile char *)&m_buy.m_04 = (char)((RHGameCampaignView *)g_unk0x6c07fc)->FUN_00456230((RHGameMission *)m_mission);
    ((RHMapWindow *)m_screen)->FUN_0053c7e0();
    return true;
}

// FUNCTION: GAME 0x005358d0
bool RHMenuMissionDescription::FUN_005358d0(int, void *, void *)
{
    ((RHGame *)g_unk0x6c0b3c)->FUN_0050ed10(true);
    *(RHMission **)((char *)g_unk0x6c07fc + 0x17c) = m_mission;
    m_choice = 0;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}

// FUNCTION: GAME 0x00535910
bool RHMenuMissionDescription::FUN_00535910(int, void *, void *)
{
    *(RHMission **)((char *)g_unk0x6c07fc + 0x17c) = m_mission;
    ((RHGame *)g_unk0x6c0b3c)->FUN_0050ed10(false);
    m_choice = 0;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}

void EmitRHMenuMissionDescription(RHMenuMissionDescription *menu)
{
    menu->RouteEvent(0);
    menu->GetUserChoice();
    menu->FUN_00535620(0);
    menu->FUN_005357e0(0, 0, 0);
    menu->FUN_005358d0(0, 0, 0);
    menu->FUN_00535910(0, 0, 0);
}
