// RHMenuOptions — declarations for RHMenuOptions.cpp (decompiled TU).
//
// BINDING: the vtable 0x006797dc holds the deleting dtor 0x00538710 (slot 0) and the
// RouteEvent override 0x00538540 (slot 20, calling HandleEvent 0x00538560 and the base
// 0x0048a970). The menu vtables are laid out in alphabetical TU order between
// RHMenuNewPlayer and RHMenuPopupScroll; per-TU <iostream> init glue bounds the code run 0x00538540... Class name from
// that position and the handler set (four handlers = OnBack/OnGraphics/OnShortcuts/OnSounds, symbols/mac-RH.txt:2912-2923).

#ifndef RHMENUOPTIONS_H
#define RHMENUOPTIONS_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"
#include "RHMenuShortcuts.h"
#include "RHMenuSounds.h"
#include "RHMenuShortMissionDescription.h"

class RHSound
{
public:
    void ApplySoundSettings();
};

class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;

class RHMenuOptions : public RHMenuWindowFocus
{
public:
    RHMenuOptions(RHMenuScreenView *screen);
    ~RHMenuOptions();
    void FUN_00538860();
    static bool FUN_00538e80(RHMenuWindowUI *ui);
    static bool bReDisplay;
    void FUN_00538540(RHMenuEvent *event);
    bool FUN_00538560(RHMenuEvent *event);
    void *FUN_00538710(unsigned flags);
    bool FUN_0052ce80(int msg, void *widget, void *data);
    bool FUN_00539250(int msg, void *widget, void *data);
    bool FUN_005393c0(int msg, void *widget, void *data);
    bool FUN_005393f0(int msg, void *widget, void *data);

    RHMenuShortMissionTitle m_title;
    RHMenuShortMissionTitle m_subtitle;
    RHPortraitButton m_graphics;
    RHPortraitButton m_sounds;
    RHPortraitButton m_shortcuts;
    RHPortraitButton m_back;
    bool m_changed; // 0x740
};

#endif
