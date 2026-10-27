#include "SBNullstr.h"
#include "RHMenuCampaignMap.h"
#include "RHPortraitRootLifetime.h"
#include "RHMenuScreenView.h"
#include "RHUnk00527870.h"
#include "RHGameInputTranslator.h"
#include "SBUIBase.h"
#include "RHMission.h"
#include "RHCampaignCore.h"
#include "RHCampaignCommandLine.h"
#include "RHFontManager.h"
#include "RHGameMenuCalls.h"
#define SBGEO_POINT2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#include "RHMenuCloseCalls.h"
#include <windows.h>
#include <stdio.h>
#include <stddef.h>
#include "RHShortMissionUpdateCalls.h"

#include "RHMenuWindowClass.h"
#include "RHUnk00528400.h"
#include "RHMenuMissionDescription.h"
#include "RHUnk0053bf20.h"

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

// unannotated: 0x004238c0 is std::wstring::_Tidy (std-only); binding this view regresses its std callers.
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

// LIBRARY: GAME 0x00525430
// ?append@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QAEAAV12@PBGI@Z

// FUNCTION: GAME 0x00525a00
void RHMenuCampaignMap::RouteEvent(RHMenuEvent *event)
{
    if (HandleEvent(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x00525a20
bool RHMenuCampaignMap::HandleEvent(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0xcc)
        handled = ((RHMenuCloseCalls *)this)->FUN_0052b520(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x418)
        handled = FUN_00528560(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x694)
        handled = FUN_00528560(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x910)
        handled = FUN_00528560(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0xb8c)
        handled = FUN_00528560(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0xe08)
        handled = FUN_00528560(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x1084)
        handled = FUN_00528560(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x1300)
        handled = FUN_00528560(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x17f8)
        handled = FUN_00528560(2, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0x418)
        handled = FUN_005287d0(0, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0x694)
        handled = FUN_005287d0(0, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0x910)
        handled = FUN_005287d0(0, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0xb8c)
        handled = FUN_005287d0(0, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0xe08)
        handled = FUN_005287d0(0, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0x1084)
        handled = FUN_005287d0(0, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0x1300)
        handled = FUN_005287d0(0, event->m_widget, event->m_data);
    if (event->m_type == 0 && event->m_widget == (char *)this + 0x17f8)
        handled = FUN_005287d0(0, event->m_widget, event->m_data);
    if (event->m_type == 1 && event->m_widget == (char *)this + 0x418)
        handled = FUN_00528730(1, event->m_widget, event->m_data);
    if (event->m_type == 1 && event->m_widget == (char *)this + 0x694)
        handled = FUN_00528730(1, event->m_widget, event->m_data);
    if (event->m_type == 1 && event->m_widget == (char *)this + 0x910)
        handled = FUN_00528730(1, event->m_widget, event->m_data);
    if (event->m_type == 1 && event->m_widget == (char *)this + 0xb8c)
        handled = FUN_00528730(1, event->m_widget, event->m_data);
    if (event->m_type == 1 && event->m_widget == (char *)this + 0xe08)
        handled = FUN_00528730(1, event->m_widget, event->m_data);
    if (event->m_type == 1 && event->m_widget == (char *)this + 0x1084)
        handled = FUN_00528730(1, event->m_widget, event->m_data);
    if (event->m_type == 1 && event->m_widget == (char *)this + 0x1300)
        handled = FUN_00528730(1, event->m_widget, event->m_data);
    if (event->m_type == 1 && event->m_widget == (char *)this + 0x17f8)
        handled = FUN_00528730(1, event->m_widget, event->m_data);
    if (event->m_type == 0x1000 && event->m_widget == *(void **)((char *)this + 0x26fc))
        handled = FUN_00528520(0x1000, (unsigned)event->m_widget, (unsigned)event->m_data);
    if (event->m_type == 0x1000 && event->m_widget == *(void **)((char *)this + 0x2700))
        handled = FUN_00528550(0x1000, (unsigned)event->m_widget, (unsigned)event->m_data);
    return handled;
}

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

// FUNCTION: GAME 0x00527c00
void RHMenuCampaignMap::FUN_00527c00(const std::vector<void *> &missions)
{
    for (std::vector<void *>::const_iterator it = missions.begin(); it != missions.end(); ++it)
    {
        RHMission *mission = (RHMission *)*it;
        unsigned locationIndex = *(unsigned *)((char *)mission->m_profile + 0x3c);
        char *base = (char *)this + locationIndex * 0x27c;
        RHMapLocation *location = (RHMapLocation *)(base + 0x19c);
        ((RHMapWidget *)location)->V54(true);
        unsigned count = *(unsigned short *)((char *)mission->m_profile + 0x4c);
        *((bool *)location + 0xcc) = (unsigned short)mission->m_4 == count - 1;
        *(unsigned *)((char *)location + 0xd4) = 1000;
        if ((char)mission->FUN_0054cc20())
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
        created = ((RHMenuWindow *)this)->FUN_00544b40(*(const std::wstring *)&title, RHMapBox(0.0f, 0.0f, 629.0f, 480.0f), 0);
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

#define m_locations ((RHMapLocation *)((char *)this + 0x19c))

// FUNCTION: GAME 0x005284b0
void RHMenuCampaignMap::FUN_005284b0()
{
    for (unsigned i = 0; i < 10; ++i)
    {
        ((RHMapWidget *)&m_locations[i])->V54(false);
        V38(&m_locations[i].m_e0);
        V38(&m_locations[i].m_1ac);
        m_locations[i].m_1ac.m_04[0] = 0;
        m_locations[i].m_278 = 0;
    }
    RHMapWidget *arrow = (RHMapWidget *)((char *)this + 0x1a74);
    for (unsigned count = 10; count != 0; --count, ++arrow)
        V38(arrow);
}
#undef m_locations

// FUNCTION: GAME 0x00528520
bool RHMenuCampaignMap::FUN_00528520(unsigned, unsigned, unsigned)
{
    (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053bb30(*(unsigned long *)((char *)this + 0x26fc));
    *(unsigned long *)((char *)this + 0x26fc) = unsigned(-1);
    FUN_00528810();
    return false;
}

// FUNCTION: GAME 0x00528550
bool RHMenuCampaignMap::FUN_00528550(unsigned, unsigned, unsigned)
{
    DisplayPseudoMissionDebriefing();
    return false;
}

// FUNCTION: GAME 0x005286b0
std::vector<void *> RHMapCampaign::FUN_005286b0()
{
    return *(std::vector<void *> *)((char *)this + 0x164);
}

// FUNCTION: GAME 0x00528560
bool RHMenuCampaignMap::FUN_00528560(int, void *widget, void *)
{
    RHMapLocation *location = (RHMapLocation *)((RHUnk00528400 *)this)->FUN_00528480((RHUnk00528410 *)widget);
    RHMenuMissionDescription description((RHMenuWindow *)this,
        *(RHMenuWindowScreen **)((char *)this + 0xb4), (RHMission *)location->m_278);
    ((RHGameMenuCalls *)((char *)this + 0x226c))->FUN_00544b30();
    unsigned long previous = (unsigned long)(*(RHUnk0053bf20 **)((char *)this + 0xb4))->FUN_0053bf20();
    (*(RHMenuScreenView **)((char *)this + 0xb4))->FUN_0053be40(0);
    description.Create();
    description.FUN_00544b80(true, true);
    (*(RHMenuScreenView **)((char *)this + 0xb4))->FUN_0053be40(previous);
    switch (description.GetUserChoice())
    {
    case 1:
        FUN_00527c00(((RHMapCampaign *)g_unk0x6c07fc)->FUN_005286b0());
        ((RHCampaign *)g_unk0x6c07fc)->FUN_004562a0();
        break;
    case 0:
        ((RHGameMenuCalls *)this)->FUN_00544b30();
        break;
    }
    FUN_00528810();
    DisplayPseudoMissionDebriefing();
    description.FUN_00544300();
    (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053c7e0();
    return true;
}

// FUNCTION: GAME 0x00528730
bool RHMenuCampaignMap::FUN_00528730(int, void *, void *)
{
    RHMapWidget *description = (RHMapWidget *)((char *)this + 0x226c);
    RHMenuScreenView *screen = *(RHMenuScreenView **)((char *)this + 0xb4);
    if (screen->FUN_0053c320(description))
    {
        SBGeoBoundingBox2D bounds(description->V24());
        ((RHGameMenuCalls *)description)->FUN_00544b30();
        (*(RHMenuScreenView **)((char *)this + 0xb4))->FUN_0053c7f0((unsigned long)&bounds);
    }
    return true;
}

// FUNCTION: GAME 0x005287d0
bool RHMenuCampaignMap::FUN_005287d0(int, void *widget, void *)
{
    RHMapLocation *location = (RHMapLocation *)((RHUnk00528400 *)this)->FUN_00528480((RHUnk00528410 *)widget);
    RHShortMissionUpdateCalls *description = (RHShortMissionUpdateCalls *)((char *)this + 0x226c);
    description->FUN_00540ed0((RHMission *)location->m_278);
    ((RHMenuWindow *)description)->FUN_00544b80(false, false);
    return true;
}

// FUNCTION: GAME 0x00528810
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
    ((RHMapWidget *)((char *)this + 0x25ec))->V2c((const RHMapTitleText &)std::wstring(message));
}

class RHMapFocusWidget
{
public:
    void FUN_00541060();
};

// FUNCTION: GAME 0x00528a60
void RHMenuCampaignMap::FUN_00528a60()
{
    RHMapFocusWidget *widget = (RHMapFocusWidget *)((char *)this + 0x226c);
    if ((*(RHMenuScreenView **)((char *)this + 0xb4))->FUN_0053c320(widget))
        widget->FUN_00541060();
}

// SYNTHETIC: GAME 0x00528a80
// ??0RHGameLifetime00515f00@@QAE@XZ

class SBUIUnk0060d530
{
public:
    void *FUN_0060d690();
};

class SBUIUnk0060da20
{
public:
    bool FUN_0060da20(unsigned);
};

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &);
};

template<class T>
static T &RHMapWidgetField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

class RHMapBlinkParent
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
};

struct RHMapCachedEvent
{
    unsigned char m_prefix[0x5c];
    unsigned m_type;
    unsigned m_bounds[5];
    void *m_widget;
    void *m_next;
};

class RHUnk00528ad0
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
    virtual unsigned V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30();
    virtual unsigned V34(unsigned);
    unsigned *FUN_00528ad0(unsigned index);
    void FUN_00528b70();
    void FUN_00528bb0();
    unsigned FUN_00528be0();
    unsigned *MakeEvent(unsigned index)
    {
        RHMapWidgetField<unsigned>(this, 0xc8) = index;
        ((RHMobileUnk00607da0 *)((char *)this + 0x60))->FUN_00607da0(
            *(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)((char *)this + 0x80))->FUN_0060d690());
        RHMapCachedEvent *event = (RHMapCachedEvent *)this;
        event->m_type = V34(V24());
        event->m_next = 0;
        event->m_widget = this;
        return &event->m_type;
    }
};

class SBUIUnk0060dd00
{
public:
    int FUN_0060dc20(unsigned id);
};

class RHUnk005254f0
{
public:
    void FUN_005254f0();
    unsigned FUN_00525510(unsigned id);
    void FUN_005255c0(const std::wstring &text);
    unsigned *FUN_005257c0(unsigned index);
    unsigned *FUN_00525830(unsigned index);
    void FUN_00525840();
};

// FUNCTION: GAME 0x005254f0
void RHUnk005254f0::FUN_005254f0()
{
    ((RHPopupRenderer0060dbc0 *)((char *)this + 0x80))->FUN_0060dd10(
        ((RHUnk00528ad0 *)this)->V24());
}

// FUNCTION: GAME 0x00525510
unsigned RHUnk005254f0::FUN_00525510(unsigned id)
{
    SBUIUnk0060dd00 *renderer = (SBUIUnk0060dd00 *)((char *)this + 0x80);
    unsigned previous = ((unsigned *)((char *)renderer + 0x40))[
        RHMapWidgetField<unsigned>(renderer, 0x48) & 1];
    unsigned current = id == 255 ? 0 : renderer->FUN_0060dc20(id);
    if (current == (unsigned)-1)
        return 3;
    if (previous != current)
        return current == 0 ? 2 : 1;
    return 0;
}

// Parked: nested string assignment inlines cleanup and self-assignment erasure at different depths.
// STUB: GAME 0x005255c0
void RHUnk005254f0::FUN_005255c0(const std::wstring &text)
{
    RHMapWidgetField<bool>(this, 0xfc) = true;
    RHMapWidgetField<bool>(this, 0xfd) = true;
    RHMapWidgetField<std::wstring>(this, 0x10) = text;
    RHMapWidgetField<std::wstring>(this, 0xa8) = text;
}

// FUNCTION: GAME 0x005257c0
unsigned *RHUnk005254f0::FUN_005257c0(unsigned index)
{
    bool &dirty = RHMapWidgetField<bool>(this, 0xfc + (index & 1));
    if (dirty == true)
    {
        dirty = false;
        return ((RHUnk00528ad0 *)this)->MakeEvent(index);
    }
    return 0;
}

// FUNCTION: GAME 0x00525830
unsigned *RHUnk005254f0::FUN_00525830(unsigned index)
{
    return 0;
}

// FUNCTION: GAME 0x00525840
void RHUnk005254f0::FUN_00525840()
{
    RHMapWidgetField<bool>(this, 0xfc) = true;
    RHMapWidgetField<bool>(this, 0xfd) = true;
    RHMapWidgetField<unsigned>(this, 0xc0) = -1;
    RHMapWidgetField<unsigned>(this, 0xc4) = -1;
}

// SYNTHETIC: GAME 0x00525560
// ??1RHGameLifetime00525560@@QAE@XZ

#pragma inline_depth(1)
// FUNCTION: GAME 0x00525860
void *RHGameLifetime00525880::FUN_00525860(unsigned flags)
{
    this->~RHGameLifetime00525880();
    if (flags & 1)
        operator delete(this);
    return this;
}

// SYNTHETIC: GAME 0x00525880
// ??1RHGameLifetime00525880@@QAE@XZ

// FUNCTION: GAME 0x005258e0
void *RHGameLifetime00525560::FUN_005258e0(unsigned flags)
{
    this->~RHGameLifetime00525560();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma inline_depth()

#include "RHGameTitleLifetimeInline.h"

#pragma inline_depth(0)
void EmitRHGameTitleLifetime()
{
    RHGameLifetime00525880 title;
}
#pragma inline_depth()

void RHMapTailEmit(void *object, unsigned index, const std::wstring &text)
{
    RHUnk005254f0 *widget = (RHUnk005254f0 *)object;
    widget->FUN_005254f0();
    widget->FUN_00525510(index);
    widget->FUN_005255c0(text);
    widget->FUN_005257c0(index);
    widget->FUN_00525830(index);
    widget->FUN_00525840();
    ((RHGameLifetime00525560 *)object)->FUN_00525860(0);
    ((RHGameLifetime00525560 *)object)->FUN_005258e0(0);
}

// FUNCTION: GAME 0x00528ad0
unsigned *RHUnk00528ad0::FUN_00528ad0(unsigned index)
{
    if (RHMapWidgetField<bool>(this, 0xcc))
    {
        unsigned now = GetTickCount();
        if (now - RHMapWidgetField<unsigned>(this, 0xd0) >= RHMapWidgetField<unsigned>(this, 0xd4))
        {
            bool blinking = RHMapWidgetField<bool>(this, 0xcd);
            RHMapWidgetField<unsigned>(this, 0xd0) = now;
            RHMapWidgetField<bool>(this, 0xcd) = !blinking;
        }
    }
    unsigned *event = MakeEvent(index);
    if (event && *event)
    {
        RHMapBlinkParent *parent = RHMapWidgetField<RHMapBlinkParent *>(this, 0xd8);
        if (parent)
            parent->V10();
    }
    return event;
}

// FUNCTION: GAME 0x00528b70
void RHUnk00528ad0::FUN_00528b70()
{
    ((SBUIUnk0060da20 *)((char *)this + 0x80))->FUN_0060da20(V24());
    RHMapBlinkParent *parent = RHMapWidgetField<RHMapBlinkParent *>(this, 0xd8);
    if (parent && RHMapWidgetField<bool>(this, 0xdc) == true && RHMapWidgetField<bool>(parent, 4) == true)
        parent->V0c();
}

// FUNCTION: GAME 0x00528bb0
void RHUnk00528ad0::FUN_00528bb0()
{
    RHMapWidgetField<int>(this, 0xc0) = -1;
    RHMapWidgetField<int>(this, 0xc4) = -1;
    RHMapWidgetField<bool>(this, 0xdc) = true;
    RHMapBlinkParent *parent = RHMapWidgetField<RHMapBlinkParent *>(this, 0xd8);
    if (parent)
        parent->V10();
}

// FUNCTION: GAME 0x00528be0
unsigned RHUnk00528ad0::FUN_00528be0()
{
    if (RHMapWidgetField<bool>(this, 0xcc) == true &&
        RHMapWidgetField<bool>(this, 4) == true && RHMapWidgetField<int>(this, 0x7c) == 0)
    {
        unsigned result = (RHMapWidgetField<bool>(this, 0xcd) ? 1 : 0) + 1;
        V10();
        return result;
    }
    if (!RHMapWidgetField<bool>(this, 4))
        return 0;
    unsigned result;
    switch (RHMapWidgetField<unsigned>(this, 0x7c))
    {
    case 2:
    case 3:
        return 3;
    case 1:
        return 2;
    case 0:
        result = 1;
        break;
    }
    if (result == 1 && !RHMapWidgetField<bool>(this, 6))
        result = 255;
    return result;
}

// FUNCTION: GAME 0x005276d0
RHUnk005276d0::RHUnk005276d0()
{
}

// FUNCTION: GAME 0x005277b0
RHUnk005276d0::~RHUnk005276d0()
{
}

// SYNTHETIC: GAME 0x00527870
// ??1RHUnk00527870@@QAE@XZ

#pragma inline_depth(1)
// FUNCTION: GAME 0x00528c70
void *RHUnk00527870::FUN_00528c70(unsigned flags)
{
    this->~RHUnk00527870();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma inline_depth()

void EmitRHMapBlink(RHUnk00528ad0 *blink)
{
    blink->FUN_00528ad0(0);
    blink->FUN_00528b70();
    blink->FUN_00528bb0();
    blink->FUN_00528be0();
    ((RHUnk00527870 *)blink)->FUN_00528c70(0);
}

#include "RHUnk00641782.h"

struct RHMapTreeNode
{
    RHMapTreeNode *left;
    RHMapTreeNode *parent;
    RHMapTreeNode *right;
};

struct RHMapTreeIterator
{
    RHMapTreeNode *node;
};

class RHMapTree
{
public:
    void FUN_0053ad50();
    RHMapTreeIterator FUN_0053d2f0(RHMapTreeIterator first, RHMapTreeIterator last);
    undefined m_00[4];
    RHMapTreeNode *m_head;
    bool m_multi;
    undefined m_09[3];
    unsigned m_size;
};

// GLOBAL: GAME 0x006c0c24
unsigned g_unk0x006c0c24 = 0;

// GLOBAL: GAME 0x006c0c28
RHMapTreeNode *g_unk0x006c0c28 = 0;

struct RHMapStringNode
{
    RHMapStringNode *m_00;
    RHMapStringNode *m_04;
    RHMapStringNode *m_08;
    std::pair<const std::string, void *> m_0c;
    int m_20;
};

struct RHMapStringIterator
{
    RHMapStringNode *m_node;
};

void RHMapConstructValue(std::pair<const std::string, void *> *, const std::pair<const std::string, void *> &);

class RHMapStringTree
{
public:
    RHMapStringIterator FUN_0053dcb0(RHMapStringNode *, RHMapStringNode *, const std::pair<const std::string, void *> &);
    RHMapStringNode *FUN_0053dfc0(const std::string &);
    void *&FUN_0053cd30(const std::string &);
    static RHMapStringNode *&Left(RHMapStringNode *node) { return node->m_00; }
    inline void RotateLeft(RHMapStringNode *node)
    {
        RHUnk00641782 lock;
        RHMapStringNode *right = node->m_08;
        node->m_08 = right->m_00;
        if (right->m_00 != (RHMapStringNode *)g_unk0x006c0c28) right->m_00->m_04 = node;
        right->m_04 = node->m_04;
        if (node == m_head->m_04) m_head->m_04 = right;
        else if (node == node->m_04->m_00) node->m_04->m_00 = right;
        else node->m_04->m_08 = right;
        right->m_00 = node;
        node->m_04 = right;
    }
    inline void RotateRight(RHMapStringNode *node)
    {
        RHUnk00641782 lock;
        RHMapStringNode *left = node->m_00;
        node->m_00 = left->m_08;
        if (left->m_08 != (RHMapStringNode *)g_unk0x006c0c28) left->m_08->m_04 = node;
        left->m_04 = node->m_04;
        if (node == m_head->m_04) m_head->m_04 = left;
        else if (node == node->m_04->m_08) node->m_04->m_08 = left;
        else node->m_04->m_00 = left;
        left->m_08 = node;
        node->m_04 = left;
    }
    unsigned m_00;
    RHMapStringNode *m_head;
    unsigned m_08;
    unsigned m_count;
};

struct RHMapTreeDecNode
{
    RHMapTreeDecNode *m_00;
    RHMapTreeDecNode *m_04;
    RHMapTreeDecNode *m_08;
    int m_0c;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    int m_20;
};

static inline RHMapTreeDecNode *&RHMapTreeDecLeft(RHMapTreeDecNode *value) { return value->m_00; }

static inline RHMapTreeDecNode *RHMapTreeDecMax(RHMapTreeDecNode *node)
{
    RHUnk00641782 lock;
    while (node->m_08 != (RHMapTreeDecNode *)g_unk0x006c0c28)
        node = node->m_08;
    return node;
}

struct RHMapTreeDecIterator
{
    RHMapTreeDecNode *m_node;
    void FUN_0053e0b0();
};

static inline RHMapTreeDecNode *RHMapTreeMin(RHMapTreeDecNode *node)
{
    RHUnk00641782 lock;
    while (node->m_00 != (RHMapTreeDecNode *)g_unk0x006c0c28)
        node = node->m_00;
    return node;
}

struct RHMapTreeIncIterator
{
    RHMapTreeDecNode *m_node;
    void FUN_0053dbf0();
};

// FUNCTION: GAME 0x0053dbf0
void RHMapTreeIncIterator::FUN_0053dbf0()
{
    RHUnk00641782 lock;
    if (m_node->m_08 != (RHMapTreeDecNode *)g_unk0x006c0c28)
        m_node = RHMapTreeMin(m_node->m_08);
    else {
        RHMapTreeDecNode *parent;
        while (m_node == (parent = m_node->m_04)->m_08)
            m_node = parent;
        if (m_node->m_08 != parent)
            m_node = parent;
    }
}

void EmitRHMapTreeInc(RHMapTreeIncIterator &iterator)
{
    iterator.FUN_0053dbf0();
}

// FUNCTION: GAME 0x0053dcb0
RHMapStringIterator RHMapStringTree::FUN_0053dcb0(RHMapStringNode *node, RHMapStringNode *parent, const std::pair<const std::string, void *> &value)
{
    RHUnk00641782 lock;
    RHMapStringNode *inserted = (RHMapStringNode *)operator new(sizeof(RHMapStringNode));
    inserted->m_04 = parent;
    inserted->m_20 = 0;
    inserted->m_00 = (RHMapStringNode *)g_unk0x006c0c28;
    inserted->m_08 = (RHMapStringNode *)g_unk0x006c0c28;
    RHMapConstructValue(&inserted->m_0c, value);
    ++m_count;
    if (parent == m_head || node != (RHMapStringNode *)g_unk0x006c0c28 ||
        ((RHCampaignCommandLine *)&value.first)->FUN_0045a010(*(const RHProfileText *)&parent->m_0c.first) < 0) {
        parent->m_00 = inserted;
        if (parent == m_head) {
            m_head->m_04 = inserted;
            m_head->m_08 = inserted;
        } else if (parent == m_head->m_00) m_head->m_00 = inserted;
    } else {
        parent->m_08 = inserted;
        if (parent == m_head->m_08) m_head->m_08 = inserted;
    }
    for (node = inserted; node != m_head->m_04 && node->m_04->m_20 == 0;) {
        if (node->m_04 == Left(node->m_04->m_04)) {
            parent = node->m_04->m_04->m_08;
            if (parent->m_20 == 0) {
                node->m_04->m_20 = 1;
                parent->m_20 = 1;
                node->m_04->m_04->m_20 = 0;
                node = node->m_04->m_04;
            } else {
                if (node == node->m_04->m_08) {
                    node = node->m_04;
                    RotateLeft(node);
                }
                node->m_04->m_20 = 1;
                node->m_04->m_04->m_20 = 0;
                RotateRight(node->m_04->m_04);
            }
        } else {
            parent = node->m_04->m_04->m_00;
            if (parent->m_20 == 0) {
                node->m_04->m_20 = 1;
                parent->m_20 = 1;
                node->m_04->m_04->m_20 = 0;
                node = node->m_04->m_04;
            } else {
                if (node == node->m_04->m_00) {
                    node = node->m_04;
                    RotateRight(node);
                }
                node->m_04->m_20 = 1;
                node->m_04->m_04->m_20 = 0;
                RotateLeft(node->m_04->m_04);
            }
        }
    }
    m_head->m_04->m_20 = 1;
    RHMapStringIterator result;
    result.m_node = inserted;
    return result;
}

void EmitRHMapStringTree(RHMapStringTree &tree, const std::pair<const std::string, void *> &value)
{
    tree.FUN_0053dcb0(0, 0, value);
}

// FUNCTION: GAME 0x0053dfc0
RHMapStringNode *RHMapStringTree::FUN_0053dfc0(const std::string &key)
{
    RHUnk00641782 lock;
    RHMapStringNode *node = m_head->m_04;
    RHMapStringNode *candidate = m_head;
    while (node != (RHMapStringNode *)g_unk0x006c0c28) {
        if (node->m_0c.first.compare(key) < 0)
            node = node->m_08;
        else {
            candidate = node;
            node = node->m_00;
        }
    }
    return candidate;
}

void EmitRHMapLowerBound(RHMapStringTree &tree, const std::string &key)
{
    tree.FUN_0053dfc0(key);
}

// FUNCTION: GAME 0x0053e0b0
void RHMapTreeDecIterator::FUN_0053e0b0()
{
    RHUnk00641782 lock;
    if (m_node->m_20 == 0 && m_node->m_04->m_04 == m_node)
        m_node = m_node->m_08;
    else if (RHMapTreeDecLeft(m_node) != (RHMapTreeDecNode *)g_unk0x006c0c28)
        m_node = RHMapTreeDecMax(RHMapTreeDecLeft(m_node));
    else
    {
        RHMapTreeDecNode *parent;
        while (m_node == (parent = m_node->m_04)->m_00)
            m_node = parent;
        m_node = parent;
    }
}

void EmitRHMapTreeDec()
{
    RHMapTreeDecIterator iterator;
    iterator.FUN_0053e0b0();
}

// FUNCTION: GAME 0x0053ad50
void RHMapTree::FUN_0053ad50()
{
    RHMapTreeIterator first;
    first.node = m_head->left;
    RHMapTreeIterator last;
    last.node = m_head;
    FUN_0053d2f0(first, last);
    delete m_head;
    m_head = 0;
    m_size = 0;
    {
        RHUnk00641782 lock;
        if (--g_unk0x006c0c24 == 0) {
            delete g_unk0x006c0c28;
            g_unk0x006c0c28 = 0;
        }
    }
}

class RHUnk00613e90;

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int, int, int, bool);
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
    void FUN_005e6440(unsigned long, int, int, unsigned long, unsigned long);
    bool Unk005e5a00(unsigned long, RHUnk00613e90 &, unsigned long);
    void Unk005e5ea0(RHUnk00613e90 &);
};

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

class RHGame
{
public:
    void FUN_005105d0(unsigned char first, char second);
};

class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;

class SBThreadedInput;
extern SBThreadedInput *g_unk0x6c1340;

inline RHMapScreenTree::RHMapScreenTree(const RHMapScreenLess &comp, bool multi, const RHMapScreenAlloc &alloc)
    : m_alloc(alloc), m_comp(comp), m_multi(multi)
{
    Init();
}

inline RHMapScreenNode *RHMapScreenTree::Buynode(RHMapScreenNode *parent, int color)
{
    RHMapScreenNode *node = (RHMapScreenNode *)operator new(sizeof(RHMapScreenNode));
    node->parent = parent;
    node->color = color;
    return node;
}

inline void RHMapScreenTree::Init()
{
    RHUnk00641782 lock;
    if ((RHMapScreenNode *)g_unk0x006c0c28 == 0) {
        g_unk0x006c0c28 = (RHMapTreeNode *)Buynode(0, 1);
        g_unk0x006c0c28->left = 0;
        g_unk0x006c0c28->right = 0;
    }
    ++g_unk0x006c0c24;
    m_head = Buynode((RHMapScreenNode *)g_unk0x006c0c28, 0);
    m_size = 0;
    m_head->left = m_head;
    m_head->right = m_head;
}

DECOMP_SIZE_ASSERT(RHMenuScreenView, 0x1990)
DECOMP_STATIC_ASSERT(offsetof(RHMenuScreenView, m_sbui) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHMenuScreenView, m_191c) == 0x191c)
DECOMP_STATIC_ASSERT(offsetof(RHMenuScreenView, m_surfaces) == 0x194c)
DECOMP_STATIC_ASSERT(offsetof(RHMenuScreenView, m_196c) == 0x196c)
DECOMP_STATIC_ASSERT(offsetof(RHMenuScreenView, m_1980) == 0x1980)
DECOMP_STATIC_ASSERT(offsetof(RHMenuScreenView, m_198c) == 0x198c)

// FUNCTION: GAME 0x0053aaa0
RHMenuScreenView::RHMenuScreenView(unsigned long flags, long background, bool colorize, bool pause, void *ui)
    : m_ui(ui), m_04(0), m_08(0),
      m_background((void *)RHMapWindow::FUN_0053b6b0(background, colorize, pause)), m_1914(0),
      m_input(g_unk0x6c1340), m_surfaces(flags), m_196c(RHMapScreenLess(), false, RHMapScreenAlloc()),
      m_197c(false), m_198c(0)
{
    FUN_0053c140(flags);
}

// FUNCTION: GAME 0x0053adc0
RHMenuScreenView::RHMenuScreenView(unsigned long flags, long background, unsigned short color, void *ui)
    : m_ui(ui), m_04(0), m_08(0), m_background(FUN_0053b730(background, color)), m_1914(0),
      m_input(g_unk0x6c1340), m_surfaces(flags), m_196c(RHMapScreenLess(), false, RHMapScreenAlloc()),
      m_197c(false), m_198c(0)
{
    FUN_0053c140(flags);
}

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &offset);
};

// FUNCTION: GAME 0x0053b1f0
void RHMenuScreenView::FUN_0053b1f0(RHMenuWindow *window)
{
    RHUnkFXDraw *draw = (RHUnkFXDraw *)g_unk0x6c11d0;
    SBGeoVector2D offset;
    SBGeoBoundingBox2D box(((RHMapWidget *)window)->V24());
    float width = box.m_p1.m_x - box.m_p0.m_x;
    offset.m_x = (float)(unsigned short)(draw->FUN_005e56c0(0) >> 1) - width * 0.5f;
    float height = box.m_p1.m_y - box.m_p0.m_y;
    offset.m_y = (float)(unsigned short)(draw->FUN_005e5750(0) >> 1) - height * 0.5f;
    {
        SBGeoVector2D origin((const SBGeoVector2D &)box.m_p0);
        offset.FUN_005fc250(origin);
    }
    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(offset);
    ((RHMapWidget *)window)->V2c((const RHMapTitleText &)box);
}

#include "SBPictureUnkView.h"

DECOMP_SIZE_ASSERT(SBPictureUnkView, 0x18)

// GLOBAL: GAME 0x00677680
float g_unk0x00677680 = 1.0f / 64.0f;

// GLOBAL: GAME 0x00677684
float g_unk0x00677684 = 1.0f / 32.0f;

// FUNCTION: GAME 0x0053b330
bool RHMapWindow::FUN_0053b330(unsigned long surface, unsigned short amount, float factor)
{
    RHUnkFXDraw *draw = (RHUnkFXDraw *)g_unk0x6c11d0;
    SBPictureUnkView view;
    if (!draw->Unk005e5a00(surface, (RHUnk00613e90 &)view, 0))
        return false;
    unsigned long pitch = view.m_pitch >> 1;
    unsigned short *row = view.m_data;
    float r, g, b, h, s, v;
    if (*(unsigned short *)((char *)draw + 0x10c) == 16)
    {
        for (unsigned short y = 0; y < view.m_height; ++y)
        {
            for (unsigned short x = 0; x < view.m_width; ++x)
            {
                unsigned short color = row[x];
                r = ((color >> 11) * g_unk0x00677684) * factor * 2.0f;
                g = (((color >> 5) & 63) * g_unk0x00677680) * factor;
                b = ((color & 31) * g_unk0x00677684) * factor;
                RHMenuScreenView::RGB_To_HSV(r, g, b, h, s, v);
                RHMenuScreenView::HSV_To_RGB(amount, s, v, r, g, b);
                row[x] = (((unsigned short)(r * 32.0f) << 6) | ((unsigned short)(g * 64.0f) & 63)) << 5
                    | ((unsigned short)(b * 32.0f) & 31);
            }
            row += pitch;
        }
    }
    else
    {
        for (unsigned short y = 0; y < view.m_height; ++y)
        {
            for (unsigned short x = 0; x < view.m_width; ++x)
            {
                unsigned short color = row[x];
                r = ((((color >> 10) & 31) * g_unk0x00677684) * factor) * 2.0f;
                g = (((color >> 5) & 31) * g_unk0x00677684) * factor;
                b = ((color & 31) * g_unk0x00677684) * factor;
                RHMenuScreenView::RGB_To_HSV(r, g, b, h, s, v);
                RHMenuScreenView::HSV_To_RGB(amount, s, v, r, g, b);
                row[x] = ((((unsigned short)(r * 32.0f) & 31) << 5) | ((unsigned short)(g * 32.0f) & 31)) << 5
                    | ((unsigned short)(b * 32.0f) & 31);
            }
            row += pitch;
        }
    }
    draw->Unk005e5ea0((RHUnk00613e90 &)view);
    return true;
}

// FUNCTION: GAME 0x0053b6b0
unsigned long RHMapWindow::FUN_0053b6b0(unsigned long source, bool colorize, bool pause)
{
    RHUnkFXDraw *draw = (RHUnkFXDraw *)g_unk0x6c11d0;
    if (g_unk0x6c0b3c && pause == true)
        ((RHGame *)g_unk0x6c0b3c)->FUN_005105d0(0, 0);
    typedef unsigned long (RHUnkFXDraw::*CreateSurface)(unsigned short, unsigned short, unsigned long, bool);
    unsigned long surface = (draw->*reinterpret_cast<CreateSurface>(&RHUnkFXDraw::Unk005e4ed0))(
        draw->FUN_005e56c0(0), draw->FUN_005e5750(0), 0, false);
    draw->FUN_005e6440(source, 0, surface, 0, 0);
    if (colorize)
        FUN_0053b330(surface, 0x96, 0.2f);
    return surface;
}

#include "SBResourceManager.h"
#include "SBDrawManagerCore.h"
#include "SBUIUnk005fd4a0.h"

// FUNCTION: GAME 0x0053b730
void *RHMenuScreenView::FUN_0053b730(long background, unsigned short color)
{
    RHUnkFXDraw *draw = (RHUnkFXDraw *)g_unk0x6c11d0;
    SBGeoBoundingBox2D source;
    SBGeoBoundingBox2D destination;
    typedef unsigned long (RHUnkFXDraw::*CreateSurface)(unsigned short, unsigned short, unsigned long, bool);
    unsigned long surface = (draw->*reinterpret_cast<CreateSurface>(&RHUnkFXDraw::Unk005e4ed0))(
        draw->FUN_005e56c0(0), draw->FUN_005e5750(0), 0, false);
    unsigned long texture;
    ((SBResourceManager *)g_unk0x006c1840)->FUN_00600920(background, 0, texture);
    ((RHMobileUnk00607da0 *)&source)->FUN_00607da0((const RHMobileUnk00607da0 &)
        RHMapBox(0, 0, draw->FUN_005e56c0(texture), draw->FUN_005e5750(texture)));
    ((RHMobileUnk00607da0 *)&destination)->FUN_00607da0((const RHMobileUnk00607da0 &)
        RHMapBox(0, 0, draw->FUN_005e56c0(0), draw->FUN_005e5750(0)));
    ((SBDrawManager *)draw)->FUN_005e61e0(surface, &destination, color, 0);
    ((RHMobileUnk00607da0 *)&source)->FUN_00607da0((const RHMobileUnk00607da0 &)source.FUN_006092c0(destination));
    ((RHMobileUnk00607da0 *)&destination)->FUN_00607da0((const RHMobileUnk00607da0 &)source.FUN_006090d0(
        SBGeoVector2D(((destination.m_p1.m_x - destination.m_p0.m_x) - (source.m_p1.m_x - source.m_p0.m_x)) * 0.5f,
            ((destination.m_p1.m_y - destination.m_p0.m_y) - (source.m_p1.m_y - source.m_p0.m_y)) * 0.5f)));
    float height = source.m_p1.m_y - source.m_p0.m_y;
    float width = source.m_p1.m_x - source.m_p0.m_x;
    ((RHMobileUnk00607da0 *)&source)->FUN_00607da0((const RHMobileUnk00607da0 &)source.FUN_006090d0(
        SBGeoVector2D((draw->FUN_005e56c0(texture) - width) * 0.5f,
            (draw->FUN_005e5750(texture) - height) * 0.5f)));
    ((SBDrawManager *)draw)->FUN_005e6440(texture, &source, surface, &destination, 0);
    ((SBUIUnk005fd4a0 *)g_unk0x006c1840)->FUN_005fd4a0(background);
    return (void *)surface;
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

// FUNCTION: GAME 0x0053bb80
void RHMenuScreenView::FUN_0053bb80(RHMenuWindow *window, bool display, bool modal)
{
    FUN_0053c650(window, display);
    if (modal == 1)
        FUN_0053b1f0(window);
    if (display)
        FUN_0053c390();
}

// FUNCTION: GAME 0x0053bbc0
void RHMenuScreenView::FUN_0053bbc0(RHMenuWindow *window)
{
    RHPortraitRootLifetime *widget = (RHPortraitRootLifetime *)window;
    typedef void (RHPortraitRootLifetime::*SetVisible)(bool);
    SetVisible setVisible;
    *(unsigned *)&setVisible = (*(unsigned **)widget)[0x12];
    (widget->*setVisible)(false);
    widget->m_visible = false;
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

// FUNCTION: GAME 0x0053be40
void RHMenuScreenView::FUN_0053be40(unsigned long value)
{
    m_04 = (unsigned long)RHGameInputTranslator::mpInstance;
    m_08 = value;
}

// FUNCTION: GAME 0x0053be60
void RHMenuScreenView::FUN_0053be60(RHMenuWindow *window)
{
    RHPortraitRootLifetime *widget = (RHPortraitRootLifetime *)window;
    typedef void (RHPortraitRootLifetime::*SetVisible)(bool);
    SetVisible setVisible;
    *(unsigned *)&setVisible = (*(unsigned **)widget)[0x12];
    (widget->*setVisible)(true);
    widget->m_visible = true;
}

// FUNCTION: GAME 0x0053bf30
RHMenuWindowUI *RHMenuScreenView::FUN_0053bf30()
{
    return (RHMenuWindowUI *)&m_sbui;
}

class RHMenuScreenFont
{
public:
    virtual void Unk00();
    virtual void Unk04();
    virtual void Unk08();
    virtual void Unk0c();
    virtual void Unk10();
    virtual void AttachToRenderContext(void *context, unsigned long flags);
};

// FUNCTION: GAME 0x0053be80
void *RHMenuScreenView::FUN_0053be80(const std::string &name)
{
    RHMapStringTree &fonts = *(RHMapStringTree *)&m_196c;
    RHMapStringIterator found;
    found.m_node = fonts.FUN_0053dfc0(name);
    RHMapStringIterator end;
    RHMapStringIterator it = found.m_node == fonts.m_head
        || ((RHCampaignCommandLine *)&name)->FUN_0045a010(*(const RHProfileText *)&found.m_node->m_0c.first) < 0
        ? (end.m_node = fonts.m_head, end) : found;
    if (it.m_node != (RHMapStringNode *)m_196c.m_head)
        return it.m_node->m_0c.second;
    RHMenuScreenFont *font = (RHMenuScreenFont *)((RHFontManager *)RHFontManager::FUN_005024f0())->GetFont(name);
    if (font)
    {
        font->AttachToRenderContext(&m_surfaces, 0);
        fonts.FUN_0053cd30(name) = font;
    }
    return font;
}

// map operator[] glue: the original inlines insert under an EH frame.
// STUB: GAME 0x0053cd30
void *&RHMapStringTree::FUN_0053cd30(const std::string &key)
{
    return FUN_0053dfc0(key)->m_0c.second;
}

// FUNCTION: GAME 0x0053bf40
void RHMenuScreenView::FUN_0053bf40(void *events)
{
    if (!m_191c.empty())
    {
        std::vector<void *> widgets = m_191c.back();
        for (std::vector<void *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            void *event = events;
            while (event)
            {
                RHPortraitRootLifetime *widget = (RHPortraitRootLifetime *)*it;
                typedef void (RHPortraitRootLifetime::*Dispatch)(void *);
                Dispatch dispatch;
                *(unsigned *)&dispatch = (*(unsigned **)widget)[0x14];
                (widget->*dispatch)(event);
                event = *(void **)((char *)event + 0x0c);
            }
        }
    }
}

// FUNCTION: GAME 0x0053c050
void RHMenuScreenView::FUN_0053c050()
{
    if (!m_191c.empty())
    {
        std::vector<void *> widgets = m_191c.back();
        for (std::vector<void *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            RHPortraitRootLifetime *widget = (RHPortraitRootLifetime *)*it;
            typedef void (RHPortraitRootLifetime::*Notify)();
            Notify notify;
            *(unsigned *)&notify = (*(unsigned **)widget)[0x15];
            (widget->*notify)();
        }
    }
}

// FUNCTION: GAME 0x0053c320
bool RHMenuScreenView::FUN_0053c320(void *widget)
{
    void **first = *(void ***)((char *)this + 0x18);
    *(bool *)((char *)this + 0x28) = false;
    *(void **)((char *)this + 0x30) = widget;
    int count = first == 0 ? 0 : *(void ***)((char *)this + 0x1c) - first;
    void **&cursor = *(void ***)((char *)this + 0x24);
    cursor = first;
    int index = 0;
    *(bool *)((char *)this + 0x29) = true;
    for (; index < count; ++index, ++cursor)
        if (*cursor == widget)
            break;
    *(int *)((char *)this + 0x2c) = index < count ? index : -1;
    return *(int *)((char *)this + 0x2c) != -1;
}

struct RHMenuScreenTimerEvent
{
    int type;
    unsigned timer;
    void *data;
    RHMenuScreenTimerEvent *next;
};

// FUNCTION: GAME 0x0053c5b0
void RHMenuScreenView::FUN_0053c5b0()
{
    unsigned now = GetTickCount();
    RHMenuScreenTimerEvent *first = 0;
    RHMenuScreenTimerEvent *last = 0;
    for (std::list<RHMenuScreenTimer>::iterator it = m_1980.begin(); it != m_1980.end(); ++it)
    {
        if (now - it->m_08 >= it->m_04)
        {
            RHMenuScreenTimerEvent *event = new RHMenuScreenTimerEvent;
            it->m_08 = now;
            event->data = 0;
            event->next = 0;
            event->timer = it->m_00;
            event->type = 0x1000;
            if (!first)
                first = event;
            else
                last->next = event;
            last = event;
        }
    }
    FUN_0053bf40(first);
    RHMenuScreenTimerEvent *current = first;
    while (current)
    {
        RHMenuScreenTimerEvent *event = current;
        current = current->next;
        delete event;
    }
}

// FUNCTION: GAME 0x0053c7e0
void RHMapWindow::FUN_0053c7e0()
{
    ((RHMapWindowPart *)((char *)this + 0x10))->FUN_00618850((char *)this + 0x1914);
}

// FUNCTION: GAME 0x0053c7f0
void RHMenuScreenView::FUN_0053c7f0(unsigned long surface)
{
    ((SBUI *)&m_sbui)->FUN_00618910(surface);
}

// FUNCTION: GAME 0x0053c800
void RHMenuScreenView::FUN_0053c800()
{
    RHMapTreeIncIterator current;
    RHMapTreeDecNode *head = *(RHMapTreeDecNode *volatile *)&m_196c.m_head;
    current.m_node = head->m_00;
    while (current.m_node != head)
    {
        RHPortraitRootLifetime *resource = (RHPortraitRootLifetime *)current.m_node->m_1c;
        typedef void (RHPortraitRootLifetime::*Detach)();
        Detach detach;
        *(unsigned *)&detach = (*(unsigned **)resource)[6];
        (resource->*detach)();
        resource = (RHPortraitRootLifetime *)current.m_node->m_1c;
        if (resource)
        {
            typedef void *(RHPortraitRootLifetime::*Destroy)(unsigned);
            Destroy destroy;
            *(unsigned *)&destroy = (*(unsigned **)resource)[2];
            (resource->*destroy)(1);
        }
        current.FUN_0053dbf0();
        head = *(RHMapTreeDecNode *volatile *)&m_196c.m_head;
    }
    RHMapTree &tree = *(RHMapTree *)&m_196c;
    RHMapTreeIterator first;
    first.node = tree.m_head->left;
    RHMapTreeIterator last;
    last.node = tree.m_head;
    tree.FUN_0053d2f0(first, last);
}

#include <math.h>

extern float g_unk0x677554;

// FUNCTION: GAME 0x0053ca30
void RHMenuScreenView::HSV_To_RGB(float h, float s, float v, float &r, float &g, float &b)
{
    if (s == 0.0f)
    {
        r = v;
        g = v;
        b = v;
        return;
    }
    h *= 1.0f / 60.0f;
    double i = floor(h);
    float f = h - i;
    float p = v * (1.0f - s);
    float q = v * (1.0f - s * f);
    float t = v * (1.0f - s * (1.0f - f));
    switch ((unsigned short)i)
    {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
        r = v;
        g = p;
        b = q;
        break;
    }
}

// FUNCTION: GAME 0x0053cbc0
void RHMenuScreenView::RGB_To_HSV(float r, float g, float b, float &h, float &s, float &v)
{
    float maximum = max(r, max(g, b));
    float minimum = min(r, min(g, b));
    v = maximum;
    if (maximum != 0.0f)
    {
        s = (maximum - minimum) / maximum;
        float delta = maximum - minimum;
        if (r == maximum)
            h = (g - b) / delta;
        else if (g == maximum)
            h = 2.0f + (b - r) / delta;
        else if (b == maximum)
            h = 4.0f + (r - g) / delta;
        float hue = h;
        h = hue * g_unk0x677554;
        if (h < 0.0f)
            h += 360.0f;
    }
    else
    {
        s = 0.0f;
        h = 360.0f;
    }
}

// FUNCTION: GAME 0x0053cd20
bool RHMenuScreenView::FUN_0053cd20()
{
    return m_197c;
}

// LIBRARY: GAME 0x0053e170
// ?_Add@const_iterator@?$deque@V?$vector@PAXV?$allocator@PAX@std@@@std@@V?$allocator@V?$vector@PAXV?$allocator@PAX@std@@@std@@@2@@std@@IAEXH@Z

// LIBRARY: GAME 0x0053e1e0
// ?_Construct@std@@YAXPAV?$vector@PAXV?$allocator@PAX@std@@@1@ABV21@@Z

void (*g_rhMapWidgetsConstruct)(std::vector<void *> *, const std::vector<void *> &) = &std::_Construct;

void RHMenuCampaignMap::Emit()
{
    float h, s, v;
    RHMenuScreenView::HSV_To_RGB(0, 0, 0, h, s, v);
    RHMenuScreenView::RGB_To_HSV(0, 0, 0, h, s, v);
    RouteEvent(0);
    Create();
    DisplayPseudoMissionDebriefing();
    RHMapCampaign *campaign = (RHMapCampaign *)g_unk0x6c07fc;
    campaign->FUN_004577a0();
    campaign->FUN_004577b0();
    RHMapWindow *window = *(RHMapWindow **)((char *)this + 0xb4);
    window->FUN_0053bb30(0);
    window->FUN_0053bbe0();
    ((RHMenuScreenView *)window)->FUN_0053c050();
    ((RHMenuScreenView *)window)->FUN_0053bf40(0);
    ((RHMenuScreenView *)window)->FUN_0053c5b0();
    RHMenuScreenView::FUN_0053bbc0((RHMenuWindow *)window);
    RHMenuScreenView::FUN_0053be60((RHMenuWindow *)window);
    window->FUN_0053c7e0();
    ((RHMenuScreenView *)window)->FUN_0053c7f0(0);
    ((RHMenuScreenView *)window)->FUN_0053c800();
    FUN_00528520(0, 0, 0);
    FUN_00528550(0, 0, 0);
    campaign->FUN_005286b0();
    FUN_00528a60();
}

void EmitRHMapTree(RHMapTree *tree)
{
    tree->FUN_0053ad50();
}
