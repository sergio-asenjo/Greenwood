#include "SB.h"

class SBGeoVector2D;

class SBGeoPoint2D
{
public:
    SBGeoPoint2D(float, float);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);

    float m_x;
    float m_y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

SBGeoPoint2D operator+(const SBGeoPoint2D &, const SBGeoVector2D &);

class SBGeoBoundingBox2D
{
public:
    void UnkSetOrigin(const SBGeoPoint2D &point)
    {
        m_flag = true;
        m_p0 = point;
    }

    void UnkSetSize(const SBGeoVector2D &vector)
    {
        m_flag = true;
        m_p1 = m_p0 + vector;
    }

    SBGeoPoint2D m_p0;
    SBGeoPoint2D m_p1;
    bool m_flag;
};

class RHMaskPointArray
{
public:
    void InsertLast(const SBGeoPoint2D &);
    char m_bytes[0x24];
};

class RHSequenceElement;
class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **, RHSequenceElement *const *);
};

class RHMaskObstacleArray
{
public:
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

    int m_grow;
    void **m_first;
    void **m_last;
    void **m_end;
    int m_10;
    bool m_dirty;
};

class RHUnkMaskObstacleTable
{
public:
    char m_pad0[0x64];
    void **m_entries;
};

class RHFastFindGrid
{
public:
    char m_pad0[0x3ea4];
    RHUnkMaskObstacleTable *m_3ea4;
};

class RHMask
{
public:
    void InitializeFromProtoStream(SBFile &, RHFastFindGrid *);
    void Emit(SBFile &, RHFastFindGrid *);
    unsigned char FUN_00524800(unsigned long index);

    char m_pad0[4];
    unsigned long m_flags; // +0x04
    SBGeoBoundingBox2D m_box; // +0x08
    float m_1c; // +0x1c
    unsigned short m_size; // +0x20
    unsigned char *m_data; // +0x24
    RHMaskPointArray m_points28; // +0x28
    RHMaskPointArray m_points4c; // +0x4c
    RHMaskObstacleArray m_obstacles; // +0x70
};
