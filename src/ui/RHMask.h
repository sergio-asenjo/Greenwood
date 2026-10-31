#ifndef RHMASK_H
#define RHMASK_H

#include <memory>
#include "SB.h"
#include "SBGeoPoint2D.h"
#include "SBGeoVector2D.h"
#include "SBGeoBoundingBox2DCore.h"

SBGeoPoint2D operator+(const SBGeoPoint2D &, const SBGeoVector2D &);

class SBGeoPoint3D
{
public:
    float m_x;
    float m_y;
    float m_z;
};

class RHElementAreaShape
{
public:
    bool FUN_0060c660(const SBGeoPoint2D &point) const;
};

class RHShadowUnk005df9e0
{
public:
    float FUN_005df9e0(float, float);
};

class RHMaskPointStorage
{
public:
    ~RHMaskPointStorage()
    {
        Destroy(m_first, m_last);
        m_allocator.deallocate(m_first, m_end - m_first);
        m_first = 0;
        m_last = 0;
        m_end = 0;
    }

    void Destroy(SBGeoPoint2D *first, SBGeoPoint2D *last)
    {
        for (; first != last; ++first)
            first->FUN_0044e990(0);
    }

    SBGeoPoint2D *begin() { return m_first; }
    SBGeoPoint2D *end() { return m_last; }

    std::allocator<SBGeoPoint2D> m_allocator;
    SBGeoPoint2D *m_first;
    SBGeoPoint2D *m_last;
    SBGeoPoint2D *m_end;
};

class RHMobileUnk00611360 : public RHMaskPointStorage
{
public:
    RHMobileUnk00611360();
    ~RHMobileUnk00611360();
    unsigned long FUN_00610f30() const;
    int m_10;
    bool m_14;
    char m_18[4];
    SBGeoPoint2D m_1c;
};

class RHUnkSectorPoints
{
public:
    SBGeoPoint2D &FUN_006112c0(unsigned int index);
};

class RHMobileUnk006100e0
{
public:
    ~RHMobileUnk006100e0();
    float FUN_00610520(float x);
};

class SBGeoSegment2D
{
public:
    SBGeoSegment2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    ~SBGeoSegment2D()
    {
        ((RHMobileUnk006100e0 *)this)->~RHMobileUnk006100e0();
    }
    SBGeoPoint2D &First() { return *(SBGeoPoint2D *)&m_00[0]; }
    SBGeoPoint2D &Second() { return *(SBGeoPoint2D *)&m_00[8]; }
    float FUN_00610520(float x) { return ((RHMobileUnk006100e0 *)this)->FUN_00610520(x); }
    void Set(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
    {
        First() = first;
        Second() = second;
    }
    unsigned char m_00[0x10];
};

class RHMaskObstacle
{
public:
    char m_00[0x24];
    SBGeoBoundingBox2D m_24; // +0x24
    char m_38[0x44];
    RHElementAreaShape m_7c; // +0x7c
    char m_7d[0x2b];
    RHShadowUnk005df9e0 m_a8; // +0xa8
    char m_a9[0x57];
    RHShadowUnk005df9e0 m_100; // +0x100
};

class RHMaskPointArray : public RHMobileUnk00611360
{
public:
    void InsertLast(const SBGeoPoint2D &);
    SBGeoPoint2D *FUN_00524840(SBGeoPoint2D *first, SBGeoPoint2D *last);
};

inline RHMobileUnk00611360::~RHMobileUnk00611360()
{
    ((RHMaskPointArray *)this)->FUN_00524840(begin(), end());
}

#include "RHSeqList.h"

#include "RHCopyPointers.h"

class RHMaskObstacleStorage
{
public:
    RHMaskObstacleStorage(const std::allocator<void *> &allocator)
        : m_allocator(allocator), m_first(0), m_last(0), m_end(0)
    {
    }

    ~RHMaskObstacleStorage()
    {
        Destroy(m_first, m_last);
        m_allocator.deallocate(m_first, m_end - m_first);
        m_first = 0;
        m_last = 0;
        m_end = 0;
    }

    void Destroy(void **first, void **last);
    void **begin() { return m_first; }
    void **end() { return m_last; }

    std::allocator<void *> m_allocator;
    void **m_first;
    void **m_last;
    void **m_end;
};

class RHMaskObstacleArray : public RHMaskObstacleStorage
{
public:
    ~RHMaskObstacleArray()
    {
        Erase(begin(), end());
    }

    void **Erase(void **first, void **last)
    {
        void **result = FUN_004598e0(last, end(), first);
        Destroy(result, end());
        m_last = result;
        return first;
    }

    unsigned int size() const { return m_first == 0 ? 0 : m_last - m_first; }
    void **Ucopy(void *const *, void *const *, void **);

    void Construct(void **dest, void *const &value)
    {
        ((RHSeqList *)this)->CopyData((RHSequenceElement **)dest, (RHSequenceElement *const *)&value);
    }

    void Ufill(void **dest, unsigned int count, void *const &value)
    {
        for (; count > 0; --count, ++dest)
            Construct(dest, value);
    }

    void Insert(void **pos, unsigned int count, void *const &value)
    {
        if ((unsigned int)(m_end - m_last) < count)
        {
            unsigned int capacity = size() + (count < size() ? size() : count);
            void **storage = (void **)::operator new((int)capacity < 0 ? 0 : capacity * 4);
            void **next = InlineUcopy(m_first, pos, storage);
            Ufill(next, count, value);
            InlineUcopy(pos, m_last, next + count);
            ::operator delete(m_first);
            m_end = storage + capacity;
            m_last = storage + size() + count;
            m_first = storage;
        }
        else if ((unsigned int)(m_last - pos) < count)
        {
            InlineUcopy(pos, m_last, pos + count);
            Ufill(m_last, count - (m_last - pos), value);
            for (void **p = pos; p != m_last; ++p)
                *p = value;
            m_last += count;
        }
        else if (count > 0)
        {
            Ucopy(m_last - count, m_last, m_last);
            void **last = m_last - count;
            void **dest = m_last;
            while (pos != last)
                *--dest = *--last;
            for (void **p = pos; p != pos + count; ++p)
                *p = value;
            m_last += count;
        }
    }

    void **InlineUcopy(void *const *first, void *const *last, void **dest)
    {
        for (; first != last; ++dest, ++first)
            Construct(dest, *first);
        return dest;
    }

    void InsertLast(void *const &value)
    {
        Insert(m_last, 1, value);
        m_dirty = true;
    }

    RHMaskObstacleArray(const std::allocator<void *> &allocator = std::allocator<void *>())
        : RHMaskObstacleStorage(allocator), m_dirty(true)
    {
    }

    int m_10;
    bool m_dirty;
};

class RHUnkMaskObstacleTable
{
public:
    char m_pad0[0x64];
    void **m_entries;
};

#include "RHFastFindGridCore.h"

class RHMask
{
public:
    RHMask();
    ~RHMask();
    void InitializeFromProtoStream(SBFile &, RHFastFindGrid *);
    void Emit(SBFile &, RHFastFindGrid *);
    bool IsAppliedToPointCharacter(const SBGeoPoint2D &point) const;
    bool IsAppliedToPointProjectile(const SBGeoPoint2D &point) const;
    bool IsAppliedToPoint(const SBGeoPoint3D &point, bool flag) const;
    unsigned char FUN_00524800(unsigned long index);

    bool m_00; // +0x00
    unsigned long m_flags; // +0x04
    SBGeoBoundingBox2D m_box; // +0x08
    float m_1c; // +0x1c
    unsigned short m_size; // +0x20
    unsigned char *m_data; // +0x24
    RHMaskPointArray m_points28; // +0x28
    RHMaskPointArray m_points4c; // +0x4c
    RHMaskObstacleArray m_obstacles; // +0x70
};

#endif
