#include "RHMenuMissionDescription.h"
#include "RHGameMenuCalls.h"
#include "RHGame.h"
#include "RHEngine.h"
#include "RHMission.h"

class RHUnk0048a970;
class RHUnk00452030;
extern RHUnk0048a970 *g_unk0x6c0b3c;
extern RHUnk00452030 *g_unk0x6c07fc;
extern RHEngine *g_pEngine;

DECOMP_SIZE_ASSERT(RHMenuMissionDescription, 0x938)

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
    menu->GetUserChoice();
    menu->FUN_00535620(0);
    menu->FUN_005357e0(0, 0, 0);
    menu->FUN_005358d0(0, 0, 0);
    menu->FUN_00535910(0, 0, 0);
}
