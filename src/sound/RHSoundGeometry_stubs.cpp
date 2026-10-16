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

#include "SBNullstr.h"
#include "RHSoundGeometry.h"
