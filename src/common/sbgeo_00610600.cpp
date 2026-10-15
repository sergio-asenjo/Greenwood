#include "SBNullstr.h"
#include "sbgeo_00610600.h"

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoSegment2D, 0x10)
DECOMP_SIZE_ASSERT(SBGeoPolyLine2DList, 0x28)
DECOMP_SIZE_ASSERT(RHMobileUnk00611360, 0x24)

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
    (*this)[index] = point;
}

// FUNCTION: GAME 0x006112c0
SBGeoPoint2D &RHUnkSectorPoints::FUN_006112c0(unsigned int index)
{
    return (*this)[index];
}

// Target pushes each point as it is fetched into an out-of-line segment constructor; the inline FUN_0060a820 wrapper caches the second point.
// STUB: GAME 0x006112d0
SBGeoSegment2D RHMobileUnk00611360::FUN_006112d0(unsigned long index) const
{
    SBGeoSegment2D segment(((RHUnkSectorPoints *)this)->FUN_006112c0(index), ((RHUnkSectorPoints *)this)->FUN_006112c0(index + 1));
    return segment;
}
