#include "RHUnkWaypointRef.h"
#include "RHWaypoint.h"
#include "RHArtificialIntelligenceCore.h"
extern char g_unk0x6c0691;

// FUNCTION: GAME 0x004105d0
void RHArtificialIntelligence::ActivateWaypoint(RHWaypoint *waypoint)
{
    if (g_unk0x6c0691)
    {
        reinterpret_cast<RHUnkWaypointRef *>((char *)waypoint + 0x60)->Unk00408750(m_npcActor);
        if (m_14 != 0xe)
            DispatchWorldEvent(0x14);
    }
}
