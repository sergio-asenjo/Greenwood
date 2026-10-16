#ifndef SBGEO_00610600_H
#define SBGEO_00610600_H

#include "Decomp.h"
#include <list>
#include <vector>

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    SBGeoPoint2D(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    float m_x; // 0x00
    float m_y; // 0x04
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

class RHUnk0053bf20
{
public:
    void *FUN_0053bf20() const;
};

class RHMobileUnk0060a820
{
public:
    RHMobileUnk0060a820 &FUN_0060a820(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    void FUN_0060a840(const RHMobileUnk0060a820 &other);
    bool FUN_0060a990(const RHMobileUnk0060a820 &other) const;
};

#include "SBGeoPolyLine2DList.h"

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

class RHMobileUnk00611360;

// SIZE 0x0c
struct RHUnkPolyArrayTail
{
    undefined m_00[4];  // 0x00
    SBGeoPoint2D m_04;  // 0x04
};

class RHUnkPolyArrayBase : public std::vector<SBGeoPoint2D>
{
public:
    RHUnkPolyArrayBase() : m_dirty(true) {}
    undefined4 m_10;    // 0x10
    bool m_dirty;       // 0x14
    RHUnkPolyArrayTail m_18; // 0x18
};

// SIZE 0x24
class RHMobileUnk00611360 : public RHUnkPolyArrayBase
{
public:
    RHMobileUnk00611360();
    RHMobileUnk00611360(const RHMobileUnk00611360 &other);
    void FUN_00610e20(const RHMobileUnk00611360 &other);
    unsigned long FUN_00610f30() const;
    void FUN_00610f50(const SBGeoPoint2D &point, unsigned long index);
    SBGeoSegment2D FUN_006112d0(unsigned long index) const;
};

class RHUnkTargetPoints : public RHUnkPolyArrayBase
{
public:
    void FUN_00611100(const SBGeoPoint2D &point);
};

class RHUnkSectorPoints : public RHUnkPolyArrayBase
{
public:
    SBGeoPoint2D &FUN_006112c0(unsigned int index);
    void FUN_006112a0(const SBGeoPoint2D &point, unsigned int index);
};

#endif
