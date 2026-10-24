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
#include "RHMenuScreenView.h"
#include "RHWidgetPortrait.h"
#include "../engine/SBUIRenderer.h"
#include <vector>

#include "RHPortraitRootList.h"

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

#include "RHPortraitDrawCalls.h"

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

#include "RHMenuWindowClass.h"

// Base of the focus-managed menus (code 0x00544c50.., outside this TU).
// SIZE 0x140
#include "RHMenuFocusClass.h"

// SIZE 0x100

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

#include "RHGameWidgetLifetime.h"

// VTABLE: GAME 0x00679ad8
// SIZE 0x448
class RHMenuYesNo : public RHMenuWindowFocus
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

    undefined m_140[4]; // 0x140
    RHGameLifetime00525880 m_144; // 0x144
    undefined m_240[4]; // 0x240
    RHPortraitButton m_244; // 0x244
    RHPortraitButton m_344; // 0x344
    undefined m_444[4]; // 0x444
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
