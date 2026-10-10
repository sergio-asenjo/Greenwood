#include "RHMenuCampaignMap.h"
#include <windows.h>
#include <stdio.h>

#define DECOMP_SIZE_ASSERT(T, S) namespace { typedef int T##_size_assert[(sizeof(T) == S) ? 1 : -1]; }
DECOMP_SIZE_ASSERT(RHMapWideText, 0x10)
DECOMP_SIZE_ASSERT(RHMapTitleText, 0x10)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(RHMapBox, 0x14)
DECOMP_SIZE_ASSERT(RHMapWidget, 0xcc)
DECOMP_SIZE_ASSERT(RHMapLocation, 0x27c)
DECOMP_SIZE_ASSERT(RHMapCampaign, 0x1b0)
DECOMP_SIZE_ASSERT(RHMapWindow, 0x1990)
DECOMP_SIZE_ASSERT(RHMapDescription, 0x1c)
DECOMP_SIZE_ASSERT(RHMenuCampaignMap, 0x2704)

// deferred: unannotated pending reccmp #534; proven 100.00% when annotated.
void RHMapWideText::Tidy(bool built)
{
    if (built && m_chars != 0)
    {
        unsigned char &references = *((unsigned char *)m_chars - 1);
        if (references == 0 || references == 255)
            operator delete(m_chars - 1);
        else
            --references;
    }
    m_chars = 0;
    m_size = 0;
    m_capacity = 0;
}

// FUNCTION: GAME 0x004577a0
unsigned RHMapCampaign::FUN_004577a0()
{
    return m_1a8;
}

// FUNCTION: GAME 0x004577b0
void RHMapCampaign::FUN_004577b0()
{
    m_1a8 = 0;
}

// TEMPLATE: GAME 0x00525430
// ?append@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QAEAAV12@PBGI@Z

// FUNCTION: GAME 0x00527a70
void RHMenuCampaignMap::FUN_00527a70(RHMapByte state)
{
    if (state.value != -1)
    {
        unsigned i = 0;
        int selected = state.value;
        RHMapWidget *arrow = (RHMapWidget *)((char *)this + 0x1a74);
        for (; i < 10; ++i, ++arrow)
        {
            if (selected == i)
            {
                void *mission = ((RHMapLocation *)((char *)this + 0x19c))[FUN_00527cc0(i)].m_278;
                if (mission)
                {
                    unsigned type = *(unsigned *)((char *)*(void **)mission + 0x34);
                    if (type == 5 || type == 1)
                        V3c(arrow);
                }
            }
            else
                V38(arrow);
        }
    }
}

// FUNCTION: GAME 0x00527ae0
void RHMenuCampaignMap::FUN_00527ae0(RHMapByte state)
{
    bool accessible[5] = {false, false, false, false, false};
    unsigned locations[5] = {5, 6, 4, 9, 7};
    switch (state.value)
    {
    case 1: case 2: accessible[0] = true; break;
    case 3: case 4: accessible[0] = true; accessible[1] = true; break;
    case 5: case 6: accessible[0] = true; accessible[1] = true; accessible[2] = true; break;
    case 7: case 8: accessible[0] = true; accessible[1] = true; accessible[2] = true; accessible[3] = true; break;
    case 9: accessible[0] = true; accessible[1] = true; accessible[2] = true; accessible[3] = true; accessible[4] = true; break;
    }
    unsigned i = 0;
    unsigned *location = locations;
    for (; i != 5; ++i, ++location)
    {
        bool enabled = accessible[i];
        unsigned index = *location;
        if (enabled)
            V3c((char *)this + (index + 1) * 0x27c);
        else
            V38((char *)this + (index + 1) * 0x27c);
    }
}

class RHMapMission
{
public:
    bool FUN_0054cc20();
    void *m_00; // 0x00
    unsigned short m_04; // 0x04
};

// STUB: GAME 0x00527c00
void RHMenuCampaignMap::FUN_00527c00(const std::vector<void *> &missions)
{
    for (std::vector<void *>::const_iterator it = missions.begin(); it != missions.end(); ++it)
    {
        RHMapMission *mission = (RHMapMission *)*it;
        unsigned locationIndex = *(unsigned *)((char *)mission->m_00 + 0x3c);
        char *base = (char *)this + locationIndex * 0x27c;
        RHMapLocation *location = (RHMapLocation *)(base + 0x19c);
        ((RHMapWidget *)location)->V54(true);
        unsigned count = *(unsigned short *)((char *)mission->m_00 + 0x4c);
        *(unsigned *)((char *)location + 0xd4) = 1000;
        *((bool *)location + 0xcc) = mission->m_04 == count - 1;
        if (mission->FUN_0054cc20())
        {
            V3c(base + 0x348);
            *(bool *)(base + 0x34c) = true;
        }
        else
        {
            V38(base + 0x348);
            *(bool *)(base + 0x34c) = false;
        }
        *(void **)(base + 0x414) = mission;
    }
}

// Parked: 99.19%, two this-register scheduling differences.
// STUB: GAME 0x00527d20
bool RHMenuCampaignMap::Create()
{
    bool created;
    {
        // STRING: GAME 0x006b09fc
        RHMapTitleText title(L"Campaign Map");
        created = FUN_00544b40(title, RHMapBox(0.0f, 0.0f, 629.0f, 480.0f), 0);
    }
    if (created)
    {
        RHMapCampaign *campaign = (RHMapCampaign *)g_unk0x6c07fc;
        RHMapWidget *arrow = (RHMapWidget *)((char *)this + 0x1a74);
        for (unsigned count = 10; count != 0; --count, ++arrow)
            V30(arrow);
        RHMapLocation *locations = (RHMapLocation *)((char *)this + 0x19c);
        for (unsigned i = 0; i < 10; ++i)
        {
            if (i != 8 && i != 0)
            {
                RHMapWidget *flag = &locations[i].m_e0;
                V30((char *)flag - 0xe0);
                V30(&locations[i].m_1ac);
                if (i != 1 && i != 2 && i != 3)
                    V30(flag);
                V38(&locations[i].m_1ac);
                locations[i].m_1ac.m_04[0] = 0;
            }
        }
        FUN_005284b0();
        FUN_00527c00(campaign->FUN_00528050());
        FUN_00527a70(campaign->UnkState());
        FUN_00527ae0(campaign->UnkState());
        if (campaign->FUN_00528050().size() == 0)
        {
            {
                // STRING: GAME 0x006b09f4
                std::wstring ok(L"OK");
                ((RHMapWidget *)((char *)this + 0xcc))->V30(ok, RHMapBox(574.0f, 5.0f, 595.0f, 26.0f), 0, 0x7c);
            }
            V30((char *)this + 0xcc);
            SBAssert(0,
                     // STRING: GAME 0x006b099c
                     "P:\\Robin Hood\\RHMenuCampaignMap.cpp", 0x1a6,
                     // STRING: GAME 0x006b09c0
                     "Campaign map : warning no missions are accessible.");
        }
        V30((char *)this + 0x25ec);
        FUN_00528810();
        DisplayPseudoMissionDebriefing();
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x00528050
std::vector<void *> RHMapCampaign::FUN_00528050()
{
    return m_154;
}

// FUNCTION: GAME 0x005280d0
void RHMenuCampaignMap::DisplayPseudoMissionDebriefing()
{
    RHMapCampaign *campaign = (RHMapCampaign *)g_unk0x6c07fc;
    if (campaign->FUN_004577a0() != 0)
    {
        if (m_2700 != unsigned(-1))
        {
            RHMapWideText message;
            *((char *)this + 0x5d) = 1;
            (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053bb30(m_2700);
            m_2700 = unsigned(-1);
            bool won = campaign->FUN_004577a0() == 1;
            RHMapDescription description;
            char directory[0x104];
            GetCurrentDirectoryA(0x104, directory);
            const char *directoryChars = g_unk0x006c0664;
            SetCurrentDirectoryA(directoryChars ? directoryChars : "");
            unsigned mission = campaign->m_1ac;
            if (!description.FUN_0063cda0(mission))
                SBAssert(0,
                         // STRING: GAME 0x006b0948
                         "P:\\Robin Hood\\RHMenuCampaignMap.cpp", 0x1ec,
                         // STRING: GAME 0x006afa88
                         "Warning: unable to load the resource description for the mission '%s'\n", &mission);
            SetCurrentDirectoryA(directory);
            RHMapDescription::Entry *entry = description.FUN_0063c9e0(mission);
            unsigned resource = won ? entry->m_30 : entry->m_38;
            RHMapResources *resources = g_unk0x006c1840;
            if (!resources->FUN_00600fc0(resource) || !resources->FUN_006009e0(resource, 0, message))
            {
                if (won)
                    (std::wstring &)message = FUN_005e23d0(0x104);
                else
                    (std::wstring &)message = FUN_005e23d0(0x103);
            }
            FUN_00529e60(*(RHMapWindow **)((char *)this + 0xb4), message, won, 0);
            (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053c7e0();
            campaign->FUN_004577b0();
            if (campaign->m_100.value == 0)
                (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053bbe0();
        }
        else
        {
            *((char *)this + 0x5d) = 0;
            m_2700 = (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053baa0(0x1f4);
        }
    }
}

// STUB: GAME 0x005284b0
void RHMenuCampaignMap::FUN_005284b0()
{
    unsigned zero = 0;
    char *location = (char *)this + 0x19c;
    for (unsigned count = 10; count != 0; --count, location += 0x27c)
    {
        ((RHMapWidget *)location)->V54(zero);
        V38(location + 0xe0);
        V38(location + 0x1ac);
        *(undefined *)(location + 0x1b0) = zero;
        *(undefined4 *)(location + 0x278) = zero;
    }
    RHMapWidget *arrow = (RHMapWidget *)((char *)this + 0x1a74);
    for (unsigned arrows = 10; arrows != 0; --arrows, ++arrow)
        V38(arrow);
}

// STUB: GAME 0x00528810
void RHMenuCampaignMap::FUN_00528810()
{
    unsigned converted = g_unk0x6c07fc->Get(4);
    unsigned remaining = g_unk0x6c07fc->Get(5);
    unsigned percentage = 0;
    if (converted != 0 || remaining != 0)
        percentage = converted * 100 / (converted + remaining);
    unsigned short money[0x100];
    unsigned short message[0x100];
    swprintf(money, FUN_005e23d0(0xf4).c_str(), g_unk0x6c07fc->Get(1));
    swprintf(message,
             // STRING: GAME 0x006b0a18
             L"%s -  %s : %d  -  %s : %d%%", money,
             FUN_005e23d0(0x40).c_str(), g_unk0x6c07fc->Get(2),
             FUN_005e23d0(0xf3).c_str(), percentage);
    RHMapTitleText text(message);
    ((RHMapWidget *)((char *)this + 0x25ec))->V2c(text);
}

// FUNCTION: GAME 0x0053baa0
unsigned RHMapWindow::FUN_0053baa0(unsigned duration)
{
    Timer timer = {m_198c, duration, GetTickCount()};
    m_1980.push_back(timer);
    return m_198c++;
}

// FUNCTION: GAME 0x0053bb30
void RHMapWindow::FUN_0053bb30(unsigned timer)
{
    for (std::list<Timer>::iterator it = m_1980.begin(); it != m_1980.end(); ++it)
    {
        if (it->m_00 == timer)
        {
            m_1980.erase(it);
            break;
        }
    }
}

// STUB: GAME 0x0053bbe0
void RHMapWindow::FUN_0053bbe0()
{
    while (!m_191c.empty())
    {
        std::vector<void *> &widgets = m_191c.back();
        for (std::vector<void *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
            ((RHMapWindowPart *)((char *)this + 0x10))->FUN_00619ad0(*it);
        m_191c.pop_back();
    }
    *((bool *)this + 0x197c) = true;
}

// FUNCTION: GAME 0x0053c7e0
void RHMapWindow::FUN_0053c7e0()
{
    ((RHMapWindowPart *)((char *)this + 0x10))->FUN_00618850((char *)this + 0x1914);
}

// TEMPLATE: GAME 0x0053e170
// ?_Add@const_iterator@?$deque@V?$vector@PAXV?$allocator@PAX@std@@@std@@V?$allocator@V?$vector@PAXV?$allocator@PAX@std@@@std@@@2@@std@@IAEXH@Z

// FUNCTION: GAME 0x00544b40
bool RHMenuCampaignMap::FUN_00544b40(const RHMapTitleText &title, const RHMapBox &box, unsigned flags)
{
    return FUN_0061a1e0(title, box, flags);
}

// FUNCTION: GAME 0x00607c10
RHMapBox::RHMapBox(float x1, float y1, float x2, float y2)
    : m_0(x1, y1), m_8(x2, y2), m_10(true)
{
}

void RHMenuCampaignMap::Emit()
{
    Create();
    DisplayPseudoMissionDebriefing();
    RHMapCampaign *campaign = (RHMapCampaign *)g_unk0x6c07fc;
    campaign->FUN_004577a0();
    campaign->FUN_004577b0();
    RHMapWindow *window = *(RHMapWindow **)((char *)this + 0xb4);
    window->FUN_0053bb30(0);
    window->FUN_0053bbe0();
    window->FUN_0053c7e0();
}
