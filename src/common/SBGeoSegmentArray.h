#ifndef SBGEOSEGMENTARRAY_H
#define SBGEOSEGMENTARRAY_H

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include "SBGeoSegment2D.h"
#include "SBGeoSegmentVector.h"

inline SBGeoSegment2D *SBGeoSegmentVector::Copy(SBGeoSegment2D *first, SBGeoSegment2D *last, SBGeoSegment2D *destination)
{
    for (; first != last; ++first, ++destination)
        *destination = *first;
    return destination;
}

inline SBGeoSegmentVector::~SBGeoSegmentVector()
{
    SBGeoSegment2D *last = m_last;
    for (SBGeoSegment2D *entry = m_first; entry != last; ++entry)
        entry->~SBGeoSegment2D();
    m_allocator.deallocate(m_first, m_end - m_first);
    m_first = 0;
    m_last = 0;
    m_end = 0;
}

class SBGeoSegmentArray : public SBGeoSegmentVector
{
public:
    ~SBGeoSegmentArray() { Destroy(); }
    void Destroy()
    {
        SBGeoSegment2D *next = Copy(end(), end(), begin());
        DestroyElements(next, end());
        m_last = next;
    }
    SBGeoSegment2D *m_current;
    bool m_dirty;
    int m_index;
    SBGeoSegment2D m_value;
};

#endif
