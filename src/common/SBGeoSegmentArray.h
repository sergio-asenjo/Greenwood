#ifndef SBGEOSEGMENTARRAY_H
#define SBGEOSEGMENTARRAY_H

#include "SBGeoSegmentVector.h"

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
