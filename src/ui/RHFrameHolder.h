#ifndef RHFRAMEHOLDER_H
#define RHFRAMEHOLDER_H

#include "SB.h"
#include "Decomp.h"
#include <map>
#include <string>

template <>
std::map<unsigned short, unsigned short>::_Pairib
std::map<unsigned short, unsigned short>::insert(const value_type &value);

// SIZE 0x08
#define SBGEO_POINT2D_VIEW
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float, float);
    ~SBGeoPoint2D();
    float m_x; // 0x00
    float m_y; // 0x04
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

template <class T>
class SBArray
{
public:
    int m_grow; // 0x00
    T *m_first; // 0x04
    T *m_last; // 0x08
    T *m_end; // 0x0c
    undefined4 m_10; // 0x10
    bool m_dirty; // 0x14

    unsigned int Size() const { return m_first == 0 ? 0 : m_last - m_first; }
    unsigned int GetSize() const;
    T &operator[](unsigned long index) { return m_first[index]; }
    void Insert(T *, unsigned int, const T &);
    void Remove(T *, T *);
    void Resize(unsigned int size)
    {
        if (Size() < size)
        {
            T *position = m_last;
            Insert(position, size - GetSize(), T());
        }
        else if (size < GetSize())
            Remove(m_first + size, m_last);
    }
    void RemoveAll() { Remove(m_first, m_last); m_dirty = true; }
    void InsertLast(const T &value) { Insert(m_last, 1, value); m_dirty = true; }
};

// SIZE 0x10
class RHFrameHolderRowMap
{
public:
    struct Node
    {
        Node *m_left; // 0x00
        Node *m_parent; // 0x04
        Node *m_right; // 0x08
        unsigned long m_key; // 0x0c
        unsigned long m_value; // 0x10
        undefined4 m_color; // 0x14
    };
    struct Iterator
    {
        Iterator() {}
        Iterator(Node *node) : m_node(node) {}
        Node *m_node; // 0x00
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
        unsigned long first; // 0x00
        unsigned long second; // 0x04
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
    undefined m_allocator[4]; // 0x00
    Node *m_head; // 0x04
    undefined m_comparator[4]; // 0x08
    unsigned long m_size; // 0x0c
};

// SIZE 0x10
class RHUnk005074d0
{
public:
    typedef RHFrameHolderRowMap::Pair Pair;
    typedef RHFrameHolderRowMap::TreePair TreePair;
    struct Node
    {
        Node *m_left; // 0x00
        Node *m_parent; // 0x04
        Node *m_right; // 0x08
        unsigned short m_key; // 0x0c
        unsigned short m_value; // 0x0e
        undefined4 m_color; // 0x10
    };
    struct Iterator
    {
        Node *m_node; // 0x00
        void FUN_005099c0();
        static Node *&Left(Node *node) { return node->m_left; }
    };
    struct Value
    {
        unsigned short m_key; // 0x00
        unsigned short m_value; // 0x02
    };
    Pair FUN_005074d0(const Value &);
    TreePair FUN_00508950(const Value &);
    RHFrameHolderRowMap::Iterator FUN_005094a0(Node *, Node *, const Value &);
    void Lrotate(Node *);
    void Rrotate(Node *);
    static Node *&Left(Node *node) { return node->m_left; }
    undefined m_00[4]; // 0x00
    Node *m_head; // 0x04
    undefined m_multi; // 0x08
    undefined m_09[3]; // 0x09
    unsigned int m_size; // 0x0c
};

namespace std
{
template <>
void _Construct(RHUnk005074d0::Value *, const RHUnk005074d0::Value &);
}

class SBResourceManager
{
public:
    unsigned int FUN_00600550(unsigned long);
    bool FUN_00600920(unsigned long, unsigned long, unsigned long &);
};

#include "RHUnk005f4fc0.h"

class RHEngine
{
public:
    unsigned int FUN_004d2340(int);
    undefined m_00[0x4790]; // 0x00
    undefined m_4790; // 0x4790
    undefined m_4791; // 0x4791
    undefined m_4792[0x312]; // 0x4792
    undefined m_4aa4; // 0x4aa4
    undefined m_4aa5; // 0x4aa5
    undefined2 m_4aa6; // 0x4aa6
};

extern RHEngine *g_pEngine;
bool FUN_005f6400(const std::string &);

// SIZE 0x14
struct RHFrameHolderRecord
{
    unsigned short m_width; // 0x00
    unsigned short m_height; // 0x02
    unsigned long m_size; // 0x04
    unsigned long m_data; // 0x08
    undefined4 m_0c; // 0x0c
    bool m_10; // 0x10
    unsigned short m_12; // 0x12
};

// SIZE 0x10
class RHUnk00506e00
{
public:
    unsigned int FUN_00506e00() const;
    RHFrameHolderRecord *FUN_00507320(RHFrameHolderRecord *, RHFrameHolderRecord *);
    void FUN_00507020(RHFrameHolderRecord *, unsigned int, const RHFrameHolderRecord &);
    RHFrameHolderRecord *Copy(const RHFrameHolderRecord *first, const RHFrameHolderRecord *last, RHFrameHolderRecord *output)
    {
        for (; first != last; ++output, ++first)
            m_allocator.construct(output, *first);
        return output;
    }
    void Fill(RHFrameHolderRecord *first, unsigned int count, const RHFrameHolderRecord &value)
    {
        for (; count > 0; --count, ++first)
            m_allocator.construct(first, value);
    }
    void Destroy(RHFrameHolderRecord *first, RHFrameHolderRecord *last)
    {
        for (; first != last; ++first)
            m_allocator.destroy(first);
    }
    unsigned int Size() const { return m_first == 0 ? 0 : m_last - m_first; }
    std::allocator<RHFrameHolderRecord> m_allocator; // 0x00
    RHFrameHolderRecord *m_first; // 0x04
    RHFrameHolderRecord *m_last; // 0x08
    RHFrameHolderRecord *m_end; // 0x0c
};

#include "RHFrameDictionary.h"

// SIZE 0x10
class RHUnk005051a0Array
{
public:
    void FUN_00506e30();
    void FUN_00508090(RHUnk005068e0 *, unsigned int, const RHUnk005068e0 &);
    unsigned int Size() const { return m_first == 0 ? 0 : m_last - m_first; }
    undefined4 m_00; // 0x00
    RHUnk005068e0 *m_first; // 0x04
    RHUnk005068e0 *m_last; // 0x08
    RHUnk005068e0 *m_end; // 0x0c
};

// SIZE 0x10
class RHFrameHolderFrameArray : public RHUnk00506e00
{
public:
    RHFrameHolderRecord &operator[](unsigned long index) { return m_first[index]; }
    void Resize(unsigned int count)
    {
        if (Size() < count)
        {
            RHFrameHolderRecord *position = m_last;
            FUN_00507020(position, count - FUN_00506e00(), RHFrameHolderRecord());
        }
        else if (count < FUN_00506e00())
            FUN_00507320(m_first + count, m_last);
    }
};

// SIZE 0x01
class RHUnk00641782
{
public:
    RHUnk00641782();
    ~RHUnk00641782();
    undefined m_00; // 0x00
};

// SIZE 0x10
class RHUnk00507500
{
public:
    RHUnk00507500(const std::less<unsigned short> &compare = std::less<unsigned short>(), const std::allocator<unsigned short> &allocator = std::allocator<unsigned short>())
        : m_allocator(allocator), m_multi(false), m_comparator(compare) { FUN_00509030(); }
    ~RHUnk00507500() { FUN_00504590(); }
    struct Node
    {
        Node *m_left; // 0x00
        Node *m_parent; // 0x04
        Node *m_right; // 0x08
        unsigned short m_key; // 0x0c
        unsigned short m_value; // 0x0e
        undefined4 m_color; // 0x10
    };
    struct Iterator
    {
        Iterator() {}
        Iterator(Node *node) : m_node(node) {}
        Node *m_node; // 0x00
        void FUN_00509a80();
        Iterator operator++(int) { Iterator previous = *this; FUN_00509a80(); return previous; }
    };
    Node *&Root() { return m_head->m_parent; }
    Node *&Leftmost() { return m_head->m_left; }
    Node *&Rightmost() { return m_head->m_right; }
    Iterator begin() { return Iterator(Leftmost()); }
    unsigned short &operator[](const unsigned short &key)
    {
        RHUnk005074d0::Value value = { key, 0 };
        return ((Node *)((RHUnk005074d0 *)this)->FUN_005074d0(value).first.m_node)->m_value;
    }
    void FUN_00504590();
    Iterator FUN_00507500(Iterator, Iterator);
    Iterator FUN_00508a80(Iterator);
    static Node *&Parent(Node *node) { return node->m_parent; }
    static Node *&Right(Node *node) { return node->m_right; }
    static Node *&Left(Node *node) { return node->m_left; }
    static undefined4 &Color(Node *node) { return node->m_color; }
    void Lrotate(Node *);
    void Rrotate(Node *);
    void FUN_00508fa0(Node *);
    void FUN_00509030();
    std::allocator<unsigned short> m_allocator; // 0x00
    Node *m_head; // 0x04
    undefined m_multi; // 0x08
    std::less<unsigned short> m_comparator; // 0x09
    unsigned int m_size; // 0x0c
};

// SIZE 0x18
class RHUnk00613e90
{
public:
    RHUnk00613e90();
    ~RHUnk00613e90();
    undefined m_00[4]; // 0x00
    unsigned short m_width; // 0x04
    unsigned short m_height; // 0x06
    unsigned long m_pitch; // 0x08
    unsigned short m_depth; // 0x0c
    undefined m_0e[2]; // 0x0e
    unsigned short *m_data; // 0x10
    undefined m_14[4]; // 0x14
};

// SIZE 0x10e
class RHUnkFXDraw
{
public:
    bool Unk005e5a00(unsigned long, RHUnk00613e90 &, unsigned long);
    void Unk005e5ea0(RHUnk00613e90 &);
    undefined m_00[0x10c]; // 0x00
    unsigned short m_depth; // 0x10c
};

class SBDrawViewport;

// SIZE 0xec
class RHFrameHolder
{
public:
    bool InitializeSpriteBank();
    unsigned long AddRowFromResource(SBResourceManager *, unsigned long, unsigned short &, SBArray<SBGeoVector2D> &);
    unsigned long FUN_00505980(unsigned long, unsigned long &, unsigned short &, unsigned short &, long &, long &);
    unsigned short FUN_005051a0(unsigned short, SBFile &);
    void FUN_00504c50(unsigned long, unsigned short, unsigned short, unsigned short, unsigned short);
    void FUN_00504bd0(unsigned long, unsigned short, unsigned short, unsigned short, unsigned short);
    void FUN_00504b10(unsigned long, unsigned long, unsigned short);
    void ApplyFogEffect(unsigned short *, unsigned long, unsigned short, unsigned short);
    unsigned long FUN_00504cd0(SBDrawViewport &, unsigned long, int);
    unsigned long FUN_00504eb0(SBDrawViewport &, unsigned long, int);
    unsigned long FUN_00504f70(SBDrawViewport &, unsigned long, unsigned long, int);
    void FUN_005050a0(unsigned short *, unsigned long *, unsigned short, unsigned short, unsigned short, unsigned short, int);
    bool FUN_00504660(unsigned long);
    unsigned long FUN_00504600(unsigned long);
    bool FUN_005058a0(unsigned long);
    unsigned short FUN_00504680(unsigned long);
    unsigned short FUN_005046a0(unsigned long);
    unsigned short FUN_005046c0(unsigned long);
    void FUN_00506120();
    bool FUN_00506160(SBFile &file);
    RHUnk005068e0 *FUN_00505170(unsigned long);
    void Emit(SBResourceManager *, SBArray<SBGeoVector2D> &);
    RHUnkFXDraw *&Draw() { return *(RHUnkFXDraw **)((char *)this + 4); }

    undefined m_00[8]; // 0x00
    RHFrameHolderFrameArray m_frames; // 0x08
    RHUnk005051a0Array m_dictionaries; // 0x18
    undefined m_28[0x24]; // 0x28
    RHFrameHolderRowMap m_rows; // [0x4c]: tree head +0x50
    RHUnk005f4fc0 m_bank; // [0x5c, 0xb4)
    unsigned long m_b4; // [0xb4]: index header
    unsigned long m_b8;
    unsigned long m_bc;
    undefined m_c0[0x28];
    bool m_e8; // [0xe8]: bank-open fallback
};

#endif
