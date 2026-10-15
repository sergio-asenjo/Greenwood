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

class RHPathQueryCalls
{
public:
    void FUN_005c8e40(int index);
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

class RHMobileUnk00611360;

// SIZE 0x10
struct RHUnkPolyLineTail
{
    undefined m_00[8];  // 0x00
    SBGeoPoint2D m_08;  // 0x08
};

// SIZE 0x0c
struct RHUnkPolyArrayTail
{
    undefined m_00[4];  // 0x00
    SBGeoPoint2D m_04;  // 0x04
};

// SIZE 0x28
class RHUnkPolyLineBase : public std::list<SBGeoPoint2D>
{
public:
    RHUnkPolyLineBase() : m_dirty(true) {}
    iterator Begin()
    {
        _Nodeptr sentinel = _Head;
        _Nodeptr first = *(_Nodeptr volatile *)&sentinel->_Next;
        return iterator(first);
    }
    iterator End()
    {
        _Nodeptr sentinel = *(_Nodeptr volatile *)&_Head;
        return iterator(sentinel);
    }
    struct Cursor : std::list<SBGeoPoint2D>::iterator
    {
        Cursor &Assign(_Nodeptr value)
        {
            *(_Nodeptr volatile *)this = value;
            return *this;
        }
    };
    iterator m_cursor;  // 0x0c
    bool m_dirty;       // 0x10
    int m_index;        // 0x14
    RHUnkPolyLineTail m_18; // 0x18
};

class SBGeoPolyLine2DList : public RHUnkPolyLineBase
{
public:
    void Seek(int wanted);
    SBGeoPolyLine2DList();
    SBGeoPolyLine2DList(const SBGeoPolyLine2DList &other);
    SBGeoPolyLine2DList(const RHMobileUnk00611360 &other);
    void FUN_00610600(const SBGeoPolyLine2DList &other);
    void FUN_00610640(const RHMobileUnk00611360 &other);
    bool FUN_006107e0();
    void GoTo(int index) { ((RHPathQueryCalls *)this)->FUN_005c8e40(index); }
    void Load(SBGeoPoint2D &target)
    {
        const SBGeoPoint2D &value = *m_cursor;
        target = value;
    }
    void FUN_00610a00(const SBGeoPoint2D &point);
    void FUN_00610a60(const SBGeoPoint2D &point);
    void FUN_00610ac0();
    void FUN_00610b10();
    void FUN_00610b50(unsigned long index);
    const SBGeoPoint2D &FUN_00610cb0(unsigned long index) const;
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
