#ifndef SB_RESOURCE_MANAGER_H
#define SB_RESOURCE_MANAGER_H

#include <string>
#include <vector>

template<unsigned int S, unsigned int C, unsigned int I> class SBResourceTreeStorage;

// SIZE 0x10
template<class N, unsigned int S, unsigned int C, unsigned int I> class SBResourceTreeRoot
{
public:
    SBResourceTreeRoot(const std::allocator<char> &compare = std::allocator<char>(),
        bool multi = false, const std::allocator<char> &allocator = std::allocator<char>())
        : m_allocator(allocator), m_compare(compare), m_multi(multi)
    {
        ((SBResourceTreeStorage<S, C, I> *)this)->Initialize();
    }
    ~SBResourceTreeRoot()
    {
        ((SBResourceTreeStorage<S, C, I> *)this)->Dispose();
    }
    std::allocator<char> m_allocator; // 0x00
    std::allocator<char> m_compare; // 0x01
    N *m_head; // 0x04
    bool m_multi; // 0x08
    unsigned int m_size; // 0x0c
};

template<class T> struct SBResourceTreeFindIterator
{
    T *m_node;
    SBResourceTreeFindIterator() {}
    SBResourceTreeFindIterator(T *node) : m_node(node) {}
};

class SBResourceSurfaceArray
{
public:
    std::vector<unsigned long> m_values;
    unsigned long *m_search;
    bool m_changed;
    bool m_searching;
    int m_index;
    unsigned long m_value;
    SBResourceSurfaceArray() : m_changed(true) {}
    SBResourceSurfaceArray(const SBResourceSurfaceArray &other)
    {
        FUN_006069e0(other);
    }
    ~SBResourceSurfaceArray() { m_values.erase(m_values.begin(), m_values.end()); }
    int Size() const { return m_values.begin() == 0 ? 0 : m_values.end() - m_values.begin(); }
    void Assign(const SBResourceSurfaceArray &, unsigned);
    void FUN_006069e0(const SBResourceSurfaceArray &);
};

#include "SBResourceUnkKeyTree.h"

struct SBResourceUnk00605440Node
{
    char m_00[0x0c];
    unsigned long m_key;
    char m_10[8];
    unsigned short m_18;
    unsigned short m_1a;
};

class SBResourceUnk00605440 : public SBResourceTreeRoot<SBResourceUnk00605440Node, 0x20, 0x1c, 0x64>
{
public:
    SBResourceUnk00605440Node *FUN_00605440(const unsigned long &);
};

class SBGeoPoint2D;
class SBFile;
struct RHScriptNode;

// SIZE 0x24
class SBResourceFileList
{
public:
    inline SBResourceFileList(const std::allocator<void *> &value = std::allocator<void *>());
    inline ~SBResourceFileList();
    std::allocator<void *> m_allocator; // 0x00
    RHScriptNode *m_head; // 0x04
    int m_count; // 0x08
    RHScriptNode *m_cursor; // 0x0c
    bool m_dirty; // 0x10
    int m_index; // 0x14
    char m_18[0x0c]; // 0x18
};

struct SBResourceTreeLinks;

template<class C> struct SBResourceEmptyText
{
    std::allocator<C> m_allocator;
    C *m_pointer;
    unsigned int m_length;
    unsigned int m_capacity;
    SBResourceEmptyText() : m_allocator(std::allocator<C>()), m_pointer(0), m_length(0), m_capacity(0) {}
    ~SBResourceEmptyText() { ((std::basic_string<C> *)this)->~basic_string(); }
};

template<class C> class SBResourceTextArray
{
public:
    typedef std::basic_string<C> Text;
    typedef std::vector<Text> Values;
    Values m_values;
    char m_10[4];
    bool m_changed;
    char m_15[7];
    SBResourceEmptyText<C> m_text;
    SBResourceTextArray(const SBResourceTextArray &other)
    {
        const Text *first = other.m_values.begin();
        const Text *last = other.m_values.end();
        m_values.clear();
        void (Values::*insert)(Text *, const Text *, const Text *) = &Values::insert;
        (m_values.*insert)(m_values.begin(), first, last);
        m_changed = true;
    }
    void Resize(unsigned int count);
    void Clear() { m_values.clear(); }
};

class SBResourceArrayLifecycle44
{
public:
    void FUN_0051d120();
};

class SBResourceArrayLifecycle74
{
public:
    std::vector<std::wstring> m_values;
    char m_10[12];
    std::wstring m_text;
    ~SBResourceArrayLifecycle74();
};

class SBResourceArrayLifecycle84
{
public:
    std::vector<std::string> m_values;
    char m_10[12];
    std::string m_text;
    ~SBResourceArrayLifecycle84();
};

struct SBResourceTreeIterator
{
    SBResourceTreeLinks *m_node;
    SBResourceTreeIterator() {}
    SBResourceTreeIterator(SBResourceTreeLinks *node) : m_node(node) {}
};

template<unsigned int S, unsigned int C, unsigned int I> class SBResourceTreeStorage
{
public:
    typedef std::pair<SBResourceTreeIterator, bool> InsertResult;
    char m_00[4];
    SBResourceTreeLinks *m_head;
    bool m_multi;
    unsigned int m_size;
    void Initialize();
    void Dispose();
    void Destroy(SBResourceTreeLinks *);
    InsertResult Insert(const unsigned long &);
    SBResourceTreeIterator InsertNode(SBResourceTreeLinks *, SBResourceTreeLinks *, const unsigned long &);
    SBResourceTreeIterator EraseNode(SBResourceTreeLinks *);
    SBResourceTreeIterator EraseRange(SBResourceTreeIterator, SBResourceTreeIterator);
    SBResourceTreeLinks *&Root();
    SBResourceTreeLinks *&Leftmost();
    SBResourceTreeLinks *&Rightmost();
    SBResourceTreeIterator Begin();
    void Lrotate(SBResourceTreeLinks *);
    void Rrotate(SBResourceTreeLinks *);
    static int &Color(SBResourceTreeLinks *);
    static SBResourceTreeLinks *&Left(SBResourceTreeLinks *);
    static SBResourceTreeLinks *&Right(SBResourceTreeLinks *);
    static SBResourceTreeLinks *&Parent(SBResourceTreeLinks *);
    static SBResourceTreeLinks *PostAdvance(SBResourceTreeLinks *&);
    static SBResourceTreeLinks *Minimum(SBResourceTreeLinks *);
    static SBResourceTreeLinks *Maximum(SBResourceTreeLinks *);
};

// SIZE 0x94
class SBResourceManager
{
public:
    SBResourceManager();
    ~SBResourceManager();
    struct Element { char m_00[16]; };
    template<class T> struct Node
    {
        char m_00[0x0c];
        unsigned long m_key;
        char m_10[4];
        T *m_first;
        T *m_last;
    };
    class Tree44 : public SBResourceTreeRoot<Node<unsigned long>, 0x34, 0x30, 0x44>
    {
    public:
        struct Iterator
        {
            Node<unsigned long> *m_node;
            Iterator() {}
            Iterator(Node<unsigned long> *node) : m_node(node) {}
        };
        Node<unsigned long> *FUN_00605220(const unsigned long &);
        Iterator &FUN_00602580(Iterator &, const unsigned long &);
        Iterator FUN_006013a0(const unsigned long &);
        Node<unsigned long> *FUN_00605770(const unsigned long &);
        Iterator FUN_00601210(Iterator, Iterator);
        unsigned int FUN_00601350(const unsigned long &);
    };
    class Tree84 : public SBResourceTreeRoot<Node<Element>, 0x40, 0x3c, 0x84>
    {
    public:
        Node<Element> *FUN_00605660(const unsigned long &);
        Node<Element> *FUN_00605ad0(const unsigned long &);
        SBResourceTreeFindIterator<Node<Element> > FUN_00601ee0(const unsigned long &);
        unsigned int FUN_00601e90(const unsigned long &);
        SBResourceTreeFindIterator<Node<Element> > FUN_00601d50(SBResourceTreeFindIterator<Node<Element> >, SBResourceTreeFindIterator<Node<Element> >);
        Node<Element> *&FUN_00604d30(Node<Element> *&, const unsigned long &);
    };
    struct ResourceNode
    {
        char m_00[0x0c];
        unsigned long m_key;
        SBFile *m_file;
        unsigned long m_position;
        unsigned long m_type;
    };
    class Tree54 : public SBResourceTreeRoot<ResourceNode, 0x20, 0x1c, 0x54>
    {
    public:
        ResourceNode *FUN_00605330(const unsigned long &);
        SBResourceTreeFindIterator<ResourceNode> FUN_00601650(const unsigned long &);
    };
    class Tree34 : public SBResourceTreeRoot<SBResourceUnkKeyNode, 0x18, 0x14, 0x34>
    {
    };
    class Tree74 : public SBResourceTreeRoot<SBResourceUnkKeyNode, 0x40, 0x3c, 0x74>
    {
    public:
        SBResourceUnkKeyNode *FUN_00605550(const unsigned long &);
        SBResourceUnkKeyNode *FUN_006059d0(const unsigned long &);
        unsigned int FUN_00601b80(const unsigned long &);
        SBResourceUnkKeyIterator FUN_00601a40(SBResourceUnkKeyIterator, SBResourceUnkKeyIterator);
        SBResourceUnkKeyIterator FUN_00601bd0(const unsigned long &);
        SBResourceUnkKeyNode *&FUN_006042a0(SBResourceUnkKeyNode *&, const unsigned long &);
    };
    char m_00[0x10];
    SBResourceFileList m_files;
    Tree34 m_34;
    Tree44 m_44;
    Tree54 m_54;
    SBResourceUnk00605440 m_64;
    Tree74 m_74;
    Tree84 m_84;
    bool FUN_005fd710(SBFile &);
    unsigned short FUN_006002d0(unsigned long);
    unsigned short FUN_00600390(unsigned long);
    const SBGeoPoint2D &FUN_00600450(unsigned long);
    unsigned int FUN_00600550(unsigned long);
    unsigned int FUN_00600620(unsigned long);
    bool FUN_00600920(unsigned long, unsigned long, unsigned long &);
    bool FUN_00600db0(unsigned long);
    int FUN_00600f10(unsigned long);
    void FUN_006001d0(Tree44::Iterator &);
    bool FUN_005fd8e0(SBFile *, unsigned long);
    bool FUN_005fdcc0(int, unsigned long);
    bool FUN_005fe000(int, unsigned long);
    bool FUN_005fe380(int, unsigned long);
    bool FUN_005fe970(int, unsigned long);
    bool FUN_005fef60(int, unsigned long);
    bool FUN_005ff3a0(SBFile *, unsigned long);
    bool FUN_005ff730(SBFile *, unsigned long);
    bool FUN_005ffac0(SBFile *, unsigned long);
    bool FUN_005ffe50(SBFile *, unsigned long);
};

#include "RHMapResources.h"

#endif
