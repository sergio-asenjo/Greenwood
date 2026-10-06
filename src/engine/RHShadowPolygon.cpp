#include "RHShadowPolygon.h"

// Parked: 96.57%; cached-list call scheduling at 0x58e93c/0x58e950.
// STUB: GAME 0x0058e7f0
void RHShadowPolygon::DisplayDebug(const SBGeoBoundingBox2D &box, float zoom, RHElementActor *actor, SBGeoPoint3D &point, RHviewParameters &view, unsigned long flags)
{
    const float *bounds = (const float *)&box;
    if (bounds[0] < g_unk0x00677488 || bounds[1] < g_unk0x00677488)
        SBAssert(1,
                 // STRING: GAME 0x006b7728
                 "P:\\Robin Hood\\rhshadowpolygon.cpp",
                 3928,
                 // STRING: GAME 0x006b774c
                 "Shadow polygon : unable to zoom in because of too small map !");

    m_28 = flags;
    FUN_00594bf0(box, zoom, actor, point, view);
    FUN_005973f0();
    FUN_0058d990();
    FUN_00595020();
    FUN_005959e0();
    FUN_005971f0();
    FUN_0058ec60();
    g_pEngine->FUN_004c9d20(m_11c);

    for (unsigned short index = 0; index < (int)m_134.m_list.size(); ++index)
    {
        FUN_00597910();
        RHUnk00597a70 *area = m_134[index];
        if (FUN_00597a70(area))
        {
            FUN_0058ffa0(area);
            if (*(unsigned long *)&m_8c == 0x3f800000)
                FUN_00590c90(area);
            else if (m_8c > g_unk0x0067749c)
                FUN_005934b0(area);
            else
                FUN_00592080(area);
        }
    }
}

void rh_shadowpolygon_emit(RHShadowPolygon *polygon, const SBGeoBoundingBox2D &box, float zoom, RHElementActor *actor, SBGeoPoint3D &point, RHviewParameters &view, unsigned long flags)
{
    polygon->DisplayDebug(box, zoom, actor, point, view, flags);
}
