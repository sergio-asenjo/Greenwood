// RHMenuPopupScroll — declarations for RHMenuPopupScroll.cpp (decompiled TU).
//
// BINDING: the vtable 0x00679834 holds the deleting dtor 0x00539710 (slot 0)
// and the RouteEvent override 0x005394e0 (slot 20, calling HandleEvent
// 0x00539500 and the base 0x0048a970). It follows RHMenuOptions in the
// alphabetical menu vtable run; the code run starts after RHMenuOptions'
// <iostream> init glue (0x00539460 group). Its single click handler
// 0x0053a860 matches the Mac oracle's lone RHMenuPopupScroll::OnOK
// (symbols/mac-RH.txt:2940).

#ifndef RHMENUPOPUPSCROLL_H
#define RHMENUPOPUPSCROLL_H

#include "SB.h"
#include "Decomp.h"
#include "RHMenuWindow.h"
#include "RHMenuMissionDescription.h"

// VTABLE: GAME 0x00679834
class RHMenuPopupScroll : public RHMenuWindowFocus
{
public:
    RHMenuPopupScroll(RHMenuScreenView *screen, const std::wstring &text, const std::string &title, int flags);
    RHMenuPopupScroll(RHMenuScreenView *screen, const std::wstring &text, int id, const std::string &title, int flags);
    void FUN_00539b30();
    const std::wstring &FUN_0053a820();
    static std::wstring FUN_0053a660(int id);
    ~RHMenuPopupScroll();
    void FUN_005394e0(RHMenuEvent *event);
    bool FUN_00539500(RHMenuEvent *event);
    void *FUN_00539710(unsigned flags);
    bool FUN_0053a860(int msg, void *widget, void *data);

    void *m_resource; // 0x140
    RHPortraitButton m_ok; // 0x144
    RHMissionDescriptionText m_title; // 0x244
    RHGameLifetime00515f00 m_text; // 0x364
    std::wstring m_message; // 0x430
    std::wstring m_left; // 0x440
    unsigned long m_450; // 0x450
    int m_flags; // 0x454
    static void FUN_0053a000(void *text, void *title, int flag);
    static void FUN_0053a380(RHMenuScreenView *screen, const std::wstring &text, const std::string &title, int flag);
    static bool FUN_0053a840();
    static void FUN_0053a0b0(int id);
    static void FUN_0053a1d0(const std::vector<int> &ids);
    static void FUN_0053a2d0();
    static void FUN_0053a4c0(RHMenuScreenView *screen, int id, const std::string &title, int flags);
    static unsigned long FUN_0053a5f0();
    static unsigned long FUN_0053a610(unsigned long index);
};

#endif
