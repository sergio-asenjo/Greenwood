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
#include <memory>

#define SBGEO_POINT2D_VIEW
class SBGeoPoint2D
{
public:
    float m_x;
    float m_y;

    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &other) const;
    bool Serialize(SBFile &file);
};

#include "RHGroundInfo.h"

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
    RHGroundInfoIter operator++(int)
    {
        RHGroundInfoIter previous = *this;
        m_p = ((RHGroundInfoNode *)m_p)->m_next;
        return previous;
    }
};

class RHGroundInfoListStorage
{
public:
    RHGroundInfoListStorage(const std::allocator<RHGroundInfo> &allocator) : m_allocator(allocator)
    {
        RHGroundInfoNode *node = (RHGroundInfoNode *)::operator new(sizeof(RHGroundInfoNode));
        node->m_next = node;
        node->m_prev = node;
        m_head = node;
        m_count = 0;
    }
    ~RHGroundInfoListStorage()
    {
        RHGroundInfoNode *last = m_head;
        RHGroundInfoNode *current = last->m_next;
        while (current != last)
        {
            RHGroundInfoNode *node = current;
            current = current->m_next;
            node->m_prev->m_next = node->m_next;
            node->m_next->m_prev = node->m_prev;
            node->m_data.Destroy(0);
            ::operator delete(node);
            --m_count;
        }
        ::operator delete(m_head);
        m_head = 0;
        m_count = 0;
    }
    std::allocator<RHGroundInfo> m_allocator;
    RHGroundInfoNode *m_head; // [0x04]
    int m_count;              // [0x08]
};

class RHGroundInfoList : public RHGroundInfoListStorage
{
public:
    RHGroundInfoList() : RHGroundInfoListStorage(std::allocator<RHGroundInfo>()), m_valid(true) {}
    // FUNCTION: GAME 0x0051c660
    ~RHGroundInfoList()
    {
        RHGroundInfoNode *last = m_head;
        RHGroundInfoNode *current = last->m_next;
        while (current != last)
        {
            RHGroundInfoNode *node = current;
            current = current->m_next;
            Erase(RHGroundInfoIter(node));
        }
    }
    RHGroundInfoNode *m_cur;
    bool m_valid;
    char m_pad1[3];
    int m_index;
    char m_18[8];
    SBGeoPoint2D m_point;
    unsigned short m_a;
    unsigned short m_b;

    void GoTo(int i);
    void *Clear(void *out, RHGroundInfoNode *first, RHGroundInfoNode *last);
    RHGroundInfoIter Erase(RHGroundInfoIter position);
    void Dispose();

    RHGroundInfoIter end() { return RHGroundInfoIter(m_head); }

    RHGroundInfoNode *Buynode(RHGroundInfoNode *narg, RHGroundInfoNode *parg)
    {
        RHGroundInfoNode *s = (RHGroundInfoNode *)::operator new(0x14);
        s->m_next = narg != 0 ? narg : s;
        s->m_prev = parg != 0 ? parg : s;
        return s;
    }

    static void Construct(RHGroundInfo *p, const RHGroundInfo &v)
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
        m_valid = true;
        ++m_count;
        return RHGroundInfoIter(s);
    }
};

class RHUnk005b5890;
class RHUnk005ef320;
class RHUnkSpriteBank;

// VTABLE: GAME 0x006790b4
class RHGroundMark
{
public:
    RHGroundMark();
    ~RHGroundMark();
    virtual void *FUN_0051bc70(unsigned flags);
    bool AddGroundMark(const SBGeoPoint2D &point, unsigned short type);
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    RHUnk005b5890 *m_sprite;
    int m_surface;
    RHUnk005ef320 *m_drawManager;
    RHUnkSpriteBank *m_spriteBank;
    RHGroundInfoList m_list;
};

void RHSerializeName(SBFile &file, const char *name);
