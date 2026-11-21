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
        ((SBUIInputFieldBoxCalls *)&segment)->FUN_0060a860(
            SBGeoSegment2D(*(const SBGeoPoint2D *)other.m_00, *(const SBGeoPoint2D *)(other.m_00 + 8)).Line());
        bool rejected = box.FUN_00607f00(segment.Line());
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
    return FUN_00608800(RHMobileUnk006100e0((const SBGeoSegment2D &)segment));
}

// FUNCTION: GAME 0x00608730
bool SBGeoBoundingBox2D::FUN_00608730(const RHMobileUnk006100e0 &segment) const
{
    if (!m_00[16]) return false;
    if (FUN_00608040(segment)) return false;
    if (FUN_00608400(segment)) return true;
    return FUN_00608800(RHMobileUnk006100e0((const RHLineSource00610000 &)segment));
}

#include "RHUnk005fc3b0.h"

// FUNCTION: GAME 0x00608800
bool SBGeoBoundingBox2D::FUN_00608800(const RHMobileUnk006100e0 &line) const
{
    SBGeoPoint2D rightBottom;
    SBGeoPoint2D leftTop;
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    SBGeoVector2D direction;
    if (!m_00[16])
        return false;
    if (FUN_00608180(line))
        return false;
    else
    {
        first = line;
        second = line.Second();
        direction = second.Unk005fc110(first);
        const float *bounds = (const float *)m_00;
        rightBottom = SBGeoPoint2D(bounds[2], bounds[1]);
        leftTop = SBGeoPoint2D(bounds[0], bounds[3]);
        float side = ((RHUnk005fc3b0 *)&direction)->FUN_005fc680(
            (const RHUnk005fc3b0 &)((const SBGeoPoint2D *)m_00)->Unk005fc110(first), 1.0f);
        if (side == 0.0f)
            return true;
        if (side > 0.0f)
            return ((RHUnk005fc3b0 *)&direction)->FUN_005fc680((const RHUnk005fc3b0 &)rightBottom.Unk005fc110(first), 1.0f) <= 0.0f ||
                ((RHUnk005fc3b0 *)&direction)->FUN_005fc680((const RHUnk005fc3b0 &)((const SBGeoPoint2D *)(m_00 + 8))->Unk005fc110(first), 1.0f) <= 0.0f ||
                ((RHUnk005fc3b0 *)&direction)->FUN_005fc680((const RHUnk005fc3b0 &)leftTop.Unk005fc110(first), 1.0f) <= 0.0f;
        else
            return ((RHUnk005fc3b0 *)&direction)->FUN_005fc680((const RHUnk005fc3b0 &)rightBottom.Unk005fc110(first), 1.0f) >= 0.0f ||
                ((RHUnk005fc3b0 *)&direction)->FUN_005fc680((const RHUnk005fc3b0 &)((const SBGeoPoint2D *)(m_00 + 8))->Unk005fc110(first), 1.0f) >= 0.0f ||
                ((RHUnk005fc3b0 *)&direction)->FUN_005fc680((const RHUnk005fc3b0 &)leftTop.Unk005fc110(first), 1.0f) >= 0.0f;
    }
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
        intersecting = FUN_00608650(line.FUN_006112d0(index).Line());
    return intersecting;
}

#include "RHElementAreaShape.h"

// FUNCTION: GAME 0x00608d60
bool SBGeoBoundingBox2D::FUN_00608d60(const RHUnkSectorPoints &polygon) const
{
    RHUnkSectorPoints &points = (RHUnkSectorPoints &)polygon;
    if (points.Unk0060ce80() == 0)
        return false;
    if (points.Unk0060ce80() == 1)
        return FUN_00608400(points.Unk0060cef0(0));
    if (FUN_00608c70(RHMobileUnk00611360((const RHMobileUnk00611360 &)polygon)))
        return true;
    if (FUN_00608650(reinterpret_cast<const RHMobileUnk006100e0 &>(
            static_cast<const SBGeoSegment2D &>(SBGeoSegment2D(
                points.Unk0060cef0(0), points.Unk0060cef0(points.Unk0060ce80() - 1))))))
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

// STUB: GAME 0x00609440
RHUnk0060fbf0 SBGeoBoundingBox2D::FUN_00609440(const RHMobileUnk006100e0 &line, double firstLimit, double lastLimit) const
{
    SBGeoPoint2D first;
    SBGeoPoint2D last;
    SBGeoPoint2D clippedFirst;
    SBGeoPoint2D clippedLast;
    const float *bounds = (const float *)m_00;
    float right = bounds[2];
    float left = bounds[0];
    float bottom = bounds[1];
    float top = bounds[3];
    double enter = firstLimit;
    double leave = lastLimit;
    first = line;
    last = line.Second();
    float dx = last.m_x - first.m_x;
    float dy = last.m_y - first.m_y;
    if (dx == 0.0f)
    {
        clippedFirst = first;
        clippedLast = last;
        if ((firstLimit < 0.0 && first.m_y < last.m_y) || first.m_y < bottom)
            clippedFirst.m_y = bottom;
        else if ((firstLimit < 0.0 && first.m_y > last.m_y) || first.m_y > top)
            clippedFirst.m_y = top;
        if ((lastLimit > 1.0 && first.m_y > last.m_y) || last.m_y < bottom)
            clippedLast.m_y = bottom;
        else if ((lastLimit > 1.0 && first.m_y < last.m_y) || last.m_y > top)
            clippedLast.m_y = top;
        return RHUnk0060fbf0(SBGeoSegment2D(clippedFirst, clippedLast).Line());
    }
    if (dy == 0.0f)
    {
        clippedFirst = first;
        clippedLast = last;
        if ((firstLimit < 0.0 && first.m_x < last.m_x) || first.m_x < left)
            clippedFirst.m_x = left;
        else if ((firstLimit < 0.0 && first.m_x > last.m_x) || first.m_x > right)
            clippedFirst.m_x = right;
        if ((lastLimit > 1.0 && first.m_x > last.m_x) || last.m_x < left)
            clippedLast.m_x = left;
        else if ((lastLimit > 1.0 && first.m_x < last.m_x) || last.m_x > right)
            clippedLast.m_x = right;
        return RHUnk0060fbf0(SBGeoSegment2D(clippedFirst, clippedLast).Line());
    }
    bool rejected = false;
    double distance;
    if (dx > 0.0f)
    {
        if (firstLimit < 0.0 || first.m_x < left)
        {
            distance = (left - first.m_x) / dx;
            if (distance > enter) enter = distance;
        }
        if (enter > leave) rejected = true;
        else
        {
            if (lastLimit > 1.0 || last.m_x > right)
            {
                distance = (right - first.m_x) / dx;
                if (distance < leave) leave = distance;
            }
            if (enter > leave) rejected = true;
        }
    }
    else
    {
        if (firstLimit < 0.0 || first.m_x > right)
        {
            distance = (right - first.m_x) / dx;
            if (distance > enter) enter = distance;
        }
        if (enter > leave) rejected = true;
        else
        {
            if (lastLimit > 1.0 || last.m_x < left)
            {
                distance = (left - first.m_x) / dx;
                if (distance < leave) leave = distance;
            }
            if (enter > leave) rejected = true;
        }
    }
    if (dy > 0.0f)
    {
        if (!rejected && (firstLimit < 0.0 || first.m_y < bottom))
        {
            distance = (bottom - first.m_y) / dy;
            if (distance > enter) enter = distance;
        }
        if (enter > leave) rejected = true;
        else
        {
            if (lastLimit > 1.0 || last.m_y > top)
            {
                distance = (top - first.m_y) / dy;
                if (distance < leave) leave = distance;
            }
            if (enter > leave) rejected = true;
        }
    }
    else
    {
        if (!rejected && (firstLimit < 0.0 || first.m_y > top))
        {
            distance = (top - first.m_y) / dy;
            if (distance > enter) enter = distance;
        }
        if (enter > leave) rejected = true;
        else
        {
            if (lastLimit > 1.0 || last.m_y < bottom)
            {
                distance = (bottom - first.m_y) / dy;
                if (distance < leave) leave = distance;
            }
            if (enter > leave) rejected = true;
        }
    }
    if (rejected)
        return RHUnk0060fbf0();
    clippedFirst.m_x = dx * enter + first.m_x;
    clippedFirst.m_y = dy * enter + first.m_y;
    clippedLast.m_x = dx * leave + first.m_x;
    clippedLast.m_y = dy * leave + first.m_y;
        return RHUnk0060fbf0(SBGeoSegment2D(clippedFirst, clippedLast).Line());
}

#include "RHUnk0060bd40.h"
#include "SBList.h"
#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(SBList<unsigned char>, 0x24)
DECOMP_STATIC_ASSERT(offsetof(SBList<unsigned char>, m_current) == 0xc)
DECOMP_STATIC_ASSERT(offsetof(SBList<unsigned char>, m_dirty) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(SBList<unsigned char>, m_index) == 0x14)

template<> inline void SBList<unsigned char>::GoTo(int wanted)
{
    int count = size();
    int from = m_dirty ? 0 : m_index;
    if (m_dirty || (wanted < from && wanted < (from + 1) / 2))
    {
        if (wanted <= (count + 1) / 2)
        {
            m_current = begin();
            from = 0;
        }
        else
        {
            m_current = end();
            from = count;
        }
    }
    else if (wanted > from && wanted >= (from + count) / 2)
    {
        m_current = end();
        from = count;
    }
    std::advance(m_current, wanted - from);
    m_dirty = false;
    m_index = wanted;
}

// STUB: GAME 0x00609aa0
void SBGeoBoundingBox2D::ClipAttached(const RHUnk0060bd40 &input, RHUnk0060bd40 &output) const
{
    SBGeoPoint2D previous;
    SBGeoPoint2D current;
    SBList<unsigned char> flags;
    float bounds[4];
    memcpy(bounds, m_00, sizeof(bounds));
    const float left = bounds[0], right = bounds[2], bottom = bounds[1], top = bounds[3];
    unsigned long last = input.FUN_0060c250() - 1;
    output.FUN_0060c280();
    if (!input.FUN_0060c250())
        return;
    previous = input.FUN_0060c2b0(last);
    for (unsigned long i = 0; i <= last; ++i)
    {
        current = input.FUN_0060c2b0(i);
        float dx = current.m_x - previous.m_x, dy = current.m_y - previous.m_y;
        float xin, xout, yin, yout;
        if (dx > 0.0f || (dx == 0.0f && previous.m_x > right))
        {
            xin = left;
            xout = right;
        }
        else
        {
            xin = right;
            xout = left;
        }
        if (dy > 0.0f || (dy == 0.0f && previous.m_y > top))
        {
            yin = bottom;
            yout = top;
        }
        else
        {
            yin = top;
            yout = bottom;
        }
        double txout, tyout;
        if (dx != 0.0f)
            txout = (xout - previous.m_x) / dx;
        else
            txout = previous.m_x < left || previous.m_x > right ? -FLT_MAX : FLT_MAX;
        if (dy != 0.0f)
            tyout = (yout - previous.m_y) / dy;
        else
            tyout = previous.m_y < bottom || previous.m_y > top ? -FLT_MAX : FLT_MAX;
        double firstOut, lastOut;
        if (txout < tyout)
        {
            firstOut = txout;
            lastOut = tyout;
        }
        else
        {
            firstOut = tyout;
            lastOut = txout;
        }
        if (lastOut > 0.0)
        {
            double txin = dx != 0.0f ? (xin - previous.m_x) / dx : -FLT_MAX;
            double tyin = dy != 0.0f ? (yin - previous.m_y) / dy : -FLT_MAX;
            double enter = txin < tyin ? tyin : txin;
            if (firstOut < enter)
            {
                if (firstOut > 0.0 && firstOut <= 1.0)
                {
                    if (txin < tyin)
                        output.FUN_0060c260(SBGeoPoint2D(xout, yin));
                    else
                        output.FUN_0060c260(SBGeoPoint2D(xin, yout));
                }
            }
            else if (firstOut > 0.0 && enter <= 1.0)
            {
                if (enter > 0.0)
                {
                    if (txin > tyin)
                        output.FUN_0060c260(SBGeoPoint2D(xin, previous.m_y + txin * dy));
                    else
                        output.FUN_0060c260(SBGeoPoint2D(previous.m_x + tyin * dx, yin));
                }
                if (firstOut < 1.0)
                {
                    if (txout < tyout)
                        output.FUN_0060c260(SBGeoPoint2D(xout, previous.m_y + txout * dy));
                    else
                        output.FUN_0060c260(SBGeoPoint2D(previous.m_x + tyout * dx, yout));
                }
                else
                    output.FUN_0060c260(current);
            }
            if (lastOut > 0.0 && lastOut <= 1.0)
                output.FUN_0060c260(SBGeoPoint2D(xout, yout));
        }
        previous = current;
    }
    unsigned long count = output.FUN_0060c250();
    if (count < 3)
    {
        output.FUN_0060c280();
        return;
    }
    for (unsigned long j = 0; j < count; ++j)
    {
        current = output.FUN_0060c2b0(j);
        unsigned char flag;
        if (current.m_x == left)
            flag = current.m_y == bottom ? 0x19 : current.m_y == top ? 0x1c : 8;
        else if (current.m_x == right)
            flag = current.m_y == bottom ? 0x13 : current.m_y == top ? 0x16 : 2;
        else
            flag = current.m_y == bottom ? 1 : current.m_y == top ? 4 : 0;
        flags.push_back(flag);
        flags.m_dirty = true;
    }
    unsigned long prev = count - 1, index = 0, next = 1;
    while (index < count)
    {
        if (count < 3)
        {
            output.FUN_0060c280();
            return;
        }
        flags.GoTo(index);
        unsigned char atFlag = *flags.m_current;
        flags.GoTo(next);
        unsigned char nextFlag = *flags.m_current;
        flags.GoTo(prev);
        unsigned char prevFlag = *flags.m_current;
        bool sameSide = (prevFlag & atFlag & 15) && (atFlag & nextFlag & 15) &&
                        (prevFlag & nextFlag & 15);
        if ((atFlag & 16) && (atFlag == nextFlag || sameSide))
        {
            flags.GoTo(index);
            flags.erase(flags.m_current);
            flags.m_dirty = true;
            output.FUN_0060c290(index);
            --count;
            index = 0;
            prev = count - 1;
            next = 1;
        }
        else
        {
            prev = index++;
            if (++next >= count)
                next -= count;
        }
    }
}
