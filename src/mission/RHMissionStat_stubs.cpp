// Stub definitions for the external symbols RHMissionStat.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHMissionStat::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBFile::Access / SBFile::GetError / SBAssert / RHSerializeName are already
// defined once, in RHSword_stubs.cpp / RHElementObject_stubs.cpp; this TU only
// declares them (include/SB.h, include/RHMissionStat.h).

#include "SBNullstr.h"
#include "RHMissionStat.h"

// LIBRARY: GAME 0x00642bc9
int __cdecl wsprintfW(unsigned short *buffer, const unsigned short *format, ...)
{
    return 0;
}

std::wstring FUN_005e2bf0(int value)
{
    return std::wstring();
}
