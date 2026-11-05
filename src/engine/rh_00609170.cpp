#include "SBGeoBoundingBox2DCore.h"

// FUNCTION: GAME 0x00609170
int SBGeoBoundingBox2D::FUN_00609170(const SBGeoBoundingBox2D &other) const
{
    if (other.m_p0 == m_p0 && other.m_p1 == m_p1)
        return 0;
    return 1;
}
