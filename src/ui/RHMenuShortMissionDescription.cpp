// RHMenuShortMissionDescription.cpp — the short mission description menu TU
// (code 0x00540730..0x005412cb). See RHMenuShortMissionDescription.h for the
// binding evidence.

#include "SBNullstr.h"
#include "RHMenuShortMissionDescription.h"

// FUNCTION: GAME 0x00540730
RHMenuShortMissionDescription::RHMenuShortMissionDescription(RHMenuWindowScreen *screen)
    : RHMenuWindow(0, screen, false)
{
    m_blazons = 0;
    m_mission = 0;
    m_vptr = 0x00679940;
}

// FUNCTION: GAME 0x00540830
void *RHMenuShortMissionDescription::FUN_00540830(unsigned flags)
{
    this->~RHMenuShortMissionDescription();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00540d20
void RHMenuShortMissionDescription::FUN_00540d20()
{
    if (m_blazons)
    {
        delete m_blazons;
        m_blazons = 0;
    }
}
