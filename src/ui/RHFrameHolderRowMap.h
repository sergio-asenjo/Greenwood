#ifndef RHFRAMEHOLDERROWMAP_H
#define RHFRAMEHOLDERROWMAP_H

#include "Decomp.h"
#include "RHUnk00641782.h"
#include <map>

class RHFrameHolderRowMap
{
public:
    RHFrameHolderRowMap(const std::less<unsigned long> &compare = std::less<unsigned long>(), const std::allocator<unsigned long> &allocator = std::allocator<unsigned long>());
    ~RHFrameHolderRowMap() { FUN_00503db0(); }
    struct Node
    {
        Node *m_left;
        Node *m_parent;
        Node *m_right;
        unsigned long m_key;
        unsigned long m_value;
        undefined4 m_color;
    };
    struct Iterator
    {
        Iterator() {}
        Iterator(Node *node) : m_node(node) {}
        Node *m_node;
        bool operator==(const Iterator &other) const { return m_node == other.m_node; }
        bool operator!=(const Iterator &other) const { return !(*this == other); }
        void FUN_005097a0();
        static Node *&Left(Node *node) { return node->m_left; }
        void FUN_00509860();
        Iterator operator++(int)
        {
            Iterator previous = *this;
            FUN_00509860();
            return previous;
        }
    };
    typedef std::pair<Iterator, bool> Pair;
    typedef Pair TreePair;
    struct Value
    {
        unsigned long first;
        unsigned long second;
        Value(unsigned long key, unsigned long value) : first(key), second(value) {}
    };
    Iterator Find(const unsigned long &);
    Node *FUN_005093e0(const unsigned long &);
    Iterator End() { Iterator result; result.m_node = m_head; return result; }
    Pair Insert(const Value &);
    TreePair InsertTree(const Value &);
    void FUN_00508000(Node *);
    void FUN_00503db0();
    Iterator FUN_00506ea0(Iterator, Iterator);
    Iterator FUN_00507ae0(Iterator);
    Node *&Root() { return m_head->m_parent; }
    Node *&Leftmost() { return m_head->m_left; }
    Node *&Rightmost() { return m_head->m_right; }
    Iterator begin() { return Iterator(Leftmost()); }
    Iterator FUN_005090e0(Node *, Node *, const Value &);
    void Lrotate(Node *);
    void Rrotate(Node *);
    static Node *&Parent(Node *node) { return node->m_parent; }
    static Node *&Right(Node *node) { return node->m_right; }
    static Node *&Left(Node *node) { return node->m_left; }
    static undefined4 &Color(Node *node) { return node->m_color; }
    unsigned long &operator[](const unsigned long &key)
    {
        TreePair result = InsertTree(Value(key, 0));
        return result.first.m_node->m_value;
    }
    std::allocator<unsigned long> m_allocator;
    std::less<unsigned long> m_comparator;
    Node *m_head;
    bool m_multi;
    unsigned long m_size;
};

extern RHFrameHolderRowMap::Node *g_unk0x006c0b2c;
extern unsigned int g_unk0x006c0b28;

inline RHFrameHolderRowMap::RHFrameHolderRowMap(const std::less<unsigned long> &compare, const std::allocator<unsigned long> &allocator)
    : m_allocator(allocator), m_comparator(compare), m_multi(false)
{
    RHUnk00641782 lock;
    if (g_unk0x006c0b2c == 0)
    {
        Node *node = (Node *)operator new(sizeof(Node));
        node->m_parent = 0;
        node->m_color = 1;
        g_unk0x006c0b2c = node;
        g_unk0x006c0b2c->m_left = 0;
        g_unk0x006c0b2c->m_right = 0;
    }
    ++g_unk0x006c0b28;
    Node *sentinel = g_unk0x006c0b2c;
    Node *node = (Node *)operator new(sizeof(Node));
    node->m_parent = sentinel;
    node->m_color = 0;
    m_head = node;
    m_size = 0;
    m_head->m_left = m_head;
    m_head->m_right = m_head;
}

#endif
