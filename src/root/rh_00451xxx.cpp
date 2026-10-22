// Anonymous cluster at 0x00451ffx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Offsets and the 12-byte element stride are exact from Game.exe.

#include "RHCampaignMissionStatus.h"

// FUNCTION: GAME 0x00451ff0
RHUnk00451f10 *RHUnk00451f00::FUN_00451ff0(int key)
{
    RHUnk00451f10 *element = m_148;
    RHUnk00451f10 *result = 0;
    while (element != m_14c)
    {
        if (*element->m_0 == key)
        {
            result = element;
            break;
        }
        element++;
    }
    return result;
}

void EmitRHUnk00451f00(RHUnk00451f00 *object)
{
    object->FUN_00451ff0(0);
}
