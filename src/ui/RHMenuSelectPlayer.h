// RHMenuSelectPlayer — declarations for RHMenuSelectPlayer.cpp (decompiled TU).
//
// BINDING: the code run 0x0053e480..0x0053fa44 sits between two per-TU
// <iostream> init glue groups (0x0053e400 / 0x0053fa50) and owns the vtable
// 0x00679890 (deleting dtor 0x0053e8b0, RouteEvent 0x0053e480). The class
// keeps ten 0x1a4-byte profile entries at +0x540 and the player profile
// manager (global 0x006c0e48) at +0x15a8, matching the Mac oracle's
// RHMenuSelectPlayer (InitializeProfiles / GetSelectedProfileIndex /
// UpdateButtonState, symbols/mac-RH.txt:2979-2994).
//
// Layout (from 0x0053e7f0 / 0x0053efe0 / 0x0053f9a0):
//   +0x140/+0x240/+0x340/+0x440  0x100-byte buttons, enable flag at +4
//   +0x540                       ten 0x1a4-byte profile entries, state at +0x7c
//   +0x15a8                      RHPlayerProfileManager *

#ifndef RHMENUSELECTPLAYER_H
#define RHMENUSELECTPLAYER_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"

class RHMenuSelectPlayerProfiles : public RHPlayerProfileManager
{
public:
    void FUN_0055d930(unsigned long index);
    void FUN_0055e410(unsigned long index);

    undefined m_00[0xc]; // 0x00
    unsigned m_count; // 0x0c
};

// SIZE 0x160
class RHMenuSelectPlayerWidget
{
public:
    void FUN_0053f9f0(RHMenuSelectPlayerWidget *stop);

    undefined m_00[0x7c]; // 0x00
    int m_state; // 0x7c
    undefined m_80[0x90]; // 0x80
    undefined m_110[0x48]; // 0x110
    RHMenuSelectPlayerWidget *m_parent; // 0x158
    undefined m_15c[4]; // 0x15c
};

// SIZE 0x15ac
class RHMenuSelectPlayer : public RHMenuWindowFocus
{
public:
    RHMenuSelectPlayer(void *screen);
    ~RHMenuSelectPlayer();
    void FUN_0053e480(RHMenuEvent *event);
    bool FUN_0053e4a0(RHMenuEvent *event);
    void *FUN_0053e8b0(unsigned flags);
    void FUN_0053e9e0();
    static void FUN_0053ede0(void *ui);
    int FUN_0053efe0();
    bool FUN_0053f690(int msg, void *widget, void *data);
    void FUN_0053f040();
    bool FUN_0053f2a0(int msg, void *widget, void *data);
    bool FUN_0053f390(int msg, void *widget, void *data);
    bool FUN_0053f410(int msg, void *widget, void *data);
    bool FUN_0053f620(int msg, void *widget, void *data);
    bool FUN_0053f6d0(int msg, void *widget, void *data);
    void FUN_0053f9a0();

    RHPortraitButton m_button140; // 0x140
    RHPortraitButton m_button240; // 0x240
    RHPortraitButton m_button340; // 0x340
    RHPortraitButton m_button440; // 0x440
    RHPortraitEditableWidget m_entries[10]; // 0x540
    RHMenuSelectPlayerProfiles *m_profiles; // 0x15a8
};

#endif
