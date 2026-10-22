// RHMenuIntro — declarations for RHMenuIntro.cpp (decompiled TU).
//
// BINDING: the vtable 0x00679518 holds the deleting dtor 0x0052e300 (slot 0) and the
// RouteEvent override 0x0052e090 (slot 20, calling HandleEvent 0x0052e0b0 and the base
// 0x0048a970). The menu vtables are laid out in alphabetical TU order between
// RHMenuIngame and RHMenuLoadSave; per-TU <iostream> init glue bounds the code run 0x0052e090..0x00530170. Class name from
// that position and the handler set (symbols/mac-RH.txt RHMenuIntro (17 methods)).

#ifndef RHMENUINTRO_H
#define RHMENUINTRO_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"
#include "RHMenuLoadSave.h"
#include "RHMenuMovies.h"
#include "RHMenuOptions.h"
#include "RHMenuShortMissionDescription.h"

class SBThreadedInput
{
public:
    void SetMouseEnabled(bool enabled);
};

extern char g_unk0x006c0685;
extern SBThreadedInput *g_unk0x6c1340;

// VTABLE: GAME 0x00679518
class RHMenuIntro : public RHMenuWindowFocus
{
public:
    RHMenuIntro(RHMenuScreenView *screen);
    ~RHMenuIntro();
    void FUN_0052e090(RHMenuEvent *event);
    bool FUN_0052e0b0(RHMenuEvent *event);
    void *FUN_0052e300(unsigned flags);
    void FUN_0052f540();
    int FUN_0052ec40();
    void *FUN_0052ec50();

    RHPortraitButton m_140;
    RHPortraitButton m_240;
    RHPortraitButton m_340;
    RHPortraitButton m_440;
    RHPortraitButton m_540;
    RHPortraitButton m_640;
    RHPortraitButton m_740;
    RHMenuShortMissionTitle m_840;
    RHMenuShortMissionTitle m_940;
    int m_choice; // 0xa40
    RHMenuLoadSaveResult m_result; // 0xa44
    bool FUN_0052ec60(int msg, void *widget, void *data);
    bool FUN_0052ecb0(int msg, void *widget, void *data);
    bool FUN_0052ed80(int msg, void *widget, void *data);
    bool FUN_0052edf0(int msg, void *widget, void *data);
    bool FUN_0052ee20(int msg, void *widget, void *data);
    bool FUN_0052efa0(int msg, void *widget, void *data);
    bool FUN_0052efc0(int msg, void *widget, void *data);
};

#endif
