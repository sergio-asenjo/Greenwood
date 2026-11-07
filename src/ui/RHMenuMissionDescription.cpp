#include "SBGeoBoundingBox2DCore.h"
#include "SBGeoVector2D.h"
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
#include "RHMapResources.h"
#include "RHMapWidget.h"
#include "RHMenuCampaignMapClass.h"
#include "RHMenuScreenView.h"
#include "RHFocusManager.h"
#include "RHSaveGameManager.h"
#include "SBUIRenderer.h"
#include "RHWidgetPortraitClass.h"
#include "RHMobileUnk00607da0.h"
#include <stddef.h>

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
extern RHMapResources *g_unk0x006c1840;

DECOMP_SIZE_ASSERT(RHMenuMissionDescription, 0x938)
DECOMP_STATIC_ASSERT(offsetof(RHMenuMissionDescription, m_buy) == 0x140)
DECOMP_STATIC_ASSERT(offsetof(RHMenuMissionDescription, m_start) == 0x240)
DECOMP_STATIC_ASSERT(offsetof(RHMenuMissionDescription, m_accept) == 0x340)
DECOMP_STATIC_ASSERT(offsetof(RHMenuMissionDescription, m_cancel) == 0x440)
DECOMP_STATIC_ASSERT(offsetof(RHMenuMissionDescription, m_close) == 0x540)
DECOMP_STATIC_ASSERT(offsetof(RHMenuMissionDescription, m_picture) == 0x640)
DECOMP_STATIC_ASSERT(offsetof(RHMenuMissionDescription, m_title) == 0x70c)
DECOMP_STATIC_ASSERT(offsetof(RHMenuMissionDescription, m_text) == 0x80c)
DECOMP_STATIC_ASSERT(offsetof(RHMenuMissionDescription, m_mission) == 0x92c)
DECOMP_STATIC_ASSERT(offsetof(RHMenuMissionDescription, m_930) == 0x930)

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

extern wchar_t g_unk0x006c0b50[1];
std::wstring FUN_005e23d0(unsigned long);

inline void RHMissionDescriptionInsert(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

inline void RHMissionDescriptionSetText(RHPortraitButton &button, const std::wstring &text)
{
    typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
    Assign assign = &std::wstring::assign;
    button.m_08 = true;
    (button.m_20.*assign)(text, 0, std::wstring::npos);
}

// STUB: GAME 0x00534770
bool RHMenuMissionDescription::Create()
{
    if (((RHMenuWindow *)this)->FUN_00544b40(g_unk0x006c0b50, RHMapBox(0.0f, 0.0f, 496.0f, 463.0f), 0))
    {
        void *titleFont = m_screen->FUN_0053be80(std::string("MissionTitle"));
        void *textFont = m_screen->FUN_0053be80(std::string("PopupScroll"));
        std::vector<void *> widgets;
        SBGeoBoundingBox2D bounds;
        ((RHMapWidget *)&m_picture)->V30(g_unk0x006c0b50, RHMapBox(50.0f, 40.0f, 50.0f, 40.0f), 0, FUN_00535620(m_mission));
        ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0((const RHMobileUnk00607da0 &)m_picture.Box());
        ((RHUnk005d92c0Sub *)&m_picture)->v08(SBGeoPoint2D(450.0f, 40.0f).FUN_005fc200(SBGeoVector2D(bounds.Width(), 0.0f)));
        ((RHMobileUnk00607da0 *)&bounds)->FUN_00607da0((const RHMobileUnk00607da0 &)m_picture.Box());
        m_close.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x92);
        ((RHMapWidget *)&m_title)->V30(FUN_00535650(m_mission, 0), RHMapBox(50.0f, 50.0f, bounds.Min().GetX() - 10.0f, 125.0f), 0, unsigned(-1));
        RHMissionDescriptionSetText(m_close, FUN_005e23d0(0x14d));
        ((RHMenuCampaignMap *)this)->V30(&m_close);
        ((RHMenuCampaignMap *)this)->V30(&m_picture);
        ((RHMenuCampaignMap *)this)->V30(&m_title);
        if ((char)m_mission->FUN_0054cbf0())
        {
            ((RHMapWidget *)&m_text)->V30(FUN_00535650(m_mission, 2), RHMapBox(50.0f, bounds.Max().GetY() + 5.0f, 450.0f, 385.0f), 0, unsigned(-1));
            ((RHMenuCampaignMap *)this)->V30(&m_text);
            m_930->FUN_0044ef60(RHMapBox(50.0f, 125.0f, bounds.Min().GetX() - 20.0f, 463.0f), (RHFocusManager *)((char *)this + 0xc8));
            m_start.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x9e);
            m_buy.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x9d);
            m_accept.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x9f);
            RHMissionDescriptionSetText(m_start, FUN_005e23d0(0x145));
            RHMissionDescriptionSetText(m_buy, FUN_005e23d0(0x146));
            RHMissionDescriptionSetText(m_accept, FUN_005e23d0(0x147));
            ((RHUnk005d92c0Sub *)&m_start)->v08(SBGeoPoint2D(0.0f, 384.0f));
            ((RHMenuCampaignMap *)this)->V30(&m_start);
            ((RHMenuCampaignMap *)this)->V30(&m_buy);
            ((RHMenuCampaignMap *)this)->V30(&m_accept);
            RHMissionDescriptionInsert(widgets, &m_start);
            RHMissionDescriptionInsert(widgets, &m_buy);
            RHMissionDescriptionInsert(widgets, &m_accept);
            *(char *)&m_start.m_04 = (char)((RHGameCampaignView *)g_unk0x6c07fc)->FUN_00456190((RHGameMission *)m_mission);
            *(char *)&m_buy.m_04 = (char)((RHGameCampaignView *)g_unk0x6c07fc)->FUN_00456230((RHGameMission *)m_mission);
            *(char *)&m_accept.m_04 = (char)((RHGameCampaignView *)g_unk0x6c07fc)->FUN_004561d0((RHGameMission *)m_mission);
            ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_start, true);
            RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
            focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_buy, true);
            focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_accept, true);
            if (*(unsigned *)((char *)m_mission->m_profile + 0x34) != 5)
            {
                m_cancel.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0xa0);
                ((RHUnk005d92c0Sub *)&m_cancel)->v08(SBGeoPoint2D(0.0f, 384.0f));
                RHMissionDescriptionSetText(m_cancel, FUN_005e23d0(0x143));
                ((RHMenuCampaignMap *)this)->V30(&m_cancel);
                focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, true);
                focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, 0x1c);
                focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, 0x9c);
                RHMissionDescriptionInsert(widgets, &m_cancel);
            }
            else if (*(unsigned short *)((char *)m_mission->m_profile + 0x70) == 0)
            {
                m_start.m_04 = false;
                m_accept.m_04 = false;
            }
        }
        else
        {
            ((RHMapWidget *)&m_text)->V30(FUN_00535650(m_mission, 2), RHMapBox(50.0f, 125.0f, 450.0f, 385.0f), 0, unsigned(-1));
            ((RHMenuCampaignMap *)this)->V30(&m_text);
            m_text.m_renderer.FUN_005cb9d0((unsigned long)(bounds.Width() + 10.0f), (unsigned long)(bounds.Max().GetY() - bounds.Min().GetY() + bounds.Min().GetY() - 125.0f + 5.0f));
            m_cancel.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x91);
            ((RHUnk005d92c0Sub *)&m_cancel)->v08(SBGeoPoint2D(0.0f, 384.0f));
            RHMissionDescriptionSetText(m_cancel, FUN_005e23d0(0x143));
            ((RHMenuCampaignMap *)this)->V30(&m_cancel);
            ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, true);
            RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
            focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, 0x1c);
            focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, 0x9c);
            RHMissionDescriptionInsert(widgets, &m_cancel);
        }
        RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_close, true);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_close, 1);
        focus.FUN_004ffd20(&m_picture);
        RHMissionDescriptionInsert(widgets, &m_close);
        ((RHMenuWindow *)this)->FUN_005449e0(widgets, 8);
        ((SBUIUnk0060dd00 *)&m_title.m_renderer)->FUN_0060e0d0(titleFont, titleFont, titleFont, titleFont);
        m_title.m_renderer.SetM64(4);
        ((SBUIUnk0060dd00 *)&m_text.m_renderer)->FUN_0060e0d0(textFont, textFont, textFont, textFont);
        m_text.m_renderer.SetM60(4);
        m_text.m_renderer.SetM64(2);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x00535620
unsigned long RHMenuMissionDescription::FUN_00535620(const RHMission *mission)
{
    RHDialogueSet *resources = g_pEngine->GetDynResources(*(unsigned long *)mission->m_profile);
    if (resources)
        return *(unsigned long *)((char *)resources + 4);
    return 0xa4;
}

// FUNCTION: GAME 0x00535650
std::wstring RHMenuMissionDescription::FUN_00535650(const RHMission *mission, unsigned long resource)
{
    RHMapResources *manager = g_unk0x006c1840;
    RHDialogueSet *resources = g_pEngine->GetDynResources(*(unsigned long *)mission->m_profile);
    std::wstring text;
    if (!resources)
        text =
            // STRING: GAME 0x006b0e78
            L"Unable to find the mission resource...";
    else if (!manager->FUN_006009e0(*(unsigned *)resources, resource, (RHMapWideText &)text))
        text = L"Invalid resource ID...";
    return text;
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
    m_930->FUN_0044f960(0);
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
    menu->Create();
    menu->RouteEvent(0);
    menu->GetUserChoice();
    menu->FUN_00535620(0);
    menu->FUN_00535650(0, 0);
    menu->FUN_005357e0(0, 0, 0);
    menu->FUN_005358d0(0, 0, 0);
    menu->FUN_00535910(0, 0, 0);
}
