#include "RHMenuCampaignMap.h"
#include "RHPortraitRootLifetime.h"
#include "RHMenuScreenView.h"
#include "RHUnk00527870.h"
#include <windows.h>
#include <stdio.h>
#include <stddef.h>

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

// LIBRARY: GAME 0x00525430
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

class RHGameWidgetLifetimeBase
{
public:
    RHGameWidgetLifetimeBase();
    ~RHGameWidgetLifetimeBase();
    unsigned m_vptr;
    undefined m_data[0x7c];
};

class RHGameRenderer0060da10
{
public:
    RHGameRenderer0060da10();
    ~RHGameRenderer0060da10();
    undefined m_data[0x4c];
};

class RHUnk00528a80 : public RHGameWidgetLifetimeBase
{
public:
    RHUnk00528a80();
    RHGameRenderer0060da10 m_renderer;
};

// FUNCTION: GAME 0x00528a80
RHUnk00528a80::RHUnk00528a80()
{
    m_vptr = 0x00678c10;
}

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

class RHPopupRenderer0060dbc0
{
public:
    bool FUN_0060dd10(unsigned id);
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

// FUNCTION: GAME 0x00525840
void RHUnk005254f0::FUN_00525840()
{
    RHMapWidgetField<bool>(this, 0xfc) = true;
    RHMapWidgetField<bool>(this, 0xfd) = true;
    RHMapWidgetField<unsigned>(this, 0xc0) = -1;
    RHMapWidgetField<unsigned>(this, 0xc4) = -1;
}

void RHMapTailEmit(void *object, unsigned index, const std::wstring &text)
{
    RHUnk005254f0 *widget = (RHUnk005254f0 *)object;
    widget->FUN_005254f0();
    widget->FUN_00525510(index);
    widget->FUN_005255c0(text);
    widget->FUN_005257c0(index);
    widget->FUN_00525840();
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

// FUNCTION: GAME 0x00528c70
void *RHUnk00527870::FUN_00528c70(unsigned flags)
{
    FUN_00527870();
    if (flags & 1)
        operator delete(this);
    return this;
}

void EmitRHMapBlink(RHUnk00528a80 *text, RHUnk00528ad0 *blink)
{
    text->RHUnk00528a80::RHUnk00528a80();
    blink->FUN_00528ad0(0);
    blink->FUN_00528b70();
    blink->FUN_00528bb0();
    blink->FUN_00528be0();
    ((RHUnk00527870 *)blink)->FUN_00528c70(0);
}

class RHUnk00641782
{
public:
    RHUnk00641782();
    ~RHUnk00641782();
    unsigned char m_00;
};

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

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int, int, int, int);
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
    void FUN_005e6440(unsigned long, int, int, unsigned long, unsigned long);
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

// LIBRARY: GAME 0x0053e170
// ?_Add@const_iterator@?$deque@V?$vector@PAXV?$allocator@PAX@std@@@std@@V?$allocator@V?$vector@PAXV?$allocator@PAX@std@@@std@@@2@@std@@IAEXH@Z

// LIBRARY: GAME 0x0053e1e0
// ?_Construct@std@@YAXPAV?$vector@PAXV?$allocator@PAX@std@@@1@ABV21@@Z

void (*g_rhMapWidgetsConstruct)(std::vector<void *> *, const std::vector<void *> &) = &std::_Construct;

// FUNCTION: GAME 0x00544b40
bool RHMenuCampaignMap::FUN_00544b40(const RHMapTitleText &title, const RHMapBox &box, unsigned flags)
{
    return ((RHPortraitRootLifetime *)this)->FUN_0061a1e0(title, box, flags);
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
    FUN_00528520(0, 0, 0);
    FUN_00528550(0, 0, 0);
    campaign->FUN_005286b0();
    FUN_00528a60();
}

void EmitRHMapTree(RHMapTree *tree)
{
    tree->FUN_0053ad50();
}
