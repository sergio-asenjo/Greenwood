#ifndef SBGEOSEGMENTVECTOR_H
#define SBGEOSEGMENTVECTOR_H

#include <memory>

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include "SBGeoSegment2D.h"

class SBGeoSegmentVector
{
public:
    SBGeoSegmentVector(const std::allocator<SBGeoSegment2D> &allocator = std::allocator<SBGeoSegment2D>())
        : m_allocator(allocator), m_first(0), m_last(0), m_end(0) {}
    ~SBGeoSegmentVector();
    SBGeoSegment2D *begin() { return m_first; }
    SBGeoSegment2D *end() { return m_last; }
    static SBGeoSegment2D *Copy(SBGeoSegment2D *first, SBGeoSegment2D *last, SBGeoSegment2D *destination);
    void DestroyElements(SBGeoSegment2D *first, SBGeoSegment2D *last);
    SBGeoSegment2D *Erase(SBGeoSegment2D *first, SBGeoSegment2D *last);
    std::allocator<SBGeoSegment2D> m_allocator;
    SBGeoSegment2D *m_first;
    SBGeoSegment2D *m_last;
    SBGeoSegment2D *m_end;
};

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

#endif
