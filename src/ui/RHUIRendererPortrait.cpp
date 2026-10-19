// RHUIRendererPortrait.cpp — translation unit with __FILE__ evidence at 0x005cbbe0
// ("P:\Robin Hood\RHUIRendererPortrait.cpp", symbols/functions-by-file.tsv:406).
//
// BINDING (0x005cbbe0 -> RHUIRendererPortrait::BlitPicture(unsigned int, float)):
//   see include/RHUIRendererPortrait.h for the full evidence chain.
//
// STATUS: exact 100% — instruction-for-instruction identical to the original.

#include "SBNullstr.h"
#include "RHUIRendererPortrait.h"

// GLOBAL: GAME 0x0067755c
float g_rhuirendererportrait_percent = 100.0f;

// LIBRARY: GAME 0x005cac40
// ?find@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QBEIPBGII@Z

#include "SBGeoBoundingBox2D.h"
#include "RHUnk005cbb80.h"

// FUNCTION: GAME 0x005cbb80
RHUnk005cbb80::RHUnk005cbb80()
{
    *(unsigned *)this = 0x00679eac;
    m_4c = 0;
    m_50 = 0;
    m_54 = 0;
    m_58 = 0;
    m_5c = 0;
    m_60 = 0;
}

// FUNCTION: GAME 0x005cbbb0
void *RHUnk005cbb80::FUN_005cbbb0(unsigned flags)
{
    this->~RHUnk005cbb80();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005cbbd0
RHUnk005cbb80::~RHUnk005cbb80()
{
}

// FUNCTION: GAME 0x005cbbe0
bool RHUIRendererPortrait::BlitPicture(unsigned int id, float f)
{
    // The copy through a float temp reproduces the original x87 operand order
    // (fld value before the named multiplier) — see Hard rule 16.
    float value = f;
    int frame = (int)(value * g_rhuirendererportrait_percent);

    if (m_resource->ResolveSurface(m_surface, id, &f) == 1)
    {
        int percent = frame & 0xffff;

        if (percent != 0)
        {
            if (percent != 100)
            {
                return m_draw->BlitScaled(f, 0, 0, &m_widget, frame, 1);
            }

            return m_draw->BlitFull(f, 0, 0, &m_widget, 1);
        }

        return true;
    }

    SBAssert(0,
             // STRING: GAME 0x6b8ccc
             "P:\\Robin Hood\\RHUIRendererPortrait.cpp",
             0x35,
             // STRING: GAME 0x6b8cf4
             "Unable to retreive a surface for the portrait rendering.");
    return false;
}

// Force emission: an unreferenced non-virtual member is dropped by VC6, so an
// out-of-line call from a global instance keeps BlitPicture in the build.
void RHUIRendererPortrait::Emit()
{
    BlitPicture(0, 0.0f);
}

RHUIRendererPortrait g_rhuirendererportrait;

void rh_uirendererportrait_emit()
{
    g_rhuirendererportrait.Emit();
}
