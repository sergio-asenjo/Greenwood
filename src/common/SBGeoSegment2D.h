#ifndef SB_GEO_SEGMENT_2D_H
#define SB_GEO_SEGMENT_2D_H

class SBGeoPoint2D;
class RHUnk0060fbf0;

#include "RHMobileSegmentCalls.h"

#include "RHMobileUnk006100e0.h"
#include "SBUIInputFieldBoxCalls.h"

// SIZE 0x10
class SBGeoSegment2D
{
public:
    SBGeoSegment2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    SBGeoSegment2D(const SBGeoSegment2D &other);
    SBGeoSegment2D &operator=(const SBGeoSegment2D &other)
    {
        ((SBUIInputFieldBoxCalls *)this)->FUN_0060a860(other.Line());
        return *this;
    }
    ~SBGeoSegment2D()
    {
        ((RHMobileUnk006100e0 *)this)->~RHMobileUnk006100e0();
    }
    SBGeoPoint2D &First() { return *(SBGeoPoint2D *)&m_00[0]; }
    SBGeoPoint2D &Second() { return *(SBGeoPoint2D *)&m_00[8]; }
    const SBGeoPoint2D &First() const { return *(const SBGeoPoint2D *)&m_00[0]; }
    const SBGeoPoint2D &Second() const { return *(const SBGeoPoint2D *)&m_00[8]; }
    const RHMobileUnk006100e0 &Line() const
    {
        return *reinterpret_cast<const RHMobileUnk006100e0 *>(m_00);
    }
    bool IsIntersecting(const SBGeoSegment2D &other) const;
    RHUnk0060fbf0 FUN_0060ad60(const RHMobileUnk006100e0 &other) const;
    bool FUN_0060a980(const RHMobileUnk0060a820 &other) const;
    RHUnk0060fbf0 FUN_0060ad80(const RHMobileUnk0060a820 &other) const;
    RHUnk0060fbf0 operator^(const SBGeoSegment2D &other) const;
    unsigned char m_00[0x10]; // 0x00
};

#endif
