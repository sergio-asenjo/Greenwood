// Stub definitions for the external symbols RHMenuLoadSave.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls are direct `call rel32` in a separate translation unit.

#include "SBNullstr.h"
#include "RHMenuLoadSave.h"

// Target 0x00530510, __thiscall.
RHMenuLoadSave::~RHMenuLoadSave() {}

// FUNCTION: GAME 0x00463d80
bool RHMenuLoadSave::FUN_00463d80(int, void *, void *) { return false; }


// Target 0x005314d0, __thiscall, ret 0xc.
bool RHMenuLoadSave::FUN_005314d0(int, void *, void *) { return false; }







// Target 0x00530320, __thiscall, ret 8.
RHMenuLoadSave::RHMenuLoadSave(RHMenuScreenView *, bool) : RHMenuWindowFocus(0, 0, 0, false) {}

// Target 0x005307d0, __thiscall.
void RHMenuLoadSave::FUN_005307d0() {}

RHMenuLoadSaveSlots::~RHMenuLoadSaveSlots() {}
RHMenuLoadSaveList::~RHMenuLoadSaveList() {}
void RHPortraitInputRenderer::FUN_0061c610(unsigned long) {}
