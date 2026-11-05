#ifndef SBUI_H
#define SBUI_H

#include "Decomp.h"
#include "RHMapWindowPart.h"
#include "SBDrawManagerCore.h"
#include "SBDrawViewport.h"

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

class RHUnk00613e90;

class RHUnkFXDraw
{
public:
    unsigned short FUN_005e56c0(unsigned long surface);
    unsigned short FUN_005e5750(unsigned long surface);
    unsigned long Unk005e4ed0(unsigned short width, unsigned short height, unsigned long, bool);
};

#include "SBThreadedInput.h"

extern SBThreadedInput *g_unk0x6c1340;

#include "SBUIUnkSurface.h"

class RHGameActionCalls : public SBUI
{
public:
    void FUN_00619cc0();
};

#endif
