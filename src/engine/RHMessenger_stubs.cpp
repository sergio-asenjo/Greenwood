// Stub definitions for the external symbols RHMessenger.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the call in RHMessenger::Serialize is a direct `call rel32`
// (matching the original shape) instead of an unresolved external. They live in
// a separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBFile::Access / SBFile::GetError / SBAssert are already defined once, in
// RHSword_stubs.cpp; RHSerializeName is defined once in
// RHElementObject_stubs.cpp. This TU just declares them (include/SB.h,
// include/RHMessenger.h).

#include "SBNullstr.h"
#include "RHMessenger.h"

// Target 0x00547560 — __thiscall(this), no extra args. PROVISIONAL identity:
// it clears a run of byte/dword flags across [0x14, 0xaa] and resets two
// embedded containers; it is called from both the loading and saving paths of
// RHMessenger::Serialize. No Windows-side __FILE__/tag/string names it, so it
// stays named by address (see include/RHMessenger.h).

// Target 0x005490f0 / 0x00549110 — the ctor/dtor pair of the 0x10-byte value
// object RHMessenger::SerializeLockUser constructs on a stack temporary and
// passes by reference to RHUnk005460c0. PROVISIONAL identity by address only:
// no Windows-side __FILE__/tag/string names the type (docs/05-naming.md).
// Defined in this separate TU so VC6 keeps the ctor/dtor as external calls and
// does not elide the matched function's EH temp frame (Hard rule 5).
RHMessenger::RHMessenger() {}
RHMessenger::~RHMessenger() {}
// FUNCTION: GAME 0x00549110
RHUnk5490f0::~RHUnk5490f0() {}

// Target 0x005460c0 — __thiscall(this, RHUnk5490f0&), ends `ret 4`. A real
// RHMessenger method: it reads this[+0x23] and the surrounding +0x20/+0x26/
// +0xa2/+0xa8 flag block and dispatches on the argument's field at +0xc. No
// Windows-side signal names it, so it stays named by address.
void RHMessenger::RHUnk005460c0(RHUnk5490f0 &) {}

class SBGeoPoint2D
{
public:
    float FUN_005fca90(const SBGeoPoint2D &other, float scale) const;
};
