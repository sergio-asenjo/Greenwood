#include "SBNullstr.h"
#include "SBGeoBoundingBox2D.h"

// FUNCTION: GAME 0x00607c70
bool SBGeoBoundingBox2D::Serialize(SBFile &file)
{
    if (file.Access(m_00, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0,
            // STRING: GAME 0x006bb528
            "P:\\Robin Hood\\SBLibNG\\SBGeoBoundingBox2D.cpp", 0x115,
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(m_00 + 4, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBGeoBoundingBox2D.cpp", 0x116,
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(m_00 + 8, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBGeoBoundingBox2D.cpp", 0x117,
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(m_00 + 12, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBGeoBoundingBox2D.cpp", 0x118,
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(m_00 + 16, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBGeoBoundingBox2D.cpp", 0x11a,
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x00607d90
void SBGeoBoundingBox2D::FUN_00607d90()
{
    m_00[16] = 0;
}

// FUNCTION: GAME 0x00607f00
bool SBGeoBoundingBox2D::FUN_00607f00(const RHMobileUnk006100e0 &segment) const
{
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    if (!m_00[16]) return true;
    {
        first = segment;
        second = *(const SBGeoPoint2D *)segment.m_08;
        const float *bounds = (const float *)m_00;
        if (first.m_x < bounds[0] && second.m_x < bounds[0]) return true;
        if (first.m_x > bounds[2] && second.m_x > bounds[2]) return true;
        if (first.m_y < bounds[1] && second.m_y < bounds[1]) return true;
        if (first.m_y > bounds[3] && second.m_y > bounds[3]) return true;
        return false;
    }
}

// FUNCTION: GAME 0x00608040
bool SBGeoBoundingBox2D::FUN_00608040(const RHMobileUnk006100e0 &segment) const
{
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    if (!m_00[16]) return true;
    {
        first = segment;
        second = *(const SBGeoPoint2D *)segment.m_08;
        const float *bounds = (const float *)m_00;
        if (first.m_x < bounds[0] && second.m_x <= first.m_x) return true;
        if (first.m_x > bounds[2] && second.m_x >= first.m_x) return true;
        if (first.m_y < bounds[1] && second.m_y <= first.m_y) return true;
        if (first.m_y > bounds[3] && second.m_y >= first.m_y) return true;
        return false;
    }
}

// FUNCTION: GAME 0x00608180
bool SBGeoBoundingBox2D::FUN_00608180(const RHMobileUnk006100e0 &segment) const
{
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    if (!m_00[16]) return true;
    {
        first = segment;
        second = *(const SBGeoPoint2D *)segment.m_08;
        const float *bounds = (const float *)m_00;
        if (first.m_x == second.m_x && (first.m_x < bounds[0] || first.m_x > bounds[2])) return true;
        if (first.m_y == second.m_y && (first.m_y < bounds[1] || first.m_y > bounds[3])) return true;
        return false;
    }
}

class SBBoundingSegmentTemporary
{
public:
    SBBoundingSegmentTemporary(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
    {
        ((RHMobileUnk0060a820 *)this)->FUN_0060a820(first, second);
    }
    ~SBBoundingSegmentTemporary()
    {
        ((RHMobileUnk006100e0 *)this)->~RHMobileUnk006100e0();
    }
    RHMobileUnk006100e0 &Value() { return *(RHMobileUnk006100e0 *)this; }
    char m_00[0x10];
};

// Parked: inline segment wrapper reloads the temporary address instead of passing the constructor's eax result; return/cleanup scheduling differs.
// STUB: GAME 0x006082a0
bool RHUnk00608f10::FUN_006082a0(void *value)
{
    const SBGeoBoundingBox2D &box = *(const SBGeoBoundingBox2D *)this;
    const SBGeoBoundingBox2D &other = *(const SBGeoBoundingBox2D *)value;
    SBBoundingSegmentTemporary segment(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f));
    if (box.m_00[16] && other.m_00[16]) {
        ((SBUIInputFieldBoxCalls *)&segment)->FUN_0060a860(
            SBBoundingSegmentTemporary(*(const SBGeoPoint2D *)other.m_00, *(const SBGeoPoint2D *)(other.m_00 + 8)).Value());
        bool rejected = box.FUN_00607f00(segment.Value());
        return rejected;
    }
    return true;
}

// FUNCTION: GAME 0x006083b0
bool SBGeoBoundingBox2D::FUN_006083b0(const SBGeoPoint2D &point) const
{
    if (!m_00[16]) return false;
    const float *bounds = (const float *)m_00;
    return bounds[0] <= point.m_x && bounds[2] > point.m_x &&
        bounds[1] <= point.m_y && bounds[3] > point.m_y;
}

void EmitSBGeoBoundingBox2D(SBGeoBoundingBox2D *box, SBFile &file)
{
    box->Serialize(file);
    box->FUN_00607d90();
    box->FUN_00607f00(*(RHMobileUnk006100e0 *)box);
    box->FUN_00608040(*(RHMobileUnk006100e0 *)box);
    box->FUN_00608180(*(RHMobileUnk006100e0 *)box);
    ((RHUnk00608f10 *)box)->FUN_006082a0(box);
    box->FUN_006083b0(*(SBGeoPoint2D *)box);
}
