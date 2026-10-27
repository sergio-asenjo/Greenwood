// RHLine.cpp — translation unit with __FILE__ evidence at 0x00521210 / 0x00521810
// / 0x005218e0 ("P:\Robin Hood\RHline.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005218e0 -> RHSeekPoint::SerializeAllData(SBFile&)):
//   - its first act writes the tag "RHSeekPoint::SerializeAllData" (0x006b0744)
//     via RHSerializeName (0x005e1b70);
//   - its final act is a call to 0x00521810; the Mac oracle's
//     RHSeekPoint::SerializeAllData ends by calling RHSeekPoint::SerializeStatus.
//
// BINDING (0x00521810 -> RHSeekPoint::SerializeStatus(SBFile&)):
//   - it writes the tag "RHSeekPoint" (0x006b0738);
//   - its field sequence (+0x14 dword, +0x38 byte, +0x39 byte) matches the Mac
//     RHSeekPoint::SerializeStatus (symbols/mac-functions-by-file.tsv);
//   - it is the tail callee of 0x005218e0, fixing it as the status serialiser.
//
// BINDING (0x00521210 -> RHUnk004b2190Member::Serialize(SBFile&)) — provisional:
//   - it writes NO tag and its leading field sequence (+0x04, +0x08, +0x34, two
//     embedded SBGeoPoint2D, four dwords, byte flags) matches the Mac
//     RHRepulsivePoint::Serialize; no Windows-side tag exists, so the class keeps
//     the neutral name RHElementObject.h already declares for its +0xbc member.
//   - it is called from RHElementObject::Serialize at +0xbc (0x004b22f4), plus
//     three not-yet-decompiled call sites.
//
#include "SBNullstr.h"
#include "RHLine.h"
#include <stddef.h>

DECOMP_SIZE_ASSERT(RHSeekPointVector, 0x10)
DECOMP_SIZE_ASSERT(RHSeekPointIndices, 0x20)
DECOMP_SIZE_ASSERT(RHSeekPoint, 0x3c)
DECOMP_STATIC_ASSERT(offsetof(RHSeekPointIndices, m_current) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHSeekPointIndices, m_dirty) == 0x14)
DECOMP_STATIC_ASSERT(offsetof(RHSeekPointIndices, m_forward) == 0x15)
DECOMP_STATIC_ASSERT(offsetof(RHSeekPointIndices, m_index) == 0x18)
DECOMP_STATIC_ASSERT(offsetof(RHSeekPointIndices, m_value) == 0x1c)
DECOMP_STATIC_ASSERT(offsetof(RHSeekPoint, m_18) == 0x18)
DECOMP_STATIC_ASSERT(offsetof(RHSeekPoint, m_38) == 0x38)
DECOMP_STATIC_ASSERT(offsetof(RHSeekPointDirectionView, value) == 0x10)

// FUNCTION: GAME 0x00521210
bool RHUnk004b2190Member::Serialize(SBFile &file)
{
    if (file.Access(&m_4, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b071c
                 "P:\\Robin Hood\\RHline.cpp",
                 0x5c5,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }
    if (file.Access(&m_8, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5c6, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_34, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5c8, "Serialize failed reason is %s", reason);
        return false;
    }

    m_14.Serialize(file);
    m_1c.Serialize(file);

    if (file.Access(&m_24, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5cd, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_28, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5ce, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5cf, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_30, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d0, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_3c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d2, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_35, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d4, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_36, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d5, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_37, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d6, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_38, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x5d7, "Serialize failed reason is %s", reason);
        return false;
    }

    return true;
}

void RHUnk004b2190Member::Emit(SBFile &file)
{
    Serialize(file);
}

// FUNCTION: GAME 0x00521810
bool RHSeekPoint::SerializeStatus(SBFile &file)
{
    // STRING: GAME 0x6b0738
    RHSerializeName(file, "RHSeekPoint");

    if (file.Access(&m_14, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x6e5, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_38, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x6e6, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_39, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", 0x6e7, "Serialize failed reason is %s", reason);
        return false;
    }

    return true;
}

class RHUnkPathGeometry
{
public:
    bool Unk004fbec0(SBFile &file, void *&value);
};

struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

#define RHSEEK_ACCESS(value, bytes, line) \
    if (file.Access(&(value), bytes) < 0) { \
        SBString *error = file.GetError(); \
        const char *reason = error->m_chars ? error->m_chars : ""; \
        SBAssert(0, "P:\\Robin Hood\\RHline.cpp", line, "Serialize failed reason is %s", reason); \
        return false; \
    }

// FUNCTION: GAME 0x005218e0
bool RHSeekPoint::SerializeAllData(SBFile &file)
{
    // STRING: GAME 0x6b0744
    RHSerializeName(file, "RHSeekPoint::SerializeAllData");
    RHSEEK_ACCESS(m_4, 4, 0x6fe);
    RHSEEK_ACCESS(m_8, 4, 0x6ff);
    RHSEEK_ACCESS(m_10, 2, 0x700);
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_c);
    RHSEEK_ACCESS(m_14, 4, 0x702);
    unsigned long count;
    unsigned short value;
    if (file.m_bLoading) {
        RHSEEK_ACCESS(count, 4, 0x707);
        RHSeekPointIndices &indices = m_18;
        indices.m_values.Clear();
        indices.m_dirty = true;
        for (unsigned long index = 0; index < count; ++index) {
            RHSEEK_ACCESS(value, 2, 0x70d);
            if (indices.FUN_005226a0(value, true) == -1) {
                typedef std::vector<unsigned short> Values;
                void (Values::*insert)(unsigned short *, unsigned, const unsigned short &) = &Values::insert;
                (indices.m_values.*insert)(indices.m_values.end(), 1, value);
                indices.m_dirty = true;
            }
        }
    } else {
        count = m_18.m_values.size();
        RHSEEK_ACCESS(count, 4, 0x715);
        for (unsigned long index = 0; index < count; ++index) {
            value = m_18.m_values[index];
            RHSEEK_ACCESS(value, 2, 0x71b);
        }
    }
    RHSEEK_ACCESS(m_38, 1, 0x71f);
    RHSEEK_ACCESS(m_39, 1, 0x720);
    if (SerializeStatus(file))
        return true;
    return false;
}

#undef RHSEEK_ACCESS

// STUB: GAME 0x00521c10
RHSeekPoint::RHSeekPoint(const RHSeekPointDirectionView *source)
{
    *(unsigned long *)m_pad0 = 0x00679134;
    *(RHMalignityPosition *)&m_4 = source->position;
    m_18.Add(source->value);
    m_14 = 0;
    m_39 = false;
}

// FUNCTION: GAME 0x00521d00
RHSeekPointIndices::~RHSeekPointIndices()
{
    m_values.clear();
}

SBGeoVector2D FUN_0040ec20(const RHMalignityPosition &first, RHMalignityPosition second);

// STUB: GAME 0x00522070
bool RHSeekPoint::FUN_00522070(const RHSeekPointDirectionView *source)
{
    if (FUN_0040ec20(source->position, *(RHMalignityPosition *)&m_4).FUN_005fc700(1.0f) <= 10.0f) {
        m_18.Add(source->value);
        return true;
    }
    return false;
}

// STUB: GAME 0x005226a0
long RHSeekPointIndices::FUN_005226a0(const unsigned short &value, bool forward)
{
    return Find(value, forward);
}

void RHSeekPoint::Emit(SBFile &file)
{
    RHSeekPoint point((const RHSeekPointDirectionView *)this);
    FUN_00522070((const RHSeekPointDirectionView *)this);
    SerializeStatus(file);
    SerializeAllData(file);
}
