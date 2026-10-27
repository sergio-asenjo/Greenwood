// Stub definitions for the external symbols RHMenuWindow.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls are direct `call rel32` in a separate translation unit.

#include "SBNullstr.h"
#include "RHMenuWindow.h"


// Target 0x00544ee0, __thiscall.
RHMenuWindowFocus::~RHMenuWindowFocus() {}
void RHMenuWindowFocus::V00() {}




// Target 0x0053af80, __thiscall.
RHMenuScreenView::~RHMenuScreenView() {}

// Target 0x005fc3e0, __thiscall, ret 4.
RHMenuResolution::RHMenuResolution(const SBGeoPoint2D &) {}



// Target 0x0053c390, __thiscall.
void RHMenuScreenView::FUN_0053c390() {}

// Target 0x0053c650, __thiscall, ret 8.
void RHMenuScreenView::FUN_0053c650(RHMenuWindow *, bool) {}
