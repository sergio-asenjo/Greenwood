#include "SBNullstr.h"
#include "sbgeo_00610600.h"

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoSegment2D, 0x10)
DECOMP_SIZE_ASSERT(SBGeoPolyLine2DList, 0x28)

// TEMPLATE: GAME 0x0044e7d0 FOLDED
// ??1?$list@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@QAE@XZ

// TEMPLATE: GAME 0x0044e0a0
// ??1RHUnkPolyLineBase@@QAE@XZ

// SYNTHETIC: GAME 0x004d2820
// SBGeoPolyLine2DList::~SBGeoPolyLine2DList

// TEMPLATE: GAME 0x0044e900 FOLDED
// ?erase@?$list@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@QAE?AViterator@12@V312@@Z

// TEMPLATE: GAME 0x0057c9c0 FOLDED
// ??Eiterator@?$list@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@QAE?AV012@H@Z
DECOMP_SIZE_ASSERT(RHMobileUnk00611360, 0x24)

// TEMPLATE: GAME 0x00461eb0
// ?insert@?$list@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@QAE?AViterator@12@V312@ABVSBGeoPoint2D@@@Z
std::list<SBGeoPoint2D>::iterator EmitSBGeoPointListInsert(std::list<SBGeoPoint2D> &list, std::list<SBGeoPoint2D>::iterator position, const SBGeoPoint2D &point)
{
    typedef std::list<SBGeoPoint2D> List;
    List::iterator (List::*insert)(List::iterator, const SBGeoPoint2D &) = &List::insert;
    return (list.*insert)(position, point);
}

#include "SBGeoIntersection2D.h"
#include "SBGeoBoundingBox2DCore.h"
#include "RHUnk0042fde0.h"
#include "RHUnk005fc3b0.h"
#include "RHUnk00608f10.h"

// FUNCTION: GAME 0x0060a980
bool SBGeoSegment2D::FUN_0060a980(const RHMobileUnk0060a820 &other) const
{
    return other.FUN_00615910(*this);
}

// FUNCTION: GAME 0x0060a990
bool SBGeoSegment2D::IsIntersecting(const SBGeoSegment2D &other) const
{
    SBGeoBoundingBox2D bounds(*this);
    SBGeoBoundingBox2D otherBounds(other);
    SBGeoVector2D direction;
    SBGeoVector2D otherDirection;
    SBGeoVector2D offset;
    if ((unsigned char)((RHUnk00608f10 *)&bounds)->FUN_00608f10(&otherBounds))
    {
        direction = First().Unk005fc110(Second());
        otherDirection = ((const RHUnk0042fde0 *)&other)->FUN_0042fde0();
        offset = other.First().Unk005fc110(First());
        float first = ((RHUnk005fc3b0 *)&direction)->FUN_005fc680((const RHUnk005fc3b0 &)offset, 1.0f);
        float second = ((RHUnk005fc3b0 *)&direction)->FUN_005fc680((const RHUnk005fc3b0 &)other.Second().Unk005fc110(First()), 1.0f);
        if ((first >= 0.0f && second <= 0.0f) || (first <= 0.0f && second >= 0.0f))
        {
            first = ((RHUnk005fc3b0 *)&otherDirection)->FUN_005fc680((const RHUnk005fc3b0 &)offset, 1.0f);
            second = ((RHUnk005fc3b0 *)&otherDirection)->FUN_005fc680((const RHUnk005fc3b0 &)Second().Unk005fc110(other.First()), 1.0f);
            if ((first <= 0.0f && second <= 0.0f) || (first >= 0.0f && second >= 0.0f))
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

// FUNCTION: GAME 0x0060ad60
RHUnk0060fbf0 SBGeoSegment2D::FUN_0060ad60(const RHMobileUnk006100e0 &other) const
{
    return other.FUN_006101c0(Line());
}

// FUNCTION: GAME 0x0060ad80
RHUnk0060fbf0 SBGeoSegment2D::FUN_0060ad80(const RHMobileUnk0060a820 &other) const
{
    return other.FUN_00615ca0(*this);
}

void EmitSBGeoSegmentIntersection(SBGeoSegment2D *segment, const RHMobileUnk006100e0 &other)
{
    segment->FUN_0060a980((const RHMobileUnk0060a820 &)other);
    segment->FUN_0060ad60(other);
    segment->FUN_0060ad80((const RHMobileUnk0060a820 &)other);
    *segment ^ *(const SBGeoSegment2D *)&other;
}

// STUB: GAME 0x0060ada0
RHUnk0060fbf0 SBGeoSegment2D::operator^(const SBGeoSegment2D &other) const
{
    SBGeoPoint2D firstMin;
    SBGeoPoint2D secondMin;
    SBGeoPoint2D firstMax;
    SBGeoPoint2D secondMax;
    SBGeoPoint2D point;
    SBGeoSegment2D overlap(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f));
    RHUnk0060fbf0 result;
    double dx = Second().m_x - First().m_x;
    double otherDx = other.Second().m_x - other.First().m_x;
    if (dx != 0.0)
    {
        double slope = (Second().m_y - First().m_y) / dx;
        double offset = First().m_y - First().m_x * slope;
        if (otherDx != 0.0)
        {
            double otherSlope = (other.Second().m_y - other.First().m_y) / otherDx;
            double otherOffset = other.First().m_y - other.First().m_x * otherSlope;
            if (slope != otherSlope)
            {
                double x = (otherOffset - offset) / (slope - otherSlope);
                if (((x <= First().m_x + 1e-9 && x >= Second().m_x - 1e-9) ||
                     (x >= First().m_x - 1e-9 && x <= Second().m_x + 1e-9)) &&
                    ((x <= other.First().m_x + 1e-9 && x >= other.Second().m_x - 1e-9) ||
                     (x >= other.First().m_x - 1e-9 && x <= other.Second().m_x + 1e-9)))
                {
                    point.m_x = x;
                    point.m_y = x * slope + offset;
                    result.FUN_0060fdc0(point);
                }
                else
                    result.FUN_0060fdb0();
                return result;
            }
            else if (offset == otherOffset)
            {
                if (First().m_x < Second().m_x)
                {
                    firstMin = First();
                    firstMax = Second();
                }
                else
                {
                    firstMax = First();
                    firstMin = Second();
                }
                if (other.First().m_x < other.Second().m_x)
                {
                    secondMin = other.First();
                    secondMax = other.Second();
                }
                else
                {
                    secondMax = other.First();
                    secondMin = other.Second();
                }
                if (secondMax.m_x < firstMin.m_x || secondMin.m_x > firstMax.m_x)
                {
                    result.FUN_0060fdb0();
                    return result;
                }
                else if (secondMin.m_x < firstMin.m_x)
                {
                    if (secondMax.m_x < firstMax.m_x)
                    {
                        overlap.First() = firstMin;
                        overlap.Second() = secondMax;
                        result.FUN_0060fe20(overlap.Line());
                        return result;
                    }
                    else
                    {
                        result.FUN_0060fe20(Line());
                        return result;
                    }
                }
                else if (firstMax.m_x >= secondMin.m_x && firstMin.m_x < secondMin.m_x)
                {
                    if (firstMax.m_x < secondMax.m_x)
                    {
                        overlap.First() = secondMin;
                        overlap.Second() = firstMax;
                        result.FUN_0060fe20(overlap.Line());
                        return result;
                    }
                    else
                    {
                        result.FUN_0060fe20(other.Line());
                        return result;
                    }
                }
                else if (firstMin.m_x == secondMax.m_x && secondMin.m_x < firstMin.m_x)
                {
                    result.FUN_0060fdc0(firstMin);
                    return result;
                }
                else if (firstMax.m_x == secondMin.m_x && secondMin.m_x > firstMin.m_x)
                {
                    result.FUN_0060fdc0(secondMin);
                    return result;
                }
            }
            else
                result.FUN_0060fdb0();
        }
        else
        {
            double y = other.First().m_x * slope + offset;
            if (((y <= First().m_y + 1e-9 && y >= Second().m_y - 1e-9) ||
                 (y >= First().m_y - 1e-9 && y <= Second().m_y + 1e-9)) &&
                ((y <= other.First().m_y + 1e-9 && y >= other.Second().m_y - 1e-9) ||
                 (y >= other.First().m_y - 1e-9 && y <= other.Second().m_y + 1e-9)))
            {
                point.m_x = other.First().m_x;
                point.m_y = y;
                result.FUN_0060fdc0(point);
            }
            else
                result.FUN_0060fdb0();
        }
    }
    else if (otherDx != 0.0)
    {
        double otherSlope = (other.Second().m_y - other.First().m_y) / otherDx;
        double otherOffset = other.First().m_y - other.First().m_x * otherSlope;
        double y = First().m_x * otherSlope + otherOffset;
        if (((y <= First().m_y + 1e-9 && y >= Second().m_y - 1e-9) ||
             (y >= First().m_y - 1e-9 && y <= Second().m_y + 1e-9)) &&
            ((First().m_x <= other.First().m_x + 1e-9 && First().m_x >= other.Second().m_x - 1e-9) ||
             (First().m_x >= other.First().m_x - 1e-9 && First().m_x <= other.Second().m_x + 1e-9)))
        {
            point.m_x = First().m_x;
            point.m_y = y;
            result.FUN_0060fdc0(point);
        }
        else
            result.FUN_0060fdb0();
    }
    else if (First().m_x == other.First().m_x)
    {
        if (First().m_y < Second().m_y)
        {
            firstMin = First();
            firstMax = Second();
        }
        else
        {
            firstMax = First();
            firstMin = Second();
        }
        if (other.First().m_y < other.Second().m_y)
        {
            secondMin = other.First();
            secondMax = other.Second();
        }
        else
        {
            secondMax = other.First();
            secondMin = other.Second();
        }
        if (secondMax.m_y < firstMin.m_y || secondMin.m_y > firstMax.m_y)
        {
            result.FUN_0060fdb0();
            return result;
        }
        else if (secondMin.m_y < firstMin.m_y)
        {
            if (secondMax.m_y < firstMax.m_y)
            {
                overlap.First() = firstMin;
                overlap.Second() = secondMax;
                result.FUN_0060fe20(overlap.Line());
                return result;
            }
            else
            {
                result.FUN_0060fe20(Line());
                return result;
            }
        }
        else if (firstMax.m_y >= secondMin.m_y && firstMin.m_y < secondMin.m_y)
        {
            if (firstMax.m_y < secondMax.m_y)
            {
                overlap.First() = secondMin;
                overlap.Second() = firstMax;
                result.FUN_0060fe20(overlap.Line());
                return result;
            }
            else
            {
                result.FUN_0060fe20(other.Line());
                return result;
            }
        }
        else if (firstMin.m_y == secondMax.m_y && secondMin.m_y < firstMin.m_y)
        {
            result.FUN_0060fdc0(firstMin);
            return result;
        }
        else if (firstMax.m_y == secondMin.m_y && secondMin.m_y > firstMin.m_y)
        {
            result.FUN_0060fdc0(secondMin);
            return result;
        }
    }
    return result;
}

inline void SBGeoPolyLine2DList::Seek(int wanted)
{
    int size = _Size;
    if (m_dirty)
    {
        if (wanted <= (size + 1) / 2)
        {
            m_cursor = Begin();
            std::bidirectional_iterator_tag category;
            FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, wanted, category);
        }
        else
        {
            m_cursor = End();
            std::bidirectional_iterator_tag category;
            FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, wanted - size, category);
        }
        m_dirty = false;
        m_index = wanted;
    }
    else
    {
        int previous = m_index;
        if (wanted != previous)
        {
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)((Cursor &)m_cursor).Assign(*(_Nodeptr volatile *)&_Head->_Next), wanted, category);
                }
                else
                {
                    int distance = wanted - previous;
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, distance, category);
                }
            }
            else if (wanted < (size + previous) / 2)
                std::advance(m_cursor, wanted - previous);
            else
            {
                m_cursor = End();
                std::advance(m_cursor, wanted - size);
            }
            m_index = wanted;
        }
    }
}

// FUNCTION: GAME 0x00610600
void SBGeoPolyLine2DList::FUN_00610600(const SBGeoPolyLine2DList &other)
{
    unsigned long count = (unsigned long)((const RHUnk0053bf20 *)&other)->FUN_0053bf20();
    for (unsigned long i = 0; i < count; ++i)
        FUN_00610a60(other.FUN_00610cb0(i));
}

// FUNCTION: GAME 0x00610640
void SBGeoPolyLine2DList::FUN_00610640(const RHMobileUnk00611360 &other)
{
    unsigned long count = other.FUN_00610f30();
    for (unsigned long i = 0; i < count; ++i)
        FUN_00610a60(((RHUnkSectorPoints *)&other)->FUN_006112c0(i));
}

// FUNCTION: GAME 0x00610680
SBGeoPolyLine2DList::SBGeoPolyLine2DList()
{
}

// FUNCTION: GAME 0x006106e0
SBGeoPolyLine2DList::SBGeoPolyLine2DList(const SBGeoPolyLine2DList &other)
{
    FUN_00610600(other);
}

// FUNCTION: GAME 0x00610760
SBGeoPolyLine2DList::SBGeoPolyLine2DList(const RHMobileUnk00611360 &other)
{
    FUN_00610640(other);
}

// FUNCTION: GAME 0x006107e0
bool SBGeoPolyLine2DList::FUN_006107e0()
{
    unsigned long count = _Size;
    if (count < 4)
        return false;
    bool swap = false;
    SBGeoSegment2D first(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f));
    SBGeoSegment2D second(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f));
    GoTo(count - 1);
    Load(first.First());
    for (int i = count - 2; i >= 2; --i)
    {
        if (swap)
        {
            GoTo(i);
            Load(first.First());
            swap = false;
        }
        else
        {
            GoTo(i);
            Load(first.Second());
            swap = true;
        }
        GoTo(i - 1);
        Load(second.First());
        bool other = false;
        for (int j = i - 2; j >= 0; --j)
        {
            if (other)
            {
                GoTo(j);
                Load(second.First());
                other = false;
            }
            else
            {
                GoTo(j);
                Load(second.Second());
                other = true;
            }
            if (first.IsIntersecting(second))
                return true;
        }
    }
    return false;
}

// FUNCTION: GAME 0x00610a00
void SBGeoPolyLine2DList::FUN_00610a00(const SBGeoPoint2D &point)
{
    push_front(point);
    m_dirty = true;
}

// FUNCTION: GAME 0x00610a60
void SBGeoPolyLine2DList::FUN_00610a60(const SBGeoPoint2D &point)
{
    push_back(point);
    m_dirty = true;
}

// FUNCTION: GAME 0x00610ac0
void SBGeoPolyLine2DList::FUN_00610ac0()
{
    clear();
    m_dirty = true;
}

// FUNCTION: GAME 0x00610b10
void SBGeoPolyLine2DList::FUN_00610b10()
{
    pop_front();
    m_dirty = true;
}

// FUNCTION: GAME 0x00610b50
void SBGeoPolyLine2DList::FUN_00610b50(unsigned long index)
{
    Seek(index);
    erase(m_cursor);
    m_dirty = true;
}

// FUNCTION: GAME 0x00610cb0
const SBGeoPoint2D &SBGeoPolyLine2DList::FUN_00610cb0(unsigned long index) const
{
    SBGeoPolyLine2DList *self = (SBGeoPolyLine2DList *)this;
    self->Seek(index);
    return *self->m_cursor;
}

// FUNCTION: GAME 0x00610e20
void RHMobileUnk00611360::FUN_00610e20(const RHMobileUnk00611360 &other)
{
    unsigned long count = other.FUN_00610f30();
    for (unsigned long i = 0; i < count; ++i)
        ((RHUnkTargetPoints *)this)->FUN_00611100(((RHUnkSectorPoints *)&other)->FUN_006112c0(i));
}

// FUNCTION: GAME 0x00610e60
RHMobileUnk00611360::RHMobileUnk00611360()
{
}

// FUNCTION: GAME 0x00610ec0
RHMobileUnk00611360::RHMobileUnk00611360(const RHMobileUnk00611360 &other)
{
    FUN_00610e20(other);
}

// FUNCTION: GAME 0x00610f30
unsigned long RHMobileUnk00611360::FUN_00610f30() const
{
    return size();
}

// Target keeps the leading size() of the inlined insert growth out-of-line (vector<SBGeoVector2D>::size clone); VC6 inlines it here.
// STUB: GAME 0x00610f50
void RHMobileUnk00611360::FUN_00610f50(const SBGeoPoint2D &point, unsigned long index)
{
    if (index == size())
    {
        push_back(point);
        m_dirty = true;
    }
    else
    {
        insert(&at(index), point);
        m_dirty = true;
    }
}

// FUNCTION: GAME 0x00611100
void RHUnkTargetPoints::FUN_00611100(const SBGeoPoint2D &point)
{
    push_back(point);
    m_dirty = true;
}

// FUNCTION: GAME 0x006112a0
void RHUnkSectorPoints::FUN_006112a0(const SBGeoPoint2D &point, unsigned int index)
{
    (*(std::vector<SBGeoPoint2D> *)this)[index] = point;
}

// FUNCTION: GAME 0x006112c0
SBGeoPoint2D &RHUnkSectorPoints::FUN_006112c0(unsigned int index)
{
    return (*(std::vector<SBGeoPoint2D> *)this)[index];
}

// FUNCTION: GAME 0x006112d0
SBGeoSegment2D RHMobileUnk00611360::FUN_006112d0(unsigned long index) const
{
    SBGeoSegment2D segment(((RHUnkSectorPoints *)this)->FUN_006112c0(index), ((RHUnkSectorPoints *)this)->FUN_006112c0(index + 1));
    return segment;
}

// TEMPLATE: GAME 0x006113b0
// ?_Xran@?$vector@VSBGeoPoint2D@@V?$allocator@VSBGeoPoint2D@@@std@@@std@@IBEXXZ
