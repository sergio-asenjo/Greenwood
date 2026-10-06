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

#include "RHElementObject.h"

// Target 0x00462330 (RHElement::Serialize — writes the "RHElement" tag).
bool RHElement::Serialize(SBFile &) { return true; }

// The nested sub-object serialiser at RHElementObject+0xbc (target 0x00521210)
// is now the real RHUnk004b2190Member::Serialize defined in src/RHLine.cpp; the
// declaration stays in include/RHElementObject.h.

// Target 0x005e1b70 (serialises a type-name tag into the stream).
void RHSerializeName(SBFile &, const char *) {}
