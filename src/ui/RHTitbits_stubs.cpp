// Stub definitions for the external symbols RHTitbits.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHTitbits::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBFile::Access / SBFile::GetError / SBAssert / RHSerializeName and the
// g_pEngine global are already defined once, in RHSword_stubs.cpp /
// RHElementObject_stubs.cpp / RHMenuDialogue_stubs.cpp; this TU only declares
// them (include/SB.h, include/RHTitbits.h).

#include "SBNullstr.h"
#include "RHTitbits.h"

// Target 0x00613e90.
RHUnk00613e90::RHUnk00613e90() {}

// Target 0x005df510.
void RHUnk005df510::Serialize(SBFile &) {}

// Target 0x0044e8b0.
void RHTitbitList::Clear(void *, RHTitbitNode *, RHTitbitNode *) {}
