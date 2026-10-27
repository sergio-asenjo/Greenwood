// Stub definitions for the external symbols RHMenuGraphics.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHMenuGraphics::SynchronizeWidgets resolve. They live
// in a separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBAssert is already defined once, in RHSword_stubs.cpp; this TU only
// declares it (include/SB.h).

// Target 0x00642b7c (VC6's float->int64 helper, CRT). The original calls it
// from SynchronizeWidgets for `(int)m_screenWidth`. Our build's `__ftol` comes
// from the CRT (build/intel/mt_obj/ftol.obj) but carries no source marker, so
// reccmp cannot name the original operand and the call compares unequal.
// Providing the local entity with the library marker gives the operand a
// symbol on both sides. LIBRARY functions are not compared, so the body is a
// minimal stand-in.
// LIBRARY: GAME 0x00642b7c
extern "C" __int64 _ftol()
{
    return 0;
}

#include "RHMenuGraphics.h"

// Target 0x0052c220, __thiscall.

// Target 0x0052c3c0, __thiscall.
