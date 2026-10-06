// Stub definitions for the external symbols RHElementPurse.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHElementPurse::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched function.
//
// SBFile::Access / SBFile::GetError / SBAssert / RHSerializeName are already
// defined once, in RHSword_stubs.cpp / RHElementObject_stubs.cpp; this TU only
// declares them (include/SB.h, include/RHElementPurse.h).

#include "RHElementPurse.h"

// Target 0x004b7500 (rhelementprojectile.cpp — writes the "RHElementProjectile"
// tag). Its own string markers belong to that TU, not this one.
bool RHElementProjectile::Serialize(SBFile &) { return true; }
