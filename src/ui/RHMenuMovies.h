// RHMenuMovies — declarations for RHMenuMovies.cpp (decompiled TU).
//
// BINDING: the vtable 0x0067972c holds the deleting dtor 0x00536c30 (slot 0) and the
// RouteEvent override 0x00536ad0 (slot 20, calling HandleEvent 0x00536af0 and the base
// 0x0048a970). The menu vtables are laid out in alphabetical TU order between
// RHMenuMissionDescription and RHMenuNewPlayer; per-TU <iostream> init glue bounds the code run 0x00536ad0... Class name from
// that position and the handler set (three handlers = OnIntro/OnOK/OnOutro, symbols/mac-RH.txt:2892-2901).

#ifndef RHMENUMOVIES_H
#define RHMENUMOVIES_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"
#include "RHMenuShortMissionDescription.h"

// SIZE 0x540
class RHMenuMovies : public RHMenuWindowFocus
{
public:
    RHMenuMovies(RHMenuScreenView *screen);
    ~RHMenuMovies();
    void FUN_00536d30();
    static void FUN_00537220(RHMenuWindowUI *ui);
    void FUN_00536ad0(RHMenuEvent *event);
    bool FUN_00536af0(RHMenuEvent *event);
    void *FUN_00536c30(unsigned flags);
    bool FUN_0052b520(int msg, void *widget, void *data);
    bool FUN_005372e0(int msg, void *widget, void *data);
    bool FUN_00537370(int msg, void *widget, void *data);
    void FUN_00537400(const std::string &path);

    RHMenuShortMissionTitle m_title;
    RHPortraitButton m_ok;
    RHPortraitButton m_intro;
    RHPortraitButton m_outro;
};

#endif
