// RHUIRendererShifting.cpp — translation unit with __FILE__ evidence at
// 0x006b8d30 ("P:\Robin Hood\RHUIRendererShifting.cpp",
// symbols/functions-by-file.tsv:407).
//
// BINDING (0x005cbe60 -> RHUIRendererShifting::Render(SBResourceWidgetID)):
//   see include/RHUIRendererShifting.h for the full evidence chain.
//
// STATUS: exact 100% — instruction-for-instruction identical to the original.

#include "SBNullstr.h"
// SIZE 0x14
class RHMobileUnk00607da0
{
public:
    void FUN_00607990(const RHMobileUnk00607da0 &other);
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
    unsigned char m_00[0x14]; // 0x00
};
#include "RHUIRendererShifting.h"
#include "RHPortraitRenderer005cadc0.h"

void EmitShiftingLifetime(RHUIRendererShifting *value, unsigned flags)
{
    value->RHUIRendererShifting::RHUIRendererShifting();
    value->FUN_005cbe30(flags);
}

// FUNCTION: GAME 0x005cbe10
RHUIRendererShifting::RHUIRendererShifting()
{
    ((RHPortraitRenderer0060dab0 *)this)->RHPortraitRenderer0060dab0::RHPortraitRenderer0060dab0();
    *(unsigned *)this = 0x00679ebc;
    *(unsigned short *)((char *)this + 0x50) = 0;
}

// FUNCTION: GAME 0x005cbe30
void *RHUIRendererShifting::FUN_005cbe30(unsigned flags)
{
    this->~RHUIRendererShifting();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005cbe50
RHUIRendererShifting::~RHUIRendererShifting()
{
    *(unsigned *)this = 0x00679ebc;
    ((RHPortraitRenderer0060dab0 *)this)->~RHPortraitRenderer0060dab0();
}

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

    if (((RHUnk00600820 *)m_resource)->ResolveSurface((void *)m_resourceId, id, (float *)&surface) != 1)
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
        ((RHMobileUnk00607da0 *)&box)->FUN_00607da0((const RHMobileUnk00607da0 &)(m_box + SBGeoVector2D((float)m_word50, 0.0f)));
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
