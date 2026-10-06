// RHGroundMark — declarations shared by RHGroundMark.cpp (decompiled TU) and
// RHGroundMark_stubs.cpp (external-symbol stubs).
//
// BINDING (0x0051c380 -> RHGroundMark::Serialize(SBFile&)): see src/RHGroundMark.cpp.
//
// Member layout derived from the target instructions of
// RHGroundMark::Serialize (0x0051c380):
//   - +0x14: an SBList<RHGroundInfo> at +0x14 (head pointer at +0x04, count at
//     +0x08, cursor at +0x0c, valid flag at +0x10, index at +0x14);
//   - RHGroundInfo = SBGeoPoint2D (8 bytes) + two unsigned shorts.

#include "SB.h"

inline void *operator new(unsigned int, void *p) { return p; }

class SBGeoPoint2D
{
public:
    float m_x;
    float m_y;

    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    bool Serialize(SBFile &file);
};

struct RHGroundInfo
{
    SBGeoPoint2D m_point;
    unsigned short m_a;
    unsigned short m_b;

    RHGroundInfo();
    RHGroundInfo(const RHGroundInfo &other);
};

struct RHGroundInfoNode
{
    RHGroundInfoNode *m_next;
    RHGroundInfoNode *m_prev;
    RHGroundInfo m_data;
};

class RHGroundInfoIter
{
public:
    void *m_p;
    RHGroundInfoIter() : m_p(0) {}
    RHGroundInfoIter(void *p) : m_p(p) {}
};

class RHGroundInfoList
{
public:
    char m_pad0[4];
    RHGroundInfoNode *m_head; // [0x04]
    int m_count;              // [0x08]
    RHGroundInfoNode *m_cur;  // [0x0c]
    char m_valid;             // [0x10]
    char m_pad1[3];
    int m_index;              // [0x14]

    void GoTo(int i);
    void Clear(void *out, RHGroundInfoNode *first, RHGroundInfoNode *last);

    RHGroundInfoIter end() { return RHGroundInfoIter(m_head); }

    RHGroundInfoNode *Buynode(RHGroundInfoNode *narg, RHGroundInfoNode *parg)
    {
        RHGroundInfoNode *s = (RHGroundInfoNode *)::operator new(0x14);
        s->m_next = narg != 0 ? narg : s;
        s->m_prev = parg != 0 ? parg : s;
        return s;
    }

    void Construct(RHGroundInfo *p, const RHGroundInfo &v)
    {
        new (p) RHGroundInfo(v);
    }

    RHGroundInfoIter insert(RHGroundInfoIter pos, const RHGroundInfo &x)
    {
        RHGroundInfoNode *s = (RHGroundInfoNode *)pos.m_p;
        s->m_prev = Buynode(s, s->m_prev);
        s = s->m_prev;
        s->m_prev->m_next = s;
        Construct(&s->m_data, x);
        ++m_count;
        return RHGroundInfoIter(s);
    }
};

class RHGroundMark
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    char m_pad0[0x14];
    RHGroundInfoList m_list;
};

void RHSerializeName(SBFile &file, const char *name);
