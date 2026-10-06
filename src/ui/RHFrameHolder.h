#ifndef RHFRAMEHOLDER_H
#define RHFRAMEHOLDER_H

#include "SB.h"
#include <map>
#include <string>

template <>
std::map<unsigned short, unsigned short>::_Pairib
std::map<unsigned short, unsigned short>::insert(const value_type &value);

class SBGeoPoint2D
{
public:
    SBGeoPoint2D(float, float);
    ~SBGeoPoint2D();
    float m_x;
    float m_y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
};

template <class T>
class SBArray
{
public:
    int m_grow;
    T *m_first;
    T *m_last;
    T *m_end;
    int m_10;
    bool m_dirty;

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

class RHFrameHolderRowMap
{
public:
    struct Node
    {
        Node *m_left;
        Node *m_parent;
        Node *m_right;
        unsigned long m_key;
        unsigned long m_value;
    };
    struct Iterator
    {
        Node *m_node;
        bool operator==(const Iterator &other) const { return m_node == other.m_node; }
        bool operator!=(const Iterator &other) const { return !(*this == other); }
    };
    struct Pair
    {
        Iterator first;
        bool second;
    };
    struct Value
    {
        unsigned long first;
        unsigned long second;
        Value(unsigned long key, unsigned long value) : first(key), second(value) {}
    };
    Iterator Find(const unsigned long &);
    Iterator End() { Iterator result; result.m_node = m_head; return result; }
    Pair Insert(const Value &);
    Pair InsertTree(const Value &);
    unsigned long &operator[](const unsigned long &key)
    {
        Pair result = InsertTree(Value(key, 0));
        return result.first.m_node->m_value;
    }
    char m_allocator[4];
    Node *m_head;
    char m_comparator[4];
    unsigned long m_size;
};

class SBResourceManager
{
public:
    unsigned short FUN_00600550(unsigned long);
    bool FUN_00600920(unsigned long, unsigned long, unsigned long &);
};

class RHUnk005f4fc0 : public SBFile
{
public:
    RHUnk005f4fc0();
    ~RHUnk005f4fc0();
    int FUN_005f5090(const std::string &, int);
    int FUN_005f5d60(const std::string &, int);
    char m_14[0x44];
};

class RHEngine
{
public:
    unsigned short FUN_004d2340(int);
};

extern RHEngine *g_pEngine;
bool FUN_005f6400(const std::string &);

struct RHFrameHolderRecord
{
    unsigned short m_width;
    unsigned short m_height;
    unsigned long m_size;
    unsigned long m_data;
    unsigned long m_0c;
    bool m_10;
    unsigned short m_12;
};

class RHFrameHolder
{
public:
    bool InitializeSpriteBank();
    unsigned long AddRowFromResource(SBResourceManager *, unsigned long, unsigned short &, SBArray<SBGeoVector2D> &);
    unsigned long FUN_00505980(unsigned long, unsigned long &, unsigned short &, unsigned short &, long &, long &);
    unsigned short FUN_005051a0(unsigned short, SBFile &);
    void FUN_00504b10(unsigned long, unsigned long, unsigned short);
    void Emit(SBResourceManager *, SBArray<SBGeoVector2D> &);

    char m_00[8]; // [0x00, 0x08)
    SBArray<RHFrameHolderRecord> m_frames; // [0x08]: first +0x0c, last +0x10
    char m_20[0x2c]; // [0x20, 0x4c)
    RHFrameHolderRowMap m_rows; // [0x4c]: tree head +0x50
    RHUnk005f4fc0 m_bank; // [0x5c, 0xb4)
    unsigned long m_b4; // [0xb4]: index header
    char m_b8[0x30]; // [0xb8, 0xe8)
    bool m_e8; // [0xe8]: bank-open fallback
};

#endif
