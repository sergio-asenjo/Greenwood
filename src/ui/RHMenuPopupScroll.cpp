// RHMenuPopupScroll.cpp — popup scroll menu TU (code 0x005394e0..). See
// RHMenuPopupScroll.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuPopupScroll.h"
#include "RHMapBox.h"
#include "RHMapWidget.h"
#include "RHMenuCampaignMapClass.h"
#include "RHFocusManager.h"
#include "RHSaveGameManager.h"
#include "SBUIRenderer.h"

// FUNCTION: GAME 0x005394e0
void RHMenuPopupScroll::FUN_005394e0(RHMenuEvent *event)
{
    if (FUN_00539500(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x00539500
bool RHMenuPopupScroll::FUN_00539500(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x144)
        handled = FUN_0053a860(2, event->m_widget, event->m_data);
    return handled;
}

// Inline budget differs: m_left's _Tidy inlines here while the literal string assign stays out of line.
// STUB: GAME 0x00539530
RHMenuPopupScroll::RHMenuPopupScroll(RHMenuScreenView *screen, const std::wstring &text, const std::string &title, int flags)
    : RHMenuWindowFocus(0, screen, 0x93, 0, false), m_resource(0), m_message(text), m_450(0), m_flags(flags)
{
    if (title.size() == 0)
        m_resource = screen->FUN_0053be80(std::string("PopupScroll"));
    else
        m_resource = screen->FUN_0053be80(title);
}

// FUNCTION: GAME 0x00539710
void *RHMenuPopupScroll::FUN_00539710(unsigned flags)
{
    this->~RHMenuPopupScroll();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00539730
RHMenuPopupScroll::RHMenuPopupScroll(RHMenuScreenView *screen, const std::wstring &text, int id, const std::string &title, int flags)
    : RHMenuWindowFocus(0, screen, 0x93, 0, false),
      m_resource(screen->FUN_0053be80(std::string("PopupScroll"))),
      m_message(text),
      m_450(FUN_0053a610(id)),
      m_flags(flags)
{
    if (title.size() == 0)
        m_resource = screen->FUN_0053be80(std::string("PopupScroll"));
    else
        m_resource = screen->FUN_0053be80(title);
}

// FUNCTION: GAME 0x00539980
RHMenuPopupScroll::~RHMenuPopupScroll()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_ok);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_title);
    if (m_450 != 0)
        ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_text);
}

extern wchar_t g_unk0x006c0b50[1];
std::wstring FUN_005e23d0(unsigned long);

inline void RHPopupScrollSetText(RHPortraitButton &button, const std::wstring &text)
{
    button.m_08 = true;
    button.m_20 = text;
}

inline void RHPopupScrollInsert(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

// FUNCTION: GAME 0x00539b30
bool RHMenuPopupScroll::FUN_00539b30()
{
    if (((RHMenuWindow *)this)->FUN_00544b40(g_unk0x006c0b50, RHMapBox(0.0f, 0.0f, 496.0f, 463.0f), 0))
    {
        void *resource = m_resource;
        std::vector<void *> widgets;
        m_ok.FUN_005d1e30((int)m_screen, g_unk0x006c0b50, 0x91);
        RHPopupScrollSetText(m_ok, FUN_005e23d0(0x14c));
        ((RHMapWidget *)&m_title)->V30(m_message, RHMapBox(50.0f, 50.0f, 450.0f, 375.0f), 0, unsigned(-1));
        RHUnk005cba10 &renderer = m_title.m_renderer;
        ((SBUIUnk0060dd00 *)&renderer)->FUN_0060e0d0(resource, resource, resource, resource);
        m_title.m_renderer.SetM60(m_flags);
        ((RHMenuCampaignMap *)this)->V30(&m_ok);
        ((RHMenuCampaignMap *)this)->V30(&m_title);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, false);
        RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, 0x1c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, 0x9c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, 1);
        ((RHUnk005d92c0Sub *)&m_ok)->v08(SBGeoPoint2D(0.0f, 380.0f));
        RHPopupScrollInsert(widgets, &m_ok);
        ((RHMenuWindow *)this)->FUN_005449e0(widgets, 0);
        if (m_450 != 0)
        {
            ((RHMapWidget *)&m_text)->V30(g_unk0x006c0b50, RHMapBox(50.0f, 50.0f, 50.0f, 50.0f), 0, m_450);
            ((RHMenuCampaignMap *)this)->V30(&m_text);
            ((RHUnk005d92c0Sub *)&m_text)->v08(SBGeoPoint2D(446.0f, 50.0f).FUN_005fc200(SBGeoVector2D(m_text.Box().Width(), 0.0f)));
            renderer.FUN_005cb9d0((int)(m_text.Box().Width() + 20.0f), (int)(m_text.Box().Height() + 15.0f));
            focus.FUN_004ffd20(&m_text);
        }
        return true;
    }
    return false;
}

extern RHUnk0048a970 *g_unk0x6c0b3c;

// GLOBAL: GAME 0x006b0f8c
unsigned long g_unk0x006b0f8c = 0xffffffff;

// FUNCTION: GAME 0x0053a000
void RHMenuPopupScroll::FUN_0053a000(void *text, void *title, int flag)
{
    bool paused = FUN_0053a840();
    RHMenuScreenView screen(0, 0, paused, paused, (char *)g_unk0x6c0b3c + 0x68);
    screen.FUN_0053be40(0);
    FUN_0053a380(&screen, *(const std::wstring *)text, *(const std::string *)title, flag);
}

// FUNCTION: GAME 0x0053a0b0
void RHMenuPopupScroll::FUN_0053a0b0(int id)
{
    bool paused = FUN_0053a840();
    RHMenuScreenView screen(0, 0, paused, paused, (char *)g_unk0x6c0b3c + 0x68);
    screen.FUN_0053be40(0);
    FUN_0053a4c0(&screen, id, std::string(), 4);
}

// FUNCTION: GAME 0x0053a1d0
void RHMenuPopupScroll::FUN_0053a1d0(const std::vector<int> &ids)
{
    RHMenuScreenView screen(0, 0, FUN_0053a840(), FUN_0053a840(), (char *)g_unk0x6c0b3c + 0x68);
    screen.FUN_0053be40(0);
    for (const int *id = ids.begin(); id != ids.end(); ++id)
        FUN_0053a4c0(&screen, *id, std::string(), 4);
}

// FUNCTION: GAME 0x0053a380
void RHMenuPopupScroll::FUN_0053a380(RHMenuScreenView *screen, const std::wstring &message, const std::string &title, int flag)
{
    std::wstring text(message);
    while (text.length() != 0) {
        RHMenuPopupScroll menu(screen, text, title, flag);
        menu.FUN_00539b30();
        menu.FUN_00544b80(true, true);
        const std::wstring &next = menu.FUN_0053a820();
        typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
        Assign assign = &std::wstring::assign;
        (text.*assign)(next, 0, std::wstring::npos);
    }
    g_unk0x006b0f8c = *(unsigned long *)((char *)g_pEngine + 0x4a94);
}

// FUNCTION: GAME 0x0053a4c0
void RHMenuPopupScroll::FUN_0053a4c0(RHMenuScreenView *screen, int id, const std::string &title, int flags)
{
    std::wstring text = FUN_0053a660(id);
    while (text.length() != 0) {
        RHMenuPopupScroll menu(screen, text, id, title, flags);
        menu.FUN_00539b30();
        menu.FUN_00544b80(true, true);
        const std::wstring &next = menu.FUN_0053a820();
        typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
        Assign assign = &std::wstring::assign;
        (text.*assign)(next, 0, std::wstring::npos);
    }
    g_unk0x006b0f8c = *(unsigned long *)((char *)g_pEngine + 0x4a94);
}

struct RHPopupScrollSet
{
    undefined m_00[0x20];
    int *m_first;
    int *m_last;
};

// FUNCTION: GAME 0x0053a2d0
void RHMenuPopupScroll::FUN_0053a2d0()
{
    RHPopupScrollSet *set = (RHPopupScrollSet *)g_pEngine->GetDynResources(0);
    std::vector<int> ids;
    for (int id = 0; id != (set->m_first == 0 ? 0 : set->m_last - set->m_first); ++id)
        ((SBArray<RHSaveGame *> *)&ids)->Insert((RHSaveGame **)ids.end(), 1, (RHSaveGame *const &)id);
    FUN_0053a1d0(ids);
}

#include "SBResourceManager.h"

extern RHMapResources *g_unk0x006c1840;

// FUNCTION: GAME 0x0053a5f0
unsigned long RHMenuPopupScroll::FUN_0053a5f0()
{
    return (char)((SBResourceManager *)g_unk0x006c1840)->FUN_00600f10(0xa4) ? 0xa4 : 0;
}

// Parked: the out-of-range array reload allocates EDX/EAX in the opposite order.
// STUB: GAME 0x0053a610
unsigned long RHMenuPopupScroll::FUN_0053a610(unsigned long index)
{
    RHPopupScrollSet *set = (RHPopupScrollSet *)g_pEngine->GetDynResources(0);
    SBResourceManager *manager = (SBResourceManager *)g_unk0x006c1840;
    if (set != 0)
    {
        std::vector<int> &ids = *(std::vector<int> *)((char *)set + 0x1c);
        if (index < ids.size())
            return *(set->m_first + index);
        manager->FUN_00600f10(*(ids.begin() + index));
    }
    return FUN_0053a5f0();
}

void RHMenuPopupScrollEmitPictures(unsigned long index)
{
    RHMenuPopupScroll::FUN_0053a610(index);
}

// FUNCTION: GAME 0x0053a820
const std::wstring &RHMenuPopupScroll::FUN_0053a820()
{
    return *(const std::wstring *)((char *)this + 0x440);
}

// FUNCTION: GAME 0x0053a830
void FUN_0053a830()
{
    g_unk0x006b0f8c = 0xffffffff;
}

// FUNCTION: GAME 0x0053a840
bool RHMenuPopupScroll::FUN_0053a840()
{
    if (*(unsigned long *)((char *)g_pEngine + 0x4a94) == g_unk0x006b0f8c)
        return false;
    return true;
}

#include "RHSectorProductionCampaign.h"
#include "RHGameMenuCalls.h"

// FUNCTION: GAME 0x0053a860
bool RHMenuPopupScroll::FUN_0053a860(int, void *, void *)
{
    *(std::wstring *)((char *)this + 0x440) =
        *(const std::wstring *)((RHSectorProductionCampaign *)((char *)this + 0x2c4))->FUN_005cb6f0();
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}
