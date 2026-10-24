// RHMenuShortMissionDescription.cpp — the short mission description menu TU
// (code 0x00540730..0x005412cb). See RHMenuShortMissionDescription.h for the
// binding evidence.

#include "SBNullstr.h"
#include "RHMenuShortMissionDescription.h"
#include "RHMapBox.h"
#include "RHMapResources.h"
#include "RHShortMissionUpdateCalls.h"
#include "RHMission.h"
#include "RHGameBlazonWidget.h"

extern RHEngine *g_pEngine;
extern RHMapResources *g_unk0x006c1840;

class RHShortMissionWidgetCalls
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c(const std::wstring &);
    virtual void V30();
    virtual void V34();
    virtual void V38(unsigned);
};

// FUNCTION: GAME 0x00540730
RHMenuShortMissionDescription::RHMenuShortMissionDescription(RHMenuWindowScreen *screen)
    : RHMenuWindow(0, screen, false), m_blazons(0), m_mission(0)
{
}

// FUNCTION: GAME 0x00540830
void *RHMenuShortMissionDescription::FUN_00540830(unsigned flags)
{
    this->~RHMenuShortMissionDescription();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00540850
RHMenuShortMissionDescription::~RHMenuShortMissionDescription()
{
    FUN_00540d20();
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_title);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_text);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_picture);
}

// FUNCTION: GAME 0x00540d20
void RHMenuShortMissionDescription::FUN_00540d20()
{
    if (m_blazons)
    {
        delete m_blazons;
        m_blazons = 0;
    }
}

// FUNCTION: GAME 0x00540d50
std::wstring RHMenuShortMissionDescription::FUN_00540d50()
{
    RHDialogueSet *resources = g_pEngine->GetDynResources(**(unsigned long **)m_mission);
    RHMapResources *manager = g_unk0x006c1840;
    std::wstring text;
    if (!resources)
        text =
            // STRING: GAME 0x006b10a4
            L"Unable to get the dynamic resouces...";
    else if (!manager->FUN_006009e0(*(unsigned *)resources, 1, (RHMapWideText &)text))
        text =
            // STRING: GAME 0x006b0e48
            L"Invalid resource ID...";
    return text;
}

// FUNCTION: GAME 0x00540ed0
void RHShortMissionUpdateCalls::FUN_00540ed0(RHMission *mission)
{
    RHMenuShortMissionDescription *menu = (RHMenuShortMissionDescription *)this;
    if (menu->m_mission != mission)
    {
        menu->m_mission = mission;
        ((RHShortMissionWidgetCalls *)&menu->m_title)->V2c(menu->FUN_00540d50());
        menu->FUN_00540d20();
        if (mission && (char)mission->FUN_0054cbf0())
        {
            menu->m_blazons = new RHMenuShortMissionBlazons(mission, this);
            menu->m_blazons->FUN_0044ef60(RHMapBox(5.0f, 80.0f, 215.0f, 95.0f), false);
        }
        unsigned picture = *(unsigned short *)((char *)mission->m_profile + 0x4c) - (unsigned short)mission->m_4 - 1;
        if (picture <= 3)
            ((RHShortMissionWidgetCalls *)&menu->m_picture)->V38(picture);
        else
            ((RHShortMissionWidgetCalls *)&menu->m_picture)->V38(4);
    }
    if (mission && (char)mission->FUN_0054cbf0())
        ((RHGameBlazonValue *)menu->m_blazons)->FUN_0044f960(0);
}

void EmitRHShortMissionUpdate(RHMenuShortMissionDescription *menu, RHMission *mission)
{
    ((RHShortMissionUpdateCalls *)menu)->FUN_00540ed0(mission);
}
