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
#include "SBGeoBoundingBox2D.h"

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

class RHGameMenuCalls
{
public:
    void FUN_00544b30();
};

class RHMenuSounds
{
public:
    bool FUN_0052ce80(int, void *, void *);
};

class RHUnk0055dbb0
{
public:
    char *FUN_0055dbb0();
};

class RHUnk005fc3b0
{
public:
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &);
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
};

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
    if (event->m_type == 2 && event->m_widget == m_bytes + 0x540)
        handled = ((RHMenuSounds *)this)->FUN_0052ce80(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == m_bytes + 0x440)
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

class RHMenuScreenView
{
public:
    RHMenuScreenView(unsigned long flags, long background, unsigned short color, void *ui);
    ~RHMenuScreenView();
    unsigned char m_bytes[0x1990];
};

class RHMenuWindowFocus
{
public:
    void FUN_00544b80(bool, bool);
};

// FUNCTION: GAME 0x0052cda0
bool RHMenuGraphics::Display(void *ui)
{
    RHMenuScreenView screen(0, 0xba, 0, ui);
    RHMenuGraphics menu(&screen);
    menu.Create();
    ((RHMenuWindowFocus *)&menu)->FUN_00544b80(true, true);
    return menu.FUN_0052ce70();
}

// FUNCTION: GAME 0x0052ce70
bool RHMenuGraphics::FUN_0052ce70() const
{
    return RHGraphicsField<bool>((void *)this, 0xdc8);
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
        ((RHUnk005fc3b0 *)(settings + 4))->FUN_005fc430(RHGraphicsField<SBGeoPoint2D>(this, 0xdc0));
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
        ((RHUnk005fc3b0 *)((char *)this + 0xdc0))->FUN_005fc430(SBGeoVector2D(640.0f, 480.0f));
    }
    else if (widget == &m_widget800)
    {
        RHGraphicsField<bool>(this, 0xdc8) = true;
        ((RHUnk005fc3b0 *)((char *)this + 0xdc0))->FUN_005fc430(SBGeoVector2D(800.0f, 600.0f));
    }
    else if (widget == &m_widget1024)
    {
        RHGraphicsField<bool>(this, 0xdc8) = true;
        ((RHUnk005fc3b0 *)((char *)this + 0xdc0))->FUN_005fc430(SBGeoVector2D(1024.0f, 768.0f));
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
