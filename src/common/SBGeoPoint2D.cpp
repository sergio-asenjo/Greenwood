#include "SBNullstr.h"
#include "SBGeoPoint2D.h"
#include "SBGeoVector2D.h"
#include "RHMobileUnk006100e0.h"
#include "SB.h"
#include <math.h>

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)

// TEMPLATE: GAME 0x0044e990 FOLDED
// ??_GSBGeoPoint2D@@QAEPAXI@Z

// TEMPLATE: GAME 0x0044e990 FOLDED
// ?FUN_0044e990@SBGeoPoint2D@@QAEPAXI@Z
void *SBGeoPoint2D::FUN_0044e990(unsigned flags)
{
    this->SBGeoPoint2D::~SBGeoPoint2D();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005fc040
SBGeoPoint2D::SBGeoPoint2D(const SBGeoPoint2D &other)
{
    FUN_005fc390(other);
}

// FUNCTION: GAME 0x005fc080
SBGeoPoint2D::~SBGeoPoint2D()
{
    ((RHMobileUnk006100e0 *)this)->FUN_00578c50();
}

// FUNCTION: GAME 0x005fc110
SBGeoVector2D SBGeoPoint2D::Unk005fc110(const SBGeoPoint2D &other) const
{
    SBGeoVector2D difference;
    difference.m_x = m_x - other.m_x;
    difference.m_y = m_y - other.m_y;
    return difference;
}

// FUNCTION: GAME 0x005fc190
SBGeoPoint2D SBGeoPoint2D::Unk005fc190(const SBGeoPoint2D &other) const
{
    SBGeoPoint2D result;
    result.m_x = other.m_x + m_x;
    result.m_y = other.m_y + m_y;
    return result;
}

// FUNCTION: GAME 0x005fc200
SBGeoPoint2D SBGeoPoint2D::FUN_005fc200(const SBGeoPoint2D &other) const
{
    SBGeoPoint2D result;
    result.m_x = m_x - other.m_x;
    result.m_y = m_y - other.m_y;
    return result;
}

// FUNCTION: GAME 0x005fc250
SBGeoPoint2D &SBGeoPoint2D::FUN_005fc250(const SBGeoPoint2D &other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    return *this;
}

// FUNCTION: GAME 0x005fc270
void SBGeoPoint2D::FUN_005fc270()
{
    m_x = (float)floor(m_x);
    m_y = (float)floor(m_y);
}

// FUNCTION: GAME 0x005fc2a0
bool SBGeoPoint2D::Serialize(SBFile &file)
{
    if (file.Access(&m_x, 4) < 0) {
        SBString *error = file.GetError();
        const char *reason = error->m_chars ? error->m_chars : "";
        SBAssert(0,
            // STRING: GAME 0x006bb340
            "P:\\Robin Hood\\SBLibNG\\SBGeoPoint2D.cpp", 264,
            "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_y, 4) < 0) {
        SBString *error = file.GetError();
        const char *reason = error->m_chars ? error->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBGeoPoint2D.cpp", 265,
            "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x005fc330
void SBGeoPoint2D::FUN_005fc330()
{
    m_x = (float)floor(m_x);
    float y = (float)floor(m_y);
    m_y = y;
}

void SBGeoPoint2D::Emit(SBFile &file)
{
    FUN_005fc200(*this);
    FUN_005fc250(*this);
    FUN_005fc270();
    Serialize(file);
    FUN_005fc330();
}
