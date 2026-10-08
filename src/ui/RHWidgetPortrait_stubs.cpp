// Stub definitions for the external symbols RHWidgetPortrait.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHWidgetPortrait::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBFile::Access / SBFile::GetError / SBAssert / RHSerializeName are already
// defined once, in RHSword_stubs.cpp / RHElementObject_stubs.cpp; this TU only
// declares them (include/SB.h, include/RHWidgetPortrait.h).

#include "RHWidgetPortrait.h"

char RHUnk005d73d0Actor::FUN_0049f510() { return 0; }
void RHWidgetPortrait::FUN_005d8ed0(int, int) {}
void RHWidgetPortrait::FUN_005d9c30() {}
void RHWidgetPortrait::FUN_005da1f0() {}
