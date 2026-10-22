// Stub definitions for the external symbols RHMinimap.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the call in RHMinimap::SerializeHighlightedElement is a direct
// `call rel32` (matching the original shape) instead of an unresolved external.
// They live in a separate translation unit so VC6 cannot inline them into the
// matched function.
//
// SBFile::Access / SBFile::GetError / SBAssert are already defined once, in
// RHSword_stubs.cpp; this TU only declares them (include/SB.h). The engine
// singleton g_pEngine is already defined once, in RHMenuDialogue_stubs.cpp;
// this TU only declares it extern (include/RHMinimap.h).

#include "SBNullstr.h"
#include "RHMinimap.h"

void RHMinimap::FUN_0054b5e0(const SBGeoPoint2D &, unsigned short) {}
