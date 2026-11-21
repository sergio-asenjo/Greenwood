#include "RHSightObstacle.h"
#include "RHElementActorHumanCore.h"
#include "RHSpriteCore.h"
#include "RHFastFindGridCore.h"

// GLOBAL: GAME 0x00677ba8
float g_unk0x00677ba8;

// FUNCTION: GAME 0x004843a0
bool RHElementActorHuman::IsRollNeeded(RHSightObstacle *area)
{
    if (area &&
        area->m_a8.Normal().z <= g_unk0x00677ba8)
        return true;
    return false;
}

// FUNCTION: GAME 0x004843d0
bool RHElementActorHuman::FindRollPoint(SBGeoPoint2D &point, RHSightObstacle *area, bool checkDirection)
{
    RHUnk00613e90 normal = area->m_a8.Normal();
    if (normal.z > 0.0f)
        normal.z -= 1.0f / normal.z;
    else
        normal.z -= 100.0f;
    normal.y *= 0.57357645f;
    normal.x *= 100.0f;
    normal.y *= 100.0f;
    normal.z *= 100.0f;
    SBGeoVector2D offset(normal.x, normal.y - normal.z);
    if (checkDirection && m_50->m_6c.FUN_005fc660(offset) < 0.0f)
        return false;
    SBGeoPoint2D destination(m_50->m_20);
    destination.FUN_005fc1e0(offset);
    SBGeoBoundingBox2D bounds(*static_cast<SBGeoBoundingBox2D *>(m_50->Unk0055fa10(3)));
    {
        SBGeoVector2D translation(destination);
        bounds.Translate(translation);
    }
    unsigned short layer = m_50->m_da;
    const SBGeoPoint2D &current = m_50->m_20;
    if (static_cast<RHFastFindGrid *>(m_64)->FindAutorizedPositionStraight(bounds, current, layer))
    {
        point = bounds.FUN_00608f40();
        return true;
    }
    return false;
}
