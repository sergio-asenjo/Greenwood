// Stub definitions for the external symbols RHMenuWindow.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls are direct `call rel32` in a separate translation unit.

#include "SBNullstr.h"
#include "RHMenuWindow.h"

// Target 0x0053bf30, __thiscall, no stack argument.
RHMenuWindowUI *RHMenuWindowScreen::FUN_0053bf30() { return 0; }


// Target 0x00544ee0, __thiscall.
RHMenuWindowFocus::~RHMenuWindowFocus() {}




// Target 0x0053af80, __thiscall.
RHMenuScreenView::~RHMenuScreenView() {}

// Target 0x005fc3e0, __thiscall, ret 4.
RHMenuResolution::RHMenuResolution(const SBGeoPoint2D &) {}


// Target 0x0053bb80, __thiscall, ret 0xc.
void RHMenuWindowScreen::FUN_0053bb80(RHMenuWindow *, bool, bool) {}

// Target 0x00545220, __thiscall, ret 8.
RHMenuYesNo::RHMenuYesNo(RHMenuWindowScreen *screen, const std::wstring &) : RHMenuWindow(0, screen, false) {}

// Target 0x005455b0, __thiscall.
RHMenuYesNo::~RHMenuYesNo() {}

// Target 0x00545710, __thiscall.
void RHMenuYesNo::FUN_00545710() {}

