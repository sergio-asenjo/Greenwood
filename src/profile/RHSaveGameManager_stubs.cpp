// Stub definitions for the external symbols RHSaveGameManager.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHSaveGameManager::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched function,
// and so the `new`-cleanup C++ EH frame is emitted at the call site.
//
// SBFile::Access / SBFile::GetError / SBAssert are defined once in
// RHSword_stubs.cpp; RHSerializeName once in RHElementObject_stubs.cpp;
// operator new once in crt_stubs.cpp. This TU only defines the remaining
// targets.

#include "RHSaveGameManager.h"

// Target 0x0056e250 (initialises the 0x48-byte RHSaveGame).
RHSaveGame::RHSaveGame(RHSaveGameManager *) {}

// Target 0x0056fd90 (releases the three string-like members at +0x0c/+0x1c/+0x2c).
RHSaveGame::~RHSaveGame() {}

// Target 0x0056ea20 (writes the "RHSaveGame" tag).
bool RHSaveGame::Serialize(SBFile &) { return true; }

// Target 0x004582d0 (out-of-line SBArray<RHSaveGame*>::Insert).
void SBArray<RHSaveGame *>::Insert(RHSaveGame **, unsigned int, RHSaveGame *const &) {}

// Target 0x0064158f (operator delete).
void operator delete(void *) {}
