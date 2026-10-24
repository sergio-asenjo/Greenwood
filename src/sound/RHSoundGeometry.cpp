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
#include "RHSoundGeometry.h"
#include "RHSoundGeometryCalls.h"
#include "Decomp.h"
#include <math.h>

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


// FUNCTION: GAME 0x005b2510
float RHUnk005b2ff0Geometry::FUN_005b2510(float distance, const RHUnk005b2410 &range)
{
    if (distance > range.m_00)
        return range.m_04;
    if (!(distance > range.m_08))
        return range.m_0c;
    return ((distance - range.m_08) / (range.m_00 - range.m_08)) * (range.m_04 - range.m_0c) + range.m_0c;
}


// FUNCTION: GAME 0x005b2560
float RHUnk005b2ff0Geometry::FUN_005b2560(const SBGeoPoint2D &point, const RHUnk005b2410 &range)
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

    if (file.Access(&m_0, 4) < 0)
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

    if (file.Access(&m_4, 4) < 0)
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
