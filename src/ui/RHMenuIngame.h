// RHMenuIngame — declarations for RHMenuIngame.cpp (decompiled TU).
//
// BINDING: the vtable 0x006794c0 holds the deleting dtor 0x0052d600 (slot 0) and the
// RouteEvent override 0x0052d3e0 (slot 20, calling HandleEvent 0x0052d400 and the base
// 0x0048a970). The menu vtables are laid out in alphabetical TU order between
// RHMenuGraphics (0x0052c030..0x0052d3d0) and RHMenuIntro; per-TU <iostream> init glue bounds the code run 0x0052d3e0..0x0052e080. Class name from
// that position and the handler set (symbols/mac-RH.txt RHMenuIngame (15 methods)).

#ifndef RHMENUINGAME_H
#define RHMENUINGAME_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"
#include "RHMenuLoadSave.h"
#include "RHMenuOptions.h"

class RHMenuIngame : public RHMenuWindowFocus
{
public:
    ~RHMenuIngame();
    void FUN_0052d3e0(RHMenuEvent *event);
    bool FUN_0052d400(RHMenuEvent *event);
    void *FUN_0052d600(unsigned flags);

    undefined m_140[0x600]; // 0x140
    RHMenuLoadSaveResult m_result; // 0x740
    undefined m_748[8]; // 0x748
    bool m_750; // 0x750
    bool m_751; // 0x751
    bool FUN_0052dcf0(int msg, void *widget, void *data);
    bool FUN_0052dd10(int msg, void *widget, void *data);
    bool FUN_0052dd80(int msg, void *widget, void *data);
    bool FUN_0052de40(int msg, void *widget, void *data);
    bool FUN_0052de60(int msg, void *widget, void *data);
    bool FUN_0052ded0(int msg, void *widget, void *data);
};

#endif
