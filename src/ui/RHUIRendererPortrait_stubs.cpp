// Stub definitions for the external symbols RHUIRendererPortrait.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHUIRendererPortrait::BlitPicture resolve. They live in
// a separate translation unit so VC6 cannot inline them into the matched
// function. They carry no // FUNCTION: marker on purpose (Hard rule 28): a
// matched caller must keep its call operand a symmetric <OFFSET>.
//
// SBAssert is defined once, in RHSword_stubs.cpp; _ftol is defined once, with a
// // LIBRARY: seed, in RHMenuGraphics_stubs.cpp. This TU only declares both.

#include "SBNullstr.h"
#include "RHUIRendererPortrait.h"

bool RHUnk005e6440::BlitFull(float, int, int, void *, int)
{
    return true;
}

bool RHUnk005e6440::BlitScaled(float, int, int, void *, int, int)
{
    return true;
}
