#include "RHGame_calls.h"
#include <vector>
#include <algorithm>

DECOMP_SIZE_ASSERT(RHGame, 0x357c)
DECOMP_SIZE_ASSERT(RHGameMissionProfile, 0x6c)
DECOMP_SIZE_ASSERT(RHGameMission, 0x0c)
DECOMP_SIZE_ASSERT(RHGameCampaignView, 0x184)
DECOMP_SIZE_ASSERT(RHGameBlazonWidget, 0xb4)
DECOMP_SIZE_ASSERT(RHGameSaveHeader, 0x0c)
DECOMP_SIZE_ASSERT(SBArray<RHSaveGame *>, 0x10)
DECOMP_SIZE_ASSERT(RHGameSaveOwner, 0x04)
DECOMP_SIZE_ASSERT(RHMapDescription::Entry, 0x48)

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

// FUNCTION: GAME 0x0050e850
void RHGame::FUN_0050e850()
{
    m_54 = 1;
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
        message.FUN_004580c0(FUN_005e23d0(259), 0, std::wstring::npos);
    RHGameDialog dialog(0, 0, true, true, (char *)this + 0x68);
    FUN_00529e60((RHMapWindow *)&dialog, message, false, 0);
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

// STRING: GAME 0x006b0178
static const char *g_rhgameFile = "P:\\Robin Hood\\RHgame.cpp";

// deferred: unannotated pending reccmp #534
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

// FUNCTION: GAME 0x00528380
void RHGameMenuCalls::FUN_00528380(const std::wstring &text)
{
    ((RHGameMenuText *)((char *)this + 0x25ec))->v11(text);
    unsigned timer = *(unsigned *)((char *)this + 0x26fc);
    if (timer != (unsigned)-1)
        (*(RHGameMenuOwner **)((char *)this + 0xb4))->FUN_0053bb30(timer);
    *(unsigned *)((char *)this + 0x26fc) =
        (*(RHGameMenuOwner **)((char *)this + 0xb4))->FUN_0053baa0(3000);
}

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

// deferred: unannotated pending reccmp #534 (0x0056e5d0)
std::string RHSaveGame::FUN_0056e5d0() const
{
    return FUN_004e4b40(FUN_004e4c70((*(RHGameSaveOwner *const *)this)->v0(), "\\"),
                       *(const std::string *)((const char *)this + 0x08));
}

// FUNCTION: GAME 0x0056e6b0
std::string RHGameSaveCalls::FUN_0056e6b0()
{
    return FUN_004e4b40(FUN_004e4c70((*(RHGameSaveOwner **)this)->v0(), "\\"),
                       *(std::string *)((char *)this + 0x18));
}

// GLOBAL: GAME 0x006c0ea0
std::string g_unk0x006c0ea0;
// GLOBAL: GAME 0x006c0ed8
std::string g_unk0x006c0ed8;
// GLOBAL: GAME 0x006c0ee8
std::string g_unk0x006c0ee8;

// Parked: 97.73%; basic_string::_Nullstr operand does not resolve to the shared empty literal.
// STUB: GAME 0x0056e790
char RHGameSaveCalls::FUN_0056e790()
{
    return ((std::string *)((char *)this + 0x08))->compare(g_unk0x006c0ea0) == 0;
}

// Parked: 97.73%; basic_string::_Nullstr operand does not resolve to the shared empty literal.
// STUB: GAME 0x0056e7f0
bool RHGameSaveCalls::FUN_0056e7f0()
{
    return ((std::string *)((char *)this + 0x08))->compare(g_unk0x006c0ed8) == 0;
}

// Parked: 97.73%; basic_string::_Nullstr operand does not resolve to the shared empty literal.
// STUB: GAME 0x0056e850
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
