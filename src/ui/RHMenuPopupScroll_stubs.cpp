// Stub definitions for the external symbols RHMenuPopupScroll.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls are direct `call rel32` in a separate translation unit.

#include "SBNullstr.h"
#include "RHMenuPopupScroll.h"

// Target 0x00539730, __thiscall.
RHMenuPopupScroll::~RHMenuPopupScroll() {}

// Target 0x0053a860, __thiscall, ret 0xc.
bool RHMenuPopupScroll::FUN_0053a860(int, void *, void *) { return false; }

RHMenuPopupScroll::RHMenuPopupScroll(RHMenuScreenView *, const std::wstring &, const std::string &, bool)
    : RHMenuWindowFocus(0, 0, 0, false) {}
bool RHMenuPopupScroll::FUN_0053a840() { return false; }
void RHMenuScreenView::FUN_0053be40(unsigned long) {}
RHMenuPopupScroll::RHMenuPopupScroll(RHMenuScreenView *, const std::wstring &, int, const std::string &, int)
    : RHMenuWindowFocus(0, 0, 0, false) {}
void RHMenuPopupScroll::FUN_00539b30() {}
const std::wstring &RHMenuPopupScroll::FUN_0053a820() { static std::wstring text; return text; }
std::wstring RHMenuPopupScroll::FUN_0053a660(int) { return std::wstring(); }
