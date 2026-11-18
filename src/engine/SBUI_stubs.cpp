#include "SBUI.h"
#include <new>






SBUI::~SBUI() {}

// FUNCTION: GAME 0x006287e0
SBUIUnkSurfaceBase::~SBUIUnkSurfaceBase()
{
    *(unsigned *)this = 0x0067ae04;
}
