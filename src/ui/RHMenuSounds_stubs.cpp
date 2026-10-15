// Stub definitions for the external symbols RHMenuSounds.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls are direct `call rel32` in a separate translation unit.

#include "SBNullstr.h"
#include "RHMenuSounds.h"

RHMenuSoundsSettings::RHMenuSoundsSettings(const RHMenuSoundsSettings &) {}
RHMenuSoundsLabel::RHMenuSoundsLabel() {}

// Target 0x005417a0, __thiscall.
RHMenuSounds::~RHMenuSounds() {}

// Target 0x00541a90, __thiscall.
void RHMenuSounds::FUN_00541a90() {}

// Target 0x0052ce80 (folded close handler), __thiscall, ret 0xc.
bool RHMenuSounds::FUN_0052ce80(int, void *, void *) { return false; }

// Target 0x00543520, __thiscall, ret 0xc.
bool RHMenuSounds::FUN_00543520(int, void *, void *) { return false; }
