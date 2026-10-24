// Anonymous cluster at 0x004e3fd0.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

#include "RHShadowPoolLifetime.h"

// FUNCTION: GAME 0x004e3fd0
RHUnk004e3fd0::RHUnk004e3fd0(const char *value)
{
    m_0 = *value;
    RHUnk004e3fd0List *list = new RHUnk004e3fd0List;
    list->m_next = list;
    list->m_prev = list;
    m_4 = list;
    m_8 = 0;
}
