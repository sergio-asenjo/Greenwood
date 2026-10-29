#include "SBNullstr.h"
#include "RHElementMobile.h"

class RHSprite
{
public:
    bool FUN_005b9e30(void *first, void *second, bool third);
};

// FUNCTION: GAME 0x004a8130
RHMobileBase004a8130::RHMobileBase004a8130(int type) : RHMobileElementBase(type, 0)
{
    RHMobileField<unsigned short>(this, 0x10) = 0x1001;
    RHMobileField<unsigned>(this, 0xa8) = 1;
    RHMobileField<unsigned char>(this, 0x12) = 1;
    RHMobileField<unsigned>(this, 0xac) = 0;
    m_cc = -1;
    m_c8 = 0;
    m_d0 = 0;
    RHMobileField<unsigned>(this, 0xb0) = 0x11b;
}

// SYNTHETIC: GAME 0x004a81d0
// RHMobileBase004a8130::`scalar deleting destructor'

// FUNCTION: GAME 0x004a81f0
RHMobileBase004a8130::~RHMobileBase004a8130()
{
}
void RHMobileBase004a8130::v1() {}
void RHMobileBase004a8130::v2() {}
void RHMobileBase004a8130::v3() {}
void RHMobileBase004a8130::v4() {}
void RHMobileBase004a8130::v5() {}
void RHMobileBase004a8130::v6() {}
void RHMobileBase004a8130::v7() {}
void RHMobileBase004a8130::v8() {}
void RHMobileBase004a8130::v9() {}
void RHMobileBase004a8130::v10() {}
void RHMobileBase004a8130::v11() {}
void RHMobileBase004a8130::v12() {}
void RHMobileBase004a8130::v13() {}
void RHMobileBase004a8130::v14(SBFile &) {}
void RHMobileBase004a8130::v15() {}
bool RHMobileBase004a8130::v16(SBFile &) { return false; }
void RHMobileBase004a8130::v17(bool) {}
void RHMobileBase004a8130::v18() {}
void RHMobileBase004a8130::v19() {}
void RHMobileBase004a8130::v20() {}
void RHMobileBase004a8130::v21() {}
void RHMobileBase004a8130::v22() {}
void RHMobileBase004a8130::v23() {}
void RHMobileBase004a8130::v24() {}
void RHMobileBase004a8130::v25() {}
// SYNTHETIC: GAME 0x004aac80
// RHUnk004aac40::`scalar deleting destructor'
// FUNCTION: GAME 0x004aaca0
RHUnk004aac40::~RHUnk004aac40() {}
void RHUnk004aac40::v9() {}
void RHUnk004aac40::v10() {}
bool RHUnk004aac40::v16(SBFile &) { return false; }

RHMobileSegment::RHMobileSegment(const SBGeoPoint2D &, const SBGeoPoint2D &) {}
RHMobileSegment::~RHMobileSegment() {}
DECOMP_SIZE_ASSERT(RHMobileUnk0060a820, 0x10)
// TEMPLATE: GAME 0x004611c0 FOLDED
// ??1RHMobileUnk0060a820@@QAE@XZ
RHMobileUnk0060a820::~RHMobileUnk0060a820() {}
void RHMobileGrid::FUN_004ed370(void *, unsigned short, const RHMobileSegment &, unsigned) {}
// FUNCTION: GAME 0x006158b0
RHMobileUnk0060a820 &RHMobileUnk0060a820::FUN_006158b0(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
{
    ((RHMobileUnk006100e0 *)this)->RHMobileUnk006100e0::RHMobileUnk006100e0(first, second);
    return *this;
}

// FUNCTION: GAME 0x006158d0
RHMobileUnk0060a820::RHMobileUnk0060a820(const RHMobileUnk0060a820 &other)
    : RHMobileUnk006100e0(other, other.Second())
{
}

// FUNCTION: GAME 0x006158f0
RHMobileUnk0060a820 &RHMobileUnk0060a820::FUN_006158f0(const RHMobileUnk006100e0 &other)
{
    ((RHMobileUnk006100e0 *)this)->FUN_00610140(other);
    return *this;
}
// FUNCTION: GAME 0x00607990
void RHMobileUnk00607da0::FUN_00607990(const RHMobileUnk00607da0 &other)
{
    bool value = *(const bool *)((const char *)&other + 0x10);
    *(bool *)((char *)this + 0x10) = value;
    if (value)
    {
        *(SBGeoPoint2D *)this = *(const SBGeoPoint2D *)&other;
        *(SBGeoPoint2D *)((char *)this + 8) = *(const SBGeoPoint2D *)((const char *)&other + 8);
    }
}
void RHMobileUnk006100e0::FUN_00578c50() throw() {}

bool RHMobilePath::FUN_00550660(unsigned char) { return false; }
void RHMobilePath::FUN_005505c0() {}
RHUnk005fc3b0::RHUnk005fc3b0(float x, float y) : SBGeoVector2D(x, y) {}
void FUN_004b0620(RHUnk005fc3b0 *destination, const RHUnk005fc3b0 &value) { new (destination) RHUnk005fc3b0(value); }
void FUN_004b05b0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last, const RHUnk005fc3b0 &value)
{
    for (; first != last; ++first)
        first->FUN_005fc430(value);
}
void FUN_004b05e0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last, RHUnk005fc3b0 *destination)
{
    while (last != first)
        (--destination)->FUN_005fc430(*--last);
}
RHUnk005fc3b0 *RHMobileUnk004b06f0::FUN_004b04d0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last, RHUnk005fc3b0 *destination)
{
    for (; first != last; ++first, ++destination)
        FUN_004b0620(destination, *first);
    return destination;
}
void RHMobileUnk004b06f0::FUN_004b0510(RHUnk005fc3b0 *first, unsigned count, const RHUnk005fc3b0 &value)
{
    for (; count; --count, ++first)
        FUN_004b0620(first, value);
}
void RHMobileUnk004b06f0::FUN_004aff00(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last)
{
    for (; first != last; ++first)
        first->~RHUnk005fc3b0();
}

RHMobilePointIterator RHMobilePointList::FUN_0046eb80()
{
    RHMobilePointIterator result;
    result.node = m_4->next;
    return result;
}
// TEMPLATE: GAME 0x005c9010 FOLDED
// ?FUN_005c9010@RHMobilePointList@@SAXAAPAURHMobilePointNode@@HI@Z
void RHMobilePointList::FUN_005c9010(RHMobilePointNode *&node, int distance, unsigned)
{
    while (distance > 0) { node = node->next; --distance; }
    while (distance < 0) { node = node->previous; ++distance; }
}

void RHMobileUnk0051fd10::FUN_00520480() {}
// FUNCTION: GAME 0x0060b640
bool RHUnk0042fde0::FUN_0060b640(const SBGeoPoint2D &point) const
{
    RHUnk005fc3b0 offset;
    RHUnk005fc3b0 direction;
    direction.FUN_005fc430(FUN_0042fde0());
    offset.FUN_005fc430(point.Unk005fc110(m_0));
    if (offset.FUN_005fc660(direction) < 0.0f)
        return false;
    offset.FUN_005fc430(point.Unk005fc110(m_8));
    return offset.FUN_005fc660(direction) <= 0.0f;
}

#include "RHUnk005fc400.h"
#include "SBGeoSegment2D.h"

// TEMPLATE: GAME 0x004e6a10
// ?_Construct@std@@YAXPAVSBGeoSegment2D@@ABV2@@Z

void (*g_mobileSegmentConstruct)(SBGeoSegment2D *, const SBGeoSegment2D &) = &std::_Construct;

extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sqrt(double);
SBGeoVector2D operator*(float factor, const SBGeoVector2D &point);

// FUNCTION: GAME 0x0060b7a0
float RHUnk0042fde0::FUN_0060b7a0(const SBGeoPoint2D &point) const
{
    if (FUN_0060b640(point))
    {
        RHUnk005fc400 offset(m_0, point);
        SBGeoVector2D normal = ((RHUnk005fc3b0 *)&FUN_0042fde0())->FUN_005fc8f0(true, 1.0f);
        ((RHUnk005fc3b0 *)&normal)->FUN_005fc7c0(1.0f);
        float distance = (float)fabs(((SBGeoVector2D *)&offset)->FUN_005fc660(normal));
        return distance;
    }
    float first = point.Unk005fc110(m_0).Unk005fc6d0(1.0f);
    float last = point.Unk005fc110(m_8).Unk005fc6d0(1.0f);
    float distance = (float)sqrt(first < last ? first : last);
    return distance;
}

// FUNCTION: GAME 0x0060b910
void RHUnk0042fde0::FUN_0060b910(SBGeoPoint2D &output, const SBGeoPoint2D &point) const
{
    SBGeoVector2D direction = FUN_0042fde0();
    if (point.Unk005fc110(m_8).FUN_005fc660(direction) >= 0.0f)
        output = m_8;
    else
    {
        float projection = point.Unk005fc110(m_0).FUN_005fc660(direction);
        if (projection <= 0.0f)
            output = m_0;
        else
            output = m_0.Unk005fc190(operator*(projection / direction.Unk005fc6d0(1.0f), direction));
    }
}

// FUNCTION: GAME 0x0060ba80
float RHUnk0042fde0::FUN_0060ba80(const SBGeoPoint2D &point) const
{
    {
        SBGeoVector2D direction = FUN_0042fde0();
        if (point.Unk005fc110(m_8).FUN_005fc660(direction) >= 0.0f)
            goto last;
        float projection = point.Unk005fc110(m_0).FUN_005fc660(direction);
        if (projection <= 0.0f)
            goto first;
        return projection / direction.Unk005fc6d0(1.0f);
    }
last:
    return 1.0f;
first:
    return 0.0f;
}
RHMobilePointerList::RHMobilePointerList()
{
    m_4 = (RHMobilePointerNode *)::operator new(12);
    m_4->next = m_4;
    m_4->previous = m_4;
    m_8 = 0;
    m_10 = true;
}
RHMobilePointerList::~RHMobilePointerList()
{
    RHMobilePointerNode *node = m_4->next;
    while (node != m_4)
    {
        RHMobilePointerNode *next = node->next;
        ::operator delete(node);
        node = next;
    }
    ::operator delete(m_4);
}
SBGeoPoint2D RHUnk005fc3b0::FUN_005fc450() const { return *this; }

RHMobilePointerArray::RHMobilePointerArray() : m_4(0), m_8(0), m_c(0), m_14(true) {}
RHMobilePointerArray::~RHMobilePointerArray() { ::operator delete(m_4); }
void RHMobilePointerArray::Append(void *value)
{
    if (m_8 == m_c)
    {
        unsigned count = m_4 ? m_8 - m_4 : 0;
        unsigned capacity = count ? count * 2 : 1;
        void **storage = (void **)::operator new(capacity * sizeof(void *));
        for (unsigned i = 0; i < count; ++i)
            storage[i] = m_4[i];
        ::operator delete(m_4);
        m_4 = storage;
        m_8 = storage + count;
        m_c = storage + capacity;
    }
    *m_8++ = value;
    m_14 = true;
}
RHMobileAreaLoad::RHMobileAreaLoad() {}
void RHMobileAreaLoad::FUN_005a3810(SBFile &, RHMobilePointerArray &) {}
// FUNCTION: GAME 0x00607c10
SBGeoBoundingBox2D::SBGeoBoundingBox2D(float left, float top, float right, float bottom) : m_0(left, top), m_8(right, bottom), m_10(1) {}
// FUNCTION: GAME 0x004aafc0
bool RHMobilePartCalls::FUN_004aafc0(void *value)
{
    return ((RHSprite *)m_50)->FUN_005b9e30(value, m_54, false);
}


class RHUnk00521550Part
{
public:
    RHUnk00521550Part();
    char m_0[0xc];
};

// TEMPLATE: GAME 0x00613e90 FOLDED
// ??0RHUnk00521550Part@@QAE@XZ
RHUnk00521550Part::RHUnk00521550Part() {}

#include "SBGeoIntersection2D.h"

// Parked: vector-use stack slots differ despite matching construction order.
// STUB: GAME 0x00615910
bool RHMobileUnk0060a820::FUN_00615910(const SBGeoSegment2D &segment) const
{
    SBGeoBoundingBox2D box;
    RHUnk005fc3b0 second;
    RHUnk005fc3b0 direction;
    RHUnk005fc3b0 first;
    box.FUN_00607e30((const RHMalignitySegment &)segment);
    if (box.FUN_00608730((const RHMobileUnk006100e0 &)*this))
    {
        const RHMobileUnk006100e0 &ray = (const RHMobileUnk006100e0 &)*this;
        const RHMobileUnk006100e0 &line = segment.Line();
        direction.FUN_005fc430(ray.Second().Unk005fc110(ray));
        first.FUN_005fc430(line.Unk005fc110(ray));
        second.FUN_005fc430(line.Second().Unk005fc110(ray));
        if (direction.FUN_005fc680(first, 1.0f) >= 0.0f &&
                direction.FUN_005fc680(second, 1.0f) <= 0.0f ||
            direction.FUN_005fc680(first, 1.0f) <= 0.0f &&
                direction.FUN_005fc680(second, 1.0f) >= 0.0f)
        {
            if (first.FUN_005fc680(second, 1.0f) > 0.0f)
            {
                if (direction.FUN_005fc680(second, 1.0f) >= 0.0f)
                    return true;
                return false;
            }
            if (direction.FUN_005fc680(second, 1.0f) <= 0.0f)
                return true;
            return false;
        }
        return false;
    }
    return false;
}


// GLOBAL: GAME 0x0067a938
double g_unk0x0067a938 = 9.999999717180685e-10;

// Parked: slope temporaries and collinear branch expansion differ.
// STUB: GAME 0x00615ca0
RHUnk0060fbf0 RHMobileUnk0060a820::FUN_00615ca0(const SBGeoSegment2D &segment) const
{
    const RHMobileUnk006100e0 &ray = (const RHMobileUnk006100e0 &)*this;
    const RHMobileUnk006100e0 &line = segment.Line();
    SBGeoPoint2D point;
    SBGeoSegment2D clipped(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f));
    RHUnk0060fbf0 result;
    double dx = ray.Second().m_x - ray.m_x;
    double otherDx = line.Second().m_x - line.m_x;
    if (dx != 0.0)
    {
        double slope = (ray.Second().m_y - ray.m_y) / dx;
        double offset = ray.m_y - ray.m_x * slope;
        if (otherDx != 0.0)
        {
            double otherSlope = (line.Second().m_y - line.m_y) / otherDx;
            double otherOffset = line.m_y - line.m_x * otherSlope;
            if (slope != otherSlope)
            {
                double x = (otherOffset - offset) / (slope - otherSlope);
                if ((ray.m_x < ray.Second().m_x ? x >= ray.m_x - g_unk0x0067a938 : x <= ray.m_x + g_unk0x0067a938) &&
                    (x <= line.m_x + g_unk0x0067a938 && x >= line.Second().m_x - g_unk0x0067a938 ||
                     x >= line.m_x - g_unk0x0067a938 && x <= line.Second().m_x + g_unk0x0067a938))
                {
                    point.m_x = x;
                    point.m_y = x * slope + offset;
                    result.FUN_0060fdc0(point);
                }
                else
                    result.FUN_0060fdb0();
                return result;
            }
            if (offset != otherOffset)
            {
                result.FUN_0060fdb0();
                return result;
            }
            const float &origin = ray.m_x;
            const float &direction = ray.Second().m_x;
            const float &first = line.m_x;
            const float &second = line.Second().m_x;
            if (origin < direction)
            {
                if (first < origin && second < origin)
                    result.FUN_0060fdb0();
                else if (first >= origin && second >= origin)
                    result.FUN_0060fe20(line);
                else if (first <= origin && second > origin)
                {
                    clipped.First() = ray;
                    clipped.Second() = line.Second();
                    result.FUN_0060fe20(clipped.Line());
                }
                else if (first > origin && second <= origin)
                {
                    clipped.First() = ray;
                    clipped.Second() = line;
                    result.FUN_0060fe20(clipped.Line());
                }
                else if (first == origin && second < origin || first < origin && second == origin)
                    result.FUN_0060fdc0(ray);
            }
            else
            {
                if (first > origin && second > origin)
                    result.FUN_0060fdb0();
                else if (first <= origin && second <= origin)
                    result.FUN_0060fe20(line);
                else if (first >= origin && second < origin)
                {
                    clipped.First() = ray;
                    clipped.Second() = line.Second();
                    result.FUN_0060fe20(clipped.Line());
                }
                else if (first < origin && second >= origin)
                {
                    clipped.First() = ray;
                    clipped.Second() = line;
                    result.FUN_0060fe20(clipped.Line());
                }
                else if (first == origin && second > origin || first > origin && second == origin)
                    result.FUN_0060fdc0(ray);
            }
            return result;
        }
        else
        {
            double y = line.m_x * slope + offset;
            if ((ray.m_x < ray.Second().m_x ? line.m_x >= ray.m_x - g_unk0x0067a938 : line.m_x <= ray.m_x + g_unk0x0067a938) &&
                (y <= line.m_y + g_unk0x0067a938 && y >= line.Second().m_y - g_unk0x0067a938 ||
                 y >= line.m_y - g_unk0x0067a938 && y <= line.Second().m_y + g_unk0x0067a938))
            {
                point.m_x = line.m_x;
                point.m_y = y;
                result.FUN_0060fdc0(point);
            }
            else
                result.FUN_0060fdb0();
            return result;
        }
    }
    else if (otherDx != 0.0)
    {
        double slope = (line.Second().m_y - line.m_y) / otherDx;
        double y = ray.m_x * slope + (line.m_y - line.m_x * slope);
        if ((ray.m_y < ray.Second().m_y ? y >= ray.m_y - g_unk0x0067a938 : y <= ray.m_y + g_unk0x0067a938) &&
            (ray.m_x <= line.m_x + g_unk0x0067a938 && ray.m_x >= line.Second().m_x - g_unk0x0067a938 ||
             ray.m_x >= line.m_x - g_unk0x0067a938 && ray.m_x <= line.Second().m_x + g_unk0x0067a938))
        {
            point.m_x = ray.m_x;
            point.m_y = y;
            result.FUN_0060fdc0(point);
        }
        else
            result.FUN_0060fdb0();
        return result;
    }
    else if (ray.m_x != line.m_x)
    {
        result.FUN_0060fdb0();
        return result;
    }
    const float &origin = ray.m_y;
    const float &direction = ray.Second().m_y;
    const float &first = line.m_y;
    const float &second = line.Second().m_y;
    if (direction > origin)
    {
        if (first < origin && second < origin)
            result.FUN_0060fdb0();
        else if (first >= origin && second >= origin)
            result.FUN_0060fe20(line);
        else if (first <= origin && second > origin)
        {
            clipped.First() = ray;
            clipped.Second() = line.Second();
            result.FUN_0060fe20(clipped.Line());
        }
        else if (first > origin && second <= origin)
        {
            clipped.First() = ray;
            clipped.Second() = line;
            result.FUN_0060fe20(clipped.Line());
        }
        else if (first == origin && second < origin || first < origin && second == origin)
            result.FUN_0060fdc0(ray);
    }
    else
    {
        if (first > origin && second > origin)
            result.FUN_0060fdb0();
        else if (first <= origin && second <= origin)
            result.FUN_0060fe20(line);
        else if (first >= origin && second < origin)
        {
            clipped.First() = ray;
            clipped.Second() = line.Second();
            result.FUN_0060fe20(clipped.Line());
        }
        else if (first < origin && second >= origin)
        {
            clipped.First() = ray;
            clipped.Second() = line;
            result.FUN_0060fe20(clipped.Line());
        }
        else if (first == origin && second > origin || first > origin && second == origin)
            result.FUN_0060fdc0(ray);
    }
    return result;
}
#include "RHMobileVectorArray.h"

DECOMP_SIZE_ASSERT(RHMobileVectorArray, 0x24)
DECOMP_SIZE_ASSERT(RHElementMobile, 0x260)
DECOMP_STATIC_ASSERT(offsetof(RHElementMobile, m_1c8) == 0x1c8)

// FUNCTION: GAME 0x004afac0
RHMobileVectorArray::~RHMobileVectorArray()
{
    Destroy();
}

void EmitRHMobileVectorArrayDestructor(RHMobileVectorArray *array)
{
    array->~RHMobileVectorArray();
}
