// Stub definitions for the external symbols RHElementObject.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHElementObject::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBFile::Access / SBFile::GetError / SBAssert are already defined once, in
// RHSword_stubs.cpp; both TUs just declare them (include/SB.h).

#include "SBNullstr.h"
#include "RHElementObject.h"

// The nested sub-object serialiser at RHElementObject+0xbc (target 0x00521210)
// is now the real RHUnk004b2190Member::Serialize defined in src/RHLine.cpp; the
// declaration stays in include/RHElementObject.h.
