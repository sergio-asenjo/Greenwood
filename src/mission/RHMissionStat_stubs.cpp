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

// FUNCTION: GAME 0x005e2bf0
std::wstring FUN_005e2bf0(int value)
{
    unsigned hours = (unsigned)value / 3600;
    unsigned minutes = ((unsigned)value - hours * 3600) / 60;
    unsigned short buffer[128];
    wsprintfW(buffer,
        // STRING: GAME 0x006b9238
        L"%02i:%02i", hours, minutes);
    return std::wstring(buffer);
}
