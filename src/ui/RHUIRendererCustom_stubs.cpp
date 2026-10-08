// Stub definitions for the external symbols RHUIRendererCustom.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHUIRendererCustom::Render resolve. They live in a
// separate translation unit so VC6 cannot inline them into the matched
// function. They carry no // FUNCTION: marker on purpose (Hard rule 28): a
// matched caller must keep its call operand a symmetric <OFFSET>.
//
// SBAssert is defined once, in RHSword_stubs.cpp. SBGeoPoint2D's ctors/dtors/
// operator= are defined once, in RHGroundMark_stubs.cpp. SBGeoBoundingBox2D's
// default ctor/operator=/operator+ (const SBGeoVector2D&) and
// SBResourceManager::GetSurfaceForResource are defined once, in
// RHUIRendererShifting_stubs.cpp. This TU defines only the genuinely-new
// targets.

#include "RHUIRendererCustom.h"

// Target 0x00609200, ret 0x8 (member returning a box by value, constructed from
// m_p0 - vector and m_p1 - vector via SBGeoPoint2D::operator- at 0x005fc200).
SBGeoBoundingBox2D SBGeoBoundingBox2D::operator-(const SBGeoVector2D &) const
{
    return *this;
}

// Target 0x005e6440, ret 0x14 (five stack arguments, __thiscall).
void RHUnk005e6440::Blit(unsigned long, SBGeoBoundingBox2D *, unsigned long,
                         SBGeoBoundingBox2D *, unsigned long)
{
}
