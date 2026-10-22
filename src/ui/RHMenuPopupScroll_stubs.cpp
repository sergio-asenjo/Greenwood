// Stub definitions for the external symbols RHMenuPopupScroll.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls are direct `call rel32` in a separate translation unit.

#include "SBNullstr.h"
#include "RHMenuPopupScroll.h"

// Target 0x00539730, __thiscall.
RHMenuPopupScroll::~RHMenuPopupScroll() {}

RHMenuPopupScroll::RHMenuPopupScroll(RHMenuScreenView *, const std::wstring &, const std::string &, bool)
    : RHMenuWindowFocus(0, 0, 0, false) {}
RHMenuPopupScroll::RHMenuPopupScroll(RHMenuScreenView *, const std::wstring &, int, const std::string &, int)
    : RHMenuWindowFocus(0, 0, 0, false) {}
void RHMenuPopupScroll::FUN_00539b30() {}
std::wstring RHMenuPopupScroll::FUN_0053a660(int) { return std::wstring(); }
