// Stub definitions for the external symbols RHSoundGeometry.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the call in RHSoundGeometry::Serialize is a direct `call rel32`
// (matching the original shape) instead of an unresolved external. They live in
// a separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBFile::Access / SBFile::GetError / SBAssert are already defined once, in
// RHSword_stubs.cpp; RHSerializeName is defined once in
// RHElementObject_stubs.cpp. This TU just declares them (include/SB.h,
// include/RHSoundGeometry.h).

#include "RHSoundGeometry.h"

// Target 0x005b2f30 — __thiscall(this, float). PROVISIONAL identity: its body
// stores the argument to [+0x08] and recomputes derived geometry floats at
// [+0xb8..c4]; it is reachable from RHSoundGeometry::Serialize and from
// 0x005a8650 (which guards the call against [+0x08] changing). No Windows-side
// __FILE__/tag/string names it, so it stays named by address
// (see include/RHSoundGeometry.h).
void RHSoundGeometry::RHUnk005b2f30(float) {}
