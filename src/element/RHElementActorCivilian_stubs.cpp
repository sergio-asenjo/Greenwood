// Stub definitions for the external symbols RHElementActorCivilian.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHElementActorCivilian::Serialize are direct
// `call rel32` (matching the original shape) instead of unresolved externals.
// They live in a separate translation unit so VC6 cannot inline them into the
// matched function.
//
// SBFile::Access / SBFile::GetError / SBAssert / RHSerializeName are already
// defined once, in RHSword_stubs.cpp / RHElementObject_stubs.cpp; this TU only
// declares them (include/SB.h, include/RHElementActorCivilian.h).

#include "SBNullstr.h"
#include "RHElementActorCivilian.h"

bool RHElementActorCivilian::FUN_00470310()
{
    return false;
}

// Target 0x0048b5d0 (rhelementactornpc.cpp — writes the "RHElementActorNPC"
// tag). Its own string markers belong to that TU, not this one.
