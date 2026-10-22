// Stub definitions for the external symbols RHUIRendererShifting.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHUIRendererShifting::Render resolve. They live in a
// separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBAssert is already defined once, in RHSword_stubs.cpp; this TU only
// declares it (include/SB.h).

#include "SBNullstr.h"
#include "RHUIRendererShifting.h"

typedef char SBGeoBoundingBox2DSize[(sizeof(SBGeoBoundingBox2D) == 0x14) ? 1 : -1];

// SBGeoPoint2D()/~SBGeoPoint2D()/operator= are already defined once in
// RHGroundMark_stubs.cpp; this TU only adds the (float,float) ctor and the
// free operator+ that no other TU provides.

SBGeoPoint2D operator+(const SBGeoPoint2D &point, const SBGeoVector2D &)
{
    return point;
}


// FUNCTION: GAME 0x006079c0
SBGeoBoundingBox2D::SBGeoBoundingBox2D()
{
    m_flag = false;
    m_p0 = SBGeoPoint2D(0.0f, 0.0f);
    m_p1 = SBGeoPoint2D(0.0f, 0.0f);
}

// FUNCTION: GAME 0x00607b40
SBGeoBoundingBox2D::SBGeoBoundingBox2D(const SBGeoSegment2D &segment)
{
    m_flag = false;
    FUN_00607e30((const RHMalignitySegment &)segment);
    m_flag = true;
}

void EmitSBGeoBoundingBoxSegment(const SBGeoSegment2D &segment)
{
    SBGeoBoundingBox2D box(segment);
}


SBGeoBoundingBox2D &SBGeoBoundingBox2D::operator=(const SBGeoBoundingBox2D &)
{
    return *this;
}

void SBGeoBoundingBox2D::Copy(const SBGeoBoundingBox2D &)
{
}

void SBDrawManager::BlitAlphaKeying(unsigned long, unsigned long, unsigned long,
                                    SBGeoBoundingBox2D *, unsigned short, unsigned short,
                                    unsigned long)
{
}
