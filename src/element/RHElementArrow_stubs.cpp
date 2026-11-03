// Stub definitions for the external symbols RHElementArrow.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHElementArrow::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched function.
//
// RHElementProjectile::Serialize, SBFile::Access / GetError, SBAssert and
// RHSerializeName are already defined once, in RHElementPurse_stubs.cpp /
// RHSword_stubs.cpp / RHElementObject_stubs.cpp; this TU only declares them
// (include/RHElementArrow.h, include/SB.h).

#include "SBNullstr.h"
#include "RHElementArrow.h"
