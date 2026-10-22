// RHUIRendererCustom.cpp — translation unit with __FILE__ evidence at
// 0x006b8c74 ("P:\Robin Hood\RHuirenderercustom.cpp",
// symbols/functions-by-file.tsv:405).
//
// BINDING (0x005ca340 -> RHUIRendererCustom::Render(SBResourceWidgetID)):
//   see include/RHUIRendererCustom.h for the full evidence chain.
//
// STATUS: BLOCKED — 92.49%, parked as STUB. VC6 merges the first failure's
// box cleanup into the second: target 0x5ca39b je +0x6a becomes je +0x3c,
// and the cleanup after EH state 3 jumps +0x50 to the shared point destruction.
// Array box[2] was tested: 41.10%, vector ctor/dtor helpers and shifted locals.
// /O2 /GX isolate probe reproduces the merge.
// for separate boxes; arrays of boxes or point members emit vector helpers.
// Implicit, forceinline and later-defined inline box dtors retain the residual.

#include "SBNullstr.h"
#include "RHUIRendererCustom.h"

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
};

// Parked: false-return cleanup/EH-tail sharing and state-store scheduling differ.
// STUB: GAME 0x005ca340
bool RHUIRendererCustom::Render(unsigned int id)
{
    SBGeoBoundingBox2D box;
    SBGeoBoundingBox2D box2;
    unsigned int surface0;
    unsigned int surface1;

    m_id = id;

    if (((RHUnk00600820 *)m_resource)->ResolveSurface((void *)m_resourceId, id, (float *)&surface0) != 1)
    {
        SBAssert(0,
                 // STRING: GAME 0x6b8c74
                 "P:\\Robin Hood\\RHuirenderercustom.cpp",
                 0x34,
                 // STRING: GAME 0x6b8c3c
                 "Unable to retrieve a resource for the custom renderer");
        return false;
    }

    if (((RHUnk00600820 *)m_resource)->ResolveSurface((void *)m_resourceId2, id, (float *)&surface1) != 1)
    {
        SBAssert(0, "P:\\Robin Hood\\RHuirenderercustom.cpp", 0x3a,
                 "Unable to retrieve a resource for the custom renderer");
        return false;
    }

    {
        SBGeoVector2D origin(*(SBGeoVector2D *)&m_box.m_p0);
        ((RHMobileUnk00607da0 *)&box)->FUN_00607da0((const RHMobileUnk00607da0 &)(m_box - origin));
    }
    ((RHMobileUnk00607da0 *)&box2)->FUN_00607da0((const RHMobileUnk00607da0 &)box);

    box.m_flag = true;
    box2.m_flag = true;

    float ratio = m_ratioNum / m_ratioDen;
    box.m_p1.m_x = box.m_p1.m_x * ratio;
    box2.m_p0.m_x = box.m_p1.m_x;

    if (box2.m_p1.m_x - box.m_p1.m_x > g_unk0x00677488)
    {
        SBGeoVector2D origin(*(SBGeoVector2D *)&m_box.m_p0);
        m_draw->Blit(surface1, &box2, m_20, &box2.FUN_006090d0(origin), 1);
    }

    if (box.m_p1.m_x - box.m_p0.m_x > g_unk0x00677488)
    {
        SBGeoVector2D origin(*(SBGeoVector2D *)&m_box.m_p0);
        m_draw->Blit(surface0, &box, m_20, &box.FUN_006090d0(origin), 1);
    }

    return true;
}

// Force emission: an unreferenced non-virtual member is dropped by VC6, so an
// out-of-line call from a global instance keeps Render in the build.
void RHUIRendererCustom::Emit()
{
    Render(0);
}

RHUIRendererCustom g_rhuirenderercustom;

void rh_uirenderercustom_emit()
{
    g_rhuirenderercustom.Emit();
}
