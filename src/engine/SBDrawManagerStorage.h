#ifndef SB_DRAW_MANAGER_STORAGE_H
#define SB_DRAW_MANAGER_STORAGE_H

#include <utility>
#include <list>
#include <string>

class SBDrawUnk005fc3b0Point
{
public:
    SBDrawUnk005fc3b0Point();
    ~SBDrawUnk005fc3b0Point();
    float m_x;
    float m_y;
};

struct SBDrawUnk005eec00Edge
{
    unsigned char m_00;
    char m_01[3];
    int m_04;
    unsigned long m_08;
    int m_0c;
    unsigned long m_10;
    int m_14;
    int m_18;
};

class SBDrawUnk005f0090Node
{
public:
    char m_pad0[0x0c];
    unsigned long m_key;
    void *m_object;
    unsigned short m_width;
    unsigned short m_height;
};

class SBDrawUnk005f0090
{
public:
    char m_pad0[4];
    SBDrawUnk005f0090Node *m_head;
    SBDrawUnk005f0090Node *FUN_005f0090(const unsigned long &);
    SBDrawUnk005f0090Node *FUN_005f01a0(const unsigned long &);
};

struct SBDrawUnk005efc10Iterator
{
    SBDrawUnk005f0090Node *m_node;
    SBDrawUnk005efc10Iterator() {}
    SBDrawUnk005efc10Iterator(SBDrawUnk005f0090Node *node) : m_node(node) {}
    bool operator==(const SBDrawUnk005efc10Iterator &other) const { return m_node == other.m_node; }
    bool operator!=(const SBDrawUnk005efc10Iterator &other) const { return m_node != other.m_node; }
    void FUN_005effc0();
    SBDrawUnk005efc10Iterator &operator++()
    {
        FUN_005effc0();
        return *this;
    }
    SBDrawUnk005efc10Iterator operator++(int)
    {
        SBDrawUnk005efc10Iterator previous = *this;
        FUN_005effc0();
        return previous;
    }
};

struct SBDrawUnk005e4f70Surface
{
    void *m_object;
    unsigned short m_width;
    unsigned short m_height;
    unsigned long m_color;
    unsigned long m_0c;
    bool m_locked;
    void *m_section;
};

typedef std::pair<const unsigned long, SBDrawUnk005e4f70Surface> SBDrawUnk005e4f70Pair;
typedef std::pair<SBDrawUnk005efc10Iterator, bool> SBDrawUnk005ef440Result;

struct SBDrawDecNode
{
    static SBDrawDecNode *&Left(SBDrawDecNode *node) { return node->m_00; }
    SBDrawDecNode *m_00;
    SBDrawDecNode *m_04;
    SBDrawDecNode *m_08;
    unsigned long m_0c;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    int m_20;
    int m_24;
    int m_28;
};

struct SBDrawSurfaceEntry;

class SBDrawUnk005efc10
{
public:
    char m_00[4];
    SBDrawUnk005f0090Node *m_head;
    unsigned m_08;
    unsigned m_size;
    void FUN_005e3ed0();
    ~SBDrawUnk005efc10();
    SBDrawUnk005efc10Iterator FUN_005efa90(SBDrawUnk005efc10Iterator, SBDrawUnk005efc10Iterator);
    SBDrawUnk005efc10Iterator FUN_005ef570(SBDrawUnk005efc10Iterator);
    typedef SBDrawDecNode Node;
    static Node *&Left(Node *node) { return node->m_00; }
    static Node *&Parent(Node *node) { return node->m_04; }
    static Node *&Right(Node *node) { return node->m_08; }
    static int &Color(Node *node) { return node->m_28; }
    Node *&EraseLeftmost() { return *(Node **)m_head; }
    Node *&EraseRightmost() { return *(Node **)((char *)m_head + 8); }
    void FUN_005efc30(SBDrawUnk005f0090Node *);
    SBDrawUnk005f0090Node *&Root() { return *(SBDrawUnk005f0090Node **)((char *)m_head + 4); }
    SBDrawUnk005f0090Node *&Leftmost() { return *(SBDrawUnk005f0090Node **)m_head; }
    SBDrawUnk005f0090Node *&Rightmost() { return *(SBDrawUnk005f0090Node **)((char *)m_head + 8); }
    SBDrawUnk005efc10Iterator Begin() { return SBDrawUnk005efc10Iterator(Leftmost()); }
    SBDrawUnk005efc10Iterator End() { return SBDrawUnk005efc10Iterator(m_head); }
    SBDrawUnk005efc10Iterator FUN_005efc10(const unsigned long &);
    SBDrawUnk005efc10Iterator FUN_005efbc0(const unsigned long &);
    SBDrawUnk005efc10Iterator FUN_005f0070(const unsigned long &);
    SBDrawUnk005ef440Result FUN_005ef440(const SBDrawUnk005e4f70Pair &);
    SBDrawUnk005efc10Iterator FUN_005efcc0(SBDrawDecNode *, SBDrawDecNode *, const SBDrawSurfaceEntry &);
    SBDrawDecNode *&InsertRoot() { return ((SBDrawDecNode *)m_head)->m_04; }
    void Lrotate(SBDrawDecNode *);
    void Rrotate(SBDrawDecNode *);
};

struct SBDrawUnk005e5ec0Surface
{
    void **m_vtable;
};

class SBDrawDriverList
{
public:
    ~SBDrawDriverList()
    {
        typedef std::list<std::string>::iterator (std::list<std::string>::*Erase)(
            std::list<std::string>::iterator, std::list<std::string>::iterator);
        Erase erase = &std::list<std::string>::erase;
        (m_list.*erase)(m_list.begin(), m_list.end());
    }
    void Add(const std::string &name)
    {
        m_list.push_back(name);
        m_dirty = true;
    }
    std::list<std::string> m_list;
    std::list<std::string>::iterator m_current;
    bool m_dirty;
    char m_pad11[0x0f];
    std::string m_text;
};

#endif
