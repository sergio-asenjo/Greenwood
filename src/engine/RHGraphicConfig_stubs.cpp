// Stub definitions for the external symbols RHGraphicConfig.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHGraphicConfig::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBFile::Access / SBFile::GetError / SBAssert are already defined once, in
// RHSword_stubs.cpp; RHSerializeName is defined once in
// RHElementObject_stubs.cpp. Both TUs just declare them (include/SB.h,
// include/RHGraphicConfig.h).

#include "RHGraphicConfig.h"

// Target 0x005fc2a0 (SBGeoPoint2D::Serialize — two 4-byte Access calls at
// __FILE__ P:\Robin Hood\SBLibNG\SBGeoPoint2D.cpp lines 264/265).
bool SBGeoPoint2D::Serialize(SBFile &) { return true; }
