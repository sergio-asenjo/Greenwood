// RHMenuGraphics.cpp — translation unit with __FILE__ evidence at 0x0052d090
// ("P:\Robin Hood\RHMenuGraphics.cpp", symbols/functions-by-file.tsv:129).
//
// BINDING (0x0052d090 -> RHMenuGraphics::SynchronizeWidgets()):
//   - TU:     rhmenugraphics.cpp (__FILE__ 0x006b0d5c).
//   - Class:  RHMenuGraphics (symbols/oracle-correlation.tsv).
//   - Method: the single rhmenugraphics.cpp method in the Mac map
//             (symbols/mac-functions-by-file.tsv:127 -> SynchronizeWidgets;
//             symbols/mac-RH.txt:2825 RHMenuGraphics::SynchronizeWidgets()).
//   - Signal: `this` in ecx, no stack argument, plain `ret` => __thiscall void.
//             The body converts the screen width at +0xdc0 to int, switches on
//             640/800/1024 (asserting "Warning, unknown screen resolution."
//             otherwise) and re-synchronises seven widget enable states.
//
// STATUS: exact 100% — instruction-for-instruction identical to the original.
//
// CODEGEN (why the widget helper is an inline method, not a stub):
//   The five `SetEnable(true)`/bool-flag sites are expanded inline while the
//   last two (m_widgetC/m_widgetD) are emitted as calls to the out-of-line copy
//   at 0x0052d2c0. Defining SetEnable in the class body reproduces exactly that
//   split: VC6 inlines five sites and emits the sixth/seventh as calls, the
//   out-of-line copy landing adjacent to SynchronizeWidgets as in the original.

#include "SBNullstr.h"
#include "RHMenuGraphics.h"
#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2D.h"
#endif

#include "RHMenuCancelCalls.h"

extern unsigned char g_unk0x006c0e48[];

template<class T>
static T &RHGraphicsField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

// FUNCTION: GAME 0x0052c030
void RHMenuGraphics::RouteEvent(RHMenuEvent *event)
{
    if (HandleEvent(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x0052c050
bool RHMenuGraphics::HandleEvent(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x540)
        handled = ((RHMenuCancelCalls *)this)->OnCancel(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x440)
        handled = OnOK(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_widget640)
        handled = OnScreen(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_widget800)
        handled = OnScreen(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_widget1024)
        handled = OnScreen(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_widgetA)
        handled = OnOption(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_widgetB)
        handled = OnOption(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_widgetC)
        handled = OnOption(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == &m_widgetD)
        handled = OnOption(2, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_widgetA)
        handled = OnOption(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_widgetB)
        handled = OnOption(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_widgetC)
        handled = OnOption(7, event->m_widget, event->m_data);
    if (event->m_type == 7 && event->m_widget == &m_widgetD)
        handled = OnOption(7, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x0052c220
RHMenuGraphics::RHMenuGraphics(RHMenuScreenView *screen)
    : RHMenuWindowFocus(0, screen, 0, false),
      m_config(*(const RHGraphicConfig *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x50)),
      m_dc8(false)
{
}

// FUNCTION: GAME 0x0052c3a0
void *RHMenuGraphics::FUN_0052c3a0(unsigned flags)
{
    this->~RHMenuGraphics();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0052c3c0
RHMenuGraphics::~RHMenuGraphics()
{
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_label140);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_label240);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_label340);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_ok);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_cancel);
    for (int i = 0; i < 3; i++)
        ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_screens[i]);
    for (int j = 0; j < 4; j++)
        ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_options[j]);
}

#include "RHMenuScreenView.h"

#include "RHMapWidget.h"
#include "RHMenuCampaignMapClass.h"
#include "RHSaveGameManager.h"
#include "RHPortraitUnk005d3880.h"

extern wchar_t g_unk0x006c0b50[1];
std::wstring FUN_005e23d0(unsigned long);

inline void RHGraphicsInsert(std::vector<void *> &widgets, void *const &widget)
{
    ((SBArray<RHSaveGame *> *)&widgets)->Insert((RHSaveGame **)widgets.end(), 1, (RHSaveGame *const &)widget);
}

// FUNCTION: GAME 0x0052c5b0
bool RHMenuGraphics::Create()
{
    if (((RHMenuWindow *)this)->FUN_00544b40(g_unk0x006c0b50, RHMapBox(0.0f, 0.0f, 640.0f, 480.0f), 0))
    {
        void *title = m_screen->FUN_0053be80(std::string("MissionTitle"));
        void *normal = m_screen->FUN_0053be80(std::string(
            // STRING: GAME 0x006b0994
            "Default"));
        void *edit = m_screen->FUN_0053be80(std::string("EditField"));
        std::vector<void *> widgets;
        ((RHMapWidget *)&m_label140)->V30(FUN_005e23d0(0x1c), RHMapBox(0.0f, 0.0f, 490.0f, 480.0f), 0, unsigned(-1));
        ((SBUIUnk0060dd00 *)&m_label140.m_renderer)->FUN_0060e0d0(title, title, title, title);
        ((RHMenuCampaignMap *)this)->V30(&m_label140);
        ((RHMapWidget *)&m_label240)->V30(FUN_005e23d0(0x2a), RHMapBox(0.0f, 80.0f, 490.0f, 480.0f), 0, unsigned(-1));
        ((SBUIUnk0060dd00 *)&m_label240.m_renderer)->FUN_0060e0d0(normal, normal, normal, normal);
        ((RHMenuCampaignMap *)this)->V30(&m_label240);
        ((RHMapWidget *)&m_label340)->V30(FUN_005e23d0(0x2e), RHMapBox(0.0f, 230.0f, 490.0f, 480.0f), 0, unsigned(-1));
        ((SBUIUnk0060dd00 *)&m_label340.m_renderer)->FUN_0060e0d0(normal, normal, normal, normal);
        ((RHMenuCampaignMap *)this)->V30(&m_label340);
        m_ok.FUN_005d1e30((int)m_screen, FUN_005e23d0(0xf), 0xbe);
        m_cancel.FUN_005d1e30((int)m_screen, FUN_005e23d0(0x10), 0xbe);
        RHGraphicsInsert(widgets, &m_ok);
        RHGraphicsInsert(widgets, &m_cancel);
        ((RHMenuCampaignMap *)this)->V30(&m_ok);
        ((RHMenuCampaignMap *)this)->V30(&m_cancel);
        ((RHFocusManager *)((char *)this + 0xc8))->FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, true);
        RHFocusManager &focus = *(RHFocusManager *)((char *)this + 0xc8);
        focus.FUN_004ffc70((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, true);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, 0x1c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_ok, 0x9c);
        focus.FUN_004ffce0((RHFocusGroupableView *)(RHPortraitButtonStrategy *)&m_cancel, 1);
        ((RHMenuWindow *)this)->FUN_00544380(widgets, 2);
        widgets.erase(widgets.begin(), widgets.end());
        for (unsigned long i = 0; i != 3; ++i)
        {
            ((RHPortraitUnk005d3880 *)&m_screens[i])->FUN_005d4bb0((int)m_screen, FUN_005e23d0(i + 0x2b), SBGeoPoint2D(30.0f, 100.0f), 0xbf);
            ((RHPortraitUnk005d3880 *)&m_screens[i])->FUN_005d3ab0((RHPortraitUnk005d3880 *)&m_screens[(i + 1) % 3]);
            *(void **)((char *)&m_screens[i] + 0xd0) = edit;
            RHGraphicsInsert(widgets, &m_screens[i]);
            ((RHMenuCampaignMap *)this)->V30(&m_screens[i]);
        }
        ((RHMenuWindow *)this)->FUN_00544800(widgets, 2);
        widgets.erase(widgets.begin(), widgets.end());
        for (int j = 0; j != 4; ++j)
        {
            ((RHPortraitUnk005d3880 *)&m_options[j])->FUN_005d4bb0((int)m_screen, FUN_005e23d0(j + 0x2f), SBGeoPoint2D(30.0f, 250.0f), 0xbf);
            *(void **)((char *)&m_options[j] + 0xd0) = edit;
            RHGraphicsInsert(widgets, &m_options[j]);
            ((RHMenuCampaignMap *)this)->V30(&m_options[j]);
        }
        ((RHMenuWindow *)this)->FUN_00544800(widgets, 2);
        widgets.erase(widgets.begin(), widgets.end());
        SynchronizeWidgets();
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x0052cda0
bool RHMenuGraphics::Display(void *ui)
{
    RHMenuScreenView screen(0, 0xba, 0, ui);
    RHMenuGraphics menu(&screen);
    menu.Create();
    ((RHMenuWindow *)&menu)->FUN_00544b80(true, true);
    return menu.FUN_0052ce70();
}

// FUNCTION: GAME 0x0052ce70
bool RHMenuGraphics::FUN_0052ce70() const
{
    return RHGraphicsField<bool>((void *)this, 0xdc8);
}

// FUNCTION: GAME 0x0052ce80
bool RHMenuCancelCalls::OnCancel(int, void *, void *)
{
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return false;
}

// FUNCTION: GAME 0x0052ce90
bool RHMenuGraphics::OnOK(int, void *, void *)
{
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    if (RHGraphicsField<bool>(this, 0xdc8))
    {
        char *settings = ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x50;
        settings[0] = m_flagDBC;
        settings[1] = m_flagDBD;
        settings[2] = m_flagDBE;
        settings[3] = m_flagDBF;
        ((SBGeoVector2D *)(settings + 4))->operator=(RHGraphicsField<SBGeoVector2D>(this, 0xdc0));
    }
    return false;
}

// FUNCTION: GAME 0x0052cee0
bool RHMenuGraphics::OnOption(int, void *widget, void *)
{
    if (widget == &m_widgetA)
    {
        RHGraphicsField<bool>(this, 0xdc8) = true;
        m_flagDBE = !m_widgetA.m_enabled;
        return false;
    }
    if (widget == &m_widgetB)
    {
        RHGraphicsField<bool>(this, 0xdc8) = true;
        m_flagDBD = m_widgetB.m_enabled;
        return false;
    }
    if (widget == &m_widgetC)
    {
        RHGraphicsField<bool>(this, 0xdc8) = true;
        m_flagDBF = m_widgetC.m_enabled;
        return false;
    }
    if (widget == &m_widgetD)
    {
        RHGraphicsField<bool>(this, 0xdc8) = true;
        m_flagDBC = m_widgetD.m_enabled;
    }
    return false;
}

// FUNCTION: GAME 0x0052cf80
bool RHMenuGraphics::OnScreen(int, void *widget, void *)
{
    if (widget == &m_widget640)
    {
        RHGraphicsField<bool>(this, 0xdc8) = true;
        ((SBGeoVector2D *)((char *)this + 0xdc0))->operator=(SBGeoVector2D(640.0f, 480.0f));
    }
    else if (widget == &m_widget800)
    {
        RHGraphicsField<bool>(this, 0xdc8) = true;
        ((SBGeoVector2D *)((char *)this + 0xdc0))->operator=(SBGeoVector2D(800.0f, 600.0f));
    }
    else if (widget == &m_widget1024)
    {
        RHGraphicsField<bool>(this, 0xdc8) = true;
        ((SBGeoVector2D *)((char *)this + 0xdc0))->operator=(SBGeoVector2D(1024.0f, 768.0f));
    }
    return false;
}

// FUNCTION: GAME 0x0052d090
void RHMenuGraphics::SynchronizeWidgets()
{
    int width = (int)m_screenWidth;

    switch (width)
    {
    case 640:
        m_widget640.SetEnable(true);
        break;

    case 800:
        m_widget800.SetEnable(true);
        break;

    case 1024:
        m_widget1024.SetEnable(true);
        break;

    default:
        SBAssert(0,
                 // STRING: GAME 0x6b0d5c
                 "P:\\Robin Hood\\RHMenuGraphics.cpp",
                 338,
                 // STRING: GAME 0x6b0d80
                 "Warning, unknown screen resolution.");
        break;
    }

    m_widgetA.SetEnable(m_flagDBE == false);
    m_widgetB.SetEnable(m_flagDBD);
    m_widgetC.SetEnable(m_flagDBF);
    m_widgetD.SetEnable(m_flagDBC);
}

// Force emission: an unreferenced non-virtual member is dropped by VC6, so an
// out-of-line call from a global instance keeps SynchronizeWidgets in the build.
void RHMenuGraphics::Emit()
{
    RouteEvent(0);
    OnOK(0, 0, 0);
    OnOption(0, 0, 0);
    OnScreen(0, 0, 0);
    SynchronizeWidgets();
    Display(0);
}

RHMenuGraphics *g_rhMenuGraphics;

void rh_menugraphics_emit()
{
    g_rhMenuGraphics->Emit();
}
