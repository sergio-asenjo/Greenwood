#ifndef RHSOUNDSOURCEMANAGERCORE_H
#define RHSOUNDSOURCEMANAGERCORE_H

#include "Decomp.h"
#include "RHSoundCacheCore.h"
#include "RHTreeDec.h"
#include <utility>

class RHSoundSource;
class RHSoundCache;
class SBFile;

// SIZE 0x20
class RHSoundSourceArray
{
public:
    RHSoundSourceArray()
    {
        undefined allocator;
        *(undefined *)&m_grow = allocator;
        m_first = 0;
        m_last = 0;
        m_end = 0;
        m_changed = true;
    }
    ~RHSoundSourceArray();
    int m_grow; // 0x00
    RHSoundSource **m_first; // 0x04
    RHSoundSource **m_last; // 0x08
    RHSoundSource **m_end; // 0x0c
    RHSoundSource **m_search; // 0x10
    bool m_changed; // 0x14
    bool m_searching; // 0x15
    int m_index; // 0x18
    RHSoundSource *m_value; // 0x1c

    int GetSize() const { return m_first == 0 ? 0 : m_last - m_first; }
    RHSoundSource *operator[](unsigned short index) { return m_first[index]; }
    RHSoundSource **begin() { return m_first; }
    RHSoundSource **end() { return m_last; }
    void RemoveAll();
    void InsertLast(RHSoundSource *const &value);
    long Find(RHSoundSource *const &value, bool searching = true)
    {
        m_changed = false;
        m_value = value;
        int count = GetSize();
        m_search = m_first;
        int index = 0;
        m_searching = searching;
        for (; index < count; ++index, ++m_search)
            if (*m_search == value)
                break;
        m_index = index < count ? index : -1;
        return m_index;
    }
};

// SIZE 0x24
class RHSoundSourceManager
{
public:
    RHSoundSourceManager(RHSoundCache *cache);
    ~RHSoundSourceManager();
    RHSoundSource *GetSoundSource(unsigned short id);
    RHSoundSource *FUN_005b4e00(unsigned short id);
    bool AddSoundSource(RHSoundSource *source);
    bool Serialize(SBFile &file);
    void RHUnk005b4ae0();
    void FUN_005b4b50(void *, void *, void *);
    void FUN_005b4db0();
    bool FUN_005b4f00(RHSoundSource *source);
    void Emit(SBFile &file, RHSoundSource *source, unsigned short id);

    undefined m_00[4]; // 0x00
    RHSoundSourceArray m_sources; // 0x04
};

extern unsigned g_unk0x006c1084;

class RHSoundSourceIDTree
{
public:
    struct Node
    {
        Node *m_left;
        Node *m_parent;
        Node *m_right;
        unsigned long m_key;
        int m_color;
        static Node *&Left(Node *node) { return node->m_left; }
    };
    struct Iterator
    {
        Node *m_node;
        Iterator() {}
        Iterator(Node *node) : m_node(node) {}
        bool operator!=(const Iterator &other) const { return m_node != other.m_node; }
        Iterator operator++(int);
        Iterator &operator++();
    };
    typedef std::pair<Iterator, bool> Pair;
    RHSoundSourceIDTree();
    ~RHSoundSourceIDTree()
    {
        Iterator first(Leftmost());
        Iterator last(m_head);
        FUN_005aa090(first, last);
        operator delete(m_head);
        m_head = 0;
        m_size = 0;
        {
            RHUnk00641782Lock lock;
            if (--g_unk0x006c1084 == 0) {
                operator delete(g_unk0x006c1088);
                g_unk0x006c1088 = 0;
            }
        }
    }
    char m_00[4];
    Node *m_head;
    unsigned m_08;
    unsigned m_size;
    Node *&Root() { return m_head->m_parent; }
    Node *&Leftmost() { return m_head->m_left; }
    Node *&Rightmost() { return m_head->m_right; }
    Iterator Begin() { return Iterator(Leftmost()); }
    static Node *&Left(Node *node) { return node->m_left; }
    static Node *&Parent(Node *node) { return node->m_parent; }
    static Node *&Right(Node *node) { return node->m_right; }
    static int &Color(Node *node) { return node->m_color; }
    Iterator FUN_005aa090(Iterator, Iterator);
    Iterator FUN_005aa200(Iterator);
    void Lrotate(Node *);
    void Rrotate(Node *);
    Iterator FUN_005b5420(Node *, Node *, const unsigned long &);
    Pair FUN_005b52f0(const unsigned long &);
    void FUN_005aa720(Node *);
    static Node *FUN_005b1540(Node *);
};

inline void RHSoundSourceIDTree::Lrotate(Node *x)
{
    RHUnk00641782Lock lock;
    Node *y = x->m_right;
    x->m_right = y->m_left;
    if (y->m_left != (Node *)g_unk0x006c1088)
        y->m_left->m_parent = x;
    y->m_parent = x->m_parent;
    if (x == Root())
        Root() = y;
    else if (x == x->m_parent->m_left)
        x->m_parent->m_left = y;
    else
        x->m_parent->m_right = y;
    y->m_left = x;
    x->m_parent = y;
}

inline void RHSoundSourceIDTree::Rrotate(Node *x)
{
    RHUnk00641782Lock lock;
    Node *y = x->m_left;
    x->m_left = y->m_right;
    if (y->m_right != (Node *)g_unk0x006c1088)
        y->m_right->m_parent = x;
    y->m_parent = x->m_parent;
    if (x == Root())
        Root() = y;
    else if (x == x->m_parent->m_right)
        x->m_parent->m_right = y;
    else
        x->m_parent->m_left = y;
    y->m_right = x;
    x->m_parent = y;
}

#endif
