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

#include "SBNullstr.h"
#include "RHSaveGame.h"

RHSaveGame::RHSaveGame(RHSaveGameManager *, const std::string &, const std::wstring &) {}

// FUNCTION: GAME 0x0056fd90
RHSaveGame::~RHSaveGame()
{
    typedef std::string NarrowString;
    typedef std::wstring WideString;
    ((WideString *)(m_data + 0x28))->~WideString();
    ((NarrowString *)(m_data + 0x18))->~NarrowString();
    ((NarrowString *)(m_data + 0x08))->~NarrowString();
}



// Target 0x0064158f (operator delete).
void operator delete(void *) {}
