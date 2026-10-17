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

// SIZE 0x114
struct RHMenuNewPlayerRadio
{
    undefined m_00[0x7c]; // 0x00
    bool m_selected; // 0x7c
    undefined m_7d[0x97]; // 0x7d
};

class RHMenuNewPlayer : public RHMenuWindowFocus
{
public:
    int FUN_00538280() const;
    bool FUN_005383e0();
    ~RHMenuNewPlayer();
    void FUN_00537570(RHMenuEvent *event);
    bool FUN_00537590(RHMenuEvent *event);
    void *FUN_00537770(unsigned flags);
    bool FUN_005383f0(int msg, void *widget, void *data);
    bool FUN_00538410(int msg, void *widget, void *data);

    undefined m_140[0x500]; // 0x140
    RHMenuNewPlayerRadio m_radios[3]; // 0x640
    undefined m_97c[0x4a4]; // 0x97c
    bool m_ok; // 0xe20
};

#endif
