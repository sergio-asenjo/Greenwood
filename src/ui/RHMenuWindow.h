// RHMenuWindow — declarations for RHMenuWindow.cpp (decompiled TU).
//
// BINDING: the code run 0x00543e70..0x00544bcb is bracketed by per-TU
// <iostream> init glue (0x00543df0 / 0x00544bd0 groups) and holds the class
// whose vtable is 0x00679a28: slot 0 is the deleting destructor 0x00543f80,
// slot 1 the Create forwarder 0x00544b40, and 0x00544b30 forwards `this` to the
// screen's CloseWindow. The two constructors match the Mac oracle's
// RHMenuWindow(RHMenuWindow*, RHMenuScreen*, bool) (0x00543e70, ret 0xc) and
// RHMenuWindow(RHMenuWindow*, RHMenuScreen*, long, bool) (0x00543fa0, ret 0x10)
// argument shapes (symbols/mac-RH.txt:3041/3042).
//
// Layout (from 0x00543e70 / 0x005442b0 / 0x00544300):
//   +0x00..+0xb0  RHPortraitRootList base (vptr 0x00678ea8, dtor 0x005df0e0)
//   +0x8c         resource owner released through 0x005fd4a0
//   +0xb0         draw manager (global 0x006c11d0)
//   +0xb4         owning screen
//   +0xb8         parent window
//   +0xbc         resource id
//   +0xc0         save surface (-1 when none)
//   +0xc4         resource-held flag

#ifndef RHMENUWINDOW_H
#define RHMENUWINDOW_H

#include "SB.h"
#include "Decomp.h"
#include "RHWidgetPortrait.h"
#include "../engine/SBUIRenderer.h"
#include <vector>

class RHPortraitRootList : public RHPortraitRootLifetime
{
public:
    RHPortraitRootList() { m_vptr = 0x00678ea8; }
    ~RHPortraitRootList();
    std::vector<RHUnk005d92c0Sub *> m_items; // 0xa0
};

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int, int, int, int);
    void Unk005e5160(unsigned long);
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
    void FUN_005e6440(unsigned long, int, int, unsigned long, unsigned long);
};

// SIZE 0x17f8
class RHMenuWindowUI
{
public:
    undefined m_00[0x17ec]; // 0x00
    unsigned long m_17ec; // 0x17ec
    void *m_17f0; // 0x17f0
    void *m_17f4; // 0x17f4
};

class RHMenuWindow;

class RHMenuWindowScreen
{
public:
    void FUN_0053bb80(RHMenuWindow *window, bool display, bool modal);
    RHMenuWindowUI *FUN_0053bf30();
};

// SIZE 0xc8
class RHMenuWindow : public RHPortraitRootList
{
public:
    RHMenuWindow(RHMenuWindow *parent, RHMenuWindowScreen *screen, bool saveBackground);
    ~RHMenuWindow();
    void *FUN_00543f80(unsigned flags);
    void FUN_00544300();
    void FUN_00544b80(bool display, bool modal);

    RHUnkFXDraw *m_draw; // 0xb0
    RHMenuWindowScreen *m_screen; // 0xb4
    RHMenuWindow *m_parent; // 0xb8
    long m_resource; // 0xbc
    unsigned long m_saveSurface; // 0xc0
    bool m_resourceHeld; // 0xc4
};

// Base of the focus-managed menus (code 0x00544c50.., outside this TU).
// SIZE 0x140
class RHMenuWindowFocus
{
public:
    RHMenuWindowFocus(RHMenuWindow *parent, void *screen, int orientation, bool wrap);
    RHMenuWindowFocus(RHMenuWindow *parent, void *screen, long resource, int orientation, bool wrap);
    ~RHMenuWindowFocus();
    void FUN_00544b80(bool display, bool modal) { ((RHMenuWindow *)this)->FUN_00544b80(display, modal); }

    unsigned m_vptr; // 0x00
    undefined m_04[0xb0]; // 0x04
    RHMenuWindowScreen *m_screen; // 0xb4
    undefined m_b8[0x88]; // 0xb8
};

// SIZE 0x100
class RHPortraitButton
{
public:
    RHPortraitButton();
    ~RHPortraitButton();
    void SetEnabled(bool enabled) { m_enabled = enabled; }

    undefined m_00[4]; // 0x00
    bool m_enabled; // 0x04
    undefined m_05[0xfb]; // 0x05
};

// SIZE 0x1a4
class RHPortraitEditableWidget
{
public:
    RHPortraitEditableWidget();
    ~RHPortraitEditableWidget();
    bool IsSelected() const { return m_state == 4 || m_state == 2 || m_state == 1 || m_state == 13; }

    undefined m_00[0x7c]; // 0x00
    int m_state; // 0x7c
    undefined m_80[0x124]; // 0x80
};

struct RHMenuEvent;

// SIZE 0x448
class RHMenuYesNo : public RHMenuWindow
{
public:
    RHMenuYesNo(RHMenuWindowScreen *screen, const std::wstring &text);
    ~RHMenuYesNo();
    void HandleEvent(RHMenuEvent *event);
    bool RouteEvent(RHMenuEvent *event);
    void *FUN_00545590(unsigned flags);
    void FUN_00545710();
    int FUN_00545ad0();
    bool OnNo(int message, void *widget, void *data);
    bool OnYes(int message, void *widget, void *data);
    static bool AskForConfirmation(RHMenuWindowScreen *screen, const std::wstring &text);

    undefined m_c8[0x380]; // 0xc8
};

// SIZE 0x8
class RHMenuResolution : public SBGeoPoint2D
{
public:
    RHMenuResolution(const SBGeoPoint2D &other);
};

// SIZE 0x8
struct RHMenuLoadSaveResult
{
    RHMenuLoadSaveResult() { ((SBGeoPoint2D *)this)->SBGeoPoint2D::SBGeoPoint2D(); }
    int m_choice; // 0x00
    int m_slot; // 0x04
};

// SIZE 0xc
struct RHMenuEvent
{
    int m_type; // 0x00
    void *m_widget; // 0x04
    void *m_data; // 0x08
};

class RHUnk0048a970
{
public:
    void Unk(int);
};

#define m_resourceOwner (*(SBUIUnk005fd4a0 **)((char *)this + 0x8c))

#endif
