// Anonymous cluster at 0x004baf0x.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Case bodies and the jump-table order are exact from Game.exe.

#include "RHElementActorHuman.h"

// FUNCTION: GAME 0x004baeb0
unsigned FUN_004baeb0(void *actor)
{
    unsigned flags = 0x406;
    if (((RHScriptBatchCalls *)actor)->Unk0049d560(0x17))
        flags = 0x506;
    if (((RHScriptBatchCalls *)actor)->Unk0049d560(9))
        flags |= 0x10;
    if (((RHHumanVirtualCalls *)actor)->V0f8())
        flags |= 8;
    return flags;
}

// FUNCTION: GAME 0x004baf00
int FUN_004baf00(volatile int type)
{
    switch (type)
    {
    case 4:
        return 1;
    case 7:
        return 0x40;
    case 8:
        return 0x20;
    case 10:
        return 0x80;
    case 9:
        return 0x10;
    }
    return 0;
}

void EmitFUN_004baf00(int type)
{
    FUN_004baeb0(0);
    FUN_004baf00(type);
}
