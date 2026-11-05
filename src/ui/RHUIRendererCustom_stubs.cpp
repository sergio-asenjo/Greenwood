#include "SBNullstr.h"
#include "RHUIRendererCustom.h"

// FUNCTION: GAME 0x00609200
SBGeoBoundingBox2D SBGeoBoundingBox2D::operator-(const SBGeoVector2D &offset) const
{
    return SBGeoBoundingBox2D(m_p0.FUN_005fc200(offset), m_p1.FUN_005fc200(offset));
}
