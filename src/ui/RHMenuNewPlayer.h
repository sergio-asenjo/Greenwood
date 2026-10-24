// RHMenuNewPlayer — declarations for RHMenuNewPlayer.cpp (decompiled TU).
//
// BINDING: the vtable 0x00679784 holds the deleting dtor 0x00537770 (slot 0) and the
// RouteEvent override 0x00537570 (slot 20, calling HandleEvent 0x00537590 and the base
// 0x0048a970). The menu vtables are laid out in alphabetical TU order between
// RHMenuMovies and RHMenuOptions; per-TU <iostream> init glue bounds the code run 0x00537570... Class name from
// that position and the handler set (two handlers = OnCancel/OnOK, symbols/mac-RH.txt:2902-2911).

#ifndef RHMENUNEWPLAYER_H
#define RHMENUNEWPLAYER_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"
#include "RHPortraitLinkedLifetimeView.h"
#include "RHGameTitleLifetimeInline.h"

// SIZE 0x114
// VTABLE: GAME 0x00679784
// SIZE 0xe24
class RHMenuNewPlayer : public RHMenuWindowFocus
{
public:
    RHMenuNewPlayer(RHMenuScreenView *screen);
    int FUN_00538280() const;
    bool FUN_005383e0();
    ~RHMenuNewPlayer();
    void FUN_00537570(RHMenuEvent *event);
    bool FUN_00537590(RHMenuEvent *event);
    void *FUN_00537770(unsigned flags);
    bool FUN_005383f0(int msg, void *widget, void *data);
    bool FUN_00538410(int msg, void *widget, void *data);

    RHGameLifetime00525560 m_title; // 0x140
    RHGameLifetime00525560 m_nameLabel; // 0x240
    RHGameLifetime00525560 m_difficultyLabel; // 0x340
    RHPortraitEditableWidget m_name; // 0x440
    RHPortraitLinkedLifetime m_radios[3]; // 0x5e4
    RHGameLifetime00525560 m_radioLabels[3]; // 0x920
    RHPortraitButton m_okButton; // 0xc20
    RHPortraitButton m_cancelButton; // 0xd20
    bool m_ok; // 0xe20
};

#endif
