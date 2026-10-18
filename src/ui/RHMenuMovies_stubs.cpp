// Stub definitions for the external symbols RHMenuMovies.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls are direct `call rel32` in a separate translation unit.

#include "SBNullstr.h"
#include "RHMenuMovies.h"
#include "RHGameMenuCalls.h"

// Target 0x00536c50, __thiscall.
RHMenuMovies::~RHMenuMovies() {}

// FUNCTION: GAME 0x0052b520
bool RHMenuMovies::FUN_0052b520(int, void *, void *)
{
    ((RHGameMenuCalls *)this)->FUN_00544b30();
    return true;
}

void RHMenuMovies::FUN_00537400(const std::string &) {}

// Target 0x00536d30, __thiscall.
void RHMenuMovies::FUN_00536d30() {}
