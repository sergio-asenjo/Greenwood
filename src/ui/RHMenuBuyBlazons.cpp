#include "SBNullstr.h"
#include "RHRendererGeometry.h"
#include "RHMenuBuyBlazons.h"
#include "RHMenuScreenView.h"
#include "RHMapBox.h"
#include "SBUIRenderer.h"
#include "RHMapWidget.h"
#include "RHMenuCampaignMapClass.h"
#include "RHFocusManager.h"
#include "RHSaveGameManager.h"
#include "RHMission.h"
#include "RHMissionStat.h"
#include "RHGameMenuCalls.h"
#include "RHWidgetPortraitClass.h"
#include <wchar.h>

extern wchar_t g_unk0x006c0b50[1];
std::wstring FUN_005e23d0(unsigned long);

class RHBuyBlazonsWidgetCalls
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
    virtual void V2c();
    virtual bool V30(const std::wstring &, const RHMapBox &, unsigned, unsigned);
};

inline void RHBuyBlazonsSetText(RHPortraitButton &button, const std::wstring &text)
{
    typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
    Assign assign = &std::wstring::assign;
    *((bool *)&button + 8) = true;
    (((std::wstring *)((char *)&button + 0x20))->*assign)(text, 0, std::wstring::npos);
}

DECOMP_SIZE_ASSERT(RHMenuBuyBlazons, 0x44c)

// Parked at 0.8023: first string boundary and register scheduling differ.
// STUB: GAME 0x00524990
RHMenuBuyBlazons::RHMenuBuyBlazons(RHMenuWindow *parent, RHMenuWindowScreen *screen)
    : RHMenuWindowFocus(parent, screen, 0xed, 1, true), m_444(0),
      m_448(screen->FUN_0053be80(std::string("Debrief")))
{
    m_cancel.FUN_005d1e30((int)m_screen, std::wstring(g_unk0x006c0b50), 0x92);
    m_ok.FUN_005d1e30((int)m_screen, std::wstring(g_unk0x006c0b50), 0x91);
    {
        const std::wstring price(
            // STRING: GAME 0x006b0900
            L"Price");
        ((RHBuyBlazonsWidgetCalls *)&m_title)->V30(price, RHMapBox(50.0f, 50.0f, 350.0f, 125.0f), 0, unsigned(-1));
    }
    RHBuyBlazonsSetText(m_ok, FUN_005e23d0(0x14a));
    RHBuyBlazonsSetText(m_cancel, FUN_005e23d0(0x14b));
    ((SBUIUnk0060dd00 *)&m_title.m_renderer)->FUN_0060e0d0(parent, parent, parent, parent);
    *(bool *)((char *)&m_title + 0xf8) = true;
}

// FUNCTION: GAME 0x00524cf0
void *RHMenuBuyBlazons::FUN_00524cf0(unsigned flags)
{
    this->~RHMenuBuyBlazons();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00524d10
RHMenuBuyBlazons::~RHMenuBuyBlazons()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_ok);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_title);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_cancel);
}

inline void RHBuyBlazonsInsert(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

// FUNCTION: GAME 0x00524dd0
bool RHMenuBuyBlazons::Create(RHMission *mission, RHMenuShortMissionBlazons *blazons)
{
    if (((RHMenuWindow *)this)->FUN_00544b40(
            // STRING: GAME 0x006b0914
            L"Buy blazons background",
            RHMapBox(0.0f, 0.0f, 400.0f, 200.0f), 0))
    {
        std::vector<void *> widgets;
        ((RHMenuCampaignMap *)this)->V30(&m_cancel);
        ((RHMenuCampaignMap *)this)->V30(&m_ok);
        ((RHMenuCampaignMap *)this)->V30(&m_title);
        ((RHUnk005d92c0Sub *)&m_ok)->v08(SBGeoPoint2D(0.0f, 135.0f));
        RHBuyBlazonsInsert(widgets, &m_ok);
        RHBuyBlazonsInsert(widgets, &m_cancel);
        ((RHMenuWindow *)this)->FUN_005449e0(widgets, 20);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, false);
        RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, false);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, 0x1c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, 0x9c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, 1);
        m_440 = mission;
        m_444 = blazons;
        UpdateState();
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x005250c0
void RHMenuBuyBlazons::UpdateState()
{
    if (g_unk0x6c07fc->Get(1) >= m_440->GetM6())
    {
        std::wstring text;
        unsigned short buffer[0x100];
        swprintf(buffer, FUN_005e23d0(0xf4).c_str(), g_unk0x6c07fc->Get(1));
        text = buffer;
        text += L"\n";
        swprintf(buffer, FUN_005e23d0(0xf0).c_str(), m_440->GetM6());
        text += buffer;
        text += L"\n";
        text += FUN_005e23d0(0xef);
        ((RHMapWidget *)&m_title)->V2c((const RHMapTitleText &)text);
        ((RHMenuCampaignMap *)this)->V1c();
    }
    else
        ((RHGameMenuCalls *)this)->FUN_00544b30();
}
