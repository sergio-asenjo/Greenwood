#include "SBNullstr.h"
// SIZE 0x14
class RHMobileUnk00607da0
{
public:
    void FUN_00607990(const RHMobileUnk00607da0 &other);
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
    unsigned char m_00[0x14]; // 0x00
};
#include "RHGame_calls.h"
#include "SBThreadedInput.h"
#include "SBDrawManager.h"
#include "../ui/RHWidgetPortraitClass.h"
#include "../ui/RHPortraitBar.h"
class RHUnk00493a80
{
public:
    int FUN_00493a80();
};

class SBGeoPoint2D;
struct RHGameWidgetInput;

struct RHGameWidgetEvent
{
    int type;
    void *widget;
    unsigned value;
    void *next;
};

struct RHGameWidgetView
{
    undefined m_00[4];
    char m_04;
    char m_05;
    char m_06;
    undefined m_07[0x4c - 7];
    RHGameWidgetEvent m_event;
    undefined m_5c[0x7c - 0x5c];
    int m_7c;
    undefined m_80[0x4c];
    char m_cc;
};

class RHUnk005165f0 : public RHGameWidgetView
{
public:
    int FUN_005165f0();
    RHGameWidgetEvent *FUN_00516670(void *);
    int FUN_005166b0(const SBGeoPoint2D &point);
    void FUN_005169f0(char selected);
    RHGameWidgetEvent *FUN_005167b0(const RHGameWidgetInput &input);
};

class RHGameWidgetSelectCalls
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
    virtual void v21(int value);
};

class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;

class RHSound
{
public:
    void PlayJingle(int jingle);
};
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
DECOMP_SIZE_ASSERT(RHUnk006114c0, 0x38)
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

#include "RHPCActionQueryCalls.h"

class RHGameWidgetVisibilityCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38(void *widget) = 0;
    virtual void V3c(void *widget) = 0;
};

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

#include "RHFrameDictionary.h"

#include "RHPortraitRootList.h"

// FUNCTION: GAME 0x00509c10
void *RHUnk005069a0::FUN_00509c10(unsigned flags)
{
    this->~RHUnk005069a0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0050e770
void *RHPortraitRootList::FUN_0050e770(unsigned flags)
{
    this->~RHPortraitRootList();
    if (flags & 1)
        operator delete(this);
    return this;
}

void RHGameTailEmit(void *object, unsigned flags)
{
    ((RHUnk005069a0 *)object)->FUN_00509c10(flags);
    ((RHPortraitRootList *)object)->FUN_0050e770(flags);
}

// FUNCTION: GAME 0x0050e530
void *RHGame::FUN_0050e530()
{
    return (char *)this + 0x70;
}

// Parked: 81.40%; cursor load folding, loop scheduling, and register-save placement differ.
// STUB: GAME 0x0050e540
int RHUnk0050e540::FUN_0050e540(void *value)
{
    int count = m_count;
    m_value = value;
    m_searching = true;
    m_current = m_head->next;
    int index;
    for (index = 0; index < count; ++index, m_current = m_current->next) {
        if (m_current->value == m_value)
            break;
    }
    if (index < count) {
        m_result = index;
        m_index = index;
        m_dirty = false;
    }
    else {
        m_result = -1;
        m_dirty = true;
    }
    return m_result != -1;
}

// FUNCTION: GAME 0x0050e5c0
char RHGame::FUN_0050e5c0()
{
    return m_5c;
}

// FUNCTION: GAME 0x0050e5d0
void RHGame::FUN_0050e5d0(char value)
{
    m_5c = value;
}

// FUNCTION: GAME 0x0050e5e0
char RHGame::FUN_0050e5e0()
{
    return m_5e;
}

// VTABLE: GAME 0x00678d18
class RHUnk0051d790 : public RHPortraitRootList
{
public:
    ~RHUnk0051d790();
    void *FUN_0050e660(unsigned flags);
    bool FUN_0051d8a0();
    void FUN_0051dba0(RHGameLifetime005161a0 *widgets, const SBGeoPoint2D &position, int style);
    void FUN_0051dd10(RHGameLifetime005161a0 *widgets);
    void FUN_0051dd40(const SBGeoPoint2D &position);
    void FUN_0051ddb0(const SBGeoBoundingBox2D &bounds);
    RHGameLifetime00517300 m_b0;
    RHGameLifetime00517300 m_180;
    RHGameLifetime005161a0 m_250[5];
    RHGameLifetime005161a0 m_660[5];
};

// FUNCTION: GAME 0x0050e660
void *RHUnk0051d790::FUN_0050e660(unsigned flags)
{
    this->~RHUnk0051d790();
    if (flags & 1)
        operator delete(this);
    return this;
}

// SYNTHETIC: GAME 0x0050e680
// ??0RHPortraitRootList@@QAE@XZ

// SYNTHETIC: GAME 0x0050e6c0
// ??0RHGameLifetime0050e6c0@@QAE@XZ

// SYNTHETIC: GAME 0x0050e710
// ??1RHGameLifetime0050e6c0@@QAE@XZ

// FUNCTION: GAME 0x0050e790
void *RHGameLifetime0050e6c0::FUN_0050e790(unsigned flags)
{
    this->~RHGameLifetime0050e6c0();
    if (flags & 1)
        operator delete(this);
    return this;
}

extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount();

// FUNCTION: GAME 0x0050e7b0
void RHGame::FUN_0050e7b0()
{
    if (!m_3560)
        m_3560 = GetTickCount();
}

// FUNCTION: GAME 0x0050e7d0
int RHGame::FUN_0050e7d0()
{
    int elapsed = g_unk0x6c07fc->Get(6);
    if (m_3560)
        elapsed += GetTickCount() - m_3560;
    return elapsed;
}

// FUNCTION: GAME 0x0050e800
void RHGame::FUN_0050e800()
{
    if (m_3560)
    {
        RHUnk00450b60 *campaign = (RHUnk00450b60 *)g_unk0x6c07fc;
        campaign->Unk(6, (GetTickCount() - m_3560) / 1000);
        m_3560 = 0;
    }
}

// FUNCTION: GAME 0x0050e850
void RHGame::FUN_0050e850()
{
    m_54 = 1;
}

// FUNCTION: GAME 0x0050e860
void RHGame::FUN_0050e860()
{
    if (m_3578)
    {
        ((RHGameMenuCalls *)m_3578)->FUN_00544b30();
        m_56 = 1;
    }
}

class RHGameToggleWidget
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c() = 0;
    virtual void V40() = 0;
    virtual void V44() = 0;
    virtual void V48() = 0;
    virtual void V4c() = 0;
    virtual void V50() = 0;
    virtual void V54(char visible) = 0; // vtable+0x54
    char m_04; // 0x04
};

class RHGameToggleFrame
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38(RHGameToggleWidget *widget) = 0; // vtable+0x38
    virtual void V3c(RHGameToggleWidget *widget) = 0; // vtable+0x3c
};

// FUNCTION: GAME 0x0050eb80
void RHGame::FUN_0050eb80(bool value)
{
    m_3559 = value;
    if (!value || !m_355a)
        ((RHGameToggleWidget *)((char *)this + 0x28bc))->V54(value);
    if (((RHGameToggleWidget *)((char *)this + 0x28bc))->m_04)
        ((RHGameToggleFrame *)((char *)this + 0x1970))->V3c((RHGameToggleWidget *)((char *)this + 0x28bc));
    else
        ((RHGameToggleFrame *)((char *)this + 0x1970))->V38((RHGameToggleWidget *)((char *)this + 0x28bc));
}

// FUNCTION: GAME 0x0050ebe0
void RHGame::FUN_0050ebe0(char value)
{
    m_355b = value;
    if (value)
        ((RHGameToggleWidget *)((char *)this + 0x28bc))->V54(0);
    else
        ((RHGameToggleWidget *)((char *)this + 0x28bc))->V54(m_3559);
    if (((RHGameToggleWidget *)((char *)this + 0x28bc))->m_04)
        ((RHGameToggleFrame *)((char *)this + 0x1970))->V3c((RHGameToggleWidget *)((char *)this + 0x28bc));
    else
        ((RHGameToggleFrame *)((char *)this + 0x1970))->V38((RHGameToggleWidget *)((char *)this + 0x28bc));
}

// FUNCTION: GAME 0x0050ec40
void RHGame::FUN_0050ec40(char value)
{
    m_355a = value;
    if (value)
        ((RHGameToggleWidget *)((char *)this + 0x27d0))->V54(0);
    else
        ((RHGameToggleWidget *)((char *)this + 0x27d0))->V54(m_3558);
    if (((RHGameToggleWidget *)((char *)this + 0x27d0))->m_04)
        ((RHGameToggleFrame *)((char *)this + 0x1970))->V3c((RHGameToggleWidget *)((char *)this + 0x27d0));
    else
        ((RHGameToggleFrame *)((char *)this + 0x1970))->V38((RHGameToggleWidget *)((char *)this + 0x27d0));
}

// FUNCTION: GAME 0x0050eca0
void RHGame::FUN_0050eca0(bool value)
{
    m_3558 = value;
    if (!value || !m_355a)
    {
        ((RHGameToggleWidget *)((char *)this + 0x27d0))->V54(value);
        ((RHGameToggleWidget *)((char *)this + 0x27d0))->V54(value);
    }
    if (((RHGameToggleWidget *)((char *)this + 0x27d0))->m_04)
        ((RHGameToggleFrame *)((char *)this + 0x1970))->V3c((RHGameToggleWidget *)((char *)this + 0x27d0));
    else
        ((RHGameToggleFrame *)((char *)this + 0x1970))->V38((RHGameToggleWidget *)((char *)this + 0x27d0));
}

// FUNCTION: GAME 0x0050ed10
void RHGame::FUN_0050ed10(bool value)
{
    m_57 = value;
    FUN_0050eca0(value);
    FUN_0050eb80(value);
    FUN_00514c50();
    ((RHGameSyncCalls *)this)->FUN_0050ed40();
}

#include "RHUnk005db7e0.h"

// FUNCTION: GAME 0x0050ef90
void *RHUnk005db7e0::FUN_0050ef90(unsigned flags)
{
    this->~RHUnk005db7e0();
    if (flags & 1)
        operator delete(this);
    return this;
}

#include "RHPortraitBar.h"
#include "RHEngineWidenedCalls.h"

// FUNCTION: GAME 0x0050efd0
void RHEngineWidenedCalls::FUN_0050efd0(void *portrait)
{
    (*(RHPortraitBar **)((char *)this + 0x196c))->RemovePortrait((RHWidgetPortrait *)portrait);
}

// FUNCTION: GAME 0x0050eff0
void RHGameActionCalls::FUN_0050eff0()
{
    (*(RHPortraitBar **)((char *)this + 0x196c))->RemoveAllPortraits();
}

// FUNCTION: GAME 0x0050f140
RHGamePortraitCalls *RHGameSyncCalls::FUN_0050f140(void *actor)
{
    return (RHGamePortraitCalls *)(*(RHPortraitBar **)((char *)this + 0x196c))->FUN_0055e7e0(actor);
}

// FUNCTION: GAME 0x0050f160
int RHGameSyncCalls::FUN_0050f160(unsigned short index)
{
    if (index < (*(RHPortraitBar **)((char *)this + 0x196c))->FUN_0055e880())
    {
        RHPortraitBar *bar = *(RHPortraitBar **)((char *)this + 0x196c);
        return *(int *)((char *)bar->portraits[index] + 0xe1c);
    }
    return 0;
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

extern std::string g_unk0x006c0ed8;
extern std::string g_unk0x006c0ee8;
#include "RHUnk0056fb70.h"

// FUNCTION: GAME 0x0050f2d0
bool RHGame::FUN_0050f2d0(bool loading)
{
    if (!m_5a)
    {
        RHGameContinueCalls *profile = (RHGameContinueCalls *)
            ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
        RHGameMission *mission = ((RHGameCampaignView *)g_unk0x6c07fc)->m_178;
        RHSaveGame *saveGame;
        if (loading)
        {
            saveGame = profile->FUN_0056f730(FUN_005e23d0(247), g_unk0x006c0ed8);
            ((RHGameActionCalls *)m_18)->FUN_004da2f0();
        }
        else
            saveGame = (RHSaveGame *)((RHUnk0056fb70 *)profile)->FUN_0056fb70(&g_unk0x006c0ed8);
        return Serialize(**(unsigned long **)mission, saveGame, loading);
    }
    return true;
}

// FUNCTION: GAME 0x0050f3d0
bool RHGame::SerializeForSherwood()
{
    if (m_5a == 1)
    {
        RHGameContinueCalls *profile = (RHGameContinueCalls *)
            ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
        RHGameMission *mission = ((RHGameCampaignView *)g_unk0x6c07fc)->m_178;
        RHSaveGame *saveGame = profile->FUN_0056f730(
            // STRING: GAME 0x006b0430
            L"Sherwood", g_unk0x006c0ee8);
        ((RHGameActionCalls *)m_18)->FUN_004da2f0();
        return Serialize(**(unsigned long **)mission, saveGame, true);
    }
    return true;
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
    RHMenuScreenView dialog(0, 0, true, true, (char *)this + 0x68);
    FUN_00529e60((RHMapWindow *)&dialog, message, false, 0);
}

// FUNCTION: GAME 0x005104b0
unsigned SBThreadedInput::FUN_005104b0()
{
    return (unsigned)&g_hotSpot;
}

// FUNCTION: GAME 0x005104c0
void *FUN_005104c0()
{
    return &g_inputPosition;
}

// FUNCTION: GAME 0x005104d0
bool RHGameActionCalls::FUN_005104d0(SBGeoPoint2D point)
{
    char *target = *(char **)((char *)this + 0x1758);
    if (target)
    {
        *(SBGeoPoint2D *)(target + 0x80) = point;
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x00510550
bool RHGameActionCalls::FUN_00510550(SBGeoVector2D point)
{
    char *target = *(char **)((char *)this + 0x1758);
    if (target)
    {
        ((SBGeoVector2D *)(target + 0x88))->operator=(point);
        return true;
    }
    return false;
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

// Parked: the cached-selection and count-accessor probes still add a frame slot and alter cursor lifetimes.
// STUB: GAME 0x00510fc0
void RHGameActionCalls::FUN_00510fc0(unsigned short value)
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

// Parked: full selection recovery still adds a frame slot and changes the count/result register lifetime.
// STUB: GAME 0x005110e0
void RHGameActionCalls::FUN_005110e0(unsigned value)
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

// Parked: full selection recovery still changes the count frame slot and inlined cursor comparison registers.
// STUB: GAME 0x00511210
void RHGameActionCalls::FUN_00511210(unsigned value)
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
            RHUnk006114c0 settings;
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

#include "RHGameInputTranslator.h"

extern float g_unk0x677554;

// Parked: named coordinate temporaries recover the frame but retain x87 store and call-view seams.
// STUB: GAME 0x005119f0
void RHGame::GenerateDeadZoneForMouseInput()
{
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    SBGeoVector2D resolution(*(SBGeoPoint2D *)(
        ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54));
    RHGameInputTranslator *translator = RHGameInputTranslator::mpInstance;
    translator->ClearDeadZone();
    first.m_x = 0.0f;
    first.m_y = resolution.m_y - g_unk0x677554;
    second.m_x = 0.0f;
    second.m_y = resolution.m_y - 3.0f;
    translator->AddToDeadZone(first, second);
    first.m_x = 2.0f;
    first.m_y = resolution.m_y - 1.0f;
    second.m_x = 60.0f;
    second.m_y = resolution.m_y - 1.0f;
    translator->AddToDeadZone(first, second);
    first.m_x = resolution.m_x - g_unk0x677554;
    first.m_y = resolution.m_y - 1.0f;
    second.m_x = resolution.m_x - 3.0f;
    second.m_y = resolution.m_y - 1.0f;
    translator->AddToDeadZone(first, second);
    first.m_x = resolution.m_x - 1.0f;
    first.m_y = resolution.m_y - 3.0f;
    second.m_x = resolution.m_x - 1.0f;
    second.m_y = resolution.m_y - g_unk0x677554;
    translator->AddToDeadZone(first, second);
}

// FUNCTION: GAME 0x00512c90
void RHGame::FUN_00512c90(void *value)
{
    if (m_5a)
        ((RHGameWidgetCalls *)((char *)this + 0x29b4))->FUN_0051df00(0);
}

// FUNCTION: GAME 0x00513070
void RHGame::FUN_00513070(void *)
{
    void *handle = *(void **)((char *)this + 0x10);
    ::CloseWindow(*(HWND *)((char *)handle + 0x100));
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

// FUNCTION: GAME 0x00513d10
void RHGame::FUN_00513d10(void *event)
{
    void *actor = *(void **)((char *)event + 0x10);
    RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(actor);
    if (portrait)
        portrait->FUN_005d9b70();
}

// FUNCTION: GAME 0x00513d30
void RHGame::FUN_00513d30(void *event)
{
    void *actor = *(void **)((char *)event + 0x10);
    RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(actor);
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


// FUNCTION: GAME 0x00513360
void RHGame::FUN_00513360(void *event)
{
    unsigned index = *(unsigned *)((char *)event + 0x08);
    for (; index < 3; ++index)
        (*(RHGameNotificationCalls **)((char *)this + 0x196c))->FUN_0055e7a0(index);
}

// FUNCTION: GAME 0x00513490
void RHGame::FUN_00513490(void *event)
{
    unsigned value = *(unsigned *)((char *)event + 0x08);
    RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(*(void **)((char *)event + 0x10));
    if (portrait)
        portrait->FUN_005d9140(value);
}

// FUNCTION: GAME 0x00513620
void RHGame::FUN_00513620(void *event)
{
    void *actor = *(void **)((char *)event + 0x10);
    if (m_5a)
    {
        ((RHActorPCTemplateCalls *)actor)->FUN_00493660(1);
        ((RHWidgetPortrait *)*(void **)((char *)actor + 0x4ec))->Method005d6690();
        ((RHGameSyncCalls *)this)->FUN_005146f0();
    }
    else
    {
        RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(actor);
        if (portrait)
            ((RHWidgetPortrait *)portrait)->Method005d6690();
    }
}

// FUNCTION: GAME 0x00513110
void RHGame::FUN_00513110(void *event)
{
    RHGameActionCalls *calls = (RHGameActionCalls *)this;
    calls->FUN_005110e0(*(unsigned short *)((char *)this + 0x355c));
    unsigned value = *(unsigned *)((char *)event + 0x08);
    calls->FUN_00510fc0((unsigned short)value);
    unsigned stored = *(unsigned *)((char *)event + 0x08);
    *(unsigned short *)((char *)this + 0x355c) = (unsigned short)stored;
}

// FUNCTION: GAME 0x005131d0
void RHGame::FUN_005131d0(void *)
{
    if (m_59)
    {
        RHGameActionCalls *calls = (RHGameActionCalls *)this;
        calls->FUN_00511210(*(unsigned short *)((char *)this + 0x355c));
        calls->FUN_00510fc0(*(unsigned short *)((char *)this + 0x355c));
        FUN_005140b0();
    }
}

// FUNCTION: GAME 0x005139b0
void RHGame::FUN_005139b0(void *)
{
    ((SBThreadedInput *)*(void **)((char *)this + 0x0c))->SetMouseEnabled(m_5d);
    ((SBThreadedInput *)*(void **)((char *)this + 0x0c))->CleanUpInputs();
    ((RHUnk005ef320 *)*(void **)((char *)this + 0x10))->FUN_005ef380(0);
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

// FUNCTION: GAME 0x00512be0
void RHGame::FUN_00512be0(void *event)
{
    if (m_5a)
    {
        char *actor = *(char **)((char *)event + 0x10);
        SBGeoPoint2D position(*(SBGeoPoint2D *)(*(char **)(actor + 0x50) + 0x24));
        ((RHEngine *)m_18)->FUN_004deeb0(position, position);
        char *widget = *(char **)((char *)this + 0x17c0);
        const SBGeoPoint2D *origin = widget ? (SBGeoPoint2D *)(widget + 0x80) :
            (SBGeoPoint2D *)((char *)this + 0x17d4);
        ((RHGameMenuText *)((char *)this + 0x29b4))->v10(*origin);
        ((RHGameWidgetCalls *)((char *)this + 0x29b4))->FUN_0051df00(*(void **)((char *)event + 0x10));
    }
}

extern std::string g_unk0x006c0eb8;
extern std::string g_unk0x006c0ec8;

// FUNCTION: GAME 0x00512cb0
void RHGame::FUN_00512cb0(void *)
{
    RHGameContinueCalls *profile = (RHGameContinueCalls *)
        ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
    if (!((RHEngine *)m_18)->FUN_004c7c90())
    {
        *(char *)((char *)this + 0x64) = 1;
        return;
    }
    RHSaveGame *saveGame = (RHSaveGame *)((RHUnk0056fb70 *)profile)->FUN_0056fb70(&g_unk0x006c0eb8);
    if (!saveGame)
        saveGame = profile->FUN_0056f730(FUN_005e23d0(248), g_unk0x006c0eb8);
    else
    {
        RHSaveGame *backup = (RHSaveGame *)((RHUnk0056fb70 *)profile)->FUN_0056fb70(&g_unk0x006c0ec8);
        if (!backup)
            backup = profile->FUN_0056f730(FUN_005e23d0(249), g_unk0x006c0ec8);
        profile->FUN_0056f700(saveGame, backup, FUN_005e23d0(249));
    }
    ((RHGameActionCalls *)m_18)->FUN_004da2f0();
    RHGameMission *mission = ((RHGameCampaignView *)g_unk0x6c07fc)->m_178;
    Serialize(**(unsigned long **)mission, saveGame, true);
    ((RHPlayerProfileManager *)g_unk0x006c0e48)->Save();
    ((RHGameActionCalls *)((char *)this + 0x68))->FUN_005104d0(*(SBGeoPoint2D *)FUN_005104c0());
    (*(SBThreadedInput **)((char *)this + 0x0c))->CleanUpInputs();
}

class RHMenuYesNo
{
public:
    static bool AskForConfirmation(RHMenuWindowScreen *screen, const std::wstring &text);
};

class RHUnk0063a1d0
{
public:
    unsigned FUN_0063a1d0();
};

// Parked: the early-return string cleanup is merged with the final cleanup instead of retaining both copies.
// STUB: GAME 0x00512eb0
void RHGame::FUN_00512eb0(void *)
{
    RHGameContinueCalls *profile = (RHGameContinueCalls *)
        ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
    RHGameMission *mission = ((RHGameCampaignView *)g_unk0x6c07fc)->m_178;
    std::string name;
    if (((RHEngine *)m_18)->FUN_004c7c90() == false)
    {
        *(char *)((char *)this + 0x63) = 1;
        return;
    }
    if (*((char *)RHUnk00546050() + 0x14))
        name = g_unk0x006c0ec8;
    else
        name = g_unk0x006c0eb8;
    RHSaveGame *saveGame = (RHSaveGame *)((RHUnk0056fb70 *)profile)->FUN_0056fb70(&name);
    if (saveGame)
    {
        if (((RHUnk0063a1d0 *)saveGame)->FUN_0063a1d0() != **(unsigned long **)mission)
        {
            bool confirmed;
            {
                RHMenuScreenView dialog(0, 0, true, true, (char *)this + 0x68);
                confirmed = RHMenuYesNo::AskForConfirmation(&dialog, FUN_005e23d0(0x105));
            }
            if (confirmed != true)
                return;
        }
        *(int *)((char *)this + 0x3550) = 7;
        *(RHSaveGame **)((char *)this + 0x3554) = saveGame;
    }
}

class RHGameSelectionArray
{
public:
    unsigned Size() const
    {
        if (!m_first)
            return 0;
        return m_last - m_first;
    }
    RHGameActorView *Get(unsigned char index) const { return m_first[index]; }
    RHGameActorView *GetForPortrait(unsigned index) const
    {
        RHGameActorView **first = m_first;
        return first[(unsigned char)index];
    }
    RHGameActorView **m_first;
    RHGameActorView **m_last;
};

// FUNCTION: GAME 0x00513390
void RHGame::FUN_00513390(void *event)
{
    unsigned action = *(unsigned *)((char *)event + 8);
    void *actor = *(void **)((char *)event + 0x10);
    if (!actor)
    {
        unsigned count = (unsigned char)((RHGameSelectionArray *)((char *)g_pEngine + 0x493c))->Size();
        for (unsigned index = 0; index < count; ++index)
        {
            RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(
                ((RHGameSelectionArray *)((char *)g_pEngine + 0x493c))->GetForPortrait(index));
            if (portrait)
                ((RHWidgetPortrait *)portrait)->FUN_005d9090(action);
        }
        RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(8, 0, action));
    }
    else
    {
        RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(actor);
        if (portrait)
            ((RHWidgetPortrait *)portrait)->FUN_005d9090(action);
    }
    FUN_005140b0();
}

// FUNCTION: GAME 0x00513b00
void RHGame::FUN_00513b00(int value)
{
    switch (((RHEngine *)m_18)->FUN_004ded90(0) & 0xff)
    {
    case 0:
    {
        RHUnk005165f0 *first = (RHUnk005165f0 *)((char *)this + 0x1eac);
        ((RHUnk005165f0 *)((char *)this + 0x1f7c))->m_05 = 0;
        ((RHUnk005165f0 *)((char *)this + 0x1eac))->m_05 = 0;
        ((RHGameWidgetSelectCalls *)first)->v21(0);
        ((RHGameWidgetSelectCalls *)((char *)this + 0x1f7c))->v21(0);
        first->FUN_005169f0(0);
        ((RHUnk005165f0 *)((char *)this + 0x1f7c))->FUN_005169f0(0);
        break;
    }
    case 2:
        ((RHGameWidgetSelectCalls *)((char *)this + 0x1eac))->v21(1);
        ((RHUnk005165f0 *)((char *)this + 0x1eac))->m_05 = 1;
        ((RHUnk005165f0 *)((char *)this + 0x1eac))->FUN_005169f0(0);
        ((RHGameWidgetSelectCalls *)((char *)this + 0x1f7c))->v21(0);
        ((RHUnk005165f0 *)((char *)this + 0x1f7c))->m_05 = 0;
        ((RHUnk005165f0 *)((char *)this + 0x1f7c))->FUN_005169f0(0);
        break;
    case 1:
        ((RHGameWidgetSelectCalls *)((char *)this + 0x1eac))->v21(0);
        ((RHUnk005165f0 *)((char *)this + 0x1eac))->m_05 = 0;
        ((RHUnk005165f0 *)((char *)this + 0x1eac))->FUN_005169f0(0);
        ((RHGameWidgetSelectCalls *)((char *)this + 0x1f7c))->v21(1);
        ((RHUnk005165f0 *)((char *)this + 0x1f7c))->m_05 = 1;
        ((RHUnk005165f0 *)((char *)this + 0x1f7c))->FUN_005169f0(0);
        break;
    case 3:
        ((RHGameWidgetSelectCalls *)((char *)this + 0x1eac))->v21(1);
        ((RHUnk005165f0 *)((char *)this + 0x1eac))->m_05 = 1;
        ((RHUnk005165f0 *)((char *)this + 0x1eac))->FUN_005169f0(0);
        ((RHGameWidgetSelectCalls *)((char *)this + 0x1f7c))->v21(1);
        ((RHUnk005165f0 *)((char *)this + 0x1f7c))->m_05 = 1;
        ((RHUnk005165f0 *)((char *)this + 0x1f7c))->FUN_005169f0(0);
        break;
    }
}

// FUNCTION: GAME 0x005134c0
void RHGame::FUN_005134c0(void *event)
{
    void *actor = *(void **)((char *)event + 0x10);
    if (!m_5a)
    {
        if (!actor)
        {
            (*(RHPortraitBar **)((char *)this + 0x196c))->FUN_0055ecb0(false);
            return;
        }
        (*(RHPortraitBar **)((char *)this + 0x196c))->SetPortraitOpened(actor, false);
        return;
    }
    if (actor)
    {
        ((RHEngineReinforcementCalls *)actor)->FUN_004936a0(1);
        ((RHGameSyncCalls *)this)->FUN_005146f0();
    }
    else
    {
        ((RHGameActionCalls *)this)->FUN_0050eff0();
        ((RHGameSyncCalls *)this)->FUN_005146f0();
    }
}

// FUNCTION: GAME 0x00513520
void RHGame::FUN_00513520(void *event)
{
    void *actor = *(void **)((char *)event + 0x10);
    if (!m_5a)
    {
        if (!actor)
        {
            (*(RHPortraitBar **)((char *)this + 0x196c))->FUN_0055ecb0(true);
            return;
        }
        char visible = (char)((RHUnk00493a80 *)actor)->FUN_00493a80();
        if (visible)
            (*(RHPortraitBar **)((char *)this + 0x196c))->SetPortraitOpened(actor, true);
        return;
    }

    if (!actor)
    {
        unsigned count = (unsigned char)((RHGameSelectionArray *)((char *)g_pEngine + 0x493c))->Size();
        for (; count != 0; --count)
        {
            RHGameActorView *view = ((RHGameSelectionArray *)((char *)g_pEngine + 0x493c))->GetForPortrait((unsigned char)(count - 1));
            RHWidgetPortrait *portrait = *(RHWidgetPortrait **)((char *)view + 0x4ec);
            char visible = (char)((RHUnk00493a80 *)view)->FUN_00493a80();
            if (visible)
            {
                ((RHActorPCTemplateCalls *)view)->FUN_00493660(1);
                portrait->Method005d6690();
            }
        }
    }
    else
    {
        char visible = (char)((RHUnk00493a80 *)actor)->FUN_00493a80();
        if (visible)
        {
            ((RHActorPCTemplateCalls *)actor)->FUN_00493660(1);
            ((RHWidgetPortrait *)*(void **)((char *)actor + 0x4ec))->Method005d6690();
        }
    }
    ((RHGameSyncCalls *)this)->FUN_005146f0();
}

class RHConsole
{
public:
    static RHConsole *GetInstance();
    bool HandleCharacter(unsigned short character);
    bool Flag5b6() const { return m_5b6; }
    unsigned char m_00[0x5b6];
    bool m_5b6;
};

extern bool g_mouseEnabled;
bool FUN_005edae0(RHUnk005ef320 *, const char *, ...);

class RHUnk005ef390
{
public:
    void FUN_005ef390();
};

// FUNCTION: GAME 0x005138b0
void RHGame::FUN_005138b0(void *)
{
    if (RHConsole::GetInstance()->Flag5b6() &&
        *(int *)((char *)this + 0x1ff8) != 8 &&
        *(int *)((char *)this + 0x1ff8) != 5)
        return;
    m_5d = g_mouseEnabled;
    ((SBThreadedInput *)*(void **)((char *)this + 0x0c))->SetMouseEnabled(false);
    if (RHConsole::GetInstance()->m_5b6)
    {
        ((RHUnk005ef390 *)*(void **)((char *)this + 0x10))->FUN_005ef390();
        // STRING: GAME 0x006b0550
        FUN_005edae0((RHUnk005ef320 *)*(void **)((char *)this + 0x10), "Enter Code:");
    }
    ((RHUnk005ef320 *)*(void **)((char *)this + 0x10))->FUN_005ef380(1);
    ((RHGameActionCalls *)*(void **)((char *)this + 0x10))->FUN_005e5260();
    bool done;
    do
    {
        done = !RHConsole::GetInstance()->HandleCharacter(SBThreadedInput::GetChar());
        ((RHGameActionCalls *)*(void **)((char *)this + 0x10))->FUN_005e5260();
    } while (!done);
    RHUnk00546050()->RHUnk005460c0(RHUnk5490f0(0x25));
}

// FUNCTION: GAME 0x00513210
void RHGame::FUN_00513210(void *event)
{
    char keep = 1;
    void *actor = *(void **)((char *)event + 0x10);
    unsigned action = *(unsigned *)((char *)event + 0x08);
    if (!actor)
    {
        unsigned count = (unsigned char)((RHGameSelectionArray *)((char *)g_pEngine + 0x493c))->Size();
        for (unsigned index = 0; index < count; ++index)
        {
            RHGameActorView *view = ((RHGameSelectionArray *)((char *)g_pEngine + 0x493c))->GetForPortrait((unsigned char)index);
            RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(view);
            if (portrait)
                ((RHWidgetPortrait *)portrait)->FUN_005d9090(action);
            char hit = (char)((RHEngineActionCalls *)m_18)->FUN_004d2300(view, action);
            if (hit)
                keep = 0;
        }
        if (keep)
            RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(8, 0, action));
    }
    else
    {
        RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(actor);
        if (portrait)
            ((RHWidgetPortrait *)portrait)->FUN_005d9090(action);
        char hit = (char)((RHEngineActionCalls *)m_18)->FUN_004d2300(actor, action);
        keep = hit == 0;
    }
    if (*(char *)((char *)m_18 + 0x71))
        ((RHSound *)g_unk0x006c1070)->PlayJingle(keep ? 4 : 5);
    FUN_005140b0();
}

// Parked: two complete reconstructions hoist the first two vptr reads before the widget state stores.
// STUB: GAME 0x00513e60
void RHGame::FUN_00513e60()
{
}

// FUNCTION: GAME 0x00513ff0
void RHGame::FUN_00513ff0()
{
    RHMessenger *messenger = RHUnk00546050();
    if (!m_59)
    {
        unsigned short action = FUN_00514470();
        *(unsigned short *)((char *)this + 0x355c) = action;
        messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(5, 0, action));
    }
    else
    {
        unsigned short action = *(unsigned short *)((char *)this + 0x355c) + 1;
        if (action == 3)
            action = 0;
        messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(9, 0, action));
    }
}

// FUNCTION: GAME 0x00513da0
void RHGame::FUN_00513da0(void *event)
{
    char *actor = *(char **)((char *)event + 0x10);
    RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(actor);
    if (portrait)
    {
        unsigned action = *(unsigned *)((char *)event + 8);
        if (!actor[(unsigned short)action + 0x508] && !actor[(unsigned short)action + 0x50b])
            portrait->FUN_005d9a60(action);
    }
}

// FUNCTION: GAME 0x00513df0
void RHGame::FUN_00513df0(void *)
{
    (*(SBThreadedInput **)((char *)this + 0x0c))->SetMouseEnabled(true);
    ((RHGameActionCalls *)((char *)this + 0x68))->FUN_005104d0(*(SBGeoPoint2D *)FUN_005104c0());
    (*(SBThreadedInput **)((char *)this + 0x0c))->CleanUpInputs();
    ((RHGameActionCalls *)((char *)this + 0x68))->FUN_00510550(
        SBGeoVector2D(*(SBGeoVector2D *)(*(SBThreadedInput **)((char *)this + 0x0c))->FUN_005104b0()));
    *(char *)((char *)this + 0x19cd) = 1;
    if (!*(volatile char *)((char *)this + 0x5a))
        *(char *)((char *)this + 0x3481) = 1;
}

#include "SBPictureTargaCore.h"

class RHGameScreenshotCalls
{
public:
    void FUN_004da390(SBPicture &picture);
};

extern "C" int sprintf(char *, const char *, ...);
bool FUN_005f6400(const std::string &name);

// FUNCTION: GAME 0x00513670
void RHGame::FUN_00513670(void *)
{
    SBPictureTarga picture;
    char capture = *((char *)RHUnk00546050() + 0x16);
    if (capture)
        ((RHGameScreenshotCalls *)m_18)->FUN_004da390(picture);
    else
    {
        picture.FUN_00611c80(*(SBPictureUnkDrawManager **)((char *)this + 0x10), 0);
        if (*((char *)RHUnk00546050() + 0x14))
            picture.FUN_00612d80(3, 3);
    }
    char filename[48];
    unsigned short index = 0;
    bool available;
    do
    {
        sprintf(filename,
            // STRING: GAME 0x006b0540
            "screen%03li.tga", (unsigned)index);
        available = !FUN_005f6400(std::string(filename));
        if (available)
            break;
        ++index;
    } while (index < 999);
    picture.SaveToFile(std::string(filename));
    picture.FUN_00611c50();
}

// FUNCTION: GAME 0x00513a60
void RHGame::FUN_00513a60(void *)
{
    memset((char *)this + 0x1960, 0, 10);
    memset((char *)this + 0x1860, 0, 0x100);
    RHGameActionCalls *calls = (RHGameActionCalls *)((char *)this + 0x68);
    calls->FUN_00619cc0();
    calls->FUN_005104d0(*(SBGeoPoint2D *)FUN_005104c0());
    ((SBThreadedInput *)*(void **)((char *)this + 0x0c))->CleanUpInputs();
}

// FUNCTION: GAME 0x00513090
void RHGame::FUN_00513090(void *)
{
    RHGameActionCalls *calls = (RHGameActionCalls *)*(void **)((char *)this + 0x18);
    calls->FUN_004da2f0();
    ((RHGameActionCalls *)*(void **)((char *)this + 0x1c))->FUN_005a7b40(2);
    m_5e = 1;
    FUN_00512310();
}

// FUNCTION: GAME 0x005130c0
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

// FUNCTION: GAME 0x00513150
void RHGame::FUN_00513150(void *event)
{
    RHGameActionCalls *calls = (RHGameActionCalls *)this;
    m_59 = 0;
    g_unk0x006c12b6 = 0;
    void *actor = *(void **)((char *)event + 0x10);
    if (!actor)
        calls->FUN_005110e0(*(unsigned short *)((char *)this + 0x355c));
    else
    {
        RHGamePortraitCalls *portrait = ((RHGameSyncCalls *)this)->FUN_0050f140(actor);
        if (portrait)
            portrait->FUN_005d8fa0(*(unsigned short *)((char *)this + 0x355c),
                ((RHEngineActionCalls *)m_18)->FUN_004d2300(actor, *(unsigned short *)((char *)this + 0x355c)));
    }
    FUN_005140b0();
}

// FUNCTION: GAME 0x005140b0
void RHGame::FUN_005140b0()
{
    unsigned count = (unsigned char)((RHGameSelectionArray *)((char *)g_pEngine + 0x493c))->Size();
    bool any = false;
    for (unsigned action = 0; action < 3; ++action)
    {
        for (unsigned index = 0; index < count; ++index)
        {
            if ((unsigned char)((RHEngineActionCalls *)m_18)->FUN_004d2300(
                ((RHGameSelectionArray *)((char *)g_pEngine + 0x493c))->Get(index), action))
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
    game->FUN_0048a970(RHUnk00549250(22, 0, *(unsigned short *)((char *)messenger + 0xa2)));
    FUN_0050eca0(m_3558 && !m_355a);
    FUN_0050eb80(m_3559 && !m_355b);
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

// Parked: raw selection-search locals spill this and change the scan schedule; two shapes exhausted.
// STUB: GAME 0x00514470
unsigned short RHGame::FUN_00514470()
{
    void **first = *(void ***)((char *)g_pEngine + 0x493c);
    unsigned count = (first == 0 ? 0 : *(void ***)((char *)g_pEngine + 0x4940) - first) & 0xff;
    for (unsigned action = 0; action < 3; ++action)
    {
        unsigned index;
        for (index = 0; index < count; ++index)
        {
            void *actor = (*(void ***)((char *)g_pEngine + 0x493c))[index & 0xff];
            char *engine = (char *)m_18;
            bool selected;
            if (actor)
            {
                *(void **)(engine + 0x4a18) = actor;
                *(bool *)(engine + 0x4a10) = true;
                *(void **)(engine + 0x4a04) = **(void ***)(engine + 0x49fc);
                int size = *(int *)(engine + 0x4a00);
                int position = 0;
                while (position < size)
                {
                    if (*(void **)(*(char **)(engine + 0x4a04) + 8) == *(void **)(engine + 0x4a18))
                        break;
                    *(void **)(engine + 0x4a04) = **(void ***)(engine + 0x4a04);
                    ++position;
                }
                if (position < size)
                {
                    *(int *)(engine + 0x4a14) = position;
                    *(bool *)(engine + 0x4a08) = false;
                    *(int *)(engine + 0x4a0c) = position;
                }
                else
                {
                    *(bool *)(engine + 0x4a08) = true;
                    *(int *)(engine + 0x4a14) = -1;
                }
                selected = *(int *)(engine + 0x4a14) != -1;
            }
            else
                selected = *(int *)(engine + 0x4a00) != 0;
            if (selected && (char)((RHEngineActionCalls *)engine)->FUN_004d2300(actor, action))
                break;
        }
        if (index == count)
            return action;
    }
    return 0;
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

#include <stdlib.h>

// FUNCTION: GAME 0x005145b0
void RHGame::FUN_005145b0()
{
    RHEngine *engine = g_pEngine;
    RHCampaign *campaign = (RHCampaign *)g_unk0x6c07fc;
    std::vector<RHPCDescription *> *characters = campaign->FUN_004553f0();
    unsigned short count = campaign->GetNumberOfPeasantsToConvertToBlazons();
    unsigned index = 0;
    for (RHPCDescription **cursor = characters->begin(); cursor != characters->end(); ++cursor, ++index)
    {
        RHPCDescription *character = *cursor;
        if ((unsigned short)index < count)
        {
            if (rand() % 200 < *(short *)((char *)character + 0x14))
                campaign->FUN_00455b80(character);
            else
                campaign->FUN_00455b20(character);
            engine->FUN_004d8fd0(character);
        }
    }
    campaign->FUN_004559f0();
    unsigned short cost = *(unsigned short *)(**(char ***)((char *)campaign + 0x17c) + 0x70);
    ((RHUnk00450b60 *)campaign)->Unk(3, count / cost);
}

#include "RHPortraitQuickList.h"

// FUNCTION: GAME 0x005146f0
void RHGameSyncCalls::FUN_005146f0()
{
    if (!*(char *)((char *)this + 0x57) && ((RHGameCampaignView *)g_unk0x6c07fc)->m_17c)
    {
        RHPortraitQuickList *list = *(RHPortraitQuickList **)((char *)this + 0x29ac);
        if (list)
            list->FUN_005dd1d0(*(RHPortraitPCList *)((char *)g_pEngine + 0x49f8));
    }
}

// FUNCTION: GAME 0x00514ac0
void RHGameTextCalls::FUN_00514ac0(const std::wstring &text, unsigned duration)
{
    ((std::wstring *)((char *)this + 0x3564))->assign(text, 0, std::wstring::npos);
    *(unsigned *)((char *)this + 0x3574) = duration;
}

class RHGameTooltip
{
public:
    void Set(const std::wstring &value)
    {
        m_enabled = 1;
        m_text.assign(value, 0, std::wstring::npos);
    }
    void SetExternal(const std::wstring &value)
    {
        m_enabled = 1;
        typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
        Assign assign = &std::wstring::assign;
        (m_text.*assign)(value, 0, std::wstring::npos);
    }
    char m_enabled;
    char m_opaque[0x17];
    std::wstring m_text;
};

// FUNCTION: GAME 0x00514c50
void RHGame::FUN_00514c50()
{
    unsigned start;
    unsigned quit;
    if (m_5a == 1)
    {
        if (m_57 == 1)
        {
            start = 325;
            quit = 300;
        }
        else
        {
            start = 298;
            quit = 300;
        }
    }
    else
    {
        start = 293;
        quit = 292;
    }
    ((RHGameTooltip *)((char *)this + 0x27d8))->SetExternal(FUN_005e23d0(start));
    ((RHGameTooltip *)((char *)this + 0x28c4))->Set(FUN_005e23d0(quit));
}

// GLOBAL: GAME 0x006c0b48
RHUnk00514e10::Node *g_unk0x006c0b48;

// GLOBAL: GAME 0x006c0b4c
unsigned g_unk0x006c0b4c;

// FUNCTION: GAME 0x00514e10
int &RHUnk00514e10::FUN_00514e10(const int &key)
{
    Value value(key, 0);
    Pair result;
    result = FUN_00514ff0(value);
    return result.first.node->value.second;
}

// FUNCTION: GAME 0x00514e50
void RHUnk00514e10::FUN_00514e50()
{
    FUN_00514ec0(Iterator(m_head->left), Iterator(m_head));
    operator delete(m_head);
    m_head = 0;
    m_size = 0;
    {
        RHUnk00641782 lock;
        if (--g_unk0x006c0b4c == 0)
        {
            operator delete(g_unk0x006c0b48);
            g_unk0x006c0b48 = 0;
        }
    }
}

// FUNCTION: GAME 0x00514ec0
RHUnk00514e10::Iterator RHUnk00514e10::FUN_00514ec0(Iterator first, Iterator last)
{
    if (m_size != 0 && first.node == m_head->left && last.node == m_head)
    {
        RHUnk00641782 lock;
        Node *node = m_head->parent;
        {
            RHUnk00641782 inner;
            for (Node *next = node; next != g_unk0x006c0b48; node = next)
            {
                FUN_00515640(next->right);
                next = next->left;
                operator delete(node);
            }
        }
        Root() = g_unk0x006c0b48;
        m_size = 0;
        Leftmost() = m_head;
        Rightmost() = m_head;
        return begin();
    }
    while (first.node != last.node)
        FUN_00515120(first++);
    return first;
}

// FUNCTION: GAME 0x00514ff0
RHUnk00514e10::Pair RHUnk00514e10::FUN_00514ff0(const Value &value)
{
    Node *parent = m_head;
    Node *node = parent->parent;
    bool left = true;
    {
        RHUnk00641782 lock;
        while (node != g_unk0x006c0b48)
        {
            parent = node;
            left = value.first < node->value.first;
            node = left ? node->left : node->right;
        }
    }
    if (m_multi)
    {
        Pair result(FUN_005156d0(node, parent, value), true);
        return result;
    }
    Iterator previous(parent);
    if (left)
    {
        if (previous.node == m_head->left)
        {
            Pair result(FUN_005156d0(node, parent, value), true);
            return result;
        }
        previous.FUN_005159d0();
    }
    if (previous.node->value.first < value.first)
    {
        Pair result(FUN_005156d0(node, parent, value), true);
        return result;
    }
    Pair result(previous, false);
    return result;
}

inline void RHUnk00514e10::RotateLeft(Node *node)
{
    RHUnk00641782 lock;
    Node *right = node->right;
    node->right = right->left;
    if (right->left != g_unk0x006c0b48)
        right->left->parent = node;
    right->parent = node->parent;
    if (node == Root())
        Root() = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}

inline void RHUnk00514e10::RotateRight(Node *node)
{
    RHUnk00641782 lock;
    Node *left = node->left;
    node->left = left->right;
    if (left->right != g_unk0x006c0b48)
        left->right->parent = node;
    left->parent = node->parent;
    if (node == Root())
        Root() = left;
    else if (node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    left->right = node;
    node->parent = left;
}

static inline RHUnk00514e10::Node *RHGameTreeMax(RHUnk00514e10::Node *node);
static inline RHUnk00514e10::Node *RHGameTreeMin(RHUnk00514e10::Node *node);

// FUNCTION: GAME 0x00515120
RHUnk00514e10::Iterator RHUnk00514e10::FUN_00515120(Iterator entry)
{
    Node *removed = (entry++).node;
    Node *original = removed;
    Node *replacement;
    RHUnk00641782 lock;
    if (Left(removed) == g_unk0x006c0b48)
        replacement = Right(removed);
    else if (Right(removed) == g_unk0x006c0b48)
        replacement = Left(removed);
    else
    {
        removed = RHGameTreeMin(Right(removed));
        replacement = Right(removed);
    }
    if (removed != original)
    {
        Parent(Left(original)) = removed;
        Left(removed) = Left(original);
        if (removed == Right(original))
            Parent(replacement) = removed;
        else
        {
            Parent(replacement) = Parent(removed);
            Left(Parent(removed)) = replacement;
            Right(removed) = Right(original);
            Parent(Right(original)) = removed;
        }
        if (Root() == original)
            Root() = removed;
        else if (Left(Parent(original)) == original)
            Left(Parent(original)) = removed;
        else
            Right(Parent(original)) = removed;
        Parent(removed) = Parent(original);
        std::swap(Color(removed), Color(original));
        removed = original;
    }
    else
    {
        Parent(replacement) = Parent(removed);
        if (Root() == original)
            Root() = replacement;
        else if (Left(Parent(original)) == original)
            Left(Parent(original)) = replacement;
        else
            Right(Parent(original)) = replacement;
        if (Leftmost() == original)
        {
            if (Right(original) == g_unk0x006c0b48)
                Leftmost() = Parent(original);
            else
                Leftmost() = RHGameTreeMin(replacement);
        }
        if (Rightmost() == original)
        {
            if (Left(original) == g_unk0x006c0b48)
                Rightmost() = Parent(original);
            else
                Rightmost() = RHGameTreeMax(replacement);
        }
    }
    if (Color(removed) == 1)
    {
        while (replacement != Root() && Color(replacement) == 1)
        {
            if (replacement == Left(Parent(replacement)))
            {
                Node *sibling = Right(Parent(replacement));
                if (Color(sibling) == 0)
                {
                    Color(sibling) = 1;
                    Color(Parent(replacement)) = 0;
                    RotateLeft(Parent(replacement));
                    sibling = Right(Parent(replacement));
                }
                if (Color(Left(sibling)) == 1 && Color(Right(sibling)) == 1)
                {
                    Color(sibling) = 0;
                    replacement = Parent(replacement);
                }
                else
                {
                    if (Color(Right(sibling)) == 1)
                    {
                        Color(Left(sibling)) = 1;
                        Color(sibling) = 0;
                        RotateRight(sibling);
                        sibling = Right(Parent(replacement));
                    }
                    Color(sibling) = Color(Parent(replacement));
                    Color(Parent(replacement)) = 1;
                    Color(Right(sibling)) = 1;
                    RotateLeft(Parent(replacement));
                    break;
                }
            }
            else
            {
                Node *sibling = Left(Parent(replacement));
                if (Color(sibling) == 0)
                {
                    Color(sibling) = 1;
                    Color(Parent(replacement)) = 0;
                    RotateRight(Parent(replacement));
                    sibling = Left(Parent(replacement));
                }
                if (Color(Right(sibling)) == 1 && Color(Left(sibling)) == 1)
                {
                    Color(sibling) = 0;
                    replacement = Parent(replacement);
                }
                else
                {
                    if (Color(Left(sibling)) == 1)
                    {
                        Color(Right(sibling)) = 1;
                        Color(sibling) = 0;
                        RotateLeft(sibling);
                        sibling = Left(Parent(replacement));
                    }
                    Color(sibling) = Color(Parent(replacement));
                    Color(Parent(replacement)) = 1;
                    Color(Left(sibling)) = 1;
                    RotateRight(Parent(replacement));
                    break;
                }
            }
        }
        Color(replacement) = 1;
    }
    operator delete(removed);
    --m_size;
    return entry;
}

// FUNCTION: GAME 0x00515640
void RHUnk00514e10::FUN_00515640(Node *node)
{
    RHUnk00641782 lock;
    for (Node *next = node; next != g_unk0x006c0b48; node = next)
    {
        FUN_00515640(next->right);
        next = next->left;
        operator delete(node);
    }
}

struct RHsoundGroup;
typedef std::pair<const unsigned long, RHsoundGroup *> RHGameFoldedPair;

namespace std
{
    void _Construct(RHGameFoldedPair *destination, const RHGameFoldedPair &value);
}

// FUNCTION: GAME 0x005156d0
RHUnk00514e10::Iterator RHUnk00514e10::FUN_005156d0(Node *node, Node *parent, const Value &value)
{
    RHUnk00641782 lock;
    Node *inserted = (Node *)operator new(sizeof(Node));
    inserted->parent = parent;
    inserted->color = 0;
    inserted->left = g_unk0x006c0b48;
    inserted->right = g_unk0x006c0b48;
    std::_Construct((RHGameFoldedPair *)&inserted->value, *(const RHGameFoldedPair *)&value);
    ++m_size;
    if (parent == m_head || node != g_unk0x006c0b48 || value.first < parent->value.first)
    {
        parent->left = inserted;
        if (parent == m_head)
        {
            Root() = inserted;
            Rightmost() = inserted;
        }
        else if (parent == Leftmost())
            Leftmost() = inserted;
    }
    else
    {
        parent->right = inserted;
        if (parent == Rightmost())
            Rightmost() = inserted;
    }
    for (node = inserted; node != Root() && node->parent->color == 0; )
    {
        if (node->parent == Left(node->parent->parent))
        {
            parent = node->parent->parent->right;
            if (parent->color == 0)
            {
                node->parent->color = 1;
                parent->color = 1;
                node->parent->parent->color = 0;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    RotateLeft(node);
                }
                node->parent->color = 1;
                node->parent->parent->color = 0;
                RotateRight(node->parent->parent);
            }
        }
        else
        {
            parent = node->parent->parent->left;
            if (parent->color == 0)
            {
                node->parent->color = 1;
                parent->color = 1;
                node->parent->parent->color = 0;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    RotateRight(node);
                }
                node->parent->color = 1;
                node->parent->parent->color = 0;
                RotateLeft(node->parent->parent);
            }
        }
    }
    Root()->color = 1;
    return Iterator(inserted);
}

struct RHGameTreeAccess
{
    static RHUnk00514e10::Node *&Left(RHUnk00514e10::Node *node) { return node->left; }
    static RHUnk00514e10::Node *&Right(RHUnk00514e10::Node *node) { return node->right; }
    static RHUnk00514e10::Node *&Parent(RHUnk00514e10::Node *node) { return node->parent; }
    static int &Color(RHUnk00514e10::Node *node) { return node->color; }
    static RHUnk00514e10::Node *Max(RHUnk00514e10::Node *node)
    {
        RHUnk00641782 inner;
        while (Right(node) != g_unk0x006c0b48)
            node = Right(node);
        return node;
    }
};

// FUNCTION: GAME 0x005159d0
void RHUnk00514e10::Iterator::FUN_005159d0()
{
    RHUnk00641782 lock;
    if (RHGameTreeAccess::Color(node) == 0 && RHGameTreeAccess::Parent(RHGameTreeAccess::Parent(node)) == node)
        node = RHGameTreeAccess::Right(node);
    else if (RHGameTreeAccess::Left(node) != g_unk0x006c0b48)
        node = RHGameTreeAccess::Max(RHGameTreeAccess::Left(node));
    else
    {
        RHUnk00514e10::Node *parent;
        while (node == RHGameTreeAccess::Left(parent = RHGameTreeAccess::Parent(node)))
            node = parent;
        node = parent;
    }
}

static inline RHUnk00514e10::Node *RHGameTreeMax(RHUnk00514e10::Node *node)
{
    RHUnk00641782 lock;
    while (node->right != g_unk0x006c0b48)
        node = node->right;
    return node;
}

static inline RHUnk00514e10::Node *RHGameTreeMin(RHUnk00514e10::Node *node)
{
    RHUnk00641782 lock;
    while (node->left != g_unk0x006c0b48)
        node = node->left;
    return node;
}

// FUNCTION: GAME 0x00515a90
void RHUnk00514e10::Iterator::FUN_00515a90()
{
    RHUnk00641782 lock;
    if (node->right != g_unk0x006c0b48)
        node = RHGameTreeMin(node->right);
    else
    {
        Node *parent;
        while (node == (parent = node->parent)->right)
            node = parent;
        if (node->right != parent)
            node = parent;
    }
}

#include "SBUIRenderer.h"


struct RHGameWidgetInput
{
    undefined m_00[0x0a];
    unsigned short flags;
    RHGameWidgetInputCalls *shortcuts;
};

struct RHGameWidgetEvent;

class RHGameWidgetDispatch
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual unsigned v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual RHGameWidgetEvent *v14(const RHGameWidgetInput &input);
    virtual RHGameWidgetEvent *v15(const RHGameWidgetInput &input);
    virtual RHGameWidgetEvent *v16(const RHGameWidgetInput &input);
    virtual RHGameWidgetEvent *v17(const RHGameWidgetInput &input);
    virtual RHGameWidgetEvent *v18(const RHGameWidgetInput &input);
    virtual bool v19(const RHGameWidgetInput &input);
};

class RHUnk00515bf0 : public RHGameWidgetView
{
public:
    void FUN_00515ba0();
    void FUN_00515bc0(unsigned long hardware);
    RHGameWidgetEvent *FUN_00515bf0(void *);
    RHGameWidgetEvent *FUN_00515c10(void *);
};

// SYNTHETIC: GAME 0x00515b40
// ??1RHGameLifetime00515b40@@QAE@XZ

// FUNCTION: GAME 0x00515ba0
void RHUnk00515bf0::FUN_00515ba0()
{
    ((SBUIUnk0060dae0 *)((char *)this + 0x80))->FUN_0060dae0(((RHGameWidgetDispatch *)this)->v9());
}

// FUNCTION: GAME 0x00515bc0
void RHUnk00515bf0::FUN_00515bc0(unsigned long hardware)
{
    ((RHGameWidgetBaseCalls *)this)->FUN_0060d290(*(const SBGeoPoint2D *)hardware);
    ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->v2(hardware);
}

// FUNCTION: GAME 0x00515bf0
RHGameWidgetEvent *RHUnk00515bf0::FUN_00515bf0(void *)
{
    RHGameWidgetEvent *event = &m_event;
    m_event.next = 0;
    m_event.widget = this;
    event->type = 0;
    m_event.value = 0;
    return event;
}

// FUNCTION: GAME 0x00515c10
RHGameWidgetEvent *RHUnk00515bf0::FUN_00515c10(void *)
{
    RHGameWidgetEvent *event = &m_event;
    m_event.next = 0;
    m_event.widget = this;
    event->type = 4;
    m_event.value = 0;
    return event;
}

class RHUnk00515c30 : public RHGameWidgetView
{
public:
    int FUN_00515c30();
    int FUN_00515ef0();
    int FUN_00515c90(const SBGeoPoint2D &point);
    RHGameWidgetEvent *FUN_00515d90(const RHGameWidgetInput &input);
};

// FUNCTION: GAME 0x00515c30
int RHUnk00515c30::FUN_00515c30()
{
    if (!m_04)
        return 0;
    int result;
    switch (m_7c)
    {
    case 2:
    case 3: result = 3; break;
    case 1: result = 2; break;
    case 0: result = 1; break;
    }
    if (result == 1 && !m_06)
        result = 255;
    return result;
}

// FUNCTION: GAME 0x00515c90
int RHUnk00515c30::FUN_00515c90(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)))
        return true;
    return false;
}

// SYNTHETIC: GAME 0x00515d30
// ??1RHGameLifetime00515d30@@QAE@XZ

// FUNCTION: GAME 0x00515d90
RHGameWidgetEvent *RHUnk00515c30::FUN_00515d90(const RHGameWidgetInput &input)
{
    RHGameWidgetDispatch *widget = (RHGameWidgetDispatch *)this;
    if (!m_04)
    {
        if (*((char *)this + 8) && widget->v19(input) &&
            ((SBUIUnk0060dae0 *)((char *)this + 0x80))->FUN_0060db80(0))
        {
            RHGameWidgetEvent *event = &m_event;
            m_event.next = 0;
            m_event.widget = this;
            m_event.value = 0;
            event->type = 18;
            return event;
        }
        return 0;
    }
    if (*(unsigned short *)((char *)this + 0x0a))
    {
        if (input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 1)
        {
            m_7c = 3;
            return widget->v17(input);
        }
        if (input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 2 ||
            input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 3)
        {
            m_7c = 2;
            return widget->v16(input);
        }
    }
    if (widget->v19(input))
    {
        if (input.flags & 0x40)
        {
            m_7c = 3;
            return widget->v17(input);
        }
        if (!(input.flags & 9))
        {
            if (!(input.flags & 0x12))
            {
                if (m_05 == 1)
                {
                    m_7c = 1;
                    return widget->v15(input);
                }
            }
            else
            {
                m_7c = 1;
                return widget->v18(input);
            }
        }
        else
        {
            m_7c = 2;
            return widget->v16(input);
        }
    }
    else if (m_7c)
    {
        m_7c = 0;
        return widget->v14(input);
    }
    return 0;
}

// FUNCTION: GAME 0x00515ef0
int RHUnk00515c30::FUN_00515ef0()
{
    return m_04 != 1 ? 255 : 0;
}

class RHUnk00515f80 : public RHGameWidgetView
{
public:
    void FUN_00515f60();
    unsigned FUN_00515f80(unsigned id);
};

// SYNTHETIC: GAME 0x00515f00
// ??1RHGameLifetime00515f00@@QAE@XZ

// FUNCTION: GAME 0x00515f60
void RHUnk00515f80::FUN_00515f60()
{
    ((RHGameRenderer005cb220 *)((char *)this + 0x80))->FUN_005cb270(((RHGameWidgetDispatch *)this)->v9());
}

// FUNCTION: GAME 0x00515f80
unsigned RHUnk00515f80::FUN_00515f80(unsigned id)
{
    SBUIUnk0060d530 *renderer = (SBUIUnk0060d530 *)((char *)this + 0x80);
    unsigned previous = ((unsigned *)((char *)renderer + 0x40))[(*(unsigned *)((char *)renderer + 0x48)) & 1];
    unsigned current = id == 255 ? 0 : renderer->FUN_0060d500(id);
    if (current == (unsigned)-1)
        return 3;
    if (previous != current)
        return current == 0 ? 2 : 1;
    return 0;
}

class RHUnk00516020 : public RHGameWidgetView
{
public:
    RHGameWidgetEvent *FUN_00516020(const RHGameWidgetInput &input);
};

// SYNTHETIC: GAME 0x00515fd0
// ??0RHGameLifetime00515fd0@@QAE@XZ

// FUNCTION: GAME 0x00516020
RHGameWidgetEvent *RHUnk00516020::FUN_00516020(const RHGameWidgetInput &input)
{
    if (m_04)
    {
        SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
        if (box.FUN_006083b0(*(SBGeoPoint2D *)&input) == 1 &&
            ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(
                ((SBGeoPoint2D *)&input)->Unk005fc110(*(SBGeoPoint2D *)&box)) == 1)
        {
            if (!(input.flags & 1))
            {
                RHGameWidgetEvent *event = &m_event;
                m_event.next = 0;
                m_event.value = 0;
                m_event.widget = this;
                event->type = 0;
                return event;
            }
        }
        else if (!*(unsigned short *)((char *)this + 0x0a) ||
            input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) != 2)
        {
            m_7c = 0;
            return 0;
        }
        RHGameWidgetEvent *event = &m_event;
        if (m_event.type != 2 && m_event.type != 7)
        {
            m_event.next = 0;
            m_event.value = 0;
            m_event.widget = this;
            event->type = 2;
            return event;
        }
        m_event.next = 0;
        m_event.value = 0;
        m_event.widget = this;
        event->type = 7;
        return event;
    }
    return 0;
}

class RHUnk00516200 : public RHGameWidgetView
{
public:
    RHGameWidgetEvent *FUN_00516200(const RHGameWidgetInput &input);
};

// SYNTHETIC: GAME 0x00516150
// ??0RHGameLifetime005161a0@@QAE@XZ

// SYNTHETIC: GAME 0x005161a0
// ??1RHGameLifetime005161a0@@QAE@XZ

// FUNCTION: GAME 0x00516200
RHGameWidgetEvent *RHUnk00516200::FUN_00516200(const RHGameWidgetInput &input)
{
    if (m_04)
    {
        SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
        if (box.FUN_006083b0(*(SBGeoPoint2D *)&input) == 1 &&
            ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(
                ((SBGeoPoint2D *)&input)->Unk005fc110(*(SBGeoPoint2D *)&box)) == 1)
        {
            if (!(input.flags & 1))
            {
                RHGameWidgetEvent *event = &m_event;
                m_event.next = 0;
                m_event.value = 0;
                m_event.widget = this;
                event->type = 0;
                return event;
            }
        }
        else if (!*(unsigned short *)((char *)this + 0x0a) ||
            input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) != 2)
        {
            m_7c = 0;
            return 0;
        }
        RHGameWidgetEvent *event = &m_event;
        if (m_event.type != 2 && m_event.type != 7)
        {
            m_event.next = 0;
            m_event.value = 0;
            m_event.widget = this;
            event->type = 2;
            return event;
        }
        m_event.next = 0;
        m_event.value = 0;
        m_event.widget = this;
        event->type = 7;
        return event;
    }
    return 0;
}

class RHUnk00516330 : public RHGameWidgetView
{
public:
    int FUN_00516330();
    int FUN_00516390(const SBGeoPoint2D &point);
    RHGameWidgetEvent *FUN_00516490(const RHGameWidgetInput &input);
};

// FUNCTION: GAME 0x00516330
int RHUnk00516330::FUN_00516330()
{
    if (!m_04)
        return 0;
    int result;
    switch (m_7c)
    {
    case 2:
    case 3: result = 3; break;
    case 1: result = 2; break;
    case 0: result = 1; break;
    }
    if (result == 1 && !m_06)
        result = 255;
    return result;
}

// FUNCTION: GAME 0x00516390
int RHUnk00516330::FUN_00516390(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)))
        return true;
    return false;
}

// SYNTHETIC: GAME 0x00516430
// ??1RHGameLifetime00516430@@QAE@XZ

// FUNCTION: GAME 0x00516490
RHGameWidgetEvent *RHUnk00516330::FUN_00516490(const RHGameWidgetInput &input)
{
    RHGameWidgetDispatch *widget = (RHGameWidgetDispatch *)this;
    if (!m_04)
    {
        if (*((char *)this + 8) && widget->v19(input) &&
            ((SBUIUnk0060d530 *)((char *)this + 0x80))->FUN_0060d500(0))
        {
            RHGameWidgetEvent *event = &m_event;
            m_event.next = 0;
            m_event.widget = this;
            m_event.value = 0;
            event->type = 18;
            return event;
        }
        return 0;
    }
    if (*(unsigned short *)((char *)this + 0x0a))
    {
        if (input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 1)
        {
            m_7c = 3;
            return widget->v17(input);
        }
        if (input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 2 ||
            input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 3)
        {
            m_7c = 2;
            return widget->v16(input);
        }
    }
    if (widget->v19(input))
    {
        if (input.flags & 0x40)
        {
            m_7c = 3;
            return widget->v17(input);
        }
        if (!(input.flags & 9))
        {
            if (!(input.flags & 0x12))
            {
                if (m_05 == 1)
                {
                    m_7c = 1;
                    return widget->v15(input);
                }
            }
            else
            {
                m_7c = 1;
                return widget->v18(input);
            }
        }
        else
        {
            m_7c = 2;
            return widget->v16(input);
        }
    }
    else if (m_7c)
    {
        m_7c = 0;
        return widget->v14(input);
    }
    return 0;
}

// FUNCTION: GAME 0x005165f0
int RHUnk005165f0::FUN_005165f0()
{
    if (!m_04)
        return 0;
    int result;
    switch (m_7c)
    {
    case 5: if (m_05 == 1) return 2; result = 1; break;
    case 6:
    case 7: result = 1; break;
    case 8: if (m_05 == 1) return 4; result = 3; break;
    case 9:
    case 10: result = 3; break;
    }
    if ((result == 1 || result == 3) && m_06 != 1)
        result = 255;
    return result;
}

// FUNCTION: GAME 0x00516670
RHGameWidgetEvent *RHUnk005165f0::FUN_00516670(void *)
{
    RHGameWidgetEvent *event = &m_event;
    if (event->type != 2 && event->type != 7)
        event->type = 2;
    else
        event->type = 7;
    m_event.value = m_cc == 1;
    m_event.next = 0;
    m_event.widget = this;
    return event;
}

// FUNCTION: GAME 0x005166b0
int RHUnk005165f0::FUN_005166b0(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)))
        return true;
    return false;
}

// SYNTHETIC: GAME 0x00516750
// ??1RHGameLifetime00516750@@QAE@XZ

// FUNCTION: GAME 0x005167b0
RHGameWidgetEvent *RHUnk005165f0::FUN_005167b0(const RHGameWidgetInput &input)
{
    RHGameWidgetDispatch *widget = (RHGameWidgetDispatch *)this;
    if (!m_04)
    {
        if (*((char *)this + 8) && widget->v19(input) &&
            ((SBUIUnk0060d530 *)((char *)this + 0x80))->FUN_0060d500(0))
        {
            m_event.next = 0;
            RHGameWidgetEvent *event = &m_event;
            m_event.value = 0;
            m_event.widget = this;
            event->type = 18;
            return event;
        }
        return 0;
    }
    if (*(unsigned short *)((char *)this + 0x0a))
    {
        if (input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 1)
        {
            if (!m_cc)
                m_7c = 10;
            else
                m_7c = 7;
            return widget->v17(input);
        }
        if (input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 2 ||
            input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 3)
        {
            if (!m_cc)
            {
                m_cc = 1;
                m_7c = 9;
            }
            else
            {
                m_cc = 0;
                m_7c = 6;
            }
            return widget->v16(input);
        }
    }
    if (widget->v19(input))
    {
        if (input.flags & 0x40)
        {
            if (!m_cc)
                m_7c = 7;
            else
                m_7c = 10;
            return widget->v17(input);
        }
        if (input.flags & 8)
        {
            RHGameWidgetEvent *event = &m_event;
            m_event.value = m_cc == 1;
            m_event.next = 0;
            m_event.widget = this;
            event->type = 7;
            return event;
        }
        if (input.flags & 1)
        {
            if (!m_cc)
            {
                m_cc = 1;
                m_7c = 9;
            }
            else
            {
                m_cc = 0;
                m_7c = 6;
            }
            return widget->v16(input);
        }
        if (!(input.flags & 0x12))
        {
            if (m_05 == 1)
            {
                if (!m_cc)
                    m_7c = 5;
                else
                    m_7c = 8;
                return widget->v15(input);
            }
        }
        else
            return widget->v18(input);
    }
    if (m_7c == 5 || m_7c == 7)
        m_7c = 6;
    if (m_7c == 8 || m_7c == 10)
        m_7c = 9;
    return 0;
}

// FUNCTION: GAME 0x005169f0
inline void RHUnk005165f0::FUN_005169f0(char selected)
{
    if (selected == 1)
    {
        if (!m_cc)
        {
            m_cc = 1;
            if (m_7c == 5)
                m_7c = 8;
            if (m_7c == 6)
                m_7c = 9;
        }
    }
    else if (!selected && m_cc == 1)
    {
        m_cc = 0;
        m_event.type = 0;
        if (m_7c == 8)
            m_7c = 5;
        if (m_7c == 9)
            m_7c = 6;
    }
}

class RHUnk00516b50 : public RHGameWidgetView
{
public:
    int FUN_00516b50();
    void FUN_00516ac0();
    RHGameWidgetEvent *FUN_00516ae0(const RHGameWidgetInput &input);
    int FUN_00516bb0(const SBGeoPoint2D &point);
};

// SYNTHETIC: GAME 0x00516a60
// ??1RHGameLifetime00516a60@@QAE@XZ

// FUNCTION: GAME 0x00516ac0
void RHUnk00516b50::FUN_00516ac0()
{
    ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_005c9320(((RHGameWidgetDispatch *)this)->v9());
}

// FUNCTION: GAME 0x00516ae0
RHGameWidgetEvent *RHUnk00516b50::FUN_00516ae0(const RHGameWidgetInput &input)
{
    if ((input.flags & 1) || (*(unsigned short *)((char *)this + 0x0a) &&
        input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 2))
        m_event.type = 2;
    else if ((input.flags & 8) || (*(unsigned short *)((char *)this + 0x0a) &&
        input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 3))
        m_event.type = 3;
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    return &m_event;
}

// FUNCTION: GAME 0x00516b50
int RHUnk00516b50::FUN_00516b50()
{
    if (!m_04)
        return 0;
    int result;
    switch (m_7c)
    {
    case 2:
    case 3: result = 3; break;
    case 1: result = 2; break;
    case 0: result = 1; break;
    }
    if (result == 1 && !m_06)
        result = 255;
    return result;
}

// FUNCTION: GAME 0x00516bb0
int RHUnk00516b50::FUN_00516bb0(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)))
        return true;
    return false;
}

class RHUnk00516cb0 : public RHGameWidgetView
{
public:
    void FUN_00516cb0();
    unsigned FUN_00516cd0(unsigned id);
};

// SYNTHETIC: GAME 0x00516c50
// ??1RHGameLifetime00516c50@@QAE@XZ

// FUNCTION: GAME 0x00516cb0
void RHUnk00516cb0::FUN_00516cb0()
{
    ((RHUIRendererShifting *)((char *)this + 0x80))->Render(((RHGameWidgetDispatch *)this)->v9());
}

// FUNCTION: GAME 0x00516cd0
unsigned RHUnk00516cb0::FUN_00516cd0(unsigned id)
{
    SBUIUnk0060dae0 *renderer = (SBUIUnk0060dae0 *)((char *)this + 0x80);
    unsigned previous = ((unsigned *)((char *)renderer + 0x40))[(*(unsigned *)((char *)renderer + 0x48)) & 1];
    unsigned current = id == 255 ? 0 : renderer->FUN_0060db80(id);
    if (current == (unsigned)-1)
        return 3;
    if (previous != current)
        return current == 0 ? 2 : 1;
    return 0;
}

class RHUnk00516d20 : public RHGameWidgetView
{
public:
    int FUN_00516d20();
    bool FUN_00516e80(long resource);
    bool FUN_00516ea0(char enabled);
    unsigned FUN_00516fa0(unsigned id);
    int FUN_00516d80(const SBGeoPoint2D &point);
    RHGameWidgetEvent *FUN_00516ed0(const RHGameWidgetInput &input);
    RHGameWidgetEvent *FUN_00516f60(void *);
    RHGameWidgetEvent *FUN_00517130(const RHGameWidgetInput &input);
    void FUN_00517000();
    RHGameWidgetEvent *ProcessInput(const RHGameWidgetInput &input);
};

// FUNCTION: GAME 0x00516d20
int RHUnk00516d20::FUN_00516d20()
{
    if (!m_04)
        return 0;
    int result;
    switch (m_7c)
    {
    case 2:
    case 3: result = 3; break;
    case 1: result = 2; break;
    case 0: result = 1; break;
    }
    if (result == 1 && !m_06)
        result = 255;
    return result;
}

// FUNCTION: GAME 0x00516d80
int RHUnk00516d20::FUN_00516d80(const SBGeoPoint2D &point)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
    if (box.FUN_006083b0(point) &&
        ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(point.Unk005fc110(*(SBGeoPoint2D *)&box)))
        return true;
    return false;
}

// FUNCTION: GAME 0x00516e20
RHGameLifetime00516e20::~RHGameLifetime00516e20()
{
}

// FUNCTION: GAME 0x00516e80
bool RHUnk00516d20::FUN_00516e80(long resource)
{
    return ((SBUIUnk0060d530 *)((char *)this + 0x80))->FUN_0060d550(resource);
}

// FUNCTION: GAME 0x00516ea0
bool RHUnk00516d20::FUN_00516ea0(char enabled)
{
    if (enabled == 1)
    {
        if (!m_04)
        {
            m_7c = 0;
            m_04 = enabled;
            return enabled;
        }
    }
    else if (!enabled)
        m_event.type = 4;
    m_04 = enabled;
    return true;
}

// FUNCTION: GAME 0x00516ed0
RHGameWidgetEvent *RHUnk00516d20::FUN_00516ed0(const RHGameWidgetInput &input)
{
    RHMessenger *messenger = RHUnk00546050();
    RHUnk5490f0 *message = *(RHUnk5490f0 **)((char *)this + 0xd8);
    if (message)
        messenger->RHUnk005460c0(*message);
    if ((input.flags & 1) || (*(unsigned short *)((char *)this + 0x0a) &&
        input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 2))
        m_event.type = 2;
    else if ((input.flags & 8) || (*(unsigned short *)((char *)this + 0x0a) &&
        input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 3))
        m_event.type = 3;
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    return &m_event;
}

// FUNCTION: GAME 0x00516f60
RHGameWidgetEvent *RHUnk00516d20::FUN_00516f60(void *)
{
    RHMessenger *messenger = RHUnk00546050();
    RHUnk5490f0 *message = *(RHUnk5490f0 **)((char *)this + 0xe0);
    if (message)
        messenger->RHUnk005460c0(*message);
    RHGameWidgetEvent *event = &m_event;
    m_event.next = 0;
    m_event.widget = this;
    m_event.value = 0;
    event->type = 4;
    return event;
}

static inline unsigned RHGameWidgetAnimatedComparison(SBUIUnk0060dae0 *renderer, unsigned id)
{
    unsigned previous = ((unsigned *)((char *)renderer + 0x40))[(*(unsigned *)((char *)renderer + 0x48)) & 1];
    unsigned current = id == 255 ? 0 : renderer->FUN_0060db80(id);
    if (current == (unsigned)-1)
        return 3;
    if (previous != current)
        return current == 0 ? 2 : 1;
    return 0;
}

// FUNCTION: GAME 0x00516fa0
unsigned RHUnk00516d20::FUN_00516fa0(unsigned id)
{
    if (*(unsigned short *)((char *)this + 0xe4) != 0)
        return 1;
    return RHGameWidgetAnimatedComparison((SBUIUnk0060dae0 *)((char *)this + 0x80), id);
}

// FUNCTION: GAME 0x00517000
void RHUnk00516d20::FUN_00517000()
{
    SBGeoBoundingBox2D &bounds = *(SBGeoBoundingBox2D *)((char *)this + 0xe8);
    if (bounds.Unk00608f30() &&
        bounds.m_second.m_x - bounds.m_first.m_x > 0.0f &&
        bounds.m_second.m_y - bounds.m_first.m_y > 0.0f)
        ((RHMobileUnk00607da0 *)((char *)this + 0x30))->FUN_00607da0((const RHMobileUnk00607da0 &)
            bounds.FUN_006090d0(SBGeoVector2D((float)*(unsigned short *)((char *)this + 0xe4), 0.0f)));
    if (*(unsigned short *)((char *)this + 0xe4))
    {
        if (*(unsigned short *)((char *)this + 0xe4) > *(unsigned short *)((char *)this + 0xe6))
            *(unsigned short *)((char *)this + 0xe4) -= *(unsigned short *)((char *)this + 0xe6);
        else
        {
            *(unsigned short *)((char *)this + 0xe4) = 0;
            *(unsigned short *)((char *)this + 0xe6) = 0;
            bounds.FUN_00607d90();
        }
    }
    ((RHUIRendererShifting *)((char *)this + 0x80))->SetCounter(*(unsigned short *)((char *)this + 0xe4));
    ((RHUIRendererShifting *)((char *)this + 0x80))->Render(((RHGameWidgetDispatch *)this)->v9());
}

inline RHGameWidgetEvent *RHUnk00516d20::ProcessInput(const RHGameWidgetInput &input)
{
    RHGameWidgetDispatch *widget = (RHGameWidgetDispatch *)this;
    if (!m_04)
    {
        if (*((char *)this + 8) && widget->v19(input) &&
            ((SBUIUnk0060dae0 *)((char *)this + 0x80))->FUN_0060db80(0))
        {
            RHGameWidgetEvent *event = &m_event;
            m_event.next = 0;
            m_event.widget = this;
            m_event.value = 0;
            event->type = 18;
            return event;
        }
        return 0;
    }
    if (*(unsigned short *)((char *)this + 0x0a))
    {
        if (input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 1)
        {
            m_7c = 3;
            return widget->v17(input);
        }
        if (input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 2 ||
            input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) == 3)
        {
            m_7c = 2;
            return widget->v16(input);
        }
    }
    if (widget->v19(input))
    {
        if (input.flags & 0x40)
        {
            m_7c = 3;
            return widget->v17(input);
        }
        if (!(input.flags & 9))
        {
            if (!(input.flags & 0x12))
            {
                if (m_05 == 1)
                {
                    m_7c = 1;
                    return widget->v15(input);
                }
            }
            else
            {
                m_7c = 1;
                return widget->v18(input);
            }
        }
        else
        {
            m_7c = 2;
            return widget->v16(input);
        }
    }
    else if (m_7c)
    {
        m_7c = 0;
        return widget->v14(input);
    }
    return 0;
}

// FUNCTION: GAME 0x00517130
RHGameWidgetEvent *RHUnk00516d20::FUN_00517130(const RHGameWidgetInput &input)
{
    RHGameWidgetEvent *event = ProcessInput(input);
    ((RHGameWidgetAnimatedCalls *)((char *)this + 0xd0))->FUN_005d5790(event, m_7c, 0);
    return event;
}

#pragma inline_depth(1)
// FUNCTION: GAME 0x00517280
void *RHGameLifetime00515b40::FUN_00517280(unsigned flags)
{
    this->~RHGameLifetime00515b40();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005172a0
void *RHGameLifetime00515d30::FUN_005172a0(unsigned flags)
{
    this->~RHGameLifetime00515d30();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005172c0
void *RHGameLifetime00515f00::FUN_005172c0(unsigned flags)
{
    this->~RHGameLifetime00515f00();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005172e0
void *RHGameLifetime00517300::FUN_005172e0(unsigned flags)
{
    this->~RHGameLifetime00517300();
    if (flags & 1)
        operator delete(this);
    return this;
}

// SYNTHETIC: GAME 0x00517300
// ??1RHGameLifetime00517300@@QAE@XZ

// FUNCTION: GAME 0x00517360
void *RHGameLifetime00515fd0::FUN_00517360(unsigned flags)
{
    this->~RHGameLifetime00515fd0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// SYNTHETIC: GAME 0x00517380
// ??1RHGameLifetime00515fd0@@QAE@XZ

// FUNCTION: GAME 0x005173e0
void *RHGameLifetime005161a0::FUN_005173e0(unsigned flags)
{
    this->~RHGameLifetime005161a0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00517400
void *RHGameLifetime00516430::FUN_00517400(unsigned flags)
{
    this->~RHGameLifetime00516430();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00517420
void *RHGameLifetime00516750::FUN_00517420(unsigned flags)
{
    this->~RHGameLifetime00516750();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00517440
void *RHGameLifetime00516a60::FUN_00517440(unsigned flags)
{
    this->~RHGameLifetime00516a60();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00517460
void *RHGameLifetime00516c50::FUN_00517460(unsigned flags)
{
    this->~RHGameLifetime00516c50();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00517480
void *RHGameLifetime005174a0::FUN_00517480(unsigned flags)
{
    this->~RHGameLifetime005174a0();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma inline_depth()

// SYNTHETIC: GAME 0x005174a0
// ??1RHGameLifetime005174a0@@QAE@XZ

class RHGameLifetime0050a460 : public RHGameLifetime005174a0
{
public:
    struct Points
    {
        SBGeoPoint2D m_0;
        SBGeoPoint2D m_8;
    };
    undefined m_d4[0x14];
    Points m_e8;
};

// SYNTHETIC: GAME 0x0050a460
// ??1RHGameLifetime0050a460@@QAE@XZ

// FUNCTION: GAME 0x00517500
void *RHGameLifetimeDeleteCalls::FUN_00517500(unsigned flags)
{
    ((RHGameLifetime0050a460 *)this)->~RHGameLifetime0050a460();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00517520
void *RHGameLifetimeDeleteCalls::FUN_00517520(unsigned flags)
{
    FUN_0050a4f0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// SYNTHETIC: GAME 0x0044fe90
// ??1RHGameLifetime0044fe90@@QAE@XZ

// FUNCTION: GAME 0x0044fef0
void *RHGameLifetime00517590::FUN_0044fef0(unsigned flags)
{
    this->~RHGameLifetime00517590();
    if (flags & 1)
        operator delete(this);
    return this;
}

// SYNTHETIC: GAME 0x0044ff10
// ??1RHGameLifetime00517590@@QAE@XZ

// SYNTHETIC: GAME 0x00517540
// ??0RHGameLifetime00515b40@@QAE@XZ

// SYNTHETIC: GAME 0x00517590
// ??0RHGameLifetime00517590@@QAE@XZ

// SYNTHETIC: GAME 0x005175e0
// ??0RHGameLifetime00516a60@@QAE@XZ

// FUNCTION: GAME 0x00517630
RHGameLifetime00517630::RHGameLifetime00517630()
{
    m_state = 0;
    m_d4 = 0;
    m_d8 = 0;
    m_dc = 0;
    m_e0 = 0;
}

// SYNTHETIC: GAME 0x0050a5c0
// ??1RHGameLifetime00517630@@QAE@XZ

// FUNCTION: GAME 0x005176d0
void *RHGameLifetimeDeleteCalls::FUN_005176d0(unsigned flags)
{
    ((RHGameLifetime00517630 *)this)->~RHGameLifetime00517630();
    if (flags & 1)
        operator delete(this);
    return this;
}

void EmitRHGameWidgetLifetimes(void *widget)
{
    ((RHGameLifetime00515d30 *)widget)->FUN_005172a0(0);
    ((RHGameLifetime00515f00 *)widget)->FUN_005172c0(0);
    ((RHGameLifetime00515fd0 *)widget)->FUN_00517360(0);
    ((RHGameLifetime005161a0 *)widget)->FUN_005173e0(0);
    ((RHGameLifetime00516430 *)widget)->FUN_00517400(0);
    ((RHGameLifetime00516750 *)widget)->FUN_00517420(0);
    ((RHGameLifetime00516c50 *)widget)->FUN_00517460(0);
    ((RHGameLifetime00516e20 *)widget)->~RHGameLifetime00516e20();
    ((RHGameLifetimeDeleteCalls *)widget)->FUN_00517500(0);
    ((RHGameLifetimeDeleteCalls *)widget)->FUN_00517520(0);
    ((RHGameLifetimeDeleteCalls *)widget)->FUN_005176d0(0);
    new RHGameLifetime00515fd0;
    new RHGameLifetime005161a0;
    new RHGameLifetime00517630;
}

#pragma inline_depth(0)
void EmitRHGameWidgetRendered()
{
    RHGameLifetime00515b40 first;
    RHGameLifetime00517590 second;
    RHGameLifetime00516a60 third;
    RHGameLifetime00517300 fourth;
    RHGameLifetime005174a0 fifth;
    RHGameLifetime00515fd0 sixth;
    RHGameLifetime005161a0 seventh;
    RHGameLifetime00515f00 eighth;
    RHGameLifetime0050e6c0 ninth;
    RHGameLifetime0044fe90 tenth;
    RHPortraitRootList eleventh;
}
#pragma inline_depth()

void (RHUnk00515bf0::*g_rhgameWidgetRender)() = &RHUnk00515bf0::FUN_00515ba0;
unsigned (RHUnk00515f80::*g_rhgameWidgetBitmapCompare)(unsigned) = &RHUnk00515f80::FUN_00515f80;
void (RHUnk00516cb0::*g_rhgameWidgetShiftingRender)() = &RHUnk00516cb0::FUN_00516cb0;
unsigned (RHUnk00516cb0::*g_rhgameWidgetShiftingCompare)(unsigned) = &RHUnk00516cb0::FUN_00516cd0;
bool (RHUnk00516d20::*g_rhgameWidgetResource)(long) = &RHUnk00516d20::FUN_00516e80;
unsigned (RHUnk00516d20::*g_rhgameWidgetAnimatedCompare)(unsigned) = &RHUnk00516d20::FUN_00516fa0;
void (RHUnk00516d20::*g_rhgameWidgetAnimatedRender)() = &RHUnk00516d20::FUN_00517000;

RHGameWidgetEvent *(RHUnk00515bf0::*g_rhgameWidgetEventMethods[])(void *) =
    { &RHUnk00515bf0::FUN_00515bf0, &RHUnk00515bf0::FUN_00515c10 };
int (RHUnk00515c30::*g_rhgameWidgetStateMethods[])() =
    { &RHUnk00515c30::FUN_00515c30, &RHUnk00515c30::FUN_00515ef0 };
int (RHUnk00516330::*g_rhgameWidgetBitmapState)() = &RHUnk00516330::FUN_00516330;
int (RHUnk005165f0::*g_rhgameWidgetToggleState)() = &RHUnk005165f0::FUN_005165f0;
RHGameWidgetEvent *(RHUnk005165f0::*g_rhgameWidgetToggleEvent)(void *) = &RHUnk005165f0::FUN_00516670;
int (RHUnk00516b50::*g_rhgameWidgetTitbitState)() = &RHUnk00516b50::FUN_00516b50;
int (RHUnk00516d20::*g_rhgameWidgetCustomState)() = &RHUnk00516d20::FUN_00516d20;
bool (RHUnk00516d20::*g_rhgameWidgetCustomEnable)(char) = &RHUnk00516d20::FUN_00516ea0;

void (RHUnk00515bf0::*g_rhgameWidgetHardware)(unsigned long) = &RHUnk00515bf0::FUN_00515bc0;
int (RHUnk00515c30::*g_rhgameWidgetInside)(const SBGeoPoint2D &) = &RHUnk00515c30::FUN_00515c90;
RHGameWidgetEvent *(RHUnk00515c30::*g_rhgameWidgetButtonInput)(const RHGameWidgetInput &) = &RHUnk00515c30::FUN_00515d90;
void (RHUnk00515f80::*g_rhgameWidgetBitmapRender)() = &RHUnk00515f80::FUN_00515f60;
RHGameWidgetEvent *(RHUnk00516020::*g_rhgameWidgetPictureInput)(const RHGameWidgetInput &) = &RHUnk00516020::FUN_00516020;
RHGameWidgetEvent *(RHUnk00516200::*g_rhgameWidgetMultiPictureInput)(const RHGameWidgetInput &) = &RHUnk00516200::FUN_00516200;
int (RHUnk00516330::*g_rhgameWidgetBitmapInside)(const SBGeoPoint2D &) = &RHUnk00516330::FUN_00516390;
RHGameWidgetEvent *(RHUnk00516330::*g_rhgameWidgetBitmapInput)(const RHGameWidgetInput &) = &RHUnk00516330::FUN_00516490;
int (RHUnk005165f0::*g_rhgameWidgetToggleInside)(const SBGeoPoint2D &) = &RHUnk005165f0::FUN_005166b0;
void (RHUnk005165f0::*g_rhgameWidgetToggleSelect)(char) = &RHUnk005165f0::FUN_005169f0;
RHGameWidgetEvent *(RHUnk005165f0::*g_rhgameWidgetToggleInput)(const RHGameWidgetInput &) = &RHUnk005165f0::FUN_005167b0;
void (RHUnk00516b50::*g_rhgameWidgetTitbitRender)() = &RHUnk00516b50::FUN_00516ac0;
RHGameWidgetEvent *(RHUnk00516b50::*g_rhgameWidgetTitbitInput)(const RHGameWidgetInput &) = &RHUnk00516b50::FUN_00516ae0;
int (RHUnk00516b50::*g_rhgameWidgetTitbitInside)(const SBGeoPoint2D &) = &RHUnk00516b50::FUN_00516bb0;
int (RHUnk00516d20::*g_rhgameWidgetCustomInside)(const SBGeoPoint2D &) = &RHUnk00516d20::FUN_00516d80;
RHGameWidgetEvent *(RHUnk00516d20::*g_rhgameWidgetCustomInput)(const RHGameWidgetInput &) = &RHUnk00516d20::FUN_00516ed0;
RHGameWidgetEvent *(RHUnk00516d20::*g_rhgameWidgetCustomReset)(void *) = &RHUnk00516d20::FUN_00516f60;
RHGameWidgetEvent *(RHUnk00516d20::*g_rhgameWidgetAnimatedInput)(const RHGameWidgetInput &) = &RHUnk00516d20::FUN_00517130;

void EmitRHGameTree(RHUnk00514e10 *tree, RHUnk00514e10::Iterator *entry, const int &key)
{
    tree->FUN_00514e10(key);
    tree->FUN_00514e50();
    entry->FUN_005159d0();
}

// FUNCTION: GAME 0x0051d790
RHUnk0051d790::~RHUnk0051d790()
{
    FUN_005df300((RHUnk005d92c0Sub *)&m_b0);
    FUN_005df300((RHUnk005d92c0Sub *)&m_180);
    FUN_0051dd10(m_250);
    FUN_0051dd10(m_660);
}

class RHUnk0051dd10View
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual bool V30(void *widget) = 0;
    virtual bool V34(void *widget) = 0; // vtable+0x34
    virtual void V38(void *widget) = 0;
};

// FUNCTION: GAME 0x0051dd10
void RHUnk0051d790::FUN_0051dd10(RHGameLifetime005161a0 *widgets)
{
    for (int i = 0; i < 5; ++i)
        ((RHUnk0051dd10View *)this)->V34(&widgets[i]);
}

class SBFrameWnd
{
public:
    void FUN_0061ac80(const SBGeoPoint2D &position);
    void FUN_0061ad20(const SBGeoBoundingBox2D &bounds);
};

class RHUnkFXDraw
{
public:
    unsigned short FUN_005e56c0(unsigned long surface);
    unsigned short FUN_005e5750(unsigned long surface);
};

extern RHUnk005ef320 *g_unk0x6c11d0;
extern float g_unk0x006c0bb0[2];
extern wchar_t g_unk0x006c0b50[1];

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &offset);
};

class RHGameStatusWidgetView
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual bool V30(const std::wstring &resource, const SBGeoBoundingBox2D &bounds, int flags, int style) = 0;
};

class RHMapBox
{
public:
    RHMapBox(float left, float top, float right, float bottom);
    SBGeoPoint2D m_first;
    SBGeoPoint2D m_second;
    int m_10;
};

// FUNCTION: GAME 0x0051d8a0
bool RHUnk0051d790::FUN_0051d8a0()
{
    bool initialized;
    {
        std::wstring title(g_unk0x006c0b50);
        initialized = RHPortraitRootLifetime::FUN_0061a1e0((const RHMapTitleText &)title,
            RHMapBox(0.0f, 0.0f, 91.0f, 42.0f), 0);
    }
    if (initialized)
    {
        {
            std::wstring title(g_unk0x006c0b50);
            ((RHGameStatusWidgetView *)&m_b0)->V30(title,
                (const SBGeoBoundingBox2D &)RHMapBox(0.0f, 0.0f, 91.0f, 24.0f), 0, 0xda);
        }
        {
            std::wstring title(g_unk0x006c0b50);
            ((RHGameStatusWidgetView *)&m_180)->V30(title,
                (const SBGeoBoundingBox2D &)RHMapBox(0.0f, 0.0f, 91.0f, 42.0f), 0, 0xdb);
        }
        ((RHUnk0051dd10View *)this)->V30(&m_b0);
        ((RHUnk0051dd10View *)this)->V30(&m_180);
        FUN_0051dba0(m_250, SBGeoPoint2D(5.0f, 5.0f), 0xd9);
        FUN_0051dba0(m_660, SBGeoPoint2D(5.0f, 22.0f), 0xd8);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x0051dba0
void RHUnk0051d790::FUN_0051dba0(RHGameLifetime005161a0 *widgets, const SBGeoPoint2D &position, int style)
{
    SBGeoBoundingBox2D bounds(position, position);
    int remaining = 5;
    do
    {
        {
            std::wstring resource(g_unk0x006c0b50);
            ((RHGameStatusWidgetView *)widgets)->V30(resource, bounds, 0, style);
        }
        ((RHUnk0051dd10View *)this)->V30(widgets);
        ((RHUnk0051dd10View *)this)->V38(widgets);
        ((RHMobileUnk006091b0 *)&bounds)->FUN_006091b0(SBGeoVector2D(16.0f, 0.0f));
        ++widgets;
    } while (--remaining);
}

// FUNCTION: GAME 0x0051dd40
void RHUnk0051d790::FUN_0051dd40(const SBGeoPoint2D &position)
{
    ((SBFrameWnd *)this)->FUN_0061ac80(position.Unk005fc190(*(SBGeoPoint2D *)g_unk0x006c0bb0));
}

inline float RHGameBoundsRight(const SBGeoBoundingBox2D &bounds)
{
    return bounds.m_second.m_x;
}

inline float RHGameBoundsBottom(const SBGeoBoundingBox2D &bounds)
{
    return bounds.m_second.m_y;
}

// FUNCTION: GAME 0x0051ddb0
void RHUnk0051d790::FUN_0051ddb0(const SBGeoBoundingBox2D &bounds)
{
    RHUnkFXDraw *draw = (RHUnkFXDraw *)g_unk0x6c11d0;
    SBGeoVector2D offset;
    if (RHGameBoundsRight(bounds) > draw->FUN_005e56c0(0))
        offset.m_x = draw->FUN_005e56c0(0) - RHGameBoundsRight(bounds);
    else
        offset.m_x = 0.0f;
    if (RHGameBoundsBottom(bounds) > draw->FUN_005e5750(0))
        offset.m_y = draw->FUN_005e5750(0) - RHGameBoundsBottom(bounds);
    else
        offset.m_y = 0.0f;
    ((SBFrameWnd *)this)->FUN_0061ad20(bounds.FUN_006090d0(offset));
}

void EmitRHHumanStatusBounds(RHUnk0051d790 *status, const SBGeoBoundingBox2D &bounds)
{
    status->FUN_0051d8a0();
    status->FUN_0051dba0(status->m_250, bounds.m_first, 0);
    status->FUN_0051dd40(bounds.m_first);
    status->FUN_0051ddb0(bounds);
}

// FUNCTION: GAME 0x0051df00
void RHGameWidgetCalls::FUN_0051df00(void *actor)
{
    unsigned first = 0;
    unsigned second = 0;
    bool enabled = false;
    bool available = false;
    if (actor)
    {
        void *status = *(void **)((char *)actor + 0x600);
        first = *(unsigned *)((char *)status + 8);
        available = true;
        if (((RHUnk0049d4f0 *)actor)->Unk(1))
        {
            enabled = true;
            second = *(unsigned *)((char *)status + 0x10);
        }
    }
    FUN_0051dfa0(available, enabled);
    FUN_0051e020((char *)this + 0x250, first, !available);
    FUN_0051e020((char *)this + 0x660, second, !enabled);
}

// FUNCTION: GAME 0x0051dfa0
void RHGameWidgetCalls::FUN_0051dfa0(bool first, bool second)
{
    RHGameWidgetVisibilityCalls *owner = (RHGameWidgetVisibilityCalls *)this;
    if (first)
    {
        if (second)
        {
            owner->V38((char *)this + 0xb0);
            owner->V3c((char *)this + 0x180);
        }
        else
        {
            owner->V3c((char *)this + 0xb0);
            owner->V38((char *)this + 0x180);
        }
    }
    else
    {
        owner->V38((char *)this + 0xb0);
        owner->V38((char *)this + 0x180);
    }
}

// FUNCTION: GAME 0x0051e020
void RHGameWidgetCalls::FUN_0051e020(void *widgets, unsigned value, bool empty)
{
    unsigned short count = empty ? 0 : value / 20 + 1;
    char *widget = (char *)widgets;
    for (unsigned index = 0; index != 5; ++index, widget += 0xd0)
    {
        if (index < count)
            ((RHGameWidgetVisibilityCalls *)this)->V3c(widget);
        else
            ((RHGameWidgetVisibilityCalls *)this)->V38(widget);
    }
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

// LIBRARY: GAME 0x00533c10
// ??_G?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QAEPAXI@Z

// FUNCTION: GAME 0x00535950
void RHGameMenuCalls::FUN_00535950(int first, int second, int third)
{
    *((char *)this + 0x344) = (char)first;
    *((char *)this + 0x144) = (char)second;
    *((char *)this + 0x244) = (char)third;
}

class RHUnk005364f0
{
public:
    void FUN_005364f0(int value);
};

// FUNCTION: GAME 0x005364f0
void RHUnk005364f0::FUN_005364f0(int value)
{
    *(int *)((char *)this + 0xbc) = value;
}

void EmitRHUnk005364f0(RHUnk005364f0 *a)
{
    a->FUN_005364f0(0);
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

// FUNCTION: GAME 0x006134a0
bool RHUnk006114c0::FUN_006134a0(void *configuration)
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
    ((SBGeoVector2D *)((char *)this + 0x28))->operator=(
        *(SBGeoVector2D *)((char *)configuration + 0x28));
    *(void **)((char *)this + 0x14) = ::operator new(*(unsigned *)((char *)this + 0x1c));
    memcpy(*(void **)((char *)this + 0x14), *(void **)((char *)configuration + 0x14),
        *(unsigned *)((char *)this + 0x1c));
    return true;
}

DECOMP_SIZE_ASSERT(RHMapDescription, 0x1c)
DECOMP_SIZE_ASSERT(RHMapDescription::Entry, 0x48)
DECOMP_SIZE_ASSERT(RHUnk0063c8b0, 0x18)

// FUNCTION: GAME 0x0063c7c0
RHMapDescription::RHMapDescription()
{
    // STRING: GAME 0x006beeb0
    m_14 = "RHLevel";
    // STRING: GAME 0x006beea8
    m_18 = ".red";
    m_00 = 0x67bbd4;
}

extern const unsigned g_unk0x0067bbd8;

class RHUnk0063c840
{
public:
    RHUnk0063c840();
    unsigned m_0;
    unsigned m_4;
};

// FUNCTION: GAME 0x0063c840
RHUnk0063c840::RHUnk0063c840()
{
    m_0 = g_unk0x0067bbd8;
    m_4 = g_unk0x0067bbd8;
}

class RHUnk0063c860
{
public:
    RHUnk0063c860();
    unsigned m_0;
    unsigned m_4;
};

// FUNCTION: GAME 0x0063c860
RHUnk0063c860::RHUnk0063c860()
{
    m_0 = 0;
    m_4 = g_unk0x0067bbd8;
}

class RHUnk0063c880
{
public:
    RHUnk0063c880();
    unsigned m_0;
    unsigned m_4;
    unsigned m_8;
    unsigned m_c;
};

// FUNCTION: GAME 0x0063c880
RHUnk0063c880::RHUnk0063c880()
{
    m_0 = 0;
    m_4 = g_unk0x0067bbd8;
    m_8 = 0;
    m_c = g_unk0x0067bbd8;
}

// FUNCTION: GAME 0x0063c8b0
RHUnk0063c8b0::RHUnk0063c8b0() : m_0(g_unk0x0067bbd8), m_4(g_unk0x0067bbd8)
{
}

// Parked: vector clear still calls the out-of-line Entry destructor instead of expanding nested cleanup.
// STUB: GAME 0x0063c8e0
RHMapDescription::~RHMapDescription()
{
    m_00 = 0x67bbd4;
    m_04.clear();
}

// Parked: lookup keeps last in EDI instead of EBX and lacks the target's short-lived EDI index.
// STUB: GAME 0x0063c9e0
RHMapDescription::Entry *RHMapDescription::FUN_0063c9e0(unsigned id)
{
    Entry *begin = ((Entry *volatile *)&m_04)[1];
    unsigned count = begin == 0 ? 0 : ((Entry *volatile *)&m_04)[2] - begin;
    if (count != 0)
    {
        Entry *last = m_04.end();
        if (id <= last[-1].m_44)
        {
            Entry *first = m_04.begin();
            if (id >= first->m_44)
            {
                unsigned index = id;
                if (index >= count)
                    index = count - 1;
                Entry *entry = first + index;
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

#pragma inline_depth(0)
void EmitRHMapRecordDestructors(RHMapDescription::Entry *entry, RHUnk0063c8b0 *record)
{
    entry->~Entry();
    record->~RHUnk0063c8b0();
}
#pragma inline_depth(8)

void RHGame::Emit(SBFile &file)
{
    FUN_00513390(0);
    FUN_00512be0(0);
    FUN_00512cb0(0);
    FUN_00513df0(0);
    GenerateDeadZoneForMouseInput();
    FUN_0050f2d0(false);
    SerializeForSherwood();
    FUN_005145b0();
    FUN_0050e860();
    FUN_00514c50();
    (*(SBThreadedInput **)((char *)this + 0x0c))->FUN_005104b0();
    FUN_005104c0();
    ((RHGameActionCalls *)((char *)this + 0x68))->FUN_00510550(SBGeoVector2D(*(SBGeoPoint2D *)FUN_005104c0()));
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
