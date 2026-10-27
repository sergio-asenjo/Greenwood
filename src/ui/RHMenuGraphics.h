// RHMenuGraphics — declarations for RHMenuGraphics.cpp (decompiled TU).
//
// BINDING (0x0052d090 -> RHMenuGraphics::SynchronizeWidgets()):
//   - TU:     rhmenugraphics.cpp (embedded __FILE__ 0x006b0d5c,
//             symbols/functions-by-file.tsv:129).
//   - Class:  RHMenuGraphics (symbols/oracle-correlation.tsv:
//             rhmenugraphics -> class RHMenuGraphics, 17 methods).
//   - Method: the Mac map has exactly one rhmenugraphics.cpp method,
//             SynchronizeWidgets (symbols/mac-functions-by-file.tsv:127), and
//             symbols/mac-RH.txt:2825 gives RHMenuGraphics::SynchronizeWidgets().
//   - Signal: `this` arrives in ecx with no stack argument and the function ends
//             in a plain `ret` (__thiscall void). Its body reads the screen
//             width at +0xdc0, dispatches on 640/800/1024 and toggles the
//             enable state of seven widget sub-objects — a per-resolution
//             widget synchroniser, i.e. SynchronizeWidgets.
//
// Member layout is derived from the target instructions of
// RHMenuGraphics::SynchronizeWidgets (0x0052d090): a float screen width at
// +0xdc0, four bool flags at +0xdbd/+0xdbe/+0xdbf/+0xdbc, and seven widget
// sub-objects (bases derived from their SetEnable field accesses below).
// Everything else is opaque padding; the offsets are exact because they are
// reached through aliases rather than laid-out members.

#include "SB.h"

// The widget base class. Its Windows-side identity is unproven (no __FILE__,
// tag or string names it), so the class stays provisional. The Mac oracle
// exposes SBWidgetButton<T>::SetEnable(bool) with the same enable/disable
// state machine (symbols/mac-RH.txt:6606 etc.), but a cross-binary name match
// is not accepted as evidence (docs/05-naming.md), so the class is named by the
// address of its out-of-line SetEnable copy in Game.exe: 0x0052d2c0.
//
// Layout from 0x0052d2c0:
//   +0x4c  int   m_unk4c    reset value written on disable
//   +0x7c  int   m_unk7c    state (5/8 enable transitions, 6/9, 8/5, 9/6)
//   +0xd8  bool  m_enabled  enabled flag
#include "RHButtonSelection.h"

#include "RHMenuWindow.h"
#include "RHGameTitleLifetimeInline.h"
#include "RHPortraitLinkedLifetimeView.h"
#include "RHPortraitRadioLifetimeView.h"
#include "../engine/RHGraphicConfigClass.h"

class RHMenuScreenView;

// VTABLE: GAME 0x00679468
// SIZE 0xdcc
class RHMenuGraphics : public RHMenuWindowFocus
{
public:
    RHMenuGraphics(RHMenuScreenView *screen);
    ~RHMenuGraphics();
    void *FUN_0052c3a0(unsigned flags);
    bool Create();
    static bool Display(void *ui);
    bool FUN_0052ce70() const;
    void RouteEvent(struct RHMenuEvent *event);
    bool HandleEvent(struct RHMenuEvent *event);
    bool OnOK(int message, void *widget, void *data);
    bool OnOption(int message, void *widget, void *data);
    bool OnScreen(int message, void *widget, void *data);
    void SynchronizeWidgets();

    void Emit();

    RHGameLifetime00525560 m_label140; // 0x140
    RHGameLifetime00525560 m_label240; // 0x240
    RHGameLifetime00525560 m_label340; // 0x340
    RHPortraitButton m_ok; // 0x440
    RHPortraitButton m_cancel; // 0x540
    RHPortraitLinkedLifetime m_screens[3]; // 0x640
    RHPortraitRadioLifetime m_options[4]; // 0x97c
    RHGraphicConfig m_config; // 0xdbc
    bool m_dc8; // 0xdc8
};

// Screen width in pixels (target `fld DWORD PTR [esi+0xdc0]`).
#define m_screenWidth (*(float *)((char *)this + 0xdc0))

// The seven widget sub-objects. Bases are derived from SetEnable's field
// accesses: for a widget base B, its state is at B+0x7c, its reset value at
// B+0x4c and its enabled flag at B+0xd8.
//   m_widget640  B=0x640 (state 0x6bc, flag 0x718) — enabled when width==640
//   m_widget800  B=0x754 (state 0x7d0, flag 0x82c) — enabled when width==800
//   m_widget1024 B=0x868 (state 0x8e4, flag 0x940) — enabled when width==1024
//   m_widgetA    B=0x97c (state 0x9f8, flag 0xa54, reset 0x9c8)
//   m_widgetB    B=0xa8c (state 0xb08, flag 0xb64, reset 0xad8)
//   m_widgetC    B=0xb9c (out-of-line call)
//   m_widgetD    B=0xcac (out-of-line call)
#define m_widget640  (*(RHUnk0052d2c0 *)((char *)this + 0x640))
#define m_widget800  (*(RHUnk0052d2c0 *)((char *)this + 0x754))
#define m_widget1024 (*(RHUnk0052d2c0 *)((char *)this + 0x868))
#define m_widgetA    (*(RHUnk0052d2c0 *)((char *)this + 0x97c))
#define m_widgetB    (*(RHUnk0052d2c0 *)((char *)this + 0xa8c))
#define m_widgetC    (*(RHUnk0052d2c0 *)((char *)this + 0xb9c))
#define m_widgetD    (*(RHUnk0052d2c0 *)((char *)this + 0xcac))

// Per-widget selection flags read by SynchronizeWidgets. They are bool members
// on the target (the calls pass them without a setne conversion).
#define m_flagDBE (*(bool *)((char *)this + 0xdbe))
#define m_flagDBD (*(bool *)((char *)this + 0xdbd))
#define m_flagDBF (*(bool *)((char *)this + 0xdbf))
#define m_flagDBC (*(bool *)((char *)this + 0xdbc))
