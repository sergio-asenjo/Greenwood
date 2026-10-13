#ifndef SB_RESOURCE_MANAGER_H
#define SB_RESOURCE_MANAGER_H

#include <string>
#include <vector>

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
    ~SBResourceSurfaceArray() { m_values.erase(m_values.begin(), m_values.end()); }
    int Size() const { return m_values.begin() == 0 ? 0 : m_values.end() - m_values.begin(); }
    void Assign(const SBResourceSurfaceArray &, unsigned);
};

struct SBResourceUnkKeyNode
{
    char m_00[0x0c];
    unsigned long m_key;
};

struct SBResourceUnkKeyIterator
{
    SBResourceUnkKeyNode *m_node;
    SBResourceUnkKeyIterator(SBResourceUnkKeyNode *node) : m_node(node) {}
};

class SBResourceUnkTreeEnd
{
public:
    char m_00[4];
    SBResourceUnkKeyNode *m_head;
    SBResourceUnkKeyIterator FUN_00617690();
};

struct SBResourceUnk00605440Node
{
    char m_00[0x0c];
    unsigned long m_key;
    char m_10[8];
    unsigned short m_18;
    unsigned short m_1a;
};

class SBResourceUnk00605440
{
public:
    char m_00[4];
    SBResourceUnk00605440Node *m_head;
    SBResourceUnk00605440Node *FUN_00605440(const unsigned long &);
};

class SBGeoPoint2D;
class SBFile;

class SBResourceManager
{
public:
    struct Element { char m_00[16]; };
    template<class T> struct Node
    {
        char m_00[0x0c];
        unsigned long m_key;
        char m_10[4];
        T *m_first;
        T *m_last;
    };
    class Tree44
    {
    public:
        struct Iterator
        {
            Node<unsigned long> *m_node;
            Iterator() {}
            Iterator(Node<unsigned long> *node) : m_node(node) {}
            Iterator(const Iterator &other) : m_node(other.m_node) {}
        };
        char m_00[4];
        Node<unsigned long> *m_head;
        Node<unsigned long> *FUN_00605220(const unsigned long &);
        Iterator &FUN_00602580(Iterator &, const unsigned long &);
        Iterator &FUN_006013a0(Iterator &, const unsigned long &);
        Node<unsigned long> *FUN_00605770(const unsigned long &);
        Iterator &FUN_00601210(Iterator &, Node<unsigned long> *, Node<unsigned long> *);
    };
    class Tree84
    {
    public:
        char m_00[4];
        Node<Element> *m_head;
        Node<Element> *FUN_00605660(const unsigned long &);
        Node<Element> *&FUN_00604d30(Node<Element> *&, const unsigned long &);
    };
    struct ResourceNode
    {
        char m_00[0x0c];
        unsigned long m_key;
        char m_10[8];
        unsigned long m_type;
    };
    class Tree54
    {
    public:
        char m_00[4];
        ResourceNode *m_head;
        ResourceNode *FUN_00605330(const unsigned long &);
        ResourceNode *&FUN_00601650(ResourceNode *&, const unsigned long &);
    };
    class Tree34
    {
    public:
        char m_00[4];
        SBResourceUnkKeyNode *m_head;
        SBResourceUnkKeyNode *FUN_005093e0(const unsigned long &);
    };
    class Tree74
    {
    public:
        char m_00[4];
        SBResourceUnkKeyNode *m_head;
        SBResourceUnkKeyNode *FUN_00605550(const unsigned long &);
        SBResourceUnkKeyNode *&FUN_00601bd0(SBResourceUnkKeyNode *&, const unsigned long &);
        SBResourceUnkKeyNode *&FUN_006042a0(SBResourceUnkKeyNode *&, const unsigned long &);
    };
    char m_00[0x34];
    Tree34 m_34;
    char m_3c[8];
    Tree44 m_44;
    char m_4c[8];
    Tree54 m_54;
    char m_5c[8];
    SBResourceUnk00605440 m_64;
    char m_6c[8];
    Tree74 m_74;
    char m_7c[8];
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
    bool FUN_005fd8e0(int, unsigned long);
    bool FUN_005fdcc0(int, unsigned long);
    bool FUN_005fe000(int, unsigned long);
    bool FUN_005fe380(int, unsigned long);
    bool FUN_005fe970(int, unsigned long);
    bool FUN_005fef60(int, unsigned long);
    bool FUN_005ff3a0(int, unsigned long);
    bool FUN_005ff730(int, unsigned long);
    bool FUN_005ffac0(int, unsigned long);
    bool FUN_005ffe50(int, unsigned long);
};

class RHMapWideText;

class RHMapResources
{
public:
    bool FUN_00600fc0(unsigned);
    bool FUN_006009e0(unsigned, unsigned, RHMapWideText &);
    bool FUN_00600bb0(unsigned long, unsigned int, std::string &);
};

#endif
