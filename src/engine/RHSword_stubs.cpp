// Stub definitions for the symbols RHSword.cpp calls or constructs.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHSword::SerializePointer are direct `call rel32`
// (matching the original shape) instead of import thunks. They live in a
// separate translation unit on purpose: VC6 emits the `new`-cleanup C++ EH
// frame only while the RHSword destructor body is not visible at the call site.

#include "RHSword.h"

RHSword::RHSword() {}
RHSword::~RHSword() {}
bool RHSword::Serialize(SBFile &) { return true; }
SBString *SBFile::GetError() { return 0; }
