#ifndef RHFRAMEHOLDERSTRINGMAP_H
#define RHFRAMEHOLDERSTRINGMAP_H

#include "Decomp.h"
#include "RHUnk00641782.h"
#include <functional>
#include <string>
#include <utility>

struct RHFrameTreeLinksB24
{
    RHFrameTreeLinksB24 *m_left;
    RHFrameTreeLinksB24 *m_parent;
    RHFrameTreeLinksB24 *m_right;
};

extern RHFrameTreeLinksB24 *g_unk0x006c0b24;

struct RHTreeInc00509910
{
    RHFrameTreeLinksB24 *m_node;
    void FUN_00509910();
};

struct RHFrameHolderStringNode
{
    RHFrameHolderStringNode *m_00;
    RHFrameHolderStringNode *m_04;
    RHFrameHolderStringNode *m_08;
    std::pair<const std::string, void *> m_0c;
    int m_20;
};

static inline RHFrameHolderStringNode *FrameHolderStringNil()
{
    return (RHFrameHolderStringNode *)g_unk0x006c0b24;
}

struct RHFrameHolderStringIterator
{
    RHFrameHolderStringNode *m_node;
    RHFrameHolderStringIterator operator++(int)
    {
        RHFrameHolderStringIterator previous = *this;
        ((RHTreeInc00509910 *)this)->FUN_00509910();
        return previous;
    }
};

class RHFrameHolderStringMap
{
public:
    RHFrameHolderStringMap(const std::less<std::string> &compare = std::less<std::string>(), const std::allocator<void *> &allocator = std::allocator<void *>());
    ~RHFrameHolderStringMap();
    RHFrameHolderStringIterator FUN_00507390(RHFrameHolderStringIterator, RHFrameHolderStringIterator);
    RHFrameHolderStringIterator FUN_00508370(RHFrameHolderStringIterator);
    void FUN_005088a0(RHFrameHolderStringNode *);
    inline void RotateLeft(RHFrameHolderStringNode *node)
    {
        RHUnk00641782 lock;
        RHFrameHolderStringNode *right = node->m_08;
        node->m_08 = right->m_00;
        if (right->m_00 != FrameHolderStringNil()) right->m_00->m_04 = node;
        right->m_04 = node->m_04;
        if (node == m_head->m_04) m_head->m_04 = right;
        else if (node == node->m_04->m_00) node->m_04->m_00 = right;
        else node->m_04->m_08 = right;
        right->m_00 = node;
        node->m_04 = right;
    }
    inline void RotateRight(RHFrameHolderStringNode *node)
    {
        RHUnk00641782 lock;
        RHFrameHolderStringNode *left = node->m_00;
        node->m_00 = left->m_08;
        if (left->m_08 != FrameHolderStringNil()) left->m_08->m_04 = node;
        left->m_04 = node->m_04;
        if (node == m_head->m_04) m_head->m_04 = left;
        else if (node == node->m_04->m_08) node->m_04->m_08 = left;
        else node->m_04->m_00 = left;
        left->m_08 = node;
        node->m_04 = left;
    }
    static RHFrameHolderStringNode *&Left(RHFrameHolderStringNode *node) { return node->m_00; }
    static RHFrameHolderStringNode *&Parent(RHFrameHolderStringNode *node) { return node->m_04; }
    static RHFrameHolderStringNode *&Right(RHFrameHolderStringNode *node) { return node->m_08; }
    static int &Color(RHFrameHolderStringNode *node) { return node->m_20; }
    RHFrameHolderStringNode *&Root() { return m_head->m_04; }
    RHFrameHolderStringNode *&Leftmost() { return m_head->m_00; }
    RHFrameHolderStringNode *&Rightmost() { return m_head->m_08; }
    std::allocator<void *> m_allocator;
    std::less<std::string> m_comparator;
    RHFrameHolderStringNode *m_head;
    bool m_08;
    unsigned m_count;
};

extern unsigned int g_unk0x006c0b20;

inline RHFrameHolderStringMap::RHFrameHolderStringMap(const std::less<std::string> &compare, const std::allocator<void *> &allocator)
    : m_allocator(allocator), m_comparator(compare), m_08(false)
{
    RHUnk00641782 lock;
    if (g_unk0x006c0b24 == 0)
    {
        RHFrameHolderStringNode *node = (RHFrameHolderStringNode *)operator new(sizeof(RHFrameHolderStringNode));
        node->m_04 = 0;
        node->m_20 = 1;
        g_unk0x006c0b24 = (RHFrameTreeLinksB24 *)node;
        g_unk0x006c0b24->m_left = 0;
        g_unk0x006c0b24->m_right = 0;
    }
    ++g_unk0x006c0b20;
    RHFrameHolderStringNode *sentinel = FrameHolderStringNil();
    RHFrameHolderStringNode *node = (RHFrameHolderStringNode *)operator new(sizeof(RHFrameHolderStringNode));
    node->m_04 = sentinel;
    node->m_20 = 0;
    m_head = node;
    m_count = 0;
    m_head->m_00 = m_head;
    m_head->m_08 = m_head;
}

inline RHFrameHolderStringMap::~RHFrameHolderStringMap()
{
    RHFrameHolderStringIterator first;
    first.m_node = m_head->m_00;
    RHFrameHolderStringIterator last;
    last.m_node = m_head;
    FUN_00507390(first, last);
    operator delete(m_head);
    m_head = 0;
    m_count = 0;
    {
        RHUnk00641782 lock;
        if (--g_unk0x006c0b20 == 0)
        {
            operator delete(g_unk0x006c0b24);
            g_unk0x006c0b24 = 0;
        }
    }
}

#endif
