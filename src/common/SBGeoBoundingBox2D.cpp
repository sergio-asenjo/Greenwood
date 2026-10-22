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
        second = segment.Second();
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
        second = segment.Second();
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
        second = segment.Second();
        const float *bounds = (const float *)m_00;
        if (first.m_x == second.m_x && (first.m_x < bounds[0] || first.m_x > bounds[2])) return true;
        if (first.m_y == second.m_y && (first.m_y < bounds[1] || first.m_y > bounds[3])) return true;
        return false;
    }
}

// FUNCTION: GAME 0x006082a0
bool RHUnk00608f10::FUN_006082a0(void *value)
{
    const SBGeoBoundingBox2D &box = *(const SBGeoBoundingBox2D *)this;
    const SBGeoBoundingBox2D &other = *(const SBGeoBoundingBox2D *)value;
    SBGeoSegment2D segment(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f));
    if (box.m_00[16] && other.m_00[16]) {
        ((SBUIInputFieldBoxCalls *)&segment)->FUN_0060a860((const RHMobileUnk006100e0 &)
            SBGeoSegment2D(*(const SBGeoPoint2D *)other.m_00, *(const SBGeoPoint2D *)(other.m_00 + 8)));
        bool rejected = box.FUN_00607f00((const RHMobileUnk006100e0 &)segment);
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

// FUNCTION: GAME 0x006085a0
bool SBGeoBoundingBox2D::FUN_006085a0(const SBGeoPoint2D &point) const
{
    float x = point.m_x;
    float y = point.m_y;
    const float *bounds = (const float *)m_00;
    float left = bounds[0];
    float bottom = bounds[1];
    float right = bounds[2];
    float top = bounds[3];
    if (x == left || x == right)
        return bottom <= y && y <= top;
    if (y == bottom || y == top)
        return left <= x && x <= right;
    return false;
}

// FUNCTION: GAME 0x00608650
bool SBGeoBoundingBox2D::FUN_00608650(const RHMobileUnk006100e0 &segment) const
{
    if (!m_00[16]) return false;
    if (FUN_00607f00(segment)) return false;
    if (FUN_00608400(segment) || FUN_00608400(segment.Second())) return true;
    return ((const RHBoxIntersection00608800 *)this)->FUN_00608800(RHBoxLine00610070(segment));
}

// FUNCTION: GAME 0x00608730
bool SBGeoBoundingBox2D::FUN_00608730(const RHMobileUnk006100e0 &segment) const
{
    if (!m_00[16]) return false;
    if (FUN_00608040(segment)) return false;
    if (FUN_00608400(segment)) return true;
    return ((const RHBoxIntersection00608800 *)this)->FUN_00608800(RHBoxLine00610070(segment));
}

#include "sbgeo_00610600.h"

// FUNCTION: GAME 0x00608c70
bool SBGeoBoundingBox2D::FUN_00608c70(const RHMobileUnk00611360 &line) const
{
    bool intersecting = false;
    if (line.FUN_00610f30() == 0)
        return false;
    if (line.FUN_00610f30() == 1)
        return FUN_00608400(((RHUnkSectorPoints *)&line)->FUN_006112c0(0));
    unsigned long last = line.FUN_00610f30() - 1;
    long index = 0;
    for (; !intersecting && index <= last; ++index)
        intersecting = FUN_00608400(((RHUnkSectorPoints *)&line)->FUN_006112c0(index));
    if (intersecting)
        return true;
    for (index = 0; !intersecting && index < last; ++index)
        intersecting = FUN_00608650((const RHMobileUnk006100e0 &)line.FUN_006112d0(index));
    return intersecting;
}

#include "RHElementAreaShape.h"

// Parked: native array cleanup calls cdecl _Destroy instead of the target's flags-zero point destructor.
// STUB: GAME 0x00608d60
bool SBGeoBoundingBox2D::FUN_00608d60(const RHUnkSectorPoints &polygon) const
{
    RHUnkSectorPoints &points = (RHUnkSectorPoints &)polygon;
    if (points.Unk0060ce80() == 0)
        return false;
    if (points.Unk0060ce80() == 1)
        return FUN_00608400(points.Unk0060cef0(0));
    if (FUN_00608c70(RHMobileUnk00611360((const RHMobileUnk00611360 &)polygon)))
        return true;
    if (FUN_00608650((const RHMobileUnk006100e0 &)SBGeoSegment2D(
            points.Unk0060cef0(0), points.Unk0060cef0(points.Unk0060ce80() - 1))))
        return true;
    return ((const RHElementAreaShape *)&polygon)->FUN_0060c660(*(const SBGeoPoint2D *)this);
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
    box->FUN_006085a0(*(SBGeoPoint2D *)box);
    box->FUN_00608650(*(RHMobileUnk006100e0 *)box);
    box->FUN_00608730(*(RHMobileUnk006100e0 *)box);
    box->FUN_00608c70(*(RHMobileUnk00611360 *)box);
    box->FUN_00608d60(*(RHUnkSectorPoints *)box);
}

#include "SBGeoIntersection2D.h"

// FUNCTION: GAME 0x006093f0
RHUnk0060fbf0 SBGeoBoundingBox2D::FUN_006093f0(const RHMobileUnk006100e0 &segment) const
{
    if (FUN_00607f00(segment))
        return RHUnk0060fbf0();
    return FUN_00609440(segment, 0.0, 1.0);
}
