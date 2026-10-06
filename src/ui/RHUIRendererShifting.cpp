// RHUIRendererShifting.cpp — translation unit with __FILE__ evidence at
// 0x006b8d30 ("P:\Robin Hood\RHUIRendererShifting.cpp",
// symbols/functions-by-file.tsv:407).
//
// BINDING (0x005cbe60 -> RHUIRendererShifting::Render(SBResourceWidgetID)):
//   see include/RHUIRendererShifting.h for the full evidence chain.
//
// STATUS: exact 100% — instruction-for-instruction identical to the original.

#include "RHUIRendererShifting.h"

// FUNCTION: GAME 0x005cbe60
bool RHUIRendererShifting::Render(unsigned int id)
{
    SBGeoBoundingBox2D box;

    m_id = id;

    if (id == 0xff)
    {
        (&m_handles)[m_index & 1] = 0;
        return false;
    }

    unsigned int surface;

    if (m_resource->GetSurfaceForResource(m_resourceId, id, surface) != 1)
    {
        SBAssert(0,
                 // STRING: GAME 0x6b8d30
                 "P:\\Robin Hood\\RHUIRendererShifting.cpp",
                 0x24,
                 // STRING: GAME 0x6b8d58
                 "Unable to retrieve a resource for the bitmap renderer");
        return false;
    }

    (&m_handles)[m_index & 1] = surface;

    if (surface != 0)
    {
        box = m_box + SBGeoVector2D((float)m_word50, 0.0f);
        m_draw->BlitAlphaKeying(surface, 0, m_unk20, &box, m_word4c, m_word4e, 1);
        return true;
    }

    return false;
}

// Force emission: an unreferenced non-virtual member is dropped by VC6, so an
// out-of-line call from a global instance keeps Render in the build.
void RHUIRendererShifting::Emit()
{
    Render(0);
}

RHUIRendererShifting g_rhuirenderershifting;

void rh_uirenderershifting_emit()
{
    g_rhuirenderershifting.Emit();
}
