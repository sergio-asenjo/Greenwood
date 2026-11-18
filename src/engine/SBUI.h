#ifndef SBUI_H
#define SBUI_H

#include "Decomp.h"
#include "RHMapWindowPart.h"
#include "SBDrawManagerCore.h"
#include "SBDrawViewport.h"

extern SBDrawManager *g_unk0x6c11d0;

class RHUnk00613e90;

#include "SBThreadedInput.h"

extern SBThreadedInput *g_unk0x6c1340;

#include "SBUIUnkSurface.h"

class RHGameActionCalls : public SBUI
{
public:
    void FUN_00619cc0();
};

#endif
