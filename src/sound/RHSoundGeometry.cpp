// RHSoundGeometry.cpp — translation unit with __FILE__ evidence at 0x005b3510
// ("P:\Robin Hood\RHsoundgeometry.cpp", symbols/functions-by-file.tsv). The two
// functions carrying this __FILE__ are GetVolumeForAltitude (0x005b32e0) and
// Serialize (0x005b3510).
//
// BINDING (0x005b32e0 -> RHSoundGeometry::GetVolumeForAltitude(float,
// RHsoundSourceAltitude)) and (0x005b3510 -> RHSoundGeometry::Serialize(SBFile&)):
// see include/RHSoundGeometry.h for the full evidence chain and member layout.
//
// The `// STRING:` and `// GLOBAL:` markers pin literals/constants to their
// original Game.exe addresses: the original is a fixed-base EXE, so its
// absolute string pointers and numeric `.rdata` operands carry no relocation
// records and reccmp cannot discover them by scanning.

#include "SBNullstr.h"
#include "RHFastFindGeometry.h"
#define SBGEO_POINT2D_VIEW
#define SBGEO_VECTOR2D_VIEW
#include "SBGeoSegment2D.h"
#include "SBGeoIntersection2D.h"
#include "RHUnk0053bf20.h"
#include "SCQuad.h"
#include "RHSoundGeometry.h"
#include "RHSoundGeometryCalls.h"
#include "Decomp.h"
#include <math.h>

extern float g_unk0x006785d8;

DECOMP_SIZE_ASSERT(RHSoundGeometry, 0xc8)



// The numeric .rdata constants GetVolumeForAltitude reads. The original is a
// fixed-base EXE, so these appear as absolute literals (`ds:0x67749c` etc.)
// with no relocations; reccmp cannot discover them from our DLL's relocations,
// so each is pinned with a `// GLOBAL:` marker on its definition here. Identity
// is unproven (no Windows-side string/tag names them), so they keep the
// address-based placeholder convention (docs/05-naming.md).
//
//
//
// GLOBAL: GAME 0x006774b8
double g_unk0x006774b8 = 0.5;
//
//
// GLOBAL: GAME 0x00677d90
double g_unk0x00677d90 = 1.0;


// FUNCTION: GAME 0x005b2430
RHSoundGeometry::RHSoundGeometry()
    : m_0(0.0f, 0.0f), m_8(0), m_c(0), m_10(0), m_14(0), m_18(0), m_1c(0)
{
}

// FUNCTION: GAME 0x005b2510
float RHSoundGeometry::FUN_005b2510(float distance, const RHUnk005b2410 &range)
{
    if (distance > range.m_00)
        return range.m_04;
    if (!(distance > range.m_08))
        return range.m_0c;
    return ((distance - range.m_08) / (range.m_00 - range.m_08)) * (range.m_04 - range.m_0c) + range.m_0c;
}


// FUNCTION: GAME 0x005b2560
float RHSoundGeometry::FUN_005b2560(const SBGeoPoint2D &point, const RHUnk005b2410 &range)
{
    float distance = (float)fabs(*(const float *)&point);
    if (distance < range.m_08)
        return 0.0f;
    if (distance >= range.m_00)
        return *(const float *)&point >= 0.0f ? 1 : -1;
    return *(const float *)&point >= 0.0f
        ? (distance - range.m_08) / (range.m_00 - range.m_08)
        : -((distance - range.m_08) / (range.m_00 - range.m_08));
}

// FUNCTION: GAME 0x005b25e0
float RHSoundGeometry::FUN_005b25e0(const RHUnk005b2410 &range)
{
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    switch (m_20)
    {
    case 1:
        return FUN_005b2560(m_ac, range);
    }
    float sum = 0.0f;
    unsigned short count = 0;
    unsigned short i;
    for (i = 0; i < m_20; ++i)
    {
        float distance = m_48[i];
        if (distance < range.m_00)
        {
            if (distance < range.m_08)
                return 0.0f;
            sum += FUN_005b2560(m_24[i], range) * FUN_005b2510(distance, range);
            ++count;
        }
    }
    for (i = 0; i < m_20 - 1; ++i)
    {
        float distance = m_68[i];
        if (distance != g_unk0x006785d8 && distance < range.m_00)
        {
            if (distance < range.m_08)
                return 0.0f;
            sum += FUN_005b2560(m_88[i], range) * FUN_005b2510(distance, range);
            ++count;
        }
    }
    if (count)
        return sum / count;
    return 0.0f;
}

// FUNCTION: GAME 0x005b27e0
float RHSoundGeometry::FUN_005b27e0(const RHUnk005b2410 &range)
{
    SBGeoPoint2D point;
    switch (m_20)
    {
    default:
    {
        float sum = 0.0f;
        unsigned short count = 0;
        unsigned short i;
        for (i = 0; i < m_20; ++i)
        {
            float distance = m_48[i];
            if (distance < range.m_00)
            {
                if (distance < range.m_08)
                    return 0.0f;
                point = m_24[i];
                sum += Weight(SBGeoPoint2D(point.m_y, point.m_x), distance, range);
                ++count;
            }
        }
        for (i = 0; i < m_20 - 1; ++i)
        {
            float distance = m_68[i];
            if (distance != g_unk0x006785d8 && distance < range.m_00)
            {
                if (distance < range.m_08)
                    return 0.0f;
                point = m_88[i];
                sum += Weight(SBGeoPoint2D(point.m_y, point.m_x), distance, range);
                ++count;
            }
        }
        if (count)
            return sum / count;
        return 0.0f;
    }
    case 1:
        return FUN_005b2560(SBGeoPoint2D(m_ac.m_y, m_ac.m_x), range);
    }
}

// FUNCTION: GAME 0x005b2a30
void RHSoundGeometry::FUN_005b2a30(RHUnk005a7220 *source, RHUnk005b2410 &)
{
    SBGeoPoint2D previous;
    int count = 0;
    SBGeoPoint2D current;
    RHUnk005fc3b0 normal;
    RHMobileUnk006100e0 line(SBGeoPoint2D(0, 0), SBGeoPoint2D(0, 0));
    RHUnk0060fbf0 intersection;
    RHUnk005b35e0Array<SBGeoPoint2D> &points = *(RHUnk005b35e0Array<SBGeoPoint2D> *)source->m_1c;
    if (source->m_20)
        count = source->m_24 - source->m_20;
    m_20 = count;
    if (m_24.GetSize() < m_20)
    {
        m_24.SetSize(m_20);
        m_48.SetSize(m_20);
        m_68.SetSize(m_20 - 1);
        m_88.SetSize(m_20 - 1);
    }
    m_b4 = 1000000.0f;
    unsigned short i;
    for (i = 0; i < m_20; ++i)
    {
        previous = points[i];
        previous.m_x = previous.m_x - m_0.m_x;
        previous.m_y = (previous.m_y - m_0.m_y) * 1.7434468269348145f;
        m_24[i] = previous;
        float distance = (float)sqrt(previous.m_y * previous.m_y + previous.m_x * previous.m_x);
        if (distance < m_b4)
        {
            m_b4 = distance;
            m_ac = previous;
        }
        m_48[i] = distance;
    }
    if (m_20 >= 2)
    {
        previous = m_24[0];
        for (i = 1; i < m_20; ++i)
        {
            current = m_24[i];
            normal.FUN_005fc430(((RHUnk005fc3b0 &)current.Unk005fc110(previous)).FUN_005fc8f0(true, 1.0f));
            normal.FUN_005fc7c0(1.0f);
            (SBGeoPoint2D &)line = SBGeoPoint2D(0, 0);
            line.Second() = normal;
            intersection.FUN_0060fca0(SBGeoSegment2D(previous, current).FUN_0060ad60(line));
            if (((SCQuadArg *)&intersection)->GetType() == 1)
            {
                previous = *(SBGeoPoint2D *)((RHUnk0053bf20 *)&intersection)->FUN_0053bf20();
                float distance = (float)sqrt(previous.m_y * previous.m_y + previous.m_x * previous.m_x);
                if (distance < m_b4)
                {
                    SBGeoPoint2D position;
                    m_b4 = distance;
                    m_ac = previous;
                    position.m_x = previous.m_x + m_0.m_x;
                    position.m_y = previous.m_y * 0.5735764503479004f + m_0.m_y;
                }
                m_68[i - 1] = distance;
                m_88[i - 1] = previous;
            }
            else
                m_68[i - 1] = -1.0f;
            previous = current;
        }
    }
}

// FUNCTION: GAME 0x005b2f30
void RHSoundGeometry::RHUnk005b2f30(float value)
{
    m_8 = value;
    if (value < 1.0f)
    {
        float factor = 1.0f - (value + value);
        m_b8 = factor * 400.0f + 1200.0f;
        float range = factor * 120.0f + 360.0f;
        m_bc = range;
        m_c0 = factor * 320.0f + 960.0f;
        m_c4 = range;
    }
    else
    {
        float factor = 1.0f - value;
        m_b8 = factor * 400.0f + 800.0f;
        float range = factor * 80.0f + 240.0f;
        m_bc = range;
        m_c0 = factor * 320.0f + 640.0f;
        m_c4 = range;
    }
}

// FUNCTION: GAME 0x005b32e0
float RHSoundGeometry::GetVolumeForAltitude(float altitude, RHsoundSourceAltitude type)
{
    switch (type)
    {
    case RH_ALTITUDE_0:
    {
        float height = m_8;
        return height * altitude * g_unk0x006774b8;
    }
    case RH_ALTITUDE_3:
        return altitude;
    default:
        if (m_8 > 1.0f)
        {
            switch (type)
            {
            case RH_ALTITUDE_1:
                return (g_unk0x00677d90 - (double)(m_8 - 1.0f) * g_unk0x006774b8) * altitude;
            case RH_ALTITUDE_2:
                return (g_unk0x006774b8 - (double)(m_8 - 1.0f) * 0.25) * altitude;
            default:
                SBAssert(1,
                         "P:\\Robin Hood\\RHsoundgeometry.cpp",
                         0x291,
                         // STRING: GAME 0x6b8668
                         "Unknown altitude for sound source !");
                return 0.0f;
            }
        }
        switch (type)
        {
        case RH_ALTITUDE_1:
            return m_8 * altitude;
        case RH_ALTITUDE_2:
            return (float)(g_unk0x006774b8 / m_8) * altitude;
        default:
            return 0.0f;
        }
    }
}

// FUNCTION: GAME 0x005b3510
bool RHSoundGeometry::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b868c
    RHSerializeName(file, "RHSoundGeometry");

    if (file.Access(&m_0.m_x, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        // NOTE: the empty string 0x006773d0 and the format
        // "Serialize failed reason is %s" (0x006a7390) are the same original
        // entities used by RHSword::SerializePointer; reccmp allows exactly one
        // marker per original address, so those two are annotated once in
        // src/RHSword.cpp. This function's reference resolves to the same
        // pooled entities.
        SBAssert(0,
                 // STRING: GAME 0x6b8644
                 "P:\\Robin Hood\\RHsoundgeometry.cpp",
                 805,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_0.m_y, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsoundgeometry.cpp", 806, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_8, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsoundgeometry.cpp", 807, "Serialize failed reason is %s", reason);
        return false;
    }

    RHUnk005b2f30(m_8);

    return true;
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps RHSoundGeometry::Serialize in the build.
void RHSoundGeometry::Emit(SBFile &file)
{
    Serialize(file);
    m_8 = GetVolumeForAltitude(m_8, RH_ALTITUDE_0);
}
