// Stub definitions for the external symbols RHUIRendererShifting.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHUIRendererShifting::Render resolve. They live in a
// separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBAssert is already defined once, in RHSword_stubs.cpp; this TU only
// declares it (include/SB.h).

#include "RHUIRendererShifting.h"

// SBGeoPoint2D()/~SBGeoPoint2D()/operator= are already defined once in
// RHGroundMark_stubs.cpp; this TU only adds the (float,float) ctor and the
// free operator+ that no other TU provides.

SBGeoPoint2D operator+(const SBGeoPoint2D &point, const SBGeoVector2D &)
{
    return point;
}


SBGeoBoundingBox2D::SBGeoBoundingBox2D()
{
}


SBGeoBoundingBox2D &SBGeoBoundingBox2D::operator=(const SBGeoBoundingBox2D &)
{
    return *this;
}

void SBGeoBoundingBox2D::Copy(const SBGeoBoundingBox2D &)
{
}

SBGeoBoundingBox2D SBGeoBoundingBox2D::operator+(const SBGeoVector2D &) const
{
    return *this;
}

bool SBResourceManager::GetSurfaceForResource(long, unsigned int, unsigned int &)
{
    return false;
}

void SBDrawManager::BlitAlphaKeying(unsigned long, unsigned long, unsigned long,
                                    SBGeoBoundingBox2D *, unsigned short, unsigned short,
                                    unsigned long)
{
}
