// Stub definitions for the external symbols RHMenuMovies.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls are direct `call rel32` in a separate translation unit.

#include "SBNullstr.h"
#include "RHMenuMovies.h"
#include "RHGameMenuCalls.h"
#include "RHMenuCloseCalls.h"

// FUNCTION: GAME 0x0052b520
bool RHMenuCloseCalls::FUN_0052b520(int, void *, void *)
{
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}



#include "SBDrawManager.h"

void RHUnk005ef320::FUN_005e4810(int, int, int) {}
