#include "SBNullstr.h"
#include "RHMenuWindow.h"

#include "RHMapBox.h"
#include "RHMapWidget.h"
#include "RHGameTitleLifetimeInline.h"

extern wchar_t g_unk0x006c0b50[1];
std::wstring FUN_005e23d0(unsigned long);

inline void RHYesNoSetText(RHPortraitButton &button, const std::wstring &text)
{
    typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
    Assign assign = &std::wstring::assign;
    button.m_08 = true;
    (button.m_20.*assign)(text, 0, std::wstring::npos);
}

DECOMP_SIZE_ASSERT(RHMenuYesNo, 0x448)
DECOMP_SIZE_ASSERT(RHPortraitButton, 0x100)

// FUNCTION: GAME 0x005451a0
void RHMenuYesNo::HandleEvent(RHMenuEvent *event)
{
    if (RouteEvent(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x005451c0
bool RHMenuYesNo::RouteEvent(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x344)
        handled = OnYes(event->m_type, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x244)
        handled = OnNo(event->m_type, event->m_widget, event->m_data);
    return handled;
}

// STUB: GAME 0x00545220
RHMenuYesNo::RHMenuYesNo(RHMenuWindowScreen *screen, const std::wstring &text)
    : RHMenuWindowFocus(0, screen, 0xed, 1, true),
      m_font(screen->FUN_0053be80(std::string("PopupScroll"))), m_choice(0)
{
    void *font = m_font;
    ((RHMapWidget *)&m_144)->V30(text, RHMapBox(25.0f, 50.0f, 375.0f, 120.0f), 0, 0);
    m_244.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x92);
    m_344.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x91);
    RHYesNoSetText(m_244, FUN_005e23d0(0x14b));
    RHYesNoSetText(m_344, FUN_005e23d0(0x14a));
    ((RHUnk005d92c0Sub *)&m_344)->v08(SBGeoPoint2D(0.0f, 130.0f));
    ((SBUIUnk0060dd00 *)&m_144.m_renderer)->FUN_0060e0d0(font, font, font, font);
}

// FUNCTION: GAME 0x00545590
void *RHMenuYesNo::FUN_00545590(unsigned flags)
{
    this->~RHMenuYesNo();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005455b0
RHMenuYesNo::~RHMenuYesNo()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_144);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_244);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_344);
}

// FUNCTION: GAME 0x00545670
bool RHMenuYesNo::AskForConfirmation(RHMenuWindowScreen *screen, const std::wstring &text)
{
    RHMenuYesNo dialog(screen, text);
    dialog.FUN_00545710();
    dialog.FUN_00544b80(true, true);
    dialog.FUN_00544300();
    return dialog.FUN_00545ad0() == 1;
}

#include "RHMapBox.h"
#include "RHMenuCampaignMapClass.h"
#include "RHFocusManager.h"
#include "RHSaveGameManager.h"

extern wchar_t g_unk0x006c0b50[1];

inline void RHYesNoInsert(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

// FUNCTION: GAME 0x00545710
bool RHMenuYesNo::FUN_00545710()
{
    if (((RHMenuWindow *)this)->FUN_00544b40(g_unk0x006c0b50, RHMapBox(0.0f, 0.0f, 400.0f, 200.0f), 0))
    {
        std::vector<void *> widgets;
        RHYesNoInsert(widgets, &m_344);
        RHYesNoInsert(widgets, &m_244);
        ((RHMenuWindow *)this)->FUN_005449e0(widgets, 18);
        ((RHMenuCampaignMap *)this)->V30(&m_344);
        ((RHMenuCampaignMap *)this)->V30(&m_244);
        ((RHMenuCampaignMap *)this)->V30(&m_144);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_344, false);
        RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_244, false);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_344, 0x1c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_344, 0x9c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_244, 1);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x00545ad0
int RHMenuYesNo::FUN_00545ad0()
{
    return m_choice;
}

// FUNCTION: GAME 0x00545ae0
bool RHMenuYesNo::OnNo(int, void *, void *)
{
    m_choice = 2;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}

// FUNCTION: GAME 0x00545b00
bool RHMenuYesNo::OnYes(int, void *, void *)
{
    m_choice = 1;
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}
