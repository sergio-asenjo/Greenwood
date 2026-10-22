// Anonymous cluster at 0x0048daxx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets are exact from Game.exe.

#include "RHSoldierNPCCalls.h"

struct RHUnk0048da10
{
    char m_0[0x10];
    int m_10;
    char m_14[0x4c - 0x14];
    RHUnk0048da10 *m_4c;
    RHUnk0048da10 *m_50;
};

// FUNCTION: GAME 0x0048da40
bool RHSoldierNPCCalls::FUN_0048da40(RHUnk0048da10 *value)
{
    while (value->m_50 == 0)
    {
        value = value->m_4c;
        if (value == 0)
            return true;
        switch (value->m_10)
        {
        case 2:
        case 0xa1:
            break;
        default:
            return false;
        }
    }
    return false;
}

void EmitFUN_0048da40(RHSoldierNPCCalls *owner, RHUnk0048da10 *value)
{
    owner->FUN_0048da40(value);
}
