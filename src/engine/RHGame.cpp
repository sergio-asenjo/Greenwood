#include "SBNullstr.h"
#include "RHGame_calls.h"
#include "SBThreadedInput.h"
#include <vector>
#include <algorithm>
#include <memory.h>

DECOMP_SIZE_ASSERT(RHGame, 0x357c)
DECOMP_SIZE_ASSERT(RHGameMissionProfile, 0x6c)
DECOMP_SIZE_ASSERT(RHGameMission, 0x0c)
DECOMP_SIZE_ASSERT(RHGameCampaignView, 0x184)
DECOMP_SIZE_ASSERT(RHGameBlazonWidget, 0xb4)
DECOMP_SIZE_ASSERT(RHGameSaveHeader, 0x0c)
DECOMP_SIZE_ASSERT(SBArray<RHSaveGame *>, 0x10)
DECOMP_SIZE_ASSERT(RHGameSaveOwner, 0x04)
DECOMP_SIZE_ASSERT(RHMapDescription::Entry, 0x48)
DECOMP_SIZE_ASSERT(RHGameConfig, 0x38)
DECOMP_SIZE_ASSERT(RHGameConfigTriple, 0x0c)

// GLOBAL: GAME 0x006c12b6
unsigned char g_unk0x006c12b6;

#define RHGAME_ACCESS(member, line) \
    if (file.Access(&member, 1) < 0) \
    { \
        SBString *error = file.GetError(); \
        SBAssert(0, "P:\\Robin Hood\\RHgame.cpp", line, "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }

// Parked: 66.67%; string cleanup, iterator scheduling, and annotated SelectMissions calls.
// STUB: GAME 0x00451a90
void RHGameCampaignView::FUN_00451a90()
{
    std::wstring scratch;
    RHGameMission *mission = *(RHGameMission **)((char *)this + 0x148) + 1;
    for (; mission != *(RHGameMission **)((char *)this + 0x14c); ++mission)
    {
        if (mission->FUN_0054c800())
        {
            RHGameMission **first = *(RHGameMission ***)((char *)this + 0x158);
            RHGameMission **last = *(RHGameMission ***)((char *)this + 0x15c);
            first = std::find(first, last, mission);
            if (first == last)
            {
                ((SBArray<RHSaveGame *> *)((char *)this + 0x154))->Insert(
                    *(RHSaveGame ***)((char *)this + 0x15c), 1, (RHSaveGame *const &)mission);
                mission->m_08 = 0;
            }
        }
    }
    ((RHCampaign *)this)->SelectMissions(false);
    ((RHCampaign *)this)->SelectMissions(true);
}

// FUNCTION: GAME 0x00453b70
void RHGameCampaignView::FUN_00453b70(RHGameMission *mission)
{
    std::vector<RHGameMission *> &missions = *(std::vector<RHGameMission *> *)((char *)this + 0x154);
    for (std::vector<RHGameMission *>::iterator it = missions.begin(); it != missions.end(); ++it)
    {
        if (*it == mission)
        {
            mission->m_04 = 0;
            missions.erase(it);
            return;
        }
    }
}

// FUNCTION: GAME 0x00456190
int RHGameCampaignView::FUN_00456190(RHGameMission *mission)
{
    int cost = (int)mission->m_profile->m_68 - (int)mission->m_profile->m_6a;
    if (*(int *)((char *)this + 0xa0) < cost &&
        FUN_00456270() >= *(unsigned short *)((char *)mission->m_profile + 0x70))
        return 1;
    return 0;
}

// FUNCTION: GAME 0x004561d0
int RHGameCampaignView::FUN_004561d0(RHGameMission *mission)
{
    RHGameMission **first = *(RHGameMission ***)((char *)this + 0x168);
    RHGameMission **last = *(RHGameMission ***)((char *)this + 0x16c);
    if (first && last - first != 0 &&
        ((int)mission->m_04 + 1 < *(unsigned short *)((char *)mission->m_profile + 0x4c) || mission->m_profile->m_34 == 5))
    {
        int cost = (int)mission->m_profile->m_68 - (int)mission->m_profile->m_6a;
        if (*(int *)((char *)this + 0xa0) < cost)
            return 1;
    }
    return 0;
}

// FUNCTION: GAME 0x00456230
int RHGameCampaignView::FUN_00456230(RHGameMission *mission)
{
    if ((int)mission->m_06 <= *(int *)((char *)this + 0x98))
    {
        int cost = (int)mission->m_profile->m_68 - (int)mission->m_profile->m_6a;
        if (*(int *)((char *)this + 0xa0) < cost)
            return 1;
    }
    return 0;
}

// FUNCTION: GAME 0x00456540
void RHGameCampaignView::FUN_00456540(bool flag, RHGameMission *mission)
{
    if (!mission)
        mission = m_178;
    if (flag)
    {
        FUN_00456e40(*((char *)mission->m_profile + 0x60));
        mission->m_08 = 1;
    }
    else
    {
        FUN_00456e40(*((char *)mission->m_profile + 0x61));
        mission->m_08 = 2;
        if (mission == m_180)
            ((RHScriptBatchCalls *)this)->Unk004520e0(3, 0);
    }
    if (mission == m_180 && mission->m_profile->m_34 == 5)
    {
        *(unsigned *)((char *)this + 0x1ac) = *(unsigned *)mission->m_profile;
        *(unsigned *)((char *)this + 0x1a8) = mission->m_08;
    }
}

// TEMPLATE: GAME 0x00509430
// ?_Ucopy@?$vector@VRHUnk005069a0@@V?$allocator@VRHUnk005069a0@@@std@@@std@@IAEPAVRHUnk005069a0@@PBV3@0PAV3@@Z

// TEMPLATE: GAME 0x00509470
// ?_Ufill@?$vector@VRHUnk005069a0@@V?$allocator@VRHUnk005069a0@@@std@@@std@@IAEXPAVRHUnk005069a0@@IABV3@@Z

// TEMPLATE: GAME 0x00509b30
// ?fill@std@@YAXPAVRHUnk005069a0@@0ABV2@@Z

// TEMPLATE: GAME 0x00509b60
// ?copy_backward@std@@YAPAVRHUnk005069a0@@PAV2@00@Z

// TEMPLATE: GAME 0x00509ba0
// ?_Construct@std@@YAXPAU?$pair@$$CBKPAURHsoundGroup@@@1@ABU21@@Z

// TEMPLATE: GAME 0x00509bc0
// ?_Construct@std@@YAXPAVRHUnk005069a0@@ABV2@@Z

// Parked: GetTickCount import is unavailable under the interim link.
// STUB: GAME 0x0050e7b0
void RHGame::FUN_0050e7b0()
{
}

// Parked: GetTickCount import is unavailable under the interim link.
// STUB: GAME 0x0050e800
void RHGame::FUN_0050e800()
{
}

// FUNCTION: GAME 0x0050e850
void RHGame::FUN_0050e850()
{
    m_54 = 1;
}

// FUNCTION: GAME 0x0050f1a0
void RHGame::FUN_0050f1a0(RHSaveGame *saveGame)
{
    RHGameSaveCalls *save = (RHGameSaveCalls *)saveGame;
    if (!save->FUN_0056e790() && !save->FUN_0056e7f0())
    {
        RHGameContinueCalls *manager = (RHGameContinueCalls *)
            ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
        RHSaveGame *continued = manager->FUN_0056f730(FUN_005e23d0(246), g_unk0x006c0ea0);
        if (continued != saveGame)
        {
            manager->FUN_0056f700(saveGame, continued, FUN_005e23d0(246));
            ((RHPlayerProfileManager *)g_unk0x006c0e48)->Save();
        }
    }
}

// FUNCTION: GAME 0x0050f510
void RHGame::DisplayLostLeicester()
{
    RHGameCampaignView *campaign = (RHGameCampaignView *)g_unk0x6c07fc;
    unsigned mission;
    RHMapWideText message;
    RHMapDescription description;
    char directory[260];
    GetCurrentDirectoryA(260, directory);
    SetCurrentDirectoryA(g_unk0x006c0664 ? g_unk0x006c0664 : "");
    mission = *(unsigned *)((char *)campaign + 0x1ac);
    if (!description.FUN_0063cda0(mission))
        SBAssert(0, "P:\\Robin Hood\\RHgame.cpp", 1224,
                 "Warning: unable to load the resource description for the mission '%s'\n", &mission);
    SetCurrentDirectoryA(directory);
    unsigned resource = description.FUN_0063c9e0(mission)->m_38;
    RHMapResources *resources = g_unk0x006c1840;
    if (!resources->FUN_00600fc0(resource) || !resources->FUN_006009e0(resource, 0, message))
    {
        typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
        Assign assign = &std::wstring::assign;
        (((std::wstring *)&message)->*assign)(FUN_005e23d0(259), 0, std::wstring::npos);
    }
    RHGameDialog dialog(0, 0, true, true, (char *)this + 0x68);
    FUN_00529e60((RHMapWindow *)&dialog, message, false, 0);
}

// FUNCTION: GAME 0x005104b0
unsigned FUN_005104b0()
{
    return (unsigned)&g_hotSpot;
}

// FUNCTION: GAME 0x005104c0
void *FUN_005104c0()
{
    return &g_inputPosition;
}

// Parked: The point temporary construction and cleanup sequence is only partially recovered.
// STUB: GAME 0x005104d0
bool RHGame::FUN_005104d0(float first, float second)
{
    float *point = (float *)((char *)this + 0x1758);
    if (!*(void **)point)
        return false;
    return first == second;
}

// Parked: The point temporary assignment and cleanup sequence is only partially recovered.
// STUB: GAME 0x00510550
bool RHGame::FUN_00510550(float first, float second)
{
    float *point = (float *)((char *)this + 0x1758);
    if (!*(void **)point)
        return false;
    return first == second;
}

// Parked: The display timer and input critical-section helpers are only partially recovered.
// STUB: GAME 0x005105d0
void RHGame::FUN_005105d0(unsigned char first, char second)
{
    if (*((char *)this + 0x5a) != 0)
        return;
    ((RHGameSyncCalls *)this)->FUN_0050ed40();
    if (*(unsigned *)((char *)this + 0x3574) != 0)
        --*(unsigned *)((char *)this + 0x3574);
    if (*(char *)((char *)this + 0x18 + 0xd1) == 0 &&
        *(unsigned *)((char *)this + 0x3550) != 1 &&
        *(unsigned *)((char *)this + 0x3550) != 2 &&
        *(unsigned *)((char *)this + 0x3550) != 3)
    {
        ((RHGameActionCalls *)((char *)this + 0x0c))->FUN_005f4900(first & *(unsigned char *)0x006c12ac);
        if (second)
            ((RHGameActionCalls *)((char *)this + 0x10))->FUN_005e5260();
        ((RHGameActionCalls *)((char *)this + 0x0c))->FUN_005f4900(*(unsigned char *)0x006c12ac);
    }
}

// FUNCTION: GAME 0x00510750
bool RHGame::FUN_00510750()
{
    unsigned char *state = *(unsigned char **)0x006c0b54;
    *(unsigned short *)((char *)this + 0x1eb6) = *(unsigned short *)(state + 0x16a);
    *(unsigned short *)((char *)this + 0x1f86) = *(unsigned short *)(state + 0x168);
    *(unsigned short *)((char *)this + 0x2056) = *(unsigned short *)(state + 0x178);
    if (!*((char *)this + 0x5a))
        *(unsigned short *)((char *)this + 0x34c8) = *(unsigned short *)(state + 0x158);
    return true;
}

// Parked: Event actions, message lifetimes, and per-widget updates are only partially recovered.
// STUB: GAME 0x005107a0
bool RHGame::FUN_005107a0(int *event)
{
    if (!event)
        return false;
    for (int *current = event; current; current = (int *)current[3])
    {
        if (current[0] == 2 && current[1] == (int)((char *)this + 0x23a4) && !*((char *)this + 0x59))
            ((RHGameActionCalls *)this)->FUN_005140b0();
        if (current[0] == 3 && current[1] == (int)((char *)this + 0x1c48))
            ((RHGameActionCalls *)((char *)this + 0x0c))->FUN_005f4900(0);
    }
    return true;
}

// Parked: Actor selection and the cached intrusive-list cursor are only partially recovered.
// STUB: GAME 0x00510fc0
void RHGameActionCalls::FUN_00510fc0(unsigned value)
{
    RHGame *game = (RHGame *)this;
    void **actors = *(void ***)((char *)*(void **)0x006c0a88 + 0x493c);
    unsigned count = actors
        ? (unsigned)(*(void ***)((char *)*(void **)0x006c0a88 + 0x4940) - actors)
        : 0;
    count &= 0xff;
    for (unsigned index = 0; index < count; ++index)
    {
        void *actor = actors[index];
        RHEngine *engine = *(RHEngine **)((char *)game + 0x18);
        if (!actor)
        {
            if (*(int *)((char *)engine + 0x4a00) == 0)
                continue;
        }
        else
        {
            *(void **)((char *)engine + 0x4a18) = actor;
            *(char *)((char *)engine + 0x4a10) = 1;
            *(void **)((char *)engine + 0x4a04) = **(void ***)((char *)engine + 0x49fc);
            int size = *(int *)((char *)engine + 0x4a00);
            int position = 0;
            while (position < size && *(void **)(*(char **)((char *)engine + 0x4a04) + 8) != actor)
            {
                ++position;
                *(void **)((char *)engine + 0x4a04) = **(void ***)((char *)engine + 0x4a04);
            }
            if (position == size)
            {
                *(int *)((char *)engine + 0x4a14) = -1;
                *(char *)((char *)engine + 0x4a08) = 1;
            }
            else
            {
                *(int *)((char *)engine + 0x4a14) = position;
                *(char *)((char *)engine + 0x4a08) = 0;
                *(int *)((char *)engine + 0x4a0c) = position;
            }
        }
        RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)game)->FUN_0050f140(actor);
        if (portrait)
            portrait->FUN_005d8f20((unsigned short)value);
    }
}

// Parked: The target's cached-list cursor and action-result call scheduling remain incomplete.
// STUB: GAME 0x005110e0
void RHGameActionCalls::FUN_005110e0(unsigned short value)
{
    RHGame *game = (RHGame *)this;
    void **actors = *(void ***)((char *)*(void **)0x006c0a88 + 0x493c);
    unsigned count = actors
        ? (unsigned)(*(void ***)((char *)*(void **)0x006c0a88 + 0x4940) - actors)
        : 0;
    for (unsigned index = 0; index < (count & 0xff); ++index)
    {
        void *actor = actors[index];
        if (!actor && *(int *)((char *)*(void **)((char *)game + 0x18) + 0x4a00) == 0)
            continue;
        RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)game)->FUN_0050f140(actor);
        if (portrait)
        {
            bool enabled = ((RHEngineActionCalls *)*(void **)((char *)game + 0x18))->FUN_004d2300(actor, value) != 0;
            portrait->FUN_005d8fa0(value, enabled);
        }
    }
}

// Parked: The target's null-actor predicate and portrait dispatch branch are not exact.
// STUB: GAME 0x00511210
void RHGameActionCalls::FUN_00511210(unsigned short value)
{
    RHGame *game = (RHGame *)this;
    void **actors = *(void ***)((char *)*(void **)0x006c0a88 + 0x493c);
    unsigned count = actors
        ? (unsigned)(*(void ***)((char *)*(void **)0x006c0a88 + 0x4940) - actors)
        : 0;
    for (unsigned index = 0; index < (count & 0xff); ++index)
    {
        void *actor = actors[index];
        if (actor && *(int *)((char *)*(void **)((char *)game + 0x18) + 0x4a00) != 0)
            continue;
        RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)game)->FUN_0050f140(actor);
        if (portrait)
        {
            bool enabled = ((RHEngineActionCalls *)*(void **)((char *)game + 0x18))->FUN_004d2300(actor, value) != 0;
            portrait->FUN_005d8fa0(value, enabled);
        }
    }
}

// Parked: 66.04%; narrow-string EH cleanup and frame-slot ordering.
// STUB: GAME 0x00511340
bool RHGame::Serialize(unsigned long mode, RHSaveGame *saveGame, bool loading)
{
    RHUnk005f4fc0 file;
    const std::string &name = saveGame->FUN_0056e5d0();
    RHGameSaveHeader header(mode);
    if (file.FUN_005f5090(name, loading ? 2 : 1) != 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHgame.cpp", 2184,
                 // STRING: GAME 0x006b0444
                 "Unable to access to the file '%s' for serialization.", saveGame->FUN_0056e5d0().c_str());
        return false;
    }
    if (!RHSaveGame::SerializeHeader(file, (RHSaveGame::Header &)header))
        return false;
    FUN_0050e800();
    if (file.m_version >= 39)
    {
        if (!file.m_bLoading)
            ((RHCampaign *)g_unk0x6c07fc)->CopyBackupTo(file);
        else
            ((RHCampaign *)g_unk0x6c07fc)->Serialize(file);
    }
    ((RHCampaign *)g_unk0x6c07fc)->Serialize(file);
    bool result = ((RHEngine *)m_18)->FUN_004c4570(file);
    FUN_0050e7b0();
    file.FUN_005f5290();
    m_60 = 0;
    m_5f = 0;
    m_62 = 0;
    m_61 = 0;
    if (file.m_bLoading)
    {
        FUN_00514140();
        m_5b = ((RHGameSaveCalls *)saveGame)->FUN_0056e790();
    }
    else
    {
        const std::string &settingsName = ((RHGameSaveCalls *)saveGame)->FUN_0056e6b0();
        RHUnk005f4fc0 settingsFile;
        if (settingsFile.FUN_005f5090(settingsName, 2) != 0)
        {
            SBAssert(0, "P:\\Robin Hood\\RHgame.cpp", 2253, "Unable to access to the file '%s' for serialization.", saveGame->FUN_0056e5d0().c_str());
        }
        else
        {
            RHGameConfig settings;
            settings.FUN_006134a0((char *)m_18 + 0xe4);
            settings.FUN_00611960(settingsFile);
            settingsFile.FUN_005f5290();
        }
        ((RHGameSaveCalls *)saveGame)->FUN_0056ecc0();
        if (m_3578)
            ((RHGameMenuCalls *)m_3578)->FUN_00528380(FUN_005e23d0(256));
    }
    if (result)
    {
        FUN_0050f1a0(saveGame);
        if (!((RHGameSaveCalls *)saveGame)->FUN_0056e7f0() && !((RHGameSaveCalls *)saveGame)->FUN_0056e850())
            ((RHGameTextCalls *)this)->FUN_00514ac0(FUN_005e23d0(256 + (loading != true)), 100);
    }
    return result;
}

// FUNCTION: GAME 0x00511780
bool RHGame::Serialize(SBFile &file)
{
    RHSerializeName(file,
                    // STRING: GAME 0x006b047c
                    "RHGame");
    if (file.m_bLoading)
        RHUnk00546050()->RHUnk005460c0(RHUnk5490f0(46));

    RHGAME_ACCESS(m_57, 2314);
    RHGAME_ACCESS(m_54, 2315);
    RHGAME_ACCESS(m_55, 2316);
    if (file.m_version >= 3)
    {
        RHGAME_ACCESS(m_58, 2320);
    }
    if (file.m_version > 6)
    {
        RHGAME_ACCESS(m_355a, 2325);
        RHGAME_ACCESS(m_355b, 2326);
    }
    else
    {
        m_355a = 0;
        m_355b = 0;
    }
    if (file.m_version > 8)
    {
        RHGAME_ACCESS(m_3558, 2336);
        RHGAME_ACCESS(m_3559, 2337);
    }
    else
    {
        m_3558 = 0;
        m_3559 = 0;
    }
    return true;
}

// FUNCTION: GAME 0x00512c90
void RHGame::FUN_00512c90(void *value)
{
    if (m_5a)
        ((RHGameWidgetCalls *)((char *)this + 0x29b4))->FUN_0051df00(0);
}

// Parked: CloseWindow is an unresolved USER32 import under the fixed link line.
// STUB: GAME 0x00513070
void RHGame::FUN_00513070(void *value)
{
    void *handle = *(void **)((char *)value + 0x10);
    RHGameWindowCalls::CloseWindow(*(void **)((char *)handle + 0x100));
    g_unk0x006a6d27 = 0;
}

// FUNCTION: GAME 0x00513ac0
void RHGame::FUN_00513ac0(void *value)
{
    if (!m_5a)
        ((RHEngineReinforcementCalls *)*(void **)((char *)value + 0x10))->FUN_004936a0(0);
}

// FUNCTION: GAME 0x00513ae0
void RHGame::FUN_00513ae0(void *value)
{
    ((RHActorPCTemplateCalls *)*(void **)((char *)value + 0x10))->FUN_00493660(0);
}

// FUNCTION: GAME 0x00513d00
void RHGame::FUN_00513d00(void *)
{
    *((char *)this + 0x61) = 0;
    *((char *)this + 0x62) = 0;
}

// Parked: Rebuilt helper argument scheduling differs from the original.
// STUB: GAME 0x00513d10
void RHGame::FUN_00513d10(void *event)
{
    RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(*(void **)((char *)event + 0x10));
    if (portrait)
        portrait->FUN_005d9b70();
}

// Parked: The body is effective-only because helper argument scheduling differs.
// STUB: GAME 0x00513d30
void RHGame::FUN_00513d30(void *event)
{
    RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(*(void **)((char *)event + 0x10));
    if (portrait)
    {
        portrait->FUN_005d9a60(0);
        portrait->FUN_005d9a60(1);
        portrait->FUN_005d9a60(2);
    }
}

// FUNCTION: GAME 0x00513d70
void RHGame::FUN_00513d70(void *event)
{
    RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(*(void **)((char *)event + 0x10));
    if (portrait)
        portrait->FUN_005d9950(*(unsigned *)((char *)event + 0x08));
}

// Parked: Loop receiver and termination branch scheduling differ.
// STUB: GAME 0x00513360
void RHGame::FUN_00513360(void *event)
{
    unsigned index = *(unsigned *)((char *)event + 0x08);
    RHGameNotificationCalls *notifications = *(RHGameNotificationCalls **)((char *)this + 0x196c);
    for (; index < 3; ++index)
        notifications->FUN_0055e7a0(index);
}

// FUNCTION: GAME 0x00513490
void RHGame::FUN_00513490(void *event)
{
    unsigned value = *(unsigned *)((char *)event + 0x08);
    RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(*(void **)((char *)event + 0x10));
    if (portrait)
        portrait->FUN_005d9140(value);
}

// Parked: The actor and portrait branches retain different receiver registers.
// STUB: GAME 0x00513620
void RHGame::FUN_00513620(void *event)
{
    if (m_5a)
    {
        void *actor = *(void **)((char *)event + 0x10);
        ((RHActorPCTemplateCalls *)actor)->FUN_00493660(1);
        ((RHGamePortraitCalls *)*(void **)((char *)actor + 0x4ec))->FUN_005d6690();
        ((RHGameActionCalls *)this)->FUN_005140b0();
    }
    else
    {
        RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(*(void **)((char *)event + 0x10));
        if (portrait)
            portrait->FUN_005d6690();
    }
}

// Parked: Argument-register allocation differs across the event and helper calls.
// STUB: GAME 0x00513110
void RHGame::FUN_00513110(void *event)
{
    RHGameActionCalls *calls = (RHGameActionCalls *)this;
    calls->FUN_005110e0(*(unsigned short *)((char *)this + 0x355c));
    unsigned value = *(unsigned *)((char *)event + 0x08);
    calls->FUN_00510fc0(value);
    *(unsigned short *)((char *)this + 0x355c) = (unsigned short)value;
}

// Parked: The target zero-extends the action before each helper call.
// STUB: GAME 0x005131d0
void RHGame::FUN_005131d0(void *)
{
    if (m_59)
    {
        RHGameActionCalls *calls = (RHGameActionCalls *)this;
        unsigned short action = *(unsigned short *)((char *)this + 0x355c);
        calls->FUN_00511210(action);
        calls->FUN_00510fc0(action);
        calls->FUN_005140b0();
    }
}

// Parked: The target calls input methods on two embedded owners, not this object.
// STUB: GAME 0x005139b0
void RHGame::FUN_005139b0(void *)
{
    ((SBThreadedInput *)*(void **)((char *)this + 0x0c))->SetMouseEnabled(m_5d);
    SBThreadedInput::CleanUpInputs();
    ((RHGameActionCalls *)*(void **)((char *)this + 0x10))->FUN_005ef380(0);
}

// FUNCTION: GAME 0x005139e0
void RHGame::FUN_005139e0(void *event)
{
    unsigned value = *(unsigned *)((char *)event + 0x08);
    m_5f = 0;
    ((RHGameMenuText *)((char *)this + 0x1ab0))->v21((value >> 16) & 1);
    ((RHGameMenuText *)((char *)this + 0x1b7c))->v21(value & 1);
}

// FUNCTION: GAME 0x00513a20
void RHGame::FUN_00513a20(void *event)
{
    unsigned value = *(unsigned *)((char *)event + 0x08);
    m_60 = 0;
    ((RHGameMenuText *)((char *)this + 0x1ab0))->v21((value >> 16) & 1);
    ((RHGameMenuText *)((char *)this + 0x1b7c))->v21(value & 1);
}

// Parked: The original constructor and two cleanup paths require exact EH ownership recovery.
// STUB: GAME 0x00512be0
void RHGame::FUN_00512be0(void *)
{
}

// Parked: The original save-selection routine owns multiple temporary strings and SEH state.
// STUB: GAME 0x00512cb0
void RHGame::FUN_00512cb0()
{
}

// Parked: The original routine has nested string and UI cleanup with recovered stack corruption.
// STUB: GAME 0x00512eb0
void RHGame::FUN_00512eb0(void *)
{
}

// Parked: Actor iteration, portrait lookup, and messenger EH state are not reconstructed.
// STUB: GAME 0x00513390
void RHGame::FUN_00513390(void *)
{
}

// Parked: The selector reads external control state and synchronizes paired widget modes.
// STUB: GAME 0x00513b00
void RHGame::FUN_00513b00()
{
}

// Parked: The actor/team branches call distinct owners and menu transitions.
// STUB: GAME 0x005134c0
void RHGame::FUN_005134c0(void *)
{
}

// Parked: The target contains actor iteration, portrait dispatch, and messenger cleanup.
// STUB: GAME 0x00513520
void RHGame::FUN_00513520(void *)
{
}

// Parked: The input polling loop and its nested SEH cleanup remain unrecovered.
// STUB: GAME 0x005138b0
void RHGame::FUN_005138b0()
{
}

// Parked: The actor scan and messaging branches have nested SEH and dynamic helper dispatch.
// STUB: GAME 0x00513210
void RHGame::FUN_00513210(void *)
{
}

// Parked: The routine mutates several paired widget states and campaign mode fields.
// STUB: GAME 0x00513e60
void RHGame::FUN_00513e60()
{
}

// Parked: This function relies on stack-backed strings and the campaign/save manager graph.
// STUB: GAME 0x00513ff0
void RHGame::FUN_00513ff0()
{
}

// Parked: Target actor validation iterates external vectors and sends per-actor portrait calls.
// STUB: GAME 0x00513da0
void RHGame::FUN_00513da0(void *)
{
}

// Parked: The function owns UI input polling, geometry temporaries, and nested SEH cleanup.
// STUB: GAME 0x00513df0
void RHGame::FUN_00513df0()
{
}

// Parked: Resource discovery loops through temporary strings and profile-owned allocations.
// STUB: GAME 0x00513670
void RHGame::FUN_00513670()
{
}

// Parked: The target constructs and copies an embedded geometry value before cleanup.
// STUB: GAME 0x00513a60
void RHGame::FUN_00513a60()
{
    memset((char *)this + 0x1960, 0, 10);
    memset((char *)this + 0x1860, 0, 0x100);
    RHGameActionCalls *calls = (RHGameActionCalls *)this;
    calls->FUN_00619cc0();
    calls->FUN_005104c0();
    calls->FUN_005104d0();
    calls->FUN_005f0fa0();
}

// Parked: The target emits a tail jump to FUN_00512310.
// STUB: GAME 0x00513090
void RHGame::FUN_00513090(void *)
{
    RHGameActionCalls *calls = (RHGameActionCalls *)this;
    calls->FUN_004da2f0();
    ((RHGameActionCalls *)*(void **)((char *)this + 0x1c))->FUN_005a7b40(2);
    m_5e = 1;
    FUN_00512310();
}

// Parked: Helper call argument materialization differs in both actor branches.
// STUB: GAME 0x005130c0
void RHGame::FUN_005130c0(void *event)
{
    RHGameActionCalls *calls = (RHGameActionCalls *)this;
    m_59 = 1;
    g_unk0x006c12b6 = 1;
    void *actor = *(void **)((char *)event + 0x10);
    if (actor == 0)
        calls->FUN_00510fc0(*(unsigned short *)((char *)this + 0x355c));
    else
    {
        RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(actor);
        if (portrait)
            portrait->FUN_005d8f20(*(unsigned short *)((char *)this + 0x355c));
    }
}

// Parked: The target carries the 16-bit action in ebx across both helper calls.
// STUB: GAME 0x00513150
void RHGame::FUN_00513150(void *event)
{
    RHGameActionCalls *calls = (RHGameActionCalls *)this;
    m_59 = 0;
    g_unk0x006c12b6 = 0;
    void *actor = *(void **)((char *)event + 0x10);
    unsigned short action = *(unsigned short *)((char *)this + 0x355c);
    if (!actor)
    {
        calls->FUN_005110e0(action);
        calls->FUN_005140b0();
        return;
    }
    RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(actor);
    if (portrait)
    {
        bool enabled = calls->FUN_004d2300(actor, action);
        portrait->FUN_005d8fa0(action, enabled);
    }
    calls->FUN_005140b0();
}

// Parked: The target's nested action/actor loops use a different frame and register schedule.
// STUB: GAME 0x005140b0
void RHGame::FUN_005140b0()
{
    RHGameActorView **first = *(RHGameActorView ***)((char *)g_pEngine + 0x493c);
    RHGameActorView **last = *(RHGameActorView ***)((char *)g_pEngine + 0x4940);
    unsigned count = first == 0 ? 0 : (unsigned)(last - first);
    count &= 0xff;
    bool any = false;
    for (unsigned action = 0; action < 3; ++action)
    {
        for (unsigned index = 0; index < count; ++index)
        {
            if (((RHEngineActionCalls *)m_18)->FUN_004d2300(first[index], action))
                any = true;
        }
    }
    ((RHGameMenuText *)((char *)this + 0x23a4))->v21(any);
}

// Parked: message EH temporaries and portrait-loop scheduling.
// STUB: GAME 0x00514140
void RHGame::FUN_00514140()
{
    RHMessenger *messenger = RHUnk00546050();
    bool any = false;
    RHGameSyncCalls *game = (RHGameSyncCalls *)this;
    for (unsigned short index = 0;
         index < (unsigned char)(*(RHGameActorView ***)((char *)g_pEngine + 0x493c) == 0 ? 0 :
             *(RHGameActorView ***)((char *)g_pEngine + 0x4940) -
             *(RHGameActorView ***)((char *)g_pEngine + 0x493c)); ++index)
    {
        RHGameActorView *actor = (*(RHGameActorView ***)((char *)g_pEngine + 0x493c))[(unsigned char)index];
        RHGamePortraitCalls *portrait = game->FUN_0050f140(actor);
        if (actor->FUN_004936e0() && portrait)
        {
            RHElementActor *value = (RHElementActor *)actor;
            RHSectorActorList *team = (RHSectorActorList *)((char *)m_18 + 0x49f8);
            if (value ? team->Unk004b8f80(value, true) != -1 : *(unsigned *)((char *)m_18 + 0x4a00) != 0)
            {
                RHUnk00549250 message(15, actor);
                game->FUN_00513520(message);
            }
            else
            {
                value = (RHElementActor *)actor;
                if (!(value ? team->Unk004b8f80(value, true) != -1 : *(unsigned *)((char *)m_18 + 0x4a00) != 0) &&
                    actor->v51() > 0)
                {
                    RHUnk00549250 message(18, actor);
                    game->FUN_005134c0(message);
                }
                else
                    actor->v53(actor->v51(), false, false);
            }
            portrait->FUN_005d9b10();
            for (unsigned short action = 0; action < 3; ++action)
            {
                bool enabled = *(unsigned *)((char *)actor + 0x514 + action * 4) != 0 ||
                               *(unsigned *)((char *)actor + 0x52c + action * 4) != 0;
                portrait->FUN_005d9ae0(action, enabled);
                any = any || enabled;
            }
        }
    }
    ((RHGameMenuText *)((char *)this + 0x23a4))->v21(any);
    game->FUN_00513b00(0);
    game->FUN_0048a970(RHUnk005492a0(22, 0, *(unsigned short *)((char *)messenger + 0xa2)));
    ((RHScriptBatchCalls *)this)->FUN_0050eca0(m_3558 && !m_355a);
    ((RHScriptBatchCalls *)this)->FUN_0050eb80(m_3559 && !m_355b);
    ((RHGameMenuText *)((char *)this + 0x1ab0))->v21(((RHGameEngineCalls *)m_18)->FUN_004c7cd0());
    ((RHGameMenuText *)((char *)this + 0x1b7c))->v21(((RHGameEngineCalls *)m_18)->FUN_004c7cf0());
    game->FUN_0050ed40();
    if (m_5a)
    {
        bool hasMission = ((RHGameCampaignView *)g_unk0x6c07fc)->m_17c != 0;
        ((RHGameMenuText *)((char *)this + 0x21e4))->v21(hasMission);
        ((RHGameMenuText *)((char *)this + 0x22b0))->v21(!hasMission);
        if (hasMission)
        {
            game->FUN_00514670();
            game->FUN_005146f0();
        }
    }
    FUN_0053a830();
    m_54 = m_55;
}

// STRING: GAME 0x006b0178
static const char *g_rhgameFile = "P:\\Robin Hood\\RHgame.cpp";

// FUNCTION: GAME 0x00514730
void RHGame::UpdateBlazons(RHMenuCampaignMap *map, RHMenuMissionDescription *description, RHMenuBuyBlazons *buy, bool flag)
{
    RHGameCampaignView *campaign = (RHGameCampaignView *)g_unk0x6c07fc;
    RHGameMission *mission = campaign->m_180;
    if (mission == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHgame.cpp", 4165,
                 // STRING: GAME 0x006b055c
                 "ACHTUNG ! Couldn't update blazon number because the game is not running in campaign mode !");
        return;
    }
    if (m_5a)
    {
        RHGameMissionProfile *profile = mission->m_profile;
        if (profile->m_34 == 5)
        {
            int cost = profile->m_68;
            if ((unsigned)((RHUnk00452030 *)campaign)->Get(3) >= (unsigned)cost)
            {
                ((RHUnk00450b60 *)campaign)->Unk(3, -cost);
                campaign->FUN_00456540(true, mission);
                campaign->FUN_00453b70(mission);
                campaign->m_17c = 0;
                campaign->FUN_00451a90();
                if (buy)
                    ((RHGameMenuCalls *)buy)->FUN_00544b30();
                if (description)
                    ((RHGameMenuCalls *)description)->FUN_00544b30();
                if (map)
                    ((RHGameMenuCalls *)map)->FUN_005283d0();
                FUN_0050e850();
            }
            else if (description)
                ((RHGameMenuCalls *)description)->FUN_00535950(campaign->FUN_004561d0(mission), campaign->FUN_00456230(mission), campaign->FUN_00456190(mission));
        }
        else
        {
            int cost = (int)profile->m_68 - (int)profile->m_6a;
            if ((unsigned)((RHUnk00452030 *)campaign)->Get(3) >= (unsigned)cost)
            {
                if (buy)
                    ((RHGameMenuCalls *)buy)->FUN_00544b30();
                if (description)
                    ((RHGameMenuCalls *)description)->FUN_00535950(0, 0, 0);
            }
        }
        if (m_29b0)
            m_29b0->FUN_005cc900(0);
    }
    else
    {
        RHGameMission *current = *(RHGameMission *volatile *)((char *)campaign + 0x178);
        RHGameMissionProfile *currentProfile = current->m_profile;
        int type = currentProfile->m_34;
        if (type == 1)
        {
            m_29b0->FUN_005cc900(0);
            if (((RHUnk00452030 *)campaign)->Get(3) >= mission->m_profile->m_68)
            {
                if (flag)
                    ((RHScriptBatchCalls *)campaign)->Unk004520e0(3, 0);
                else
                    ((RHScriptBatchCalls *)g_pEngine)->Unk004e3220(1);
            }
        }
        else if (type == 6)
        {
            RHGameMissionProfile *profile = mission->m_profile;
            int cost = (int)profile->m_68 - (int)profile->m_6a;
            if (flag && ((RHUnk00452030 *)campaign)->Get(3) >= mission->m_profile->m_68)
            {
                ((RHScriptBatchCalls *)campaign)->Unk004520e0(3, 0);
                campaign->FUN_00456540(true, mission);
                campaign->FUN_00453b70(mission);
            }
            else if ((unsigned)((RHUnk00452030 *)campaign)->Get(3) > (unsigned)cost)
            {
                int difference = ((RHUnk00452030 *)campaign)->Get(3) - cost;
                ((RHScriptBatchCalls *)campaign)->Unk004520e0(3, cost);
                m_29b0->FUN_005cc920(difference);
            }
            if (m_29b0)
                m_29b0->FUN_005cc900(0);
        }
    }
}

// FUNCTION: GAME 0x00514ac0
void RHGameTextCalls::FUN_00514ac0(const std::wstring &text, unsigned duration)
{
    ((std::wstring *)((char *)this + 0x3564))->assign(text, 0, std::wstring::npos);
    *(unsigned *)((char *)this + 0x3574) = duration;
}

// FUNCTION: GAME 0x00528380
void RHGameMenuCalls::FUN_00528380(const std::wstring &text)
{
    ((RHGameMenuText *)((char *)this + 0x25ec))->v11(text);
    unsigned timer = *(unsigned *)((char *)this + 0x26fc);
    if (timer != (unsigned)-1)
        (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053bb30(timer);
    *(unsigned *)((char *)this + 0x26fc) =
        (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053baa0(3000);
}

// FUNCTION: GAME 0x005283d0
void RHGameMenuCalls::FUN_005283d0()
{
    RHMenuCampaignMap *map = (RHMenuCampaignMap *)this;
    map->FUN_005284b0();
    map->FUN_00527c00(((RHMapCampaign *)g_unk0x6c07fc)->FUN_00528050());
    map->FUN_00527a70(*(RHMapByte *)((char *)g_unk0x6c07fc + 0x100));
    map->FUN_00527ae0(*(RHMapByte *)((char *)g_unk0x6c07fc + 0x100));
    (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053c7e0();
}

// SYNTHETIC: GAME 0x00533c10
// ??_G?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QAEPAXI@Z

// FUNCTION: GAME 0x00535950
void RHGameMenuCalls::FUN_00535950(int first, int second, int third)
{
    *((char *)this + 0x344) = (char)first;
    *((char *)this + 0x144) = (char)second;
    *((char *)this + 0x244) = (char)third;
}

// FUNCTION: GAME 0x00544b30
void RHGameMenuCalls::FUN_00544b30()
{
    (*(RHGameMenuOwner **)((char *)this + 0xb4))->FUN_0053c870(this);
}

// FUNCTION: GAME 0x0056e230
RHGameSaveHeader::RHGameSaveHeader(unsigned long mode)
{
    m_00 = 0x52485347;
    m_04 = 0x30;
    m_08 = mode;
}

// FUNCTION: GAME 0x0056e5d0
std::string RHSaveGame::FUN_0056e5d0() const
{
    return FUN_004e4c70((*(RHGameSaveOwner *const *)this)->v0(), "\\") +
           *(const std::string *)((const char *)this + 0x08);
}

// FUNCTION: GAME 0x0056e6b0
std::string RHGameSaveCalls::FUN_0056e6b0()
{
    return FUN_004e4c70((*(RHGameSaveOwner **)this)->v0(), "\\") +
           *(std::string *)((char *)this + 0x18);
}

// GLOBAL: GAME 0x006c0ea0
std::string g_unk0x006c0ea0;
// GLOBAL: GAME 0x006c0ed8
std::string g_unk0x006c0ed8;
// GLOBAL: GAME 0x006c0ee8
std::string g_unk0x006c0ee8;

// FUNCTION: GAME 0x0056e790
char RHGameSaveCalls::FUN_0056e790()
{
    return ((std::string *)((char *)this + 0x08))->compare(g_unk0x006c0ea0) == 0;
}

// FUNCTION: GAME 0x0056e7f0
bool RHGameSaveCalls::FUN_0056e7f0()
{
    return ((std::string *)((char *)this + 0x08))->compare(g_unk0x006c0ed8) == 0;
}

// FUNCTION: GAME 0x0056e850
bool RHGameSaveCalls::FUN_0056e850()
{
    return ((std::string *)((char *)this + 0x08))->compare(g_unk0x006c0ee8) == 0;
}

// FUNCTION: GAME 0x005cc900
void RHGameBlazonWidget::FUN_005cc900(int value)
{
    if (m_b0)
        m_b0->FUN_0044f960(value);
}

// FUNCTION: GAME 0x005cc920
void RHGameBlazonWidget::FUN_005cc920(int value)
{
    if (m_b0)
        m_b0->FUN_0044f8d0(value);
}

// FUNCTION: GAME 0x006134a0
bool RHGameConfig::FUN_006134a0(void *configuration)
{
    if (*(unsigned *)((char *)this + 0x1c))
        ::operator delete(*(void **)((char *)this + 0x14));
    *(unsigned *)((char *)this + 0x04) = *(unsigned *)((char *)configuration + 0x04);
    *(RHGameConfigTriple *)((char *)this + 0x08) =
        *(RHGameConfigTriple *)((char *)configuration + 0x08);
    *(unsigned *)((char *)this + 0x1c) = *(unsigned *)((char *)configuration + 0x1c);
    *(unsigned short *)((char *)this + 0x20) = *(unsigned short *)((char *)configuration + 0x20);
    *(unsigned short *)((char *)this + 0x22) = *(unsigned short *)((char *)configuration + 0x22);
    *(unsigned short *)((char *)this + 0x24) = *(unsigned short *)((char *)configuration + 0x24);
    ((RHUnk005fc3b0 *)((char *)this + 0x28))->FUN_005fc430(
        *(SBGeoPoint2D *)((char *)configuration + 0x28));
    *(void **)((char *)this + 0x14) = ::operator new(*(unsigned *)((char *)this + 0x1c));
    memcpy(*(void **)((char *)this + 0x14), *(void **)((char *)configuration + 0x14),
        *(unsigned *)((char *)this + 0x1c));
    return true;
}

// Parked: 65.17%; lookup register scheduling; unannotated to preserve DisplayLostLeicester.
RHMapDescription::Entry *RHMapDescription::FUN_0063c9e0(unsigned id)
{
    Entry *first = *(Entry *volatile *)((char *)this + 0x08);
    unsigned count = first == 0 ? 0 : *(Entry *volatile *)((char *)this + 0x0c) - first;
    if (count != 0)
    {
        Entry *last = *(Entry **)((char *)this + 0x0c);
        if (id <= last[-1].m_44)
        {
            first = *(Entry **)((char *)this + 0x08);
            if (id >= first->m_44)
            {
                Entry *entry = first + (id < count ? id : count - 1);
                if (entry->m_44 == id)
                    return entry;
                for (entry = first; entry != last; ++entry)
                {
                    if (id < entry->m_44)
                        return 0;
                    if (id == entry->m_44)
                        return entry;
                }
            }
        }
    }
    return 0;
}

void RHGame::Emit(SBFile &file)
{
    FUN_005104b0();
    FUN_005104c0();
    FUN_005104d0(0.0f, 0.0f);
    FUN_00510550(0.0f, 0.0f);
    FUN_005105d0(0, 0);
    FUN_00510750();
    FUN_005107a0(0);
    Serialize(file);
    UpdateBlazons(0, 0, 0, false);
    DisplayLostLeicester();
    Serialize(0, 0, false);
    ((RHGameSaveCalls *)this)->FUN_0056e790();
    ((RHGameSaveCalls *)this)->FUN_0056e6b0();
    ((RHGameSaveCalls *)this)->FUN_0056e7f0();
    ((RHGameSaveCalls *)this)->FUN_0056e850();
    FUN_0050e850();
    RHGameMenuCalls *menu = (RHGameMenuCalls *)m_3578;
    menu->FUN_00535950(0, 0, 0);
    menu->FUN_00544b30();
    menu->FUN_00528380(std::wstring());
    RHGameSaveHeader header(0);
    m_29b0->FUN_005cc900(0);
    m_29b0->FUN_005cc920(0);
    RHGameCampaignView *campaign = (RHGameCampaignView *)g_unk0x6c07fc;
    campaign->FUN_00456190(0);
    campaign->FUN_004561d0(0);
    campaign->FUN_00456230(0);
    campaign->FUN_00456540(false, 0);
    campaign->FUN_00453b70(0);
}
