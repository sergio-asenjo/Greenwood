// Stub definitions for the external symbols RHMenuShortcuts.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls are direct `call rel32` in a separate translation unit.

#include "SBNullstr.h"
#include "RHMenuShortcuts.h"

// Target 0x0051ebf0, __thiscall, ret 4 (RHKeyConfig copy assignment).
RHMenuShortcutsKeys &RHMenuShortcutsKeys::FUN_0051ebf0(const RHKeyConfig &) { return *this; }

// Target 0x005ccc00, __thiscall.
RHMenuShortcutsList::RHMenuShortcutsList() {}

RHMenuShortcutsList::~RHMenuShortcutsList() {}

// Target 0x0052ce80 (folded close handler), __thiscall, ret 0xc.
bool RHMenuShortcuts::FUN_0052ce80(int, void *, void *) { return false; }

// Target 0x0053fcc0, __thiscall.
RHMenuShortcuts::~RHMenuShortcuts() {}

// Target 0x0053fdd0, __thiscall.
void RHMenuShortcuts::FUN_0053fdd0() {}

// Target 0x005ced90, __thiscall, no stack argument.
void RHMenuShortcutsList::FUN_005ced90() {}

// GLOBAL: GAME 0x006c069c
bool g_unk0x6c069c;
