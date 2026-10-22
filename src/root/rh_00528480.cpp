// Anonymous cluster at 0x0052848x.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets and the 0x27c element stride are exact from Game.exe.

#include "RHUnk00528400.h"

// FUNCTION: GAME 0x00528480
RHUnk00528410 *RHUnk00528400::FUN_00528480(RHUnk00528410 *target)
{
    RHUnk00528410 *element = m_19c;
    RHUnk00528410 *last = m_19c + 10;
    RHUnk00528410 *result = 0;
    while (element != last)
    {
        if (element == target)
        {
            result = element;
            break;
        }
        element++;
    }
    return result;
}

void EmitRHUnk00528400(RHUnk00528400 *object)
{
    object->FUN_00528480(0);
}
