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

// Targets 0x005d6690 / 0x005d67e0 / 0x005d73d0 / 0x005d7530.
void RHWidgetPortrait::Method005d6690() {}
void RHWidgetPortrait::Method005d67e0() {}
void RHWidgetPortrait::Method005d73d0() {}
void RHWidgetPortrait::Method005d7530() {}
