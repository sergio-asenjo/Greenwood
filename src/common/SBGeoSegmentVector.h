#ifndef SBGEOSEGMENTVECTOR_H
#define SBGEOSEGMENTVECTOR_H

#include <memory>

class SBGeoSegment2D;

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

#endif
