#ifndef SB_GEO_SEGMENT_2D_H
#define SB_GEO_SEGMENT_2D_H

class SBGeoPoint2D;

class RHMobileUnk0060a820
{
public:
    RHMobileUnk0060a820 &FUN_0060a820(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    void FUN_0060a840(const RHMobileUnk0060a820 &other);
    bool FUN_0060a990(const RHMobileUnk0060a820 &other) const;
};

class RHMobileUnk006100e0
{
public:
    ~RHMobileUnk006100e0();
};

// SIZE 0x10
class SBGeoSegment2D
{
public:
    SBGeoSegment2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
    {
        ((RHMobileUnk0060a820 *)this)->FUN_0060a820(first, second);
    }
    SBGeoSegment2D(const SBGeoSegment2D &other)
    {
        ((RHMobileUnk0060a820 *)this)->FUN_0060a840(*(const RHMobileUnk0060a820 *)&other);
    }
    ~SBGeoSegment2D()
    {
        ((RHMobileUnk006100e0 *)this)->~RHMobileUnk006100e0();
    }
    SBGeoPoint2D &First() { return *(SBGeoPoint2D *)&m_00[0]; }
    SBGeoPoint2D &Second() { return *(SBGeoPoint2D *)&m_00[8]; }
    bool IsIntersecting(const SBGeoSegment2D &other) const
    {
        return ((const RHMobileUnk0060a820 *)this)->FUN_0060a990(*(const RHMobileUnk0060a820 *)&other);
    }
    unsigned char m_00[0x10]; // 0x00
};

#endif
