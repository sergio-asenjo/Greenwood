#include "SBNullstr.h"
#include "RHElementFX.h"

SBGeoBoundingBox2D RHUnkFXSprite::Unk005bd970() { return *(SBGeoBoundingBox2D *)0; }
// FUNCTION: GAME 0x006092a0
SBGeoBoundingBox2D &SBGeoBoundingBox2D::operator-=(const SBGeoVector2D &vector)
{
    m_p0.FUN_005fc250(vector);
    m_p1.FUN_005fc250(vector);
    return *this;
}
// FUNCTION: GAME 0x00608f30
bool SBGeoBoundingBox2D::Unk00608f30() const { return m_flag; }
unsigned long RHUnkFXDraw::Unk005e4ed0(int, int, int, int) { return 0; }
