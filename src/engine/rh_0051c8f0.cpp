#include "RHHikingGuideStorage.h"
#include "RHFastFindGridCore.h"
#include "RHGate.h"
#include "RHMalignityPosition.h"
#include "SBGeoVector2D.h"

extern RHFastFindGrid *g_unk0x6c0a9c;
SBGeoVector2D FUN_0040ec60(const RHMalignityPosition &first, SBGeoPoint2D second);

DECOMP_SIZE_ASSERT(RHHikingGuide, 0x24)
DECOMP_SIZE_ASSERT(RHHikingGroupArray, 0x20)
DECOMP_SIZE_ASSERT(RHUnk0051d2c0, 0x20)
DECOMP_STATIC_ASSERT(offsetof(RHHikingGuide, m_04) == 4)
DECOMP_STATIC_ASSERT(offsetof(RHFastFindGrid, m_gates) == 0x4080)
DECOMP_STATIC_ASSERT(offsetof(RHUnk0051a5e0, m_kind) == 4)
DECOMP_STATIC_ASSERT(offsetof(RHWaypoint, m_64) == 0x64)
DECOMP_STATIC_ASSERT(offsetof(RHWaypoint, m_6c) == 0x6c)

// FUNCTION: GAME 0x0051c8f0
RHHikingGuide::RHHikingGuide()
{
    g_unk0x6c0b9c = this;
}

// SYNTHETIC: GAME 0x0051c920
// RHHikingGuide::`scalar deleting destructor'

// STUB: GAME 0x0051c940
RHHikingGuide::~RHHikingGuide()
{
    m_04.Destroy();
}

// STUB: GAME 0x0051cde0
void RHHikingGuide::BeamDoorWaypointsIntoHouses()
{
    RHFastFindPointerArray &gates = g_unk0x6c0a9c->m_gates;
    int paths = m_04.size();
    RHHikingGroupArray &groups = m_04;
    if ((unsigned short)paths > 0)
    {
        unsigned path = 0;
        unsigned remaining = (unsigned short)paths;
        do
        {
            RHUnk0051d2c0 *group = groups[path];
            if (group->begin())
            {
                unsigned points = group->size();
                if ((unsigned short)points > 0)
                {
                    unsigned index = 0;
                    unsigned left = (unsigned short)points;
                    do
                    {
                        RHWaypoint *waypoint = (*group)[index];
                        RHMalignityPosition position;
                        position.x = (float)waypoint->m_64;
                        position.y = (float)waypoint->m_66;
                        position.area = waypoint->m_68;
                        volatile unsigned short &positionLayer = position.layer;
                        positionLayer = waypoint->m_6c;
                        unsigned gateCount = gates.size();
                        for (unsigned door = 0; (unsigned short)door < (unsigned short)gateCount; ++door)
                        {
                            RHUnk0051a5e0 *entry = static_cast<RHUnk0051a5e0 *>(gates.begin()[(unsigned short)door]);
                            if (entry->m_kind != 1)
                                continue;
                            RHUnk0051aa00 *gate = static_cast<RHUnk0051aa00 *>(entry);
                            if (gate->m_88 == 1 &&
                                FUN_0040ec60(position, gate->FUN_00414320()).FUN_005fc700(1.0f) <= 5.0f)
                            {
                                RHMalignityPosition target;
                                target.layer = gate->m_16;
                                target.y = gate->m_20.m_y;
                                target.x = gate->m_20.m_x;
                                target.area = gate->m_10;
                                position = target;
                                waypoint->m_64 = (short)position.x;
                                waypoint->m_66 = (short)position.y;
                                waypoint->m_68 = position.area;
                                waypoint->m_6c = position.layer;
                                break;
                            }
                        }
                        ++index;
                    } while (--left);
                }
            }
            ++path;
        } while (--remaining);
    }
}
